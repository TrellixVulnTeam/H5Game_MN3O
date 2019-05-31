#ifndef _pw_orm_globalcharge_
#define _pw_orm_globalcharge_

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


	class GlobalCharge : public pwutils::KvormBase
	{
		RTTI(GlobalCharge,pwutils::KvormBase);
	public:
		GlobalCharge();
		virtual ~GlobalCharge();
	public:
		virtual bool is_default_value() const; // override
	public:
		GlobalCharge* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "globalcharge"; }
		static const int64 meta_hash = 5339228414535;
		static const char* prefix() { return "globalcharge_"; }
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
		int64 get_date() const;
		float get_rmb() const;
		float get_pubacct_rmb() const;

		void set_date(int64 value);
		void set_rmb(float value);
		void set_pubacct_rmb(float value);

	public:
		int64 date;
		float rmb;
		float pubacct_rmb;
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_globalcharge_
