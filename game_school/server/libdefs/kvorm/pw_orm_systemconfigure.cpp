#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_systemconfigure.h"

namespace orm
{

	RTTI_TOUCH(SystemConfigure);

	SystemConfigure::SystemConfigure()
		: id(0)
		, ivar1(0)
		, ivar2(0)
		, svar("")
		, __hash(0)
	{
	}


	SystemConfigure::~SystemConfigure()
	{
	}

	std::string SystemConfigure::rawkey()
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

	std::string SystemConfigure::getkey()
	{
		return this->rawkey();
	}

	std::string SystemConfigure::getmeta()
	{
		return SystemConfigure::meta();
	}

	void SystemConfigure::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	SystemConfigure* SystemConfigure::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		SystemConfigure* tmp = new SystemConfigure();
		tmp->from_bson(__obj);
		return tmp;
	}

	void SystemConfigure::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void SystemConfigure::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void SystemConfigure::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(id != 0)
			__builder.append("id",id);
		if(ivar1 != 0)
			__builder.append("ivar1",ivar1);
		if(ivar2 != 0)
			__builder.append("ivar2",ivar2);
		if(svar != "")
			__builder.append("svar",svar);
		__obj = __builder.obj();
	}

	void SystemConfigure::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void SystemConfigure::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void SystemConfigure::from_bson(const char* __data,size_t __size)
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

	void SystemConfigure::from_bson(const bson::bo& __obj)
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
			case 880468309535: // id type: int32
				{
					pwutils::bsonToCppVariable(id,__be);
				}
				break;
			case 2075593878939: // ivar1 type: int64
				{
					pwutils::bsonToCppVariable(ivar1,__be);
				}
				break;
			case 2079888846236: // ivar2 type: int64
				{
					pwutils::bsonToCppVariable(ivar2,__be);
				}
				break;
			case 1907226047708: // svar type: string
				{
					pwutils::bsonToCppVariable(svar,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 SystemConfigure::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&id,sizeof(id),_result);

		_result = pwutils::city_hash(&ivar1,sizeof(ivar1),_result);

		_result = pwutils::city_hash(&ivar2,sizeof(ivar2),_result);

		_result = pwutils::city_hash(svar.c_str(),svar.length(),_result);

		return _result;
	}

	int32 SystemConfigure::get_id() const
	{
		return id;
	}

	void SystemConfigure::set_id(int32 value)
	{
		this->id = value;
	}

	int64 SystemConfigure::get_ivar1() const
	{
		return ivar1;
	}

	void SystemConfigure::set_ivar1(int64 value)
	{
		this->ivar1 = value;
	}

	int64 SystemConfigure::get_ivar2() const
	{
		return ivar2;
	}

	void SystemConfigure::set_ivar2(int64 value)
	{
		this->ivar2 = value;
	}

	const char* SystemConfigure::get_svar() const
	{
		return svar.c_str();
	}

	void SystemConfigure::set_svar(const char* value)
	{
		this->svar = value;
	}


	bool SystemConfigure::is_default_value() const
	{
		if(id != 0)
			return false;

		if(ivar1 != 0)
			return false;

		if(ivar2 != 0)
			return false;

		if(svar.length() != 0)
			return false;

		return true;
	}

}
