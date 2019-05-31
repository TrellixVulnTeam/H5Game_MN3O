#include "pw_heronew.h"
#include "pw_human.h"
#include "pw_orm_helper.h"
#include "pw_heronew_dataset.h"
#include "pw_module_magic.h"
#include "pw_magic_set.h"
#include "pw_unit_oper.h"
#include "pw_human_oper.h"
#include "00000_00000_def.pb.h"
#include "pw_item_multi_sandbox.h"
#include "pw_item.h"
#include "pw_unit_def.h"
#include "pw_module_statistic.h"
#include "pw_module_combat_point.h"
#include "pw_module_daily_bonus.h"
#include "pw_hero_card.h"
#include "pw_module_hero_card.h"
#include "pw_module_aura.h"
#include "pw_module_hero_tactical.h"
#include "pw_module_hero_spirit.h"


namespace pwngs
{
	HeroNew::HeroNew(orm::HeroNew* heroNew,Unit* owner)
		: m_pOrmHeroNew(heroNew)
		, m_pOwner(owner)
	{
	}

	HeroNew::~HeroNew()
	{
	}

	int HeroNew::OrmLoad()
	{
		return 0 ;
	}

	int HeroNew::OrmSave(bool update /* = true */)
	{
		Human* h = m_pOwner->QueryObjectEx<Human>();
		pwassertf(h);

		if(update)
			h->GetOrmHelper()->OrmUpdate(m_pOrmHeroNew);
		else
			h->GetOrmHelper()->OrmInsert(m_pOrmHeroNew);

		return 0 ;
	}

	//struct HeroNew
	//{
	//	<slave_table Human>
	//	int64	hid <masterid>;
	//	int64	id <key> <autoincr> <value_type>;
	//	int32	did <value_type>;
	//	int16	state <value_type> <comment "状态">;
	//	int16	star <value_type> <comment "星级">;
	//	bool	activated <value_type> <comment "是否激活">;
	//	int16	assistance_loc <default 0> <value_type> <comment "助战位">;
	//	int16	rank <default 0> <value_type> <comment "当前阶级">;
	//	int16	rank_item_flag <default 0> <value_type> <comment "当前阶级镶嵌物品信息(1-6位表示)">;
	//}
	int HeroNew::InitialFromConfig()
	{
		SHeroNewData* pHeroNewData = g_objHeroNewDataset.GetHeroNewData(GetDID()) ;
		pwassertf(pHeroNewData) ;

		m_pOrmHeroNew->state = HERONEW_STATE_IDLE ;
		m_pOrmHeroNew->star = 1;

		this->OrmSave(false) ;

		this->OnEnterWorld() ;

		return 0 ;
	}

	int HeroNew::OnIdle()
	{
		m_pOrmHeroNew->state = HERONEW_STATE_IDLE;
		this->OrmSave();
		return 0 ;
	}

	int HeroNew::OnAssistance(float fPlusrate)
	{
		this->AddAura();

		m_pOrmHeroNew->state = HERONEW_STATE_ASSISTANCE;
		this->OrmSave();

		return 0 ;
	}

	int HeroNew::OnUnAssistance(float fPlusrate)
	{
		this->DelAura() ;

		return 0 ;
	}

	int HeroNew::OnActivated(bool useitems /* = true */)
	{
		SHeroNewData* pHeroNewData = g_objHeroNewDataset.GetHeroNewData(GetDID()) ;
		pwassertf(pHeroNewData) ;

		Human* pHuman = m_pOwner->QueryObjectEx<Human>();
		pwassertf(pHuman);

		if(useitems)
		{
			sint32 tid = pHeroNewData->hero_pieces;
			sint32 count = pHeroNewData->pieces_req[0];
			pwassertf(tid > 0 && count > 0);

			MultiItemSandbox box(pHuman);
			box.OperDel(Item::GetDefaultBag(tid),tid,count);
			sint32 result = box.Commit(CASH_SPEND_TYPE_HERO_ACTIVIED);
			if_fail(result)
				return result;
		}

		pwassertf(m_pOrmHeroNew->activated == false);
		m_pOrmHeroNew->activated = true;
		m_pOrmHeroNew->star = 1;

		// 附加属性增加
		HandleStatisticOnActivated(true);

		// 战力增加
		HandleCombatPointOnActivated(true);

		this->OrmSave(true);

		// 激活对应的第一个英雄卡牌
		ModHeroCard* pModHeroCard = pHuman->GetModHeroCard();
		pwassertf(pModHeroCard);
		pwassertf(false == pModHeroCard->IsActivated(pHeroNewData->skill_id[0]));
		pwassertf(0 == pModHeroCard->ActivatedByDid(pHeroNewData->skill_id[0]));

		pHuman->GetModHeroSpirit()->CreateHeroSpiritFromConfig(this->GetDID());

		return 0 ;
	}

