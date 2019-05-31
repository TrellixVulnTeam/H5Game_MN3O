#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_passporthuman.h"

namespace orm
{

	RTTI_TOUCH(PassportHuman);

	PassportHuman::PassportHuman()
		: passport("")
		, __hash(0)
	{
	}


	PassportHuman::~PassportHuman()
	{
	}

	std::string PassportHuman::rawkey()
	{
		std::string result;
		result.reserve(64);

		result.append(passport.c_str());
		return result;
	}

	std::string PassportHuman::getkey()
	{
		return this->rawkey();
	}

	std::string PassportHuman::getmeta()
	{
		return PassportHuman::meta();
	}

	void PassportHuman::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	PassportHuman* PassportHuman::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		PassportHuman* tmp = new PassportHuman();
		tmp->from_bson(__obj);
		return tmp;
	}

	void PassportHuman::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void PassportHuman::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void PassportHuman::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(passport != "")
			__builder.append("passport",passport);

		if(!hid.is_default_value())
		{
			mongo::BSONArrayBuilder hid_builder;
			for(size_t i = 0; i < hid.size(); ++i)
			{
				hid_builder.append(hid[i]);
			}
			__builder.appendArray("hid",hid_builder.obj());
		}


		__obj = __builder.obj();
	}

	void PassportHuman::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportHuman::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportHuman::from_bson(const char* __data,size_t __size)
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

	void PassportHuman::from_bson(const bson::bo& __obj)
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
			case 3831688010902: // passport type: string
				{
					pwutils::bsonToCppVariable(passport,__be);
				}
				break;
			case 1327146693063: // hid type: int64
				{
					hid.cleanup();
					mongo::BSONObj aobj = __be.Obj();
					mongo::BSONObjIterator aiter(aobj);
					while(aiter.more())
					{
						mongo::BSONElement ae = aiter.next();
						int64 tmpvar;
						pwutils::bsonToCppVariable(tmpvar,ae);
						hid.push_back(tmpvar);
					}
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 PassportHuman::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&passport,sizeof(passport),_result);

		_result = hid.hash_make(_result);

		return _result;
	}

	const char* PassportHuman::get_passport() const
	{
		return passport.c_str();
	}

	void PassportHuman::set_passport(const char* value)
	{
		this->passport = value;
	}


	bool PassportHuman::is_default_value() const
	{
		if(passport.length() != 0)
			return false;

		if(!hid.is_default_value())
			return false;

		return true;
	}

}
