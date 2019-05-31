#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_globalwelfare.h"

namespace orm
{

	RTTI_TOUCH(GlobalWelfare);

	GlobalWelfare::GlobalWelfare()
		: id(0)
		, datetime("")
		, itemtype(0)
		, itemcount(0)
		, req_profession_mask(255)
		, __hash(0)
	{
		memset(req_level_range,0,sizeof(req_level_range));
	}


	GlobalWelfare::~GlobalWelfare()
	{
	}

	std::string GlobalWelfare::rawkey()
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

	std::string GlobalWelfare::getkey()
	{
		return this->rawkey();
	}

	std::string GlobalWelfare::getmeta()
	{
		return GlobalWelfare::meta();
	}

	void GlobalWelfare::set_autoincr(int64 key)
	{
		id = key;
	}

	GlobalWelfare* GlobalWelfare::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		GlobalWelfare* tmp = new GlobalWelfare();
		tmp->from_bson(__obj);
		return tmp;
	}

	void GlobalWelfare::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void GlobalWelfare::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void GlobalWelfare::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(id != 0)
			__builder.append("id",id);
		if(datetime != "")
			__builder.append("datetime",datetime);
		if(itemtype != 0)
			__builder.append("itemtype",itemtype);
		if(itemcount != 0)
			__builder.append("itemcount",itemcount);

		if(!pwutils::is_default_value(req_level_range,2,0))
		{
			mongo::BSONArrayBuilder req_level_range_builder;
			for(size_t i = 0; i < 2; ++i)
			{
				req_level_range_builder.append(req_level_range[i]);
			}
			__builder.appendArray("req_level_range",req_level_range_builder.obj());
		}

		if(req_profession_mask != 255)
			__builder.append("req_profession_mask",req_profession_mask);
		__obj = __builder.obj();
	}

	void GlobalWelfare::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void GlobalWelfare::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void GlobalWelfare::from_bson(const char* __data,size_t __size)
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

	void GlobalWelfare::from_bson(const bson::bo& __obj)
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
			case 3629514625199: // datetime type: string
				{
					pwutils::bsonToCppVariable(datetime,__be);
				}
				break;
			case 3784367266533: // itemtype type: int32
				{
					pwutils::bsonToCppVariable(itemtype,__be);
				}
				break;
			case 4226730701820: // itemcount type: int16
				{
					pwutils::bsonToCppVariable(itemcount,__be);
				}
				break;
			case 6783121385101: // req_level_range type: int16
				{

					mongo::BSONObj aobj = __be.Obj();
					mongo::BSONObjIterator aiter(aobj);
					size_t count = 0;
					while(aiter.more())
					{
						mongo::BSONElement ae = aiter.next();
						pwassertop(count < 2,continue);
						int16 tmpvar;
						pwutils::bsonToCppVariable(tmpvar,ae);
						req_level_range[count] = tmpvar;
						++count;
					}
				}
				break;
			case 8770353070454: // req_profession_mask type: uint8
				{
					pwutils::bsonToCppVariable(req_profession_mask,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 GlobalWelfare::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&id,sizeof(id),_result);

		_result = pwutils::city_hash(&datetime,sizeof(datetime),_result);

		_result = pwutils::city_hash(&itemtype,sizeof(itemtype),_result);

		_result = pwutils::city_hash(&itemcount,sizeof(itemcount),_result);

		for(size_t i = 0; i < 2;++i)
		{
			_result = pwutils::city_hash(&i,sizeof(i),_result);
			_result = pwutils::city_hash(&req_level_range[i],sizeof(req_level_range[i]),_result);
		}

		_result = pwutils::city_hash(&req_profession_mask,sizeof(req_profession_mask),_result);

		return _result;
	}

	int64 GlobalWelfare::get_id() const
	{
		return id;
	}

	void GlobalWelfare::set_id(int64 value)
	{
		this->id = value;
	}

	const char* GlobalWelfare::get_datetime() const
	{
		return datetime.c_str();
	}

	void GlobalWelfare::set_datetime(const char* value)
	{
		this->datetime = value;
	}

	int32 GlobalWelfare::get_itemtype() const
	{
		return itemtype;
	}

	void GlobalWelfare::set_itemtype(int32 value)
	{
		this->itemtype = value;
	}

	int16 GlobalWelfare::get_itemcount() const
	{
		return itemcount;
	}

	void GlobalWelfare::set_itemcount(int16 value)
	{
		this->itemcount = value;
	}

	uint8 GlobalWelfare::get_req_profession_mask() const
	{
		return req_profession_mask;
	}

	void GlobalWelfare::set_req_profession_mask(uint8 value)
	{
		this->req_profession_mask = value;
	}


	bool GlobalWelfare::is_default_value() const
	{
		if(id != 0)
			return false;

		if(datetime.length() != 0)
			return false;

		if(itemtype != 0)
			return false;

		if(itemcount != 0)
			return false;

		for(size_t i = 0; i < 2; ++i)
			if(req_level_range[i] != 0)
				return false;

		if(req_profession_mask != 255)
			return false;

		return true;
	}

}
