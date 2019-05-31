#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_namedhuman.h"

namespace orm
{

	RTTI_TOUCH(NamedHuman);

	NamedHuman::NamedHuman()
		: name("")
		, hid(0)
		, __hash(0)
	{
	}


	NamedHuman::~NamedHuman()
	{
	}

	std::string NamedHuman::rawkey()
	{
		std::string result;
		result.reserve(64);

		result.append(name.c_str());
		return result;
	}

	std::string NamedHuman::getkey()
	{
		return this->rawkey();
	}

	std::string NamedHuman::getmeta()
	{
		return NamedHuman::meta();
	}

	void NamedHuman::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	NamedHuman* NamedHuman::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		NamedHuman* tmp = new NamedHuman();
		tmp->from_bson(__obj);
		return tmp;
	}

	void NamedHuman::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void NamedHuman::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void NamedHuman::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(name != "")
			__builder.append("name",name);
		if(hid != 0)
			__builder.append("hid",hid);
		__obj = __builder.obj();
	}

	void NamedHuman::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void NamedHuman::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void NamedHuman::from_bson(const char* __data,size_t __size)
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

	void NamedHuman::from_bson(const bson::bo& __obj)
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
			case 1327146693063: // hid type: int64
				{
					pwutils::bsonToCppVariable(hid,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 NamedHuman::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&name,sizeof(name),_result);

		_result = pwutils::city_hash(&hid,sizeof(hid),_result);

		return _result;
	}

	const char* NamedHuman::get_name() const
	{
		return name.c_str();
	}

	void NamedHuman::set_name(const char* value)
	{
		this->name = value;
	}

	int64 NamedHuman::get_hid() const
	{
		return hid;
	}

	void NamedHuman::set_hid(int64 value)
	{
		this->hid = value;
	}


	bool NamedHuman::is_default_value() const
	{
		if(name.length() != 0)
			return false;

		if(hid != 0)
			return false;

		return true;
	}

}
