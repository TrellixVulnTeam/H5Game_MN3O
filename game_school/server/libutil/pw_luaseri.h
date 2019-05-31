#ifndef _pw_luaseri_
#define _pw_luaseri_

#include "pw_def.h"
#include "pw_lua.h"
#include "pw_chunk.h"
// #include "pwdist_parameter.h"

namespace pwlua
{
	extern int luaseri_pack(lua_State* L);
	extern int luaseri_unpack(lua_State* L);
	extern int luaseri_unpack(lua_State* L,char* buf,int len);

	const char LUA_TINT64 = 100;

	class PackHelper
	{
	public:
		PackHelper(lua_State* _L = NULL);
		~PackHelper();
	public:
		int AddFromLua(int index);
	public:
		int AddInteger(lua_Integer v);
		int AddNumber(lua_Number v);
		int AddString(const char* text,size_t len);
		int AddInt64(int64 v);
	public:
		inline void* GetBuf()
		{
			return mBuf;
		}

		inline size_t GetLen()
		{
			return mLenUsed;
		}

		inline pwngs::Chunk GetChunk()
		{
			return pwngs::Chunk(mBuf,mLenUsed);
		}

		inline pwngs::Chunk Detach()
		{
			pwngs::Chunk result(mBuf,mLenUsed);
			mBuf = NULL;
			mLen = 0;
			mLenUsed = 0;
			return result;
		}
	private:
		size_t writeType(char t);
		size_t writeBuffer(void* v, size_t n);
	private:
		lua_State* L;
	private:
		char* mBuf;
		size_t mLen; 
		size_t mLenUsed;
	};

	class UnpackHelper
	{
	public:
		struct Var
		{
			char type;
			int32 len;
			union
			{
				int32 i32;
				int64 i64;
				double f64;
				const_char_ptr str;
			};

			int32 toint32();
			int64 toint64();
		};
	public:
		UnpackHelper(lua_State* _L,void* buf,size_t len);
	public:
		int Push();
		int PushAll();
	public:
		int ReadToVar(Var& var);
		int ReadAllToVar(Var* vars,int size);
	private:
		int readType(char& t);
		int readBuffer(void* v, size_t n);
		int skip(size_t n);
	private:
		lua_State* L;
	private:
		char* mBuf;
		size_t mLen; 
		size_t mLenUsed;
	};
}

#endif // _pw_luaseri_