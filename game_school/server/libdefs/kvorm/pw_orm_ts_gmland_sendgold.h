#ifndef _pw_orm_ts_gmland_sendgold_
#define _pw_orm_ts_gmland_sendgold_

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


	class TS_Gmland_SendGold : public pwutils::KvormBase
	{
		RTTI(TS_Gmland_SendGold,pwutils::KvormBase);
	public:
		TS_Gmland_SendGold();
		virtual ~TS_Gmland_SendGold();
	public:
		virtual bool is_default_value() const; // override
	public:
		TS_Gmland_SendGold* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "ts_gmland_sendgold"; }
		static const int64 meta_hash = 8143746557090;
		static const char* prefix() { return "ts_gmland_sendgold_"; }
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
		int64 get_gold() const;
		int64 get_target_hid() const;
		int64 get_sender_hid() const;
		const char* get_sender_name() const;

		void set_gold(int64 value);
		void set_target_hid(int64 value);
		void set_sender_hid(int64 value);
		void set_sender_name(const char* value);

	public:
		int64 gold;
		int64 target_hid;
		int64 sender_hid;
		pwutils::fixed_string<64> sender_name;
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_ts_gmland_sendgold_
