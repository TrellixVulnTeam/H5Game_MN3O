#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_passportgold.h"

namespace orm
{

	RTTI_TOUCH(PassportGold);

	PassportGold::PassportGold()
		: passport("")
		, gold(0)
		, chksum_base64("")
		, __hash(0)
	{
	}


	PassportGold::~PassportGold()
	{
	}

	std::string PassportGold::rawkey()
	{
		std::string result;
		result.reserve(64);

		result.append(passport.c_str());
		return result;
	}

	std::string PassportGold::getkey()
	{
		std::string result;
		result.reserve(64);
		result.append(passport.c_str());
		return result;
	}

	std::string PassportGold::getmeta()
	{
		return PassportGold::meta();
	}

	void PassportGold::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	PassportGold* PassportGold::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		PassportGold* tmp = new PassportGold();
		tmp->from_bson(__obj);
		return tmp;
	}

	void PassportGold::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void PassportGold::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void PassportGold::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(passport != "")
			__builder.append("passport",passport);
		if(gold != 0)
			__builder.append("gold",gold);
		if(chksum_base64 != "")
			__builder.append("chksum_base64",chksum_base64);
		__obj = __builder.obj();
	}

	void PassportGold::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportGold::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportGold::from_bson(const char* __data,size_t __size)
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

	void PassportGold::from_bson(const bson::bo& __obj)
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
			case 1812709671404: // gold type: int64
				{
					pwutils::bsonToCppVariable(gold,__be);
				}
				break;
			case 5426652924365: // chksum_base64 type: string
				{
					pwutils::bsonToCppVariable(chksum_base64,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 PassportGold::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&passport,sizeof(passport),_result);

		_result = pwutils::city_hash(&gold,sizeof(gold),_result);

		_result = pwutils::city_hash(chksum_base64.c_str(),chksum_base64.length(),_result);

		return _result;
	}

	const char* PassportGold::get_passport() const
	{
		return passport.c_str();
	}

	void PassportGold::set_passport(const char* value)
	{
		this->passport = value;
	}

	int64 PassportGold::get_gold() const
	{
		return gold;
	}

	void PassportGold::set_gold(int64 value)
	{
		this->gold = value;
	}

	const char* PassportGold::get_chksum_base64() const
	{
		return chksum_base64.c_str();
	}

	void PassportGold::set_chksum_base64(const char* value)
	{
		this->chksum_base64 = value;
	}


	bool PassportGold::is_default_value() const
	{
		if(passport.length() != 0)
			return false;

		if(gold != 0)
			return false;

		if(chksum_base64.length() != 0)
			return false;

		return true;
	}

}
