#ifndef _pw_orm_mail_
#define _pw_orm_mail_

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


	class Mail : public pwutils::KvormBase
	{
		RTTI(Mail,pwutils::KvormBase);
	public:
		Mail();
		virtual ~Mail();
	public:
		virtual bool is_default_value() const; // override
	public:
		Mail* clone() const;
	public:
		virtual std::string rawkey();
		virtual std::string getkey();
		virtual std::string getmeta();
	public:
		static const char* meta() { return "mail"; }
		static const int64 meta_hash = 1799838017423;
		static const char* prefix() { return "mail_"; }
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
		int64 get_id() const;
		int16 get_mode() const;
		int16 get_flag() const;
		int64 get_send_date() const;
		int64 get_sender_id() const;
		int64 get_receiver_id() const;
		bool get_item_binded() const;

		void set_id(int64 value);
		void set_mode(int16 value);
		void set_flag(int16 value);
		void set_send_date(int64 value);
		void set_sender_id(int64 value);
		void set_receiver_id(int64 value);
		void set_item_binded(bool value);

	public:
		int64 id;
		int16 mode;
		int16 flag;
		int64 send_date;
		int64 sender_id;
		char sender_name[64];
		int64 receiver_id;
		char subject[40];
		char content[256];
		char append_data[64];
		bool item_binded;
	public:
		int64 __hash;
	};
}

#endif // _pw_orm_mail_
