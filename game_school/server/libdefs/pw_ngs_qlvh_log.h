#ifndef _pw_ngs_qlvh_log_
#define _pw_ngs_qlvh_log_

#include "pw_types.h"
#include <string>

namespace pwngs
{
	extern void WriteWLog(int32 type,const char* text,bool write_syslog = true);
	extern void WriteMData(int32 type, const char* text, bool write_syslog = true);
	extern std::string extract_passport(const char* userid);
	extern std::string extract_passport_agent(const char* userid);

	#define WLOG_HUMAN_INFO(h) h->GetAgent(),h->GetAccountName(),h->GetID(),h->GetNameUTF8(),h->GetLevel(),h->GetModVip()->GetLevel()
	#define WLOG_HUMAN_MONEY_INFO(h) h->GetZoneId(),h->GetAccountName(),h->GetID(),h->GetAgent(),h->GetNameUTF8(),h->GetLevel(),h->GetModVip()->GetLevel(),h->GetClientTypeName()
	#define WLOG_HUMAN_QUEST_INFO(h) h->GetZoneId(),h->GetAccountName(),h->GetAgent(),h->GetID(),h->GetNameUTF8(),h->GetLevel(),h->GetClientTypeName()
	#define WLOG_DRAGON_STATUS(h,d) h->GetZoneId(),h->GetAccountName(),h->GetID(),h->GetNameUTF8(),h->GetLevel(),h->GetAgent(),h->GetClientTypeName(),d->GetID(),d->GetName(),d->GetLevel()

	enum WLogLogoutStatus
	{
		WLOG_LOGOUT_STATUS_KICK = 1,
		WLOG_LOGOUT_STATUS_DISCONNECT,
		WLOG_LOGOUT_STATUS_DBKICK,
		WLOG_LOGOUT_STATUS_AUKICK,
		WLOG_LOGOUT_STATUS_FATIGUE,
		WLOG_LOGOUT_STATUS_CHEAT,
		WLOG_LOGOUT_STATUS_TIMEOUT,
	};

	enum WLOG_QUEST_STATUS
	{
		WLOG_QUEST_STATUS_COMPLETE = 0,
		WLOG_QUEST_STATUS_GIVEUP,
		WLOG_QUEST_STATUS_ACCEPT,
	};

	enum WLOG_QUEST_TYPE
	{
		WLOG_QUEST_TYPE_GUIDE = 0,
		WLOG_QUEST_TYPE_NORMAL,
		WLOG_QUEST_TYPE_MAIN,
	};

	enum EWlogArenaType
	{
		WLOG_ARENA_TYPE_COMMON,
		WLOG_ARENA_TYPE_DARKARENA,
	};

	enum EWlogBehavior
	{
		WLOG_BEHAVIOR_KILL,
		WLOG_BEHAVIOR_TAME_DRAGON,
		WLOG_BEHAVIOR_GEM_INLAY,
		WLOG_BEHAVIOR_GEM_LEVELUP,
		WLOG_BEHAVIOR_NUM,
	};

	enum WLOG_TRADE_TYPE
	{
		WLOG_TRADETYPE_GRANT = 1,
		WLOG_TRADETYPE_SPEND = 2,
	};

	enum WLOG_TRADE_BUYTYPE
	{
		WLOG_TRADE_BUYTYPE_GOLD = 0,
		WLOG_TRADE_BUYTYPE_GOLDGIFT = 7,
		WLOG_TRADE_BUYTYPE_SILVER = 2,
		WLOG_TRADE_BUYTYPE_HONOR = 10, // 荣誉
		WLOG_TRADE_BUYTYPE_ARENA_POINT = 11, // 竞技点
		WLOG_TRADE_BUYTYPE_MEDAL_POINT = 12, // 勋章
		WLOG_TRADE_BUYTYPE_ARENA_MEDAL = 13, // 竞技勋章
		WLOG_TRADE_BUYTYPE_BATTLE_POINT = 14,
		WLOG_TRADE_BUYTYPE_CRYSTAL_POINT = 15,
		WLOG_TRADE_BUYTYPE_TRIAL_POINT = 16,
	};

	enum EWLOGRoleChangeType
	{
		WLOG_ROLECHANGED_DELETED = 0,
		WLOG_ROLECHANGED_CANCEL_DELETE = 1,
	};

