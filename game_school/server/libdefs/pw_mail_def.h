#ifndef _pw_mail_def_
#define _pw_mail_def_

#include "pw_def.h"
#include "pw_ngs_common.h"
#include "pw_item_package.h"
#include "kvorm/pw_orm_mail.h"
namespace pwngs
{
	const int cst_mail_item_max_num = 12;

	// 标题
	const int cst_mail_caption_strid_begin = 30000;

	// 事件
	const int cst_mail_subject_strid_ah_sell_success = 3000;
	const int cst_mail_subject_strid_ah_buy_success = 3001;
	const int cst_mail_subject_strid_ah_sell_expired = 3002;
	const int cst_mail_subject_strid_ah_buy_failed = 3003;
	const int cst_mail_subject_strid_ah_sell_cancel = 3004;
	const int cst_mail_subject_strid_arena_join_reward = 3005;
	const int cst_mail_subject_strid_guild_depot = 3006;
	const int cst_mail_subject_strid_guild_kicked = 3007;
	const int cst_mail_subject_strid_dts_join_reward = 3008;
	const int cst_mail_subject_strid_dts_rank_reward = 3009;
	const int cst_mail_subject_strid_arena_1v1_rank_reward = 3010;
	const int cst_mail_subject_strid_arena_1v1_season_reward = 3011;
	const int cst_mail_subject_strid_arena_fwin_reward = 3012;
	const int cst_mail_subject_strid_activity = 3013;
	const int cst_mail_subject_strid_arena_3v3_rank_reward = 3014;
	const int cst_mail_subject_strid_arena_3v3_season_reward = 3015;
	const int cst_mail_subject_strid_arena_5v5_rank_reward = 3016;
	const int cst_mail_subject_strid_arena_5v5_season_reward = 3017;
	const int cst_mail_subject_strid_item_expired = 3018;
	const int cst_mail_subject_strid_ranklist_changed = 3019;

	const int cst_mail_subject_strid_kfmz_sy = 3213;	//神佑试炼奖励
	const int cst_mail_subject_strid_kfmz_tts = 3214;	//淘汰赛邮件标题
	const int cst_mail_subject_strid_360_gm = 3216;	//360gm邮件标题
	const int cst_mail_subject_strid_holy_equip = 3023;
	const int cst_mail_subject_strid_common_activity = 3024;
	const int cst_mail_subject_strid_warlord_worship_award = 3025;
	const int cst_mail_subject_strid_warlord_rank_award = 3026;
	const int cst_mail_subject_strid_babel_reward = 3027;
	const int cst_mail_subject_strid_arena_daily_rank_reward = 3028;
	const int cst_mail_subject_strid_arena_season_rank_reward = 3030;
	const int cst_mail_subject_strid_173_giftcard_reward = 3031;
	const int cst_mail_subject_strid_sweep_reward = 3032;
	const int cst_mail_subject_strid_njtz_support_reward = 3033;
	const int cst_mail_subject_strid_njtz_winner_reward = 3034;
	const int cst_mail_subject_strid_njtz_loser_reward = 3035;
	const int cst_mail_subject_strid_njtz_rank_reward = 3036;
	const int cst_mail_subject_strid_guild_select_commander = 3037;
	const int cst_mail_subject_strid_md_winter_reward = 3040;
	const int cst_mail_subject_strid_open_auction_finish = 3041;
	const int cst_mail_subject_strid_md_longyu_reward = 3042;
	const int cst_mail_subject_strid_offline_reward = 3043;
	const int cst_mail_subject_strid_dts_substitute_reward = 3044;
	const int cst_mail_subject_strid_hot_activity_reward = 3045;
	const int cst_mail_subject_strid_send_gold = 3046; // 金币送礼
	const int cst_mail_subject_strid_7day_quest_reward = 3047;
	const int cst_mail_subject_strid_njtz_join_reward = 3048;
	const int cst_mail_subject_strid_battle_reward = 3050;
	const int cst_mail_subject_strid_lgkj_drop = 3051;
	const int cst_mail_subject_strid_lgkj_exchange = 3052;
	const int cst_mail_subject_strid_yzsl_finished = 3053;
	const int cst_mail_subject_strid_trial_land_award = 3054;
	const int cst_mail_subject_strid_recharge_award = 3055;
	const int cst_mail_subject_strid_propsfundsex_return = 3056;
	const int cst_mail_subject_strid_guild_dismiss = 3057;
	const int cst_mail_subject_strid_lgkj_reward = 3058;
	const int cst_mail_subject_strid_lgkj_signup_reward = 3059;
	const int cst_mail_subject_strid_worldboss_reward = 3100;
	const int cst_mail_subject_strid_firstdailyrecharge_award = 3201;
	const int cst_mail_subject_strid_sumdailyrecharge_award = 3202;
	const int cst_mail_subject_strid_holidayactivity_rankreward = 3203;
	const int cst_mail_subject_strid_premium_purchase_finalreward = 3204;
	const int cst_mail_subject_strid_kor_active_code = 3215; //韩国激活码礼包
	const int cst_mail_subject_strid_hac_recharge_lottery = 3216; //运营活动随机抽奖
	const int cst_mail_subject_strid_use_treasure_box = 12501;
	const int cst_mail_subject_strid_hell_trial_finished = 3207;

