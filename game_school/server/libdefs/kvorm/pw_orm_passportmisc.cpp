#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_passportmisc.h"

namespace orm
{

	RTTI_TOUCH(PassportMisc);

	PassportMisc::PassportMisc()
		: passport("")
		, locked_time(0)
		, locked_chat_time(0)
		, __hash(0)
	{
	}


	PassportMisc::~PassportMisc()
	{
	}

	std::string PassportMisc::rawkey()
	{
		std::string result;
		result.reserve(64);

		result.append(passport.c_str());
		return result;
	}

	std::string PassportMisc::getkey()
	{
		std::string result;
		result.reserve(64);
		result.append(passport.c_str());
		return result;
	}

	std::string PassportMisc::getmeta()
	{
		return PassportMisc::meta();
	}

	void PassportMisc::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	PassportMisc* PassportMisc::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		PassportMisc* tmp = new PassportMisc();
		tmp->from_bson(__obj);
		return tmp;
	}

	void PassportMisc::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void PassportMisc::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void PassportMisc::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(passport != "")
			__builder.append("passport",passport);
		if(locked_time != 0)
			__builder.append("locked_time",locked_time);
		if(locked_chat_time != 0)
			__builder.append("locked_chat_time",locked_chat_time);
		__obj = __builder.obj();
	}

	void PassportMisc::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportMisc::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportMisc::from_bson(const char* __data,size_t __size)
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

	void PassportMisc::from_bson(const bson::bo& __obj)
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
			case 3831688010902: // passport type: string
				{
					pwutils::bsonToCppVariable(passport,__be);
				}
				break;
			case 4949720616390: // locked_time type: int64
				{
					pwutils::bsonToCppVariable(locked_time,__be);
				}
				break;
			case 7143561541871: // locked_chat_time type: int64
				{
					pwutils::bsonToCppVariable(locked_chat_time,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 PassportMisc::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&passport,sizeof(passport),_result);

		_result = pwutils::city_hash(&locked_time,sizeof(locked_time),_result);

		_result = pwutils::city_hash(&locked_chat_time,sizeof(locked_chat_time),_result);

		return _result;
	}

	const char* PassportMisc::get_passport() const
	{
		return passport.c_str();
	}

	void PassportMisc::set_passport(const char* value)
	{
		this->passport = value;
	}

	int64 PassportMisc::get_locked_time() const
	{
		return locked_time;
	}

	void PassportMisc::set_locked_time(int64 value)
	{
		this->locked_time = value;
	}

	int64 PassportMisc::get_locked_chat_time() const
	{
		return locked_chat_time;
	}

	void PassportMisc::set_locked_chat_time(int64 value)
	{
		this->locked_chat_time = value;
	}


	bool PassportMisc::is_default_value() const
	{
		if(passport.length() != 0)
			return false;

		if(locked_time != 0)
			return false;

		if(locked_chat_time != 0)
			return false;

		return true;
	}

}
