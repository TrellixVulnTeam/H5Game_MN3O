#include "kvorm/pw_orm_collection_human.h"
#include "pw_logger.h"
#include "pw_utils.h"
#include "snappy/snappy.h"

#include "kvorm/pw_orm_human.h"
//#include "kvorm/pw_orm_human7dayquests.h"
//#include "kvorm/pw_orm_humanachievement.h"
//#include "kvorm/pw_orm_humanactivitecode.h"
//#include "kvorm/pw_orm_humanacution.h"
//#include "kvorm/pw_orm_humanalchemy.h"
//#include "kvorm/pw_orm_humanarena.h"
//#include "kvorm/pw_orm_humanattr.h"
//#include "kvorm/pw_orm_humanbabel.h"
//#include "kvorm/pw_orm_humanbattle.h"
//#include "kvorm/pw_orm_humancash.h"
//#include "kvorm/pw_orm_humanchallenge.h"
//#include "kvorm/pw_orm_humanchallengelive.h"
//#include "kvorm/pw_orm_humanchallengeother.h"
//#include "kvorm/pw_orm_humanchest.h"
//#include "kvorm/pw_orm_humanclientsetting.h"
//#include "kvorm/pw_orm_humancommonactivity.h"
//#include "kvorm/pw_orm_humancommoncooldown.h"
//#include "kvorm/pw_orm_humancompletedquests.h"
//#include "kvorm/pw_orm_humancontacts.h"
//#include "kvorm/pw_orm_humandailybonus.h"
//#include "kvorm/pw_orm_humandailyrecharge.h"
//#include "kvorm/pw_orm_humandarkarena.h"
//#include "kvorm/pw_orm_humandragonhunt.h"
//#include "kvorm/pw_orm_humandts.h"
//#include "kvorm/pw_orm_humandungeonrecord.h"
//#include "kvorm/pw_orm_humanequiprefine.h"
//#include "kvorm/pw_orm_humanexplore.h"
//#include "kvorm/pw_orm_humanfestivalactivity.h"
//#include "kvorm/pw_orm_humanfish.h"
//#include "kvorm/pw_orm_humanflag.h"
//#include "kvorm/pw_orm_humanfood.h"
//#include "kvorm/pw_orm_humanformation.h"
//#include "kvorm/pw_orm_humanfunction.h"
//#include "kvorm/pw_orm_humangjfb.h"
//#include "kvorm/pw_orm_humangemequipslotstate.h"
//#include "kvorm/pw_orm_humangift.h"
//#include "kvorm/pw_orm_humanguide.h"
//#include "kvorm/pw_orm_humanguildquests.h"
//#include "kvorm/pw_orm_humanguildshopitems.h"
//#include "kvorm/pw_orm_humanhelltrial.h"
//#include "kvorm/pw_orm_humanhero.h"
#include "kvorm/pw_orm_humanherocollect.h"
//#include "kvorm/pw_orm_humanherotactical.h"
//#include "kvorm/pw_orm_humanholyequip.h"
//#include "kvorm/pw_orm_humanhotactivity.h"
//#include "kvorm/pw_orm_humanintensify.h"
//#include "kvorm/pw_orm_humanitemexchange.h"
//#include "kvorm/pw_orm_humanlansquenet.h"
//#include "kvorm/pw_orm_humanlevelgift.h"
//#include "kvorm/pw_orm_humanlottery.h"
//#include "kvorm/pw_orm_humanlotteryprize.h"
//#include "kvorm/pw_orm_humanmdlongyu.h"
//#include "kvorm/pw_orm_humanmdwinter.h"
//#include "kvorm/pw_orm_humanmagiccircle.h"
//#include "kvorm/pw_orm_humanmall.h"
//#include "kvorm/pw_orm_humanmeditation.h"
//#include "kvorm/pw_orm_humanmeridian.h"
//#include "kvorm/pw_orm_humanmilitary.h"
//#include "kvorm/pw_orm_humanmisc.h"
//#include "kvorm/pw_orm_humanmonstermanual.h"
//#include "kvorm/pw_orm_humanmultiplayerdungeon.h"
//#include "kvorm/pw_orm_humanofflinereward.h"
//#include "kvorm/pw_orm_humanonlinereward.h"
//#include "kvorm/pw_orm_humanopenauction.h"
//#include "kvorm/pw_orm_humanownedaura.h"
//#include "kvorm/pw_orm_humanownedskill.h"
//#include "kvorm/pw_orm_humanpet.h"
//#include "kvorm/pw_orm_humanpill.h"
//#include "kvorm/pw_orm_humanprayerstar.h"
//#include "kvorm/pw_orm_humanproducecoin.h"
//#include "kvorm/pw_orm_humanpropsfund.h"
//#include "kvorm/pw_orm_humanpropsfundex.h"
//#include "kvorm/pw_orm_humanpseudorandom.h"
//#include "kvorm/pw_orm_humanrandshop.h"
//#include "kvorm/pw_orm_humanrandomquests.h"
//#include "kvorm/pw_orm_humanrepeatablequests.h"
//#include "kvorm/pw_orm_humanride.h"
//#include "kvorm/pw_orm_humanrolecreatedbonus.h"
//#include "kvorm/pw_orm_humanruncar.h"
//#include "kvorm/pw_orm_humanshadow.h"
//#include "kvorm/pw_orm_humansingleboss.h"
//#include "kvorm/pw_orm_humanskillcooldown.h"
//#include "kvorm/pw_orm_humansweep.h"
//#include "kvorm/pw_orm_humanteleporter.h"
//#include "kvorm/pw_orm_humantencentaward.h"
//#include "kvorm/pw_orm_humantimers.h"
//#include "kvorm/pw_orm_humantitle.h"
//#include "kvorm/pw_orm_humanunderwayquests.h"
//#include "kvorm/pw_orm_humanvip.h"
//#include "kvorm/pw_orm_humanwarlord.h"
//#include "kvorm/pw_orm_humanyzsl.h"
//#include "kvorm/pw_orm_hero.h"
#include "kvorm/pw_orm_herocard.h"
#include "kvorm/pw_orm_heronew.h"
//#include "kvorm/pw_orm_holyweapon.h"
//#include "kvorm/pw_orm_humanherospirit.h"
//#include "kvorm/pw_orm_humanitems.h"
//#include "kvorm/pw_orm_humanloaditemequipposupgrade.h"
//#include "kvorm/pw_orm_humanloaditemwash.h"
//#include "kvorm/pw_orm_humanloaditems.h"
//#include "kvorm/pw_orm_humannull.h"
//#include "kvorm/pw_orm_magicweapon.h"
//#include "kvorm/pw_orm_newweapon.h"

namespace orm
{

	void HumanCollection::load(std::string& compressedBuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(compressedBuf.c_str(),compressedBuf.length(),&tmpbuf);
		this->load(tmpbuf.c_str(),tmpbuf.length());
	}

