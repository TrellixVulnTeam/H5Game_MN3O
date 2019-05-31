#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_dpo_charge.h"

namespace orm
{

	RTTI_TOUCH(DPO_Charge);

	DPO_Charge::DPO_Charge()
		: gold(0)
		, goods(0)
		, amount(0)
		, rmb(0.0f)
		, pubacct_rmb(0.0f)
		, req_is_gameseller(false)
		, __hash(0)
	{
	}


	DPO_Charge::~DPO_Charge()
	{
	}

	std::string DPO_Charge::rawkey()
	{
		std::string result;
		result.reserve(64);
		return result;
	}

	std::string DPO_Charge::getkey()
	{
		return this->rawkey();
	}

	std::string DPO_Charge::getmeta()
	{
		return DPO_Charge::meta();
	}

	void DPO_Charge::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	DPO_Charge* DPO_Charge::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		DPO_Charge* tmp = new DPO_Charge();
		tmp->from_bson(__obj);
		return tmp;
	}

	void DPO_Charge::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void DPO_Charge::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void DPO_Charge::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(gold != 0)
			__builder.append("gold",gold);
		if(goods != 0)
			__builder.append("goods",goods);
		if(amount != 0)
			__builder.append("amount",amount);
		if(rmb != 0.0f)
			__builder.append("rmb",rmb);
		if(pubacct_rmb != 0.0f)
			__builder.append("pubacct_rmb",pubacct_rmb);
		if(req_is_gameseller != false)
			__builder.append("req_is_gameseller",req_is_gameseller);
		__obj = __builder.obj();
	}

	void DPO_Charge::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void DPO_Charge::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void DPO_Charge::from_bson(const char* __data,size_t __size)
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

	void DPO_Charge::from_bson(const bson::bo& __obj)
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
			case 1812709671404: // gold type: int64
				{
					pwutils::bsonToCppVariable(gold,__be);
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
			case 1378686472747: // rmb type: float
				{
					pwutils::bsonToCppVariable(rmb,__be);
				}
				break;
			case 4957643118020: // pubacct_rmb type: float
				{
					pwutils::bsonToCppVariable(pubacct_rmb,__be);
				}
				break;
			case 7710658728129: // req_is_gameseller type: bool
				{
					pwutils::bsonToCppVariable(req_is_gameseller,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 DPO_Charge::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&gold,sizeof(gold),_result);

		_result = pwutils::city_hash(&goods,sizeof(goods),_result);

		_result = pwutils::city_hash(&amount,sizeof(amount),_result);

		_result = pwutils::city_hash(&rmb,sizeof(rmb),_result);

		_result = pwutils::city_hash(&pubacct_rmb,sizeof(pubacct_rmb),_result);

		_result = pwutils::city_hash(&req_is_gameseller,sizeof(req_is_gameseller),_result);

		return _result;
	}

	int64 DPO_Charge::get_gold() const
	{
		return gold;
	}

	void DPO_Charge::set_gold(int64 value)
	{
		this->gold = value;
	}

	int64 DPO_Charge::get_goods() const
	{
		return goods;
	}

	void DPO_Charge::set_goods(int64 value)
	{
		this->goods = value;
	}

	int32 DPO_Charge::get_amount() const
	{
		return amount;
	}

	void DPO_Charge::set_amount(int32 value)
	{
		this->amount = value;
	}

	float DPO_Charge::get_rmb() const
	{
		return rmb;
	}

	void DPO_Charge::set_rmb(float value)
	{
		this->rmb = value;
	}

	float DPO_Charge::get_pubacct_rmb() const
	{
		return pubacct_rmb;
	}

	void DPO_Charge::set_pubacct_rmb(float value)
	{
		this->pubacct_rmb = value;
	}

	bool DPO_Charge::get_req_is_gameseller() const
	{
		return req_is_gameseller;
	}

	void DPO_Charge::set_req_is_gameseller(bool value)
	{
		this->req_is_gameseller = value;
	}


	bool DPO_Charge::is_default_value() const
	{
		if(gold != 0)
			return false;

		if(goods != 0)
			return false;

		if(amount != 0)
			return false;

		if(rmb != 0.0f)
			return false;

		if(pubacct_rmb != 0.0f)
			return false;

		if(req_is_gameseller != false)
			return false;

		return true;
	}

}
