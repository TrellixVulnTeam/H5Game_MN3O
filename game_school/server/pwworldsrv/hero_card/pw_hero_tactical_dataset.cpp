#include "pw_hero_tactical_dataset.h"
#include "pw_logger.h"
namespace pwngs
{
	HeroTacticalDataset g_objHeroTacticalDataset;
	int HeroTacticalDataset::Load(const std::string& path)
	{
		pwconf::HeroAssistancePos heroTacticalSlot;

		if (!heroTacticalSlot.LoadFrom(path + "pwconf_HeroAssistancePos.csv"))
		{
			gErrorStream("Error LoadHeroTacticalSlot " << path + "pwconf_HeroAssistancePos.csv");
			pwassertn(false && "Error,LoadHeroTacticalSlot");
			return -1;
		}

		for (size_t i = 0; i < heroTacticalSlot.Count(); ++i)
		{
			SHeroTacticalSlot& type = heroTacticalSlot.Get(i);
			pwassertop(m_mapTacticalSlotDatas.insert(std::make_pair(type.id, type)).second, continue);
		}

		LoadHeroTacticalSlotLev(path);

		return 0;
	}

	int HeroTacticalDataset::LoadHeroTacticalSlotLev(const std::string& path)
	{
		pwconf::HeroAssistancePosLvl heroTacticalSlotLev;

		if (!heroTacticalSlotLev.LoadFrom(path + "pwconf_HeroAssistancePosLvl.csv"))
		{
			gErrorStream("Error LoadHeroTacticalSlotLev " << path + "pwconf_HeroAssistancePosLvl.csv");
			pwassertn(false && "Error,LoadHeroTacticalSlotLev");
			return -1;
		}

		for (size_t i = 0; i < heroTacticalSlotLev.Count(); ++i)
		{
			SHeroTacticalSlotLev& type = heroTacticalSlotLev.Get(i);
			pwassertop(m_mapTacticalSlotLevDatas.insert(std::make_pair(type.id, type)).second, continue);
		}

		return 0;
	}

	int HeroTacticalDataset::TacticalSlotOpenCosts(int32 slot_id, int32 open_type, std_unordered_map<int32, int32>& itemcost)
	{
		for (HeroTacticalSlotDatas::iterator it_slot = m_mapTacticalSlotDatas.begin(); it_slot != m_mapTacticalSlotDatas.end(); ++it_slot)
		{
			if (it_slot->first != slot_id)
			{
				continue;
			}

			if (open_type == TACTICAL_TYPE_COMMON)
			{
				if (it_slot->second.activate_1_item_1[0] != 0 && it_slot->second.activate_1_item_1[1] != 0)
				{
					std_unordered_map<int32, int32>::iterator pItem = itemcost.find(it_slot->second.activate_1_item_1[0]);
					if (pItem == itemcost.end())
					{
						itemcost.insert(std::make_pair(it_slot->second.activate_1_item_1[0], it_slot->second.activate_1_item_1[1]));
					}
					else
					{
						pItem->second += it_slot->second.activate_1_item_1[1];
					}
				}

				if (it_slot->second.activate_1_item_2[0] != 0 && it_slot->second.activate_1_item_2[1] != 0)
				{
					std_unordered_map<int32, int32>::iterator pItem = itemcost.find(it_slot->second.activate_1_item_2[0]);
					if (pItem == itemcost.end())
					{
						itemcost.insert(std::make_pair(it_slot->second.activate_1_item_2[0], it_slot->second.activate_1_item_2[1]));
					}
					else
					{
						pItem->second += it_slot->second.activate_1_item_2[1];
					}
				}

				if (it_slot->second.activate_1_item_3[0] != 0 && it_slot->second.activate_1_item_3[1] != 0)
				{
					std_unordered_map<int32, int32>::iterator pItem = itemcost.find(it_slot->second.activate_1_item_3[0]);
					if (pItem == itemcost.end())
					{
						itemcost.insert(std::make_pair(it_slot->second.activate_1_item_3[0], it_slot->second.activate_1_item_3[1]));
					}
					else
					{
						pItem->second += it_slot->second.activate_1_item_3[1];
					}
				}
			}
			else if (open_type == TACTICAL_TYPE_SPECIAL)
			{
				if (it_slot->second.activate_2_item_1[0] != 0 && it_slot->second.activate_2_item_1[1] != 0)
				{
					std_unordered_map<int32, int32>::iterator pItem = itemcost.find(it_slot->second.activate_2_item_1[0]);
					if (pItem == itemcost.end())
					{
						itemcost.insert(std::make_pair(it_slot->second.activate_2_item_1[0], it_slot->second.activate_2_item_1[1]));
					}
					else
					{
						pItem->second += it_slot->second.activate_2_item_1[1];
					}
				}

				if (it_slot->second.activate_2_item_2[0] != 0 && it_slot->second.activate_2_item_2[1] != 0)
				{
					std_unordered_map<int32, int32>::iterator pItem = itemcost.find(it_slot->second.activate_2_item_2[0]);
					if (pItem == itemcost.end())
					{
						itemcost.insert(std::make_pair(it_slot->second.activate_2_item_2[0], it_slot->second.activate_2_item_2[1]));
					}
					else
					{
						pItem->second += it_slot->second.activate_2_item_2[1];
					}
				}

				if (it_slot->second.activate_2_item_3[0] != 0 && it_slot->second.activate_2_item_3[1] != 0)
				{
					std_unordered_map<int32, int32>::iterator pItem = itemcost.find(it_slot->second.activate_2_item_3[0]);
					if (pItem == itemcost.end())
					{
						itemcost.insert(std::make_pair(it_slot->second.activate_2_item_3[0], it_slot->second.activate_2_item_3[1]));
					}
					else
					{
						pItem->second += it_slot->second.activate_2_item_3[1];
					}
				}
			}
		}
		return 0;
	}

