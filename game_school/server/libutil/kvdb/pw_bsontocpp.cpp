#include "pw_bsontocpp.h"
#include "pw_logger.h"
#include "pw_utils.h"

namespace pwutils
{
	extern bool bsonToCppVariable(bool& var,mongo::BSONElement& be)
	{
		if(be.isBoolean())
		{
			var = be.boolean();
			return true;
		}
		pwreportvars(false,__FUNCTION__ << " to bool:" << be.toString());
		pwasserte(false && "bsonToCppVariable: invalid convert");
		return false;
	}

	extern bool bsonToCppVariable(uint8& var,mongo::BSONElement& be)
	{
		if(be.isNumber())
		{
			var = (uint8)be.numberInt();
			return true;
		}
		pwreportvars(false,__FUNCTION__ << " to uint8:" << be.toString());
		pwasserte(false && "bsonToCppVariable: invalid convert");
		return false;
	}

	extern bool bsonToCppVariable(int16& var,mongo::BSONElement& be)
	{
		if(be.isNumber())
		{
			var = (int16)be.numberInt();
			return true;
		}
		pwreportvars(false,__FUNCTION__ << " to int16:" << be.toString());
		pwasserte(false && "bsonToCppVariable: invalid convert");
		return false;
	}

	extern bool bsonToCppVariable(float& var,mongo::BSONElement& be)
	{
		if(be.isNumber())
		{
			var = (float)be.numberDouble();
			return true;
		}
		pwreportvars(false,__FUNCTION__ << " to float:" << be.toString());
		pwasserte(false && "bsonToCppVariable: invalid convert");
		return false;
	}

	extern bool bsonToCppVariable(double& var,mongo::BSONElement& be)
	{
		if(be.isNumber())
		{
			var = be.numberDouble();
			return true;
		}
		pwreportvars(false,__FUNCTION__ << " to double:" << be.toString());
		pwasserte(false && "bsonToCppVariable: invalid convert");
		return false;
	}

    extern bool bsonToCppVariable(int32& var,mongo::BSONElement& be)
    {
        if(be.isNumber())
        {
            var = be.numberInt();
            return true;
        }
        pwreportvars(false,__FUNCTION__ << " to int32:" << be.toString());
        pwasserte(false && "bsonToCppVariable: invalid convert");
		return false;
    }

    extern bool bsonToCppVariable(int64& var,mongo::BSONElement& be)
    {
        if(be.isNumber())
        {
            var = be.numberLong();
            return true;
        }
        pwreportvars(false,__FUNCTION__ << " to int64:" << be.toString());
        pwasserte(false && "bsonToCppVariable: invalid convert");
		return false;
    }

    extern bool bsonToCppVariable(std::string& var,mongo::BSONElement& be)
    {
        if(be.type() == mongo::String)
        {
            var = std::string(be.valuestrsafe(),be.valuestrsize()-1);
            return true;
        }
		else if(be.type() == mongo::BinData)
		{
			int len = 0;
			const char* data = be.binData(len);
			var.clear();
			var.append(data,len);
			return true;
		}
        pwreportvars(false,__FUNCTION__ << " to string:" << be.toString());
        pwasserte(false && "bsonToCppVariable: invalid convert");
		return false;
    }

    extern bool bsonToCppVariable(fixed_string_base var,mongo::BSONElement& be)
    {
        if(be.type() == mongo::String)
        {
			pwutils::strncpy(var.buf,be.valuestrsafe(),__min(var.len,be.valuestrsize()));
            return true;
        }
        pwreportvars(false,__FUNCTION__ << " to fixed_string_base:" << be.toString());
        pwasserte(false && "bsonToCppVariable: invalid convert");
		return false;
    }

	extern bool bsonToCppVariable( uint32& var,mongo::BSONElement& be )
	{
		if(be.isNumber())
		{
			var = (uint32)be.numberInt();
			return true;
		}
		pwreportvars(false,__FUNCTION__ << " to uint32:" << be.toString());
		pwasserte(false && "bsonToCppVariable: invalid convert");
		return false;
	}

	extern bool bsonToCppVariable( uint64& var,mongo::BSONElement& be )
	{
		if(be.isNumber())
		{
			var = (uint64)be.numberLong();
			return true;
		}
		pwreportvars(false,__FUNCTION__ << " to uint64:" << be.toString());
		pwasserte(false && "bsonToCppVariable: invalid convert");
		return false;
	}


	extern bool is_default_value( const char* v,size_t size,const char& nullv )
	{
		return strlen(v) == 0;
	}

	extern bool is_default_value( const uint32* v,size_t size,const uint32& nullv )
	{
		for(size_t i = 0; i < size; ++i)
			if(v[i] != nullv)
				return false;
		return true;
	}

	extern bool is_default_value( const uint64* v,size_t size,const uint64& nullv )
	{
		for(size_t i = 0; i < size; ++i)
			if(v[i] != nullv)
				return false;
		return true;
	}

	extern bool is_default_value( const uint8* v,size_t size,const uint8& nullv )
	{
		for(size_t i = 0; i < size; ++i)
			if(v[i] != nullv)
				return false;
		return true;
	}

	extern bool is_default_value( const int32* v,size_t size,const int32& nullv )
	{
		for(size_t i = 0; i < size; ++i)
			if(v[i] != nullv)
				return false;
		return true;
	}

	extern bool is_default_value( const int64* v,size_t size,const int64& nullv )
	{
		for(size_t i = 0; i < size; ++i)
			if(v[i] != nullv)
				return false;
		return true;
	}

	extern bool is_default_value( const int16* v,size_t size,const int16& nullv )
	{
		for(size_t i = 0; i < size; ++i)
			if(v[i] != nullv)
				return false;
		return true;
	}

	extern bool is_default_value( const float* v,size_t size,const float& nullv )
	{
		for(size_t i = 0; i < size; ++i)
			if(v[i] != nullv)
				return false;
		return true;
	}

	extern bool is_default_value( const double* v,size_t size,const double& nullv )
	{
		for(size_t i = 0; i < size; ++i)
			if(v[i] != nullv)
				return false;
		return true;
	}

	extern bool is_default_value( const std::string* v,size_t size,const char* nullv )
	{
		for(size_t i = 0; i < size; ++i)
			if(v[i] != nullv)
				return false;
		return true;
	}

	extern bool is_default_value_binary( const char* v,size_t size,const char& nullv )
	{
		for(size_t i = 0; i < size; ++i)
			if(v[i] != nullv)
				return false;
		return true;
	}







}