	const int cst_mail_subject_strid_dungeon_reward_chest_B = 3300;
	const int cst_mail_subject_strid_dungeon_reward_chest_A = 3301;
	const int cst_mail_subject_strid_dungeon_reward_chest_S = 3302;
	const int cst_mail_subject_strid_dungeon_reward_chest_first = 3303;
	const int cst_mail_subject_strid_md_devil_reward = 3051;
	const int cst_mail_subject_strid_challenge_reward = 4082;
	const int cst_mail_subject_strid_challenge_other_reward = 4080;
	const int cst_mail_subject_strid_hero_collect = 10508;
	const int cst_mail_subject_strid_dark_arena_reward = 12501;
	const int cst_mail_subject_strid_daily_sign = 3060;
	const int cst_mail_subject_strid_achievement_title = 140111;
	const int cst_mail_subject_strid_story_star_reward = 51435;	//剧情副本星级奖励

	const int cst_mail_subject_strid_njtz_win_reward = 4090;	// 帮派战冠军奖励
	const int cst_mail_subject_strid_rename = 3061;
	const int cst_mail_subject_strid_lottery = 3062; //大转盘
	const int cst_mail_subject_fire_reward = 3063; // 篝火道具奖励

	const int cst_mail_subject_redenvelope = 3067;	//红包

	const int cst_mail_subject_strid_lottery_prize = 3068; //大转盘（命运轮）
	const int cst_mail_subject_single_boss = 3069; //单人boss
	const int cst_mail_subject_run_car = 3070; //运镖
	const int cst_mail_subject_360_rebate = 3071;//360返利
	const int cst_mail_subject_360_GM = 3072;//360GM后台


