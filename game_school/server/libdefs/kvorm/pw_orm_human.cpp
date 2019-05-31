#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_human.h"

namespace orm
{

	RTTI_TOUCH(Human);

	Human::Human()
		: id(0)
		, passport("")
		, name("")
		, last_login("")
		, last_logout("")
		, online_seconds(0)
		, online_seconds_today(0)
		, birthday(0)
		, profession(0)
		, sex(0)
		, level(0)
		, exp(0)
		, level_need_exp(0)
		, loc_stage(0)
		, __hash(0)
	{
	}


	Human::~Human()
	{
	}

	std::string Human::rawkey()
	{
		std::string result;
		result.reserve(64);

		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)id);
			result.append(tmpbuf);
		}
		return result;
	}

	std::string Human::getkey()
	{
		return this->rawkey();
	}

	std::string Human::getmeta()
	{
		return Human::meta();
	}

	void Human::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	Human* Human::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		Human* tmp = new Human();
		tmp->from_bson(__obj);
		return tmp;
	}

	void Human::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void Human::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void Human::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(id != 0)
			__builder.append("id",id);
		if(passport != "")
			__builder.append("passport",passport);
		if(name != "")
			__builder.append("name",name);
		if(last_login != "")
			__builder.append("last_login",last_login);
		if(last_logout != "")
			__builder.append("last_logout",last_logout);
		if(online_seconds != 0)
			__builder.append("online_seconds",online_seconds);
		if(online_seconds_today != 0)
			__builder.append("online_seconds_today",online_seconds_today);
		if(birthday != 0)
			__builder.append("birthday",birthday);
		if(profession != 0)
			__builder.append("profession",profession);
		if(sex != 0)
			__builder.append("sex",sex);
		if(level != 0)
			__builder.append("level",level);
		if(exp != 0)
			__builder.append("exp",exp);
		if(level_need_exp != 0)
			__builder.append("level_need_exp",level_need_exp);
		if(loc_stage != 0)
			__builder.append("loc_stage",loc_stage);
		__obj = __builder.obj();
	}

	void Human::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void Human::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void Human::from_bson(const char* __data,size_t __size)
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

	void Human::from_bson(const bson::bo& __obj)
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
			case 880468309535: // id type: int64
				{
					pwutils::bsonToCppVariable(id,__be);
				}
				break;
			case 3831688010902: // passport type: string
				{
					pwutils::bsonToCppVariable(passport,__be);
				}
				break;
			case 1791250331439: // name type: string
				{
					pwutils::bsonToCppVariable(name,__be);
				}
				break;
			case 4587806726624: // last_login type: string
				{
					pwutils::bsonToCppVariable(last_login,__be);
				}
				break;
			case 5142540964831: // last_logout type: string
				{
					pwutils::bsonToCppVariable(last_logout,__be);
				}
				break;
			case 6404480444099: // online_seconds type: int64
				{
					pwutils::bsonToCppVariable(online_seconds,__be);
				}
				break;
			case 9153279922305: // online_seconds_today type: int64
				{
					pwutils::bsonToCppVariable(online_seconds_today,__be);
				}
				break;
			case 3673629363897: // birthday type: int32
				{
					pwutils::bsonToCppVariable(birthday,__be);
				}
				break;
			case 4708513036684: // profession type: uint8
				{
					pwutils::bsonToCppVariable(profession,__be);
				}
				break;
			case 1443110998322: // sex type: uint8
				{
					pwutils::bsonToCppVariable(sex,__be);
				}
				break;
			case 2304072786580: // level type: int16
				{
					pwutils::bsonToCppVariable(level,__be);
				}
				break;
			case 1430225858661: // exp type: int64
				{
					pwutils::bsonToCppVariable(exp,__be);
				}
				break;
			case 6318660338751: // level_need_exp type: int64
				{
					pwutils::bsonToCppVariable(level_need_exp,__be);
				}
				break;
			case 4058775524715: // loc_stage type: int32
				{
					pwutils::bsonToCppVariable(loc_stage,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 Human::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&id,sizeof(id),_result);

		_result = pwutils::city_hash(&passport,sizeof(passport),_result);

		_result = pwutils::city_hash(&name,sizeof(name),_result);

		_result = pwutils::city_hash(&last_login,sizeof(last_login),_result);

		_result = pwutils::city_hash(&last_logout,sizeof(last_logout),_result);

		_result = pwutils::city_hash(&online_seconds,sizeof(online_seconds),_result);

		_result = pwutils::city_hash(&online_seconds_today,sizeof(online_seconds_today),_result);

		_result = pwutils::city_hash(&birthday,sizeof(birthday),_result);

		_result = pwutils::city_hash(&profession,sizeof(profession),_result);

		_result = pwutils::city_hash(&sex,sizeof(sex),_result);

		_result = pwutils::city_hash(&level,sizeof(level),_result);

		_result = pwutils::city_hash(&exp,sizeof(exp),_result);

		_result = pwutils::city_hash(&level_need_exp,sizeof(level_need_exp),_result);

		_result = pwutils::city_hash(&loc_stage,sizeof(loc_stage),_result);

		return _result;
	}

	int64 Human::get_id() const
	{
		return id;
	}

	void Human::set_id(int64 value)
	{
		this->id = value;
	}

	const char* Human::get_passport() const
	{
		return passport.c_str();
	}

	void Human::set_passport(const char* value)
	{
		this->passport = value;
	}

	const char* Human::get_name() const
	{
		return name.c_str();
	}

	void Human::set_name(const char* value)
	{
		this->name = value;
	}

	const char* Human::get_last_login() const
	{
		return last_login.c_str();
	}

	void Human::set_last_login(const char* value)
	{
		this->last_login = value;
	}

	const char* Human::get_last_logout() const
	{
		return last_logout.c_str();
	}

	void Human::set_last_logout(const char* value)
	{
		this->last_logout = value;
	}

	int64 Human::get_online_seconds() const
	{
		return online_seconds;
	}

	void Human::set_online_seconds(int64 value)
	{
		this->online_seconds = value;
	}

	int64 Human::get_online_seconds_today() const
	{
		return online_seconds_today;
	}

	void Human::set_online_seconds_today(int64 value)
	{
		this->online_seconds_today = value;
	}

	int32 Human::get_birthday() const
	{
		return birthday;
	}

	void Human::set_birthday(int32 value)
	{
		this->birthday = value;
	}

	uint8 Human::get_profession() const
	{
		return profession;
	}

	void Human::set_profession(uint8 value)
	{
		this->profession = value;
	}

	uint8 Human::get_sex() const
	{
		return sex;
	}

	void Human::set_sex(uint8 value)
	{
		this->sex = value;
	}

	int16 Human::get_level() const
	{
		return level;
	}

	void Human::set_level(int16 value)
	{
		this->level = value;
	}

	int64 Human::get_exp() const
	{
		return exp;
	}

	void Human::set_exp(int64 value)
	{
		this->exp = value;
	}

	int64 Human::get_level_need_exp() const
	{
		return level_need_exp;
	}

	void Human::set_level_need_exp(int64 value)
	{
		this->level_need_exp = value;
	}

	int32 Human::get_loc_stage() const
	{
		return loc_stage;
	}

	void Human::set_loc_stage(int32 value)
	{
		this->loc_stage = value;
	}


	bool Human::is_default_value() const
	{
		if(id != 0)
			return false;

		if(passport.length() != 0)
			return false;

		if(name.length() != 0)
			return false;

		if(last_login.length() != 0)
			return false;

		if(last_logout.length() != 0)
			return false;

		if(online_seconds != 0)
			return false;

		if(online_seconds_today != 0)
			return false;

		if(birthday != 0)
			return false;

		if(profession != 0)
			return false;

		if(sex != 0)
			return false;

		if(level != 0)
			return false;

		if(exp != 0)
			return false;

		if(level_need_exp != 0)
			return false;

		if(loc_stage != 0)
			return false;

		return true;
	}

}
