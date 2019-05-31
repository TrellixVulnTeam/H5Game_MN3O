#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_ts_gmland_setgs.h"

namespace orm
{

	RTTI_TOUCH(TS_Gmland_SetGS);

	TS_Gmland_SetGS::TS_Gmland_SetGS()
		: level(0)
		, __hash(0)
	{
	}


	TS_Gmland_SetGS::~TS_Gmland_SetGS()
	{
	}

	std::string TS_Gmland_SetGS::rawkey()
	{
		std::string result;
		result.reserve(64);
		return result;
	}

	std::string TS_Gmland_SetGS::getkey()
	{
		return this->rawkey();
	}

	std::string TS_Gmland_SetGS::getmeta()
	{
		return TS_Gmland_SetGS::meta();
	}

	void TS_Gmland_SetGS::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	TS_Gmland_SetGS* TS_Gmland_SetGS::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		TS_Gmland_SetGS* tmp = new TS_Gmland_SetGS();
		tmp->from_bson(__obj);
		return tmp;
	}

	void TS_Gmland_SetGS::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void TS_Gmland_SetGS::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void TS_Gmland_SetGS::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(level != 0)
			__builder.append("level",level);
		__obj = __builder.obj();
	}

	void TS_Gmland_SetGS::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void TS_Gmland_SetGS::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void TS_Gmland_SetGS::from_bson(const char* __data,size_t __size)
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

	void TS_Gmland_SetGS::from_bson(const bson::bo& __obj)
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
			case 2304072786580: // level type: int16
				{
					pwutils::bsonToCppVariable(level,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 TS_Gmland_SetGS::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&level,sizeof(level),_result);

		return _result;
	}

	int16 TS_Gmland_SetGS::get_level() const
	{
		return level;
	}

	void TS_Gmland_SetGS::set_level(int16 value)
	{
		this->level = value;
	}


	bool TS_Gmland_SetGS::is_default_value() const
	{
		if(level != 0)
			return false;

		return true;
	}

}
