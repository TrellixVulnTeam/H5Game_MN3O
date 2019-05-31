#include "pw_module_hero_collect.h"
#include "kvorm/pw_orm_collection_human.h"
#include "pw_human.h"
#include "pw_kvorm_uuid_pool.h"
#include "pw_human_oper.h"
#include "pw_logger.h"
#include "pw_heronew_dataset.h"
#include "pw_mail_builder.h"
#include "pw_stage.h"
#include "pw_module_heronew.h"
#include "pw_orm_helper.h"
#include "pw_vip_new_dataset.h"
#include "pw_module_vip_new.h"
#include "pw_module_item.h"
#include "pw_module_daily_bonus.h"

namespace pwngs
{
	ModHeroCollect::ModHeroCollect(Module<Human>::TOwnerPtr ptr)
		: Module<Human>(ptr)
		, m_pOrmHeroCollect(NULL)
	{
	}

	ModHeroCollect::~ModHeroCollect()
	{
	}

	sint32 ModHeroCollect::OrmLoad()
	{
		m_pOrmHeroCollect = m_pOwner->GetOrmCollection()->mutable_humanherocollect();
		InitialLastFreeTime();
		InitialEnergy();
		return 0;
	}

	sint32 ModHeroCollect::InitialLastFreeTime()
	{
		for (sint32 ii = 0; ii < COLLECT_LEVEL_MAX; ++ii)
		{
			SHeroGet* pSHeroGet = g_objHeroCollectDataset.GetHeroCollect(ii);
			pwasserte(pSHeroGet);
			if (0 == m_pOrmHeroCollect->last_free_times[ii])
			{
				if (0 < pSHeroGet->freeStartCd)
				{
					m_pOrmHeroCollect->last_free_times[ii] = (pwutils::time::clib_time() - pSHeroGet->freeCd + pSHeroGet->freeStartCd);
				}
			}
		}
		return 0;
	}

	sint32 ModHeroCollect::InitialEnergy()
	{
		for (sint32 ii = 0; ii < COLLECT_LEVEL_MAX; ++ii)
		{
			SHeroGet* pSHeroGet = g_objHeroCollectDataset.GetHeroCollect(ii);
			pwasserte(pSHeroGet);
			if (0 == m_pOrmHeroCollect->collect_energyes[ii])
			{
				sint32 nEnergy = pSHeroGet->normalEnergyNeed;
				float fEnergy = pwutils::random(-0.3f, 0.3f) * nEnergy;
				nEnergy = fEnergy;
				m_pOrmHeroCollect->collect_energyes[ii] = nEnergy;
			}
		}
		return 0;
	}

	sint32 ModHeroCollect::OrmSave()
	{
		pwassertf(m_pOrmHeroCollect);
		return m_pOwner->GetOrmHelper()->OrmUpdate(m_pOrmHeroCollect);
	}

	sint32 ModHeroCollect::Query()
	{
		HumanOper oper(m_pOwner);
		return oper.SendHeroCollectQueryResult();
	}

