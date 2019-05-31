#ifndef _pw_gdb_operation_def_
#define _pw_gdb_operation_def_

#include <vector>
#include <memory>
#include "leveldb/db.h"
#include "leveldb/iterator.h"
#include "leveldb/comparator.h"
#include "pw_gdb_stdint.h"
#include <stdexcept>

namespace gdb
{
	// ***************************************************************

	typedef leveldb::Slice Slice;

	typedef std::vector<leveldb::Slice> CollectionSlicesT;
	typedef std::vector<std::string>	CollectionBuffersT;

	typedef std::auto_ptr<leveldb::Iterator> IteratorPtr;


	// ***************************************************************

	const size_t cst_max_key_len = 8192;

	// ***************************************************************

	const char SEPARATOR1 = '!';
	const char SEPARATOR1_R = '@'; // zscore ·´Ïò
	const char SEPARATOR2 = '#';
	const char SEPARATOR3 = '$';

	const char KV_PREFIX = 'k';
	const char HM_PREFIX = 'h';
	const char ZS_PREFIX = 'z';
	const char SO_PREFIX = 's';

	class script_exception : public std::exception
	{
	public:
		script_exception(const char* err) : _what(err) {}
		virtual ~script_exception() throw() {}
	public:
		virtual const char * what() const throw ()
		{
			return _what.c_str();
		}
	protected:
		std::string _what;
	};
}

#endif // _pw_gdb_operation_def_