	// 内容
	const int cst_mail_content_strid_system = 4000;
	const int cst_mail_content_strid_guild = 4001;
	const int cst_mail_content_strid_guild_invite = 4002;
	const int cst_mail_content_strid_guild_kicked = 4003;
	const int cst_mail_content_strid_guild_agreed = 4004;
	const int cst_mail_content_strid_relation = 4005;
	const int cst_mail_content_strid_castle = 4006;
	const int cst_mail_content_strid_activity = 4007;
	const int cst_mail_content_strid_guild_war = 4008;
	const int cst_mail_content_strid_adventure = 4009;
	const int cst_mail_content_strid_ah_buy_success = 4010;
	const int cst_mail_content_strid_ah_sell_success = 4011;
	const int cst_mail_content_strid_ah_sell_expired = 4012;
	const int cst_mail_content_strid_ah_buy_failed = 4013;
	const int cst_mail_content_strid_ah_sell_cancel = 4014;
	const int cst_mail_content_strid_guild_depot = 4015;
	const int cst_mail_content_strid_dts_rank_reward = 4016;
	const int cst_mail_content_strid_dts_join_reward = 4017;
	const int cst_mail_content_strid_item_expired = 4018;
	const int cst_mail_content_strid_ranklist_fightpoint_changed = 4019;
	const int cst_mail_content_strid_ranklist_guild_changed = 4020;
	const int cst_mail_content_strid_ranklist_arena1v1_changed = 4021;
	const int cst_mail_content_strid_ranklist_arena3v3_changed = 4022;
	const int cst_mail_content_strid_ranklist_arena5v5_changed = 4023;
	const int cst_mail_content_strid_ranklist_level_changed = 4024;
	const int cst_mail_content_strid_ranklist_blood_changed = 4025;
	const int cst_mail_content_strid_ranklist_achievement_changed = 4026;
	const int cst_mail_content_strid_holy_equip = 4027;
	const int cst_mail_content_strid_common_activity = 4028;
	const int cst_mail_content_strid_warlord_worship_award = 4029;
	const int cst_mail_content_strid_warlord_rank_award = 4030;
	const int cst_mail_content_strid_babel_reward = 4031;
	const int cst_mail_content_strid_arena_rank_reward_1 = 4032;
	const int cst_mail_content_strid_arena_rank_reward_2 = 4033;
	const int cst_mail_content_strid_arena_rank_reward_3 = 4034;
	const int cst_mail_content_strid_arena_rank_reward_4 = 4035;
	const int cst_mail_content_strid_arena_rank_reward_5 = 4036;
	const int cst_mail_content_strid_arena_rank_reward_6 = 4037;
	const int cst_mail_content_strid_arena_rank_reward_7 = 4038;
	const int cst_mail_content_strid_arena_rank_reward = 4039;
	const int cst_mail_content_strid_173_giftcard_reward = 4040;
	const int cst_mail_content_strid_sweep_reward = 4041;
	const int cst_mail_content_strid_njtz_support_reward = 4042;
	const int cst_mail_content_strid_njtz_winner_reward = 4043;
	const int cst_mail_content_strid_njtz_loser_reward = 4044;
	const int cst_mail_content_strid_njtz_rank_reward = 4045;
	const int cst_mail_content_strid_md_winter_reward = 4046;
	const int cst_mail_content_strid_open_auction_finish = 4047;
	const int cst_mail_content_strid_guild_select_commander = 4048;
	const int cst_mail_content_strid_guild_kicked_commander = 4049;
	const int cst_mail_content_strid_md_longyu_reward = 4050;
	const int cst_mail_content_strid_offline_reward = 4051;
	const int cst_mail_content_strid_dts_substitute_reward = 4052;
	const int cst_mail_content_strid_hot_activity_reward = 4053;
	const int cst_mail_content_strid_7day_quest_reward = 4054;
	const int cst_mail_content_strid_njtz_join_reward = 4055;
	const int cst_mail_content_strid_hot_activity_hv_recharge = 4056; //横纵充值
	const int cst_mail_content_strid_battle_reward = 4060;
	const int cst_mail_content_strid_send_gold = 4070; // 金币送礼
	const int cst_mail_content_strid_lgkj_drop = 4071;
	const int cst_mail_content_strid_award = 4072;
	const int cst_mail_content_strid_lgkj_exchange = 4073;
	const int cst_mail_content_strid_lgkj_exchange2 = 4074;
	const int cst_mail_content_strid_yzsl_finished = 4075;
	const int cst_mail_content_strid_trial_land_award = 4076;
	const int cst_mail_context_strid_propsfundsex_return = 4077;
	const int cst_mail_content_strid_guild_dismiss = 4078;
	const int cst_mail_content_strid_lgkj_reward = 4079;
	const int cst_mail_content_strid_lgkj_signup_reward = 4080;
	
	const int cst_mail_content_strid_njtz_win_reward = 4091;	// 帮派战冠军奖励

	const int cst_mail_content_strid_worldboss_reward = 4100;

	const int cst_mail_content_strid_firstdailyrecharge_reward = 4201;
	const int cst_mail_content_strid_sumdailyrecharge_reward = 4203;
	const int cst_mail_content_strid_holidayactivity_rankreward = 4204;

	const int cst_mail_content_strid_premium_purchase_finalreward = 4205;
	const int cst_mail_content_strid_kor_active_code = 4248;// 韩国激活码礼包
	const int cst_mail_content_strid_360_gm = 4251;// 360
	const int cst_mail_content_strid_use_treasure_box = 60001;

	const int cst_mail_content_strid_hell_trial_finished = 4207;
	const int cst_mail_content_strid_md_devil_reward = 60001;
	const int cst_mail_content_strid_challenge_reward = 4081;
	const int cst_mail_content_strid_hero_collect = 60001;
	const int cst_mail_content_strid_daily_sign = 60001;
	const int cst_mail_content_strid_dark_arena_reward = 60001;
	const int cst_mail_content_strid_achievement_title = 140110;
	const int cst_mail_content_strid_story_star_reward = 51436;	//剧情副本星级奖励
	const int cst_mail_content_strid_rename = 4101;

