#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_dpo_market.h"

namespace orm
{

	RTTI_TOUCH(DPO_Market);

	DPO_Market::DPO_Market()
		: aid("")
		, goods(0)
		, amount(0)
		, __hash(0)
	{
	}


	DPO_Market::~DPO_Market()
	{
	}

	std::string DPO_Market::rawkey()
	{
		std::string result;
		result.reserve(64);
		return result;
	}

	std::string DPO_Market::getkey()
	{
		return this->rawkey();
	}

	std::string DPO_Market::getmeta()
	{
		return DPO_Market::meta();
	}

	void DPO_Market::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	DPO_Market* DPO_Market::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		DPO_Market* tmp = new DPO_Market();
		tmp->from_bson(__obj);
		return tmp;
	}

	void DPO_Market::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void DPO_Market::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void DPO_Market::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(aid != "")
			__builder.append("aid",aid);
		if(goods != 0)
			__builder.append("goods",goods);
		if(amount != 0)
			__builder.append("amount",amount);
		__obj = __builder.obj();
	}

	void DPO_Market::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void DPO_Market::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void DPO_Market::from_bson(const char* __data,size_t __size)
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

	void DPO_Market::from_bson(const bson::bo& __obj)
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
			case 1297081801864: // aid type: string
				{
					pwutils::bsonToCppVariable(aid,__be);
				}
				break;
			case 2319802516818: // goods type: int64
				{
					pwutils::bsonToCppVariable(goods,__be);
				}
				break;
			case 2836112193824: // amount type: int32
				{
					pwutils::bsonToCppVariable(amount,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 DPO_Market::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(aid.c_str(),aid.length(),_result);

		_result = pwutils::city_hash(&goods,sizeof(goods),_result);

		_result = pwutils::city_hash(&amount,sizeof(amount),_result);

		return _result;
	}

	const char* DPO_Market::get_aid() const
	{
		return aid.c_str();
	}

	void DPO_Market::set_aid(const char* value)
	{
		this->aid = value;
	}

	int64 DPO_Market::get_goods() const
	{
		return goods;
	}

	void DPO_Market::set_goods(int64 value)
	{
		this->goods = value;
	}

	int32 DPO_Market::get_amount() const
	{
		return amount;
	}

	void DPO_Market::set_amount(int32 value)
	{
		this->amount = value;
	}


	bool DPO_Market::is_default_value() const
	{
		if(aid.length() != 0)
			return false;

		if(goods != 0)
			return false;

		if(amount != 0)
			return false;

		return true;
	}

}