	int HeroNew::OnStarUp(bool useitems /* = true */)
	{
		// 判断星级是否已满
		sint32 nCurStar = this->GetStar() ;
		if (nCurStar >= cst_heronew_star_max)
			return -1 ;

		SHeroNewData* pHeroNewData = g_objHeroNewDataset.GetHeroNewData(GetDID()) ;
		pwassertf(pHeroNewData) ;

		Human* pHuman = m_pOwner->QueryObjectEx<Human>();
		pwassertf(pHuman);

		// 判断升星所需物品是否足够
		if (useitems)
		{
			pwassertf(nCurStar > 0 && nCurStar < cst_heronew_star_max);

			sint32 tid = pHeroNewData->hero_pieces;
			sint32 count = pHeroNewData->pieces_req[nCurStar];
			pwassertf(tid > 0 && count > 0);

			MultiItemSandbox box(pHuman);
			box.OperDel(Item::GetDefaultBag(tid),tid,count);
			sint32 result = box.Commit(CASH_SPEND_TYPE_HERO_STARUP);
			if_fail(result)
				return result;
		}

		// 附加属性减少
		HandleStatisticOnActivated(false);
		// 战力减少
		HandleCombatPointOnActivated(false);

		// 星级变化
		m_pOrmHeroNew->star += 1;

		// 附加属性增加
		HandleStatisticOnActivated(true);
		// 战力增加
		HandleCombatPointOnActivated(true);

		this->OrmSave(true);

		// 激活英雄卡牌
		ModHeroCard* pModHeroCard = pHuman->GetModHeroCard();
		pwassertf(pModHeroCard);
		if (cst_heronew_card_max >= GetStar())
		{
			int32 nCardIndex = GetStar() - 1;
			pwassertf(false == pModHeroCard->IsActivated(pHeroNewData->skill_id[nCardIndex]));
			pwassertf(0 == pModHeroCard->ActivatedByDid(pHeroNewData->skill_id[nCardIndex]));
		}
		//else
		//{
		//	int32 nCardIndex2 = ((GetStar() - 1) % cst_heronew_card_max);
		//	pwassertf(pModHeroCard->IsActivated(pHeroNewData->skill_id[nCardIndex2]));
		//	pwassertf(0 == pModHeroCard->StarUpByDid(pHeroNewData->skill_id[nCardIndex2]));
		//}

		return 0 ;
	}

