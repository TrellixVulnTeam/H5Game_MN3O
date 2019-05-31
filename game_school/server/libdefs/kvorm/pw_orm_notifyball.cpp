#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_notifyball.h"

namespace orm
{

	RTTI_TOUCH(NotifyBall);

	NotifyBall::NotifyBall()
		: receiver_id(0)
		, uuid(0)
		, id(0)
		, timestamp(0)
		, __hash(0)
	{
	}


	NotifyBall::~NotifyBall()
	{
	}

	std::string NotifyBall::rawkey()
	{
		std::string result;
		result.reserve(64);

		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)uuid);
			result.append(tmpbuf);
		}
		return result;
	}

	std::string NotifyBall::getkey()
	{
		return this->rawkey();
	}

	std::string NotifyBall::getmeta()
	{
		std::string result;
		result.reserve(64);
		result.append(meta());
		result.append(".");
		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)receiver_id);
			result.append(tmpbuf);
		}
		return result;
	}

	void NotifyBall::set_autoincr(int64 key)
	{
		uuid = key;
	}

	NotifyBall* NotifyBall::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		NotifyBall* tmp = new NotifyBall();
		tmp->from_bson(__obj);
		return tmp;
	}

	void NotifyBall::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void NotifyBall::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void NotifyBall::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(receiver_id != 0)
			__builder.append("receiver_id",receiver_id);
		if(uuid != 0)
			__builder.append("uuid",uuid);
		if(id != 0)
			__builder.append("id",id);
		if(timestamp != 0)
			__builder.append("timestamp",timestamp);

		if(!args.is_default_value())
		{
			mongo::BSONArrayBuilder args_builder;
			for(size_t i = 0; i < args.size(); ++i)
			{
				args_builder.append(args[i]);
			}
			__builder.appendArray("args",args_builder.obj());
		}


		__obj = __builder.obj();
	}

	void NotifyBall::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void NotifyBall::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void NotifyBall::from_bson(const char* __data,size_t __size)
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

	void NotifyBall::from_bson(const bson::bo& __obj)
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
			case 4952964483423: // receiver_id type: int64
				{
					pwutils::bsonToCppVariable(receiver_id,__be);
				}
				break;
			case 1885755691283: // uuid type: int64
				{
					pwutils::bsonToCppVariable(uuid,__be);
				}
				break;
			case 880468309535: // id type: int32
				{
					pwutils::bsonToCppVariable(id,__be);
				}
				break;
			case 4210982330490: // timestamp type: int64
				{
					pwutils::bsonToCppVariable(timestamp,__be);
				}
				break;
			case 1842761004773: // args type: string
				{
					args.cleanup();
					mongo::BSONObj aobj = __be.Obj();
					mongo::BSONObjIterator aiter(aobj);
					while(aiter.more())
					{
						mongo::BSONElement ae = aiter.next();
						std::string tmpvar;
						pwutils::bsonToCppVariable(tmpvar,ae);
						args.push_back(tmpvar);
					}
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 NotifyBall::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&receiver_id,sizeof(receiver_id),_result);

		_result = pwutils::city_hash(&uuid,sizeof(uuid),_result);

		_result = pwutils::city_hash(&id,sizeof(id),_result);

		_result = pwutils::city_hash(&timestamp,sizeof(timestamp),_result);

		_result = args.hash_make(_result);

		return _result;
	}

	int64 NotifyBall::get_receiver_id() const
	{
		return receiver_id;
	}

	void NotifyBall::set_receiver_id(int64 value)
	{
		this->receiver_id = value;
	}

	int64 NotifyBall::get_uuid() const
	{
		return uuid;
	}

	void NotifyBall::set_uuid(int64 value)
	{
		this->uuid = value;
	}

	int32 NotifyBall::get_id() const
	{
		return id;
	}

	void NotifyBall::set_id(int32 value)
	{
		this->id = value;
	}

	int64 NotifyBall::get_timestamp() const
	{
		return timestamp;
	}

	void NotifyBall::set_timestamp(int64 value)
	{
		this->timestamp = value;
	}


	bool NotifyBall::is_default_value() const
	{
		if(receiver_id != 0)
			return false;

		if(uuid != 0)
			return false;

		if(id != 0)
			return false;

		if(timestamp != 0)
			return false;

		if(!args.is_default_value())
			return false;

		return true;
	}

}
