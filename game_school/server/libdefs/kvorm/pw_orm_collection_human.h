#ifndef _pw_orm_collection_human_
#define _pw_orm_collection_human_

#include "kvdb/pw_kvorm.h"
#include "kvdb/pw_kvorm_array.h"

namespace orm
{

	class Human;
	class Human7DayQuests;
	class HumanAchievement;
	class HumanActiviteCode;
	class HumanAcution;
	class HumanAlchemy;
	class HumanArena;
	class HumanAttr;
	class HumanBabel;
	class HumanBattle;
	class HumanCash;
	class HumanChallenge;
	class HumanChallengeLive;
	class HumanChallengeOther;
	class HumanChest;
	class HumanClientSetting;
	class HumanCommonActivity;
	class HumanCommonCooldown;
	class HumanCompletedQuests;
	class HumanContacts;
	class HumanDailyBonus;
	class HumanDailyRecharge;
	class HumanDarkarena;
	class HumanDragonHunt;
	class HumanDts;
	class HumanDungeonRecord;
	class HumanEquipRefine;
	class HumanExplore;
	class HumanFestivalActivity;
	class HumanFish;
	class HumanFlag;
	class HumanFood;
	class HumanFormation;
	class HumanFunction;
	class HumanGJFB;
	class HumanGemEquipSlotState;
	class HumanGift;
	class HumanGuide;
	class HumanGuildQuests;
	class HumanGuildShopItems;
	class HumanHellTrial;
	class HumanHero;
	class HumanHeroCollect;
	class HumanHeroTactical;
	class HumanHolyEquip;
	class HumanHotActivity;
	class HumanIntensify;
	class HumanItemExchange;
	class HumanLansquenet;
	class HumanLevelGift;
	class HumanLottery;
	class HumanLotteryPrize;
	class HumanMDLongYu;
	class HumanMDWinter;
	class HumanMagicCircle;
	class HumanMall;
	class HumanMeditation;
	class HumanMeridian;
	class HumanMilitary;
	class HumanMisc;
	class HumanMonsterManual;
	class HumanMultiplayerDungeon;
	class HumanOfflineReward;
	class HumanOnlineReward;
	class HumanOpenAuction;
	class HumanOwnedAura;
	class HumanOwnedSkill;
	class HumanPet;
	class HumanPill;
	class HumanPrayerStar;
	class HumanProduceCoin;
	class HumanPropsFund;
	class HumanPropsFundEx;
	class HumanPseudoRandom;
	class HumanRandShop;
	class HumanRandomQuests;
	class HumanRepeatableQuests;
	class HumanRide;
	class HumanRoleCreatedBonus;
	class HumanRunCar;
	class HumanShadow;
	class HumanSingleBoss;
	class HumanSkillCooldown;
	class HumanSweep;
	class HumanTeleporter;
	class HumanTencentAward;
	class HumanTimers;
	class HumanTitle;
	class HumanUnderwayQuests;
	class HumanVip;
	class HumanWarlord;
	class HumanYZSL;
	class Hero;
	class HeroCard;
	class HeroNew;
	class HolyWeapon;
	class HumanHeroSpirit;
	class HumanItems;
	class HumanLoadItemEquipPosUpgrade;
	class HumanLoadItemWash;
	class HumanLoadItems;
	class HumanNull;
	class MagicWeapon;
	class NewWeapon;

