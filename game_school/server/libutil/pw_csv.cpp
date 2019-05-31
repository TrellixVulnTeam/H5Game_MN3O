#include "pw_csv.h"
#include <fstream>
#include "tokenizer.h"
#include "pw_utils.h"
#include "pw_iconv.h"

namespace pwutils
{
	void trim_right(char* text)
	{
		int n = strlen(text);
		while(n >= 0)
		{
			if(text[n] == '\r' || text[n] == '\n' || text[n] == ' ')
			{
				text[n] = '\0';
				n --;
			}
			else
			{
				break;
			}
		}
	}

	int CSVReader::load(const std::string& file)
	{
		mRows.clear();
		mNames.clear();

		std::fstream stream;
		stream.open(file.c_str(),std::ios_base::in);
		if(!stream.good())
			return -1;

		while(!stream.eof())
		{
			char buf[10240] = "";
			stream.getline(buf,sizeof(buf));
			if(buf[0] == '\0')
				continue;

			std::string realline = pwutils::utf8_to_mbs(buf);
			memset(buf,0,sizeof(buf));
			strncpy(buf,realline.c_str(),_countof(buf));

			assert(realline.length() > 1 && "encoding error!,check server_group.xml default_encoding or agent");

			trim_right(buf);

			CollectionValuesT values;

			tokenize(buf,values,"\t","","\"");

			if(values.size() == 0)
				continue;

			if(mNames.size() == 0)
				mNames = values;
			else
				mRows.push_back(values);
		}
		return 0;
	}

	const char* CSVReader::get(size_t row,size_t col)
	{
		assert(row >= 0 && row < mRows.size());

		CollectionValuesT& values = mRows[row];

		assert(col >= 0 && col < values.size());

		return values[col].c_str();
	}

	const char* CSVReader::get_str(size_t row,size_t col)
	{
		return get(row,col);
	}

	void CSVReader::get_str(size_t row, size_t col, const char * split, std::vector<std::string> & v)
	{
			assert(row >= 0 && row < mRows.size());

			CollectionValuesT& values = mRows[row];

			assert(col >= 0 && col < values.size());

			tokenize(values[col].c_str(), v, split);
	}

	sint32 CSVReader::get_i32(size_t row,size_t col)
	{
		const char* value = this->get(row,col);

		return (sint32)pwutils::atoi(value);
	}

	sint64 CSVReader::get_i64(size_t row,size_t col)
	{
		const char* value = this->get(row,col);

		return pwutils::atoi(value);
	}

	double CSVReader::get_dec(size_t row,size_t col)
	{
		const char* value = this->get(row,col);

		return pwutils::atof(value);
	}

	sint32 CSVReader::get_i32_byindex(size_t row,size_t col,const char** names,size_t count)
	{
		assert(names && count > 0);

		const char* name = this->get_str(row,col);

		for(size_t i = 0; i < count; ++i)
		{
			if(pwutils::stricmp(name,names[i]) == 0)
				return (sint32)i;
		}
		assert(false && "wrong configure");
		return -1;
	}

	bool CSVReader::get_bool(size_t row,size_t col)
	{
		const char* name = this->get_str(row,col);
		if(stricmp(name,"true") == 0)
			return true;
		if(stricmp(name,"false") == 0)
			return false;
		return pwutils::atoi(name) == 1;
	}

	size_t CSVReader::index(const char* name)
	{
		for(size_t i = 0; i < mNames.size(); ++i)
		{
			const char* c = mNames[i].c_str();
			if(pwutils::stricmp(c,name) == 0)
				return i;
		}
		return std::string::npos;
	}

	size_t CSVReader::index(const char* name,size_t row)
	{
		if(row == 0)
			return index(name);

		CollectionValuesT& values = mRows[row - 1];

		for(size_t i = 0; i < values.size(); ++i)
		{
			const char* c = values[i].c_str();
			if(pwutils::stricmp(c,name) == 0)
				return i;
		}
		return std::string::npos;
	}

	size_t CSVReader::count()
	{
		return mRows.size();
	}

	size_t CSVReader::field_count()
	{
		return mNames.size();
	}

	const char* CSVReader::get_column_name( size_t col,size_t row )
	{
		assert(col >= 0 && col < mNames.size());
		if(row == 0)
			return mNames[col].c_str();
		return mRows[row - 1][col].c_str();
	}

}
