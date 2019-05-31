#ifndef _pw_item_package_
#define _pw_item_package_

#include "pw_def.h"

PreDefineOrm(DPackItem);

namespace pwngs
{
	// 杂货物品定义（非背包物品） ！！！注意：增删该列表需通知客户端同步
	enum EItemMiscTypeId
	{
		ITEM_MISC_TYPE_ID_SILVER = 100001,				// 金币（银币）
		ITEM_MISC_TYPE_ID_EXP = 100002,					// 经验
		ITEM_MISC_TYPE_ID_GOLD = 100003,				// 元宝（金币）
		ITEM_MISC_TYPE_ID_GOLD_GIFTS = 100004,			// 礼券（赠币）
		ITEM_MISC_TYPE_ID_REPUTATION = 100005,			// 声望
		ITEM_MISC_TYPE_ID_VIGOR = 100006,				// 体力
		ITEM_MISC_TYPE_ID_FRIENDLINESS = 100007,		// 友好度
		ITEM_MISC_TYPE_ID_DEVELOPMENT = 100008,			// 繁荣度
		ITEM_MISC_TYPE_ID_LILIAN = 100010,				// 历练值
		ITEM_MISC_TYPE_ID_GUILD_DEVOTION = 100011,		// 公会贡献度
		ITEM_MISC_TYPE_ID_GUILD_DEVELOPMENT = 100012,	// 公会建设度
		ITEM_MISC_TYPE_ID_DRAGON_FLUTE = 100013,		// 龙笛累积值
		ITEM_MISC_TYPE_ID_MAGIC_POINT = 100014,			// 技能点
		ITEM_MISC_TYPE_ID_HONOR = 100019,				// 荣誉点
		ITEM_MISC_TYPE_ID_AURA = 100020,				// 光环
		ITEM_MISC_TYPE_ID_ARENA_POINT = 100021,			// 竞技点
		ITEM_MISC_TYPE_ID_MEDAL_POINT = 100022,			// 武神勋章
		ITEM_MISC_TYPE_ID_ARENA_MEDAL = 100023,			// 竞技勋章
		ITEM_MISC_TYPE_ID_AWAKE_POINT = 100024,			// 觉醒点
		ITEM_MISC_TYPE_ID_BATTLE_POINT = 100025,		// 密林印记
		ITEM_MISC_TYPE_ID_CRYSTAL_POINT = 100026,		// 水晶硬币
		ITEM_MISC_TYPE_ID_TRIAL_POINT = 100027,			// 试炼硬币
		ITEM_MISC_TYPE_ID_DTS = 400024,					// 星魄（古墓迷宫）
		ITEM_MISC_TYPE_ID_VIP_EXP = 400101,					// vip经验
	};

#pragma pack(push,1)

	// 包装的物品
	struct SPackItem
	{
		sint32 tid;
		sint32 count;
	};

#pragma pack(pop)

	typedef std::vector<SPackItem> CollectionPackItemsT;
	typedef std::vector<int32> CollectionPackAurasT;

	extern void SPackItemToDPackItem(const SPackItem& src,orm::DPackItem& dst);
	extern void DPackItemToSPackItem(const orm::DPackItem& src,SPackItem& dst);

	// 一个物品包
	struct SItemPackage
	{
		sint32 silver;
		sint32 exp;
		sint32 vipexp;
		sint32 gold;
		sint32 gold_gifts;
		sint32 reputation;
		sint32 vigor;
		sint32 friendliness;
		sint32 development;
		sint32 guild_devotion;
		sint32 guild_development;
		sint32 dragon_flute;
		sint32 magic_point;
		sint32 honor;
		sint32 arena_point;
		sint32 medal_point;
		sint32 arena_medal;
		sint32 awake_point;
		sint32 battle_point;
		sint32 crystal_point;
		sint32 trial_point;
		sint32 lilian;
		CollectionPackItemsT items;
		CollectionPackAurasT auras;
		
