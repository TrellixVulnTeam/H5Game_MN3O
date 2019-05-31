#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_ts_gmland_lockchat.h"

namespace orm
{

	RTTI_TOUCH(TS_Gmland_LockChat);

	TS_Gmland_LockChat::TS_Gmland_LockChat()
		: seconds(0)
		, __hash(0)
	{
	}


	TS_Gmland_LockChat::~TS_Gmland_LockChat()
	{
	}

	std::string TS_Gmland_LockChat::rawkey()
	{
		std::string result;
		result.reserve(64);
		return result;
	}

	std::string TS_Gmland_LockChat::getkey()
	{
		return this->rawkey();
	}

	std::string TS_Gmland_LockChat::getmeta()
	{
		return TS_Gmland_LockChat::meta();
	}

	void TS_Gmland_LockChat::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	TS_Gmland_LockChat* TS_Gmland_LockChat::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		TS_Gmland_LockChat* tmp = new TS_Gmland_LockChat();
		tmp->from_bson(__obj);
		return tmp;
	}

	void TS_Gmland_LockChat::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void TS_Gmland_LockChat::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void TS_Gmland_LockChat::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(seconds != 0)
			__builder.append("seconds",seconds);
		__obj = __builder.obj();
	}

	void TS_Gmland_LockChat::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void TS_Gmland_LockChat::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void TS_Gmland_LockChat::from_bson(const char* __data,size_t __size)
	{
		pwassert(__data != 0);
		pwassert(__size >= sizeof(int));
		try
		{
			bson::bo __obj(__data);
			pwassert(__obj.objsize() == __size);
			from_bson(__obj);
		}
		catch(const bson::assertion&)
		{
			pwreportvars(false && "invalid bson_data",__size);
			pwassert(false && "invalid bson_data");
		}
	}

	void TS_Gmland_LockChat::from_bson(const bson::bo& __obj)
	{
		mongo::BSONObjIterator iter(__obj);
		while(iter.more())
		{
			mongo::BSONElement __be = iter.next();
			const char* fieldName = __be.fieldName();
			int64 hash = pwutils::bkdr_hash_and_sum(fieldName);
			switch(hash)
			{
			case 768799158513: // _T
				{
					pwasserte(pwutils::strcmp(__be.valuestr(),meta()) == 0);
				}
				break;
			case 3226597847007: // seconds type: int64
				{
					pwutils::bsonToCppVariable(seconds,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 TS_Gmland_LockChat::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&seconds,sizeof(seconds),_result);

		return _result;
	}

	int64 TS_Gmland_LockChat::get_seconds() const
	{
		return seconds;
	}

	void TS_Gmland_LockChat::set_seconds(int64 value)
	{
		this->seconds = value;
	}


	bool TS_Gmland_LockChat::is_default_value() const
	{
		if(seconds != 0)
			return false;

		return true;
	}

}
