#ifndef _pw_orm_mallitem_
#define _pw_orm_mallitem_

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


	class MallItem : public pwutils::KvormBase
	{
		RTTI(MallItem,pwutils::KvormBase);
	public:
		MallItem();
		virtual ~MallItem();
	public:
		virtual bool is_default_value() const; // override
	public:
		MallItem* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "mallitem"; }
		static const int64 meta_hash = 3665214110043;
		static const char* prefix() { return "mallitem_"; }
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
		int32 get_cfg_id() const;
		int32 get_sold_count() const;

		void set_cfg_id(int32 value);
		void set_sold_count(int32 value);

	public:
		int32 cfg_id;
		int32 sold_count;
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_mallitem_