	enum EWLOG_DragonStatus
	{
		WLOG_DRAGON_STATUS_BLESS = 1, // 祝福
		WLOG_DRAGON_STATUS_SKILL, // 技能
		WLOG_DRAGON_STATUS_DELVE, // 专精
		WLOG_DRAGON_STATUS_SAVEY, // 悟性
		WLOG_DRAGON_STATUS_TALENT, // 天赋
	};

	enum EWLOG_WeaponBehavior
	{
		WLOG_WEAPON_ADVANCE = 1, //升阶
		WLOG_WEAPON_UPSTAR,		//升星
		WLOG_WEAPON_UPQUALITY,  //升品
		
	};

	enum EWLOG_CultivateSystem
	{
		WLOG_CULTIVATE_PET = 1, //宠物
		WLOG_CULTIVATE_RIDE,	//坐骑
		WLOG_CULTIVATE_FLAG,	//背旗
		WLOG_CULTIVATE_MAGICCIRCLE,	//法阵
	};

	enum EWLOG_CultivateBehavior
	{
		WLOG_CULTIVATE_UPLEVEL = 1,	//升级
		WLOG_CULTIVATE_ADVANCE,	//升阶

	};

	enum EWLOG_LansquenetBehavior
	{
		WLOG_LANSQUENET_UPLEVEL = 1, //升级
		WLOG_LANSQUENET_UPSTAR,		//升星
		WLOG_LANSQUENET_UPINJECT,  //升注灵
		WLOG_LANSQUENET_UPHEART,	//升心法
	};

	extern const char* cst_wlog_behavior_names[WLOG_BEHAVIOR_NUM];

	//fwcq BI函数
	// 登录log
	extern void WLOG_Login(int32 zid,const char* account,const char* userid,int64 roleid,const char* ip,const char* mac,
		const char* agent, const char* clientType, const char* deviceid, const char* source, const char* rolename, const char* pf, 
		int32 level, int32 scene);
	
	// 登出
	extern void WLOG_Logout(int32 zid,const char* account,const char* userid,int64 roleid,const char* ip,const char* mac,
		const char* agent,int32 time,int32 status,int32 locationx,int32 locationy,const char* quest,
		int32 level,int32 scene,const char* clientType,const char* rolename,const char* sceneName,int64 fightpoint,const char* pf);

	// 在线
	extern void WLOG_OnlineUser(int32 zid,int32 currentnum,int32 maxnumonsrv,int32 regisnum,const char* clientType,
		const char* agent,int32 totalmaxonline,int32 registaccount);

	// 充值
	extern void WLOG_AddCash(int32 zid,const char* account,const char* userid,int64 roleid,const char* agent,
		const char* serial, int64 cash_add, int64 delta, int32 viplev, const char* clientType, const char* rolename, 
		float rmb, float pubacct_rmb, const char* pf, int32 guildID);

	// 升级
	extern void WLOG_Upgrade(int32 zid,const char* userid,int64 roleid,int32 profession,const char* agent,int32 vip_lev,
		int64 fightvalue, int32 level, int64 exp, int64 money, int64 time, const char* clientType, const char* rolename, const char* pf, 
		int32 scene, int source);

	//金钱
	extern void WLOG_Money(int32 zid,const char* userid,int64 roleid,const char* agent,const char* rolename,
		int32 level,int32 vip_lev,const char* clientType,
		const char* order_id,int64 itemtype,const char* itemname,int32 itemcount,WLOG_TRADE_BUYTYPE buytype,int64 cashneed,
		int64 cashleft,int32 wayid,int32 discount,WLOG_TRADE_TYPE type,const char* pf, int32 mapid = 0, bool isMall=false);

	//任务
	extern void WLOG_Quest(int32 zid,const char* userid,const char* agent,int64 roleid,const char* rolename,int32 lev,const char* clientType,
		int32 questid,const char* questname,int firstCompleted,WLOG_QUEST_STATUS quest_status,WLOG_QUEST_TYPE questtype,const char* pf, int32 scene);

	//创建角色
	extern void WLOG_CreateRole(int32 zid,const char* userid,int64 roleid,const char* name,const char* ip,const char* agent,
		const char* adid,int profession,const char* clientType,int gender,const char* pf);

