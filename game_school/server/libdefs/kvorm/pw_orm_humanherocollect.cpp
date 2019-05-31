#include "kvdb/pw_bsontocpp.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "kvorm/pw_orm_humanherocollect.h"

namespace orm
{

	RTTI_TOUCH(HumanHeroCollect);

	HumanHeroCollect::HumanHeroCollect()
		: hid(0)
		, is_open_high(false)
		, last_random_time(0)
		, __hash(0)
	{
		memset(last_free_times,0,sizeof(last_free_times));
		memset(collect_energyes,0,sizeof(collect_energyes));
		memset(low_records,0,sizeof(low_records));
		memset(middle_records,0,sizeof(middle_records));
		memset(high_records,0,sizeof(high_records));
	}


	HumanHeroCollect::~HumanHeroCollect()
	{
	}

	std::string HumanHeroCollect::rawkey()
	{
		std::string result;
		result.reserve(64);
		return result;
	}

	std::string HumanHeroCollect::getkey()
	{
		std::string result;
		result.reserve(64);
		{
			char tmpbuf[64] = "";
			pwutils::itoa(tmpbuf,(int64)hid);
			result.append(tmpbuf);
		}
		return result;
	}

	std::string HumanHeroCollect::getmeta()
	{
		return HumanHeroCollect::meta();
	}

	void HumanHeroCollect::set_autoincr(int64 key)
	{
		pwassert(false);
	}

	HumanHeroCollect* HumanHeroCollect::clone() const
	{
		bson::bo __obj;
		to_bson(__obj);
		HumanHeroCollect* tmp = new HumanHeroCollect();
		tmp->from_bson(__obj);
		return tmp;
	}

	void HumanHeroCollect::to_snappy_buffer(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		snappy::Compress(__obj.objdata(),__obj.objsize(),&__buf);
	}

	void HumanHeroCollect::to_bson(std::string& __buf) const
	{
		bson::bo __obj;
		to_bson(__obj);
		__buf = std::string(__obj.objdata(),__obj.objsize());
	}

	void HumanHeroCollect::to_bson(bson::bo& __obj) const
	{
		mongo::BSONObjBuilder __builder;
		__builder.append("_T",meta());
		if(hid != 0)
			__builder.append("hid",hid);
		if(is_open_high != false)
			__builder.append("is_open_high",is_open_high);
		if(last_random_time != 0)
			__builder.append("last_random_time",last_random_time);

		if(!pwutils::is_default_value(last_free_times,3,0))
		{
			mongo::BSONArrayBuilder last_free_times_builder;
			for(size_t i = 0; i < 3; ++i)
			{
				last_free_times_builder.append(last_free_times[i]);
			}
			__builder.appendArray("last_free_times",last_free_times_builder.obj());
		}


		if(!pwutils::is_default_value(collect_energyes,3,0))
		{
			mongo::BSONArrayBuilder collect_energyes_builder;
			for(size_t i = 0; i < 3; ++i)
			{
				collect_energyes_builder.append(collect_energyes[i]);
			}
			__builder.appendArray("collect_energyes",collect_energyes_builder.obj());
		}


		if(!pwutils::is_default_value(low_records,2,0))
		{
			mongo::BSONArrayBuilder low_records_builder;
			for(size_t i = 0; i < 2; ++i)
			{
				low_records_builder.append(low_records[i]);
			}
			__builder.appendArray("low_records",low_records_builder.obj());
		}


		if(!pwutils::is_default_value(middle_records,2,0))
		{
			mongo::BSONArrayBuilder middle_records_builder;
			for(size_t i = 0; i < 2; ++i)
			{
				middle_records_builder.append(middle_records[i]);
			}
			__builder.appendArray("middle_records",middle_records_builder.obj());
		}


		if(!pwutils::is_default_value(high_records,2,0))
		{
			mongo::BSONArrayBuilder high_records_builder;
			for(size_t i = 0; i < 2; ++i)
			{
				high_records_builder.append(high_records[i]);
			}
			__builder.appendArray("high_records",high_records_builder.obj());
		}

		__obj = __builder.obj();
	}

