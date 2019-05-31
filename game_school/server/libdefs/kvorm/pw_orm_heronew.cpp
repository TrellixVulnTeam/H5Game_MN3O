#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_heronew.h"

namespace orm
{

	RTTI_TOUCH(HeroNew);

	HeroNew::HeroNew()
		: hid(0)
		, id(0)
		, did(0)
		, state(0)
		, star(0)
		, activated(false)
		, assistance_loc(0)
		, rank(0)
		, rank_item_flag(0)
		, __hash(0)
	{
	}


	HeroNew::~HeroNew()
	{
	}

	std::string HeroNew::rawkey()
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

	std::string HeroNew::getkey()
	{
		return this->rawkey();
	}

	std::string HeroNew::getmeta()
	{
		std::string result;
		result.reserve(64);
		result.append(meta());
		result.append(".");
		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)hid);
			result.append(tmpbuf);
		}
		return result;
	}

	void HeroNew::set_autoincr(int64 key)
	{
		id = key;
	}

	HeroNew* HeroNew::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		HeroNew* tmp = new HeroNew();
		tmp->from_bson(__obj);
		return tmp;
	}

	void HeroNew::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void HeroNew::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void HeroNew::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(hid != 0)
			__builder.append("hid",hid);
		if(id != 0)
			__builder.append("id",id);
		if(did != 0)
			__builder.append("did",did);
		if(state != 0)
			__builder.append("state",state);
		if(star != 0)
			__builder.append("star",star);
		if(activated != false)
			__builder.append("activated",activated);
		if(assistance_loc != 0)
			__builder.append("assistance_loc",assistance_loc);
		if(rank != 0)
			__builder.append("rank",rank);
		if(rank_item_flag != 0)
			__builder.append("rank_item_flag",rank_item_flag);
		__obj = __builder.obj();
	}

	void HeroNew::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void HeroNew::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void HeroNew::from_bson(const char* __data,size_t __size)
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

	void HeroNew::from_bson(const bson::bo& __obj)
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
			case 1327146693063: // hid type: int64
				{
					pwutils::bsonToCppVariable(hid,__be);
				}
				break;
			case 880468309535: // id type: int64
				{
					pwutils::bsonToCppVariable(id,__be);
				}
				break;
			case 1309966755235: // did type: int32
				{
					pwutils::bsonToCppVariable(did,__be);
				}
				break;
			case 2342674870985: // state type: int16
				{
					pwutils::bsonToCppVariable(state,__be);
				}
				break;
			case 1898636078794: // star type: int16
				{
					pwutils::bsonToCppVariable(star,__be);
				}
				break;
			case 4077442710521: // activated type: bool
				{
					pwutils::bsonToCppVariable(activated,__be);
				}
				break;
			case 6370870730253: // assistance_loc type: int16
				{
					pwutils::bsonToCppVariable(assistance_loc,__be);
				}
				break;
			case 1838503964196: // rank type: int16
				{
					pwutils::bsonToCppVariable(rank,__be);
				}
				break;
			case 6266913655745: // rank_item_flag type: int16
				{
					pwutils::bsonToCppVariable(rank_item_flag,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 HeroNew::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&hid,sizeof(hid),_result);

		_result = pwutils::city_hash(&id,sizeof(id),_result);

		_result = pwutils::city_hash(&did,sizeof(did),_result);

		_result = pwutils::city_hash(&state,sizeof(state),_result);

		_result = pwutils::city_hash(&star,sizeof(star),_result);

		_result = pwutils::city_hash(&activated,sizeof(activated),_result);

		_result = pwutils::city_hash(&assistance_loc,sizeof(assistance_loc),_result);

		_result = pwutils::city_hash(&rank,sizeof(rank),_result);

		_result = pwutils::city_hash(&rank_item_flag,sizeof(rank_item_flag),_result);

		return _result;
	}

	int64 HeroNew::get_hid() const
	{
		return hid;
	}

	void HeroNew::set_hid(int64 value)
	{
		this->hid = value;
	}

	int64 HeroNew::get_id() const
	{
		return id;
	}

	void HeroNew::set_id(int64 value)
	{
		this->id = value;
	}

	int32 HeroNew::get_did() const
	{
		return did;
	}

	void HeroNew::set_did(int32 value)
	{
		this->did = value;
	}

	int16 HeroNew::get_state() const
	{
		return state;
	}

	void HeroNew::set_state(int16 value)
	{
		this->state = value;
	}

	int16 HeroNew::get_star() const
	{
		return star;
	}

	void HeroNew::set_star(int16 value)
	{
		this->star = value;
	}

	bool HeroNew::get_activated() const
	{
		return activated;
	}

	void HeroNew::set_activated(bool value)
	{
		this->activated = value;
	}

	int16 HeroNew::get_assistance_loc() const
	{
		return assistance_loc;
	}

	void HeroNew::set_assistance_loc(int16 value)
	{
		this->assistance_loc = value;
	}

	int16 HeroNew::get_rank() const
	{
		return rank;
	}

	void HeroNew::set_rank(int16 value)
	{
		this->rank = value;
	}

	int16 HeroNew::get_rank_item_flag() const
	{
		return rank_item_flag;
	}

	void HeroNew::set_rank_item_flag(int16 value)
	{
		this->rank_item_flag = value;
	}


	bool HeroNew::is_default_value() const
	{
		if(hid != 0)
			return false;

		if(id != 0)
			return false;

		if(did != 0)
			return false;

		if(state != 0)
			return false;

		if(star != 0)
			return false;

		if(activated != false)
			return false;

		if(assistance_loc != 0)
			return false;

		if(rank != 0)
			return false;

		if(rank_item_flag != 0)
			return false;

		return true;
	}

}
