#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_shopitem.h"

namespace orm
{

	RTTI_TOUCH(ShopItem);

	ShopItem::ShopItem()
		: cfg_id(0)
		, sold_count(0)
		, __hash(0)
	{
	}


	ShopItem::~ShopItem()
	{
	}

	std::string ShopItem::rawkey()
	{
		std::string result;
		result.reserve(64);

		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)cfg_id);
			result.append(tmpbuf);
		}
		return result;
	}

	std::string ShopItem::getkey()
	{
		return this->rawkey();
	}

	std::string ShopItem::getmeta()
	{
		return ShopItem::meta();
	}

	void ShopItem::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	ShopItem* ShopItem::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		ShopItem* tmp = new ShopItem();
		tmp->from_bson(__obj);
		return tmp;
	}

	void ShopItem::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void ShopItem::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void ShopItem::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(cfg_id != 0)
			__builder.append("cfg_id",cfg_id);
		if(sold_count != 0)
			__builder.append("sold_count",sold_count);
		__obj = __builder.obj();
	}

	void ShopItem::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void ShopItem::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void ShopItem::from_bson(const char* __data,size_t __size)
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

	void ShopItem::from_bson(const bson::bo& __obj)
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
			case 2595511214482: // cfg_id type: int32
				{
					pwutils::bsonToCppVariable(cfg_id,__be);
				}
				break;
			case 4647884265664: // sold_count type: int32
				{
					pwutils::bsonToCppVariable(sold_count,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 ShopItem::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&cfg_id,sizeof(cfg_id),_result);

		_result = pwutils::city_hash(&sold_count,sizeof(sold_count),_result);

		return _result;
	}

	int32 ShopItem::get_cfg_id() const
	{
		return cfg_id;
	}

	void ShopItem::set_cfg_id(int32 value)
	{
		this->cfg_id = value;
	}

	int32 ShopItem::get_sold_count() const
	{
		return sold_count;
	}

	void ShopItem::set_sold_count(int32 value)
	{
		this->sold_count = value;
	}


	bool ShopItem::is_default_value() const
	{
		if(cfg_id != 0)
			return false;

		if(sold_count != 0)
			return false;

		return true;
	}

}
