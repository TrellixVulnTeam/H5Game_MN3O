#ifndef _pw_orm_human_
#define _pw_orm_human_

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


	class Human : public pwutils::KvormBase
	{
		RTTI(Human,pwutils::KvormBase);
	public:
		Human();
		virtual ~Human();
	public:
		virtual bool is_default_value() const; // override
	public:
		Human* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "human"; }
		static const int64 meta_hash = 2307225568677;
		static const char* prefix() { return "human_"; }
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
		int64 get_id() const;
		const char* get_passport() const;
		const char* get_name() const;
		const char* get_last_login() const;
		const char* get_last_logout() const;
		int64 get_online_seconds() const;
		int64 get_online_seconds_today() const;
		int32 get_birthday() const;
		uint8 get_profession() const;
		uint8 get_sex() const;
		int16 get_level() const;
		int64 get_exp() const;
		int64 get_level_need_exp() const;
		int32 get_loc_stage() const;

		void set_id(int64 value);
		void set_passport(const char* value);
		void set_name(const char* value);
		void set_last_login(const char* value);
		void set_last_logout(const char* value);
		void set_online_seconds(int64 value);
		void set_online_seconds_today(int64 value);
		void set_birthday(int32 value);
		void set_profession(uint8 value);
		void set_sex(uint8 value);
		void set_level(int16 value);
		void set_exp(int64 value);
		void set_level_need_exp(int64 value);
		void set_loc_stage(int32 value);

		void exp_plus(int64 value) { exp += value; }
		void exp_minus(int64 value) { exp -= value; }

		void level_need_exp_plus(int64 value) { level_need_exp += value; }
		void level_need_exp_minus(int64 value) { level_need_exp -= value; }

	public:
		int64 id;
		pwutils::fixed_string<64> passport;
		pwutils::fixed_string<64> name;
		pwutils::fixed_string<24> last_login;
		pwutils::fixed_string<24> last_logout;
		int64 online_seconds;
		int64 online_seconds_today;
		int32 birthday; // ∏Ò Ω£∫yymmdd
		uint8 profession;
		uint8 sex;
		int16 level;
		int64 exp;
		int64 level_need_exp;
		int32 loc_stage;
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_human_
