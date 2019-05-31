#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_passportnull.h"

namespace orm
{

	RTTI_TOUCH(PassportNull);

	PassportNull::PassportNull()
		: passport("")
		, __hash(0)
	{
	}


	PassportNull::~PassportNull()
	{
	}

	std::string PassportNull::rawkey()
	{
		std::string result;
		result.reserve(64);

		result.append(passport.c_str());
		return result;
	}

	std::string PassportNull::getkey()
	{
		return this->rawkey();
	}

	std::string PassportNull::getmeta()
	{
		std::string result;
		result.reserve(64);
		result.append(meta());
		result.append(".");
		result.append(passport.c_str());
		return result;
	}

	void PassportNull::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	PassportNull* PassportNull::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		PassportNull* tmp = new PassportNull();
		tmp->from_bson(__obj);
		return tmp;
	}

	void PassportNull::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void PassportNull::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void PassportNull::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(passport != "")
			__builder.append("passport",passport);
		__obj = __builder.obj();
	}

	void PassportNull::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportNull::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportNull::from_bson(const char* __data,size_t __size)
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

	void PassportNull::from_bson(const bson::bo& __obj)
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
			}
		}
		__hash = hash_make(0);
	}


	int64 PassportNull::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&passport,sizeof(passport),_result);

		return _result;
	}

	const char* PassportNull::get_passport() const
	{
		return passport.c_str();
	}

	void PassportNull::set_passport(const char* value)
	{
		this->passport = value;
	}


	bool PassportNull::is_default_value() const
	{
		if(passport.length() != 0)
			return false;

		return true;
	}

}