	void HumanCollection::load(const char* __buf,size_t __len)
	{
		mongo::BSONObj __obj(__buf);
		pwassert(__obj.objsize() == __len);

		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			mongo::BSONObj __tmpobj = __be.Obj();
			int64 hash = pwutils::bkdr_hash_and_sum(__be.fieldName());
			switch(hash)
			{
			case 2307225568677: // Human
				{
					mutable_human()->from_bson(__tmpobj);
				}
				break;
			//case 6817215997851: // Human7DayQuests
			//	{
			//		mutable_human7dayquests()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7294635250530: // HumanAchievement
			//	{
			//		mutable_humanachievement()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7753213225917: // HumanActiviteCode
			//	{
			//		mutable_humanactivitecode()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 5550465953270: // HumanAcution
			//	{
			//		mutable_humanacution()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 5482183938796: // HumanAlchemy
			//	{
			//		mutable_humanalchemy()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4535938576142: // HumanArena
			//	{
			//		mutable_humanarena()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4209432091346: // HumanAttr
			//	{
			//		mutable_humanattr()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4463180361833: // HumanBabel
			//	{
			//		mutable_humanbabel()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 5038619273357: // HumanBattle
			//	{
			//		mutable_humanbattle()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4089177177040: // HumanCash
			//	{
			//		mutable_humancash()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6305303040658: // HumanChallenge
			//	{
			//		mutable_humanchallenge()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 8161702520078: // HumanChallengeLive
			//	{
			//		mutable_humanchallengelive()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 8651286037690: // HumanChallengeOther
			//	{
			//		mutable_humanchallengeother()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4605224572484: // HumanChest
			//	{
			//		mutable_humanchest()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 8342910473804: // HumanClientSetting
			//	{
			//		mutable_humanclientsetting()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 8861380313191: // HumanCommonActivity
			//	{
			//		mutable_humancommonactivity()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 8827823167275: // HumanCommonCooldown
			//	{
			//		mutable_humancommoncooldown()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 9325717003999: // HumanCompletedQuests
			//	{
			//		mutable_humancompletedquests()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6014039864640: // HumanContacts
			//	{
			//		mutable_humancontacts()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6954916452459: // HumanDailyBonus
			//	{
			//		mutable_humandailybonus()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 8165472271399: // HumanDailyRecharge
			//	{
			//		mutable_humandailyrecharge()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6331513629056: // HumanDarkarena
			//	{
			//		mutable_humandarkarena()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6954480629827: // HumanDragonHunt
			//	{
			//		mutable_humandragonhunt()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 3729706530618: // HumanDts
			//	{
			//		mutable_humandts()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 8282740382098: // HumanDungeonRecord
			//	{
			//		mutable_humandungeonrecord()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7379655636988: // HumanEquipRefine
			//	{
			//		mutable_humanequiprefine()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 5602472125714: // HumanExplore
			//	{
			//		mutable_humanexplore()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 9776125973484: // HumanFestivalActivity
			//	{
			//		mutable_humanfestivalactivity()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4136428698857: // HumanFish
			//	{
			//		mutable_humanfish()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4067709271245: // HumanFlag
			//	{
			//		mutable_humanflag()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4127838866703: // HumanFood
			//	{
			//		mutable_humanfood()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6495544554540: // HumanFormation
			//	{
			//		mutable_humanformation()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6044012696377: // HumanFunction
			//	{
			//		mutable_humanfunction()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4063416518368: // HumanGJFB
			//	{
			//		mutable_humangjfb()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 10279617906557: // HumanGemEquipSlotState
			//	{
			//		mutable_humangemequipslotstate()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4136430945257: // HumanGift
			//	{
			//		mutable_humangift()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4565629674703: // HumanGuide
			//	{
			//		mutable_humanguide()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7504129852607: // HumanGuildQuests
			//	{
			//		mutable_humanguildquests()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 8840501326944: // HumanGuildShopItems
			//	{
			//		mutable_humanguildshopitems()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6435913413144: // HumanHellTrial
			//	{
			//		mutable_humanhelltrial()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4153612995455: // HumanHero
			//	{
			//		mutable_humanhero()->from_bson(__tmpobj);
			//	}
			//	break;
			case 7341599328119: // HumanHeroCollect
				{
					mutable_humanherocollect()->from_bson(__tmpobj);
				}
				break;
			//case 7748176823646: // HumanHeroTactical
			//	{
			//		mutable_humanherotactical()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6568659235723: // HumanHolyEquip
			//	{
			//		mutable_humanholyequip()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7494728700723: // HumanHotActivity
			//	{
			//		mutable_humanhotactivity()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6537506525456: // HumanIntensify
			//	{
			//		mutable_humanintensify()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7744327912987: // HumanItemExchange
			//	{
			//		mutable_humanitemexchange()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6979958489815: // HumanLansquenet
			//	{
			//		mutable_humanlansquenet()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6440287684951: // HumanLevelGift
			//	{
			//		mutable_humanlevelgift()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 5687843137740: // HumanLottery
			//	{
			//		mutable_humanlottery()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 8065966122910: // HumanLotteryPrize
			//	{
			//		mutable_humanlotteryprize()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6083182877812: // HumanMDLongYu
			//	{
			//		mutable_humanmdlongyu()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6061261369781: // HumanMDWinter
			//	{
			//		mutable_humanmdwinter()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7199137469392: // HumanMagicCircle
			//	{
			//		mutable_humanmagiccircle()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4119264428109: // HumanMall
			//	{
			//		mutable_humanmall()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6902995372507: // HumanMeditation
			//	{
			//		mutable_humanmeditation()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 5918617495758: // HumanMeridian
			//	{
			//		mutable_humanmeridian()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6066522512806: // HumanMilitary
			//	{
			//		mutable_humanmilitary()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4145034370081: // HumanMisc
			//	{
			//		mutable_humanmisc()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 8381216810723: // HumanMonsterManual
			//	{
			//		mutable_humanmonstermanual()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 10725155600677: // HumanMultiplayerDungeon
			//	{
			//		mutable_humanmultiplayerdungeon()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 8252593781717: // HumanOfflineReward
			//	{
			//		mutable_humanofflinereward()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7847586046407: // HumanOnlineReward
			//	{
			//		mutable_humanonlinereward()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7414807717984: // HumanOpenAuction
			//	{
			//		mutable_humanopenauction()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6457426535051: // HumanOwnedAura
			//	{
			//		mutable_humanownedaura()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6964275241345: // HumanOwnedSkill
			//	{
			//		mutable_humanownedskill()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 3721116799994: // HumanPet
			//	{
			//		mutable_humanpet()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4166515949926: // HumanPill
			//	{
			//		mutable_humanpill()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7036473209062: // HumanPrayerStar
			//	{
			//		mutable_humanprayerstar()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7371567705092: // HumanProduceCoin
			//	{
			//		mutable_humanproducecoin()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6572575879804: // HumanPropsFund
			//	{
			//		mutable_humanpropsfund()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7520754806403: // HumanPropsFundEx
			//	{
			//		mutable_humanpropsfundex()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7878195431254: // HumanPseudoRandom
			//	{
			//		mutable_humanpseudorandom()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6014153182328: // HumanRandShop
			//	{
			//		mutable_humanrandshop()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7967942781573: // HumanRandomQuests
			//	{
			//		mutable_humanrandomquests()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 9704145505291: // HumanRepeatableQuests
			//	{
			//		mutable_humanrepeatablequests()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4110685870205: // HumanRide
			//	{
			//		mutable_humanride()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 9664320054250: // HumanRoleCreatedBonus
			//	{
			//		mutable_humanrolecreatedbonus()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 5103421576002: // HumanRunCar
			//	{
			//		mutable_humanruncar()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 5082308785649: // HumanShadow
			//	{
			//		mutable_humanshadow()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 6950299635322: // HumanSingleBoss
			//	{
			//		mutable_humansingleboss()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 8370966760275: // HumanSkillCooldown
			//	{
			//		mutable_humanskillcooldown()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4661509898299: // HumanSweep
			//	{
			//		mutable_humansweep()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7007059136569: // HumanTeleporter
			//	{
			//		mutable_humanteleporter()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 7804204147485: // HumanTencentAward
			//	{
			//		mutable_humantencentaward()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 5142684606343: // HumanTimers
			//	{
			//		mutable_humantimers()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4653183248675: // HumanTitle
			//	{
			//		mutable_humantitle()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 8990784387493: // HumanUnderwayQuests
			//	{
			//		mutable_humanunderwayquests()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 3746886707256: // HumanVip
			//	{
			//		mutable_humanvip()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 5584198041504: // HumanWarlord
			//	{
			//		mutable_humanwarlord()->from_bson(__tmpobj);
			//	}
			//	break;
			//case 4308270396167: // HumanYZSL
			//	{
			//		mutable_humanyzsl()->from_bson(__tmpobj);
			//	}
			//	break;
			case 1847071487050: // Hero
				{
					load_hero(__tmpobj);
				}
				break;
			case 3609761074046: // HeroCard
				{
					load_herocard(__tmpobj);
				}
				break;
			case 3264239693010: // HeroNew
				{
					load_heronew(__tmpobj);
				}
				break;
			case 4699122853004: // HolyWeapon
				{
					load_holyweapon(__tmpobj);
				}
				break;
			case 7019678904452: // HumanHeroSpirit
				{
					load_humanherospirit(__tmpobj);
				}
				break;
			case 4652115704923: // HumanItems
				{
					load_humanitems(__tmpobj);
				}
				break;
			case 12946561904138: // HumanLoadItemEquipPosUpgrade
				{
					load_humanloaditemequipposupgrade(__tmpobj);
				}
				break;
			case 7813144243025: // HumanLoadItemWash
				{
					load_humanloaditemwash(__tmpobj);
				}
				break;
			case 6438826113761: // HumanLoadItems
				{
					load_humanloaditems(__tmpobj);
				}
				break;
			case 4209461332636: // HumanNull
				{
					load_humannull(__tmpobj);
				}
				break;
			case 4996676248061: // MagicWeapon
				{
					load_magicweapon(__tmpobj);
				}
				break;
			case 4210210641588: // NewWeapon
				{
					load_newweapon(__tmpobj);
				}
				break;
			default:
				{
					pwasserte(false && "invalid metahash");
				}
				break;
			}
		}
	}

	void HumanCollection::save(std::string& compressedBuf,size_t builderInitSize)
	{
		mongo::BSONObjBuilder __builder(builderInitSize);
		save(__builder);
		mongo::BSONObj __tmpobj = __builder.obj();
		snappy::Compress(__tmpobj.objdata(),__tmpobj.objsize(),&compressedBuf);
	}

	void HumanCollection::save(mongo::BSONObjBuilder& __builder)
	{
		if(m_pHuman != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHuman->to_bson(__tmpobj);
			__builder.append(Human::meta(),__tmpobj);
		}

		/*if(m_pHuman7DayQuests != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHuman7DayQuests->to_bson(__tmpobj);
			__builder.append(Human7DayQuests::meta(),__tmpobj);
		}

		if(m_pHumanAchievement != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanAchievement->to_bson(__tmpobj);
			__builder.append(HumanAchievement::meta(),__tmpobj);
		}

		if(m_pHumanActiviteCode != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanActiviteCode->to_bson(__tmpobj);
			__builder.append(HumanActiviteCode::meta(),__tmpobj);
		}

		if(m_pHumanAcution != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanAcution->to_bson(__tmpobj);
			__builder.append(HumanAcution::meta(),__tmpobj);
		}

		if(m_pHumanAlchemy != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanAlchemy->to_bson(__tmpobj);
			__builder.append(HumanAlchemy::meta(),__tmpobj);
		}

		if(m_pHumanArena != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanArena->to_bson(__tmpobj);
			__builder.append(HumanArena::meta(),__tmpobj);
		}

		if(m_pHumanAttr != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanAttr->to_bson(__tmpobj);
			__builder.append(HumanAttr::meta(),__tmpobj);
		}

		if(m_pHumanBabel != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanBabel->to_bson(__tmpobj);
			__builder.append(HumanBabel::meta(),__tmpobj);
		}

		if(m_pHumanBattle != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanBattle->to_bson(__tmpobj);
			__builder.append(HumanBattle::meta(),__tmpobj);
		}

		if(m_pHumanCash != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanCash->to_bson(__tmpobj);
			__builder.append(HumanCash::meta(),__tmpobj);
		}

		if(m_pHumanChallenge != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanChallenge->to_bson(__tmpobj);
			__builder.append(HumanChallenge::meta(),__tmpobj);
		}

		if(m_pHumanChallengeLive != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanChallengeLive->to_bson(__tmpobj);
			__builder.append(HumanChallengeLive::meta(),__tmpobj);
		}

		if(m_pHumanChallengeOther != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanChallengeOther->to_bson(__tmpobj);
			__builder.append(HumanChallengeOther::meta(),__tmpobj);
		}

		if(m_pHumanChest != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanChest->to_bson(__tmpobj);
			__builder.append(HumanChest::meta(),__tmpobj);
		}

		if(m_pHumanClientSetting != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanClientSetting->to_bson(__tmpobj);
			__builder.append(HumanClientSetting::meta(),__tmpobj);
		}

		if(m_pHumanCommonActivity != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanCommonActivity->to_bson(__tmpobj);
			__builder.append(HumanCommonActivity::meta(),__tmpobj);
		}

		if(m_pHumanCommonCooldown != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanCommonCooldown->to_bson(__tmpobj);
			__builder.append(HumanCommonCooldown::meta(),__tmpobj);
		}

		if(m_pHumanCompletedQuests != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanCompletedQuests->to_bson(__tmpobj);
			__builder.append(HumanCompletedQuests::meta(),__tmpobj);
		}

		if(m_pHumanContacts != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanContacts->to_bson(__tmpobj);
			__builder.append(HumanContacts::meta(),__tmpobj);
		}

		if(m_pHumanDailyBonus != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanDailyBonus->to_bson(__tmpobj);
			__builder.append(HumanDailyBonus::meta(),__tmpobj);
		}

		if(m_pHumanDailyRecharge != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanDailyRecharge->to_bson(__tmpobj);
			__builder.append(HumanDailyRecharge::meta(),__tmpobj);
		}

		if(m_pHumanDarkarena != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanDarkarena->to_bson(__tmpobj);
			__builder.append(HumanDarkarena::meta(),__tmpobj);
		}

		if(m_pHumanDragonHunt != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanDragonHunt->to_bson(__tmpobj);
			__builder.append(HumanDragonHunt::meta(),__tmpobj);
		}

		if(m_pHumanDts != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanDts->to_bson(__tmpobj);
			__builder.append(HumanDts::meta(),__tmpobj);
		}

		if(m_pHumanDungeonRecord != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanDungeonRecord->to_bson(__tmpobj);
			__builder.append(HumanDungeonRecord::meta(),__tmpobj);
		}

		if(m_pHumanEquipRefine != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanEquipRefine->to_bson(__tmpobj);
			__builder.append(HumanEquipRefine::meta(),__tmpobj);
		}

		if(m_pHumanExplore != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanExplore->to_bson(__tmpobj);
			__builder.append(HumanExplore::meta(),__tmpobj);
		}

		if(m_pHumanFestivalActivity != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanFestivalActivity->to_bson(__tmpobj);
			__builder.append(HumanFestivalActivity::meta(),__tmpobj);
		}

		if(m_pHumanFish != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanFish->to_bson(__tmpobj);
			__builder.append(HumanFish::meta(),__tmpobj);
		}

		if(m_pHumanFlag != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanFlag->to_bson(__tmpobj);
			__builder.append(HumanFlag::meta(),__tmpobj);
		}

		if(m_pHumanFood != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanFood->to_bson(__tmpobj);
			__builder.append(HumanFood::meta(),__tmpobj);
		}

		if(m_pHumanFormation != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanFormation->to_bson(__tmpobj);
			__builder.append(HumanFormation::meta(),__tmpobj);
		}

		if(m_pHumanFunction != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanFunction->to_bson(__tmpobj);
			__builder.append(HumanFunction::meta(),__tmpobj);
		}

		if(m_pHumanGJFB != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanGJFB->to_bson(__tmpobj);
			__builder.append(HumanGJFB::meta(),__tmpobj);
		}

		if(m_pHumanGemEquipSlotState != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanGemEquipSlotState->to_bson(__tmpobj);
			__builder.append(HumanGemEquipSlotState::meta(),__tmpobj);
		}

		if(m_pHumanGift != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanGift->to_bson(__tmpobj);
			__builder.append(HumanGift::meta(),__tmpobj);
		}

		if(m_pHumanGuide != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanGuide->to_bson(__tmpobj);
			__builder.append(HumanGuide::meta(),__tmpobj);
		}

		if(m_pHumanGuildQuests != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanGuildQuests->to_bson(__tmpobj);
			__builder.append(HumanGuildQuests::meta(),__tmpobj);
		}

		if(m_pHumanGuildShopItems != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanGuildShopItems->to_bson(__tmpobj);
			__builder.append(HumanGuildShopItems::meta(),__tmpobj);
		}

		if(m_pHumanHellTrial != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanHellTrial->to_bson(__tmpobj);
			__builder.append(HumanHellTrial::meta(),__tmpobj);
		}

		if(m_pHumanHero != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanHero->to_bson(__tmpobj);
			__builder.append(HumanHero::meta(),__tmpobj);
		}
*/
		if(m_pHumanHeroCollect != NULL)
		{
			mongo::BSONObj __tmpobj;
			m_pHumanHeroCollect->to_bson(__tmpobj);
			__builder.append(HumanHeroCollect::meta(),__tmpobj);
		}

		//if(m_pHumanHeroTactical != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanHeroTactical->to_bson(__tmpobj);
		//	__builder.append(HumanHeroTactical::meta(),__tmpobj);
		//}

		//if(m_pHumanHolyEquip != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanHolyEquip->to_bson(__tmpobj);
		//	__builder.append(HumanHolyEquip::meta(),__tmpobj);
		//}

		//if(m_pHumanHotActivity != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanHotActivity->to_bson(__tmpobj);
		//	__builder.append(HumanHotActivity::meta(),__tmpobj);
		//}

		//if(m_pHumanIntensify != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanIntensify->to_bson(__tmpobj);
		//	__builder.append(HumanIntensify::meta(),__tmpobj);
		//}

		//if(m_pHumanItemExchange != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanItemExchange->to_bson(__tmpobj);
		//	__builder.append(HumanItemExchange::meta(),__tmpobj);
		//}

		//if(m_pHumanLansquenet != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanLansquenet->to_bson(__tmpobj);
		//	__builder.append(HumanLansquenet::meta(),__tmpobj);
		//}

		//if(m_pHumanLevelGift != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanLevelGift->to_bson(__tmpobj);
		//	__builder.append(HumanLevelGift::meta(),__tmpobj);
		//}

		//if(m_pHumanLottery != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanLottery->to_bson(__tmpobj);
		//	__builder.append(HumanLottery::meta(),__tmpobj);
		//}

		//if(m_pHumanLotteryPrize != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanLotteryPrize->to_bson(__tmpobj);
		//	__builder.append(HumanLotteryPrize::meta(),__tmpobj);
		//}

		//if(m_pHumanMDLongYu != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanMDLongYu->to_bson(__tmpobj);
		//	__builder.append(HumanMDLongYu::meta(),__tmpobj);
		//}

		//if(m_pHumanMDWinter != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanMDWinter->to_bson(__tmpobj);
		//	__builder.append(HumanMDWinter::meta(),__tmpobj);
		//}

		//if(m_pHumanMagicCircle != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanMagicCircle->to_bson(__tmpobj);
		//	__builder.append(HumanMagicCircle::meta(),__tmpobj);
		//}

		//if(m_pHumanMall != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanMall->to_bson(__tmpobj);
		//	__builder.append(HumanMall::meta(),__tmpobj);
		//}

		//if(m_pHumanMeditation != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanMeditation->to_bson(__tmpobj);
		//	__builder.append(HumanMeditation::meta(),__tmpobj);
		//}

		//if(m_pHumanMeridian != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanMeridian->to_bson(__tmpobj);
		//	__builder.append(HumanMeridian::meta(),__tmpobj);
		//}

		//if(m_pHumanMilitary != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanMilitary->to_bson(__tmpobj);
		//	__builder.append(HumanMilitary::meta(),__tmpobj);
		//}

		//if(m_pHumanMisc != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanMisc->to_bson(__tmpobj);
		//	__builder.append(HumanMisc::meta(),__tmpobj);
		//}

		//if(m_pHumanMonsterManual != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanMonsterManual->to_bson(__tmpobj);
		//	__builder.append(HumanMonsterManual::meta(),__tmpobj);
		//}

		//if(m_pHumanMultiplayerDungeon != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanMultiplayerDungeon->to_bson(__tmpobj);
		//	__builder.append(HumanMultiplayerDungeon::meta(),__tmpobj);
		//}

		//if(m_pHumanOfflineReward != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanOfflineReward->to_bson(__tmpobj);
		//	__builder.append(HumanOfflineReward::meta(),__tmpobj);
		//}

		//if(m_pHumanOnlineReward != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanOnlineReward->to_bson(__tmpobj);
		//	__builder.append(HumanOnlineReward::meta(),__tmpobj);
		//}

		//if(m_pHumanOpenAuction != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanOpenAuction->to_bson(__tmpobj);
		//	__builder.append(HumanOpenAuction::meta(),__tmpobj);
		//}

		//if(m_pHumanOwnedAura != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanOwnedAura->to_bson(__tmpobj);
		//	__builder.append(HumanOwnedAura::meta(),__tmpobj);
		//}

		//if(m_pHumanOwnedSkill != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanOwnedSkill->to_bson(__tmpobj);
		//	__builder.append(HumanOwnedSkill::meta(),__tmpobj);
		//}

		//if(m_pHumanPet != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanPet->to_bson(__tmpobj);
		//	__builder.append(HumanPet::meta(),__tmpobj);
		//}

		//if(m_pHumanPill != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanPill->to_bson(__tmpobj);
		//	__builder.append(HumanPill::meta(),__tmpobj);
		//}

		//if(m_pHumanPrayerStar != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanPrayerStar->to_bson(__tmpobj);
		//	__builder.append(HumanPrayerStar::meta(),__tmpobj);
		//}

		//if(m_pHumanProduceCoin != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanProduceCoin->to_bson(__tmpobj);
		//	__builder.append(HumanProduceCoin::meta(),__tmpobj);
		//}

		//if(m_pHumanPropsFund != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanPropsFund->to_bson(__tmpobj);
		//	__builder.append(HumanPropsFund::meta(),__tmpobj);
		//}

		//if(m_pHumanPropsFundEx != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanPropsFundEx->to_bson(__tmpobj);
		//	__builder.append(HumanPropsFundEx::meta(),__tmpobj);
		//}

		//if(m_pHumanPseudoRandom != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanPseudoRandom->to_bson(__tmpobj);
		//	__builder.append(HumanPseudoRandom::meta(),__tmpobj);
		//}

		//if(m_pHumanRandShop != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanRandShop->to_bson(__tmpobj);
		//	__builder.append(HumanRandShop::meta(),__tmpobj);
		//}

		//if(m_pHumanRandomQuests != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanRandomQuests->to_bson(__tmpobj);
		//	__builder.append(HumanRandomQuests::meta(),__tmpobj);
		//}

		//if(m_pHumanRepeatableQuests != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanRepeatableQuests->to_bson(__tmpobj);
		//	__builder.append(HumanRepeatableQuests::meta(),__tmpobj);
		//}

		//if(m_pHumanRide != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanRide->to_bson(__tmpobj);
		//	__builder.append(HumanRide::meta(),__tmpobj);
		//}

		//if(m_pHumanRoleCreatedBonus != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanRoleCreatedBonus->to_bson(__tmpobj);
		//	__builder.append(HumanRoleCreatedBonus::meta(),__tmpobj);
		//}

		//if(m_pHumanRunCar != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanRunCar->to_bson(__tmpobj);
		//	__builder.append(HumanRunCar::meta(),__tmpobj);
		//}

		//if(m_pHumanShadow != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanShadow->to_bson(__tmpobj);
		//	__builder.append(HumanShadow::meta(),__tmpobj);
		//}

		//if(m_pHumanSingleBoss != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanSingleBoss->to_bson(__tmpobj);
		//	__builder.append(HumanSingleBoss::meta(),__tmpobj);
		//}

		//if(m_pHumanSkillCooldown != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanSkillCooldown->to_bson(__tmpobj);
		//	__builder.append(HumanSkillCooldown::meta(),__tmpobj);
		//}

		//if(m_pHumanSweep != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanSweep->to_bson(__tmpobj);
		//	__builder.append(HumanSweep::meta(),__tmpobj);
		//}

		//if(m_pHumanTeleporter != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanTeleporter->to_bson(__tmpobj);
		//	__builder.append(HumanTeleporter::meta(),__tmpobj);
		//}

		//if(m_pHumanTencentAward != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanTencentAward->to_bson(__tmpobj);
		//	__builder.append(HumanTencentAward::meta(),__tmpobj);
		//}

		//if(m_pHumanTimers != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanTimers->to_bson(__tmpobj);
		//	__builder.append(HumanTimers::meta(),__tmpobj);
		//}

		//if(m_pHumanTitle != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanTitle->to_bson(__tmpobj);
		//	__builder.append(HumanTitle::meta(),__tmpobj);
		//}

		//if(m_pHumanUnderwayQuests != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanUnderwayQuests->to_bson(__tmpobj);
		//	__builder.append(HumanUnderwayQuests::meta(),__tmpobj);
		//}

		//if(m_pHumanVip != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanVip->to_bson(__tmpobj);
		//	__builder.append(HumanVip::meta(),__tmpobj);
		//}

		//if(m_pHumanWarlord != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanWarlord->to_bson(__tmpobj);
		//	__builder.append(HumanWarlord::meta(),__tmpobj);
		//}

		//if(m_pHumanYZSL != NULL)
		//{
		//	mongo::BSONObj __tmpobj;
		//	m_pHumanYZSL->to_bson(__tmpobj);
		//	__builder.append(HumanYZSL::meta(),__tmpobj);
		//}

		//{
		//	mongo::BSONArrayBuilder __tmpbuilder;
		//	this->save_hero(__tmpbuilder);
		//	__builder.append(Hero::meta(),__tmpbuilder.obj());
		//}

		{
			mongo::BSONArrayBuilder __tmpbuilder;
			this->save_herocard(__tmpbuilder);
			__builder.append(HeroCard::meta(),__tmpbuilder.obj());
		}

		{
			mongo::BSONArrayBuilder __tmpbuilder;
			this->save_heronew(__tmpbuilder);
			__builder.append(HeroNew::meta(),__tmpbuilder.obj());
		}

		{
		/*	mongo::BSONArrayBuilder __tmpbuilder;
			this->save_holyweapon(__tmpbuilder);
			__builder.append(HolyWeapon::meta(),__tmpbuilder.obj());
		}

		{
			mongo::BSONArrayBuilder __tmpbuilder;
			this->save_humanherospirit(__tmpbuilder);
			__builder.append(HumanHeroSpirit::meta(),__tmpbuilder.obj());
		}

		{
			mongo::BSONArrayBuilder __tmpbuilder;
			this->save_humanitems(__tmpbuilder);
			__builder.append(HumanItems::meta(),__tmpbuilder.obj());
		}

		{
			mongo::BSONArrayBuilder __tmpbuilder;
			this->save_humanloaditemequipposupgrade(__tmpbuilder);
			__builder.append(HumanLoadItemEquipPosUpgrade::meta(),__tmpbuilder.obj());
		}

		{
			mongo::BSONArrayBuilder __tmpbuilder;
			this->save_humanloaditemwash(__tmpbuilder);
			__builder.append(HumanLoadItemWash::meta(),__tmpbuilder.obj());
		}

		{
			mongo::BSONArrayBuilder __tmpbuilder;
			this->save_humanloaditems(__tmpbuilder);
			__builder.append(HumanLoadItems::meta(),__tmpbuilder.obj());
		}

		{
			mongo::BSONArrayBuilder __tmpbuilder;
			this->save_humannull(__tmpbuilder);
			__builder.append(HumanNull::meta(),__tmpbuilder.obj());
		}

		{
			mongo::BSONArrayBuilder __tmpbuilder;
			this->save_magicweapon(__tmpbuilder);
			__builder.append(MagicWeapon::meta(),__tmpbuilder.obj());
		}

		{
			mongo::BSONArrayBuilder __tmpbuilder;
			this->save_newweapon(__tmpbuilder);
			__builder.append(NewWeapon::meta(),__tmpbuilder.obj());
		}*/

	}

	HumanCollection::HumanCollection()
	{
		m_pHuman = NULL;
		m_pHuman7DayQuests = NULL;
		m_pHumanAchievement = NULL;
		m_pHumanActiviteCode = NULL;
		m_pHumanAcution = NULL;
		m_pHumanAlchemy = NULL;
		m_pHumanArena = NULL;
		m_pHumanAttr = NULL;
		m_pHumanBabel = NULL;
		m_pHumanBattle = NULL;
		m_pHumanCash = NULL;
		m_pHumanChallenge = NULL;
		m_pHumanChallengeLive = NULL;
		m_pHumanChallengeOther = NULL;
		m_pHumanChest = NULL;
		m_pHumanClientSetting = NULL;
		m_pHumanCommonActivity = NULL;
		m_pHumanCommonCooldown = NULL;
		m_pHumanCompletedQuests = NULL;
		m_pHumanContacts = NULL;
		m_pHumanDailyBonus = NULL;
		m_pHumanDailyRecharge = NULL;
		m_pHumanDarkarena = NULL;
		m_pHumanDragonHunt = NULL;
		m_pHumanDts = NULL;
		m_pHumanDungeonRecord = NULL;
		m_pHumanEquipRefine = NULL;
		m_pHumanExplore = NULL;
		m_pHumanFestivalActivity = NULL;
		m_pHumanFish = NULL;
		m_pHumanFlag = NULL;
		m_pHumanFood = NULL;
		m_pHumanFormation = NULL;
		m_pHumanFunction = NULL;
		m_pHumanGJFB = NULL;
		m_pHumanGemEquipSlotState = NULL;
		m_pHumanGift = NULL;
		m_pHumanGuide = NULL;
		m_pHumanGuildQuests = NULL;
		m_pHumanGuildShopItems = NULL;
		m_pHumanHellTrial = NULL;
		m_pHumanHero = NULL;
		m_pHumanHeroCollect = NULL;
		m_pHumanHeroTactical = NULL;
		m_pHumanHolyEquip = NULL;
		m_pHumanHotActivity = NULL;
		m_pHumanIntensify = NULL;
		m_pHumanItemExchange = NULL;
		m_pHumanLansquenet = NULL;
		m_pHumanLevelGift = NULL;
		m_pHumanLottery = NULL;
		m_pHumanLotteryPrize = NULL;
		m_pHumanMDLongYu = NULL;
		m_pHumanMDWinter = NULL;
		m_pHumanMagicCircle = NULL;
		m_pHumanMall = NULL;
		m_pHumanMeditation = NULL;
		m_pHumanMeridian = NULL;
		m_pHumanMilitary = NULL;
		m_pHumanMisc = NULL;
		m_pHumanMonsterManual = NULL;
		m_pHumanMultiplayerDungeon = NULL;
		m_pHumanOfflineReward = NULL;
		m_pHumanOnlineReward = NULL;
		m_pHumanOpenAuction = NULL;
		m_pHumanOwnedAura = NULL;
		m_pHumanOwnedSkill = NULL;
		m_pHumanPet = NULL;
		m_pHumanPill = NULL;
		m_pHumanPrayerStar = NULL;
		m_pHumanProduceCoin = NULL;
		m_pHumanPropsFund = NULL;
		m_pHumanPropsFundEx = NULL;
		m_pHumanPseudoRandom = NULL;
		m_pHumanRandShop = NULL;
		m_pHumanRandomQuests = NULL;
		m_pHumanRepeatableQuests = NULL;
		m_pHumanRide = NULL;
		m_pHumanRoleCreatedBonus = NULL;
		m_pHumanRunCar = NULL;
		m_pHumanShadow = NULL;
		m_pHumanSingleBoss = NULL;
		m_pHumanSkillCooldown = NULL;
		m_pHumanSweep = NULL;
		m_pHumanTeleporter = NULL;
		m_pHumanTencentAward = NULL;
		m_pHumanTimers = NULL;
		m_pHumanTitle = NULL;
		m_pHumanUnderwayQuests = NULL;
		m_pHumanVip = NULL;
		m_pHumanWarlord = NULL;
		m_pHumanYZSL = NULL;
	}

	HumanCollection::~HumanCollection()
	{
		_safe_delete(m_pHuman);
		_safe_delete(m_pHuman7DayQuests);
		_safe_delete(m_pHumanAchievement);
		_safe_delete(m_pHumanActiviteCode);
		_safe_delete(m_pHumanAcution);
		_safe_delete(m_pHumanAlchemy);
		_safe_delete(m_pHumanArena);
		_safe_delete(m_pHumanAttr);
		_safe_delete(m_pHumanBabel);
		_safe_delete(m_pHumanBattle);
		_safe_delete(m_pHumanCash);
		_safe_delete(m_pHumanChallenge);
		_safe_delete(m_pHumanChallengeLive);
		_safe_delete(m_pHumanChallengeOther);
		_safe_delete(m_pHumanChest);
		_safe_delete(m_pHumanClientSetting);
		_safe_delete(m_pHumanCommonActivity);
		_safe_delete(m_pHumanCommonCooldown);
		_safe_delete(m_pHumanCompletedQuests);
		_safe_delete(m_pHumanContacts);
		_safe_delete(m_pHumanDailyBonus);
		_safe_delete(m_pHumanDailyRecharge);
		_safe_delete(m_pHumanDarkarena);
		_safe_delete(m_pHumanDragonHunt);
		_safe_delete(m_pHumanDts);
		_safe_delete(m_pHumanDungeonRecord);
		_safe_delete(m_pHumanEquipRefine);
		_safe_delete(m_pHumanExplore);
		_safe_delete(m_pHumanFestivalActivity);
		_safe_delete(m_pHumanFish);
		_safe_delete(m_pHumanFlag);
		_safe_delete(m_pHumanFood);
		_safe_delete(m_pHumanFormation);
		_safe_delete(m_pHumanFunction);
		_safe_delete(m_pHumanGJFB);
		_safe_delete(m_pHumanGemEquipSlotState);
		_safe_delete(m_pHumanGift);
		_safe_delete(m_pHumanGuide);
		_safe_delete(m_pHumanGuildQuests);
		_safe_delete(m_pHumanGuildShopItems);
		_safe_delete(m_pHumanHellTrial);
		_safe_delete(m_pHumanHero);
		_safe_delete(m_pHumanHeroCollect);
		_safe_delete(m_pHumanHeroTactical);
		_safe_delete(m_pHumanHolyEquip);
		_safe_delete(m_pHumanHotActivity);
		_safe_delete(m_pHumanIntensify);
		_safe_delete(m_pHumanItemExchange);
		_safe_delete(m_pHumanLansquenet);
		_safe_delete(m_pHumanLevelGift);
		_safe_delete(m_pHumanLottery);
		_safe_delete(m_pHumanLotteryPrize);
		_safe_delete(m_pHumanMDLongYu);
		_safe_delete(m_pHumanMDWinter);
		_safe_delete(m_pHumanMagicCircle);
		_safe_delete(m_pHumanMall);
		_safe_delete(m_pHumanMeditation);
		_safe_delete(m_pHumanMeridian);
		_safe_delete(m_pHumanMilitary);
		_safe_delete(m_pHumanMisc);
		_safe_delete(m_pHumanMonsterManual);
		_safe_delete(m_pHumanMultiplayerDungeon);
		_safe_delete(m_pHumanOfflineReward);
		_safe_delete(m_pHumanOnlineReward);
		_safe_delete(m_pHumanOpenAuction);
		_safe_delete(m_pHumanOwnedAura);
		_safe_delete(m_pHumanOwnedSkill);
		_safe_delete(m_pHumanPet);
		_safe_delete(m_pHumanPill);
		_safe_delete(m_pHumanPrayerStar);
		_safe_delete(m_pHumanProduceCoin);
		_safe_delete(m_pHumanPropsFund);
		_safe_delete(m_pHumanPropsFundEx);
		_safe_delete(m_pHumanPseudoRandom);
		_safe_delete(m_pHumanRandShop);
		_safe_delete(m_pHumanRandomQuests);
		_safe_delete(m_pHumanRepeatableQuests);
		_safe_delete(m_pHumanRide);
		_safe_delete(m_pHumanRoleCreatedBonus);
		_safe_delete(m_pHumanRunCar);
		_safe_delete(m_pHumanShadow);
		_safe_delete(m_pHumanSingleBoss);
		_safe_delete(m_pHumanSkillCooldown);
		_safe_delete(m_pHumanSweep);
		_safe_delete(m_pHumanTeleporter);
		_safe_delete(m_pHumanTencentAward);
		_safe_delete(m_pHumanTimers);
		_safe_delete(m_pHumanTitle);
		_safe_delete(m_pHumanUnderwayQuests);
		_safe_delete(m_pHumanVip);
		_safe_delete(m_pHumanWarlord);
		_safe_delete(m_pHumanYZSL);
	}

	Human* HumanCollection::mutable_human()
	{
		if(m_pHuman == NULL)
		{
			m_pHuman = new Human();
			m_pHuman->set_masterid(m_vMasterId);
		}
		return m_pHuman;
	}

	Human7DayQuests* HumanCollection::mutable_human7dayquests()
	{
		if(m_pHuman7DayQuests == NULL)
		{
		/*	m_pHuman7DayQuests = new Human7DayQuests();
			m_pHuman7DayQuests->set_masterid(m_vMasterId);*/
		}
		return m_pHuman7DayQuests;
	}

	HumanAchievement* HumanCollection::mutable_humanachievement()
	{
		if(m_pHumanAchievement == NULL)
		{
			/*m_pHumanAchievement = new HumanAchievement();
			m_pHumanAchievement->set_masterid(m_vMasterId);*/
		}
		return m_pHumanAchievement;
	}

	HumanActiviteCode* HumanCollection::mutable_humanactivitecode()
	{
		if(m_pHumanActiviteCode == NULL)
		{
			/*m_pHumanActiviteCode = new HumanActiviteCode();
			m_pHumanActiviteCode->set_masterid(m_vMasterId);*/
		}
		return m_pHumanActiviteCode;
	}

	HumanAcution* HumanCollection::mutable_humanacution()
	{
		if(m_pHumanAcution == NULL)
		{
			/*m_pHumanAcution = new HumanAcution();
			m_pHumanAcution->set_masterid(m_vMasterId);*/
		}
		return m_pHumanAcution;
	}

	HumanAlchemy* HumanCollection::mutable_humanalchemy()
	{
		if(m_pHumanAlchemy == NULL)
		{
			/*m_pHumanAlchemy = new HumanAlchemy();
			m_pHumanAlchemy->set_masterid(m_vMasterId);*/
		}
		return m_pHumanAlchemy;
	}

	HumanArena* HumanCollection::mutable_humanarena()
	{
		if(m_pHumanArena == NULL)
		{
			/*m_pHumanArena = new HumanArena();
			m_pHumanArena->set_masterid(m_vMasterId);*/
		}
		return m_pHumanArena;
	}

	HumanAttr* HumanCollection::mutable_humanattr()
	{
		if(m_pHumanAttr == NULL)
		{
			/*m_pHumanAttr = new HumanAttr();
			m_pHumanAttr->set_masterid(m_vMasterId);*/
		}
		return m_pHumanAttr;
	}

	HumanBabel* HumanCollection::mutable_humanbabel()
	{
		if(m_pHumanBabel == NULL)
		{
			/*m_pHumanBabel = new HumanBabel();
			m_pHumanBabel->set_masterid(m_vMasterId);*/
		}
		return m_pHumanBabel;
	}

	HumanBattle* HumanCollection::mutable_humanbattle()
	{
		if(m_pHumanBattle == NULL)
		{
		/*	m_pHumanBattle = new HumanBattle();
			m_pHumanBattle->set_masterid(m_vMasterId);*/
		}
		return m_pHumanBattle;
	}

	HumanCash* HumanCollection::mutable_humancash()
	{
		if(m_pHumanCash == NULL)
		{
			/*	m_pHumanCash = new HumanCash();
				m_pHumanCash->set_masterid(m_vMasterId);*/
		}
		return m_pHumanCash;
	}

	HumanChallenge* HumanCollection::mutable_humanchallenge()
	{
		if(m_pHumanChallenge == NULL)
		{
			/*m_pHumanChallenge = new HumanChallenge();
			m_pHumanChallenge->set_masterid(m_vMasterId);*/
		}
		return m_pHumanChallenge;
	}

	HumanChallengeLive* HumanCollection::mutable_humanchallengelive()
	{
		if(m_pHumanChallengeLive == NULL)
		{
			/*m_pHumanChallengeLive = new HumanChallengeLive();
			m_pHumanChallengeLive->set_masterid(m_vMasterId);*/
		}
		return m_pHumanChallengeLive;
	}

	HumanChallengeOther* HumanCollection::mutable_humanchallengeother()
	{
		if(m_pHumanChallengeOther == NULL)
		{
			/*m_pHumanChallengeOther = new HumanChallengeOther();
			m_pHumanChallengeOther->set_masterid(m_vMasterId);*/
		}
		return m_pHumanChallengeOther;
	}

	HumanChest* HumanCollection::mutable_humanchest()
	{
		if(m_pHumanChest == NULL)
		{
			/*m_pHumanChest = new HumanChest();
			m_pHumanChest->set_masterid(m_vMasterId);*/
		}
		return m_pHumanChest;
	}

	HumanClientSetting* HumanCollection::mutable_humanclientsetting()
	{
		if(m_pHumanClientSetting == NULL)
		{
			/*m_pHumanClientSetting = new HumanClientSetting();
			m_pHumanClientSetting->set_masterid(m_vMasterId);*/
		}
		return m_pHumanClientSetting;
	}

	HumanCommonActivity* HumanCollection::mutable_humancommonactivity()
	{
		if(m_pHumanCommonActivity == NULL)
		{
		/*	m_pHumanCommonActivity = new HumanCommonActivity();
			m_pHumanCommonActivity->set_masterid(m_vMasterId);*/
		}
		return m_pHumanCommonActivity;
	}

	HumanCommonCooldown* HumanCollection::mutable_humancommoncooldown()
	{
		if(m_pHumanCommonCooldown == NULL)
		{
			/*m_pHumanCommonCooldown = new HumanCommonCooldown();
			m_pHumanCommonCooldown->set_masterid(m_vMasterId);*/
		}
		return m_pHumanCommonCooldown;
	}

	HumanCompletedQuests* HumanCollection::mutable_humancompletedquests()
	{
		if(m_pHumanCompletedQuests == NULL)
		{
			/*m_pHumanCompletedQuests = new HumanCompletedQuests();
			m_pHumanCompletedQuests->set_masterid(m_vMasterId);*/
		}
		return m_pHumanCompletedQuests;
	}

	HumanContacts* HumanCollection::mutable_humancontacts()
	{
		if(m_pHumanContacts == NULL)
		{
			/*m_pHumanContacts = new HumanContacts();
			m_pHumanContacts->set_masterid(m_vMasterId);*/
		}
		return m_pHumanContacts;
	}

	HumanDailyBonus* HumanCollection::mutable_humandailybonus()
	{
		if(m_pHumanDailyBonus == NULL)
		{
			/*m_pHumanDailyBonus = new HumanDailyBonus();
			m_pHumanDailyBonus->set_masterid(m_vMasterId);*/
		}
		return m_pHumanDailyBonus;
	}

	HumanDailyRecharge* HumanCollection::mutable_humandailyrecharge()
	{
		if(m_pHumanDailyRecharge == NULL)
		{
			/*m_pHumanDailyRecharge = new HumanDailyRecharge();
			m_pHumanDailyRecharge->set_masterid(m_vMasterId);*/
		}
		return m_pHumanDailyRecharge;
	}

	HumanDarkarena* HumanCollection::mutable_humandarkarena()
	{
		if(m_pHumanDarkarena == NULL)
		{
			/*m_pHumanDarkarena = new HumanDarkarena();
			m_pHumanDarkarena->set_masterid(m_vMasterId);*/
		}
		return m_pHumanDarkarena;
	}

	HumanDragonHunt* HumanCollection::mutable_humandragonhunt()
	{
		if(m_pHumanDragonHunt == NULL)
		{
			/*m_pHumanDragonHunt = new HumanDragonHunt();
			m_pHumanDragonHunt->set_masterid(m_vMasterId);*/
		}
		return m_pHumanDragonHunt;
	}

	HumanDts* HumanCollection::mutable_humandts()
	{
		if(m_pHumanDts == NULL)
		{
			/*m_pHumanDts = new HumanDts();
			m_pHumanDts->set_masterid(m_vMasterId);*/
		}
		return m_pHumanDts;
	}

	HumanDungeonRecord* HumanCollection::mutable_humandungeonrecord()
	{
		if(m_pHumanDungeonRecord == NULL)
		{
			/*m_pHumanDungeonRecord = new HumanDungeonRecord();
			m_pHumanDungeonRecord->set_masterid(m_vMasterId);*/
		}
		return m_pHumanDungeonRecord;
	}

	HumanEquipRefine* HumanCollection::mutable_humanequiprefine()
	{
		if(m_pHumanEquipRefine == NULL)
		{
			/*m_pHumanEquipRefine = new HumanEquipRefine();
			m_pHumanEquipRefine->set_masterid(m_vMasterId);*/
		}
		return m_pHumanEquipRefine;
	}

	HumanExplore* HumanCollection::mutable_humanexplore()
	{
		if(m_pHumanExplore == NULL)
		{
			/*m_pHumanExplore = new HumanExplore();
			m_pHumanExplore->set_masterid(m_vMasterId);*/
		}
		return m_pHumanExplore;
	}

	HumanFestivalActivity* HumanCollection::mutable_humanfestivalactivity()
	{
		if(m_pHumanFestivalActivity == NULL)
		{
			/*m_pHumanFestivalActivity = new HumanFestivalActivity();
			m_pHumanFestivalActivity->set_masterid(m_vMasterId);*/
		}
		return m_pHumanFestivalActivity;
	}

	HumanFish* HumanCollection::mutable_humanfish()
	{
		if(m_pHumanFish == NULL)
		{
			/*	m_pHumanFish = new HumanFish();
				m_pHumanFish->set_masterid(m_vMasterId);*/
		}
		return m_pHumanFish;
	}

	HumanFlag* HumanCollection::mutable_humanflag()
	{
		if(m_pHumanFlag == NULL)
		{
			/*	m_pHumanFlag = new HumanFlag();
				m_pHumanFlag->set_masterid(m_vMasterId);*/
		}
		return m_pHumanFlag;
	}

	HumanFood* HumanCollection::mutable_humanfood()
	{
		if(m_pHumanFood == NULL)
		{
			m_pHumanFood = new HumanFood();
			m_pHumanFood->set_masterid(m_vMasterId);
		}
		return m_pHumanFood;
	}

	HumanFormation* HumanCollection::mutable_humanformation()
	{
		if(m_pHumanFormation == NULL)
		{
			m_pHumanFormation = new HumanFormation();
			m_pHumanFormation->set_masterid(m_vMasterId);
		}
		return m_pHumanFormation;
	}

	HumanFunction* HumanCollection::mutable_humanfunction()
	{
		if(m_pHumanFunction == NULL)
		{
			m_pHumanFunction = new HumanFunction();
			m_pHumanFunction->set_masterid(m_vMasterId);
		}
		return m_pHumanFunction;
	}

	HumanGJFB* HumanCollection::mutable_humangjfb()
	{
		if(m_pHumanGJFB == NULL)
		{
			m_pHumanGJFB = new HumanGJFB();
			m_pHumanGJFB->set_masterid(m_vMasterId);
		}
		return m_pHumanGJFB;
	}

	HumanGemEquipSlotState* HumanCollection::mutable_humangemequipslotstate()
	{
		if(m_pHumanGemEquipSlotState == NULL)
		{
			m_pHumanGemEquipSlotState = new HumanGemEquipSlotState();
			m_pHumanGemEquipSlotState->set_masterid(m_vMasterId);
		}
		return m_pHumanGemEquipSlotState;
	}

	HumanGift* HumanCollection::mutable_humangift()
	{
		if(m_pHumanGift == NULL)
		{
			m_pHumanGift = new HumanGift();
			m_pHumanGift->set_masterid(m_vMasterId);
		}
		return m_pHumanGift;
	}

	HumanGuide* HumanCollection::mutable_humanguide()
	{
		if(m_pHumanGuide == NULL)
		{
			m_pHumanGuide = new HumanGuide();
			m_pHumanGuide->set_masterid(m_vMasterId);
		}
		return m_pHumanGuide;
	}

	HumanGuildQuests* HumanCollection::mutable_humanguildquests()
	{
		if(m_pHumanGuildQuests == NULL)
		{
			m_pHumanGuildQuests = new HumanGuildQuests();
			m_pHumanGuildQuests->set_masterid(m_vMasterId);
		}
		return m_pHumanGuildQuests;
	}

	HumanGuildShopItems* HumanCollection::mutable_humanguildshopitems()
	{
		if(m_pHumanGuildShopItems == NULL)
		{
			m_pHumanGuildShopItems = new HumanGuildShopItems();
			m_pHumanGuildShopItems->set_masterid(m_vMasterId);
		}
		return m_pHumanGuildShopItems;
	}

	HumanHellTrial* HumanCollection::mutable_humanhelltrial()
	{
		if(m_pHumanHellTrial == NULL)
		{
			m_pHumanHellTrial = new HumanHellTrial();
			m_pHumanHellTrial->set_masterid(m_vMasterId);
		}
		return m_pHumanHellTrial;
	}

	HumanHero* HumanCollection::mutable_humanhero()
	{
		if(m_pHumanHero == NULL)
		{
			m_pHumanHero = new HumanHero();
			m_pHumanHero->set_masterid(m_vMasterId);
		}
		return m_pHumanHero;
	}

	HumanHeroCollect* HumanCollection::mutable_humanherocollect()
	{
		if(m_pHumanHeroCollect == NULL)
		{
			m_pHumanHeroCollect = new HumanHeroCollect();
			m_pHumanHeroCollect->set_masterid(m_vMasterId);
		}
		return m_pHumanHeroCollect;
	}

	HumanHeroTactical* HumanCollection::mutable_humanherotactical()
	{
		if(m_pHumanHeroTactical == NULL)
		{
			m_pHumanHeroTactical = new HumanHeroTactical();
			m_pHumanHeroTactical->set_masterid(m_vMasterId);
		}
		return m_pHumanHeroTactical;
	}

	HumanHolyEquip* HumanCollection::mutable_humanholyequip()
	{
		if(m_pHumanHolyEquip == NULL)
		{
			m_pHumanHolyEquip = new HumanHolyEquip();
			m_pHumanHolyEquip->set_masterid(m_vMasterId);
		}
		return m_pHumanHolyEquip;
	}

	HumanHotActivity* HumanCollection::mutable_humanhotactivity()
	{
		if(m_pHumanHotActivity == NULL)
		{
			m_pHumanHotActivity = new HumanHotActivity();
			m_pHumanHotActivity->set_masterid(m_vMasterId);
		}
		return m_pHumanHotActivity;
	}

	HumanIntensify* HumanCollection::mutable_humanintensify()
	{
		if(m_pHumanIntensify == NULL)
		{
			m_pHumanIntensify = new HumanIntensify();
			m_pHumanIntensify->set_masterid(m_vMasterId);
		}
		return m_pHumanIntensify;
	}

	HumanItemExchange* HumanCollection::mutable_humanitemexchange()
	{
		if(m_pHumanItemExchange == NULL)
		{
			m_pHumanItemExchange = new HumanItemExchange();
			m_pHumanItemExchange->set_masterid(m_vMasterId);
		}
		return m_pHumanItemExchange;
	}

	HumanLansquenet* HumanCollection::mutable_humanlansquenet()
	{
		if(m_pHumanLansquenet == NULL)
		{
			m_pHumanLansquenet = new HumanLansquenet();
			m_pHumanLansquenet->set_masterid(m_vMasterId);
		}
		return m_pHumanLansquenet;
	}

	HumanLevelGift* HumanCollection::mutable_humanlevelgift()
	{
		if(m_pHumanLevelGift == NULL)
		{
			m_pHumanLevelGift = new HumanLevelGift();
			m_pHumanLevelGift->set_masterid(m_vMasterId);
		}
		return m_pHumanLevelGift;
	}

	HumanLottery* HumanCollection::mutable_humanlottery()
	{
		if(m_pHumanLottery == NULL)
		{
			m_pHumanLottery = new HumanLottery();
			m_pHumanLottery->set_masterid(m_vMasterId);
		}
		return m_pHumanLottery;
	}

	HumanLotteryPrize* HumanCollection::mutable_humanlotteryprize()
	{
		if(m_pHumanLotteryPrize == NULL)
		{
			m_pHumanLotteryPrize = new HumanLotteryPrize();
			m_pHumanLotteryPrize->set_masterid(m_vMasterId);
		}
		return m_pHumanLotteryPrize;
	}

	HumanMDLongYu* HumanCollection::mutable_humanmdlongyu()
	{
		if(m_pHumanMDLongYu == NULL)
		{
			m_pHumanMDLongYu = new HumanMDLongYu();
			m_pHumanMDLongYu->set_masterid(m_vMasterId);
		}
		return m_pHumanMDLongYu;
	}

	HumanMDWinter* HumanCollection::mutable_humanmdwinter()
	{
		if(m_pHumanMDWinter == NULL)
		{
			m_pHumanMDWinter = new HumanMDWinter();
			m_pHumanMDWinter->set_masterid(m_vMasterId);
		}
		return m_pHumanMDWinter;
	}

	HumanMagicCircle* HumanCollection::mutable_humanmagiccircle()
	{
		if(m_pHumanMagicCircle == NULL)
		{
			m_pHumanMagicCircle = new HumanMagicCircle();
			m_pHumanMagicCircle->set_masterid(m_vMasterId);
		}
		return m_pHumanMagicCircle;
	}

	HumanMall* HumanCollection::mutable_humanmall()
	{
		if(m_pHumanMall == NULL)
		{
			m_pHumanMall = new HumanMall();
			m_pHumanMall->set_masterid(m_vMasterId);
		}
		return m_pHumanMall;
	}

	HumanMeditation* HumanCollection::mutable_humanmeditation()
	{
		if(m_pHumanMeditation == NULL)
		{
			m_pHumanMeditation = new HumanMeditation();
			m_pHumanMeditation->set_masterid(m_vMasterId);
		}
		return m_pHumanMeditation;
	}

	HumanMeridian* HumanCollection::mutable_humanmeridian()
	{
		if(m_pHumanMeridian == NULL)
		{
			m_pHumanMeridian = new HumanMeridian();
			m_pHumanMeridian->set_masterid(m_vMasterId);
		}
		return m_pHumanMeridian;
	}

	HumanMilitary* HumanCollection::mutable_humanmilitary()
	{
		if(m_pHumanMilitary == NULL)
		{
			m_pHumanMilitary = new HumanMilitary();
			m_pHumanMilitary->set_masterid(m_vMasterId);
		}
		return m_pHumanMilitary;
	}

	HumanMisc* HumanCollection::mutable_humanmisc()
	{
		if(m_pHumanMisc == NULL)
		{
			m_pHumanMisc = new HumanMisc();
			m_pHumanMisc->set_masterid(m_vMasterId);
		}
		return m_pHumanMisc;
	}

	HumanMonsterManual* HumanCollection::mutable_humanmonstermanual()
	{
		if(m_pHumanMonsterManual == NULL)
		{
			m_pHumanMonsterManual = new HumanMonsterManual();
			m_pHumanMonsterManual->set_masterid(m_vMasterId);
		}
		return m_pHumanMonsterManual;
	}

	HumanMultiplayerDungeon* HumanCollection::mutable_humanmultiplayerdungeon()
	{
		if(m_pHumanMultiplayerDungeon == NULL)
		{
			m_pHumanMultiplayerDungeon = new HumanMultiplayerDungeon();
			m_pHumanMultiplayerDungeon->set_masterid(m_vMasterId);
		}
		return m_pHumanMultiplayerDungeon;
	}

	HumanOfflineReward* HumanCollection::mutable_humanofflinereward()
	{
		if(m_pHumanOfflineReward == NULL)
		{
			m_pHumanOfflineReward = new HumanOfflineReward();
			m_pHumanOfflineReward->set_masterid(m_vMasterId);
		}
		return m_pHumanOfflineReward;
	}

	HumanOnlineReward* HumanCollection::mutable_humanonlinereward()
	{
		if(m_pHumanOnlineReward == NULL)
		{
			m_pHumanOnlineReward = new HumanOnlineReward();
			m_pHumanOnlineReward->set_masterid(m_vMasterId);
		}
		return m_pHumanOnlineReward;
	}

	HumanOpenAuction* HumanCollection::mutable_humanopenauction()
	{
		if(m_pHumanOpenAuction == NULL)
		{
			m_pHumanOpenAuction = new HumanOpenAuction();
			m_pHumanOpenAuction->set_masterid(m_vMasterId);
		}
		return m_pHumanOpenAuction;
	}

	HumanOwnedAura* HumanCollection::mutable_humanownedaura()
	{
		if(m_pHumanOwnedAura == NULL)
		{
			m_pHumanOwnedAura = new HumanOwnedAura();
			m_pHumanOwnedAura->set_masterid(m_vMasterId);
		}
		return m_pHumanOwnedAura;
	}

	HumanOwnedSkill* HumanCollection::mutable_humanownedskill()
	{
		if(m_pHumanOwnedSkill == NULL)
		{
			m_pHumanOwnedSkill = new HumanOwnedSkill();
			m_pHumanOwnedSkill->set_masterid(m_vMasterId);
		}
		return m_pHumanOwnedSkill;
	}

	HumanPet* HumanCollection::mutable_humanpet()
	{
		if(m_pHumanPet == NULL)
		{
			m_pHumanPet = new HumanPet();
			m_pHumanPet->set_masterid(m_vMasterId);
		}
		return m_pHumanPet;
	}

	HumanPill* HumanCollection::mutable_humanpill()
	{
		if(m_pHumanPill == NULL)
		{
			m_pHumanPill = new HumanPill();
			m_pHumanPill->set_masterid(m_vMasterId);
		}
		return m_pHumanPill;
	}

	HumanPrayerStar* HumanCollection::mutable_humanprayerstar()
	{
		if(m_pHumanPrayerStar == NULL)
		{
			m_pHumanPrayerStar = new HumanPrayerStar();
			m_pHumanPrayerStar->set_masterid(m_vMasterId);
		}
		return m_pHumanPrayerStar;
	}

	HumanProduceCoin* HumanCollection::mutable_humanproducecoin()
	{
		if(m_pHumanProduceCoin == NULL)
		{
			m_pHumanProduceCoin = new HumanProduceCoin();
			m_pHumanProduceCoin->set_masterid(m_vMasterId);
		}
		return m_pHumanProduceCoin;
	}

	HumanPropsFund* HumanCollection::mutable_humanpropsfund()
	{
		if(m_pHumanPropsFund == NULL)
		{
			m_pHumanPropsFund = new HumanPropsFund();
			m_pHumanPropsFund->set_masterid(m_vMasterId);
		}
		return m_pHumanPropsFund;
	}

	HumanPropsFundEx* HumanCollection::mutable_humanpropsfundex()
	{
		if(m_pHumanPropsFundEx == NULL)
		{
			m_pHumanPropsFundEx = new HumanPropsFundEx();
			m_pHumanPropsFundEx->set_masterid(m_vMasterId);
		}
		return m_pHumanPropsFundEx;
	}

	HumanPseudoRandom* HumanCollection::mutable_humanpseudorandom()
	{
		if(m_pHumanPseudoRandom == NULL)
		{
			m_pHumanPseudoRandom = new HumanPseudoRandom();
			m_pHumanPseudoRandom->set_masterid(m_vMasterId);
		}
		return m_pHumanPseudoRandom;
	}

	HumanRandShop* HumanCollection::mutable_humanrandshop()
	{
		if(m_pHumanRandShop == NULL)
		{
			m_pHumanRandShop = new HumanRandShop();
			m_pHumanRandShop->set_masterid(m_vMasterId);
		}
		return m_pHumanRandShop;
	}

	HumanRandomQuests* HumanCollection::mutable_humanrandomquests()
	{
		if(m_pHumanRandomQuests == NULL)
		{
			m_pHumanRandomQuests = new HumanRandomQuests();
			m_pHumanRandomQuests->set_masterid(m_vMasterId);
		}
		return m_pHumanRandomQuests;
	}

	HumanRepeatableQuests* HumanCollection::mutable_humanrepeatablequests()
	{
		if(m_pHumanRepeatableQuests == NULL)
		{
			m_pHumanRepeatableQuests = new HumanRepeatableQuests();
			m_pHumanRepeatableQuests->set_masterid(m_vMasterId);
		}
		return m_pHumanRepeatableQuests;
	}

	HumanRide* HumanCollection::mutable_humanride()
	{
		if(m_pHumanRide == NULL)
		{
			m_pHumanRide = new HumanRide();
			m_pHumanRide->set_masterid(m_vMasterId);
		}
		return m_pHumanRide;
	}

	HumanRoleCreatedBonus* HumanCollection::mutable_humanrolecreatedbonus()
	{
		if(m_pHumanRoleCreatedBonus == NULL)
		{
			m_pHumanRoleCreatedBonus = new HumanRoleCreatedBonus();
			m_pHumanRoleCreatedBonus->set_masterid(m_vMasterId);
		}
		return m_pHumanRoleCreatedBonus;
	}

	HumanRunCar* HumanCollection::mutable_humanruncar()
	{
		if(m_pHumanRunCar == NULL)
		{
			m_pHumanRunCar = new HumanRunCar();
			m_pHumanRunCar->set_masterid(m_vMasterId);
		}
		return m_pHumanRunCar;
	}

	HumanShadow* HumanCollection::mutable_humanshadow()
	{
		if(m_pHumanShadow == NULL)
		{
			m_pHumanShadow = new HumanShadow();
			m_pHumanShadow->set_masterid(m_vMasterId);
		}
		return m_pHumanShadow;
	}

	HumanSingleBoss* HumanCollection::mutable_humansingleboss()
	{
		if(m_pHumanSingleBoss == NULL)
		{
			m_pHumanSingleBoss = new HumanSingleBoss();
			m_pHumanSingleBoss->set_masterid(m_vMasterId);
		}
		return m_pHumanSingleBoss;
	}

	HumanSkillCooldown* HumanCollection::mutable_humanskillcooldown()
	{
		if(m_pHumanSkillCooldown == NULL)
		{
			m_pHumanSkillCooldown = new HumanSkillCooldown();
			m_pHumanSkillCooldown->set_masterid(m_vMasterId);
		}
		return m_pHumanSkillCooldown;
	}

	HumanSweep* HumanCollection::mutable_humansweep()
	{
		if(m_pHumanSweep == NULL)
		{
			m_pHumanSweep = new HumanSweep();
			m_pHumanSweep->set_masterid(m_vMasterId);
		}
		return m_pHumanSweep;
	}

	HumanTeleporter* HumanCollection::mutable_humanteleporter()
	{
		if(m_pHumanTeleporter == NULL)
		{
			m_pHumanTeleporter = new HumanTeleporter();
			m_pHumanTeleporter->set_masterid(m_vMasterId);
		}
		return m_pHumanTeleporter;
	}

	HumanTencentAward* HumanCollection::mutable_humantencentaward()
	{
		if(m_pHumanTencentAward == NULL)
		{
			m_pHumanTencentAward = new HumanTencentAward();
			m_pHumanTencentAward->set_masterid(m_vMasterId);
		}
		return m_pHumanTencentAward;
	}

	HumanTimers* HumanCollection::mutable_humantimers()
	{
		if(m_pHumanTimers == NULL)
		{
			m_pHumanTimers = new HumanTimers();
			m_pHumanTimers->set_masterid(m_vMasterId);
		}
		return m_pHumanTimers;
	}

	HumanTitle* HumanCollection::mutable_humantitle()
	{
		if(m_pHumanTitle == NULL)
		{
			m_pHumanTitle = new HumanTitle();
			m_pHumanTitle->set_masterid(m_vMasterId);
		}
		return m_pHumanTitle;
	}

	HumanUnderwayQuests* HumanCollection::mutable_humanunderwayquests()
	{
		if(m_pHumanUnderwayQuests == NULL)
		{
			m_pHumanUnderwayQuests = new HumanUnderwayQuests();
			m_pHumanUnderwayQuests->set_masterid(m_vMasterId);
		}
		return m_pHumanUnderwayQuests;
	}

	HumanVip* HumanCollection::mutable_humanvip()
	{
		if(m_pHumanVip == NULL)
		{
			m_pHumanVip = new HumanVip();
			m_pHumanVip->set_masterid(m_vMasterId);
		}
		return m_pHumanVip;
	}

	HumanWarlord* HumanCollection::mutable_humanwarlord()
	{
		if(m_pHumanWarlord == NULL)
		{
			m_pHumanWarlord = new HumanWarlord();
			m_pHumanWarlord->set_masterid(m_vMasterId);
		}
		return m_pHumanWarlord;
	}

	HumanYZSL* HumanCollection::mutable_humanyzsl()
	{
		if(m_pHumanYZSL == NULL)
		{
			m_pHumanYZSL = new HumanYZSL();
			m_pHumanYZSL->set_masterid(m_vMasterId);
		}
		return m_pHumanYZSL;
	}

	void HumanCollection::cleanup_human()
	{
		_safe_delete(m_pHuman);
	}

	void HumanCollection::cleanup_human7dayquests()
	{
		_safe_delete(m_pHuman7DayQuests);
	}

	void HumanCollection::cleanup_humanachievement()
	{
		_safe_delete(m_pHumanAchievement);
	}

	void HumanCollection::cleanup_humanactivitecode()
	{
		_safe_delete(m_pHumanActiviteCode);
	}

	void HumanCollection::cleanup_humanacution()
	{
		_safe_delete(m_pHumanAcution);
	}

	void HumanCollection::cleanup_humanalchemy()
	{
		_safe_delete(m_pHumanAlchemy);
	}

	void HumanCollection::cleanup_humanarena()
	{
		_safe_delete(m_pHumanArena);
	}

	void HumanCollection::cleanup_humanattr()
	{
		_safe_delete(m_pHumanAttr);
	}

	void HumanCollection::cleanup_humanbabel()
	{
		_safe_delete(m_pHumanBabel);
	}

	void HumanCollection::cleanup_humanbattle()
	{
		_safe_delete(m_pHumanBattle);
	}

	void HumanCollection::cleanup_humancash()
	{
		_safe_delete(m_pHumanCash);
	}

	void HumanCollection::cleanup_humanchallenge()
	{
		_safe_delete(m_pHumanChallenge);
	}

	void HumanCollection::cleanup_humanchallengelive()
	{
		_safe_delete(m_pHumanChallengeLive);
	}

	void HumanCollection::cleanup_humanchallengeother()
	{
		_safe_delete(m_pHumanChallengeOther);
	}

	void HumanCollection::cleanup_humanchest()
	{
		_safe_delete(m_pHumanChest);
	}

	void HumanCollection::cleanup_humanclientsetting()
	{
		_safe_delete(m_pHumanClientSetting);
	}

	void HumanCollection::cleanup_humancommonactivity()
	{
		_safe_delete(m_pHumanCommonActivity);
	}

	void HumanCollection::cleanup_humancommoncooldown()
	{
		_safe_delete(m_pHumanCommonCooldown);
	}

	void HumanCollection::cleanup_humancompletedquests()
	{
		_safe_delete(m_pHumanCompletedQuests);
	}

	void HumanCollection::cleanup_humancontacts()
	{
		_safe_delete(m_pHumanContacts);
	}

	void HumanCollection::cleanup_humandailybonus()
	{
		_safe_delete(m_pHumanDailyBonus);
	}

	void HumanCollection::cleanup_humandailyrecharge()
	{
		_safe_delete(m_pHumanDailyRecharge);
	}

	void HumanCollection::cleanup_humandarkarena()
	{
		_safe_delete(m_pHumanDarkarena);
	}

	void HumanCollection::cleanup_humandragonhunt()
	{
		_safe_delete(m_pHumanDragonHunt);
	}

	void HumanCollection::cleanup_humandts()
	{
		_safe_delete(m_pHumanDts);
	}

	void HumanCollection::cleanup_humandungeonrecord()
	{
		_safe_delete(m_pHumanDungeonRecord);
	}

	void HumanCollection::cleanup_humanequiprefine()
	{
		_safe_delete(m_pHumanEquipRefine);
	}

	void HumanCollection::cleanup_humanexplore()
	{
		_safe_delete(m_pHumanExplore);
	}

	void HumanCollection::cleanup_humanfestivalactivity()
	{
		_safe_delete(m_pHumanFestivalActivity);
	}

	void HumanCollection::cleanup_humanfish()
	{
		_safe_delete(m_pHumanFish);
	}

	void HumanCollection::cleanup_humanflag()
	{
		_safe_delete(m_pHumanFlag);
	}

	void HumanCollection::cleanup_humanfood()
	{
		_safe_delete(m_pHumanFood);
	}

	void HumanCollection::cleanup_humanformation()
	{
		_safe_delete(m_pHumanFormation);
	}

	void HumanCollection::cleanup_humanfunction()
	{
		_safe_delete(m_pHumanFunction);
	}

	void HumanCollection::cleanup_humangjfb()
	{
		_safe_delete(m_pHumanGJFB);
	}

	void HumanCollection::cleanup_humangemequipslotstate()
	{
		_safe_delete(m_pHumanGemEquipSlotState);
	}

	void HumanCollection::cleanup_humangift()
	{
		_safe_delete(m_pHumanGift);
	}

	void HumanCollection::cleanup_humanguide()
	{
		_safe_delete(m_pHumanGuide);
	}

	void HumanCollection::cleanup_humanguildquests()
	{
		_safe_delete(m_pHumanGuildQuests);
	}

	void HumanCollection::cleanup_humanguildshopitems()
	{
		_safe_delete(m_pHumanGuildShopItems);
	}

	void HumanCollection::cleanup_humanhelltrial()
	{
		_safe_delete(m_pHumanHellTrial);
	}

	void HumanCollection::cleanup_humanhero()
	{
		_safe_delete(m_pHumanHero);
	}

	void HumanCollection::cleanup_humanherocollect()
	{
		_safe_delete(m_pHumanHeroCollect);
	}

	void HumanCollection::cleanup_humanherotactical()
	{
		_safe_delete(m_pHumanHeroTactical);
	}

	void HumanCollection::cleanup_humanholyequip()
	{
		_safe_delete(m_pHumanHolyEquip);
	}

	void HumanCollection::cleanup_humanhotactivity()
	{
		_safe_delete(m_pHumanHotActivity);
	}

	void HumanCollection::cleanup_humanintensify()
	{
		_safe_delete(m_pHumanIntensify);
	}

	void HumanCollection::cleanup_humanitemexchange()
	{
		_safe_delete(m_pHumanItemExchange);
	}

	void HumanCollection::cleanup_humanlansquenet()
	{
		_safe_delete(m_pHumanLansquenet);
	}

	void HumanCollection::cleanup_humanlevelgift()
	{
		_safe_delete(m_pHumanLevelGift);
	}

	void HumanCollection::cleanup_humanlottery()
	{
		_safe_delete(m_pHumanLottery);
	}

	void HumanCollection::cleanup_humanlotteryprize()
	{
		_safe_delete(m_pHumanLotteryPrize);
	}

	void HumanCollection::cleanup_humanmdlongyu()
	{
		_safe_delete(m_pHumanMDLongYu);
	}

	void HumanCollection::cleanup_humanmdwinter()
	{
		_safe_delete(m_pHumanMDWinter);
	}

	void HumanCollection::cleanup_humanmagiccircle()
	{
		_safe_delete(m_pHumanMagicCircle);
	}

	void HumanCollection::cleanup_humanmall()
	{
		_safe_delete(m_pHumanMall);
	}

	void HumanCollection::cleanup_humanmeditation()
	{
		_safe_delete(m_pHumanMeditation);
	}

	void HumanCollection::cleanup_humanmeridian()
	{
		_safe_delete(m_pHumanMeridian);
	}

	void HumanCollection::cleanup_humanmilitary()
	{
		_safe_delete(m_pHumanMilitary);
	}

	void HumanCollection::cleanup_humanmisc()
	{
		_safe_delete(m_pHumanMisc);
	}

	void HumanCollection::cleanup_humanmonstermanual()
	{
		_safe_delete(m_pHumanMonsterManual);
	}

	void HumanCollection::cleanup_humanmultiplayerdungeon()
	{
		_safe_delete(m_pHumanMultiplayerDungeon);
	}

	void HumanCollection::cleanup_humanofflinereward()
	{
		_safe_delete(m_pHumanOfflineReward);
	}

	void HumanCollection::cleanup_humanonlinereward()
	{
		_safe_delete(m_pHumanOnlineReward);
	}

	void HumanCollection::cleanup_humanopenauction()
	{
		_safe_delete(m_pHumanOpenAuction);
	}

	void HumanCollection::cleanup_humanownedaura()
	{
		_safe_delete(m_pHumanOwnedAura);
	}

	void HumanCollection::cleanup_humanownedskill()
	{
		_safe_delete(m_pHumanOwnedSkill);
	}

	void HumanCollection::cleanup_humanpet()
	{
		_safe_delete(m_pHumanPet);
	}

	void HumanCollection::cleanup_humanpill()
	{
		_safe_delete(m_pHumanPill);
	}

	void HumanCollection::cleanup_humanprayerstar()
	{
		_safe_delete(m_pHumanPrayerStar);
	}

	void HumanCollection::cleanup_humanproducecoin()
	{
		_safe_delete(m_pHumanProduceCoin);
	}

	void HumanCollection::cleanup_humanpropsfund()
	{
		_safe_delete(m_pHumanPropsFund);
	}

	void HumanCollection::cleanup_humanpropsfundex()
	{
		_safe_delete(m_pHumanPropsFundEx);
	}

	void HumanCollection::cleanup_humanpseudorandom()
	{
		_safe_delete(m_pHumanPseudoRandom);
	}

	void HumanCollection::cleanup_humanrandshop()
	{
		_safe_delete(m_pHumanRandShop);
	}

	void HumanCollection::cleanup_humanrandomquests()
	{
		_safe_delete(m_pHumanRandomQuests);
	}

	void HumanCollection::cleanup_humanrepeatablequests()
	{
		_safe_delete(m_pHumanRepeatableQuests);
	}

	void HumanCollection::cleanup_humanride()
	{
		_safe_delete(m_pHumanRide);
	}

	void HumanCollection::cleanup_humanrolecreatedbonus()
	{
		_safe_delete(m_pHumanRoleCreatedBonus);
	}

	void HumanCollection::cleanup_humanruncar()
	{
		_safe_delete(m_pHumanRunCar);
	}

	void HumanCollection::cleanup_humanshadow()
	{
		_safe_delete(m_pHumanShadow);
	}

	void HumanCollection::cleanup_humansingleboss()
	{
		_safe_delete(m_pHumanSingleBoss);
	}

	void HumanCollection::cleanup_humanskillcooldown()
	{
		_safe_delete(m_pHumanSkillCooldown);
	}

	void HumanCollection::cleanup_humansweep()
	{
		_safe_delete(m_pHumanSweep);
	}

	void HumanCollection::cleanup_humanteleporter()
	{
		_safe_delete(m_pHumanTeleporter);
	}

	void HumanCollection::cleanup_humantencentaward()
	{
		_safe_delete(m_pHumanTencentAward);
	}

	void HumanCollection::cleanup_humantimers()
	{
		_safe_delete(m_pHumanTimers);
	}

	void HumanCollection::cleanup_humantitle()
	{
		_safe_delete(m_pHumanTitle);
	}

	void HumanCollection::cleanup_humanunderwayquests()
	{
		_safe_delete(m_pHumanUnderwayQuests);
	}

	void HumanCollection::cleanup_humanvip()
	{
		_safe_delete(m_pHumanVip);
	}

	void HumanCollection::cleanup_humanwarlord()
	{
		_safe_delete(m_pHumanWarlord);
	}

	void HumanCollection::cleanup_humanyzsl()
	{
		_safe_delete(m_pHumanYZSL);
	}

	Hero* HumanCollection::new_hero(bool manager)
	{
		Hero* tmp = new Hero();
		tmp->set_masterid(m_vMasterId);
		if(manager)
			m_vHero.push_back(tmp);
		return tmp;
	}

	bool HumanCollection::del_hero(Hero* value,bool freeIt)
	{
		return m_vHero.remove(value,freeIt);
	}

	void HumanCollection::load_hero(mongo::BSONObj& __obj)
	{
		m_vHero.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			Hero* tmp = new_hero(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void HumanCollection::save_hero(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vHero.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			Hero* tmp = m_vHero[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

	HeroCard* HumanCollection::new_herocard(bool manager)
	{
		HeroCard* tmp = new HeroCard();
		tmp->set_masterid(m_vMasterId);
		if(manager)
			m_vHeroCard.push_back(tmp);
		return tmp;
	}

	bool HumanCollection::del_herocard(HeroCard* value,bool freeIt)
	{
		return m_vHeroCard.remove(value,freeIt);
	}

	void HumanCollection::load_herocard(mongo::BSONObj& __obj)
	{
		m_vHeroCard.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			HeroCard* tmp = new_herocard(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void HumanCollection::save_herocard(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vHeroCard.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			HeroCard* tmp = m_vHeroCard[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

	HeroNew* HumanCollection::new_heronew(bool manager)
	{
		HeroNew* tmp = new HeroNew();
		tmp->set_masterid(m_vMasterId);
		if(manager)
			m_vHeroNew.push_back(tmp);
		return tmp;
	}

	bool HumanCollection::del_heronew(HeroNew* value,bool freeIt)
	{
		return m_vHeroNew.remove(value,freeIt);
	}

	void HumanCollection::load_heronew(mongo::BSONObj& __obj)
	{
		m_vHeroNew.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			HeroNew* tmp = new_heronew(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void HumanCollection::save_heronew(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vHeroNew.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			HeroNew* tmp = m_vHeroNew[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

	HolyWeapon* HumanCollection::new_holyweapon(bool manager)
	{
		HolyWeapon* tmp = new HolyWeapon();
		tmp->set_masterid(m_vMasterId);
		if(manager)
			m_vHolyWeapon.push_back(tmp);
		return tmp;
	}

	bool HumanCollection::del_holyweapon(HolyWeapon* value,bool freeIt)
	{
		return m_vHolyWeapon.remove(value,freeIt);
	}

	void HumanCollection::load_holyweapon(mongo::BSONObj& __obj)
	{
		m_vHolyWeapon.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			HolyWeapon* tmp = new_holyweapon(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void HumanCollection::save_holyweapon(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vHolyWeapon.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			HolyWeapon* tmp = m_vHolyWeapon[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

	HumanHeroSpirit* HumanCollection::new_humanherospirit(bool manager)
	{
		HumanHeroSpirit* tmp = new HumanHeroSpirit();
		tmp->set_masterid(m_vMasterId);
		if(manager)
			m_vHumanHeroSpirit.push_back(tmp);
		return tmp;
	}

	bool HumanCollection::del_humanherospirit(HumanHeroSpirit* value,bool freeIt)
	{
		return m_vHumanHeroSpirit.remove(value,freeIt);
	}

	void HumanCollection::load_humanherospirit(mongo::BSONObj& __obj)
	{
		m_vHumanHeroSpirit.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			HumanHeroSpirit* tmp = new_humanherospirit(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void HumanCollection::save_humanherospirit(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vHumanHeroSpirit.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			HumanHeroSpirit* tmp = m_vHumanHeroSpirit[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

	HumanItems* HumanCollection::new_humanitems(bool manager)
	{
		HumanItems* tmp = new HumanItems();
		tmp->set_masterid(m_vMasterId);
		if(manager)
			m_vHumanItems.push_back(tmp);
		return tmp;
	}

	bool HumanCollection::del_humanitems(HumanItems* value,bool freeIt)
	{
		return m_vHumanItems.remove(value,freeIt);
	}

	void HumanCollection::load_humanitems(mongo::BSONObj& __obj)
	{
		m_vHumanItems.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			HumanItems* tmp = new_humanitems(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void HumanCollection::save_humanitems(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vHumanItems.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			HumanItems* tmp = m_vHumanItems[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

	HumanLoadItemEquipPosUpgrade* HumanCollection::new_humanloaditemequipposupgrade(bool manager)
	{
		HumanLoadItemEquipPosUpgrade* tmp = new HumanLoadItemEquipPosUpgrade();
		tmp->set_masterid(m_vMasterId);
		if(manager)
			m_vHumanLoadItemEquipPosUpgrade.push_back(tmp);
		return tmp;
	}

	bool HumanCollection::del_humanloaditemequipposupgrade(HumanLoadItemEquipPosUpgrade* value,bool freeIt)
	{
		return m_vHumanLoadItemEquipPosUpgrade.remove(value,freeIt);
	}

	void HumanCollection::load_humanloaditemequipposupgrade(mongo::BSONObj& __obj)
	{
		m_vHumanLoadItemEquipPosUpgrade.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			HumanLoadItemEquipPosUpgrade* tmp = new_humanloaditemequipposupgrade(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void HumanCollection::save_humanloaditemequipposupgrade(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vHumanLoadItemEquipPosUpgrade.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			HumanLoadItemEquipPosUpgrade* tmp = m_vHumanLoadItemEquipPosUpgrade[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

	HumanLoadItemWash* HumanCollection::new_humanloaditemwash(bool manager)
	{
		HumanLoadItemWash* tmp = new HumanLoadItemWash();
		tmp->set_masterid(m_vMasterId);
		if(manager)
			m_vHumanLoadItemWash.push_back(tmp);
		return tmp;
	}

	bool HumanCollection::del_humanloaditemwash(HumanLoadItemWash* value,bool freeIt)
	{
		return m_vHumanLoadItemWash.remove(value,freeIt);
	}

	void HumanCollection::load_humanloaditemwash(mongo::BSONObj& __obj)
	{
		m_vHumanLoadItemWash.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			HumanLoadItemWash* tmp = new_humanloaditemwash(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void HumanCollection::save_humanloaditemwash(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vHumanLoadItemWash.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			HumanLoadItemWash* tmp = m_vHumanLoadItemWash[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

	HumanLoadItems* HumanCollection::new_humanloaditems(bool manager)
	{
		HumanLoadItems* tmp = new HumanLoadItems();
		tmp->set_masterid(m_vMasterId);
		if(manager)
			m_vHumanLoadItems.push_back(tmp);
		return tmp;
	}

	bool HumanCollection::del_humanloaditems(HumanLoadItems* value,bool freeIt)
	{
		return m_vHumanLoadItems.remove(value,freeIt);
	}

	void HumanCollection::load_humanloaditems(mongo::BSONObj& __obj)
	{
		m_vHumanLoadItems.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			HumanLoadItems* tmp = new_humanloaditems(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void HumanCollection::save_humanloaditems(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vHumanLoadItems.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			HumanLoadItems* tmp = m_vHumanLoadItems[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

	HumanNull* HumanCollection::new_humannull(bool manager)
	{
		HumanNull* tmp = new HumanNull();
		tmp->set_masterid(m_vMasterId);
		if(manager)
			m_vHumanNull.push_back(tmp);
		return tmp;
	}

	bool HumanCollection::del_humannull(HumanNull* value,bool freeIt)
	{
		return m_vHumanNull.remove(value,freeIt);
	}

	void HumanCollection::load_humannull(mongo::BSONObj& __obj)
	{
		m_vHumanNull.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			HumanNull* tmp = new_humannull(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void HumanCollection::save_humannull(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vHumanNull.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			HumanNull* tmp = m_vHumanNull[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

	MagicWeapon* HumanCollection::new_magicweapon(bool manager)
	{
		MagicWeapon* tmp = new MagicWeapon();
		tmp->set_masterid(m_vMasterId);
		if(manager)
			m_vMagicWeapon.push_back(tmp);
		return tmp;
	}

	bool HumanCollection::del_magicweapon(MagicWeapon* value,bool freeIt)
	{
		return m_vMagicWeapon.remove(value,freeIt);
	}

	void HumanCollection::load_magicweapon(mongo::BSONObj& __obj)
	{
		m_vMagicWeapon.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			MagicWeapon* tmp = new_magicweapon(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void HumanCollection::save_magicweapon(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vMagicWeapon.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			MagicWeapon* tmp = m_vMagicWeapon[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

	NewWeapon* HumanCollection::new_newweapon(bool manager)
	{
		NewWeapon* tmp = new NewWeapon();
		tmp->set_masterid(m_vMasterId);
		if(manager)
			m_vNewWeapon.push_back(tmp);
		return tmp;
	}

	bool HumanCollection::del_newweapon(NewWeapon* value,bool freeIt)
	{
		return m_vNewWeapon.remove(value,freeIt);
	}

	void HumanCollection::load_newweapon(mongo::BSONObj& __obj)
	{
		m_vNewWeapon.cleanup();
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			pwassertop(__be.isABSONObj(),continue);
			NewWeapon* tmp = new_newweapon(true);
			tmp->from_bson(__be.Obj());
		}
	}

	void HumanCollection::save_newweapon(mongo::BSONArrayBuilder& __tmpbuilder)
	{
		for(size_t i = 0; i < m_vNewWeapon.size(); ++i)
		{
			mongo::BSONObj __tmpobj;
			NewWeapon* tmp = m_vNewWeapon[i];
			tmp->to_bson(__tmpobj);
			__tmpbuilder.append(__tmpobj);
		}
	}

}
