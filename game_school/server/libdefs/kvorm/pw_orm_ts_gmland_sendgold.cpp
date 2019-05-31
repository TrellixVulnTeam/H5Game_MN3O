#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_ts_gmland_sendgold.h"

namespace orm
{

	RTTI_TOUCH(TS_Gmland_SendGold);

	TS_Gmland_SendGold::TS_Gmland_SendGold()
		: gold(0)
		, target_hid(0)
		, sender_hid(0)
		, sender_name("")
		, __hash(0)
	{
	}


	TS_Gmland_SendGold::~TS_Gmland_SendGold()
	{
	}

	std::string TS_Gmland_SendGold::rawkey()
	{
		std::string result;
		result.reserve(64);
		return result;
	}

	std::string TS_Gmland_SendGold::getkey()
	{
		return this->rawkey();
	}

	std::string TS_Gmland_SendGold::getmeta()
	{
		return TS_Gmland_SendGold::meta();
	}

	void TS_Gmland_SendGold::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	TS_Gmland_SendGold* TS_Gmland_SendGold::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		TS_Gmland_SendGold* tmp = new TS_Gmland_SendGold();
		tmp->from_bson(__obj);
		return tmp;
	}

	void TS_Gmland_SendGold::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void TS_Gmland_SendGold::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void TS_Gmland_SendGold::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(gold != 0)
			__builder.append("gold",gold);
		if(target_hid != 0)
			__builder.append("target_hid",target_hid);
		if(sender_hid != 0)
			__builder.append("sender_hid",sender_hid);
		if(sender_name != "")
			__builder.append("sender_name",sender_name);
		__obj = __builder.obj();
	}

	void TS_Gmland_SendGold::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void TS_Gmland_SendGold::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void TS_Gmland_SendGold::from_bson(const char* __data,size_t __size)
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

	void TS_Gmland_SendGold::from_bson(const bson::bo& __obj)
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
			case 1812709671404: // gold type: int64
				{
					pwutils::bsonToCppVariable(gold,__be);
				}
				break;
			case 4514416909169: // target_hid type: int64
				{
					pwutils::bsonToCppVariable(target_hid,__be);
				}
				break;
			case 4488406208569: // sender_hid type: int64
				{
					pwutils::bsonToCppVariable(sender_hid,__be);
				}
				break;
			case 4952301144965: // sender_name type: string
				{
					pwutils::bsonToCppVariable(sender_name,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 TS_Gmland_SendGold::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&gold,sizeof(gold),_result);

		_result = pwutils::city_hash(&target_hid,sizeof(target_hid),_result);

		_result = pwutils::city_hash(&sender_hid,sizeof(sender_hid),_result);

		_result = pwutils::city_hash(&sender_name,sizeof(sender_name),_result);

		return _result;
	}

	int64 TS_Gmland_SendGold::get_gold() const
	{
		return gold;
	}

	void TS_Gmland_SendGold::set_gold(int64 value)
	{
		this->gold = value;
	}

	int64 TS_Gmland_SendGold::get_target_hid() const
	{
		return target_hid;
	}

	void TS_Gmland_SendGold::set_target_hid(int64 value)
	{
		this->target_hid = value;
	}

	int64 TS_Gmland_SendGold::get_sender_hid() const
	{
		return sender_hid;
	}

	void TS_Gmland_SendGold::set_sender_hid(int64 value)
	{
		this->sender_hid = value;
	}

	const char* TS_Gmland_SendGold::get_sender_name() const
	{
		return sender_name.c_str();
	}

	void TS_Gmland_SendGold::set_sender_name(const char* value)
	{
		this->sender_name = value;
	}


	bool TS_Gmland_SendGold::is_default_value() const
	{
		if(gold != 0)
			return false;

		if(target_hid != 0)
			return false;

		if(sender_hid != 0)
			return false;

		if(sender_name.length() != 0)
			return false;

		return true;
	}

}