	sint32 ModHeroCollect::DoCollect(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType)
	{
		SHeroGet* pSHeroGet = g_objHeroCollectDataset.GetHeroCollect(nCollectLevel);
		pwassertf(pSHeroGet);
		HumanOper oper(m_pOwner);
		CollectionRandomItemsT vtRandomItemList;
		CollectionPackItemsT vtPackItems;

		// 不是十连抽，则根据CD矫正当前使用的抽取方式
		if (COLLECT_TYPE_MULTICOST != nCollectType)
		{
			nCollectType = GetCollectType(nCollectLevel);
		}

		// 抽取条件判断，并扣除花费
		sint32 nRet = CheckCollect(nCollectLevel, nCollectType);
		if (HERO_COLLECT_SUCCESS != nRet)
		{
			oper.SendHeroCollectResult(nRet, vtRandomItemList, vtPackItems);
			return nRet;
		}

		// 生成随机包，并执行能量值的消耗和积累
		// 由于优先、满能量、普通随机池需要消耗的能量值不同，故写在下面函数中
		sint32 nNum = 1;
		if (COLLECT_TYPE_MULTICOST == nCollectType)
		{
			nNum = CST_HERO_COLLECT_TEN;
		}
		for (sint32 ii = 0; ii < nNum; ++ii)
		{
			SRandomItem randomItem;
			GetRandomItem(nCollectLevel, nCollectType, randomItem);
			vtRandomItemList.push_back(randomItem);
		}
		pwassertf(0 < vtRandomItemList.size());
		if (COLLECT_TYPE_MULTICOST == nCollectType)
		{
			ReplaceRandomItemWithHero(vtRandomItemList, pSHeroGet->energyPool);
		}

		for (CollectionRandomItemsT::iterator iter = vtRandomItemList.begin(); iter != vtRandomItemList.end(); ++iter)
		{
			SPackItem item;
			ConvertRandomItemToPackItem(*iter, item);
			vtPackItems.push_back(item);
		}

		// 获取随机包结果
		ObtainItem(vtPackItems);

		// 通知客户端抽取结果
		oper.SendHeroCollectResult(nRet, vtRandomItemList, vtPackItems);

		// 记录免费抽取时间
		if (COLLECT_TYPE_FREE == nCollectType)
		{
			m_pOrmHeroCollect->last_free_times[nCollectLevel] = pwutils::time::clib_time();
		}
		
		oper.SendHeroCollectQueryResult();

		// 存储DB
		OrmSave();

		// 增加活跃度
		m_pOwner->GetModDailyBonus()->InjectActivityComplete(DAILY_BONUS_ACTIVITY_HERO_COLLECT, nNum);
		return nRet;
	}

	sint32 ModHeroCollect::CheckCollect(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType)
	{
		pwassertf(COLLECT_LEVEL_LOW <= nCollectLevel && COLLECT_LEVEL_MAX > nCollectLevel);
		pwassertf(COLLECT_TYPE_FREE <= nCollectType && COLLECT_TYPE_MAX > nCollectType);
		SHeroGet* pSHeroGet = g_objHeroCollectDataset.GetHeroCollect(nCollectLevel);
		pwassertf(pSHeroGet);
		HumanOper oper(m_pOwner);

		// 是否开启高级抽取
		if (COLLECT_LEVEL_HIGH == nCollectLevel)
		{
			if (!CheckCollectLevelHigh())
			{
				return HERO_COLLECT_FAILED_LEVEL;
			}
		}

		// 配置表中抽取级别是否开启抽取方式
		if (!g_objHeroCollectDataset.CheckHeroCollectOpen(nCollectLevel, nCollectType))
		{
			return -1;
		}

		// 背包剩余格数是否足够
		ItemContainer* pItemContainer = m_pOwner->GetModItem()->GetContainer(ITEM_CONTAINER_TYPE_INVENTORY);
		pwassertf(pItemContainer);
		size_t nFreeSize = pItemContainer->FreeSize();
		if (COLLECT_TYPE_FREE == nCollectType || COLLECT_TYPE_COST == nCollectType)
		{
			if (1 > nFreeSize)
			{
				return HERO_COLLECT_FAILED_BAG_NOT_ENOUGH;
			}
		}
		if (COLLECT_TYPE_MULTICOST == nCollectType)
		{
			if (CST_HERO_COLLECT_TEN > nFreeSize)
			{
				return HERO_COLLECT_FAILED_BAG_NOT_ENOUGH;
			}
		}

		// 付费抽取，扣除花费
		if (COLLECT_TYPE_FREE != nCollectType)
		{
			SItemPackage costPackage;
			if_fail(GetCost(nCollectLevel, nCollectType, costPackage))
			{
				gErrorStream("ModHeroCollect::GetCost failed.");
				return -1;
			}
			if_fail(oper.SpendItemPackageTest(costPackage))
			{
				gErrorStream("ModHeroCollect::SpendItemPackageTest failed.");
				return HERO_COLLECT_FAILED_COST;
			}
			if_fail(oper.SpendItemPackage(costPackage, CASH_SPEND_TYPE_HERO_CHECKCOLLECT))
			{
				gErrorStream("ModHeroCollect::SpendItemPackage failed.");
				return HERO_COLLECT_FAILED_COST;
			}
		}
		return 0;
	}

