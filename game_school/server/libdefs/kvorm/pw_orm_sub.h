#ifndef _pw_orm_sub_
#define _pw_orm_sub_

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


	class Sub : public pwutils::KvormBase
	{
		RTTI(Sub,pwutils::KvormBase);
	public:
		Sub();
		virtual ~Sub();
	public:
		virtual bool is_default_value() const; // override
	public:
		Sub* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "sub"; }
		static const int64 meta_hash = 1417341196620;
		static const char* prefix() { return "sub_"; }
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
		virtual int64 get_masterid() { return 0; } // override
		virtual void  set_masterid(int64 v) { } // override
		virtual void  set_masterid(const char* v) { } // override
		virtual const char* get_masterstrid() { return ""; } // override
	public:
		uint8 get_level() const;
		uint8 get_talent_awake_type() const;
		int32 get_exp() const;

		void set_level(uint8 value);
		void set_talent_awake_type(uint8 value);
		void set_exp(int32 value);

	public:
		uint8 level;
		uint8 talent_awake_type;
		int32 exp;
		int32 talent_awake_param[2];
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_sub_