		sint32 cash_reason;
		sint32 item_reason;
		sint32 exp_reason;
		sint32 magic_point_reason;
		sint32 awake_point_reason;
		uint64 item_flags;
		sint32 item_container;
		sint32 item_context;

		SItemPackage()
			: silver(0)
			, exp(0)
			, vipexp(0)
			, gold(0)
			, gold_gifts(0)
			, reputation(0)
			, vigor(0)
			, friendliness(0)
			, development(0)
			, guild_devotion(0)
			, guild_development(0)
			, dragon_flute(0)
			, magic_point(0)
			, honor(0)
			, arena_point(0)
			, medal_point(0)
			, arena_medal(0)
			, awake_point(0)
			, battle_point(0)
			, crystal_point(0)
			, trial_point(0)
			, lilian(0)
			, cash_reason(0)
			, item_reason(0)
			, exp_reason(0)
			, magic_point_reason(0)
			, awake_point_reason(0)
			, item_flags(0)
			, item_container(0)
			, item_context(0)
		{
		}

		void SetCashReason(sint32 r) { cash_reason = r; }
		void SetItemReason(sint32 r) { item_reason = r; }
		void SetExpReason(sint32 r) { exp_reason = r; }
		void SetMagicPointReason(sint32 r) { magic_point_reason = r; }
		void SetAwakePointReason(sint32 r) { awake_point_reason = r; }
		void SetItemFlags(uint64 flags) { item_flags = flags; }
		void SetItemContainer(sint32 r) { item_container = r; }
		void SetItemContext(sint32 r) { item_context = r; }

		int ParseFromPackItems(const CollectionPackItemsT& vtItems)
		{
			for(CollectionPackItemsT::const_iterator iter = vtItems.begin(); iter != vtItems.end(); ++iter)
			{
				if(iter->tid <= 0 || iter->count <= 0)
					continue;
				
				this->ParseFromPackItem(*iter);
			}
			return 0;
		}
		
		int ParseFromPackItem(const SPackItem& item)
		{
			if(item.tid <= 0 || item.count <= 0)
				return -1;
	
			switch(item.tid)
			{
			case ITEM_MISC_TYPE_ID_SILVER:
				silver += item.count;
				break;
			case ITEM_MISC_TYPE_ID_EXP:
				exp += item.count;
				break;
			case ITEM_MISC_TYPE_ID_VIP_EXP:
				vipexp += item.count;
				break;
			case ITEM_MISC_TYPE_ID_GOLD:
				gold += item.count;
				break;
			case ITEM_MISC_TYPE_ID_GOLD_GIFTS:
				gold_gifts += item.count;
				break;
			case ITEM_MISC_TYPE_ID_REPUTATION:
				reputation += item.count;
				break;
			case ITEM_MISC_TYPE_ID_VIGOR:
				vigor += item.count;
				break;
			case ITEM_MISC_TYPE_ID_FRIENDLINESS:
				friendliness += item.count;
				break;
			case ITEM_MISC_TYPE_ID_DEVELOPMENT:
				development += item.count;
				break;
			case ITEM_MISC_TYPE_ID_LILIAN:
				lilian += item.count;
				break;
			case ITEM_MISC_TYPE_ID_GUILD_DEVOTION:
				guild_devotion += item.count;
				break;
			case ITEM_MISC_TYPE_ID_GUILD_DEVELOPMENT:
				guild_development += item.count;
				break;
			case ITEM_MISC_TYPE_ID_DRAGON_FLUTE:
				dragon_flute += item.count;
				break;
			case ITEM_MISC_TYPE_ID_MAGIC_POINT:
				magic_point += item.count;
				break;
			case ITEM_MISC_TYPE_ID_HONOR:
				honor += item.count;
				break;
			case ITEM_MISC_TYPE_ID_AURA:
				auras.push_back(item.count);
				break;
			case ITEM_MISC_TYPE_ID_ARENA_POINT:
				arena_point += item.count;
				break;
			case ITEM_MISC_TYPE_ID_MEDAL_POINT:
				medal_point += item.count;
				break;
			case ITEM_MISC_TYPE_ID_ARENA_MEDAL:
				arena_medal += item.count;
				break;
			case ITEM_MISC_TYPE_ID_AWAKE_POINT:
				awake_point += item.count;
				break;
			case ITEM_MISC_TYPE_ID_BATTLE_POINT:
				battle_point += item.count;
				break;
			case ITEM_MISC_TYPE_ID_CRYSTAL_POINT:
				crystal_point += item.count;
				break;
			case ITEM_MISC_TYPE_ID_TRIAL_POINT:
				trial_point += item.count;
				break;
			default:
				items.push_back(item);
				break;
			}
			return 0;
		}

