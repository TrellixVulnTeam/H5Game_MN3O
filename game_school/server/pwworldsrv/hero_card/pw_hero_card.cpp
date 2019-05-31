#include "pw_hero_card.h"
#include "pw_human.h"
#include "pw_orm_helper.h"
#include "pw_hero_card_dataset.h"
#include "pw_module_magic.h"
#include "pw_magic_set.h"
#include "pw_unit_oper.h"
#include "pw_human_oper.h"
#include "00000_00000_def.pb.h"
#include "pw_item_multi_sandbox.h"
#include "pw_item.h"
#include "pw_unit_def.h"
#include "pw_module_daily_bonus.h"
#include "pw_module_hero_card.h"


namespace pwngs
{
	HeroCard::HeroCard(orm::HeroCard* heroCard,Unit* owner)
		: m_pOrmHeroCard(heroCard)
		, m_pOwner(owner)
	{

	}

	HeroCard::~HeroCard()
	{
		Cleanup() ;
	}

	int HeroCard::Cleanup()
	{
		return 0 ;
	}

	int HeroCard::OrmLoad()
	{
		return 0 ;
	}

	int HeroCard::OrmSave(bool update /* = true */)
	{
		Human* h = m_pOwner->QueryObjectEx<Human>();
		pwassertf(h);

		if(update)
			h->GetOrmHelper()->OrmUpdate(m_pOrmHeroCard);
		else
			h->GetOrmHelper()->OrmInsert(m_pOrmHeroCard);

		return 0 ;
	}

	int HeroCard::InitialFromConfig()
	{
		SHeroCardData* pHeroCardData = g_objHeroCardDataset.GetHeroCardData(GetDID()) ;
		pwassertf(pHeroCardData) ;

		m_pOrmHeroCard->state = HERO_CARD_STATE_IDLE ;
		m_pOrmHeroCard->star = 1 ;
		m_pOrmHeroCard->skill = pHeroCardData->magic_id;

		this->OrmSave(false) ;

		this->OnEnterWorld() ;

		return 0 ;
	}

	int HeroCard::OnIdle(int32 flag /*= 0*/)
	{
		if(flag & HERO_CARD_OPER_CHANGE_STATE)
		{
			m_pOrmHeroCard->state = HERO_CARD_STATE_IDLE ;
			this->OrmSave() ;
		}

		return 0 ;
	}

	int HeroCard::OnGuard(int32 flag /*= 0*/)
	{
		if(flag & HERO_CARD_OPER_CHANGE_STATE)
		{
			m_pOrmHeroCard->state = HERO_CARD_STATE_GUARD ;
			this->OrmSave() ;
		}

		return 0 ;
	}

	int HeroCard::OnEquip(int32 flag /*= 0*/)
	{
		/*if(flag & HERO_CARD_OPER_CHANGE_STATE)
		{
			this->AddOwnerMagic(this->GetEquipLoc() + MAGIC_LOC_KEYBOARD_Q);

			m_pOrmHeroCard->state = HERO_CARD_STATE_EQUIP;
			this->OrmSave();
		}*/

		return 0 ;
	}

	int HeroCard::OnUnGuard(int32 flag /*= 0*/)
	{
		if(flag & HERO_OPER_CHANGE_STATE)
		{
		}

		return 0 ;
	}

	int HeroCard::OnUnEquip(int32 flag /*= 0*/)
	{
		if(flag & HERO_CARD_OPER_CHANGE_STATE)
		{
			this->DelOwnerMagic() ;
		}

		return 0 ;
	}

	int HeroCard::OnActivated()
	{
		SHeroCardData* pHeroCardData = g_objHeroCardDataset.GetHeroCardData(GetDID()) ;
		pwassertf(pHeroCardData) ;

		Human* pHuman = m_pOwner->QueryObjectEx<Human>();
		pwassertf(pHuman);

		pwassertf(m_pOrmHeroCard->activated == false);
		m_pOrmHeroCard->activated = true;
		m_pOrmHeroCard->star = 1;
		m_pOrmHeroCard->skill = pHeroCardData->magic_id;

		this->OrmSave(true);

		// 英雄卡牌数量任务
		pHuman->InjectQuestEvent(XQUEST_GOAL_MAINTYPE_FUNCTION, XQUEST_GOAL_SUBTYPE_HEROCARD);

		return 0 ;
	}

	int HeroCard::OnStarUp()
	{
		// 判断星级是否已满
		//sint32 nCurStar = this->GetStar() ;
		//if (0 >= nCurStar || nCurStar >= cst_hero_card_star_max)
		//	return -1 ;

		//SHeroCardData* pHeroCardData = g_objHeroCardDataset.GetHeroCardData(GetDID()) ;
		//pwassertf(pHeroCardData) ;

		//Human* pHuman = m_pOwner->QueryObjectEx<Human>();
		//pwassertf(pHuman);

		//if (this->IsEquip())
		//{
		//	// 删掉现有技能
		//	this->DelOwnerMagic() ;
		//}
		//else if (this->IsGuard())
		//{
		//}

		//// 星级变化
		//m_pOrmHeroCard->star += 1 ;

		//// 技能变化
		//pwassertf(nCurStar > 0 && nCurStar < cst_hero_card_star_max) ;
		//sint32 nSkillId = pHeroCardData->magic_id;
		//pwassertf(nSkillId > 0);
		//m_pOrmHeroCard->skill = nSkillId ;

		//if (this->IsEquip())
		//{
		//	// 增加技能
		//	this->AddOwnerMagic(this->GetEquipLoc() + MAGIC_LOC_KEYBOARD_Q) ;
		//}
		//else if (this->IsGuard())
		//{
		//}

		//this->OrmSave(true);

		return 0 ;
	}