	sint32 ModHeroCollect::GetRandomItem(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType, SRandomItem& rRandomItem)
	{
		SHeroGet* pSHeroGet = g_objHeroCollectDataset.GetHeroCollect(nCollectLevel);
		pwassertf(pSHeroGet);

		// 判定特殊抽取
		sint32 nCurrCollectCount = GenerateCurrCollectCount(nCollectLevel, nCollectType);
		sint32 nTotalCollectCount = GetTotalCollectCount(nCollectLevel) + 1;
		sint32 nRandomID = g_objHeroCollectDataset.FindRandomIDByCondition(nCollectLevel, nCollectType, nCurrCollectCount, nTotalCollectCount);
		if (0 < nRandomID)
		{
			RandomItemConfig* pConfig = g_objRandomPoolDataset.GetRandomItemConfig(nRandomID);
			pwassertf(pConfig);
			GenerateRandomItem(nRandomID, rRandomItem);
		}
		else
		{
			// 普通抽取
			sint32 nPriorHeroID = 0;
			// 优先英雄池不为空
			if (0 < pSHeroGet->firstHero && 0 < (nPriorHeroID = GetPriorHeroID(pSHeroGet->firstHero)))
			{
				// 满足优先英雄池能量值需求
				if (CheckPriorEnergy(nCollectLevel))
				{
					rRandomItem.nType = RANDOM_TYPE_HERO;
					rRandomItem.nTID = nPriorHeroID;
					rRandomItem.nCount = 1;
					rRandomItem.nWeight = 1;
					// 扣除优先抽取能量
					CostPriorEnergy(nCollectLevel);
				} 
				// 普通随机池
				else
				{
					GenerateRandomItem(pSHeroGet->normalPool, rRandomItem);
				}
			}
			else
			{
				// 满能量随机池
				if (CheckFullEnergy(nCollectLevel))
				{
					GenerateRandomItem(pSHeroGet->energyPool, rRandomItem);
					// 扣除满能量抽取能量
					CostFullEnergy(nCollectLevel);
				}
				// 普通随机池
				else
				{
					GenerateRandomItem(pSHeroGet->normalPool, rRandomItem);
				}
			}

			// 积累抽取能量
			ObtainEnergy(nCollectLevel, nCollectType);
		}
		// 抽取记录
		AddRecord(nCollectLevel, nCollectType);
		return 0;
	}

	sint32 ModHeroCollect::ObtainItem(const CollectionPackItemsT& vtPackItems)
	{
		HumanOper oper(m_pOwner);
		SItemPackage package;
		package.ParseFromPackItems(vtPackItems);
		//for (sint32 ii = 0; ii < vtPackItems.size(); ++ii)
		//{
		//	gErrorStream("ModHeroCollect::ObtainItem item id=" << vtPackItems[ii].tid << ", count=" << vtPackItems[ii].count);
		//}
		if (0 == oper.GrantItemPackageTest(package))
		{
			pwassertf(oper.GrantItemPackage(package, CASH_GRANT_TYPE_HERO_COLLECT) == 0);
		}
		else
		{
			MailBuilder mail(MAIL_MODE_GIFT);
			mail.AddSubject("i", cst_mail_subject_strid_hero_collect);
			mail.AddContent("i", cst_mail_content_strid_hero_collect);
			mail.AddItems(vtPackItems);
			mail.Send(m_pOwner->GetStage()->GetStageThread(), m_pOwner->GetID());
		}
		return 0;
	}

	bool ModHeroCollect::CheckCollectLevelHigh()
	{
		pwassertn(m_pOwner->GetModVip());
		if (0 < m_pOwner->GetModVip()->GetVipStat(STAT_VIP_BONUS_HERO_COLLECT))
		{
			return true;
		}
		else
		{
			sint64 nCurTime = pwutils::time::clib_time();
			if (!pwutils::time::clib_is_same_day(m_pOrmHeroCollect->get_last_random_time(), nCurTime))
			{
				const sint32 nHundred = 100;
				sint32 nRandom = pwutils::random(0, nHundred);
				if (CST_HERO_COLLECT_HIGH_PERCENT > nRandom)
				{
					m_pOrmHeroCollect->set_is_open_high(true);
				}
				else
				{
					m_pOrmHeroCollect->set_is_open_high(false);
				}
				m_pOrmHeroCollect->set_last_random_time(nCurTime);
				OrmSave();
			}
			return m_pOrmHeroCollect->get_is_open_high();
		}
	}

