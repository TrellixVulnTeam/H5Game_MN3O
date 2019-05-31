#ifndef _pw_category_
#define _pw_category_

#include "pw_def.h"

namespace db
{
	const char cst_TableCharacters[] = "characters";

	const char cst_TableGuild[] = "guilds";
	const char cst_TableGuildMember[] = "guild_members";

	const char cst_TableMail[] = "mails";
// 	const char cst_TableTeam[] = "teams";
	const char cst_TableRelation[] = "relations";
// 	const char cst_TablePet[] = "pets";
	const char cst_TableServerInfo[] = "serverinfo";
	const char cst_TableServerConfigure[] = "syscfg";
	
	const char cst_TableShop[] = "shops";
	const char cst_TableDragon[] = "dragons";
	const char cst_TableCash[] = "cash";
	const char cst_TableChats[] = "chats";

	const char cst_TableActivityGuildWar[] = "activityguildwar";
	const char cst_TableJTZ[] = "jtz";

	const char cst_TableFigthRanklist[] = "fight";
	const char cst_TableArena1V1Ranklist[] = "arena1";
	const char cst_TableArena3V3Ranklist[] = "arena3";
	const char cst_TableArena5V5Ranklist[] = "arena5";

	const char cst_TableServerAwards[] = "server_awards";
	const char cst_TableAuctionHouse[] = "auction_house";
	const char cst_TableOperations[] = "operations";

	namespace fields
	{
		struct Syscfg
		{
			enum { id,ivar1,ivar2,svar,comment, };
		};

		struct Guild
		{
			enum 
			{
				id,name,level,unuse_development,total_development,liveness,applicant_list,notice,logs,
				creator_id,creator_name,create_date,shop_level,fruiter_level,
				statue_level,depository,fruiter,hunt,hunt_opened_times,hunt_doubled,
			};
		};

		struct GuildMember
		{
			enum 
			{
				id,gid,name,title,level,profession,fight_point,
				today_devotion,week_devotion,unuse_devotion,total_devotion,last_login,
			};
		};

		struct Cash
		{
			enum
			{
				account,gold,chksum,
			};
		};

		struct Character
		{
			enum
			{
			    id,account,name,last_login,last_logout,online_seconds,profession,sex,level,exp,
				cash_gold_gifts,cash_silver,
				HP,MP,strength,intellect,vitality,energy,
				max_hp,max_mp,
				damage_phy,damage_spe,reduced_phy,reduced_spe,chance_hit,amount_hit,chance_dodge,amount_dodge,
				chance_crit,amount_crit,chance_pen,amount_pen,chance_block,amount_block,resilience,amount_resilience,
				dmg_crit,dmg_crit_amount,res_crit,res_crit_amount,
				fire_dmg,cold_dmg,light_dmg,poison_dmg,fire_res,cold_res,light_res,poison_res,
				life_per_sec,life_steal_chance,life_steal_rate,move_speed,thorns_chance,thorns_amount,beat_back_rate,gold_pickup_radius,
				dungeon_exp_bon,dragon_spi,dragon_spi_bon,exploit,exploit_bon,manual_val,manual_val_bon,eloquence,
				fit_rate,mel_dmg_red,ran_dmg_red,all_dmg_red,phy_dmg_red,spe_dmg_red,magic_dmg_bon,ext_dmg_bon,rare_dmg_bon,
				add_mp_per_sec,add_mp_beaten,add_mp_crit,add_mp_block,add_mp_dodge,
				fire_spe_res,cold_spe_res,light_spe_res,poison_spe_res,fight_point,
			    loc_stage,loc_x,loc_y,loc_z,dir_x,dir_y,dir_z,
			    astro_level,astro_exp,blessing_gift,blessing_soul,
				owned_bloodslot,owned_bloodgobm,
				blood_lv,blood_flags,dragonic,dragon_space_size,dragon_equip_size,
				divine_day,divine_last_time,divine_last_add_time,divine_cards,
				babel_rank,babel_curlv,babel_maxlv,babel_last_reset_time,babel_curr_time_consume,babel_pass_time_consume,
				bag_size,store_size,rune_size,
				owned_items,owned_quest_items,owned_store,owned_astro,owned_runes,owned_souls,owned_blood,
				owned_magics,
				owned_equips,
				owned_bless,
			    quest_taken,
				quest_complete,
				quest_daily,
				owned_auras,
				magics_cooldown,
				common_cooldown,
				guide,
				dungeonRecord,
				elite_dungeon_records,
				elite_dungeon_last_reset_time,
				owned_function,
				owned_function_delayed,
				gifts,
				arena_record,
				offline_timers,
				dragon_flute_value,
				vigor_buy_times,vigor,vigor_extra,
				alchemy_click_count,alchemy_chest_status,
				vip_exp,vip_reward_bits,vip_reward_daily,vip_temporary_level,
				ride_size,ride_curr,owned_rides,
				fatigue_time,fatigue_seconds,
				multiplayer_dungeon_enter_times_used,
				online_seconds_today,flags,
				locked_time,locked_chat_time,
				guild_quest,guild_quest_today_accepted_count,guild_quest_last_refresh_time,
				award_server_taken_id,
				sign_total,sign_month,sign_last_time,sign_curr_com_reward,sign_curr_vip_reward,
				active_today,active_total,active_reward_flag,owned_active_cnt,
				achieve_curr_reward,achieve_vip_start,achieve_vip_end,
				tarot_castle_left_free_draw,tarot_castle_draw_count,tarot_castle_last_reset_time,owned_tarot_castle,
				devil_tree_last_pick_time,owned_devil_tree,
				crystal_cube_turn_cnt,crystal_cube_turn_start_time,crystal_cube_last_draw_time,crystal_cube_type_today,owned_crystal_cube,
				server_group,
				client_setting,
				guild_shop,guild_statue_today_donate_count,guild_last_leave_time,guild_fruit_pickup_count,
				home_quest,home_quest_today_accepted_count,home_quest_last_refresh_time,
				agent,zoneid,
				dragon_hunt_free_times,dragon_hunt_gold_times,
				gamble_free_started_count,gamble_gold_started_count,gamble_started,gamble_rolled_times,gamble_rolled_silver,gamble_revived_times,
				magic_point,dark_arena,bid_items,
				completed_achievement,underway_achievement,titles,current_title,
				pay_gold_sum,got_gold_sum_fromsale,los_gold_sum_forbuy,use_gold_sum,
				babel_pass,arena_1v1_point,arena_3v3_point,arena_5v5_point,teleporters,owned_gems,
			};
		};

