#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_passportitems.h"

namespace orm
{

	RTTI_TOUCH(PassportItems);

	PassportItems::PassportItems()
		: passport("")
		, container(0)
		, size(0)
		, __hash(0)
	{
	}


	PassportItems::~PassportItems()
	{
	}

	std::string PassportItems::rawkey()
	{
		std::string result;
		result.reserve(64);

		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)container);
			result.append(tmpbuf);
		}
		return result;
	}

	std::string PassportItems::getkey()
	{
		return this->rawkey();
	}

	std::string PassportItems::getmeta()
	{
		std::string result;
		result.reserve(64);
		result.append(meta());
		result.append(".");
		result.append(passport.c_str());
		return result;
	}

	void PassportItems::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	PassportItems* PassportItems::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		PassportItems* tmp = new PassportItems();
		tmp->from_bson(__obj);
		return tmp;
	}

	void PassportItems::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void PassportItems::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void PassportItems::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(passport != "")
			__builder.append("passport",passport);
		if(container != 0)
			__builder.append("container",container);
		if(size != 0)
			__builder.append("size",size);

		if(!item_uuids.is_default_value())
		{
			mongo::BSONArrayBuilder item_uuids_builder;
			for(size_t i = 0; i < item_uuids.size(); ++i)
			{
				item_uuids_builder.append(item_uuids[i]);
			}
			__builder.appendArray("item_uuids",item_uuids_builder.obj());
		}


		__obj = __builder.obj();
	}

	void PassportItems::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportItems::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportItems::from_bson(const char* __data,size_t __size)
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

	void PassportItems::from_bson(const bson::bo& __obj)
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
			case 4137267643557: // container type: int16
				{
					pwutils::bsonToCppVariable(container,__be);
				}
				break;
			case 1902930860581: // size type: int16
				{
					pwutils::bsonToCppVariable(size,__be);
				}
				break;
			case 4639465560868: // item_uuids type: int64
				{
					item_uuids.cleanup();
					mongo::BSONObj aobj = __be.Obj();
					mongo::BSONObjIterator aiter(aobj);
					while(aiter.more())
					{
						mongo::BSONElement ae = aiter.next();
						int64 tmpvar;
						pwutils::bsonToCppVariable(tmpvar,ae);
						item_uuids.push_back(tmpvar);
					}
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 PassportItems::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&passport,sizeof(passport),_result);

		_result = pwutils::city_hash(&container,sizeof(container),_result);

		_result = pwutils::city_hash(&size,sizeof(size),_result);

		_result = item_uuids.hash_make(_result);

		return _result;
	}

	const char* PassportItems::get_passport() const
	{
		return passport.c_str();
	}

	void PassportItems::set_passport(const char* value)
	{
		this->passport = value;
	}

	int16 PassportItems::get_container() const
	{
		return container;
	}

	void PassportItems::set_container(int16 value)
	{
		this->container = value;
	}

	int16 PassportItems::get_size() const
	{
		return size;
	}

	void PassportItems::set_size(int16 value)
	{
		this->size = value;
	}


	bool PassportItems::is_default_value() const
	{
		if(passport.length() != 0)
			return false;

		if(container != 0)
			return false;

		if(size != 0)
			return false;

		if(!item_uuids.is_default_value())
			return false;

		return true;
	}

}
