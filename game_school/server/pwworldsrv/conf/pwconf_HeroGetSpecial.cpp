#include "pwconf_HeroGetSpecial.h"
#include "pw_csv.h"
#include "tokenizer.h"
#include "pw_utils.h"
#include "pw_logger.h"

namespace pwconf
{
	bool HeroGetSpecial::LoadFrom(const char* filename)
	{
		pwutils::CSVReader csv;
		if(csv.load(filename) != 0)
			return false;
		size_t index_id = csv.index("id",1);
		pwassertn(index_id != (size_t)-1);
		
		size_t index_comment = csv.index("comment",1);
		pwassertn(index_comment != (size_t)-1);
		
		size_t index_priority = csv.index("priority",1);
		pwassertn(index_priority != (size_t)-1);
		
		size_t index_randomPool = csv.index("randomPool",1);
		pwassertn(index_randomPool != (size_t)-1);
		
		size_t index_type = csv.index("type",1);
		pwassertn(index_type != (size_t)-1);
		
		size_t index_npara1 = csv.index("npara1",1);
		pwassertn(index_npara1 != (size_t)-1);
		
		size_t index_npara2 = csv.index("npara2",1);
		pwassertn(index_npara2 != (size_t)-1);
		
		size_t index_npara3 = csv.index("npara3",1);
		pwassertn(index_npara3 != (size_t)-1);
		
		size_t index_fpara1 = csv.index("fpara1",1);
		pwassertn(index_fpara1 != (size_t)-1);
		
		
		for(size_t row = 3; row < csv.count(); ++row)
		{
			SHeroGetSpecial conf;
			conf.id = csv.get_i32(row,index_id);
			conf.comment = csv.get_str(row,index_comment);
			conf.priority = csv.get_i32(row,index_priority);
			conf.randomPool = csv.get_i32(row,index_randomPool);
			conf.type = csv.get_i32(row,index_type);
			conf.npara1 = csv.get_i32(row,index_npara1);
			conf.npara2 = csv.get_i32(row,index_npara2);
			conf.npara3 = csv.get_i32(row,index_npara3);
			conf.fpara1 = (float)csv.get_dec(row,index_fpara1);
			m_vtConfigures.push_back(conf);
		}
		return true;
	}
	
	SHeroGetSpecial& HeroGetSpecial::Get(size_t row)
	{
		return m_vtConfigures.at(row);
	}
}
