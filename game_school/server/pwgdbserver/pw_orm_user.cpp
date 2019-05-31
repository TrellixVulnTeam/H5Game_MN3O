#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "pw_orm_user.h"

namespace orm
{

	RTTI_TOUCH(User);

	User::User()
		: name("")
		, pswd("")
		, sysuser(false)
		, __hash(0)
	{
	}

	User::~User()
	{
	}

	std::string User::rawkey()
	{
		std::string result;
		result.reserve(64);
		return result;
	}

	std::string User::getkey()
	{
		return this->rawkey();
	}

	std::string User::getmeta()
	{
		return User::meta();
	}

	void User::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	User* User::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		User* tmp = new User();
		tmp->from_bson(__obj);
		return tmp;
	}

	void User::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void User::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void User::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(name != "")
			__builder.append("name",name);
		if(pswd != "")
			__builder.append("pswd",pswd);
		if(sysuser != false)
			__builder.append("sysuser",sysuser);
		__obj = __builder.obj();
	}

	void User::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void User::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void User::from_bson(const char* __data,size_t __size)
	{
		bson::bo __obj(__data);
		pwassert(__obj.objsize() == __size);
		from_bson(__obj);
	}

	void User::from_bson(const bson::bo& __obj)
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
			case 1791250331439: // name type: string
				{
					pwutils::bsonToCppVariable(name,__be);
				}
				break;
			case 1915809189412: // pswd type: string
				{
					pwutils::bsonToCppVariable(pswd,__be);
				}
				break;
			case 3427387595580: // sysuser type: bool
				{
					pwutils::bsonToCppVariable(sysuser,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 User::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&name,sizeof(name),_result);

		_result = pwutils::city_hash(&pswd,sizeof(pswd),_result);

		_result = pwutils::city_hash(&sysuser,sizeof(sysuser),_result);

		return _result;
	}

	const char* User::get_name() const
	{
		return name.c_str();
	}

	void User::set_name(const char* value)
	{
		this->name = value;
	}

	const char* User::get_pswd() const
	{
		return pswd.c_str();
	}

	void User::set_pswd(const char* value)
	{
		this->pswd = value;
	}

	bool User::get_sysuser() const
	{
		return sysuser;
	}

	void User::set_sysuser(bool value)
	{
		this->sysuser = value;
	}


	bool User::is_default_value() const
	{
		if(name.length() != 0)
			return false;

		if(pswd.length() != 0)
			return false;

		if(sysuser != false)
			return false;

		return true;
	}

}