	int HeroNew::OnEmbed(int16 nRankItemFlag, bool useitems)
	{
		// 判断镶嵌位参数
		if (GetRankItemFlag() >= nRankItemFlag || nRankItemFlag >= (1 << (HERONEW_RANK_SOLT_MAX - 1)))
		{
			return HERONEW_EMBED_FAILED_SOLT;
		}
		int16 nCurrItemSoltFlag = GetRankItemFlag();
		if ((nCurrItemSoltFlag&nRankItemFlag) != nCurrItemSoltFlag)
		{
			return HERONEW_EMBED_FAILED_SOLT;
		}

		Human* pHuman = m_pOwner->QueryObjectEx<Human>();
		pwassertf(pHuman);
		HumanOper oper(pHuman);

		// 新添加的镶嵌位 001-111
		int16 nAddItemSoltFlag = nRankItemFlag - (nRankItemFlag&nCurrItemSoltFlag);
		pwassertf(0 < nAddItemSoltFlag);
		// 判断升阶镶嵌所需物品是否足够
		if (useitems)
		{
			CollectionPackItemsT vtItems;
			g_objHeroNewDataset.CollectRankUpPackItems(GetDID(), GetRank(), nAddItemSoltFlag, vtItems);
			pwassertf(0 < vtItems.size());
			SItemPackage spendPackage;
			spendPackage.ParseFromPackItems(vtItems);
			if_fail(oper.SpendItemPackageTest(spendPackage))
			{
				gErrorStream("HeroNew::SpendItemPackageTest failed.");
				return HERONEW_EMBED_FAILED_ITEM_NOT_ENOUGH;
			}
			if_fail(oper.SpendItemPackage(spendPackage, CASH_SPEND_TYPE_HERO_CARD_RANKUP))
			{
				gErrorStream("HeroNew::SpendItemPackage failed.");
				return HERONEW_EMBED_FAILED_ITEM_NOT_ENOUGH;
			}
		}

		// 助战倍率
		ModHeroTactical* pModHeroTactical = pHuman->GetModHeroTactical();
		pwassertf(pModHeroTactical);
		float fPlusrate = 1.0f;
		if (IsAssistance())
		{
			pwassertf(GetAssistanceLoc() == pModHeroTactical->GetSlotIDByHeroID(GetID()));
			fPlusrate = pModHeroTactical->GetSlotCurPercentage(GetAssistanceLoc());
		}

		// 附加属性减少
		HandleStatisticOnActivated(false);
		// 战力减少
		HandleCombatPointOnActivated(false);
		if (this->IsAssistance())
		{
			// 删掉现有技能
			this->DelAura();
		}

		// 镶嵌位变化
		SetRankItemFlag(nRankItemFlag);

		// 附加属性增加
		HandleStatisticOnActivated(true);
		// 战力增加
		HandleCombatPointOnActivated(true);
		if (this->IsAssistance())
		{
			// 增加技能
			this->AddAura();
		}

		this->OrmSave(true);

		return 0;
	}

	int HeroNew::OnRankUp()
	{
		// 是否达到最高阶
		if (GetRank() >= g_objHeroNewDataset.GetHeroMaxRank(GetDID()))
		{
			return -1;
		}

		// 判断镶嵌位参数是否满足升阶
		if (GetRankItemFlag() != ((1 << (HERONEW_RANK_SOLT_MAX - 1)) - 1))
		{
			return HERONEW_RANKUP_FAILED_NOT_FULL;
		}

		// 助战倍率
		Human* pHuman = m_pOwner->QueryObjectEx<Human>();
		pwassertf(pHuman);
		ModHeroTactical* pModHeroTactical = pHuman->GetModHeroTactical();
		pwassertf(pModHeroTactical);
		float fPlusrate = 1.0f;
		if (IsAssistance())
		{
			pwassertf(GetAssistanceLoc() == pModHeroTactical->GetSlotIDByHeroID(GetID()));
			fPlusrate = pModHeroTactical->GetSlotCurPercentage(GetAssistanceLoc());
		}

		// 附加属性减少
		HandleStatisticOnActivated(false);
		// 战力减少
		HandleCombatPointOnActivated(false);
		if (this->IsAssistance())
		{
			// 删掉现有技能
			this->DelAura();
		}

		// 等阶和镶嵌变化
		SetRank(GetRank() + 1);
		SetRankItemFlag(HERONEW_RANK_SOLT_NONE);

		// 附加属性增加
		HandleStatisticOnActivated(true);
		// 战力增加
		HandleCombatPointOnActivated(true);
		if (this->IsAssistance())
		{
			// 增加技能
			this->AddAura();
		}

		this->OrmSave(true);

		return 0;
	}

	int HeroNew::GetAura()
	{
		SHeroNewData* pHeroNewData = g_objHeroNewDataset.GetHeroNewData(GetDID());
		pwassertf(pHeroNewData);
		pwassertf(pHeroNewData->passive_skill_id.size() > GetRank());
		return pHeroNewData->passive_skill_id[GetRank()];
	}

	int HeroNew::AddAura()
	{
		DelAura();
		Human* pHuman = m_pOwner->QueryObjectEx<Human>();
		pwassertf(pHuman);
		pwassertf(0 < GetAura());
		SAuraType* pType = g_objAuraDataset.Get(GetAura());
		pwassertf(pType);
		pwassertf(pHuman->GetModAuras());
		return pHuman->GetModAuras()->CreateAura(pHuman, pType);
	}