		int SerializeToPackItems(CollectionPackItemsT& vtItems) const 
		{
			if(silver > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_SILVER,silver};
				vtItems.push_back(item);
			}

			if(exp > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_EXP,exp};
				vtItems.push_back(item);
			}

			if (vipexp > 0)
			{
				SPackItem item = { ITEM_MISC_TYPE_ID_EXP, vipexp };
				vtItems.push_back(item);
			}

			if(gold > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_GOLD,gold};
				vtItems.push_back(item);
			}

			if(gold_gifts > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_GOLD_GIFTS,gold_gifts};
				vtItems.push_back(item);
			}

			if(reputation > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_REPUTATION,reputation};
				vtItems.push_back(item);
			}

			if(vigor > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_VIGOR,vigor};
				vtItems.push_back(item);
			}

			if(friendliness > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_FRIENDLINESS,friendliness};
				vtItems.push_back(item);
			}
			
			if(development > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_DEVELOPMENT,development};
				vtItems.push_back(item);
			}
			
			if(lilian > 0)
			{
				SPackItem item = { ITEM_MISC_TYPE_ID_LILIAN, lilian };
				vtItems.push_back(item);
			}

			if(guild_devotion > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_GUILD_DEVOTION,guild_devotion};
				vtItems.push_back(item);
			}
			
			if(guild_development > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_GUILD_DEVELOPMENT,guild_development};
				vtItems.push_back(item);
			}

			if(dragon_flute > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_DRAGON_FLUTE,dragon_flute};
				vtItems.push_back(item);
			}

			if(magic_point > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_MAGIC_POINT,magic_point};
				vtItems.push_back(item);
			}

			if(honor > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_HONOR,honor};
				vtItems.push_back(item);
			}

			if(auras.size() > 0)
			{
				for(size_t i = 0; i < auras.size(); ++i)
				{
					SPackItem item = {ITEM_MISC_TYPE_ID_AURA,auras[i] };
					vtItems.push_back(item);
				}
			}

			if(arena_point > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_ARENA_POINT,arena_point};
				vtItems.push_back(item);
			}

			if(medal_point > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_MEDAL_POINT,medal_point};
				vtItems.push_back(item);
			}
			
			if(arena_medal > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_ARENA_MEDAL,arena_medal};
				vtItems.push_back(item);
			}

			if(awake_point > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_AWAKE_POINT,awake_point};
				vtItems.push_back(item);
			}

			if(battle_point > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_BATTLE_POINT,battle_point};
				vtItems.push_back(item);
			}
			
			if(crystal_point > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_CRYSTAL_POINT,crystal_point};
				vtItems.push_back(item);
			}
			if(trial_point > 0)
			{
				SPackItem item = {ITEM_MISC_TYPE_ID_TRIAL_POINT,trial_point};
				vtItems.push_back(item);
			}

			if(!items.empty())
			{
				vtItems.insert(vtItems.end(),items.begin(),items.end());
			}
			return 0;
		}
	};
}
#endif //_pw_item_package_
