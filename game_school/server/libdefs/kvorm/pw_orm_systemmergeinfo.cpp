#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_systemmergeinfo.h"

namespace orm
{

	RTTI_TOUCH(SystemMergeInfo);

	SystemMergeInfo::SystemMergeInfo()
		: sid(0)
		, zoneid(0)
		, date("")
		, __hash(0)
	{
	}


	SystemMergeInfo::~SystemMergeInfo()
	{
	}

	std::string SystemMergeInfo::rawkey()
	{
		std::string result;
		result.reserve(64);

		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)sid);
			result.append(tmpbuf);
		}
		return result;
	}

	std::string SystemMergeInfo::getkey()
	{
		return this->rawkey();
	}

	std::string SystemMergeInfo::getmeta()
	{
		return SystemMergeInfo::meta();
	}

	void SystemMergeInfo::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	SystemMergeInfo* SystemMergeInfo::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		SystemMergeInfo* tmp = new SystemMergeInfo();
		tmp->from_bson(__obj);
		return tmp;
	}

	void SystemMergeInfo::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void SystemMergeInfo::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void SystemMergeInfo::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(sid != 0)
			__builder.append("sid",sid);
		if(zoneid != 0)
			__builder.append("zoneid",zoneid);
		if(date != "")
			__builder.append("date",date);
		__obj = __builder.obj();
	}

	void SystemMergeInfo::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void SystemMergeInfo::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void SystemMergeInfo::from_bson(const char* __data,size_t __size)
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

	void SystemMergeInfo::from_bson(const bson::bo& __obj)
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
			case 1374391522090: // sid type: int32
				{
					pwutils::bsonToCppVariable(sid,__be);
				}
				break;
			case 2787573629747: // zoneid type: int32
				{
					pwutils::bsonToCppVariable(zoneid,__be);
				}
				break;
			case 1778342949558: // date type: string
				{
					pwutils::bsonToCppVariable(date,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 SystemMergeInfo::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&sid,sizeof(sid),_result);

		_result = pwutils::city_hash(&zoneid,sizeof(zoneid),_result);

		_result = pwutils::city_hash(date.c_str(),date.length(),_result);

		return _result;
	}

	int32 SystemMergeInfo::get_sid() const
	{
		return sid;
	}

	void SystemMergeInfo::set_sid(int32 value)
	{
		this->sid = value;
	}

	int32 SystemMergeInfo::get_zoneid() const
	{
		return zoneid;
	}

	void SystemMergeInfo::set_zoneid(int32 value)
	{
		this->zoneid = value;
	}

	const char* SystemMergeInfo::get_date() const
	{
		return date.c_str();
	}

	void SystemMergeInfo::set_date(const char* value)
	{
		this->date = value;
	}


	bool SystemMergeInfo::is_default_value() const
	{
		if(sid != 0)
			return false;

		if(zoneid != 0)
			return false;

		if(date.length() != 0)
			return false;

		return true;
	}

}