	int HeroNew::DelAura()
	{
		Human* pHuman = m_pOwner->QueryObjectEx<Human>();
		pwassertf(pHuman);
		pwassertf(0 < GetAura());
		pwassertf(pHuman->GetModAuras());
		return pHuman->GetModAuras()->ilua_DeleteAura(GetAura());
	}

	int HeroNew::OnEnterWorld()
	{
		//if(this->IsAssistance())
		//	this->OnAssistance();

		return 0;
	}

	int HeroNew::OnLeaveWorld()
	{
		//if(this->IsAssistance())
		//	this->OnUnAssistance();

		return 0;
	}

	void HeroNew::BuildStruct(MsgW(SHeroNew)& msg)
	{
		msg.set_id(GetID());
		msg.set_did(GetDID());
		msg.set_state(GetState());
		msg.set_star(GetStar());
		msg.set_activated(IsActivated());
		msg.set_assistance_loc(GetAssistanceLoc());
		msg.set_rank(GetRank());
		msg.set_rank_item_flag(GetRankItemFlag());
		msg.set_combat_point(this->CalcCombatPoint());
	}

	int HeroNew::HandleStatisticOnActivated(bool apply, float fPlusrate)
	{
		std::vector<int32> vtAttr ;
		g_objHeroNewDataset.CollectHeroAttr(vtAttr, this->GetDID(), this->GetStar());
		g_objHeroNewDataset.CollectHeroTotalRankAttr(vtAttr, this->GetDID(), GetRank(), GetRankItemFlag());
		pwassertf(vtAttr.size()%2 == 0) ;

		std::vector<SStatisticModifier> vtStat ;
		for (size_t i = 0; i < vtAttr.size(); i += 2)
		{
			SStatisticModifier stat ;
			stat.attr = vtAttr[i] ;
			stat.type = MODIFIER_BASAL_VALUE ;
			stat.value = vtAttr[i+1] ;

			vtStat.push_back(stat) ;
		}

		this->HandleStatistic(vtStat, apply, fPlusrate) ;

		return 0 ;
	}

	int HeroNew::HandleCombatPointOnActivated(bool apply)
	{
		Human* pHuman = m_pOwner->QueryObjectEx<Human>();
		pwassertf(pHuman);

		ModCombatPoint* pModCombatPoint = pHuman->GetModCombatPoint();
		pwassertf(pModCombatPoint);

		float fCombatPoint = this->CalcCombatPoint();

		pModCombatPoint->UpdateSubCombatPoint(fCombatPoint, COMBAT_POINT_TYPE_HERONEW, apply ? COMBAT_POINT_MOD_TYPE_PLUS : COMBAT_POINT_MOD_TYPE_MIN);

		return 0;
	}

	int HeroNew::HandleStatistic(std::vector<SStatisticModifier>& vtStat,bool apply,float plusrate /* = 1.0f */)
	{
		ModStatistic* pModStatistic = m_pOwner->GetModStatistic();
		pwassertf(pModStatistic);

		for(size_t i = 0; i < vtStat.size(); ++i)
		{
			SStatisticModifier& stat = vtStat[i];

			pModStatistic->HandleModifier(stat.attr,(UnitModifierType)stat.type,stat.value * plusrate,apply);
		}
		return 0;
	}

	float HeroNew::CalcCombatPoint()
	{
		Human* pHuman = m_pOwner->QueryObjectEx<Human>();
		pwassertr(pHuman, 0.0f);

		ModCombatPoint* pModCombatPoint = pHuman->GetModCombatPoint();
		pwassertr(pModCombatPoint, 0.0f);

		std::vector<int32> vtAttr;
		g_objHeroNewDataset.CollectHeroAttr(vtAttr, this->GetDID(), this->GetStar());
		g_objHeroNewDataset.CollectHeroTotalRankAttr(vtAttr, this->GetDID(), GetRank(), GetRankItemFlag());
		pwassertr(vtAttr.size() % 2 == 0, 0.0f);

		std::vector<pwngs::SItemModAttr> vtStat;
		for (size_t i = 0; i < vtAttr.size(); i += 2)
		{
			pwngs::SItemModAttr stat;
			stat.mod = vtAttr[i];
			stat.type = MODIFIER_BASAL_VALUE;
			stat.value = vtAttr[i + 1];

			vtStat.push_back(stat);
		}

		return pModCombatPoint->CalcCombatPoint(vtStat, pHuman->GetProfession());
	}
}