	EHeroCollectType ModHeroCollect::GetCollectType(EHeroCollectLevel nCollectLevel)
	{
		SHeroGet* pSHeroGet = g_objHeroCollectDataset.GetHeroCollect(nCollectLevel);
		pwasserte(pSHeroGet);
		EHeroCollectType nType = COLLECT_TYPE_COST;
		sint64 nCurTime = pwutils::time::clib_time();
		if (m_pOrmHeroCollect->last_free_times[nCollectLevel] + pSHeroGet->freeCd < nCurTime)
		{
			nType = COLLECT_TYPE_FREE;
		}
		else
		{
			nType = COLLECT_TYPE_COST;
		}

		// 判定配置表格中抽取级别是否开启抽取方式
		if (!g_objHeroCollectDataset.CheckHeroCollectOpen(nCollectLevel, nType))
		{
			nType = COLLECT_TYPE_COST;
		}
		return nType;
	}

	sint32 ModHeroCollect::GenerateCurrCollectCount(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType)
	{
		pwassertf(COLLECT_LEVEL_LOW <= nCollectLevel && COLLECT_LEVEL_MAX > nCollectLevel);
		pwassertf(COLLECT_TYPE_FREE <= nCollectType && COLLECT_TYPE_MAX > nCollectType);
		if (COLLECT_TYPE_FREE == nCollectType)
		{
			return GetFreeCollectCount(nCollectLevel) + 1;
		}
		if (COLLECT_TYPE_COST == nCollectType || COLLECT_TYPE_MULTICOST == nCollectType)
		{
			return GetCostCollectCount(nCollectLevel) + 1;
		}
		return 1;
	}

	sint32 ModHeroCollect::GetCost(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType, SItemPackage& rPackage)
	{
		SHeroGet* pSHeroGet = g_objHeroCollectDataset.GetHeroCollect(nCollectLevel);
		pwassertf(pSHeroGet);
		SPackItem cost;
		cost.tid = pSHeroGet->costType;
		if (COLLECT_TYPE_COST == nCollectType)
		{
			cost.count = pSHeroGet->normalCost;
		}
		else if (COLLECT_TYPE_MULTICOST == nCollectType)
		{
			cost.count = pSHeroGet->tenTimesCost;
		}
		rPackage.SetCashReason(CASH_SPEND_TYPE_HERO_COLLECT);
		return rPackage.ParseFromPackItem(cost);
	}

	bool ModHeroCollect::CheckPriorEnergy(EHeroCollectLevel nCollectLevel)
	{
		SHeroGet* pSHeroGet = g_objHeroCollectDataset.GetHeroCollect(nCollectLevel);
		pwasserte(pSHeroGet);
		return m_pOrmHeroCollect->collect_energyes[nCollectLevel] >= pSHeroGet->firstEnergyNeed;
	}

	bool ModHeroCollect::CheckFullEnergy(EHeroCollectLevel nCollectLevel)
	{
		SHeroGet* pSHeroGet = g_objHeroCollectDataset.GetHeroCollect(nCollectLevel);
		pwasserte(pSHeroGet);
		return m_pOrmHeroCollect->collect_energyes[nCollectLevel] >= pSHeroGet->normalEnergyNeed;
	}

	sint32 ModHeroCollect::ObtainEnergy(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType)
	{
		sint32 nObtainEnergy = CalcEnergy(nCollectLevel, nCollectType);
		return AlterEnergy(nCollectLevel, nObtainEnergy);
	}

	sint32 ModHeroCollect::CostPriorEnergy(EHeroCollectLevel nCollectLevel)
	{
		SHeroGet* pSHeroGet = g_objHeroCollectDataset.GetHeroCollect(nCollectLevel);
		pwassertn(pSHeroGet);
		sint32 nCostEnergy = pSHeroGet->firstEnergyNeed;
		float fCostEnergy = pwutils::random(0.7f, 1.3f) * nCostEnergy;
		nCostEnergy = fCostEnergy;
		return AlterEnergy(nCollectLevel, -nCostEnergy);
	}

