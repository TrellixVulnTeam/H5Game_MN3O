#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_mail.h"

namespace orm
{

	RTTI_TOUCH(Mail);

	Mail::Mail()
		: id(0)
		, mode(0)
		, flag(0)
		, send_date(0)
		, sender_id(0)
		, receiver_id(0)
		, item_binded(false)
		, __hash(0)
	{
		memset(sender_name,0,sizeof(sender_name));
		memset(subject,0,sizeof(subject));
		memset(content,0,sizeof(content));
		memset(append_data,0,sizeof(append_data));
	}


	Mail::~Mail()
	{
	}

	std::string Mail::rawkey()
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

	std::string Mail::getkey()
	{
		return this->rawkey();
	}

	std::string Mail::getmeta()
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

	void Mail::set_autoincr(int64 key)
	{
		id = key;
	}

	Mail* Mail::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		Mail* tmp = new Mail();
		tmp->from_bson(__obj);
		return tmp;
	}

	void Mail::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void Mail::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void Mail::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(id != 0)
			__builder.append("id",id);
		if(mode != 0)
			__builder.append("mode",mode);
		if(flag != 0)
			__builder.append("flag",flag);
		if(send_date != 0)
			__builder.append("send_date",send_date);
		if(sender_id != 0)
			__builder.append("sender_id",sender_id);

		if(!pwutils::is_default_value(sender_name,64,0))
			__builder.append("sender_name",sender_name);

		if(receiver_id != 0)
			__builder.append("receiver_id",receiver_id);

		if(!pwutils::is_default_value(subject,40,0))
			__builder.append("subject",subject);


		if(!pwutils::is_default_value(content,256,0))
			__builder.append("content",content);


		if(!pwutils::is_default_value(append_data,64,0))
			__builder.append("append_data",append_data);

		if(item_binded != false)
			__builder.append("item_binded",item_binded);
		__obj = __builder.obj();
	}

	void Mail::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void Mail::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void Mail::from_bson(const char* __data,size_t __size)
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

	void Mail::from_bson(const bson::bo& __obj)
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
			case 1808428191607: // mode type: int16
				{
					pwutils::bsonToCppVariable(mode,__be);
				}
				break;
			case 1761167762840: // flag type: int16
				{
					pwutils::bsonToCppVariable(flag,__be);
				}
				break;
			case 4017193883289: // send_date type: int64
				{
					pwutils::bsonToCppVariable(send_date,__be);
				}
				break;
			case 4042614640453: // sender_id type: int64
				{
					pwutils::bsonToCppVariable(sender_id,__be);
				}
				break;
			case 4952301144965: // sender_name type: char
				{
					pwutils::strncpy(sender_name,__be.valuestrsafe(),_countof(sender_name));
				}
				break;
			case 4952964483423: // receiver_id type: int64
				{
					pwutils::bsonToCppVariable(receiver_id,__be);
				}
				break;
			case 3231530946788: // subject type: char
				{
					pwutils::strncpy(subject,__be.valuestrsafe(),_countof(subject));
				}
				break;
			case 3277227370525: // content type: char
				{
					pwutils::strncpy(content,__be.valuestrsafe(),_countof(content));
				}
				break;
			case 4884127127051: // append_data type: char
				{
					pwutils::strncpy(append_data,__be.valuestrsafe(),_countof(append_data));
				}
				break;
			case 4898367863640: // item_binded type: bool
				{
					pwutils::bsonToCppVariable(item_binded,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 Mail::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&id,sizeof(id),_result);

		_result = pwutils::city_hash(&mode,sizeof(mode),_result);

		_result = pwutils::city_hash(&flag,sizeof(flag),_result);

		_result = pwutils::city_hash(&send_date,sizeof(send_date),_result);

		_result = pwutils::city_hash(&sender_id,sizeof(sender_id),_result);

		_result = pwutils::city_hash(sender_name,strlen(sender_name),_result);

		_result = pwutils::city_hash(&receiver_id,sizeof(receiver_id),_result);

		_result = pwutils::city_hash(subject,strlen(subject),_result);

		_result = pwutils::city_hash(content,strlen(content),_result);

		_result = pwutils::city_hash(append_data,strlen(append_data),_result);

		_result = pwutils::city_hash(&item_binded,sizeof(item_binded),_result);

		return _result;
	}

	int64 Mail::get_id() const
	{
		return id;
	}

	void Mail::set_id(int64 value)
	{
		this->id = value;
	}

	int16 Mail::get_mode() const
	{
		return mode;
	}

	void Mail::set_mode(int16 value)
	{
		this->mode = value;
	}

	int16 Mail::get_flag() const
	{
		return flag;
	}

	void Mail::set_flag(int16 value)
	{
		this->flag = value;
	}

	int64 Mail::get_send_date() const
	{
		return send_date;
	}

	void Mail::set_send_date(int64 value)
	{
		this->send_date = value;
	}

	int64 Mail::get_sender_id() const
	{
		return sender_id;
	}

	void Mail::set_sender_id(int64 value)
	{
		this->sender_id = value;
	}

	int64 Mail::get_receiver_id() const
	{
		return receiver_id;
	}

	void Mail::set_receiver_id(int64 value)
	{
		this->receiver_id = value;
	}

	bool Mail::get_item_binded() const
	{
		return item_binded;
	}

	void Mail::set_item_binded(bool value)
	{
		this->item_binded = value;
	}


	bool Mail::is_default_value() const
	{
		if(id != 0)
			return false;

		if(mode != 0)
			return false;

		if(flag != 0)
			return false;

		if(send_date != 0)
			return false;

		if(sender_id != 0)
			return false;

		if(!pwutils::is_default_value(sender_name,64,0))
			return false;

		if(receiver_id != 0)
			return false;

		if(!pwutils::is_default_value(subject,40,0))
			return false;

		if(!pwutils::is_default_value(content,256,0))
			return false;

		if(!pwutils::is_default_value(append_data,64,0))
			return false;

		if(item_binded != false)
			return false;

		return true;
	}

}
