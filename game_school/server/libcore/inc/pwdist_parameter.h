#ifndef _pwdist_parameter_
#define _pwdist_parameter_

#include "pwdist_def.h"
#include "pw_chunk.h"

namespace pwdist
{
	const size_t cst_max_param_num = 10;

	// ------------------------------------------------------

	enum
	{
		PARAMETER_TYPE_I32 = 'i',
		PARAMETER_TYPE_I64 = 'I',
		PARAMETER_TYPE_DEC = 'd',
		PARAMETER_TYPE_STR = 's',
		PARAMETER_TYPE_BUF = 'p',
	};

	struct Parameter
	{
		int32 type;
		int32 size;

		union
		{
			int32 vali32;
			int64 vali64;
			dec64 valdec;
			char* valbuf;
		};
	};

	// ------------------------------------------------------

	typedef pwngs::Chunk Chunk;

// 	struct Chunk
// 	{
// 		char* buf;
// 		int32 len;
// 
// 		Chunk()
// 			: buf(NULL)
// 			, len(0)
// 		{
// 		}
// 
// 		Chunk(void* b,int32 l)
// 			: buf((char*)b)
// 			, len(l)
// 		{
// 		}
// 	};

	// ------------------------------------------------------

	struct Parameters
	{
		size_t paramsNum;
		Parameter params[cst_max_param_num];

		size_t BytePtr();
		size_t LoadPtr(char* buf,size_t len);
		size_t SavePtr(char* buf,size_t len);
	};

	// -----------------------------------------------------------------------------

	struct i_ParameterHelper_i32
	{
		static char GetName()
		{
			return PARAMETER_TYPE_I32;
		}

		static int32 Get(Parameter& param)
		{
			switch(param.type)
			{
			case PARAMETER_TYPE_I32:
				return param.vali32;
			case PARAMETER_TYPE_I64:
				return (int32)param.vali64;
			case PARAMETER_TYPE_DEC:
				return (int32)param.valdec;
			default:
				stdasserte(false && "invalid convert to i32");
				break;
			}
			return -1;			
		}

		static void Make(Parameter& param, int32 value)
		{
			param.size = 0;
			param.vali32 = value;
			param.type = PARAMETER_TYPE_I32;
		}
	};

	struct i_ParameterHelper_i64
	{
		static char GetName()
		{
			return PARAMETER_TYPE_I64;
		}

		static int64 Get(Parameter& param)
		{
			switch(param.type)
			{
			case PARAMETER_TYPE_I32:
				return param.vali32;
			case PARAMETER_TYPE_I64:
				return param.vali64;
			case PARAMETER_TYPE_DEC:
				return (int64)param.valdec;
			default:
				stdasserte(false && "invalid convert to i64");
				break;
			}
			return -1;
		}

		static void Make(Parameter& param, int64 value)
		{
			param.size = 0;
			param.vali64 = value;
			param.type = PARAMETER_TYPE_I64;
		}
	};

	template<class T> struct ParameterHelper
	{

	};

