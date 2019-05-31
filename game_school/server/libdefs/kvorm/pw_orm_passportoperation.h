#ifndef _pw_orm_passportoperation_
#define _pw_orm_passportoperation_

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

	class DPO_Charge;
	class DPO_Market;

	class PassportOperation : public pwutils::KvormBase
	{
		RTTI(PassportOperation,pwutils::KvormBase);
	public:
		PassportOperation();
		virtual ~PassportOperation();
	public:
		virtual bool is_default_value() const; // override
	public:
		PassportOperation* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "passportoperation"; }
		static const int64 meta_hash = 8028551751245;
		static const char* prefix() { return "passportoperation_"; }
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
		virtual void  set_masterid(const char* v) { passport = v; } // override
		virtual const char* get_masterstrid() { return passport.c_str(); } // override
	public:
		int64 get_id() const;
		const char* get_passport() const;
		const char* get_func_name() const;
		int64 get_func_hash() const;

		void set_id(int64 value);
		void set_passport(const char* value);
		void set_func_name(const char* value);
		void set_func_hash(int64 value);

	public:
		DPO_Charge* mutable_dpo_charge();
		DPO_Market* mutable_dpo_market();
	public:
		PassportOperation(const PassportOperation& v);
		const PassportOperation& operator=(const PassportOperation& v) { this->from_obj(&v); return *this; }
	public:
		int64 id;
		pwutils::fixed_string<64> passport;
		pwutils::fixed_string<64> func_name;
		int64 func_hash;
		DPO_Charge* dpo_charge;
		DPO_Market* dpo_market;
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_passportoperation_
