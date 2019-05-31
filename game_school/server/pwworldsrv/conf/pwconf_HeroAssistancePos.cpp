#include "pwconf_HeroAssistancePos.h"
#include "pw_csv.h"
#include "tokenizer.h"
#include "pw_utils.h"
#include "pw_logger.h"

namespace pwconf
{
	bool HeroAssistancePos::LoadFrom(const char* filename)
	{
		pwutils::CSVReader csv;
		if(csv.load(filename) != 0)
			return false;
		size_t index_id = csv.index("id",1);
		pwassertn(index_id != (size_t)-1);
		
		size_t index_postion_initial = csv.index("postion_initial",1);
		pwassertn(index_postion_initial != (size_t)-1);
		
		size_t index_activate_1_item_1 = csv.index("activate_1_item_1",1);
		pwassertn(index_activate_1_item_1 != (size_t)-1);
		
		size_t index_activate_1_item_2 = csv.index("activate_1_item_2",1);
		pwassertn(index_activate_1_item_2 != (size_t)-1);
		
		size_t index_activate_1_item_3 = csv.index("activate_1_item_3",1);
		pwassertn(index_activate_1_item_3 != (size_t)-1);
		
		size_t index_activate_2_item_1 = csv.index("activate_2_item_1",1);
		pwassertn(index_activate_2_item_1 != (size_t)-1);
		
		size_t index_activate_2_item_2 = csv.index("activate_2_item_2",1);
		pwassertn(index_activate_2_item_2 != (size_t)-1);
		
		size_t index_activate_2_item_3 = csv.index("activate_2_item_3",1);
		pwassertn(index_activate_2_item_3 != (size_t)-1);
		
		size_t index_activate_lvl = csv.index("activate_lvl",1);
		pwassertn(index_activate_lvl != (size_t)-1);
		
		size_t index_max_lvl = csv.index("max_lvl",1);
		pwassertn(index_max_lvl != (size_t)-1);
		
		
		for(size_t row = 3; row < csv.count(); ++row)
		{
			SHeroAssistancePos conf;
			conf.id = csv.get_i32(row,index_id);
			conf.postion_initial = csv.get_i32(row,index_postion_initial);
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_activate_1_item_1);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 2|| vals.empty());
				for(size_t i = 0; i < 2; ++i)
					conf.activate_1_item_1[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_activate_1_item_2);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 2|| vals.empty());
				for(size_t i = 0; i < 2; ++i)
					conf.activate_1_item_2[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_activate_1_item_3);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 2|| vals.empty());
				for(size_t i = 0; i < 2; ++i)
					conf.activate_1_item_3[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_activate_2_item_1);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 2|| vals.empty());
				for(size_t i = 0; i < 2; ++i)
					conf.activate_2_item_1[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_activate_2_item_2);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 2|| vals.empty());
				for(size_t i = 0; i < 2; ++i)
					conf.activate_2_item_2[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_activate_2_item_3);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 2|| vals.empty());
				for(size_t i = 0; i < 2; ++i)
					conf.activate_2_item_3[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			conf.activate_lvl = csv.get_i32(row,index_activate_lvl);
			conf.max_lvl = csv.get_i32(row,index_max_lvl);
			m_vtConfigures.push_back(conf);
		}
		return true;
	}
	
	SHeroAssistancePos& HeroAssistancePos::Get(size_t row)
	{
		return m_vtConfigures.at(row);
	}
}