	sint32 ModHeroCollect::CostFullEnergy(EHeroCollectLevel nCollectLevel)
	{
		SHeroGet* pSHeroGet = g_objHeroCollectDataset.GetHeroCollect(nCollectLevel);
		pwassertn(pSHeroGet);
		sint32 nCostEnergy = pSHeroGet->normalEnergyNeed;
		float fCostEnergy = pwutils::random(0.7f, 1.3f) * nCostEnergy;
		nCostEnergy = fCostEnergy;
		return AlterEnergy(nCollectLevel, -nCostEnergy);
	}

	sint32 ModHeroCollect::CalcEnergy(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType)
	{
		pwassertn(COLLECT_TYPE_FREE <= nCollectType && COLLECT_TYPE_MAX > nCollectType);
		const sint32 nTenThousand = 10000;
		SHeroGet* pSHeroGet = g_objHeroCollectDataset.GetHeroCollect(nCollectLevel);
		pwassertn(pSHeroGet);
		pwassertn(m_pOwner->GetModVip());
		sint32 nVipLevel = m_pOwner->GetModVip()->GetLevel();
		pwconf::SVipNew* pSVipNewConfig = g_objVipNewDataset.Get(nVipLevel);
		pwassertn(pSVipNewConfig);
		sint32 nEnergy = pSHeroGet->normalCost * pSHeroGet->energyGet / nTenThousand;
		if (COLLECT_TYPE_FREE == nCollectType)
		{
			nEnergy = nEnergy * pSVipNewConfig->freeGetEnergy / nTenThousand;
		}
		else
		{
			nEnergy = nEnergy * pSVipNewConfig->payGetEnergy / nTenThousand;
		}
		float fEnergy = pwutils::random(0.7f, 1.3f) * nEnergy;
		nEnergy = fEnergy;
		return nEnergy;
	}

	sint32 ModHeroCollect::AlterEnergy(EHeroCollectLevel nCollectLevel, sint32 nModifyEnergy)
	{
		pwassertf(COLLECT_LEVEL_MAX > nCollectLevel);
		sint32 nCurrEnergy = m_pOrmHeroCollect->collect_energyes[nCollectLevel];
		nCurrEnergy += nModifyEnergy;
		// 为了方便创建新角色时随机能量值的处理，故不允许玩家能量值为0
		if (0 == nCurrEnergy)
		{
			nCurrEnergy = 1;
		}
		m_pOrmHeroCollect->collect_energyes[nCollectLevel] = nCurrEnergy;
		return 0;
	}

	sint32 ModHeroCollect::AddRecord(EHeroCollectLevel nCollectLevel, EHeroCollectType nCollectType)
	{
		pwassertf(COLLECT_LEVEL_LOW <= nCollectLevel && COLLECT_LEVEL_MAX > nCollectLevel);
		pwassertf(COLLECT_TYPE_FREE <= nCollectType && COLLECT_TYPE_MAX > nCollectType);
		if (COLLECT_TYPE_MULTICOST == nCollectType)
		{
			nCollectType = COLLECT_TYPE_COST;
		}
		if (COLLECT_LEVEL_LOW == nCollectLevel)
		{
			++m_pOrmHeroCollect->low_records[nCollectType];
		}
		else if (COLLECT_LEVEL_MIDDLE == nCollectLevel)
		{
			++m_pOrmHeroCollect->middle_records[nCollectType];
		}
		else if (COLLECT_LEVEL_HIGH == nCollectLevel)
		{
			++m_pOrmHeroCollect->high_records[nCollectType];
		}
		return 0;
	}

	sint32 ModHeroCollect::GetFreeCollectCount(EHeroCollectLevel nCollectLevel) const
	{
		pwassertn(COLLECT_LEVEL_LOW <= nCollectLevel && COLLECT_LEVEL_MAX > nCollectLevel);
		if (COLLECT_LEVEL_LOW == nCollectLevel)
		{
			return m_pOrmHeroCollect->low_records[COLLECT_TYPE_FREE];
		}
		else if (COLLECT_LEVEL_MIDDLE == nCollectLevel)
		{
			return m_pOrmHeroCollect->middle_records[COLLECT_TYPE_FREE];
		}
		else if (COLLECT_LEVEL_HIGH == nCollectLevel)
		{
			return m_pOrmHeroCollect->high_records[COLLECT_TYPE_FREE];
		}
		return 0;
	}

