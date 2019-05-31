#ifndef _pw_orm_globaldailyinfolianyun_
#define _pw_orm_globaldailyinfolianyun_

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


	class GlobalDailyInfoLianYun : public pwutils::KvormBase
	{
		RTTI(GlobalDailyInfoLianYun,pwutils::KvormBase);
	public:
		GlobalDailyInfoLianYun();
		virtual ~GlobalDailyInfoLianYun();
	public:
		virtual bool is_default_value() const; // override
	public:
		GlobalDailyInfoLianYun* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "globaldailyinfolianyun"; }
		static const int64 meta_hash = 10102396882108;
		static const char* prefix() { return "globaldailyinfolianyun_"; }
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
		int32 get_date() const;
		int32 get_role_created_num() const;
		int32 get_role_logined_num() const;
		int32 get_role_onlined_max() const;
		int64 get_role_spend_gold_sum() const;

		void set_date(int32 value);
		void set_role_created_num(int32 value);
		void set_role_logined_num(int32 value);
		void set_role_onlined_max(int32 value);
		void set_role_spend_gold_sum(int64 value);

		void role_created_num_plus(int32 value) { role_created_num += value; }
		void role_created_num_minus(int32 value) { role_created_num -= value; }

		void role_logined_num_plus(int32 value) { role_logined_num += value; }
		void role_logined_num_minus(int32 value) { role_logined_num -= value; }

		void role_spend_gold_sum_plus(int64 value) { role_spend_gold_sum += value; }
		void role_spend_gold_sum_minus(int64 value) { role_spend_gold_sum -= value; }

	public:
		int32 date;
		int32 role_created_num;
		int32 role_logined_num;
		int32 role_onlined_max;
		int64 role_spend_gold_sum; // 本日消息累计充值金币
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_globaldailyinfolianyun_
