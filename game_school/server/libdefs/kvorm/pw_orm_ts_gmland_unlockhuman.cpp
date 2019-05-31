#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_ts_gmland_unlockhuman.h"

namespace orm
{

	RTTI_TOUCH(TS_Gmland_UnlockHuman);

	TS_Gmland_UnlockHuman::TS_Gmland_UnlockHuman()
		: __hash(0)
	{
	}


	TS_Gmland_UnlockHuman::~TS_Gmland_UnlockHuman()
	{
	}

	std::string TS_Gmland_UnlockHuman::rawkey()
	{
		std::string result;
		result.reserve(64);
		return result;
	}

	std::string TS_Gmland_UnlockHuman::getkey()
	{
		return this->rawkey();
	}

	std::string TS_Gmland_UnlockHuman::getmeta()
	{
		return TS_Gmland_UnlockHuman::meta();
	}

	void TS_Gmland_UnlockHuman::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	TS_Gmland_UnlockHuman* TS_Gmland_UnlockHuman::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		TS_Gmland_UnlockHuman* tmp = new TS_Gmland_UnlockHuman();
		tmp->from_bson(__obj);
		return tmp;
	}

	void TS_Gmland_UnlockHuman::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void TS_Gmland_UnlockHuman::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void TS_Gmland_UnlockHuman::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		__obj = __builder.obj();
	}

	void TS_Gmland_UnlockHuman::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void TS_Gmland_UnlockHuman::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void TS_Gmland_UnlockHuman::from_bson(const char* __data,size_t __size)
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

	void TS_Gmland_UnlockHuman::from_bson(const bson::bo& __obj)
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
			}
		}
		__hash = hash_make(0);
	}


	int64 TS_Gmland_UnlockHuman::hash_make(int64 seed)
	{
		int64 _result = seed;
		return _result;
	}


	bool TS_Gmland_UnlockHuman::is_default_value() const
	{
		return true;
	}

}