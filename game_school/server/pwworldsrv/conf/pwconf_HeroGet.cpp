#include "pwconf_HeroGet.h"
#include "pw_csv.h"
#include "tokenizer.h"
#include "pw_utils.h"
#include "pw_logger.h"

namespace pwconf
{
	bool HeroGet::LoadFrom(const char* filename)
	{
		pwutils::CSVReader csv;
		if(csv.load(filename) != 0)
			return false;
		size_t index_id = csv.index("id",1);
		pwassertn(index_id != (size_t)-1);
		
		size_t index_comment = csv.index("comment",1);
		pwassertn(index_comment != (size_t)-1);
		
		size_t index_costType = csv.index("costType",1);
		pwassertn(index_costType != (size_t)-1);
		
		size_t index_normalCost = csv.index("normalCost",1);
		pwassertn(index_normalCost != (size_t)-1);
		
		size_t index_tenTimesCost = csv.index("tenTimesCost",1);
		pwassertn(index_tenTimesCost != (size_t)-1);
		
		size_t index_freeCd = csv.index("freeCd",1);
		pwassertn(index_freeCd != (size_t)-1);
		
		size_t index_freeStartCd = csv.index("freeStartCd",1);
		pwassertn(index_freeStartCd != (size_t)-1);
		
		size_t index_dailyMaxFree = csv.index("dailyMaxFree",1);
		pwassertn(index_dailyMaxFree != (size_t)-1);
		
		size_t index_energyGet = csv.index("energyGet",1);
		pwassertn(index_energyGet != (size_t)-1);
		
		size_t index_normalPool = csv.index("normalPool",1);
		pwassertn(index_normalPool != (size_t)-1);
		
		size_t index_normalEnergyNeed = csv.index("normalEnergyNeed",1);
		pwassertn(index_normalEnergyNeed != (size_t)-1);
		
		size_t index_energyPool = csv.index("energyPool",1);
		pwassertn(index_energyPool != (size_t)-1);
		
		size_t index_firstEnergyNeed = csv.index("firstEnergyNeed",1);
		pwassertn(index_firstEnergyNeed != (size_t)-1);
		
		size_t index_firstHero = csv.index("firstHero",1);
		pwassertn(index_firstHero != (size_t)-1);
		
		
		for(size_t row = 3; row < csv.count(); ++row)
		{
			SHeroGet conf;
			conf.id = csv.get_i32(row,index_id);
			conf.comment = csv.get_str(row,index_comment);
			conf.costType = csv.get_i32(row,index_costType);
			conf.normalCost = csv.get_i32(row,index_normalCost);
			conf.tenTimesCost = csv.get_i32(row,index_tenTimesCost);
			conf.freeCd = csv.get_i32(row,index_freeCd);
			conf.freeStartCd = csv.get_i32(row,index_freeStartCd);
			conf.dailyMaxFree = csv.get_i32(row,index_dailyMaxFree);
			conf.energyGet = csv.get_i32(row,index_energyGet);
			conf.normalPool = csv.get_i32(row,index_normalPool);
			conf.normalEnergyNeed = csv.get_i32(row,index_normalEnergyNeed);
			conf.energyPool = csv.get_i32(row,index_energyPool);
			conf.firstEnergyNeed = csv.get_i32(row,index_firstEnergyNeed);
			conf.firstHero = csv.get_i32(row,index_firstHero);
			m_vtConfigures.push_back(conf);
		}
		return true;
	}
	
	SHeroGet& HeroGet::Get(size_t row)
	{
		return m_vtConfigures.at(row);
	}
}
