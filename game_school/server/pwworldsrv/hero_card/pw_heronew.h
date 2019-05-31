#ifndef _pw_heronew_
#define _pw_heronew_

#include "kvorm/pw_orm_heronew.h"
#include "pw_memory.h"
#include "pw_heronew_def.h"

namespace pwngs
{
	PreDefineMsgW(SHeroNew);

	class Unit;

	struct SStatisticModifier ;

	class HeroNew : public pwutils::memory::ObjectInThread<HeroNew>
	{
	public:
		HeroNew(orm::HeroNew* heroCard,Unit* owner);
		virtual ~HeroNew();

	public:
		int					OrmLoad();
		int					OrmSave(bool update = true);

	public:
		int					InitialFromConfig();

	public:
		inline orm::HeroNew*	GetOrmHeroNew() { return m_pOrmHeroNew; };
		inline sint64		GetID() const { return m_pOrmHeroNew->id ; } ;
		inline sint32		GetDID() const { return m_pOrmHeroNew->did ; } ;
		inline int32		GetState() const { return m_pOrmHeroNew->state ; } ;
		inline int32		GetStar() const { return m_pOrmHeroNew->star ; } ;
		inline bool		IsActivated() const { return m_pOrmHeroNew->activated ; } ;
		inline int32		GetAssistanceLoc() { return (int32)m_pOrmHeroNew->assistance_loc; };
		inline void			SetAssistanceLoc(int32 loc) { m_pOrmHeroNew->assistance_loc = loc; };
		inline int16		GetRank() const { return m_pOrmHeroNew->get_rank(); }
		inline void			SetRank(int16 nRank) { m_pOrmHeroNew->set_rank(nRank); }
		inline int16		GetRankItemFlag() const { return m_pOrmHeroNew->get_rank_item_flag(); }
		inline void			SetRankItemFlag(int16 nFlag) { m_pOrmHeroNew->set_rank_item_flag(nFlag); }
		inline bool		IsAssistance() { return m_pOrmHeroNew->state == HERONEW_STATE_ASSISTANCE; };
		inline bool		IsIdle() { return m_pOrmHeroNew->state == HERONEW_STATE_IDLE; };

	public:
		int					OnIdle() ;
		int					OnAssistance(float fPlusrate);
		int					OnUnAssistance(float fPlusrate);
		int					OnActivated(bool useitems = true) ;
		int					OnStarUp(bool useitems = true) ;
		int					OnEmbed(int16 nRankItemFlag, bool useitems = true);
		int					OnRankUp();

	public:
		int					GetAura();
		int					AddAura();
		int					DelAura();

	public:
		int					OnEnterWorld() ;
		int					OnLeaveWorld() ;

	public:
		void					BuildStruct(MsgW(SHeroNew)& msg);

	public:
		/**
		 * @brief 附加属性操作
		 */
		int					HandleStatisticOnActivated(bool apply, float fPlusrate = 1.0f);
		/**
		* @brief 战力计算
		*/
		int					HandleCombatPointOnActivated(bool apply);
		/**
		 * @brief 属性变化
		 */
		int					HandleStatistic(std::vector<SStatisticModifier>& vtStat,bool apply,float plusrate = 1.0f);
		/**
		* @brief 计算战力
		*/
		float					CalcCombatPoint();

	private:
		Unit* m_pOwner;
		orm::HeroNew* m_pOrmHeroNew;
	};
}


#endif
