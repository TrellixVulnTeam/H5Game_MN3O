#ifndef _pw_orm_heronew_
#define _pw_orm_heronew_

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


	class HeroNew : public pwutils::KvormBase
	{
		RTTI(HeroNew,pwutils::KvormBase);
	public:
		HeroNew();
		virtual ~HeroNew();
	public:
		virtual bool is_default_value() const; // override
	public:
		HeroNew* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "heronew"; }
		static const int64 meta_hash = 3264239693010;
		static const char* prefix() { return "heronew_"; }
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
		int16 get_star() const;
		bool get_activated() const;
		int16 get_assistance_loc() const;
		int16 get_rank() const;
		int16 get_rank_item_flag() const;

		void set_hid(int64 value);
		void set_id(int64 value);
		void set_did(int32 value);
		void set_state(int16 value);
		void set_star(int16 value);
		void set_activated(bool value);
		void set_assistance_loc(int16 value);
		void set_rank(int16 value);
		void set_rank_item_flag(int16 value);

	public:
		int64 hid;
		int64 id;
		int32 did;
		int16 state; // 状态
		int16 star; // 星级
		bool activated; // 是否激活
		int16 assistance_loc; // 助战位
		int16 rank; // 当前阶级
		int16 rank_item_flag; // 当前阶级镶嵌物品信息(1-6位表示)
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_heronew_