	bool HeroTacticalDataset::IsMaxLevelSlot(int32 slot_id, int32 slot_level)
	{
		for (HeroTacticalSlotDatas::iterator it_slot = m_mapTacticalSlotDatas.begin(); it_slot != m_mapTacticalSlotDatas.end(); ++it_slot)
		{
			if (it_slot->first != slot_id)
			{
				continue;
			}

			if (slot_level >= it_slot->second.max_lvl)
			{
				return true;
			}
		}

		return false;
	}

	int HeroTacticalDataset::UplevelSlotCosts(int32 slot_level, std_unordered_map<int32, int32>& itemcost)
	{
		for (HeroTacticalSlotLevDatas::iterator it_level = m_mapTacticalSlotLevDatas.begin(); it_level != m_mapTacticalSlotLevDatas.end(); ++it_level)
		{
			if (it_level->first != slot_level)
			{
				continue;
			}

			if (it_level->second.Lvlup_item_1[0] != 0 && it_level->second.Lvlup_item_1[1] != 0)
			{
				std_unordered_map<int32, int32>::iterator pFindItem = itemcost.find(it_level->second.Lvlup_item_1[0]);
				if (pFindItem == itemcost.end())
				{
					itemcost.insert(std::make_pair(it_level->second.Lvlup_item_1[0], it_level->second.Lvlup_item_1[1]));
				}
				else
				{
					pFindItem->second += it_level->second.Lvlup_item_1[1];
				}
			}

			if (it_level->second.Lvlup_item_2[0] != 0 && it_level->second.Lvlup_item_2[1] != 0)
			{
				std_unordered_map<int32, int32>::iterator pFindItem = itemcost.find(it_level->second.Lvlup_item_2[0]);
				if (pFindItem == itemcost.end())
				{
					itemcost.insert(std::make_pair(it_level->second.Lvlup_item_2[0], it_level->second.Lvlup_item_2[1]));
				}
				else
				{
					pFindItem->second += it_level->second.Lvlup_item_2[1];
				}
			}

			if (it_level->second.Lvlup_item_3[0] != 0 && it_level->second.Lvlup_item_3[1] != 0)
			{
				std_unordered_map<int32, int32>::iterator pFindItem = itemcost.find(it_level->second.Lvlup_item_3[0]);
				if (pFindItem == itemcost.end())
				{
					itemcost.insert(std::make_pair(it_level->second.Lvlup_item_3[0], it_level->second.Lvlup_item_3[1]));
				}
				else
				{
					pFindItem->second += it_level->second.Lvlup_item_3[1];
				}
			}
			break;
		}

		return 0;
	}

	float HeroTacticalDataset::GetSlotLevelPercentage(int32 slot_level)
	{
		for (HeroTacticalSlotLevDatas::iterator it_level = m_mapTacticalSlotLevDatas.begin(); it_level != m_mapTacticalSlotLevDatas.end(); ++it_level)
		{
			if (it_level->first != slot_level)
			{
				continue;
			}

			return it_level->second.lvl_percentage;
		}

		return -1;
	}

}