	const int cst_mail_content_strid_kfmz_sy = 4244;	//神佑邮件内容
	const int cst_mail_content_strid_kfmz_tts = 4245;	//淘汰赛邮件内容
	const int cst_mail_content_strid_lottery = 4246;	//大转盘内容
	const int cst_mail_content_strid_fire_reward = 4247; // 篝火道具奖励

	const int cst_mail_content_strid_redenvelope = 4249; // 红包

	const int cst_mail_content_strid_lottery_prize = 4250;	//大转盘内容（命运轮）

	const int cst_mail_content_strid_single_boss = 4252;	//单人BOSS

	const int cst_mail_content_strid_hac_recharge_lottery = 4253; //从冰火移过来
	const int cst_mail_content_strid_run_car = 4254; //运镖
	const int cst_mail_content_360_rebate = 4255;//360返利

	// 邮件类型
	enum EMailMode
	{
		MAIL_MODE_SYSTEM = 0,					// 系统通用
		MAIL_MODE_SYSTEM_SEND,					// 系统发送邮件

		MAIL_MODE_GUILD = 100,					// 联盟通用
		MAIL_MODE_GUILD_INVITE,					// 联盟邀请
		MAIL_MODE_GUILD_DEPOT,					// 分配宝箱
		MAIL_MODE_GUILD_KICKED,					// 开除会员
		MAIL_MODE_GUILD_SELECT_COMMANDER,		// 弹劾统帅
		
		MAIL_MODE_RELATION = 200,				// 好友通用
		MAIL_MODE_CASTLE = 300,					// 城堡通用
		MAIL_MODE_ACTIVITY = 400,				// 活动通用
		MAIL_MODE_ADVENTURE = 500,				// 探险通用
		MAIL_MODE_DIVINE = 600,					// 占卜通用

		MAIL_MODE_CHARGE = 700,					// 充值通用
		MAIL_MODE_CHARGE_FEEDBACK,				// 充值回馈
		
		MAIL_MODE_CUSTOMER_SERVICE = 800,		// 部门客服接口
		
		MAIL_MODE_ARENA = 900,					// 竞技场
		MAIL_MODE_ARENA_JOIN_REWARD,			// 竞技场参赛奖励
		MAIL_MODE_ARENA_RANK_REWARD,			// 竞技场排名奖励
		MAIL_MODE_ARENA_SEASON_REWARD,			// 竞技场赛季奖励
		MAIL_MODE_ARENA_FWIN_REWARD,			// 竞技场首胜奖励
		
		MAIL_MODE_GIFT = 1000,					// 礼包通用
		MAIL_MODE_GIFT_NOVICE,					// 新手礼包
		MAIL_MODE_GIFT_MEDIA,					// 媒体礼包
		MAIL_MODE_GIFT_FESTIVAL,				// 节日礼包
		MAIL_MODE_GIFT_CONSUMER_FEEDBACK,		// 消费回馈

		MAIL_MODE_AUCTION_HOUSE = 1100,			// 拍卖行
		MAIL_MODE_AUCTION_HOUSE_BUY_SUCCESS,	// 竞拍成功
		MAIL_MODE_AUCTION_HOUSE_BUY_FAILED,		// 竞拍失败
		MAIL_MODE_AUCTION_HOUSE_SELL_EXPIRED,	// 寄拍到期
		MAIL_MODE_AUCTION_HOUSE_SELL_SUCCESS,	// 寄拍出售
		MAIL_MODE_AUCTION_HOUSE_SELL_CANCEL,	// 寄拍取消

		MAIL_MODE_DTS = 1200,					// 大逃杀
		MAIL_MODE_DTS_JOIN_REWARD,				// 大逃杀参赛奖励
		MAIL_MODE_DTS_RANK_REWARD,				// 大逃杀排名奖励
		MAIL_MODE_DTS_SUBSTITUTE_REWARD,		// 大逃杀替身经验奖励

		MAIL_MODE_RANKLIST = 1300,				// 排行榜
		MAIL_MODE_DUNGEON_PRIZE = 1400,			// 副本奖励
		MAIL_MODE_HOLY_EQUIP	= 1500,			// 神装活动
		MAIL_MODE_COMMON_ACTIVITY	= 1600,		// 通用活动

