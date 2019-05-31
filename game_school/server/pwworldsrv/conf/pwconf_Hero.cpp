#include "pwconf_Hero.h"
#include "pw_csv.h"
#include "tokenizer.h"
#include "pw_utils.h"
#include "pw_logger.h"

namespace pwconf
{
	bool Hero::LoadFrom(const char* filename)
	{
		pwutils::CSVReader csv;
		if(csv.load(filename) != 0)
			return false;
		size_t index_id = csv.index("id",1);
		pwassertn(index_id != (size_t)-1);
		
		size_t index_hero_name = csv.index("hero_name",1);
		pwassertn(index_hero_name != (size_t)-1);
		
		size_t index_skill_id = csv.index("skill_id",1);
		pwassertn(index_skill_id != (size_t)-1);
		
		size_t index_color = csv.index("color",1);
		pwassertn(index_color != (size_t)-1);
		
		size_t index_passive_skill_id = csv.index("passive_skill_id",1);
		pwassertn(index_passive_skill_id != (size_t)-1);
		
		size_t index_hero_spirit = csv.index("hero_spirit",1);
		pwassertn(index_hero_spirit != (size_t)-1);
		
		size_t index_description = csv.index("description",1);
		pwassertn(index_description != (size_t)-1);
		
		size_t index_hero_pieces = csv.index("hero_pieces",1);
		pwassertn(index_hero_pieces != (size_t)-1);
		
		size_t index_pieces_req = csv.index("pieces_req",1);
		pwassertn(index_pieces_req != (size_t)-1);
		
		size_t index_attr_star1 = csv.index("attr_star1",1);
		pwassertn(index_attr_star1 != (size_t)-1);
		
		size_t index_attr_star2 = csv.index("attr_star2",1);
		pwassertn(index_attr_star2 != (size_t)-1);
		
		size_t index_attr_star3 = csv.index("attr_star3",1);
		pwassertn(index_attr_star3 != (size_t)-1);
		
		size_t index_attr_star4 = csv.index("attr_star4",1);
		pwassertn(index_attr_star4 != (size_t)-1);
		
		size_t index_attr_star5 = csv.index("attr_star5",1);
		pwassertn(index_attr_star5 != (size_t)-1);
		
		
		for(size_t row = 3; row < csv.count(); ++row)
		{
			SHero conf;
			conf.id = csv.get_i32(row,index_id);
			conf.hero_name = csv.get_str(row,index_hero_name);
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_skill_id);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 3|| vals.empty());
				for(size_t i = 0; i < 3; ++i)
					conf.skill_id[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			conf.color = csv.get_i32(row,index_color);
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_passive_skill_id);
				tokenize(__tmp,vals,",","","\"");;
				for(size_t i = 0; i < vals.size(); ++i)
					conf.passive_skill_id.push_back(pwutils::atoi(vals[i].c_str()));
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_hero_spirit);
				tokenize(__tmp,vals,",","","\"");;
				for(size_t i = 0; i < vals.size(); ++i)
					conf.hero_spirit.push_back(pwutils::atoi(vals[i].c_str()));
			}
			conf.description = csv.get_str(row,index_description);
			conf.hero_pieces = csv.get_i32(row,index_hero_pieces);
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_pieces_req);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 5|| vals.empty());
				for(size_t i = 0; i < 5; ++i)
					conf.pieces_req[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_attr_star1);
				tokenize(__tmp,vals,",","","\"");;
				for(size_t i = 0; i < vals.size(); ++i)
					conf.attr_star1.push_back(pwutils::atoi(vals[i].c_str()));
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_attr_star2);
				tokenize(__tmp,vals,",","","\"");;
				for(size_t i = 0; i < vals.size(); ++i)
					conf.attr_star2.push_back(pwutils::atoi(vals[i].c_str()));
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_attr_star3);
				tokenize(__tmp,vals,",","","\"");;
				for(size_t i = 0; i < vals.size(); ++i)
					conf.attr_star3.push_back(pwutils::atoi(vals[i].c_str()));
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_attr_star4);
				tokenize(__tmp,vals,",","","\"");;
				for(size_t i = 0; i < vals.size(); ++i)
					conf.attr_star4.push_back(pwutils::atoi(vals[i].c_str()));
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_attr_star5);
				tokenize(__tmp,vals,",","","\"");;
				for(size_t i = 0; i < vals.size(); ++i)
					conf.attr_star5.push_back(pwutils::atoi(vals[i].c_str()));
			}
			m_vtConfigures.push_back(conf);
		}
		return true;
	}
	
	SHero& Hero::Get(size_t row)
	{
		return m_vtConfigures.at(row);
	}
}
