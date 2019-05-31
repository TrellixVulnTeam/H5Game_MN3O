#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_ghotfixcommand.h"

namespace orm
{

	RTTI_TOUCH(GHotfixCommand);

	GHotfixCommand::GHotfixCommand()
		: time(0)
		, text("")
		, __hash(0)
	{
	}


	GHotfixCommand::~GHotfixCommand()
	{
	}

	std::string GHotfixCommand::rawkey()
	{
		std::string result;
		result.reserve(64);

		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)time);
			result.append(tmpbuf);
		}
		return result;
	}

	std::string GHotfixCommand::getkey()
	{
		return this->rawkey();
	}

	std::string GHotfixCommand::getmeta()
	{
		return GHotfixCommand::meta();
	}

	void GHotfixCommand::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	GHotfixCommand* GHotfixCommand::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		GHotfixCommand* tmp = new GHotfixCommand();
		tmp->from_bson(__obj);
		return tmp;
	}

	void GHotfixCommand::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void GHotfixCommand::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void GHotfixCommand::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(time != 0)
			__builder.append("time",time);
		if(text != "")
			__builder.append("text",text);
		__obj = __builder.obj();
	}

	void GHotfixCommand::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void GHotfixCommand::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void GHotfixCommand::from_bson(const char* __data,size_t __size)
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

	void GHotfixCommand::from_bson(const bson::bo& __obj)
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
			case 1851393499417: // time type: int64
				{
					pwutils::bsonToCppVariable(time,__be);
				}
				break;
			case 1945882712741: // text type: string
				{
					pwutils::bsonToCppVariable(text,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 GHotfixCommand::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&time,sizeof(time),_result);

		_result = pwutils::city_hash(text.c_str(),text.length(),_result);

		return _result;
	}

	int64 GHotfixCommand::get_time() const
	{
		return time;
	}

	void GHotfixCommand::set_time(int64 value)
	{
		this->time = value;
	}

	const char* GHotfixCommand::get_text() const
	{
		return text.c_str();
	}

	void GHotfixCommand::set_text(const char* value)
	{
		this->text = value;
	}


	bool GHotfixCommand::is_default_value() const
	{
		if(time != 0)
			return false;

		if(text.length() != 0)
			return false;

		return true;
	}

}
