#include "pwconf_HeroAssistancePosLvl.h"
#include "pw_csv.h"
#include "tokenizer.h"
#include "pw_utils.h"
#include "pw_logger.h"

namespace pwconf
{
	bool HeroAssistancePosLvl::LoadFrom(const char* filename)
	{
		pwutils::CSVReader csv;
		if(csv.load(filename) != 0)
			return false;
		size_t index_id = csv.index("id",1);
		pwassertn(index_id != (size_t)-1);
		
		size_t index_lvl_percentage = csv.index("lvl_percentage",1);
		pwassertn(index_lvl_percentage != (size_t)-1);
		
		size_t index_Lvlup_item_1 = csv.index("Lvlup_item_1",1);
		pwassertn(index_Lvlup_item_1 != (size_t)-1);
		
		size_t index_Lvlup_item_2 = csv.index("Lvlup_item_2",1);
		pwassertn(index_Lvlup_item_2 != (size_t)-1);
		
		size_t index_Lvlup_item_3 = csv.index("Lvlup_item_3",1);
		pwassertn(index_Lvlup_item_3 != (size_t)-1);
		
		
		for(size_t row = 3; row < csv.count(); ++row)
		{
			SHeroAssistancePosLvl conf;
			conf.id = csv.get_i32(row,index_id);
			conf.lvl_percentage = (float)csv.get_dec(row,index_lvl_percentage);
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_Lvlup_item_1);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 2|| vals.empty());
				for(size_t i = 0; i < 2; ++i)
					conf.Lvlup_item_1[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_Lvlup_item_2);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 2|| vals.empty());
				for(size_t i = 0; i < 2; ++i)
					conf.Lvlup_item_2[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_Lvlup_item_3);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 2|| vals.empty());
				for(size_t i = 0; i < 2; ++i)
					conf.Lvlup_item_3[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			m_vtConfigures.push_back(conf);
		}
		return true;
	}
	
	SHeroAssistancePosLvl& HeroAssistancePosLvl::Get(size_t row)
	{
		return m_vtConfigures.at(row);
	}
}