	//新用户
	extern void WLOG_NewUser(int32 zid, const char* userid, const char* agent, const char* adid, const char* client, const char* pf);

	//道具相关
	extern void WLOG_DictItem(int32 itemid, int32 itemcount, const char* itemname, int32 itemtype, const char* itemtypename, int32 item_expire, int32 zid,
		int32 price_gold = 0, int32 price_silver = 0, int32 price_arena_point = 0,
		int32 price_horno = 0, int32 price_medal_point = 0, int32 price_arena_medal = 0);

	extern void WLOG_Dungeon(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int level,
		int copyid, const char* copyname, int firstCompleted, int copystatus, int copymark, const char* clientType, const char* pf);
	extern void WLOG_Item(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int level,
		int propid, const char* propname, int propcount, int propsurpluscount, int type, const char* pf, bool isBind = true);

	extern void WLOG_Mall_Buy(const char* agent, const char* userid, int64 roleid, int level,
		int64 balance, int32 itemid, int amount, int64 money, int64 remain, int32 map_id, int type);

	extern void WLOG_Shop_Sell(const char* agent, const char* userid, int64 roleid, int level,
		int64 balance, int32 itemid, int amount, int64 money, int32 map_id);

	extern void WLOG_CashSnapshot(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int level,
		int64 pay, int64 buy, int64 sale, int64 used, int64 surplusyuanbao);

