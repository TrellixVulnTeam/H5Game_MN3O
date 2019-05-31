#include "pw_def.h"


namespace pwutils
{
	class CSVReader
	{
	public:
		int load(const std::string& file);
	public:
		const char* get(size_t row,size_t col);
		const char* get_str(size_t row,size_t col);
		void get_str(size_t row, size_t col, const char * split, std::vector<std::string> & v);
		sint32 get_i32(size_t row,size_t col);
		sint64 get_i64(size_t row,size_t col);
		double get_dec(size_t row,size_t col);
		sint32 get_i32_byindex(size_t row,size_t col,const char** names,size_t count);
		bool get_bool(size_t row,size_t col);
	public:
		const char* get_column_name(size_t col,size_t row = 0);
	public:
		size_t index(const char* name);
		size_t index(const char* name,size_t row);
		size_t count();
		size_t field_count();
	public:
		typedef std::vector<std::string> CollectionValuesT;
		typedef std::vector<CollectionValuesT> CollectionRowsT;
	private:
		CollectionRowsT mRows;
		CollectionValuesT mNames;
	};
}