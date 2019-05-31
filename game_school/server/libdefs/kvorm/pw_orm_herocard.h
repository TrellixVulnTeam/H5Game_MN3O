#ifndef _pw_orm_herocard_
#define _pw_orm_herocard_

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


	class HeroCard : public pwutils::KvormBase
	{
		RTTI(HeroCard,pwutils::KvormBase);
	public:
		HeroCard();
		virtual ~HeroCard();
	public:
		virtual bool is_default_value() const; // override
	public:
		HeroCard* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "herocard"; }
		static const int64 meta_hash = 3609761074046;
		static const char* prefix() { return "herocard_"; }
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
		int64 get_id() const;
		int32 get_did() const;
		int16 get_state() const;
		int16 get_level() const;
		int16 get_star() const;
		bool get_activated() const;
		int16 get_equip_loc() const;
		int16 get_guard_loc() const;
		int16 get_guard_level() const;
		int32 get_skill() const;

		void set_hid(int64 value);
		void set_id(int64 value);
		void set_did(int32 value);
		void set_state(int16 value);
		void set_level(int16 value);
		void set_star(int16 value);
		void set_activated(bool value);
		void set_equip_loc(int16 value);
		void set_guard_loc(int16 value);
		void set_guard_level(int16 value);
		void set_skill(int32 value);

	public:
		int64 hid;
		int64 id;
		int32 did;
		int16 state;
		int16 level;
		int16 star;
		bool activated;
		int16 equip_loc;
		int16 guard_loc;
		int16 guard_level;
		int32 skill;
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_herocard_
