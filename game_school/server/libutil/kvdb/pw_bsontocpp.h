#ifndef PW_BSONTOCPP_H
#define PW_BSONTOCPP_H

#include "pw_def.h"
#include "pw_fixed_string.h"
#include "bson/bson.h"
#include "pw_kvorm.h"

namespace pwutils
{
	extern int64 city_hash(const void* buf,size_t len,int64 seed);

	extern bool bsonToCppVariable(uint8& var,mongo::BSONElement& be);
	extern bool bsonToCppVariable(int16& var,mongo::BSONElement& be);
    extern bool bsonToCppVariable(int32& var,mongo::BSONElement& be);
	extern bool bsonToCppVariable(uint32& var,mongo::BSONElement& be);
    extern bool bsonToCppVariable(int64& var,mongo::BSONElement& be);
	extern bool bsonToCppVariable(uint64& var,mongo::BSONElement& be);
	extern bool bsonToCppVariable(float& var,mongo::BSONElement& be);
	extern bool bsonToCppVariable(double& var,mongo::BSONElement& be);
	extern bool bsonToCppVariable(bool& var,mongo::BSONElement& be);
    extern bool bsonToCppVariable(std::string& var,mongo::BSONElement& be);
    extern bool bsonToCppVariable(fixed_string_base var,mongo::BSONElement& be);

	extern bool is_default_value_binary(const char* v,size_t size,const char& nullv);
	extern bool is_default_value(const char* v,size_t size,const char& nullv);
	extern bool is_default_value(const uint32* v,size_t size,const uint32& nullv);
	extern bool is_default_value(const uint64* v,size_t size,const uint64& nullv);
	extern bool is_default_value(const uint8* v,size_t size,const uint8& nullv);
	extern bool is_default_value(const int32* v,size_t size,const int32& nullv);
	extern bool is_default_value(const int64* v,size_t size,const int64& nullv);
	extern bool is_default_value(const int16* v,size_t size,const int16& nullv);
	extern bool is_default_value(const float* v,size_t size,const float& nullv);
	extern bool is_default_value(const double* v,size_t size,const double& nullv);
	extern bool is_default_value(const std::string* v,size_t size,const char* nullv);

	template<class T> struct BsonMakeHash
	{
		template <class T2,class U> class conversion
		{
			typedef char _small;
			typedef long _big;
			static _small test(U);
			static _big test(...);
			static T2 makeT();
		public:
			enum { exists = sizeof(test(makeT())) == sizeof(_small) };
			enum { exists2way = (exists && conversion<U,T2>::exists) };
			enum { sameType = false };
		};

		template<class T2,int U> struct RealHasher
		{
			static int64 make(const T2& v,int64 seed)
			{
				return city_hash(&v,sizeof(T2),seed);
			}
		};

		template<class T2> struct RealHasher<T2,1>
		{
			static int64 make(const T2& v,int64 seed)
			{
				return const_cast<T2&>(v).hash_make(seed);
			}
		};

		static int64 make(const T& v,int64 seed)
		{
			return RealHasher<T,conversion<T,const pwutils::KvormBase&>::exists>::make(v,seed);
		}

	};

	template<> struct BsonMakeHash<std::string>
	{
		static int64 make(const std::string& v,int64 seed)
		{
			return city_hash(v.c_str(),v.length(),seed);
		}
	};

	template<> struct BsonMakeHash<fixed_string_base>
	{
		static int64 make(const fixed_string_base& v,int64 seed)
		{
			return city_hash(v.buf,strlen(v.buf),seed);
		}
	};
}

#endif // PW_BSONTOCPP_H
