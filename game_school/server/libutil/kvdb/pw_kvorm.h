#ifndef PW_KVORM_H
#define PW_KVORM_H

#include "pw_def.h"
#include "bson/bsonobj.h"
#include "pw_object.h"
#include "pw_linked_object.h"

namespace pwutils
{
    class KvormBuffer
    {
    public:
        char* buf;
        int32 len;
    public:
        KvormBuffer(char* b = NULL,int32 l = 0)
            : buf(b)
            , len(l)
        {
        }
    };

	class KvormHelperObject
	{
	public:
		KvormHelperObject() 
			: m_operation(-1)
			, m_sync_level(-1)
		{}
	public:
		inline int16 orm_helper_operation() { return m_operation; }
		inline int16 orm_helper_sync_level() { return m_sync_level; }
		inline void orm_helper_operation(int16 v) { m_operation = v; }
		inline void orm_helper_sync_level(int16 v) { m_sync_level = v; }
	private:
		int16	m_operation;
		int16	m_sync_level;
	};

	class KvormBase : public PWOBJECT
    {
		RTTI(pwutils::KvormBase,Object);
    public:
		KvormBase() {}
        virtual ~KvormBase() {}
	public:
		virtual std::string rawkey() = 0;
		virtual std::string getkey() = 0;
		virtual std::string getmeta() = 0;
	public:
		virtual bool is_default_value() const = 0;
	public:
		virtual void to_bson(std::string& buf) const = 0;
		virtual void to_bson(bson::bo& obj) const = 0;
		virtual void to_snappy_buffer(std::string& buf) const = 0;
		virtual void from_bson(const char* data,size_t size) = 0;
		virtual void from_bson(const bson::bo& obj) = 0;
		virtual void from_snappy_buffer(const char* data,size_t size) = 0;
		virtual void from_snappy_buffer(const std::string& buf) = 0;
	public:
		virtual void from_obj(const KvormBase* r);
	public:
		virtual int64 hash_make(int64 seed) = 0;
		virtual int64 hash_origin() = 0;
		virtual void  hash_update(int64 hash) = 0;
	public:
		virtual void set_autoincr(int64 key) = 0;
	public:
		virtual int64 get_masterid() = 0;
		virtual void  set_masterid(int64 v) = 0;
	public:
		virtual const char* get_masterstrid() = 0;
		virtual void  set_masterid(const char* v) = 0;
    };

	// ----------------------------------------------------------------------------

/*
	template <class T> class KvormT : public KvormBase
	{
	public:
		virtual std::string rawkey()
		{
			return _mvalue.rawkey();
		}
		virtual std::string getkey()
		{
			return _mvalue.getkey();
		}
		virtual std::string getmeta()
		{
			return _mvalue.getmeta();
		}
	public:
		virtual bool is_default_value()
		{
			return _mvalue.is_default_value();
		}
	public:
		virtual void to_bson(std::string& buf)
		{
			return _mvalue.to_bson(buf);
		}
		virtual void to_bson(bson::bo& obj) 
		{
			return _mvalue.to_bson(obj);
		}
		virtual void to_snappy_buffer(std::string& buf)
		{
			return _mvalue.to_snappy_buffer(buf);
		}
		virtual void from_bson(const char* data,size_t size)
		{
			return _mvalue.from_bson(data,size);
		}
		virtual void from_bson(const bson::bo& obj)
		{
			return _mvalue.from_bson(obj);
		}
		virtual void from_snappy_buffer(const char* data,size_t size) 
		{
			return _mvalue.from_snappy_buffer(data,size);
		}

		virtual void from_snappy_buffer(const std::string& buf)
		{
			return _mvalue.from_snappy_buffer(buf);
		}
	public:
		virtual int64 hash_make(int64 seed)
		{
			return _mvalue.hash_make(seed);
		}
		virtual int64 hash_origin()
		{
			return _mvalue.hash_origin(seed);
		}
		virtual void  hash_update(int64 hash)
		{
			_mvalue.hash_update(hash);
		}
	public:
		virtual void set_autoincr(int64 key)
		{
			_mvalue.set_autoincr(key);
		}
	public:
		virtual int64 get_masterid()
		{
			return _mvalue.get_masterid();
		}
		virtual void  set_masterid(int64 v)
		{
			return _mvalue.set_masterid(v);
		}
	public:
		virtual const char* get_masterstrid()
		{
			return _mvalue.get_masterstrid();
		}
		virtual void  set_masterid(const char* v)
		{
			return _mvalue.set_masterid();
		}
	public:
		T _mvalue;
	};

*/

	// ----------------------------------------------------------------------------

	class KvormCollectionInteger
	{
	public:
		KvormCollectionInteger()
			: m_vMasterId(0)
		{
		}
	public:
		void set_master_id(int64 id) { m_vMasterId = id; }
	protected:
		int64 m_vMasterId;
	};


	class KvormCollectionString
	{
	public:
		void set_master_id(const char* id) { m_vMasterId = id; }
	protected:
		std::string m_vMasterId;
	};

	// ----------------------------------------------------------------------------

	extern void KvormBuildSlaveTableName(char* destbuf,size_t destlen,const char* name,int64 ownerkey);
	extern void KvormBuildSlaveTableName(char* destbuf,size_t destlen,const char* name,const char* ownerkey);
}

#endif // PW_KVORM_H