	void HumanHeroCollect::from_snappy_buffer(const std::string& __inbuf)
	{
		std::string tmpbuf;
		snappy::Uncompress(__inbuf.c_str(),__inbuf.length(),&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void HumanHeroCollect::from_snappy_buffer(const char* __data,size_t __size)
	{
		std::string tmpbuf;
		snappy::Uncompress(__data,__size,&tmpbuf);
		bson::bo __obj(tmpbuf.c_str());
		pwassert(__obj.objsize() == tmpbuf.length());
		from_bson(__obj);
	}

	void HumanHeroCollect::from_bson(const char* __data,size_t __size)
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

	void HumanHeroCollect::from_bson(const bson::bo& __obj)
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
			case 5413678182038: // is_open_high type: bool
				{
					pwutils::bsonToCppVariable(is_open_high,__be);
				}
				break;
			case 7292946655636: // last_random_time type: int64
				{
					pwutils::bsonToCppVariable(last_random_time,__be);
				}
				break;
			case 6829034708280: // last_free_times type: int64
				{

					mongo::BSONObj aobj = __be.Obj();
					mongo::BSONObjIterator aiter(aobj);
					size_t count = 0;
					while(aiter.more())
					{
						mongo::BSONElement ae = aiter.next();
						pwassertop(count < 3,continue);
						pwutils::bsonToCppVariable(last_free_times[count],ae);
						++count;
					}
				}
				break;
			case 7314526052683: // collect_energyes type: int64
				{

					mongo::BSONObj aobj = __be.Obj();
					mongo::BSONObjIterator aiter(aobj);
					size_t count = 0;
					while(aiter.more())
					{
						mongo::BSONElement ae = aiter.next();
						pwassertop(count < 3,continue);
						pwutils::bsonToCppVariable(collect_energyes[count],ae);
						++count;
					}
				}
				break;
			case 5099150581583: // low_records type: int32
				{

					mongo::BSONObj aobj = __be.Obj();
					mongo::BSONObjIterator aiter(aobj);
					size_t count = 0;
					while(aiter.more())
					{
						mongo::BSONElement ae = aiter.next();
						pwassertop(count < 2,continue);
						pwutils::bsonToCppVariable(low_records[count],ae);
						++count;
					}
				}
				break;
			case 6323943924168: // middle_records type: int32
				{

					mongo::BSONObj aobj = __be.Obj();
					mongo::BSONObjIterator aiter(aobj);
					size_t count = 0;
					while(aiter.more())
					{
						mongo::BSONElement ae = aiter.next();
						pwassertop(count < 2,continue);
						pwutils::bsonToCppVariable(middle_records[count],ae);
						++count;
					}
				}
				break;
			case 5435068643525: // high_records type: int32
				{

					mongo::BSONObj aobj = __be.Obj();
					mongo::BSONObjIterator aiter(aobj);
					size_t count = 0;
					while(aiter.more())
					{
						mongo::BSONElement ae = aiter.next();
						pwassertop(count < 2,continue);
						pwutils::bsonToCppVariable(high_records[count],ae);
						++count;
					}
				}
				break;
			}
		}
		__hash = hash_make(0);
	}


	int64 HumanHeroCollect::hash_make(int64 seed)
	{
		int64 _result = seed;
		_result = pwutils::city_hash(&hid,sizeof(hid),_result);

		_result = pwutils::city_hash(&is_open_high,sizeof(is_open_high),_result);

		_result = pwutils::city_hash(&last_random_time,sizeof(last_random_time),_result);

		for(size_t i = 0; i < 3;++i)
		{
			_result = pwutils::city_hash(&i,sizeof(i),_result);
			_result = pwutils::city_hash(&last_free_times[i],sizeof(last_free_times[i]),_result);
		}

		for(size_t i = 0; i < 3;++i)
		{
			_result = pwutils::city_hash(&i,sizeof(i),_result);
			_result = pwutils::city_hash(&collect_energyes[i],sizeof(collect_energyes[i]),_result);
		}

		for(size_t i = 0; i < 2;++i)
		{
			_result = pwutils::city_hash(&i,sizeof(i),_result);
			_result = pwutils::city_hash(&low_records[i],sizeof(low_records[i]),_result);
		}

		for(size_t i = 0; i < 2;++i)
		{
			_result = pwutils::city_hash(&i,sizeof(i),_result);
			_result = pwutils::city_hash(&middle_records[i],sizeof(middle_records[i]),_result);
		}

		for(size_t i = 0; i < 2;++i)
		{
			_result = pwutils::city_hash(&i,sizeof(i),_result);
			_result = pwutils::city_hash(&high_records[i],sizeof(high_records[i]),_result);
		}

		return _result;
	}

	int64 HumanHeroCollect::get_hid() const
	{
		return hid;
	}

	void HumanHeroCollect::set_hid(int64 value)
	{
		this->hid = value;
	}

	bool HumanHeroCollect::get_is_open_high() const
	{
		return is_open_high;
	}

	void HumanHeroCollect::set_is_open_high(bool value)
	{
		this->is_open_high = value;
	}

	int64 HumanHeroCollect::get_last_random_time() const
	{
		return last_random_time;
	}

	void HumanHeroCollect::set_last_random_time(int64 value)
	{
		this->last_random_time = value;
	}


	bool HumanHeroCollect::is_default_value() const
	{
		if(hid != 0)
			return false;

		if(is_open_high != false)
			return false;

		if(last_random_time != 0)
			return false;

		if(!pwutils::is_default_value(last_free_times,3,0))
			return false;

		if(!pwutils::is_default_value(collect_energyes,3,0))
			return false;

		if(!pwutils::is_default_value(low_records,2,0))
			return false;

		if(!pwutils::is_default_value(middle_records,2,0))
			return false;

		if(!pwutils::is_default_value(high_records,2,0))
			return false;

		return true;
	}

}