		MAIL_MODE_WARLORD = 1700,				// 武神争霸
		MAIL_MODE_WARLORD_WORSHIP_AWARD,		// 武神争霸膜拜奖励
		MAIL_MODE_WARLORD_RANK_AWARD,			// 武神争霸排名奖励

		MAIL_MODE_BABEL = 1800,					// 通天塔

		MAIL_MODE_SWEEP = 1900,					// 扫荡奖励

		MAIL_MODE_NJTZ = 2000,					// 公会战
		MAIL_MODE_NJTZ_SUPPORT_REWARD,			// 公会战助威奖励
		MAIL_MODE_NJTZ_WINNER_REWARD,			// 公会战获胜奖励
		MAIL_MODE_NJTZ_LOSER_REWARD,			// 公会战失败奖励
		MAIL_MODE_NJTZ_RANK_REWARD,				// 公会战前五名奖励
		MAIL_MODE_NJTZ_JOIN_REWARD,				// 公会战积分不为零奖励

		MAIL_MODE_MD_WINTER = 2100,				// 凛冬修炼场

		MAIL_MODE_OPEN_AUCTION = 2200,			// 开服竞拍
		MAIL_MODE_OPEN_AUCTION_FINISH,			// 开服竞拍成功


		MAIL_MODE_MD_LONGYU = 2300,				// 龙域守护

		MAIL_MODE_OFFLINE_REWARD = 2400,		// 离线奖励

		MAIL_MODE_HOT_ACTIVITY_REWARD = 2500,	// 运营活动奖励

		MAIL_MODE_7DAY_QUEST = 2600,			// 七日任务奖励

		MAIL_MODE_BATTLE = 3000,				// 战场系统
		MAIL_MODE_BATTLE_REWARD,				// 战场奖励

		MAIL_MODE_SEND_GOLD = 3500,				// 金币送礼(韩服)
		MAIL_MODE_LGKJ = 3600,					// 龙骨矿井
		MAIL_MODE_LGKJ_REWARD,					// 龙骨矿井替身奖励

		MAIL_MODE_YZSL = 3700,					// 勇者试炼

		MAIL_MODE_TRIAL_LAND = 3800,			// 试炼之地
		MAIL_MODE_WORLD_BOSS = 3900,			// 世界BOSS

		

		MAIL_MODE_FIRST_DAILY_RECHARGE = 4100,	// 每日首冲

	

		MAIL_MODE_SUN_DAILY_RECHARGE = 4200,	// 每日累充

		MAIL_MODE_PREMIUM_PURCHASE = 4300,	// 超值乐购

		MAIL_MODE_HELL_TRIAL = 4400,			// 地狱试炼
		MAIL_MODE_LOTTERY = 4500,			// 大转盘
		MAIL_MODE_REDENVELOP = 4600,	//红包

		MAIL_MODE_LOTTERY_PRIZE = 4700,	// 大转盘(命运轮)

		MAIL_MODE_SINGLE_BOSS = 4800,	//单人boss

		MAIL_MODE_KFMZ_SY		= 4900,	//神佑试炼发件人,对应serverstr[30049]
		MAIL_MODE_KFMZ_TTS		= 5000,	//淘汰赛发件人,对应serverstr[30050]
		MAIL_MODE_KOR           = 5200,  //韩国激活码发邮件,对应serverstr[30052]
		MAIL_MODE_360          = 5300,//360发邮件
		MAIL_MODE_RUNCAR	 = 5400,//30054
		MAIL_MODE_360_REBATE = 5500,//360返利
		
		
	};

	// 邮件标记
	enum EMailFlag
	{
		MAIL_FLAG_UNRECV = 0,		// 未读
		MAIL_FLAG_RECVED,			// 已读 未领取附件
		MAIL_FLAG_RECVED_REWARD,	// 已读 已领取附件
		MAIL_FLAG_DELETED,			// 已删除
	};

	typedef orm::Mail SMail;
/*
	// 邮件正文
	struct SMailBody
	{
		char subject[64];
		char content[256];
	};

	// 邮件附件
	struct SMailAtts
	{
		SPackItem pack_items[20];
		SItem real_items[1];
	};

	// 完整邮件
	struct SMail
	{
		sint32 mode;
		sint64 date;
		sint64 sender_id;
		sint64 target_id;
		char sender_name[max_name_len];
		char append_data[64];

		SMailBody body;
		SMailAtts atts;
	};
*/
}

#endif //_pw_mail_def_
