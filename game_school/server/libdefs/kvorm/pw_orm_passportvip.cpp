#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_passportvip.h"

namespace orm
{

	RTTI_TOUCH(PassportVip);

	PassportVip::PassportVip()
		: passport("")
		, exp(0)
		, exp_new(0)
		, reward_bits(0)
		, reward_bits_new(0)
		, level(0)
		, is_get_dailyreward(0)
		, __hash(0)
	{
	}


	PassportVip::~PassportVip()
	{
	}

	std::string PassportVip::rawkey()
	{
		std::string result;
		result.reserve(64);

		result.append(passport.c_str());
		return result;
	}

	std::string PassportVip::getkey()
	{
		std::string result;
		result.reserve(64);
		result.append(passport.c_str());
		return result;
	}

	std::string PassportVip::getmeta()
	{
		return PassportVip::meta();
	}

	void PassportVip::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	PassportVip* PassportVip::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		PassportVip* tmp = new PassportVip();
		tmp->from_bson(__obj);
		return tmp;
	}

	void PassportVip::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void PassportVip::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void PassportVip::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(passport != "")
			__builder.append("passport",passport);
		if(exp != 0)
			__builder.append("exp",exp);
		if(exp_new != 0)
			__builder.append("exp_new",exp_new);
		if(reward_bits != 0)
			__builder.append("reward_bits",reward_bits);
		if(reward_bits_new != 0)
			__builder.append("reward_bits_new",reward_bits_new);
		if(level != 0)
			__builder.append("level",level);
		if(is_get_dailyreward != 0)
			__builder.append("is_get_dailyreward",is_get_dailyreward);
		__obj = __builder.obj();
	}

	void PassportVip::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportVip::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportVip::from_bson(const char* __data,size_t __size)
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

	void PassportVip::from_bson(const bson::bo& __obj)
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
			case 1430225858661: // exp type: int32
				{
					pwutils::bsonToCppVariable(exp,__be);
				}
				break;
			case 3257385774206: // exp_new type: int32
				{
					pwutils::bsonToCppVariable(exp_new,__be);
				}
				break;
			case 5042475657926: // reward_bits type: int32
				{
					pwutils::bsonToCppVariable(reward_bits,__be);
				}
				break;
			case 6868028644143: // reward_bits_new type: int32
				{
					pwutils::bsonToCppVariable(reward_bits_new,__be);
				}
				break;
			case 2304072786580: // level type: int32
				{
					pwutils::bsonToCppVariable(level,__be);
				}
				break;
			case 8186333042762: // is_get_dailyreward type: int32
				{
					pwutils::bsonToCppVariable(is_get_dailyreward,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 PassportVip::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&passport,sizeof(passport),_result);

		_result = pwutils::city_hash(&exp,sizeof(exp),_result);

		_result = pwutils::city_hash(&exp_new,sizeof(exp_new),_result);

		_result = pwutils::city_hash(&reward_bits,sizeof(reward_bits),_result);

		_result = pwutils::city_hash(&reward_bits_new,sizeof(reward_bits_new),_result);

		_result = pwutils::city_hash(&level,sizeof(level),_result);

		_result = pwutils::city_hash(&is_get_dailyreward,sizeof(is_get_dailyreward),_result);

		return _result;
	}

	const char* PassportVip::get_passport() const
	{
		return passport.c_str();
	}

	void PassportVip::set_passport(const char* value)
	{
		this->passport = value;
	}

	int32 PassportVip::get_exp() const
	{
		return exp;
	}

	void PassportVip::set_exp(int32 value)
	{
		this->exp = value;
	}

	int32 PassportVip::get_exp_new() const
	{
		return exp_new;
	}

	void PassportVip::set_exp_new(int32 value)
	{
		this->exp_new = value;
	}

	int32 PassportVip::get_reward_bits() const
	{
		return reward_bits;
	}

	void PassportVip::set_reward_bits(int32 value)
	{
		this->reward_bits = value;
	}

	int32 PassportVip::get_reward_bits_new() const
	{
		return reward_bits_new;
	}

	void PassportVip::set_reward_bits_new(int32 value)
	{
		this->reward_bits_new = value;
	}

	int32 PassportVip::get_level() const
	{
		return level;
	}

	void PassportVip::set_level(int32 value)
	{
		this->level = value;
	}

	int32 PassportVip::get_is_get_dailyreward() const
	{
		return is_get_dailyreward;
	}

	void PassportVip::set_is_get_dailyreward(int32 value)
	{
		this->is_get_dailyreward = value;
	}


	bool PassportVip::is_default_value() const
	{
		if(passport.length() != 0)
			return false;

		if(exp != 0)
			return false;

		if(exp_new != 0)
			return false;

		if(reward_bits != 0)
			return false;

		if(reward_bits_new != 0)
			return false;

		if(level != 0)
			return false;

		if(is_get_dailyreward != 0)
			return false;

		return true;
	}

}