	template<> struct ParameterHelper<const_char_ptr>
	{
		static char GetName()
		{
			return PARAMETER_TYPE_STR;
		}

		static const_char_ptr Get(Parameter& param)
		{
			switch(param.type)
			{
			case PARAMETER_TYPE_STR:
			case PARAMETER_TYPE_BUF:
				return param.valbuf;
			default:
				stdasserte(false && "invalid convert to const char*");
				break;
			}
			return "";
		}

		static void Make(Parameter& param, const_char_ptr value)
		{
			param.size = strlen(value) + 1;
			param.valbuf = (char*)value;
			param.type = PARAMETER_TYPE_STR;
		}
	};

// 	template<> struct ParameterHelper<std::string&>
// 	{
// 		static char GetName()
// 		{
// 			return PARAMETER_TYPE_BUF;
// 		}
// 
// 		static std::string Get(Parameter& param)
// 		{
// 			switch(param.type)
// 			{
// 			case PARAMETER_TYPE_STR:
// 			case PARAMETER_TYPE_BUF:
// 				return std::string(param.valbuf,param.size);
// 			default:
// 				stdasserte(false && "invalid convert to string");
// 			}
// 			return "";
// 		}
// 
// 		static void Make(Parameter& param, std::string& value)
// 		{
// 			param.size = value.length();
// 			param.valbuf = (char*)value.c_str();
// 			param.type = PARAMETER_TYPE_BUF;
// 		}
// 	};
// 
// 	template<> struct ParameterHelper<std::string>
// 	{
// 		static char GetName()
// 		{
// 			return PARAMETER_TYPE_BUF;
// 		}
// 
// 		static std::string Get(Parameter& param)
// 		{
// 			switch(param.type)
// 			{
// 			case PARAMETER_TYPE_STR:
// 			case PARAMETER_TYPE_BUF:
// 				return std::string(param.valbuf,param.size);
// 			default:
// 				stdasserte(false && "invalid convert to string");
// 			}
// 			return "";
// 		}
// 
// 		static void Make(Parameter& param, const std::string& value)
// 		{
// 			param.size = value.length();
// 			param.valbuf = (char*)value.c_str();
// 			param.type = PARAMETER_TYPE_BUF;
// 		}
// 	};

	template<> struct ParameterHelper<Chunk>
	{
		static char GetName()
		{
			return PARAMETER_TYPE_BUF;
		}

		static Chunk Get(Parameter& param)
		{
			Chunk result;
			switch(param.type)
			{
			case PARAMETER_TYPE_BUF:
				result.buf = param.valbuf;
				result.len = param.size;
				break;
			default:
				stdasserte(false && "invalid convert to buffer");
				break;
			}
			return result;
		}

		static void Make(Parameter& param, Chunk buf)
		{
			param.size = buf.len;
			param.valbuf = buf.buf;
			param.type = PARAMETER_TYPE_BUF;
		}
	};

	template<> struct ParameterHelper<bool>
	{
		static char GetName()
		{
			return i_ParameterHelper_i32::GetName();
		}

		static bool Get(Parameter& param)
		{
			return i_ParameterHelper_i32::Get(param) == 1;
		}

		static void Make(Parameter& param, bool val)
		{
			return i_ParameterHelper_i32::Make(param,val ? 1 : 0);
		}
	};
	template<> struct ParameterHelper<char> : public i_ParameterHelper_i32 {};
	template<> struct ParameterHelper<sint16> : public i_ParameterHelper_i32 {};
	template<> struct ParameterHelper<uint16> : public i_ParameterHelper_i32 {};
	template<> struct ParameterHelper<sint32> : public i_ParameterHelper_i32 {};
	template<> struct ParameterHelper<uint32> : public i_ParameterHelper_i32 {};
	template<> struct ParameterHelper<long> : public i_ParameterHelper_i64 {};
	template<> struct ParameterHelper<sint64> : public i_ParameterHelper_i64 {};
	template<> struct ParameterHelper<uint64> : public i_ParameterHelper_i64 {};

	// -----------------------------------------------------------------------
	// -----------------------------------------------------------------------

	struct CallHelper
	{
		static void MakeDef(char* def,Parameters& params)
		{
			for(size_t i = 0; i < params.paramsNum; ++i)
			{
				def[i] = (char)params.params[i].type;
			}
			def[params.paramsNum] = '\0';
		}

