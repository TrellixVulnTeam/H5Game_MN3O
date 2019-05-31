#include "pwconf_HeroCard.h"
#include "pw_csv.h"
#include "tokenizer.h"
#include "pw_utils.h"
#include "pw_logger.h"

namespace pwconf
{
	bool HeroCard::LoadFrom(const char* filename)
	{
		pwutils::CSVReader csv;
		if(csv.load(filename) != 0)
			return false;
		size_t index_id = csv.index("id",1);
		pwassertn(index_id != (size_t)-1);
		
		size_t index_skill_name = csv.index("skill_name",1);
		pwassertn(index_skill_name != (size_t)-1);
		
		size_t index_hero_id = csv.index("hero_id",1);
		pwassertn(index_hero_id != (size_t)-1);
		
		size_t index_skill_position = csv.index("skill_position",1);
		pwassertn(index_skill_position != (size_t)-1);
		
		size_t index_color = csv.index("color",1);
		pwassertn(index_color != (size_t)-1);
		
		size_t index_magic_id = csv.index("magic_id",1);
		pwassertn(index_magic_id != (size_t)-1);
		
		size_t index_herointroduction = csv.index("herointroduction",1);
		pwassertn(index_herointroduction != (size_t)-1);
		
		size_t index_label_self = csv.index("label_self",1);
		pwassertn(index_label_self != (size_t)-1);
		
		size_t index_label_relative_self = csv.index("label_relative_self",1);
		pwassertn(index_label_relative_self != (size_t)-1);
		
		size_t index_label_relative_enemy = csv.index("label_relative_enemy",1);
		pwassertn(index_label_relative_enemy != (size_t)-1);
		
		size_t index_skill_tip = csv.index("skill_tip",1);
		pwassertn(index_skill_tip != (size_t)-1);
		
		
		for(size_t row = 3; row < csv.count(); ++row)
		{
			SHeroCard conf;
			conf.id = csv.get_i32(row,index_id);
			conf.skill_name = csv.get_str(row,index_skill_name);
			conf.hero_id = csv.get_i32(row,index_hero_id);
			conf.skill_position = csv.get_i32(row,index_skill_position);
			conf.color = csv.get_i32(row,index_color);
			conf.magic_id = csv.get_i32(row,index_magic_id);
			conf.herointroduction = csv.get_str(row,index_herointroduction);
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_label_self);
				tokenize(__tmp,vals,",","","\"");;
				for(size_t i = 0; i < vals.size(); ++i)
					conf.label_self.push_back(pwutils::atoi(vals[i].c_str()));
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_label_relative_self);
				tokenize(__tmp,vals,",","","\"");;
				for(size_t i = 0; i < vals.size(); ++i)
					conf.label_relative_self.push_back(pwutils::atoi(vals[i].c_str()));
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_label_relative_enemy);
				tokenize(__tmp,vals,",","","\"");;
				for(size_t i = 0; i < vals.size(); ++i)
					conf.label_relative_enemy.push_back(pwutils::atoi(vals[i].c_str()));
			}
			conf.skill_tip = csv.get_str(row,index_skill_tip);
			m_vtConfigures.push_back(conf);
		}
		return true;
	}
	
	SHeroCard& HeroCard::Get(size_t row)
	{
		return m_vtConfigures.at(row);
	}
}
