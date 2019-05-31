#ifndef _pw_hero_card_
#define _pw_hero_card_

#include "kvorm/pw_orm_herocard.h"
#include "pw_memory.h"
#include "pw_hero_card_def.h"

namespace pwngs
{
	PreDefineMsgW(SHeroCard);

	class Unit;

	struct SStatisticModifier ;

	class HeroCard : public pwutils::memory::ObjectInThread<HeroCard>
	{
	public:
		HeroCard(orm::HeroCard* heroCard,Unit* owner);
		virtual ~HeroCard();

	public:
		int					OrmLoad();
		int					OrmSave(bool update = true);

	public:
		int					Cleanup();

	public:
		int					InitialFromConfig();

	public:
		inline int32		GetEquipLoc() { return (int32)m_pOrmHeroCard->equip_loc; } ;
		inline void			SetEquipLoc(int32 loc) { m_pOrmHeroCard->equip_loc = loc ; } ;
		inline int32		GetGuardLoc() { return (int32)m_pOrmHeroCard->guard_loc; } ;
		inline void			SetGuardLoc(int32 loc) { m_pOrmHeroCard->guard_loc = loc ;} ;

	public:
		inline orm::HeroCard*	GetOrmHeroCard() { return m_pOrmHeroCard ; } ;

	public:
		inline sint64		GetID() const { return m_pOrmHeroCard->id ; } ;
		inline sint32		GetDID() const { return m_pOrmHeroCard->did ; } ;
		inline int32		GetState() const { return m_pOrmHeroCard->state ; } ;
		inline sint32		GetLevel() const { return m_pOrmHeroCard->level ; } ;
		inline int32		GetStar() const { return m_pOrmHeroCard->star ; } ;
		inline int32		GetGuardLevel() const { return m_pOrmHeroCard->guard_level ;} 
		inline int32		GetSkill() const { return m_pOrmHeroCard->skill ; } ;
		inline bool		IsActivated() const { return m_pOrmHeroCard->activated ; } ;

	public:
		inline bool			IsEquip() { return m_pOrmHeroCard->state == HERO_CARD_STATE_EQUIP ; } ;
		inline bool			IsGuard() { return m_pOrmHeroCard->state == HERO_CARD_STATE_GUARD ; } ;
		inline bool			IsIdle() { return m_pOrmHeroCard->state == HERO_CARD_STATE_IDLE; } ;

	public:
		int					OnIdle(int32 flag = 0) ;
		int					OnGuard(int32 flag = 0) ;
		int					OnEquip(int32 flag = 0) ;
		int					OnUnGuard(int32 flag = 0) ;
		int					OnUnEquip(int32 flag = 0) ;
		int					OnActivated() ;
		int					OnStarUp() ;
		int					OnLevelUp(bool bIsAuto = false, bool useitems = true);

	public:
		int					AddOwnerMagic(sint32 loc) ;
		int					DelOwnerMagic() ;

	public:
		int					OnEnterWorld() ;
		int					OnLeaveWorld() ;

	public:
		void				BuildStruct(MsgW(SHeroCard)& msg) ;

	private:
		Unit* m_pOwner;
		orm::HeroCard* m_pOrmHeroCard;
	};
}


#endif