		static void MakeDef(char* def)
		{
			def[0] = '\0';
		}
		template<class P1> static void MakeDef(char* def,P1& v1)
		{
			def[0] = ParameterHelper<P1>::GetName();
			def[1] = '\0';
		}
		template<class P1,class P2> static void MakeDef(char* def,P1& v1,P2& v2)
		{
			def[0] = ParameterHelper<P1>::GetName();
			def[1] = ParameterHelper<P2>::GetName();
			def[2] = '\0';
		}
		template<class P1,class P2,class P3> static void MakeDef(char* def,P1& v1,P2& v2,P3& v3)
		{
			def[0] = ParameterHelper<P1>::GetName();
			def[1] = ParameterHelper<P2>::GetName();
			def[2] = ParameterHelper<P3>::GetName();
			def[3] = '\0';
		}
		template<class P1,class P2,class P3,class P4> static void MakeDef(char* def,P1& v1,P2& v2,P3& v3,P4& v4)
		{
			def[0] = ParameterHelper<P1>::GetName();
			def[1] = ParameterHelper<P2>::GetName();
			def[2] = ParameterHelper<P3>::GetName();
			def[3] = ParameterHelper<P4>::GetName();
			def[4] = '\0';
		}
		template<class P1,class P2,class P3,class P4,class P5> static void MakeDef(char* def,P1& v1,P2& v2,P3& v3,P4& v4,P5& v5)
		{
			def[0] = ParameterHelper<P1>::GetName();
			def[1] = ParameterHelper<P2>::GetName();
			def[2] = ParameterHelper<P3>::GetName();
			def[3] = ParameterHelper<P4>::GetName();
			def[4] = ParameterHelper<P5>::GetName();
			def[5] = '\0';
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6> static void MakeDef(char* def,P1& v1,P2& v2,P3& v3,P4& v4,P5& v5,P6& v6)
		{
			def[0] = ParameterHelper<P1>::GetName();
			def[1] = ParameterHelper<P2>::GetName();
			def[2] = ParameterHelper<P3>::GetName();
			def[3] = ParameterHelper<P4>::GetName();
			def[4] = ParameterHelper<P5>::GetName();
			def[5] = ParameterHelper<P6>::GetName();
			def[6] = '\0';
		}
	};

	struct CallParameterHelper
	{
		static void MakeParams(Parameters& params)
		{
			params.paramsNum = 0;
		}

		template<class P1> static void MakeParams(Parameters& params,P1& p1)
		{
			params.paramsNum = 1;
			ParameterHelper<P1>::Make(params.params[0],p1);
		}

		template<class P1,class P2> static void MakeParams(Parameters& params,P1& p1,P2& p2)
		{
			params.paramsNum = 2;
			ParameterHelper<P1>::Make(params.params[0],p1);
			ParameterHelper<P2>::Make(params.params[1],p2);
		}

		template<class P1,class P2,class P3> static void MakeParams(Parameters& params,P1& p1,P2& p2,P3& p3)
		{
			params.paramsNum = 3;
			ParameterHelper<P1>::Make(params.params[0],p1);
			ParameterHelper<P2>::Make(params.params[1],p2);
			ParameterHelper<P3>::Make(params.params[2],p3);
		}

		template<class P1,class P2,class P3,class P4> static void MakeParams(Parameters& params,P1& p1,P2& p2,P3& p3,P4& p4)
		{
			params.paramsNum = 4;
			ParameterHelper<P1>::Make(params.params[0],p1);
			ParameterHelper<P2>::Make(params.params[1],p2);
			ParameterHelper<P3>::Make(params.params[2],p3);
			ParameterHelper<P4>::Make(params.params[3],p4);
		}

		template<class P1,class P2,class P3,class P4,class P5> static void MakeParams(Parameters& params,P1& p1,P2& p2,P3& p3,P4& p4,P5& p5)
		{
			params.paramsNum = 5;
			ParameterHelper<P1>::Make(params.params[0],p1);
			ParameterHelper<P2>::Make(params.params[1],p2);
			ParameterHelper<P3>::Make(params.params[2],p3);
			ParameterHelper<P4>::Make(params.params[3],p4);
			ParameterHelper<P5>::Make(params.params[4],p5);
		}

		template<class P1,class P2,class P3,class P4,class P5,class P6> static void MakeParams(Parameters& params,P1& p1,P2& p2,P3& p3,P4& p4,P5& p5,P6& p6)
		{
			params.paramsNum = 6;
			ParameterHelper<P1>::Make(params.params[0],p1);
			ParameterHelper<P2>::Make(params.params[1],p2);
			ParameterHelper<P3>::Make(params.params[2],p3);
			ParameterHelper<P4>::Make(params.params[3],p4);
			ParameterHelper<P5>::Make(params.params[4],p5);
			ParameterHelper<P6>::Make(params.params[5],p6);
		}
	};
}

#endif // _pwdist_parameter_