	class HumanCollection : public pwutils::KvormCollectionInteger
	{
	public:
		HumanCollection();
		~HumanCollection();
	public:
		void load(const char* __buf,size_t __len);
		void load(std::string& compressedBuf);
		void save(std::string& compressedBuf,size_t builderInitSize = 1*1024*1024);
		void save(mongo::BSONObjBuilder& __builder);
	public:
		template<class VISITOR,class PARAM> void visit(VISITOR visitor,PARAM& param)
		{
			if(!visitor(m_pHuman,param))
				return ;
			if(!visitor(m_pHuman7DayQuests,param))
				return ;
			if(!visitor(m_pHumanAchievement,param))
				return ;
			if(!visitor(m_pHumanActiviteCode,param))
				return ;
			if(!visitor(m_pHumanAcution,param))
				return ;
			if(!visitor(m_pHumanAlchemy,param))
				return ;
			if(!visitor(m_pHumanArena,param))
				return ;
			if(!visitor(m_pHumanAttr,param))
				return ;
			if(!visitor(m_pHumanBabel,param))
				return ;
			if(!visitor(m_pHumanBattle,param))
				return ;
			if(!visitor(m_pHumanCash,param))
				return ;
			if(!visitor(m_pHumanChallenge,param))
				return ;
			if(!visitor(m_pHumanChallengeLive,param))
				return ;
			if(!visitor(m_pHumanChallengeOther,param))
				return ;
			if(!visitor(m_pHumanChest,param))
				return ;
			if(!visitor(m_pHumanClientSetting,param))
				return ;
			if(!visitor(m_pHumanCommonActivity,param))
				return ;
			if(!visitor(m_pHumanCommonCooldown,param))
				return ;
			if(!visitor(m_pHumanCompletedQuests,param))
				return ;
			if(!visitor(m_pHumanContacts,param))
				return ;
			if(!visitor(m_pHumanDailyBonus,param))
				return ;
			if(!visitor(m_pHumanDailyRecharge,param))
				return ;
			if(!visitor(m_pHumanDarkarena,param))
				return ;
			if(!visitor(m_pHumanDragonHunt,param))
				return ;
			if(!visitor(m_pHumanDts,param))
				return ;
			if(!visitor(m_pHumanDungeonRecord,param))
				return ;
			if(!visitor(m_pHumanEquipRefine,param))
				return ;
			if(!visitor(m_pHumanExplore,param))
				return ;
			if(!visitor(m_pHumanFestivalActivity,param))
				return ;
			if(!visitor(m_pHumanFish,param))
				return ;
			if(!visitor(m_pHumanFlag,param))
				return ;
			if(!visitor(m_pHumanFood,param))
				return ;
			if(!visitor(m_pHumanFormation,param))
				return ;
			if(!visitor(m_pHumanFunction,param))
				return ;
			if(!visitor(m_pHumanGJFB,param))
				return ;
			if(!visitor(m_pHumanGemEquipSlotState,param))
				return ;
			if(!visitor(m_pHumanGift,param))
				return ;
			if(!visitor(m_pHumanGuide,param))
				return ;
			if(!visitor(m_pHumanGuildQuests,param))
				return ;
			if(!visitor(m_pHumanGuildShopItems,param))
				return ;
			if(!visitor(m_pHumanHellTrial,param))
				return ;
			if(!visitor(m_pHumanHero,param))
				return ;
			if(!visitor(m_pHumanHeroCollect,param))
				return ;
			if(!visitor(m_pHumanHeroTactical,param))
				return ;
			if(!visitor(m_pHumanHolyEquip,param))
				return ;
			if(!visitor(m_pHumanHotActivity,param))
				return ;
			if(!visitor(m_pHumanIntensify,param))
				return ;
			if(!visitor(m_pHumanItemExchange,param))
				return ;
			if(!visitor(m_pHumanLansquenet,param))
				return ;
			if(!visitor(m_pHumanLevelGift,param))
				return ;
			if(!visitor(m_pHumanLottery,param))
				return ;
			if(!visitor(m_pHumanLotteryPrize,param))
				return ;
			if(!visitor(m_pHumanMDLongYu,param))
				return ;
			if(!visitor(m_pHumanMDWinter,param))
				return ;
			if(!visitor(m_pHumanMagicCircle,param))
				return ;
			if(!visitor(m_pHumanMall,param))
				return ;
			if(!visitor(m_pHumanMeditation,param))
				return ;
			if(!visitor(m_pHumanMeridian,param))
				return ;
			if(!visitor(m_pHumanMilitary,param))
				return ;
			if(!visitor(m_pHumanMisc,param))
				return ;
			if(!visitor(m_pHumanMonsterManual,param))
				return ;
			if(!visitor(m_pHumanMultiplayerDungeon,param))
				return ;
			if(!visitor(m_pHumanOfflineReward,param))
				return ;
			if(!visitor(m_pHumanOnlineReward,param))
				return ;
			if(!visitor(m_pHumanOpenAuction,param))
				return ;
			if(!visitor(m_pHumanOwnedAura,param))
				return ;
			if(!visitor(m_pHumanOwnedSkill,param))
				return ;
			if(!visitor(m_pHumanPet,param))
				return ;
			if(!visitor(m_pHumanPill,param))
				return ;
			if(!visitor(m_pHumanPrayerStar,param))
				return ;
			if(!visitor(m_pHumanProduceCoin,param))
				return ;
			if(!visitor(m_pHumanPropsFund,param))
				return ;
			if(!visitor(m_pHumanPropsFundEx,param))
				return ;
			if(!visitor(m_pHumanPseudoRandom,param))
				return ;
			if(!visitor(m_pHumanRandShop,param))
				return ;
			if(!visitor(m_pHumanRandomQuests,param))
				return ;
			if(!visitor(m_pHumanRepeatableQuests,param))
				return ;
			if(!visitor(m_pHumanRide,param))
				return ;
			if(!visitor(m_pHumanRoleCreatedBonus,param))
				return ;
			if(!visitor(m_pHumanRunCar,param))
				return ;
			if(!visitor(m_pHumanShadow,param))
				return ;
			if(!visitor(m_pHumanSingleBoss,param))
				return ;
			if(!visitor(m_pHumanSkillCooldown,param))
				return ;
			if(!visitor(m_pHumanSweep,param))
				return ;
			if(!visitor(m_pHumanTeleporter,param))
				return ;
			if(!visitor(m_pHumanTencentAward,param))
				return ;
			if(!visitor(m_pHumanTimers,param))
				return ;
			if(!visitor(m_pHumanTitle,param))
				return ;
			if(!visitor(m_pHumanUnderwayQuests,param))
				return ;
			if(!visitor(m_pHumanVip,param))
				return ;
			if(!visitor(m_pHumanWarlord,param))
				return ;
			if(!visitor(m_pHumanYZSL,param))
				return ;

			for(pwutils::KvormObjectArray<Hero*>::iterator iter = m_vHero.begin(); iter != m_vHero.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
			for(pwutils::KvormObjectArray<HeroCard*>::iterator iter = m_vHeroCard.begin(); iter != m_vHeroCard.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
			for(pwutils::KvormObjectArray<HeroNew*>::iterator iter = m_vHeroNew.begin(); iter != m_vHeroNew.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
			for(pwutils::KvormObjectArray<HolyWeapon*>::iterator iter = m_vHolyWeapon.begin(); iter != m_vHolyWeapon.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
			for(pwutils::KvormObjectArray<HumanHeroSpirit*>::iterator iter = m_vHumanHeroSpirit.begin(); iter != m_vHumanHeroSpirit.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
			for(pwutils::KvormObjectArray<HumanItems*>::iterator iter = m_vHumanItems.begin(); iter != m_vHumanItems.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
			for(pwutils::KvormObjectArray<HumanLoadItemEquipPosUpgrade*>::iterator iter = m_vHumanLoadItemEquipPosUpgrade.begin(); iter != m_vHumanLoadItemEquipPosUpgrade.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
			for(pwutils::KvormObjectArray<HumanLoadItemWash*>::iterator iter = m_vHumanLoadItemWash.begin(); iter != m_vHumanLoadItemWash.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
			for(pwutils::KvormObjectArray<HumanLoadItems*>::iterator iter = m_vHumanLoadItems.begin(); iter != m_vHumanLoadItems.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
			for(pwutils::KvormObjectArray<HumanNull*>::iterator iter = m_vHumanNull.begin(); iter != m_vHumanNull.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
			for(pwutils::KvormObjectArray<MagicWeapon*>::iterator iter = m_vMagicWeapon.begin(); iter != m_vMagicWeapon.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
			for(pwutils::KvormObjectArray<NewWeapon*>::iterator iter = m_vNewWeapon.begin(); iter != m_vNewWeapon.end(); ++iter)
			{
				if(!visitor(*iter,param))
					return;
			}
		}
	public:
		Human* human() { return m_pHuman; }
		Human* mutable_human();
		void cleanup_human();

		Human7DayQuests* human7dayquests() { return m_pHuman7DayQuests; }
		Human7DayQuests* mutable_human7dayquests();
		void cleanup_human7dayquests();

		HumanAchievement* humanachievement() { return m_pHumanAchievement; }
		HumanAchievement* mutable_humanachievement();
		void cleanup_humanachievement();

		HumanActiviteCode* humanactivitecode() { return m_pHumanActiviteCode; }
		HumanActiviteCode* mutable_humanactivitecode();
		void cleanup_humanactivitecode();

		HumanAcution* humanacution() { return m_pHumanAcution; }
		HumanAcution* mutable_humanacution();
		void cleanup_humanacution();

		HumanAlchemy* humanalchemy() { return m_pHumanAlchemy; }
		HumanAlchemy* mutable_humanalchemy();
		void cleanup_humanalchemy();

		HumanArena* humanarena() { return m_pHumanArena; }
		HumanArena* mutable_humanarena();
		void cleanup_humanarena();

		HumanAttr* humanattr() { return m_pHumanAttr; }
		HumanAttr* mutable_humanattr();
		void cleanup_humanattr();

		HumanBabel* humanbabel() { return m_pHumanBabel; }
		HumanBabel* mutable_humanbabel();
		void cleanup_humanbabel();

		HumanBattle* humanbattle() { return m_pHumanBattle; }
		HumanBattle* mutable_humanbattle();
		void cleanup_humanbattle();

		HumanCash* humancash() { return m_pHumanCash; }
		HumanCash* mutable_humancash();
		void cleanup_humancash();

		HumanChallenge* humanchallenge() { return m_pHumanChallenge; }
		HumanChallenge* mutable_humanchallenge();
		void cleanup_humanchallenge();

		HumanChallengeLive* humanchallengelive() { return m_pHumanChallengeLive; }
		HumanChallengeLive* mutable_humanchallengelive();
		void cleanup_humanchallengelive();

		HumanChallengeOther* humanchallengeother() { return m_pHumanChallengeOther; }
		HumanChallengeOther* mutable_humanchallengeother();
		void cleanup_humanchallengeother();

		HumanChest* humanchest() { return m_pHumanChest; }
		HumanChest* mutable_humanchest();
		void cleanup_humanchest();

		HumanClientSetting* humanclientsetting() { return m_pHumanClientSetting; }
		HumanClientSetting* mutable_humanclientsetting();
		void cleanup_humanclientsetting();

		HumanCommonActivity* humancommonactivity() { return m_pHumanCommonActivity; }
		HumanCommonActivity* mutable_humancommonactivity();
		void cleanup_humancommonactivity();

		HumanCommonCooldown* humancommoncooldown() { return m_pHumanCommonCooldown; }
		HumanCommonCooldown* mutable_humancommoncooldown();
		void cleanup_humancommoncooldown();

		HumanCompletedQuests* humancompletedquests() { return m_pHumanCompletedQuests; }
		HumanCompletedQuests* mutable_humancompletedquests();
		void cleanup_humancompletedquests();

		HumanContacts* humancontacts() { return m_pHumanContacts; }
		HumanContacts* mutable_humancontacts();
		void cleanup_humancontacts();

		HumanDailyBonus* humandailybonus() { return m_pHumanDailyBonus; }
		HumanDailyBonus* mutable_humandailybonus();
		void cleanup_humandailybonus();

		HumanDailyRecharge* humandailyrecharge() { return m_pHumanDailyRecharge; }
		HumanDailyRecharge* mutable_humandailyrecharge();
		void cleanup_humandailyrecharge();

		HumanDarkarena* humandarkarena() { return m_pHumanDarkarena; }
		HumanDarkarena* mutable_humandarkarena();
		void cleanup_humandarkarena();

		HumanDragonHunt* humandragonhunt() { return m_pHumanDragonHunt; }
		HumanDragonHunt* mutable_humandragonhunt();
		void cleanup_humandragonhunt();

		HumanDts* humandts() { return m_pHumanDts; }
		HumanDts* mutable_humandts();
		void cleanup_humandts();

		HumanDungeonRecord* humandungeonrecord() { return m_pHumanDungeonRecord; }
		HumanDungeonRecord* mutable_humandungeonrecord();
		void cleanup_humandungeonrecord();

		HumanEquipRefine* humanequiprefine() { return m_pHumanEquipRefine; }
		HumanEquipRefine* mutable_humanequiprefine();
		void cleanup_humanequiprefine();

		HumanExplore* humanexplore() { return m_pHumanExplore; }
		HumanExplore* mutable_humanexplore();
		void cleanup_humanexplore();

		HumanFestivalActivity* humanfestivalactivity() { return m_pHumanFestivalActivity; }
		HumanFestivalActivity* mutable_humanfestivalactivity();
		void cleanup_humanfestivalactivity();

		HumanFish* humanfish() { return m_pHumanFish; }
		HumanFish* mutable_humanfish();
		void cleanup_humanfish();

		HumanFlag* humanflag() { return m_pHumanFlag; }
		HumanFlag* mutable_humanflag();
		void cleanup_humanflag();

		HumanFood* humanfood() { return m_pHumanFood; }
		HumanFood* mutable_humanfood();
		void cleanup_humanfood();

		HumanFormation* humanformation() { return m_pHumanFormation; }
		HumanFormation* mutable_humanformation();
		void cleanup_humanformation();

		HumanFunction* humanfunction() { return m_pHumanFunction; }
		HumanFunction* mutable_humanfunction();
		void cleanup_humanfunction();

		HumanGJFB* humangjfb() { return m_pHumanGJFB; }
		HumanGJFB* mutable_humangjfb();
		void cleanup_humangjfb();

		HumanGemEquipSlotState* humangemequipslotstate() { return m_pHumanGemEquipSlotState; }
		HumanGemEquipSlotState* mutable_humangemequipslotstate();
		void cleanup_humangemequipslotstate();

		HumanGift* humangift() { return m_pHumanGift; }
		HumanGift* mutable_humangift();
		void cleanup_humangift();

		HumanGuide* humanguide() { return m_pHumanGuide; }
		HumanGuide* mutable_humanguide();
		void cleanup_humanguide();

		HumanGuildQuests* humanguildquests() { return m_pHumanGuildQuests; }
		HumanGuildQuests* mutable_humanguildquests();
		void cleanup_humanguildquests();

		HumanGuildShopItems* humanguildshopitems() { return m_pHumanGuildShopItems; }
		HumanGuildShopItems* mutable_humanguildshopitems();
		void cleanup_humanguildshopitems();

		HumanHellTrial* humanhelltrial() { return m_pHumanHellTrial; }
		HumanHellTrial* mutable_humanhelltrial();
		void cleanup_humanhelltrial();

		HumanHero* humanhero() { return m_pHumanHero; }
		HumanHero* mutable_humanhero();
		void cleanup_humanhero();

		HumanHeroCollect* humanherocollect() { return m_pHumanHeroCollect; }
		HumanHeroCollect* mutable_humanherocollect();
		void cleanup_humanherocollect();

		HumanHeroTactical* humanherotactical() { return m_pHumanHeroTactical; }
		HumanHeroTactical* mutable_humanherotactical();
		void cleanup_humanherotactical();

		HumanHolyEquip* humanholyequip() { return m_pHumanHolyEquip; }
		HumanHolyEquip* mutable_humanholyequip();
		void cleanup_humanholyequip();

		HumanHotActivity* humanhotactivity() { return m_pHumanHotActivity; }
		HumanHotActivity* mutable_humanhotactivity();
		void cleanup_humanhotactivity();

		HumanIntensify* humanintensify() { return m_pHumanIntensify; }
		HumanIntensify* mutable_humanintensify();
		void cleanup_humanintensify();

		HumanItemExchange* humanitemexchange() { return m_pHumanItemExchange; }
		HumanItemExchange* mutable_humanitemexchange();
		void cleanup_humanitemexchange();

		HumanLansquenet* humanlansquenet() { return m_pHumanLansquenet; }
		HumanLansquenet* mutable_humanlansquenet();
		void cleanup_humanlansquenet();

		HumanLevelGift* humanlevelgift() { return m_pHumanLevelGift; }
		HumanLevelGift* mutable_humanlevelgift();
		void cleanup_humanlevelgift();

		HumanLottery* humanlottery() { return m_pHumanLottery; }
		HumanLottery* mutable_humanlottery();
		void cleanup_humanlottery();

		HumanLotteryPrize* humanlotteryprize() { return m_pHumanLotteryPrize; }
		HumanLotteryPrize* mutable_humanlotteryprize();
		void cleanup_humanlotteryprize();

		HumanMDLongYu* humanmdlongyu() { return m_pHumanMDLongYu; }
		HumanMDLongYu* mutable_humanmdlongyu();
		void cleanup_humanmdlongyu();

		HumanMDWinter* humanmdwinter() { return m_pHumanMDWinter; }
		HumanMDWinter* mutable_humanmdwinter();
		void cleanup_humanmdwinter();

		HumanMagicCircle* humanmagiccircle() { return m_pHumanMagicCircle; }
		HumanMagicCircle* mutable_humanmagiccircle();
		void cleanup_humanmagiccircle();

		HumanMall* humanmall() { return m_pHumanMall; }
		HumanMall* mutable_humanmall();
		void cleanup_humanmall();

		HumanMeditation* humanmeditation() { return m_pHumanMeditation; }
		HumanMeditation* mutable_humanmeditation();
		void cleanup_humanmeditation();

		HumanMeridian* humanmeridian() { return m_pHumanMeridian; }
		HumanMeridian* mutable_humanmeridian();
		void cleanup_humanmeridian();

		HumanMilitary* humanmilitary() { return m_pHumanMilitary; }
		HumanMilitary* mutable_humanmilitary();
		void cleanup_humanmilitary();

		HumanMisc* humanmisc() { return m_pHumanMisc; }
		HumanMisc* mutable_humanmisc();
		void cleanup_humanmisc();

		HumanMonsterManual* humanmonstermanual() { return m_pHumanMonsterManual; }
		HumanMonsterManual* mutable_humanmonstermanual();
		void cleanup_humanmonstermanual();

		HumanMultiplayerDungeon* humanmultiplayerdungeon() { return m_pHumanMultiplayerDungeon; }
		HumanMultiplayerDungeon* mutable_humanmultiplayerdungeon();
		void cleanup_humanmultiplayerdungeon();

		HumanOfflineReward* humanofflinereward() { return m_pHumanOfflineReward; }
		HumanOfflineReward* mutable_humanofflinereward();
		void cleanup_humanofflinereward();

		HumanOnlineReward* humanonlinereward() { return m_pHumanOnlineReward; }
		HumanOnlineReward* mutable_humanonlinereward();
		void cleanup_humanonlinereward();

		HumanOpenAuction* humanopenauction() { return m_pHumanOpenAuction; }
		HumanOpenAuction* mutable_humanopenauction();
		void cleanup_humanopenauction();

		HumanOwnedAura* humanownedaura() { return m_pHumanOwnedAura; }
		HumanOwnedAura* mutable_humanownedaura();
		void cleanup_humanownedaura();

		HumanOwnedSkill* humanownedskill() { return m_pHumanOwnedSkill; }
		HumanOwnedSkill* mutable_humanownedskill();
		void cleanup_humanownedskill();

		HumanPet* humanpet() { return m_pHumanPet; }
		HumanPet* mutable_humanpet();
		void cleanup_humanpet();

		HumanPill* humanpill() { return m_pHumanPill; }
		HumanPill* mutable_humanpill();
		void cleanup_humanpill();

		HumanPrayerStar* humanprayerstar() { return m_pHumanPrayerStar; }
		HumanPrayerStar* mutable_humanprayerstar();
		void cleanup_humanprayerstar();

		HumanProduceCoin* humanproducecoin() { return m_pHumanProduceCoin; }
		HumanProduceCoin* mutable_humanproducecoin();
		void cleanup_humanproducecoin();

		HumanPropsFund* humanpropsfund() { return m_pHumanPropsFund; }
		HumanPropsFund* mutable_humanpropsfund();
		void cleanup_humanpropsfund();

		HumanPropsFundEx* humanpropsfundex() { return m_pHumanPropsFundEx; }
		HumanPropsFundEx* mutable_humanpropsfundex();
		void cleanup_humanpropsfundex();

		HumanPseudoRandom* humanpseudorandom() { return m_pHumanPseudoRandom; }
		HumanPseudoRandom* mutable_humanpseudorandom();
		void cleanup_humanpseudorandom();

		HumanRandShop* humanrandshop() { return m_pHumanRandShop; }
		HumanRandShop* mutable_humanrandshop();
		void cleanup_humanrandshop();

		HumanRandomQuests* humanrandomquests() { return m_pHumanRandomQuests; }
		HumanRandomQuests* mutable_humanrandomquests();
		void cleanup_humanrandomquests();

		HumanRepeatableQuests* humanrepeatablequests() { return m_pHumanRepeatableQuests; }
		HumanRepeatableQuests* mutable_humanrepeatablequests();
		void cleanup_humanrepeatablequests();

		HumanRide* humanride() { return m_pHumanRide; }
		HumanRide* mutable_humanride();
		void cleanup_humanride();

		HumanRoleCreatedBonus* humanrolecreatedbonus() { return m_pHumanRoleCreatedBonus; }
		HumanRoleCreatedBonus* mutable_humanrolecreatedbonus();
		void cleanup_humanrolecreatedbonus();

		HumanRunCar* humanruncar() { return m_pHumanRunCar; }
		HumanRunCar* mutable_humanruncar();
		void cleanup_humanruncar();

		HumanShadow* humanshadow() { return m_pHumanShadow; }
		HumanShadow* mutable_humanshadow();
		void cleanup_humanshadow();

		HumanSingleBoss* humansingleboss() { return m_pHumanSingleBoss; }
		HumanSingleBoss* mutable_humansingleboss();
		void cleanup_humansingleboss();

		HumanSkillCooldown* humanskillcooldown() { return m_pHumanSkillCooldown; }
		HumanSkillCooldown* mutable_humanskillcooldown();
		void cleanup_humanskillcooldown();

		HumanSweep* humansweep() { return m_pHumanSweep; }
		HumanSweep* mutable_humansweep();
		void cleanup_humansweep();

		HumanTeleporter* humanteleporter() { return m_pHumanTeleporter; }
		HumanTeleporter* mutable_humanteleporter();
		void cleanup_humanteleporter();

		HumanTencentAward* humantencentaward() { return m_pHumanTencentAward; }
		HumanTencentAward* mutable_humantencentaward();
		void cleanup_humantencentaward();

		HumanTimers* humantimers() { return m_pHumanTimers; }
		HumanTimers* mutable_humantimers();
		void cleanup_humantimers();

		HumanTitle* humantitle() { return m_pHumanTitle; }
		HumanTitle* mutable_humantitle();
		void cleanup_humantitle();

		HumanUnderwayQuests* humanunderwayquests() { return m_pHumanUnderwayQuests; }
		HumanUnderwayQuests* mutable_humanunderwayquests();
		void cleanup_humanunderwayquests();

		HumanVip* humanvip() { return m_pHumanVip; }
		HumanVip* mutable_humanvip();
		void cleanup_humanvip();

		HumanWarlord* humanwarlord() { return m_pHumanWarlord; }
		HumanWarlord* mutable_humanwarlord();
		void cleanup_humanwarlord();

		HumanYZSL* humanyzsl() { return m_pHumanYZSL; }
		HumanYZSL* mutable_humanyzsl();
		void cleanup_humanyzsl();

	public:
		inline pwutils::KvormObjectArray< Hero* >& hero() { return m_vHero; }
		inline pwutils::KvormObjectArray< HeroCard* >& herocard() { return m_vHeroCard; }
		inline pwutils::KvormObjectArray< HeroNew* >& heronew() { return m_vHeroNew; }
		inline pwutils::KvormObjectArray< HolyWeapon* >& holyweapon() { return m_vHolyWeapon; }
		inline pwutils::KvormObjectArray< HumanHeroSpirit* >& humanherospirit() { return m_vHumanHeroSpirit; }
		inline pwutils::KvormObjectArray< HumanItems* >& humanitems() { return m_vHumanItems; }
		inline pwutils::KvormObjectArray< HumanLoadItemEquipPosUpgrade* >& humanloaditemequipposupgrade() { return m_vHumanLoadItemEquipPosUpgrade; }
		inline pwutils::KvormObjectArray< HumanLoadItemWash* >& humanloaditemwash() { return m_vHumanLoadItemWash; }
		inline pwutils::KvormObjectArray< HumanLoadItems* >& humanloaditems() { return m_vHumanLoadItems; }
		inline pwutils::KvormObjectArray< HumanNull* >& humannull() { return m_vHumanNull; }
		inline pwutils::KvormObjectArray< MagicWeapon* >& magicweapon() { return m_vMagicWeapon; }
		inline pwutils::KvormObjectArray< NewWeapon* >& newweapon() { return m_vNewWeapon; }
	public:
		Hero* new_hero(bool manager = true);
		bool del_hero(Hero* value,bool freeIt = false);
		void load_hero(mongo::BSONObj& __obj);
		void save_hero(mongo::BSONArrayBuilder& __tmpbuilder);

		HeroCard* new_herocard(bool manager = true);
		bool del_herocard(HeroCard* value,bool freeIt = false);
		void load_herocard(mongo::BSONObj& __obj);
		void save_herocard(mongo::BSONArrayBuilder& __tmpbuilder);

		HeroNew* new_heronew(bool manager = true);
		bool del_heronew(HeroNew* value,bool freeIt = false);
		void load_heronew(mongo::BSONObj& __obj);
		void save_heronew(mongo::BSONArrayBuilder& __tmpbuilder);

		HolyWeapon* new_holyweapon(bool manager = true);
		bool del_holyweapon(HolyWeapon* value,bool freeIt = false);
		void load_holyweapon(mongo::BSONObj& __obj);
		void save_holyweapon(mongo::BSONArrayBuilder& __tmpbuilder);

		HumanHeroSpirit* new_humanherospirit(bool manager = true);
		bool del_humanherospirit(HumanHeroSpirit* value,bool freeIt = false);
		void load_humanherospirit(mongo::BSONObj& __obj);
		void save_humanherospirit(mongo::BSONArrayBuilder& __tmpbuilder);

		HumanItems* new_humanitems(bool manager = true);
		bool del_humanitems(HumanItems* value,bool freeIt = false);
		void load_humanitems(mongo::BSONObj& __obj);
		void save_humanitems(mongo::BSONArrayBuilder& __tmpbuilder);

		HumanLoadItemEquipPosUpgrade* new_humanloaditemequipposupgrade(bool manager = true);
		bool del_humanloaditemequipposupgrade(HumanLoadItemEquipPosUpgrade* value,bool freeIt = false);
		void load_humanloaditemequipposupgrade(mongo::BSONObj& __obj);
		void save_humanloaditemequipposupgrade(mongo::BSONArrayBuilder& __tmpbuilder);

		HumanLoadItemWash* new_humanloaditemwash(bool manager = true);
		bool del_humanloaditemwash(HumanLoadItemWash* value,bool freeIt = false);
		void load_humanloaditemwash(mongo::BSONObj& __obj);
		void save_humanloaditemwash(mongo::BSONArrayBuilder& __tmpbuilder);

		HumanLoadItems* new_humanloaditems(bool manager = true);
		bool del_humanloaditems(HumanLoadItems* value,bool freeIt = false);
		void load_humanloaditems(mongo::BSONObj& __obj);
		void save_humanloaditems(mongo::BSONArrayBuilder& __tmpbuilder);

		HumanNull* new_humannull(bool manager = true);
		bool del_humannull(HumanNull* value,bool freeIt = false);
		void load_humannull(mongo::BSONObj& __obj);
		void save_humannull(mongo::BSONArrayBuilder& __tmpbuilder);

		MagicWeapon* new_magicweapon(bool manager = true);
		bool del_magicweapon(MagicWeapon* value,bool freeIt = false);
		void load_magicweapon(mongo::BSONObj& __obj);
		void save_magicweapon(mongo::BSONArrayBuilder& __tmpbuilder);

		NewWeapon* new_newweapon(bool manager = true);
		bool del_newweapon(NewWeapon* value,bool freeIt = false);
		void load_newweapon(mongo::BSONObj& __obj);
		void save_newweapon(mongo::BSONArrayBuilder& __tmpbuilder);

	private:
		Human* m_pHuman;
		Human7DayQuests* m_pHuman7DayQuests;
		HumanAchievement* m_pHumanAchievement;
		HumanActiviteCode* m_pHumanActiviteCode;
		HumanAcution* m_pHumanAcution;
		HumanAlchemy* m_pHumanAlchemy;
		HumanArena* m_pHumanArena;
		HumanAttr* m_pHumanAttr;
		HumanBabel* m_pHumanBabel;
		HumanBattle* m_pHumanBattle;
		HumanCash* m_pHumanCash;
		HumanChallenge* m_pHumanChallenge;
		HumanChallengeLive* m_pHumanChallengeLive;
		HumanChallengeOther* m_pHumanChallengeOther;
		HumanChest* m_pHumanChest;
		HumanClientSetting* m_pHumanClientSetting;
		HumanCommonActivity* m_pHumanCommonActivity;
		HumanCommonCooldown* m_pHumanCommonCooldown;
		HumanCompletedQuests* m_pHumanCompletedQuests;
		HumanContacts* m_pHumanContacts;
		HumanDailyBonus* m_pHumanDailyBonus;
		HumanDailyRecharge* m_pHumanDailyRecharge;
		HumanDarkarena* m_pHumanDarkarena;
		HumanDragonHunt* m_pHumanDragonHunt;
		HumanDts* m_pHumanDts;
		HumanDungeonRecord* m_pHumanDungeonRecord;
		HumanEquipRefine* m_pHumanEquipRefine;
		HumanExplore* m_pHumanExplore;
		HumanFestivalActivity* m_pHumanFestivalActivity;
		HumanFish* m_pHumanFish;
		HumanFlag* m_pHumanFlag;
		HumanFood* m_pHumanFood;
		HumanFormation* m_pHumanFormation;
		HumanFunction* m_pHumanFunction;
		HumanGJFB* m_pHumanGJFB;
		HumanGemEquipSlotState* m_pHumanGemEquipSlotState;
		HumanGift* m_pHumanGift;
		HumanGuide* m_pHumanGuide;
		HumanGuildQuests* m_pHumanGuildQuests;
		HumanGuildShopItems* m_pHumanGuildShopItems;
		HumanHellTrial* m_pHumanHellTrial;
		HumanHero* m_pHumanHero;
		HumanHeroCollect* m_pHumanHeroCollect;
		HumanHeroTactical* m_pHumanHeroTactical;
		HumanHolyEquip* m_pHumanHolyEquip;
		HumanHotActivity* m_pHumanHotActivity;
		HumanIntensify* m_pHumanIntensify;
		HumanItemExchange* m_pHumanItemExchange;
		HumanLansquenet* m_pHumanLansquenet;
		HumanLevelGift* m_pHumanLevelGift;
		HumanLottery* m_pHumanLottery;
		HumanLotteryPrize* m_pHumanLotteryPrize;
		HumanMDLongYu* m_pHumanMDLongYu;
		HumanMDWinter* m_pHumanMDWinter;
		HumanMagicCircle* m_pHumanMagicCircle;
		HumanMall* m_pHumanMall;
		HumanMeditation* m_pHumanMeditation;
		HumanMeridian* m_pHumanMeridian;
		HumanMilitary* m_pHumanMilitary;
		HumanMisc* m_pHumanMisc;
		HumanMonsterManual* m_pHumanMonsterManual;
		HumanMultiplayerDungeon* m_pHumanMultiplayerDungeon;
		HumanOfflineReward* m_pHumanOfflineReward;
		HumanOnlineReward* m_pHumanOnlineReward;
		HumanOpenAuction* m_pHumanOpenAuction;
		HumanOwnedAura* m_pHumanOwnedAura;
		HumanOwnedSkill* m_pHumanOwnedSkill;
		HumanPet* m_pHumanPet;
		HumanPill* m_pHumanPill;
		HumanPrayerStar* m_pHumanPrayerStar;
		HumanProduceCoin* m_pHumanProduceCoin;
		HumanPropsFund* m_pHumanPropsFund;
		HumanPropsFundEx* m_pHumanPropsFundEx;
		HumanPseudoRandom* m_pHumanPseudoRandom;
		HumanRandShop* m_pHumanRandShop;
		HumanRandomQuests* m_pHumanRandomQuests;
		HumanRepeatableQuests* m_pHumanRepeatableQuests;
		HumanRide* m_pHumanRide;
		HumanRoleCreatedBonus* m_pHumanRoleCreatedBonus;
		HumanRunCar* m_pHumanRunCar;
		HumanShadow* m_pHumanShadow;
		HumanSingleBoss* m_pHumanSingleBoss;
		HumanSkillCooldown* m_pHumanSkillCooldown;
		HumanSweep* m_pHumanSweep;
		HumanTeleporter* m_pHumanTeleporter;
		HumanTencentAward* m_pHumanTencentAward;
		HumanTimers* m_pHumanTimers;
		HumanTitle* m_pHumanTitle;
		HumanUnderwayQuests* m_pHumanUnderwayQuests;
		HumanVip* m_pHumanVip;
		HumanWarlord* m_pHumanWarlord;
		HumanYZSL* m_pHumanYZSL;
	private:
		pwutils::KvormObjectArray<Hero* > m_vHero;
		pwutils::KvormObjectArray<HeroCard* > m_vHeroCard;
		pwutils::KvormObjectArray<HeroNew* > m_vHeroNew;
		pwutils::KvormObjectArray<HolyWeapon* > m_vHolyWeapon;
		pwutils::KvormObjectArray<HumanHeroSpirit* > m_vHumanHeroSpirit;
		pwutils::KvormObjectArray<HumanItems* > m_vHumanItems;
		pwutils::KvormObjectArray<HumanLoadItemEquipPosUpgrade* > m_vHumanLoadItemEquipPosUpgrade;
		pwutils::KvormObjectArray<HumanLoadItemWash* > m_vHumanLoadItemWash;
		pwutils::KvormObjectArray<HumanLoadItems* > m_vHumanLoadItems;
		pwutils::KvormObjectArray<HumanNull* > m_vHumanNull;
		pwutils::KvormObjectArray<MagicWeapon* > m_vMagicWeapon;
		pwutils::KvormObjectArray<NewWeapon* > m_vNewWeapon;
	};
}

#endif // _pw_orm_collection_human_
