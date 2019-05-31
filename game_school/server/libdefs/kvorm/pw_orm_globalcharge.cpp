#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_globalcharge.h"

namespace orm
{

	RTTI_TOUCH(GlobalCharge);

	GlobalCharge::GlobalCharge()
		: date(0)
		, rmb(0)
		, pubacct_rmb(0)
		, __hash(0)
	{
	}


	GlobalCharge::~GlobalCharge()
	{
	}

	std::string GlobalCharge::rawkey()
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

	std::string GlobalCharge::getkey()
	{
		return this->rawkey();
	}

	std::string GlobalCharge::getmeta()
	{
		return GlobalCharge::meta();
	}

	void GlobalCharge::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	GlobalCharge* GlobalCharge::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		GlobalCharge* tmp = new GlobalCharge();
		tmp->from_bson(__obj);
		return tmp;
	}

	void GlobalCharge::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void GlobalCharge::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void GlobalCharge::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(date != 0)
			__builder.append("date",date);
		if(rmb != 0)
			__builder.append("rmb",rmb);
		if(pubacct_rmb != 0)
			__builder.append("pubacct_rmb",pubacct_rmb);
		__obj = __builder.obj();
	}

	void GlobalCharge::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void GlobalCharge::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void GlobalCharge::from_bson(const char* __data,size_t __size)
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

	void GlobalCharge::from_bson(const bson::bo& __obj)
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
			case 1778342949558: // date type: int64
				{
					pwutils::bsonToCppVariable(date,__be);
				}
				break;
			case 1378686472747: // rmb type: float
				{
					pwutils::bsonToCppVariable(rmb,__be);
				}
				break;
			case 4957643118020: // pubacct_rmb type: float
				{
					pwutils::bsonToCppVariable(pubacct_rmb,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 GlobalCharge::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&date,sizeof(date),_result);

		_result = pwutils::city_hash(&rmb,sizeof(rmb),_result);

		_result = pwutils::city_hash(&pubacct_rmb,sizeof(pubacct_rmb),_result);

		return _result;
	}

	int64 GlobalCharge::get_date() const
	{
		return date;
	}

	void GlobalCharge::set_date(int64 value)
	{
		this->date = value;
	}

	float GlobalCharge::get_rmb() const
	{
		return rmb;
	}

	void GlobalCharge::set_rmb(float value)
	{
		this->rmb = value;
	}

	float GlobalCharge::get_pubacct_rmb() const
	{
		return pubacct_rmb;
	}

	void GlobalCharge::set_pubacct_rmb(float value)
	{
		this->pubacct_rmb = value;
	}


	bool GlobalCharge::is_default_value() const
	{
		if(date != 0)
			return false;

		if(rmb != 0)
			return false;

		if(pubacct_rmb != 0)
			return false;

		return true;
	}

}
