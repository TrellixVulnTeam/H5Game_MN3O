#ifndef _pw_orm_notifyball_
#define _pw_orm_notifyball_

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


	class NotifyBall : public pwutils::KvormBase
	{
		RTTI(NotifyBall,pwutils::KvormBase);
	public:
		NotifyBall();
		virtual ~NotifyBall();
	public:
		virtual bool is_default_value() const; // override
	public:
		NotifyBall* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "notifyball"; }
		static const int64 meta_hash = 4622123010528;
		static const char* prefix() { return "notifyball_"; }
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
		virtual int64 get_masterid() { return receiver_id; } // override
		virtual void  set_masterid(int64 v) { receiver_id = v; } // override
		virtual void  set_masterid(const char* v) { } // override
		virtual const char* get_masterstrid() { return ""; } // override
	public:
		int64 get_receiver_id() const;
		int64 get_uuid() const;
		int32 get_id() const;
		int64 get_timestamp() const;

		void set_receiver_id(int64 value);
		void set_uuid(int64 value);
		void set_id(int32 value);
		void set_timestamp(int64 value);

	public:
		pwutils::KvormArray< std::string >* mutable_args() { return &args; }
	public:
		int64 receiver_id;
		int64 uuid;
		int32 id;
		int64 timestamp;
		pwutils::KvormArray< std::string > args;
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_notifyball_