	int HeroCard::OnLevelUp(bool bIsAuto, bool useitems)
	{
		// 判定玩家等级
		//Human* pHuman = m_pOwner->QueryObjectEx<Human>();
		//pwassertf(pHuman);
		//HumanOper oper(pHuman);
		//int nMaxLevel = pHuman->GetLevel();
		//if (GetLevel() >= nMaxLevel)
		//{
		//	return HERO_CARD_LEVELUP_FAILED_MAX_LEVEL;
		//}

		//int nCurrLevel = GetLevel();

		//// 判断升级所需物品是否足够，并计算升级的最高级
		//if (!bIsAuto)
		//{
		//	nMaxLevel = GetLevel() + 1;
		//}
		//if (useitems)
		//{
		//	CollectionPackItemsT vtItems;
		//	CollectionPackItemsT vtTestItems;
		//	for (; nCurrLevel < nMaxLevel; ++nCurrLevel)
		//	{
		//		g_objHeroCardDataset.CollectLevelUpPackItems(nCurrLevel, vtTestItems);
		//		SItemPackage spendTestPackage;
		//		spendTestPackage.ParseFromPackItems(vtTestItems);
		//		if_fail(oper.SpendItemPackageTest(spendTestPackage))
		//		{
		//			break;
		//		}
		//		g_objHeroCardDataset.CollectLevelUpPackItems(nCurrLevel, vtItems);
		//	}
		//	if (GetLevel() == nCurrLevel || vtItems.empty())
		//	{
		//		return HERO_CARD_LEVELUP_FAILED_ITEM_NOT_ENOUGH;
		//	}
		//	SItemPackage spendPackage;
		//	spendPackage.ParseFromPackItems(vtItems);
		//	if_fail(oper.SpendItemPackage(spendPackage, CASH_SPEND_TYPE_HERO_CARD_LEVELUP))
		//	{
		//		gErrorStream("HeroCard::SpendItemPackage failed.");
		//		return HERO_CARD_LEVELUP_FAILED_ITEM_NOT_ENOUGH;
		//	}
		//}

		//if (this->IsEquip())
		//{
		//	// 删掉现有技能
		//	this->DelOwnerMagic();
		//}
		//else if (this->IsGuard())
		//{
		//}

		//// 技能等级变化
		//m_pOrmHeroCard->level = nCurrLevel;

		//if (this->IsEquip())
		//{
		//	// 增加技能
		//	this->AddOwnerMagic(this->GetEquipLoc() + MAGIC_LOC_KEYBOARD_Q);
		//}
		//else if (this->IsGuard())
		//{
		//}

		//this->OrmSave(true);

		//// 增加活跃度
		//pHuman->GetModDailyBonus()->InjectActivityComplete(DAILY_BONUS_ACTIVITY_HEROCARD_LEVELUP);

		//// 英雄卡牌升级任务
		//pHuman->InjectQuestEvent(XQUEST_GOAL_MAINTYPE_FUNCTION, XQUEST_GOAL_SUBTYPE_HEROCARD_LEVELUP);

		return 0;
	}

	int HeroCard::AddOwnerMagic(sint32 loc)
	{
		/*pwassertf(loc >= MAGIC_LOC_KEYBOARD_Q && loc <= MAGIC_LOC_KEYBOARD_R);

		Human* pHuman = m_pOwner->QueryObjectEx<Human>();
		pwassertf(pHuman);

		sint32 result = pHuman->GetModMagic()->AddMagic(m_pOrmHeroCard->skill,(EMagicLocation)loc,m_pOrmHeroCard->level);

		if_succ(result)
		{
			UnitOper oper(pHuman);
			oper.SendMagicAdd(m_pOrmHeroCard->skill);

			if (pHuman->GetModHeroCard()->IsEquipLocUsed(this->GetEquipLoc()))
			{
				SMagicType* pMagicType = pHuman->GetModMagic()->GetMagicSet()->Get(m_pOrmHeroCard->skill);
				pwassertf(pMagicType);

				pHuman->GetModMagic()->StartCooldown(pMagicType, true, pMagicType->CDTime);
			}
			else
			{
				pHuman->GetModHeroCard()->UseEquipLoc(this->GetEquipLoc());
			}
		}

		return result;*/
		return 0;
	}

	int HeroCard::DelOwnerMagic()
	{
		Human* pHuman = m_pOwner->QueryObjectEx<Human>();
		pwassertf(pHuman);

		sint32 result = pHuman->GetModMagic()->DelMagic(m_pOrmHeroCard->skill);
		if_succ(result)
		{
			HumanOper oper(pHuman);
			oper.SendMagicDel(m_pOrmHeroCard->skill);
		}

		return result;
	}

	int HeroCard::OnEnterWorld()
	{
		if(this->IsEquip())
			this->OnEquip();

		if(this->IsGuard())
			this->OnGuard();

		return 0;
	}

	int HeroCard::OnLeaveWorld()
	{
		if(this->IsEquip())
			this->OnUnEquip();

		if(this->IsGuard())
			this->OnUnGuard();

		return 0;
	}

	void HeroCard::BuildStruct(MsgW(SHeroCard)& msg)
	{
		msg.set_id(GetID()) ;
		msg.set_did(GetDID()) ;
		msg.set_state(GetState()) ;
		msg.set_level(GetLevel()) ;
		msg.set_star(GetStar()) ;
		msg.set_equip_loc(GetEquipLoc()) ;
		msg.set_guard_loc(GetGuardLoc()) ;
		msg.set_guard_level(GetGuardLevel()) ;
		msg.set_skill(GetSkill()) ;
		msg.set_activated(IsActivated()) ;
		msg.set_combat_point(0);
	}
}