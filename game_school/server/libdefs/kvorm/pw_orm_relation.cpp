#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_relation.h"

namespace orm
{

	RTTI_TOUCH(Relation);

	Relation::Relation()
		: uid(0)
		, rid(0)
		, type(0)
		, __hash(0)
	{
	}


	Relation::~Relation()
	{
	}

	std::string Relation::rawkey()
	{
		std::string result;
		result.reserve(64);

		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)uid);
			result.append(tmpbuf);
		}

		result.append(".");
		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)rid);
			result.append(tmpbuf);
		}

		result.append(".");
		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)type);
			result.append(tmpbuf);
		}
		return result;
	}

	std::string Relation::getkey()
	{
		return this->rawkey();
	}

	std::string Relation::getmeta()
	{
		return Relation::meta();
	}

	void Relation::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	Relation* Relation::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		Relation* tmp = new Relation();
		tmp->from_bson(__obj);
		return tmp;
	}

	void Relation::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void Relation::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void Relation::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(uid != 0)
			__builder.append("uid",uid);
		if(rid != 0)
			__builder.append("rid",rid);
		if(type != 0)
			__builder.append("type",type);
		__obj = __builder.obj();
	}

	void Relation::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void Relation::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void Relation::from_bson(const char* __data,size_t __size)
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

	void Relation::from_bson(const bson::bo& __obj)
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
			case 1382981491004: // uid type: int64
				{
					pwutils::bsonToCppVariable(uid,__be);
				}
				break;
			case 1370096537633: // rid type: int64
				{
					pwutils::bsonToCppVariable(rid,__be);
				}
				break;
			case 1932998153010: // type type: uint8
				{
					pwutils::bsonToCppVariable(type,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 Relation::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&uid,sizeof(uid),_result);

		_result = pwutils::city_hash(&rid,sizeof(rid),_result);

		_result = pwutils::city_hash(&type,sizeof(type),_result);

		return _result;
	}

	int64 Relation::get_uid() const
	{
		return uid;
	}

	void Relation::set_uid(int64 value)
	{
		this->uid = value;
	}

	int64 Relation::get_rid() const
	{
		return rid;
	}

	void Relation::set_rid(int64 value)
	{
		this->rid = value;
	}

	uint8 Relation::get_type() const
	{
		return type;
	}

	void Relation::set_type(uint8 value)
	{
		this->type = value;
	}


	bool Relation::is_default_value() const
	{
		if(uid != 0)
			return false;

		if(rid != 0)
			return false;

		if(type != 0)
			return false;

		return true;
	}

}