	sint32 ModHeroCollect::GetCostCollectCount(EHeroCollectLevel nCollectLevel) const
	{
		pwassertn(COLLECT_LEVEL_LOW <= nCollectLevel && COLLECT_LEVEL_MAX > nCollectLevel);
		if (COLLECT_LEVEL_LOW == nCollectLevel)
		{
			return m_pOrmHeroCollect->low_records[COLLECT_TYPE_COST];
		}
		else if (COLLECT_LEVEL_MIDDLE == nCollectLevel)
		{
			return m_pOrmHeroCollect->middle_records[COLLECT_TYPE_COST];
		}
		else if (COLLECT_LEVEL_HIGH == nCollectLevel)
		{
			return m_pOrmHeroCollect->high_records[COLLECT_TYPE_COST];
		}
		return 0;
	}

	sint32 ModHeroCollect::GetTotalCollectCount(EHeroCollectLevel nCollectLevel) const
	{
		pwassertn(COLLECT_LEVEL_LOW <= nCollectLevel && COLLECT_LEVEL_MAX > nCollectLevel);
		return GetFreeCollectCount(nCollectLevel) + GetCostCollectCount(nCollectLevel);
	}

	sint32 ModHeroCollect::CollectPriorHero(sint32 nRandomID, CollectionRandomItemsT& vtRandomItemList)
	{
		pwassertn(m_pOwner->GetModHeroNew());
		RandomItemConfig* pConfig = g_objRandomPoolDataset.GetRandomItemConfig(nRandomID);
		pwassertf(pConfig);
		const CollectionRandomItemsT& vtRandomItems = pConfig->GetRandomItems();
		for (sint32 ii = 0; ii < vtRandomItems.size(); ++ii)
		{
			const SRandomItem& rRandomItem = vtRandomItems[ii];
			pwassertf(RANDOM_TYPE_HERO == rRandomItem.nType);
			if (!m_pOwner->GetModHeroNew()->IsActivated(rRandomItem.nTID))
			{
				SRandomItem item = rRandomItem;
				vtRandomItemList.push_back(item);
			}
		}
		return 0;
	}

	sint32 ModHeroCollect::GetPriorHeroID(sint32 nRandomID)
	{
		pwassertf(0 < nRandomID);
		CollectionRandomItemsT vtRandomItemList;
		CollectPriorHero(nRandomID, vtRandomItemList);
		if (0 == vtRandomItemList.size())
		{
			return -1;
		}

		sint32 nRandomContainerWeightSum = 0;
		for (size_t ii = 0; ii < vtRandomItemList.size(); ++ii)
		{
			SRandomItem& rRandomItem = vtRandomItemList[ii];
			pwassertf(RANDOM_TYPE_HERO == rRandomItem.nType);
			nRandomContainerWeightSum += rRandomItem.nWeight;
		}

		int32 rnd = pwutils::random(0, nRandomContainerWeightSum);
		int32 thresold = 0;
		for (size_t jj = 0; jj < vtRandomItemList.size(); ++jj)
		{
			SRandomItem& rRandomItem = vtRandomItemList[jj];
			if (RANDOM_TYPE_HERO != rRandomItem.nType)
			{
				continue;
			}
			thresold += rRandomItem.nWeight;
			if (rnd < __max(1, thresold))
			{
				return rRandomItem.nTID;
			}
		}
		return -1;
	}

	sint32 ModHeroCollect::GetWholeHeroCollectNum(sint32 nHeroID) const
	{
		pwassertn(m_pOwner);
		pwassertn(m_pOwner->GetModHeroNew());
		pwassertn(m_pOwner->GetModItem());
		if (m_pOwner->GetModHeroNew()->IsActivated(nHeroID))
		{
			return CST_HERO_DEBRIS_DEFAULT;
		}
		else
		{
			SHeroNewData* pData = g_objHeroNewDataset.GetHeroNewData(nHeroID);
			if (NULL == pData)
			{
				return 0;
			}
			else
			{

				return g_objHeroNewDataset.GetActivatedHeroNewDebrisNum(nHeroID);
				//sint32 nNum = g_objHeroNewDataset.GetActivatedHeroNewDebrisNum(nHeroID);
				//sint32 nCount = m_pOwner->GetModItem()->CollectItemNum(pData->hero_pieces);
				//if (nCount >= nNum)
				//{
				//	return CST_HERO_DEBRIS_DEFAULT;
				//}
				//else
				//{
				//	return nNum - nCount;
				//}
			}
		}
	}

