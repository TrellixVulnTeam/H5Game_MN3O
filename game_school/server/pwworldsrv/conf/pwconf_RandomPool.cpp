#include "pwconf_RandomPool.h"
#include "pw_csv.h"
#include "tokenizer.h"
#include "pw_utils.h"
#include "pw_logger.h"

namespace pwconf
{
	bool RandomPool::LoadFrom(const char* filename)
	{
		pwutils::CSVReader csv;
		if(csv.load(filename) != 0)
			return false;
		size_t index_id = csv.index("id",1);
		pwassertn(index_id != (size_t)-1);
		
		size_t index_comment = csv.index("comment",1);
		pwassertn(index_comment != (size_t)-1);
		
		size_t index_randType = csv.index("randType",1);
		pwassertn(index_randType != (size_t)-1);
		
		size_t index_randNum = csv.index("randNum",1);
		pwassertn(index_randNum != (size_t)-1);
		
		size_t index_item1 = csv.index("item1",1);
		pwassertn(index_item1 != (size_t)-1);
		
		size_t index_item2 = csv.index("item2",1);
		pwassertn(index_item2 != (size_t)-1);
		
		size_t index_item3 = csv.index("item3",1);
		pwassertn(index_item3 != (size_t)-1);
		
		size_t index_item4 = csv.index("item4",1);
		pwassertn(index_item4 != (size_t)-1);
		
		size_t index_item5 = csv.index("item5",1);
		pwassertn(index_item5 != (size_t)-1);
		
		size_t index_item6 = csv.index("item6",1);
		pwassertn(index_item6 != (size_t)-1);
		
		size_t index_item7 = csv.index("item7",1);
		pwassertn(index_item7 != (size_t)-1);
		
		size_t index_item8 = csv.index("item8",1);
		pwassertn(index_item8 != (size_t)-1);
		
		size_t index_item9 = csv.index("item9",1);
		pwassertn(index_item9 != (size_t)-1);
		
		size_t index_item10 = csv.index("item10",1);
		pwassertn(index_item10 != (size_t)-1);
		
		size_t index_item11 = csv.index("item11",1);
		pwassertn(index_item11 != (size_t)-1);
		
		size_t index_item12 = csv.index("item12",1);
		pwassertn(index_item12 != (size_t)-1);
		
		size_t index_item13 = csv.index("item13",1);
		pwassertn(index_item13 != (size_t)-1);
		
		size_t index_item14 = csv.index("item14",1);
		pwassertn(index_item14 != (size_t)-1);
		
		size_t index_item15 = csv.index("item15",1);
		pwassertn(index_item15 != (size_t)-1);
		
		size_t index_item16 = csv.index("item16",1);
		pwassertn(index_item16 != (size_t)-1);
		
		size_t index_item17 = csv.index("item17",1);
		pwassertn(index_item17 != (size_t)-1);
		
		size_t index_item18 = csv.index("item18",1);
		pwassertn(index_item18 != (size_t)-1);
		
		size_t index_item19 = csv.index("item19",1);
		pwassertn(index_item19 != (size_t)-1);
		
		size_t index_item20 = csv.index("item20",1);
		pwassertn(index_item20 != (size_t)-1);
		
		
		for(size_t row = 3; row < csv.count(); ++row)
		{
			SRandomPool conf;
			conf.id = csv.get_i32(row,index_id);
			conf.comment = csv.get_str(row,index_comment);
			conf.randType = csv.get_i32(row,index_randType);
			conf.randNum = csv.get_i32(row,index_randNum);
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item1);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item1[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item2);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item2[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item3);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item3[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item4);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item4[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item5);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item5[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item6);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item6[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item7);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item7[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item8);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item8[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item9);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item9[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item10);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item10[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item11);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item11[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item12);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item12[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item13);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item13[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item14);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item14[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item15);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item15[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item16);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item16[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item17);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item17[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item18);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item18[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item19);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item19[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			{
				std::vector<std::string> vals;
				const char* __tmp = csv.get_str(row,index_item20);
				tokenize(__tmp,vals,",","","\"");;
				pwassertn(vals.size() == 4|| vals.empty());
				for(size_t i = 0; i < 4; ++i)
					conf.item20[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());
			}
			m_vtConfigures.push_back(conf);
		}
		return true;
	}
	
	SRandomPool& RandomPool::Get(size_t row)
	{
		return m_vtConfigures.at(row);
	}
}
