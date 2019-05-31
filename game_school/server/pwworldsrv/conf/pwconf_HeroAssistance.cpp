#include "pwconf_HeroAssistance.h"
#include "pw_csv.h"
#include "tokenizer.h"
#include "pw_utils.h"
#include "pw_logger.h"

namespace pwconf
{
	bool HeroAssistance::LoadFrom(const char* filename)
	{
		pwutils::CSVReader csv;
		if(csv.load(filename) != 0)
			return false;
		size_t index_id = csv.index("id",1);
		pwassertn(index_id != (size_t)-1);
		
		size_t index_hero_id = csv.index("hero_id",1);
		pwassertn(index_hero_id != (size_t)-1);
		
		size_t index_item_id = csv.index("item_id",1);
		pwassertn(index_item_id != (size_t)-1);
		
		size_t index_item_rank = csv.index("item_rank",1);
		pwassertn(index_item_rank != (size_t)-1);
		
		size_t index_item_slot = csv.index("item_slot",1);
		pwassertn(index_item_slot != (size_t)-1);
		
		size_t index_item_attr = csv.index("item_attr",1);
		pwassertn(index_item_attr != (size_t)-1);
		
		size_t index_req_item1 = csv.index("req_item1",1);
		pwassertn(index_req_item1 != (size_t)-1);
		
		size_t index_req_item2 = csv.index("req_item2",1);
		pwassertn(index_req_item2 != (size_t)-1);
		
		size_t index_req_item3 = csv.index("req_item3",1);
		pwassertn(index_req_item3 != (size_t)-1);
		
		
		for(size_t row = 3; row < csv.count(); ++row)
		{
			SHeroAssistance conf;
			conf.id = csv.get_i32(row,index_id);
			conf.hero_id = csv.get_i32(row,index_hero_id);
			conf.item_id = csv.get_i32(row,index_item_id);
			conf.item_rank = csv.get_i32(row,index_item_rank);
			conf.item_slot = csv.get_i32(row,index_item_slot);
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item_attr);
				tokenize(__tmp,vals,",","","\"");;
				for(size_t i = 0; i < vals.size(); ++i)
					conf.item_attr.push_back(pwutils::atoi(vals[i].c_str()));
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_req_item1);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 2|| vals.empty());
				for(size_t i = 0; i < 2; ++i)
					conf.req_item1[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_req_item2);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 2|| vals.empty());
				for(size_t i = 0; i < 2; ++i)
					conf.req_item2[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_req_item3);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 2|| vals.empty());
				for(size_t i = 0; i < 2; ++i)
					conf.req_item3[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			m_vtConfigures.push_back(conf);
		}
		return true;
	}
	
	SHeroAssistance& HeroAssistance::Get(size_t row)
	{
		return m_vtConfigures.at(row);
	}
}
