#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_ts_gmland_queryinfo.h"

namespace orm
{

	RTTI_TOUCH(TS_Gmland_QueryInfo);

	TS_Gmland_QueryInfo::TS_Gmland_QueryInfo()
		: type(0)
		, __hash(0)
	{
	}


	TS_Gmland_QueryInfo::~TS_Gmland_QueryInfo()
	{
	}

	std::string TS_Gmland_QueryInfo::rawkey()
	{
		std::string result;
		result.reserve(64);
		return result;
	}

	std::string TS_Gmland_QueryInfo::getkey()
	{
		return this->rawkey();
	}

	std::string TS_Gmland_QueryInfo::getmeta()
	{
		return TS_Gmland_QueryInfo::meta();
	}

	void TS_Gmland_QueryInfo::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	TS_Gmland_QueryInfo* TS_Gmland_QueryInfo::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		TS_Gmland_QueryInfo* tmp = new TS_Gmland_QueryInfo();
		tmp->from_bson(__obj);
		return tmp;
	}

	void TS_Gmland_QueryInfo::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void TS_Gmland_QueryInfo::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void TS_Gmland_QueryInfo::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(type != 0)
			__builder.append("type",type);
		__obj = __builder.obj();
	}

	void TS_Gmland_QueryInfo::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void TS_Gmland_QueryInfo::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void TS_Gmland_QueryInfo::from_bson(const char* __data,size_t __size)
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

	void TS_Gmland_QueryInfo::from_bson(const bson::bo& __obj)
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
			case 1932998153010: // type type: int16
				{
					pwutils::bsonToCppVariable(type,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 TS_Gmland_QueryInfo::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&type,sizeof(type),_result);

		return _result;
	}

	int16 TS_Gmland_QueryInfo::get_type() const
	{
		return type;
	}

	void TS_Gmland_QueryInfo::set_type(int16 value)
	{
		this->type = value;
	}


	bool TS_Gmland_QueryInfo::is_default_value() const
	{
		if(type != 0)
			return false;

		return true;
	}

}
