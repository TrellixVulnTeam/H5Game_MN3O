#ifndef _pw_orm_globalwelfare_
#define _pw_orm_globalwelfare_

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


	class GlobalWelfare : public pwutils::KvormBase
	{
		RTTI(GlobalWelfare,pwutils::KvormBase);
	public:
		GlobalWelfare();
		virtual ~GlobalWelfare();
	public:
		virtual bool is_default_value() const; // override
	public:
		GlobalWelfare* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "globalwelfare"; }
		static const int64 meta_hash = 5872216603645;
		static const char* prefix() { return "globalwelfare_"; }
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
		const char* get_datetime() const;
		int32 get_itemtype() const;
		int16 get_itemcount() const;
		uint8 get_req_profession_mask() const;

		void set_id(int64 value);
		void set_datetime(const char* value);
		void set_itemtype(int32 value);
		void set_itemcount(int16 value);
		void set_req_profession_mask(uint8 value);

	public:
		int64 id;
		pwutils::fixed_string<24> datetime;
		int32 itemtype;
		int16 itemcount;
		int16 req_level_range[2];
		uint8 req_profession_mask;
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_globalwelfare_
