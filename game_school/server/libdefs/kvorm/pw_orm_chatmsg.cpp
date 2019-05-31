#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_chatmsg.h"

namespace orm
{

	RTTI_TOUCH(ChatMsg);

	ChatMsg::ChatMsg()
		: uid(0)
		, rid(0)
		, timestamp(0)
		, flags(0)
		, __hash(0)
	{
		memset(content,0,sizeof(content));
	}


	ChatMsg::~ChatMsg()
	{
	}

	std::string ChatMsg::rawkey()
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
			pwutils::itoa(tmpbuf,(int64)timestamp);
			result.append(tmpbuf);
		}
		return result;
	}

	std::string ChatMsg::getkey()
	{
		return this->rawkey();
	}

	std::string ChatMsg::getmeta()
	{
		std::string result;
		result.reserve(64);
		result.append(meta());
		result.append(".");
		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)uid);
			result.append(tmpbuf);
		}
		return result;
	}

	void ChatMsg::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	ChatMsg* ChatMsg::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		ChatMsg* tmp = new ChatMsg();
		tmp->from_bson(__obj);
		return tmp;
	}

	void ChatMsg::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void ChatMsg::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void ChatMsg::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(uid != 0)
			__builder.append("uid",uid);
		if(rid != 0)
			__builder.append("rid",rid);
		if(timestamp != 0)
			__builder.append("timestamp",timestamp);

		if(!pwutils::is_default_value(content,128,0))
			__builder.append("content",content);

		if(flags != 0)
			__builder.append("flags",flags);
		__obj = __builder.obj();
	}

	void ChatMsg::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void ChatMsg::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void ChatMsg::from_bson(const char* __data,size_t __size)
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

	void ChatMsg::from_bson(const bson::bo& __obj)
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
			case 4210982330490: // timestamp type: int64
				{
					pwutils::bsonToCppVariable(timestamp,__be);
				}
				break;
			case 3277227370525: // content type: char
				{
					pwutils::strncpy(content,__be.valuestrsafe(),_countof(content));
				}
				break;
			case 2255076523323: // flags type: int32
				{
					pwutils::bsonToCppVariable(flags,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 ChatMsg::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&uid,sizeof(uid),_result);

		_result = pwutils::city_hash(&rid,sizeof(rid),_result);

		_result = pwutils::city_hash(&timestamp,sizeof(timestamp),_result);

		_result = pwutils::city_hash(content,strlen(content),_result);

		_result = pwutils::city_hash(&flags,sizeof(flags),_result);

		return _result;
	}

	int64 ChatMsg::get_uid() const
	{
		return uid;
	}

	void ChatMsg::set_uid(int64 value)
	{
		this->uid = value;
	}

	int64 ChatMsg::get_rid() const
	{
		return rid;
	}

	void ChatMsg::set_rid(int64 value)
	{
		this->rid = value;
	}

	int64 ChatMsg::get_timestamp() const
	{
		return timestamp;
	}

	void ChatMsg::set_timestamp(int64 value)
	{
		this->timestamp = value;
	}

	int32 ChatMsg::get_flags() const
	{
		return flags;
	}

	void ChatMsg::set_flags(int32 value)
	{
		this->flags = value;
	}


	bool ChatMsg::is_default_value() const
	{
		if(uid != 0)
			return false;

		if(rid != 0)
			return false;

		if(timestamp != 0)
			return false;

		if(!pwutils::is_default_value(content,128,0))
			return false;

		if(flags != 0)
			return false;

		return true;
	}

}
