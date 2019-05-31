#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_herocard.h"

namespace orm
{

	RTTI_TOUCH(HeroCard);

	HeroCard::HeroCard()
		: hid(0)
		, id(0)
		, did(0)
		, state(0)
		, level(1)
		, star(0)
		, activated(false)
		, equip_loc(0)
		, guard_loc(0)
		, guard_level(1)
		, skill(0)
		, __hash(0)
	{
	}


	HeroCard::~HeroCard()
	{
	}

	std::string HeroCard::rawkey()
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

	std::string HeroCard::getkey()
	{
		return this->rawkey();
	}

	std::string HeroCard::getmeta()
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

	void HeroCard::set_autoincr(int64 key)
	{
		id = key;
	}

	HeroCard* HeroCard::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		HeroCard* tmp = new HeroCard();
		tmp->from_bson(__obj);
		return tmp;
	}

	void HeroCard::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void HeroCard::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void HeroCard::to_bson(bson::bo& __obj) const
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
		if(level != 1)
			__builder.append("level",level);
		if(star != 0)
			__builder.append("star",star);
		if(activated != false)
			__builder.append("activated",activated);
		if(equip_loc != 0)
			__builder.append("equip_loc",equip_loc);
		if(guard_loc != 0)
			__builder.append("guard_loc",guard_loc);
		if(guard_level != 1)
			__builder.append("guard_level",guard_level);
		if(skill != 0)
			__builder.append("skill",skill);
		__obj = __builder.obj();
	}

	void HeroCard::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void HeroCard::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void HeroCard::from_bson(const char* __data,size_t __size)
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

	void HeroCard::from_bson(const bson::bo& __obj)
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
			case 2304072786580: // level type: int16
				{
					pwutils::bsonToCppVariable(level,__be);
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
			case 4127756483241: // equip_loc type: int16
				{
					pwutils::bsonToCppVariable(equip_loc,__be);
				}
				break;
			case 4054587339874: // guard_loc type: int16
				{
					pwutils::bsonToCppVariable(guard_loc,__be);
				}
				break;
			case 4991771763498: // guard_level type: int16
				{
					pwutils::bsonToCppVariable(guard_level,__be);
				}
				break;
			case 2334064839821: // skill type: int32
				{
					pwutils::bsonToCppVariable(skill,__be);
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 HeroCard::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&hid,sizeof(hid),_result);

		_result = pwutils::city_hash(&id,sizeof(id),_result);

		_result = pwutils::city_hash(&did,sizeof(did),_result);

		_result = pwutils::city_hash(&state,sizeof(state),_result);

		_result = pwutils::city_hash(&level,sizeof(level),_result);

		_result = pwutils::city_hash(&star,sizeof(star),_result);

		_result = pwutils::city_hash(&activated,sizeof(activated),_result);

		_result = pwutils::city_hash(&equip_loc,sizeof(equip_loc),_result);

		_result = pwutils::city_hash(&guard_loc,sizeof(guard_loc),_result);

		_result = pwutils::city_hash(&guard_level,sizeof(guard_level),_result);

		_result = pwutils::city_hash(&skill,sizeof(skill),_result);

		return _result;
	}

	int64 HeroCard::get_hid() const
	{
		return hid;
	}

	void HeroCard::set_hid(int64 value)
	{
		this->hid = value;
	}

	int64 HeroCard::get_id() const
	{
		return id;
	}

	void HeroCard::set_id(int64 value)
	{
		this->id = value;
	}

	int32 HeroCard::get_did() const
	{
		return did;
	}

	void HeroCard::set_did(int32 value)
	{
		this->did = value;
	}

	int16 HeroCard::get_state() const
	{
		return state;
	}

	void HeroCard::set_state(int16 value)
	{
		this->state = value;
	}

	int16 HeroCard::get_level() const
	{
		return level;
	}

	void HeroCard::set_level(int16 value)
	{
		this->level = value;
	}

	int16 HeroCard::get_star() const
	{
		return star;
	}

	void HeroCard::set_star(int16 value)
	{
		this->star = value;
	}

	bool HeroCard::get_activated() const
	{
		return activated;
	}

	void HeroCard::set_activated(bool value)
	{
		this->activated = value;
	}

	int16 HeroCard::get_equip_loc() const
	{
		return equip_loc;
	}

	void HeroCard::set_equip_loc(int16 value)
	{
		this->equip_loc = value;
	}

	int16 HeroCard::get_guard_loc() const
	{
		return guard_loc;
	}

	void HeroCard::set_guard_loc(int16 value)
	{
		this->guard_loc = value;
	}

	int16 HeroCard::get_guard_level() const
	{
		return guard_level;
	}

	void HeroCard::set_guard_level(int16 value)
	{
		this->guard_level = value;
	}

	int32 HeroCard::get_skill() const
	{
		return skill;
	}

	void HeroCard::set_skill(int32 value)
	{
		this->skill = value;
	}


	bool HeroCard::is_default_value() const
	{
		if(hid != 0)
			return false;

		if(id != 0)
			return false;

		if(did != 0)
			return false;

		if(state != 0)
			return false;

		if(level != 1)
			return false;

		if(star != 0)
			return false;

		if(activated != false)
			return false;

		if(equip_loc != 0)
			return false;

		if(guard_loc != 0)
			return false;

		if(guard_level != 1)
			return false;

		if(skill != 0)
			return false;

		return true;
	}

}
