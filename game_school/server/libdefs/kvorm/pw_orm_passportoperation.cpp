#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_passportoperation.h"
#include "kvorm/pw_orm_dpo_charge.h"
#include "kvorm/pw_orm_dpo_market.h"

namespace orm
{

	RTTI_TOUCH(PassportOperation);

	PassportOperation::PassportOperation()
		: id(0)
		, passport("")
		, func_name("")
		, func_hash(0)
		, dpo_charge(NULL)
		, dpo_market(NULL)
		, __hash(0)
	{
	}

	PassportOperation::PassportOperation(const PassportOperation& v)
		: id(0)
		, passport("")
		, func_name("")
		, func_hash(0)
		, dpo_charge(NULL)
		, dpo_market(NULL)
		, __hash(0)
	{
		this->from_obj(&v);
	}

	PassportOperation::~PassportOperation()
	{
		_safe_delete(dpo_charge);
		_safe_delete(dpo_market);
	}

	std::string PassportOperation::rawkey()
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

	std::string PassportOperation::getkey()
	{
		return this->rawkey();
	}

	std::string PassportOperation::getmeta()
	{
		std::string result;
		result.reserve(64);
		result.append(meta());
		result.append(".");
		result.append(passport.c_str());
		return result;
	}

	void PassportOperation::set_autoincr(int64 key)
	{
		id = key;
	}

	PassportOperation* PassportOperation::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		PassportOperation* tmp = new PassportOperation();
		tmp->from_bson(__obj);
		return tmp;
	}

	void PassportOperation::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void PassportOperation::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void PassportOperation::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(id != 0)
			__builder.append("id",id);
		if(passport != "")
			__builder.append("passport",passport);
		if(func_name != "")
			__builder.append("func_name",func_name);
		if(func_hash != 0)
			__builder.append("func_hash",func_hash);
		if(dpo_charge!= NULL && !dpo_charge->is_default_value())
		{
			bson::bo __tmpobj;
			dpo_charge->to_bson(__tmpobj);
			__builder.append("dpo_charge",__tmpobj);
		}
		if(dpo_market!= NULL && !dpo_market->is_default_value())
		{
			bson::bo __tmpobj;
			dpo_market->to_bson(__tmpobj);
			__builder.append("dpo_market",__tmpobj);
		}
		__obj = __builder.obj();
	}

	void PassportOperation::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportOperation::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void PassportOperation::from_bson(const char* __data,size_t __size)
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

	void PassportOperation::from_bson(const bson::bo& __obj)
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
			case 3831688010902: // passport type: string
				{
					pwutils::bsonToCppVariable(passport,__be);
				}
				break;
			case 4037432330018: // func_name type: string
				{
					pwutils::bsonToCppVariable(func_name,__be);
				}
				break;
			case 4050303744149: // func_hash type: int64
				{
					pwutils::bsonToCppVariable(func_hash,__be);
				}
				break;
			case 4451694039200: // dpo_charge type: DPO_Charge
				{
					if(dpo_charge == NULL)
						dpo_charge = new DPO_Charge();
					bson::bo __obj = __be.Obj();
					dpo_charge->from_bson(__obj);
				}
				break;
			case 4562735110140: // dpo_market type: DPO_Market
				{
					if(dpo_market == NULL)
						dpo_market = new DPO_Market();
					bson::bo __obj = __be.Obj();
					dpo_market->from_bson(__obj);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 PassportOperation::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&id,sizeof(id),_result);

		_result = pwutils::city_hash(&passport,sizeof(passport),_result);

		_result = pwutils::city_hash(&func_name,sizeof(func_name),_result);

		_result = pwutils::city_hash(&func_hash,sizeof(func_hash),_result);

		if(dpo_charge != NULL)
			_result = dpo_charge->hash_make(_result);

		if(dpo_market != NULL)
			_result = dpo_market->hash_make(_result);

		return _result;
	}

	int64 PassportOperation::get_id() const
	{
		return id;
	}

	void PassportOperation::set_id(int64 value)
	{
		this->id = value;
	}

	const char* PassportOperation::get_passport() const
	{
		return passport.c_str();
	}

	void PassportOperation::set_passport(const char* value)
	{
		this->passport = value;
	}

	const char* PassportOperation::get_func_name() const
	{
		return func_name.c_str();
	}

	void PassportOperation::set_func_name(const char* value)
	{
		this->func_name = value;
	}

	int64 PassportOperation::get_func_hash() const
	{
		return func_hash;
	}

	void PassportOperation::set_func_hash(int64 value)
	{
		this->func_hash = value;
	}

	DPO_Charge* PassportOperation::mutable_dpo_charge()
	{
		if(this->dpo_charge == NULL)
			this->dpo_charge = new DPO_Charge();
		return this->dpo_charge;
	}

	DPO_Market* PassportOperation::mutable_dpo_market()
	{
		if(this->dpo_market == NULL)
			this->dpo_market = new DPO_Market();
		return this->dpo_market;
	}


	bool PassportOperation::is_default_value() const
	{
		if(id != 0)
			return false;

		if(passport.length() != 0)
			return false;

		if(func_name.length() != 0)
			return false;

		if(func_hash != 0)
			return false;

		if(dpo_charge != NULL && !dpo_charge->is_default_value())
			return false;

		if(dpo_market != NULL && !dpo_market->is_default_value())
			return false;

		return true;
	}

}
