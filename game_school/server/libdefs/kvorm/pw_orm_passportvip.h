#ifndef _pw_orm_passportvip_
#define _pw_orm_passportvip_

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


	class PassportVip : public pwutils::KvormBase
	{
		RTTI(PassportVip,pwutils::KvormBase);
	public:
		PassportVip();
		virtual ~PassportVip();
	public:
		virtual bool is_default_value() const; // override
	public:
		PassportVip* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "passportvip"; }
		static const int64 meta_hash = 5270530066723;
		static const char* prefix() { return "passportvip_"; }
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
		const char* get_passport() const;
		int32 get_exp() const;
		int32 get_exp_new() const;
		int32 get_reward_bits() const;
		int32 get_reward_bits_new() const;
		int32 get_level() const;
		int32 get_is_get_dailyreward() const;

		void set_passport(const char* value);
		void set_exp(int32 value);
		void set_exp_new(int32 value);
		void set_reward_bits(int32 value);
		void set_reward_bits_new(int32 value);
		void set_level(int32 value);
		void set_is_get_dailyreward(int32 value);

		void exp_plus(int32 value) { exp += value; }
		void exp_minus(int32 value) { exp -= value; }

		void exp_new_plus(int32 value) { exp_new += value; }
		void exp_new_minus(int32 value) { exp_new -= value; }

		void reward_bits_include(int32 value) { reward_bits |= value; }
		void reward_bits_exclude(int32 value) { reward_bits &= ~value; }
		bool is_reward_bits_include(int32 value) { return reward_bits & value; }

		void reward_bits_new_include(int32 value) { reward_bits_new |= value; }
		void reward_bits_new_exclude(int32 value) { reward_bits_new &= ~value; }
		bool is_reward_bits_new_include(int32 value) { return reward_bits_new & value; }

	public:
		pwutils::fixed_string<64> passport;
		int32 exp;
		int32 exp_new;
		int32 reward_bits;
		int32 reward_bits_new;
		int32 level;
		int32 is_get_dailyreward;
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_passportvip_