	sint32 ModHeroCollect::ConvertRandomItemToPackItem(const SRandomItem& rRandomItem, SPackItem& rPackItem)
	{
		pwassertf(RANDOM_TYPE_NONE < rRandomItem.nType && RANDOM_TYPE_PACKAGE > rRandomItem.nType);
		rPackItem.tid = rRandomItem.nTID;
		rPackItem.count = rRandomItem.nCount;
		if (RANDOM_TYPE_HERO == rRandomItem.nType)
		{
			SHeroNewData* pData = g_objHeroNewDataset.GetHeroNewData(rRandomItem.nTID);
			pwassertf(pData);
			rPackItem.tid = pData->hero_pieces;
			rPackItem.count = GetWholeHeroCollectNum(rRandomItem.nTID);
		}
		return 0;
	}

	sint32 ModHeroCollect::GetReplaceHeroID(sint32 nRandomID) const
	{
		RandomItemConfig* pConfig = g_objRandomPoolDataset.GetRandomItemConfig(nRandomID);
		pwassertf(pConfig);
		const CollectionRandomItemsT& vtRandomItems = pConfig->GetRandomItems();
		sint32 nHeroID = 0;
		sint32 nColor = 100;
		for (sint32 ii = 0; ii < vtRandomItems.size(); ++ii)
		{
			const SRandomItem& rRandomItem = vtRandomItems[ii];
			if (RANDOM_TYPE_HERO != rRandomItem.nType || 0 >= rRandomItem.nTID)
			{
				continue;
			}
			SHeroNewData* pData = g_objHeroNewDataset.GetHeroNewData(rRandomItem.nTID);
			pwassertf(pData);
			if (NULL == pData)
			{
				continue;
			}
			if (pData->color < nColor)
			{
				nHeroID = pData->id;
				nColor = pData->color;
			}
		}
		return nHeroID;
	}

	sint32 ModHeroCollect::GenerateRandomItem(sint32 nRandomID, SRandomItem& rRandomItem)
	{
		if (0 >= nRandomID)
		{
			return -1;
		}
		RandomItemConfig* pConfig = g_objRandomPoolDataset.GetRandomItemConfig(nRandomID);
		pwassertf(pConfig);
		pwassertf(1 == pConfig->GetRandomNum()); // 策划约定：英雄碎片的随机包只能随机一次

		CollectionRandomItemsT vtRandomItemList;
		g_objRandomPoolDataset.CollectRandomList(nRandomID, vtRandomItemList);
		pwassertf(1 == vtRandomItemList.size()); // 策划约定：英雄碎片的随机包只能生成一种物品
		pwassertf(RANDOM_TYPE_NONE < vtRandomItemList[0].nType && RANDOM_TYPE_MAX > vtRandomItemList[0].nType);
		pwassertf(0 < vtRandomItemList[0].nTID);
		rRandomItem = vtRandomItemList[0];
		return 0;
	}

	sint32 ModHeroCollect::ReplaceRandomItemWithHero(CollectionRandomItemsT& vtRandomItemList, sint32 nFullRandomID)
	{
		pwassertf(0 < vtRandomItemList.size() || 0 >= nFullRandomID);

		// 若替换随机池中无英雄则不替换
		sint32 nHeroID = GetReplaceHeroID(nFullRandomID);
		if (0 == nHeroID)
		{
			return 0;
		}

		// 是否包含英雄
		if (!g_objRandomPoolDataset.IsContainHero(vtRandomItemList))
		{
			vtRandomItemList.pop_back();
			SRandomItem randomItem = { RANDOM_TYPE_HERO, nHeroID, 1, 1 };
			vtRandomItemList.push_back(randomItem);
		}
		return 0;
	}

}