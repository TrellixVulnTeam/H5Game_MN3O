#ifndef _pw_orm_humanherocollect_
#define _pw_orm_humanherocollect_

#include "pw_types.h"
#include "snappy/snappy.h"
#include "kvdb/pw_fixed_string.h"
#include "kvdb/pw_kvorm.h"
#include "kvdb/pw_kvorm_array.h"
#include "kvdb/pw_kvorm_hashmap.h"
#include "bson/bson.h"
#include "bson/bsonobjbuilder.h"

namespace orm
{


	class HumanHeroCollect : public pwutils::KvormBase
	{
		RTTI(HumanHeroCollect,pwutils::KvormBase);
	public:
		HumanHeroCollect();
		virtual ~HumanHeroCollect();
	public:
		virtual bool is_default_value() const; // override
	public:
		HumanHeroCollect* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "humanherocollect"; }
		static const int64 meta_hash = 7341599328119;
		static const char* prefix() { return "humanherocollect_"; }
	public:
		virtual void to_bson(std::string& __buf) const; // override
		virtual void to_bson(bson::bo& __obj) const; // override
		virtual void to_snappy_buffer(std::string& __buf) const; // override
		virtual void from_bson(const char* __data,size_t __size); // override
		virtual void from_bson(const bson::bo& __obj); // override
		virtual void from_snappy_buffer(const char* __data,size_t __size); // override
		virtual void from_snappy_buffer(const std::string& __buf); // override
	public:
		virtual int64 hash_make(int64 seed);
		virtual int64 hash_origin() { return __hash; }
		virtual void  hash_update(int64 hash) { __hash = hash; }
	public:
		virtual void set_autoincr(int64 key); // override
	public:
		virtual int64 get_masterid() { return hid; } // override
		virtual void  set_masterid(int64 v) { hid = v; } // override
		virtual void  set_masterid(const char* v) { } // override
		virtual const char* get_masterstrid() { return ""; } // override
	public:
		int64 get_hid() const;
		bool get_is_open_high() const;
		int64 get_last_random_time() const;

		void set_hid(int64 value);
		void set_is_open_high(bool value);
		void set_last_random_time(int64 value);

	public:
		int64 hid;
		bool is_open_high; // 是否开启高级抽取
		int64 last_random_time; // 上次高级抽取随机时间
		int64 last_free_times[3]; // 上次免费抽取时间
		int64 collect_energyes[3]; // 能量值
		int32 low_records[2]; // 初级抽取记录
		int32 middle_records[2]; // 中级抽取记录
		int32 high_records[2]; // 高级抽取记录
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_humanherocollect_