		struct Mail
		{
			enum
			{
			    id,mode,flag,send_date,sender_id,sender_name,receiver_id,
				subject,content,append_data,pack_items,real_items,
			};
		};

		struct Team
		{
			enum 
			{
				id,name,leader_id,tm1_id,tm1_name,tm2_id,tm2_name,
			    tm3_id,tm3_name,tm4_id,tm4_name,tm5_id,tm5_name
			     
			};
		};

		struct Relation
		{
			enum {id,type,rid,name,sex,pro,level};
		};

		struct ServerInfo
		{
			enum { serverid,lastitemid, };
		};

		struct Shop
		{
			enum { shopid, item_type, sold_count,};
		};

		struct Dragon
		{
			enum
			{
				id,uid,did,bag,bag_index,name,level,exp,
				energy,energy_max,ene_sum_consume,ene_consume,ene_recover,
				talent_max,
				growth,
				owned_magics,
				owned_talents,
				owned_statistic,
			};
		};

		struct Chat
		{
			enum { id_a,id_b,name_a,name_b,sex_a,sex_b,pro_a,pro_b,level_a,level_b,title_a,title_b,msg_a,msg_b,last_date_a,last_date_b, };
		};

		struct ActivityGuildWar
		{
			enum {guildId, curTurn, curRound, guildInfo, guildSupportList};
		};

		struct JTZ
		{
			enum { id, level, name, uname, development, liveness, flags, position, results, encourages };
		};

		struct Ranklist
		{
			enum { id, name, data };
		};

		struct ServerAwards
		{
			enum { id,dt,itemtype,itemcount,cond, };
		};

		struct AuctionHouse
		{
			enum
			{
				id,uid,uname,ubuyerid,ubuyername,current_price_gold,current_price_gold_gift,
				start_time,minutes,
				floor_price,bnp,bid,
				item_buf_ver,item_buf,
				item_type,item_name,item_level,item_color,item_class,
				attr_type,
				equip_attr_1,
				equip_attr_2,
				equip_attr_3,
				equip_attr_4,
				equip_attr_5,
				equip_attr_6,
				equip_attr_7,
				equip_attr_8,
			};
		};

		struct Operations
		{
			enum
			{
				id,uid,fn,buf,
			};
		};
	}
}

#endif //_pw_category_
