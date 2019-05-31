#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_globaldailyinfolianyun.h"

namespace orm
{

	RTTI_TOUCH(GlobalDailyInfoLianYun);

	GlobalDailyInfoLianYun::GlobalDailyInfoLianYun()
		: date(0)
		, role_created_num(0)
		, role_logined_num(0)
		, role_onlined_max(0)
		, role_spend_gold_sum(0)
		, __hash(0)
	{
	}


	GlobalDailyInfoLianYun::~GlobalDailyInfoLianYun()
	{
	}

	std::string GlobalDailyInfoLianYun::rawkey()
	{
		std::string result;
		result.reserve(64);

		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)date);
			result.append(tmpbuf);
		}
		return result;
	}

	std::string GlobalDailyInfoLianYun::getkey()
	{
		return this->rawkey();
	}

	std::string GlobalDailyInfoLianYun::getmeta()
	{
		return GlobalDailyInfoLianYun::meta();
	}

	void GlobalDailyInfoLianYun::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	GlobalDailyInfoLianYun* GlobalDailyInfoLianYun::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		GlobalDailyInfoLianYun* tmp = new GlobalDailyInfoLianYun();
		tmp->from_bson(__obj);
		return tmp;
	}

	void GlobalDailyInfoLianYun::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void GlobalDailyInfoLianYun::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void GlobalDailyInfoLianYun::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(date != 0)
			__builder.append("date",date);
		if(role_created_num != 0)
			__builder.append("role_created_num",role_created_num);
		if(role_logined_num != 0)
			__builder.append("role_logined_num",role_logined_num);
		if(role_onlined_max != 0)
			__builder.append("role_onlined_max",role_onlined_max);
		if(role_spend_gold_sum != 0)
			__builder.append("role_spend_gold_sum",role_spend_gold_sum);
		__obj = __builder.obj();
	}

	void GlobalDailyInfoLianYun::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void GlobalDailyInfoLianYun::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void GlobalDailyInfoLianYun::from_bson(const char* __data,size_t __size)
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

	void GlobalDailyInfoLianYun::from_bson(const bson::bo& __obj)
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
			case 1778342949558: // date type: int32
				{
					pwutils::bsonToCppVariable(date,__be);
				}
				break;
			case 7249993209602: // role_created_num type: int32
				{
					pwutils::bsonToCppVariable(role_created_num,__be);
				}
				break;
			case 7294336850510: // role_logined_num type: int32
				{
					pwutils::bsonToCppVariable(role_logined_num,__be);
				}
				break;
			case 7280881338577: // role_onlined_max type: int32
				{
					pwutils::bsonToCppVariable(role_onlined_max,__be);
				}
				break;
			case 8676834539882: // role_spend_gold_sum type: int64
				{
					pwutils::bsonToCppVariable(role_spend_gold_sum,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 GlobalDailyInfoLianYun::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&date,sizeof(date),_result);

		_result = pwutils::city_hash(&role_created_num,sizeof(role_created_num),_result);

		_result = pwutils::city_hash(&role_logined_num,sizeof(role_logined_num),_result);

		_result = pwutils::city_hash(&role_onlined_max,sizeof(role_onlined_max),_result);

		_result = pwutils::city_hash(&role_spend_gold_sum,sizeof(role_spend_gold_sum),_result);

		return _result;
	}

	int32 GlobalDailyInfoLianYun::get_date() const
	{
		return date;
	}

	void GlobalDailyInfoLianYun::set_date(int32 value)
	{
		this->date = value;
	}

	int32 GlobalDailyInfoLianYun::get_role_created_num() const
	{
		return role_created_num;
	}

	void GlobalDailyInfoLianYun::set_role_created_num(int32 value)
	{
		this->role_created_num = value;
	}

	int32 GlobalDailyInfoLianYun::get_role_logined_num() const
	{
		return role_logined_num;
	}

	void GlobalDailyInfoLianYun::set_role_logined_num(int32 value)
	{
		this->role_logined_num = value;
	}

	int32 GlobalDailyInfoLianYun::get_role_onlined_max() const
	{
		return role_onlined_max;
	}

	void GlobalDailyInfoLianYun::set_role_onlined_max(int32 value)
	{
		this->role_onlined_max = value;
	}

	int64 GlobalDailyInfoLianYun::get_role_spend_gold_sum() const
	{
		return role_spend_gold_sum;
	}

	void GlobalDailyInfoLianYun::set_role_spend_gold_sum(int64 value)
	{
		this->role_spend_gold_sum = value;
	}


	bool GlobalDailyInfoLianYun::is_default_value() const
	{
		if(date != 0)
			return false;

		if(role_created_num != 0)
			return false;

		if(role_logined_num != 0)
			return false;

		if(role_onlined_max != 0)
			return false;

		if(role_spend_gold_sum != 0)
			return false;

		return true;
	}

}