	//装备宝石
	extern void WLOG_EquipGem(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int nIndex, int32 nItemID, const char* pf = "");
	//装备洗练
	extern void WLOG_EquipWash(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int nIndex, int level, const char* pf = "");
	//装备数据
	extern void WLOG_EquipmentData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int level, const char* itemdata, int flag = 0);
	//经脉数据
	extern void WLOG_MeridianData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int learned_id);
	//技能数据
	extern void WLOG_SkillSnapshot(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int level, int occupation,
		int skillid, const char* skillname, int skilllvl);
	//法宝数据
	extern void WLOG_WeaponData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename,int32 nID, int advance, int starlevel, int quality, EWLOG_WeaponBehavior type);
	//养成数据（坐骑，宠物，背旗）
	extern void WLOG_CultivateData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int32 nID, 
		int advance, int advance_star, int level, int levelstar, EWLOG_CultivateSystem type_S, EWLOG_CultivateBehavior type_B);
	//侍从数据
	extern void WLOG_LansquenetData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int32 nID, 
		int32 level, int32 starlevel, const char* injectlevel, const char* heartlevel, EWLOG_LansquenetBehavior type);
	//等级礼包
	extern void WLOG_LevelGiftData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int32 nGiftLev, const char* type);
	//VIP变化
	extern void WLOG_VipUpgrade(int32 zid, const char* passport, const char* agent, int64 roleid, const char* rolename,
		int oldlev, int newlev, int64 charged, const char* clientType, const char* pf);
	//新神器数据
	extern void WLOG_NewWeaponData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int32 nID, int advance, EWLOG_WeaponBehavior type);

	// ------------------------------------------------------------------------------------------------

	extern void WLOG_Behavior(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int level,
		EWlogBehavior type, int behaviortime = 1, const char* pf = "");

	extern void WLOG_ChangeRole(int32 zid, const char* userid, int64 roleid, const char* rolename, const char* ip,
		int32 occupation, const char* agent, const char* client, EWLOGRoleChangeType type, const char* pf);


	extern void WLOG_OpenPlayentry(int32 zid, const char* userid, int64 roleid, const char* rolename, const char* ip,
		int32 occupation, const char* agent, const char* client, int32 playentry, const char* pf);

	extern void WLOG_DragonStatus(int32 zid, const char* userid, int64 roleid, const char* rolename, int32 rolelev,
		const char* agent, const char* client,
		int64 dragonid, const std::string& dragonname_mbs, int32 dragonlev,
		EWLOG_DragonStatus type, int32 attrid, const char* attrname_mbs, double attrvalue, const char* pf);


	extern void WLOG_GemSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int color,
		int numstonelvl1,int numstonelvl2,int numstonelvl3,int numstonelvl4,int numstonelvl5,
		int numstonelvl6,int numstonelvl7,int numstonelvl8,int numstonelvl9,int numstonelvl10,
		int numstonelvl11,int numstonelvl12,int numstonelvl13,int numstonelvl14,int numstonelvl15);
	extern void WLOG_GemSnapshotSuccessful(int32 zid,const char* flag="success");

	
	extern void WLOG_Arena(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,int occupation,
		int credits,int reputation,int paymark,int status,EWlogArenaType type,const char* pf);
	extern void WLOG_Battle(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,int occupation,
		int result,const char* pf);
	
	extern void WLOG_CommonActivityReward( int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,int aid,int gid,const char* pf);
	extern void WLOG_ChargeCallBackReward( int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,int tid,int cnt,const char* pf);
	extern void WLOG_HotActivityReward( int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,int aid,int gid,const char* pf);
	
	/*
	1000 骑龙战斗loading
	1001 骑龙战斗
	2000 创角loading
	2001 创建角色
	3000 游戏loading
	3001 进入游戏
	*/
	enum EWLOG_CRL_TYPE
	{
		WLOG_CRL_NEWBIE_LOADING = 1000, // 
		WLOG_CRL_NEWBIE_ENTER = 1001,
		WLOG_CRL_CREATE_LOADING = 2000,
		WLOG_CRL_CREATE_OK = 2001,
		WLOG_CRL_PLAY_LOADING = 3000,
		WLOG_CRL_PLAY_ENTER = 3001,


		WLOG_CRL_MASK_PLAY_LOADING = 1,
		WLOG_CRL_MASK_PLAY_ENTER = 2,
		WLOG_CRL_MASK_NEWBIE_LOADING = 3,
		WLOG_CRL_MASK_NEWBIE_ENTER = 4,
		WLOG_CRL_MASK_CREATE_LOADING = 5,
		WLOG_CRL_MASK_CREATE_OK = 6,
		

		WLOG_CRL_MASK_INVALID = 100,
	};
	
	extern void WLOG_CreateRoleLoss(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, EWLOG_CRL_TYPE crltype, const char* clientname, const char* deviceid, const char* pf, const char* ip);
	extern void MDATA_ChangeRelationData(int32 zid, const char* agent, const char* userid, EWLOG_CRL_TYPE crltype, const char* clientname, const char* pf);
	extern void WLOG_ActivityPCU(int32 zid,int64 activityid,int32 num,int32 pcu);
	extern void WLOG_ActivityEnter(int32 zid,int64 activityid,int64 uid);

	enum EWLOG_BLOOD_FUSION_TYPE
	{
		WLOG_BLOOD_FUSION_MANUAL = 1,
		WLOG_BLOOD_FUSION_ONKEY = 2,
	};

	extern void WLOG_BloodFusion(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int vip,EWLOG_BLOOD_FUSION_TYPE type,int quality,int count,const char* clientType);

	enum ELOG_PLAY_TYPE
	{
		WLOG_PLAY_TYPE_BABEL,
		WLOG_PLAY_TYPE_DARKARENA,
		WLOG_PLAY_TYPE_CRYSTALCUBE,
		WLOG_PLAY_TYPE_TAROT,
		WLOG_PLAY_TYPE_DEVILTREE,
		WLOG_PLAY_TYPE_HOMEQUEST,
		WLOG_PLAY_TYPE_DRAGON,
		WLOG_PLAY_TYPE_RIDE,
		WLOG_PLAY_TYPE_GEM,
		WLOG_PLAY_TYPE_ALCHEMY,
		WLOG_PLAY_TYPE_WARLORD, // 武神争霸
		WLOG_PLAY_TYPE_SWEEP, // 扫荡
		WLOG_PLAY_TYPE_MAGIC_AWAKE, // 技能觉醒
		WLOG_PLAY_TYPE_EQUIPMENT,		// 装备
		WLOG_PLAY_TYPE_WING,			// 翅膀
		WLOG_PLAY_TYPE_BLOOD_RELIC,		// 血脉圣物
		WLOG_PLAY_TYPE_FORMATION,		// 阵法
		WLOG_PLAY_TYPE_LADDER,			// 跨服
		WLOG_PLAY_TYPE_QUEST,			//任务
	};

	enum EWLOG_PLAY_SUBTYPE
	{
		WLOG_PLAY_SUBTYPE_NONE = 0,
		WLOG_PLAY_SUBTYPE_BABEL_ENTER,
		WLOG_PLAY_SUBTYPE_BABEL_RESET,
		WLOG_PLAY_SUBTYPE_DARKARENA_ENTER,
		WLOG_PLAY_SUBTYPE_DARKARENA_RESET,
		WLOG_PLAY_SUBTYPE_CRYSTALCUBE_TURN, // 修炼
		WLOG_PLAY_SUBTYPE_CRYSTALCUBE_DRAW, // 领奖
		WLOG_PLAY_SUBTYPE_TAROT_DRAW, // 翻牌
		WLOG_PLAY_SUBTYPE_TAROT_RESET, // 刷新
		WLOG_PLAY_SUBTYPE_DEVILTREE_PICK, // 摘取
		WLOG_PLAY_SUBTYPE_DEVILTREE_ACCE, // 催熟
		WLOG_PLAY_SUBTYPE_HOMEQUEST_RESET, // 刷新任务
		WLOG_PLAY_SUBTYPE_HOMEQUEST_ACCEPT, // 接受任务
		WLOG_PLAY_SUBTYPE_HOMEQUEST_COMPLETE, // 完成任务
		WLOG_PLAY_SUBTYPE_DRAGON_DELVE, // 龙祭炼
		WLOG_PLAY_SUBTYPE_DRAGON_SAVEY, // 龙参透
		WLOG_PLAY_SUBTYPE_DRAGON_BLESS, // 龙祝福
		WLOG_PLAY_SUBTYPE_RIDE_LEVELUP, // 坐骑培养
		WLOG_PLAY_SUBTYPE_GEM_COMBINE, // 宝石合成
		WLOG_PLAY_SUBTYPE_ALCHEMY, // 点金
		WLOG_PLAY_SUBTYPE_WARLORD_CHALLENGE, // 武神争霸-挑战
		WLOG_PLAY_SUBTYPE_WARLORD_BUY, // 武神争霸-购买
		WLOG_PLAY_SUBTYPE_WARLORD_WORSHIP, // 武神争霸-膜拜
		WLOG_PLAY_SUBTYPE_SWEEP, // 扫荡
		WLOG_PLAY_SUBTYPE_DRAGON_BLESS_BATCH, // 龙一键祝福	
		WLOG_PLAY_SUBTYPE_DRAGON_DELVE_BATCH, // 龙一键祭炼
		WLOG_PLAY_SUBTYPE_DRAGON_ADD_SPEC_STAT, // 龙增加专精属性
		WLOG_PLAY_SUBTYPE_DRAGON_OPEN_GUARD, // 龙增加守护位置
		WLOG_PLAY_SUBTYPE_RIDE_LEVELUP_BATCH,// 坐骑一键培养
		WLOG_PLAY_SUBTYPE_MAGIC_AWAKE_UPGRADE,// 技能觉醒升级
		WLOG_PLAY_SUBTYPE_TAROT_DRAW_BATCH, // 一键翻牌
		WLOG_PLAY_SUBTYPE_DEVILTREE_ACCE_BATCH, // 一键催熟
		WLOG_PLAY_SUBTYPE_DEVILTREE_PICK_BATCH, // 一键摘取
		WLOG_PLAY_SUBTYPE_DRAGON_MAGIC_UPGRADE,	// 龙技能升级
		WLOG_PLAY_SUBTYPE_RIDE_RANKUP,	// 坐骑-升阶

		WLOG_PLAY_SUBTYPE_EQUIPMENT_FASHION_PARTS_ENHANCE,	// 装备-时装碎片强化
		WLOG_PLAY_SUBTYPE_GEM_COMBINE_EX, // 宝石融合
		WLOG_PLAY_SUBTYPE_RIDE_STARUP,	// 坐骑-升星
		WLOG_PLAY_SUBTYPE_DRAGON_STARUP, // 龙升星
		WLOG_PLAY_SUBTYPE_WING_LEVELUP, // 翅膀升级
		WLOG_PLAY_SUBTYPE_RIDE_ADDED,	// 坐骑-获得
		WLOG_PLAY_SUBTYPE_BLOOD_RELIC_LEVELUP, // 血脉圣物-升级
		WLOG_PLAY_SUBTYPE_EQUIPMENT_FASHION_ENHANCE, // 时装强化
		WLOG_PLAY_SUBTYPE_FORMATION_LEVELUP, // 阵法-升级
		WLOG_PLAY_SUBTYPE_LADDER_JOIN_1V1,	 // 跨服-参与
		WLOG_PLAY_SUBTYPE_LADDER_JOIN_3V3,	 // 跨服-参与
		WLOG_PLAY_SUBTYPE_LADDER_JOIN_15V15, // 跨服-参与
		WLOG_PLAY_SUBTYPE_QUEST_FINISH,	//任务完成
	};

	enum EWLOG_PALY_COMPLETE_TYPE
	{
		WLOG_PALY_COMPLETE_NONE = 0,

		WLOG_PALY_COMPLETE_DONE = 1,
		WLOG_PALY_COMPLETE_DONE_WITH_MAIL = 2,

		WLOG_PALY_COMPLETE_SUCC = 1000,
		WLOG_PALY_COMPLETE_FAIL = 2000,

	};

	extern void WLOG_Play(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int level, int vip,
		ELOG_PLAY_TYPE playtype, EWLOG_PLAY_SUBTYPE playsubtype, const char* clientType, bool ispay = false, int quality = 0, int type = 0, EWLOG_PALY_COMPLETE_TYPE completetype = WLOG_PALY_COMPLETE_NONE, const char* pf = "");

	
	extern void WLOG_DailyRecharge(int32 zid,const char* passport,const char* agent,int64 roleid,const char* rolename, int32 type, int32 layer, int32 datatype,const char* pf);

	// ----------------------------------------------------------------------------------------------

	
	extern void WLOG_SkillSnapshotSuccessful(int32 zid,const char* flag="success");
	
	extern void WLOG_EquipSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int white,int blue,int purple,int yellow,int orange,int soul);
	extern void WLOG_EquipSnapshotSuccessful(int32 zid,const char* flag="success");

	
	extern void WLOG_BabelSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int vip,int layer,const char* clientType);
	extern void WLOG_CashSnapshotSuccessful(int32 zid,const char* flag="success");

	extern void WLOG_FashionWeaponSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int fashionid,const char* fashionname,int enchantlvl);
	extern void WLOG_FashionWeaponSnapshotSuccessful(int32 zid,const char* flag="success");

	extern void WLOG_FashionClothSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int fashionid,const char* fashionname,int enchantlvl);
	extern void WLOG_FashionClothSnapshotSuccessful(int32 zid,const char* flag="success");
	
	extern void WLOG_FashionWingSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int fashionid,const char* fashionname,int fashionlvl);
	extern void WLOG_FashionWingSnapshotSuccessful(int32 zid,const char* flag="success");

	extern void WLOG_DragonSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int dragonid,int saveylvl,int itemcount,int have,const char* dragonname);
	extern void WLOG_DragonSnapshotSuccessful(int32 zid,const char* flag="success");

	extern void WLOG_RideSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int rideid,int enchantlvl,const char* ridename);
	extern void WLOG_RideSnapshotSuccessful(int32 zid,const char* flag="success");

	extern void WLOG_RelicSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int relicid,int reliclvl,const char* relicname);
	extern void WLOG_RelicSnapshotSuccessful(int32 zid,const char* flag="success");

	extern void WLOG_FormationSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int relicid,int reliclvl,const char* relicname);
	extern void WLOG_FormationSnapshotSuccessful(int32 zid,const char* flag="success");

	extern void WLOG_BloodSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int relicid,int reliclvl,int reliccolor);
	extern void WLOG_BloodSnapshotSuccessful(int32 zid,const char* flag="success");

	// ------------------------------------------------------------------------------------------------

	extern void BLOG_DTS(int64 id,const char* utfname,int level,int profession,int64 fightpoint);
	extern void BLOG_Babel(int64 id,const char* utfname,int level,int profession,int64 fightpoint,int babel_lev);

	extern void BLOG_DarkArena(int64 id,const char* utfname,int level,int profession,int64 fightpoint,int mlev,int successful);

	// 4、魔王魂域（魔王本）
	// log需求信息：玩家每次进入魔王本，记录一条log，包含信息：日期，时间，角色名，角色id，等级，职业，战斗力，副本名字，是否挑战成功
	extern void BLOG_MDungeon(int64 id,const char* utfname,int level,int profession,int64 fightpoint,int64 mapid,int successful);

	
}

#endif // _pw_ngs_qlvh_log_