#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_sub.h"

namespace orm
{

	RTTI_TOUCH(Sub);

	Sub::Sub()
		: level(0)
		, talent_awake_type(0)
		, exp(0)
		, __hash(0)
	{
		memset(talent_awake_param,0,sizeof(talent_awake_param));
	}


	Sub::~Sub()
	{
	}

	std::string Sub::rawkey()
	{
		std::string result;
		result.reserve(64);
		return result;
	}

	std::string Sub::getkey()
	{
		return this->rawkey();
	}

	std::string Sub::getmeta()
	{
		return Sub::meta();
	}

	void Sub::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	Sub* Sub::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		Sub* tmp = new Sub();
		tmp->from_bson(__obj);
		return tmp;
	}

	void Sub::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void Sub::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void Sub::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(level != 0)
			__builder.append("level",level);
		if(talent_awake_type != 0)
			__builder.append("talent_awake_type",talent_awake_type);
		if(exp != 0)
			__builder.append("exp",exp);

		if(!pwutils::is_default_value(talent_awake_param,2,0))
		{
			mongo::BSONArrayBuilder talent_awake_param_builder;
			for(size_t i = 0; i < 2; ++i)
			{
				talent_awake_param_builder.append(talent_awake_param[i]);
			}
			__builder.appendArray("talent_awake_param",talent_awake_param_builder.obj());
		}

		__obj = __builder.obj();
	}

	void Sub::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void Sub::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void Sub::from_bson(const char* __data,size_t __size)
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

	void Sub::from_bson(const bson::bo& __obj)
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
			case 2304072786580: // level type: uint8
				{
					pwutils::bsonToCppVariable(level,__be);
				}
				break;
			case 7771097398307: // talent_awake_type type: uint8
				{
					pwutils::bsonToCppVariable(talent_awake_type,__be);
				}
				break;
			case 1430225858661: // exp type: int32
				{
					pwutils::bsonToCppVariable(exp,__be);
				}
				break;
			case 8108949662352: // talent_awake_param type: int32
				{

					mongo::BSONObj aobj = __be.Obj();
					mongo::BSONObjIterator aiter(aobj);
					size_t count = 0;
					while(aiter.more())
					{
						mongo::BSONElement ae = aiter.next();
						pwassertop(count < 2,continue);
						int32 tmpvar;
						pwutils::bsonToCppVariable(tmpvar,ae);
						talent_awake_param[count] = tmpvar;
						++count;
					}
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 Sub::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&level,sizeof(level),_result);

		_result = pwutils::city_hash(&talent_awake_type,sizeof(talent_awake_type),_result);

		_result = pwutils::city_hash(&exp,sizeof(exp),_result);

		for(size_t i = 0; i < 2;++i)
		{
			_result = pwutils::city_hash(&i,sizeof(i),_result);
			_result = pwutils::city_hash(&talent_awake_param[i],sizeof(talent_awake_param[i]),_result);
		}

		return _result;
	}

	uint8 Sub::get_level() const
	{
		return level;
	}

	void Sub::set_level(uint8 value)
	{
		this->level = value;
	}

	uint8 Sub::get_talent_awake_type() const
	{
		return talent_awake_type;
	}

	void Sub::set_talent_awake_type(uint8 value)
	{
		this->talent_awake_type = value;
	}

	int32 Sub::get_exp() const
	{
		return exp;
	}

	void Sub::set_exp(int32 value)
	{
		this->exp = value;
	}


	bool Sub::is_default_value() const
	{
		if(level != 0)
			return false;

		if(talent_awake_type != 0)
			return false;

		if(exp != 0)
			return false;

		for(size_t i = 0; i < 2; ++i)
			if(talent_awake_param[i] != 0)
				return false;

		return true;
	}

}
