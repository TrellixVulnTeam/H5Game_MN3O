/********************************************************************
	created:	2012/04/07
	created:	7:4:2012   10:03
	filename: 	e:\tmp\LuaHelper\pwlua.h
	file path:	e:\tmp\LuaHelper
	file base:	pwlua
	file ext:	h
	author:		cbh
	
	purpose:	
*********************************************************************/
#ifndef _pw_lua_
#define _pw_lua_

#include <vector>

extern "C" 
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

#include <cassert>
#include <string>
#include <string.h>
#include "pw_utils.h"
#include "pw_linked_object.h"
#include "pw_logger.h"

// #include "pw_def.h"

namespace pwlua
{

	class refcounted_object
	{
	public:
		refcounted_object()
		{
			_ref = 0;
		}
		virtual ~refcounted_object()
		{

		}
	public:
		void ref()
		{
			++_ref;
		}

		void unref()
		{
			if(--_ref == 0)
				delete this;
		}
	protected:
		int _ref;
	};

	template <class T,class U> class conversion
	{
		typedef char _small;
		typedef long _big;
		static _small test(U);
		static _big test(...);
		static T makeT();
	public:
		enum { exists = sizeof(test(makeT())) == sizeof(_small) };
		enum { exists2way = (exists && conversion<U,T>::exists) };
		enum { sameType = false };
	};

	template<bool,class T,class U> struct select;

	template<class T,class U> struct select<true,T,U>
	{
		typedef T Result;
	};

	template<class T,class U> struct select<false,T,U>
	{
		typedef U Result;
	};

	template<class T,class U,bool O>
	struct linked_init
	{
		static void exec(T* t,U* u)
		{
			u->init(t);
		}
	};

	template<class T,class U>
	struct linked_init<T,U,false>
	{
		static void exec(T* t,U* u)
		{
			
		}
	};

	template<class T,bool O>
	struct ref
	{
		static void exec(T* v)
		{
			static_cast<refcounted_object*>(v)->ref();
		}

		static void unexec(T* v)
		{
			static_cast<refcounted_object*>(v)->unref();
		}
	};

	template<class T>
	struct ref<T,false>
	{
		static void exec(T* v)
		{
		}

		static void unexec(T* v)
		{
		}
	};

#ifdef _MSC_VER
	typedef __int64 int64;
	typedef __int32 int32;
#else
	typedef long long int64;
	typedef int int32;
#endif

	static const bool is_i64_system = (sizeof(void*) == sizeof(int64));

	const int __lua_default_slot = 438349857;

	// ***************************************************************************

	namespace _detail
	{
		// ***************************************************************************

		typedef int (*fnCast)(lua_State* L,void* obj,const char* classname,int offset);
		typedef int (*fnFind)(lua_State* L,void* obj,const char* classname,int offset);

		typedef void* (*fnCppDynamicCast)(void*);

		struct _class
		{
			ptrdiff_t offset;
			fnCast fn_castup;
			fnCast fn_castdown;
			fnCast fn_castlup;
			fnCast fn_castldown;
			fnFind fn_index;

			fnCppDynamicCast fn_dyncast;

			char* classname;
			int meta;
		};

	}

	struct utils
	{
		static void print_script_info(lua_State* L);		
	};

	// ***************************************************************************

	template<class T> class class_name
	{
	public:
		static int meta;
		static bool linked_dtor;
		static char name[128];
		static _detail::_class* parents;
		static _detail::_class* subs;
	};

	template<class T> int	class_name<T>::meta = LUA_NOREF;
	template<class T> char	class_name<T>::name[128] = "";
	template<class T> bool	class_name<T>::linked_dtor = false;
	template<class T> _detail::_class*	class_name<T>::parents = NULL;
	template<class T> _detail::_class*	class_name<T>::subs = NULL;


	// ---------------------------------------------------------------------------------------------------------

	static const char* _class_name = "classname";
	static const char* _base_classes = "baseclasses";
	static const char* _sub_classes = "subclasses";
	static const char* _cast = "__cast";
	static const char* _cast_l = "cast";
	static const char* _IsNil_ = "IsNil";

	static const char _type_method_ = 100;
	static const char _type_object_ = 101;
	static const char _type_member_ = 102;

	// ---------------------------------------------------------------------------------------------------------


	extern int int64_eq(lua_State* L);
	extern int int64_lt(lua_State* L);
	extern int int64_le(lua_State* L);
	extern int int64_tostring(lua_State* L);
	extern int int64_convert(lua_State* L);
	extern int int64_unm(lua_State* L);
	extern int int64_mod(lua_State* L);
	extern int int64_is(lua_State* L);
	extern bool int64_check(lua_State* L,int index);

	extern int int64_error(lua_State* L,int index);

	typedef const char* (*fnContextInformation)(lua_State* L);

	//  int64 support

	const char cst_int64_metatable[] = "__int64_metatable";
	extern fnContextInformation g_pfnContextInformation;

	extern void initial_int64_support(lua_State* L);

#define PWLUA_CONTEXT_INFO(L) (g_pfnContextInformation ? g_pfnContextInformation(L) : "None")

	// ---------------------------------------------------------------------------------------------------------

	namespace _detail
	{

		// ***************************************************************************
		// ***************************************************************************
		// ***************************************************************************

		template<class T> struct stack_helper
		{
			
		};


		
		// ***************************************************************************

		template<class T> struct stack_helper<const std::vector<T>& >
		{
			static void push(lua_State* L,const std::vector<T>& val)
			{
				lua_newtable(L);
				for(size_t i = 0; i < val.size(); ++i)
				{
					lua_pushinteger(L,(int)i+1);
					stack_helper<T>::push(L,val[i]);
					lua_settable(L,-3);
				}
			}

			static std::vector<T> cast(lua_State* L,int index)
			{
				std::vector<T> results;

				lua_pushvalue(L,index);

				int len = lua_objlen(L,-1);
				for(int i = 0; i < len; ++ i)
				{
					lua_pushinteger(L,i+1);
					lua_gettable(L,-2);
					results.push_back(stack_helper<T>::cast(L,-1));
					lua_pop(L,1);
				}
				lua_pop(L,1);
				return results;
			}

			static bool check(lua_State* L,int index)
			{
				return true;
			}
		};

		// ***************************************************************************

		template<class T> struct stack_helper<std::vector<T>& >
		{
			static void push(lua_State* L,std::vector<T>& val)
			{
				lua_newtable(L);
				for(size_t i = 0; i < val.size(); ++i)
				{
					lua_pushinteger(L,(int)i+1);
					stack_helper<T>::push(L,val[i]);
					lua_settable(L,-3);
				}
			}

			static std::vector<T> cast(lua_State* L,int index)
			{
				std::vector<T> results;

				lua_pushvalue(L,index);

				int len = lua_objlen(L,-1);
				for(int i = 0; i < len; ++ i)
				{
					lua_pushinteger(L,i+1);
					lua_gettable(L,-2);
					results.push_back(stack_helper<T>::cast(L,-1));
					lua_pop(L,1);
				}
				lua_pop(L,1);
				return results;
			}

			static bool check(lua_State* L,int index)
			{
				return true;
			}
		};

		// ***************************************************************************

		template<class T> struct stack_helper<std::vector<T> >
		{
			static void push(lua_State* L,const std::vector<T>& val)
			{
				lua_newtable(L);
				for(size_t i = 0; i < val.size(); ++i)
				{
					lua_pushinteger(L,(int)(i+1));
					stack_helper<T>::push(L,val[i]);
					lua_settable(L,-3);
				}
			}

			static std::vector<T> cast(lua_State* L,int index)
			{
				std::vector<T> results;

				lua_pushvalue(L,index);

				int len = lua_objlen(L,-1);
				for(int i = 0; i < len; ++ i)
				{
					lua_pushinteger(L,(int)(i+1));
					lua_gettable(L,-2);
					results.push_back(stack_helper<T>::cast(L,-1));
					lua_pop(L,1);
				}
				lua_pop(L,1);
				return results;
			}

			static bool check(lua_State* L,int index)
			{
				return true;
			}
		};

		// ***************************************************************************

		template<class T> struct stack_helper<T*>
		{
			static void push(lua_State* L,T* val, bool gc = false);

			static T* cast(lua_State* L,int index);

			static bool check(lua_State* L,int index)
			{
				return lua_isuserdata(L,index) || lua_isnil(L,index);
			}

		};

		// ***************************************************************************

		template<class T> struct stack_helper<T&>
		{
			static void push(lua_State* L,T& val);
			
			static T& cast(lua_State* L,int index);

			static bool check(lua_State* L,int index)
			{
				return lua_isuserdata(L,index) || lua_isnil(L,index);
			}
		};

		// ***************************************************************************

		template<> struct stack_helper<bool>
		{		
			static void push(lua_State* L,const bool& val)
			{
				lua_pushboolean(L,val);
			}

			static int cast(lua_State* L,int index)
			{
				pwassertr(lua_isboolean(L,index),0);
				return lua_toboolean(L,index);
			}

			static bool check(lua_State* L,int index)
			{
				return lua_isboolean(L,index);
			}
		};

		// ***************************************************************************

		template<> struct stack_helper<char>
		{		
			static void push(lua_State* L,const char& val)
			{
				lua_pushinteger(L,val);
			}

			static char cast(lua_State* L,int index)
			{
				pwassertr(lua_isnumber(L,index),0x7f);
				return (char)lua_tointeger(L,index);
			}

			static bool check(lua_State* L,int index)
			{
				return lua_isnumber(L,index);
			}
		};

		// ***************************************************************************

		template<> struct stack_helper<short>
		{		
			static void push(lua_State* L,const short& val)
			{
				lua_pushinteger(L,val);
			}

			static short cast(lua_State* L,int index)
			{
				pwassertr(lua_isnumber(L,index),0x7fff);
				return (short)lua_tointeger(L,index);
			}

			static bool check(lua_State* L,int index)
			{
				return lua_isnumber(L,index);
			}
		};

		// ***************************************************************************

		template<> struct stack_helper<void*>
		{		
			static void push(lua_State* L,void* val)
			{
				lua_pushlightuserdata(L,val);
			}

			static void* cast(lua_State* L,short index)
			{
				pwassertr(lua_type(L,index) == LUA_TLIGHTUSERDATA,0);

				return lua_touserdata(L,index);
			}

			static bool check(lua_State* L,int index)
			{
				return lua_type(L,index) == LUA_TLIGHTUSERDATA;
			}
		};

		// ***************************************************************************

		template<> struct stack_helper<int32>
		{		
			static void push(lua_State* L,const int32& val)
			{
				lua_pushinteger(L,val);
			}

			static int32 cast(lua_State* L,int32 index)
			{
				pwassertr(lua_isnumber(L,index),0x7fffffff);
				return (int32)lua_tointeger(L,index);
			}

			static bool check(lua_State* L,int index)
			{
				return lua_isnumber(L,index);
			}
		};

		// ***************************************************************************

		template<> struct stack_helper<uint32>
		{		
			static void push(lua_State* L,const uint32& val)
			{
				lua_pushinteger(L,val);
			}

			static uint32 cast(lua_State* L,int32 index)
			{
				pwassertr(lua_isnumber(L,index),0x7fffffff);
				return (uint32)lua_tointeger(L,index);
			}

			static bool check(lua_State* L,int index)
			{
				return lua_isnumber(L,index);
			}
		};

		// ***************************************************************************

		template<> struct stack_helper<int64>
		{	
			static void push(lua_State* L,const int64& val)
			{
				if(is_i64_system)
				{
					lua_pushlightuserdata(L,(void*)val);
				}
				else
				{
// 					char buf[100] = "";
// 					pwutils::itoa(buf,val);
// 
// 					lua_newtable(L);
// 					lua_pushinteger(L,0);
// 					lua_pushstring(L,buf);
// 					lua_settable(L,-3);
					int64* p = (int64*)lua_newuserdata(L,sizeof(int64));
					*p = val;
				}
				lua_getglobal(L,cst_int64_metatable);
				if(lua_setmetatable(L,-2) == 0)
				{
					int64_error(L,1);
				}
			}

			static int64 cast(lua_State* L,int index)
			{
				int64 result = 0;
				int t = lua_type(L,index);

				if(is_i64_system)
				{
					if(t == LUA_TUSERDATA || t == LUA_TLIGHTUSERDATA)
					{
						result = (int64)lua_touserdata(L,index);
					}
					else if(t == LUA_TNUMBER)
					{
						result = (int64)lua_tonumber(L,index);
					}
					else if(t == LUA_TSTRING) 
					{
						result = pwutils::atoi(lua_tostring(L,index));
					}
// 					else if(t == LUA_TTABLE) 
// 					{
// 						lua_pushinteger(L,0);
// 						lua_gettable(L,index);
// 						result = pwutils::atoi(lua_tostring(L,-1));
// 						lua_pop(L,1);
// 					}
					else
					{
						result = 0;
						int64_error(L,index);
					}
				}
				else
				{
					if(t == LUA_TUSERDATA || t == LUA_TLIGHTUSERDATA)
					{
						int64* p = (int64*)lua_touserdata(L,index);
						result = *p;
					}
					else if(t == LUA_TNUMBER)
					{
						result = (int64)lua_tonumber(L,index);
					}
					else if(t == LUA_TSTRING) 
					{
						result = pwutils::atoi(lua_tostring(L,index));
					}
// 					else if(t == LUA_TTABLE) 
// 					{
// 						lua_pushinteger(L,0);
// 						lua_gettable(L,index);
// 						result = pwutils::atoi(lua_tostring(L,-1));
// 						lua_pop(L,1);
// 					}
					else
					{
						result = 0;
						int64_error(L,index);
					}
				
				}
				return result;
			}

			static bool check(lua_State* L,int index)
			{
				int t = lua_type(L,index);
				return t == LUA_TUSERDATA || t == LUA_TLIGHTUSERDATA || t == LUA_TNUMBER || t == LUA_TSTRING;
			}
		};

		// ***************************************************************************

		template<> struct stack_helper<double>
		{		
			static void push(lua_State* L,const double& val)
			{
				lua_pushnumber(L,val);
			}

			static double cast(lua_State* L,int index)
			{
				pwassertr(lua_isnumber(L,index),0.0f);
				return lua_tonumber(L,index);
			}

			static bool check(lua_State* L,int index)
			{
				return lua_isnumber(L,index);
			}
		};

		// ***************************************************************************

		template<> struct stack_helper<float>
		{		
			static void push(lua_State* L,const float& val)
			{
				lua_pushnumber(L,val);
			}

			static float cast(lua_State* L,int index)
			{
				pwassertr(lua_isnumber(L,index),0.0f);
				return (float)lua_tonumber(L,index);
			}

			static bool check(lua_State* L,int index)
			{
				return lua_isnumber(L,index);
			}
		};

		// ***************************************************************************

// 		template<> struct stack_helper<size_t>
// 		{		
// 			static void push(lua_State* L,const size_t& val)
// 			{
// 				lua_pushinteger(L,val);
// 			}
// 
// 			static size_t cast(lua_State* L,int index)
// 			{
// 				pwassertr(lua_isnumber(L,index),0x7fffffff);
// 				return (size_t)lua_tointeger(L,index);
// 			}
// 
// 			static bool check(lua_State* L,int index)
// 			{
// 				return lua_isnumber(L,index);
// 			}
// 		};

		// ***************************************************************************
		
		template<> struct stack_helper<const char*>
		{		
			static void push(lua_State* L,const char* val)
			{
				lua_pushstring(L,val);
			}

			static const char* cast(lua_State* L,int index)
			{
				pwassertr(lua_isstring(L,index) || lua_isnil(L,index),"");
				return lua_tostring(L,index);
			}

			static bool check(lua_State* L,int index)
			{
				return lua_isstring(L,index) || lua_isnil(L,index);
			}
		};

		// ***************************************************************************

		template<> struct stack_helper<std::string>
		{		
			static void push(lua_State* L,const std::string& val)
			{
				lua_pushlstring(L,val.c_str(),val.length());
			}

			static std::string cast(lua_State* L,int index)
			{
				pwassertr(lua_isstring(L,index) || lua_isnil(L,index),"");
				size_t len = 0;
				const char* s = lua_tolstring(L,index,&len);
				return std::string(s,len);
			}

			static bool check(lua_State* L,int index)
			{
				return lua_isstring(L,index) || lua_isnil(L,index);
			}
		};

		// ***************************************************************************
		// ***************************************************************************
		// ***************************************************************************

		struct cast
		{
			template<class T1,class T2> static T1* to(T2* p)
			{
				return static_cast<T1*>(p);
			}
		};

		// ***************************************************************************
		// ***************************************************************************
		// ***************************************************************************

		template<class T1,class T2> ptrdiff_t offset()
		{
			T2* p2 = (T2*)1000000L;
			return (ptrdiff_t)cast::to<T1>(p2) - (ptrdiff_t)cast::to<T2>(p2);
		};


		// ***************************************************************************
		// ***************************************************************************

		// ***************************************************************************
		// ***************************************************************************

		template<class T> struct object
		{
			struct proxy : public pwutils::linked_object
			{
				proxy()
				{
				}

				virtual void detach()
				{
					obj = NULL;
					pwutils::linked_object::detach();
				}
				char type;
				T* obj;
				bool gc;
				bool linked;
				ptrdiff_t offset;
				int meta;
			};

			
			// ******************************************************************************************

			struct member_proxy_base
			{
				char type;
				lua_CFunction getter;
				lua_CFunction setter;
			};


			template<class D> struct member
			{
				struct member_proxy : public member_proxy_base
				{
					D (T::*fnget)();
					void (T::*fnset)(D t);
				};

				static int get(lua_State* L)
				{
					proxy* _proxy = (proxy*)lua_touserdata(L,1);
					T* obj = (T*)((char*)_proxy->obj + _proxy->offset);
					_proxy->offset = 0;

					// 2 == name
					// const char* name = lua_tostring(L,2);

					member_proxy* mproxy = (member_proxy*)lua_touserdata(L,3);

					if(mproxy->fnget == NULL)
					{
						lua_pushstring(L,"error can't get member");
						lua_error(L);
					}
					stack_helper<D>::push(L,(obj->*(mproxy->fnget))());

					return 1;
				}

				static int set(lua_State* L)
				{
					proxy* _proxy = (proxy*)lua_touserdata(L,1);
					T* obj = (T*)((char*)_proxy->obj + _proxy->offset);
					_proxy->offset = 0;

					// 2 == name
					// 3 = value

					member_proxy* mproxy = (member_proxy*)lua_touserdata(L,4);

					if(mproxy->fnset == NULL)
					{
						lua_pushstring(L,"error can't get member");
						lua_error(L);
					}

					(obj->*(mproxy->fnset))(stack_helper<D>::cast(L,3));

					return 0;
				}
			};

			template<class D,class DT> struct member_slow
			{
				struct member_proxy : public member_proxy_base
				{
					DT dt;
				};

				static int get(lua_State* L)
				{
					proxy* _proxy = (proxy*)lua_touserdata(L,1);
					T* obj = (T*)((char*)_proxy->obj + _proxy->offset);
					_proxy->offset = 0;

					// 2 == name
					// const char* name = lua_tostring(L,2);

					member_proxy* mproxy = (member_proxy*)lua_touserdata(L,3);
					
					stack_helper<D>::push(L,(obj->*mproxy->dt));

					return 1;
				}

				static int set(lua_State* L)
				{
					proxy* _proxy = (proxy*)lua_touserdata(L,1);
					T* obj = (T*)((char*)_proxy->obj + _proxy->offset);
					_proxy->offset = 0;

					// 2 == name
					// 3 = value

					member_proxy* mproxy = (member_proxy*)lua_touserdata(L,4);

					(obj->*mproxy->dt) = stack_helper<D>::cast(L,3);

					return 0;
				}
			};

			template<class D,class DT> struct member_slow<D*,DT>
			{
				struct member_proxy : public member_proxy_base
				{
					DT dt;
				};

				static int get(lua_State* L)
				{
					proxy* _proxy = (proxy*)lua_touserdata(L,1);
					T* obj = (T*)((char*)_proxy->obj + _proxy->offset);
					_proxy->offset = 0;

					// 2 == name
					// const char* name = lua_tostring(L,2);

					member_proxy* mproxy = (member_proxy*)lua_touserdata(L,3);

					stack_helper<D&>::push(L,*(obj->*mproxy->dt));

					return 1;
				}

				static int set(lua_State* L)
				{
					proxy* _proxy = (proxy*)lua_touserdata(L,1);
					T* obj = (T*)((char*)_proxy->obj + _proxy->offset);
					_proxy->offset = 0;

					// 2 == name
					// 3 = value

					member_proxy* mproxy = (member_proxy*)lua_touserdata(L,4);

					(obj->*mproxy->dt) = stack_helper<D*>::cast(L,3);

					return 0;
				}
			};
			
			// ******************************************************************************************
		};
			
		

		template<class T,class FN> struct object_method_slow
		{
			struct method_proxy
			{
				char type;
				FN fn;
			};
		};
		// ***************************************************************************

		template<class T,class FN,long N> struct object_method
		{
			static FN fn;
		};
		
		template<class T,class FN,long N> FN object_method<T,FN,N>::fn = NULL;
		
		// ***************************************************************************

		template<class T,class FN,long N,class RT> struct object_method_helper
		{
			static int invoke(lua_State* L)
			{
				typename object<T>::proxy* _proxy = (typename object<T>::proxy*)lua_touserdata(L,1);
				pwassertn(_proxy);

				T* obj = (T*)((char*)_proxy->obj + _proxy->offset);
				_proxy->offset = 0;
				pwreportvars(_proxy->obj,typeid(T).name() << " " << typeid(FN).name() << " context:" << PWLUA_CONTEXT_INFO(L));
				pwassertn(_proxy->obj);

				stack_helper<RT>::push(L,call(*obj,object_method<T,FN,N>::fn,L,2));
				return 1;
			}

			static RT call(T& caller,RT (T::*func)(),lua_State* L,int index)
			{
				return (caller.*func)();
			}

			template<class P1> static RT call(T& caller,RT (T::*func)(P1),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0),
							(utils::print_script_info(L),RT()));
				return (caller.*func)
					(
					stack_helper<P1>::cast(L,index + 0)
					);
			}

			template<class P1,class P2> static RT call(T& caller,RT (T::*func)(P1,P2),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1),
							(utils::print_script_info(L),RT()));
				return (caller.*func)
					(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1)
					);
			}

			template<class P1,class P2,class P3> static RT call(T& caller,RT (T::*func)(P1,P2,P3),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1) && 
							stack_helper<P3>::check(L,index + 2),
							(utils::print_script_info(L),RT()));
				return (caller.*func)
					(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1),
					stack_helper<P3>::cast(L,index + 2)
					);
			}

			template<class P1,class P2,class P3,class P4> static RT call(T& caller,RT (T::*func)(P1,P2,P3,P4),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1) && 
							stack_helper<P3>::check(L,index + 2) &&
							stack_helper<P4>::check(L,index + 3),
							(utils::print_script_info(L),RT()));
				return (caller.*func)
					(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1),
					stack_helper<P3>::cast(L,index + 2),
					stack_helper<P4>::cast(L,index + 3)
					);
			}

			template<class P1,class P2,class P3,class P4,class P5> static RT call(T& caller,RT (T::*func)(P1,P2,P3,P4,P5),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1) && 
							stack_helper<P3>::check(L,index + 2) &&
							stack_helper<P4>::check(L,index + 3) &&
							stack_helper<P5>::check(L,index + 4),
							(utils::print_script_info(L),RT()));
				return (caller.*func)
					(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1),
					stack_helper<P3>::cast(L,index + 2),
					stack_helper<P4>::cast(L,index + 3),
					stack_helper<P5>::cast(L,index + 4)
					);
			}
		};

		// ***************************************************************************

		template<class T,class FN,long N> struct object_method_helper<T,FN,N,void>
		{
			static int invoke(lua_State* L)
			{
				typename object<T>::proxy* _proxy = (typename object<T>::proxy*)lua_touserdata(L,1);
				pwassertn(_proxy);

				T* obj = (T*)((char*)_proxy->obj + _proxy->offset);
				_proxy->offset = 0;
				pwreportvars(_proxy->obj,typeid(T).name() << " " << typeid(FN).name() << " context:" << PWLUA_CONTEXT_INFO(L));
				pwassertn(_proxy->obj);

				call(*obj,object_method<T,FN,N>::fn,L,2);
				return 0;
			}

			static void call(T& caller,void (T::*func)(),lua_State* L,int index)
			{
				(caller.*func)();
			}

			template<class P1> static void call(T& caller,void (T::*func)(P1),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0),
							(utils::print_script_info(L),void()));
				(caller.*func)
					(
					stack_helper<P1>::cast(L,index + 0)
					);
			}

			template<class P1,class P2> static void call(T& caller,void (T::*func)(P1,P2),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1),
							(utils::print_script_info(L),void()));
				(caller.*func)
					(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1)
					);
			}

			template<class P1,class P2,class P3> static void call(T& caller,void (T::*func)(P1,P2,P3),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1) && 
							stack_helper<P3>::check(L,index + 2),
							(utils::print_script_info(L),void()));
				(caller.*func)
					(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1),
					stack_helper<P3>::cast(L,index + 2)
					);
			}

			template<class P1,class P2,class P3,class P4> static void call(T& caller,void (T::*func)(P1,P2,P3,P4),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1) && 
							stack_helper<P3>::check(L,index + 2) &&
							stack_helper<P4>::check(L,index + 3),
							(utils::print_script_info(L),void()));
				(caller.*func)
					(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1),
					stack_helper<P3>::cast(L,index + 2),
					stack_helper<P4>::cast(L,index + 3)
					);
			}

			template<class P1,class P2,class P3,class P4,class P5> static void call(T& caller,void (T::*func)(P1,P2,P3,P4,P5),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1) && 
							stack_helper<P3>::check(L,index + 2) &&
							stack_helper<P4>::check(L,index + 3) &&
							stack_helper<P5>::check(L,index + 4),
							(utils::print_script_info(L),void()));
				(caller.*func)
					(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1),
					stack_helper<P3>::cast(L,index + 2),
					stack_helper<P4>::cast(L,index + 3),
					stack_helper<P5>::cast(L,index + 4)
					);
			}
		};

		template<class T,class FN,class RT> struct object_slow_method_helper
		{
			static int invoke(lua_State* L)
			{
				typename object<T>::proxy* _proxy = (typename object<T>::proxy*)lua_touserdata(L,2);
				T* obj = (T*)((char*)_proxy->obj + _proxy->offset);
				_proxy->offset = 0;

				typename _detail::object_method_slow<T,FN>::method_proxy* mproxy = 
					(typename _detail::object_method_slow<T,FN>::method_proxy*)lua_touserdata(L,1);

				stack_helper<RT>::push(L,object_method_helper<T,FN,__lua_default_slot,RT>::call(*obj,mproxy->fn,L,3) );
				return 1;					
			}
		};

		template<class T,class FN> struct object_slow_method_helper<T,FN,void>
		{
			static int invoke(lua_State* L)
			{
				typename object<T>::proxy* _proxy = (typename object<T>::proxy*)lua_touserdata(L,2);
				T* obj = (T*)((char*)_proxy->obj + _proxy->offset);
				_proxy->offset = 0;

				object_method_slow<T,FN>* mproxy = (object_method_slow<T,FN>*)lua_touserdata(L,1);

				object_method_helper<T,FN,__lua_default_slot,void>::call(*obj,mproxy->fn,L,3);
				
				return 0;
			}
		};
		
		// ***************************************************************************
		// ***************************************************************************
		// ***************************************************************************

		template<class FN> struct method_slow
		{
			struct method_proxy
			{
				char type;
				FN fn;
			};
		};
		
		// ******************************************************************************************

		template<class FN,long N> struct method
		{
			static FN fn;
		};
		
		template<class FN,long N> FN method<FN,N>::fn = NULL;
		
		template<class FN,long N,class RT> struct method_helper
		{
			static int invoke(lua_State* L)
			{
				stack_helper<RT>::push(L,call(method<FN,N>::fn,L,1));
				return 1;
			}


			static RT call(RT (*func)(),lua_State* L,int index)
			{
				return (*func)();

			}

			template<class P1> static RT call(RT (*func)(P1),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0),
							(utils::print_script_info(L),RT()));
				return (*func)(
								stack_helper<P1>::cast(L,index + 0)
							);
				
			}

			template<class P1,class P2> static RT call(RT (*func)(P1,P2),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1),
							(utils::print_script_info(L),RT()));
				return (*func)(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1)
					);

			}

			template<class P1,class P2,class P3> static RT call(RT (*func)(P1,P2,P3),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1) && 
							stack_helper<P3>::check(L,index + 2),
							(utils::print_script_info(L),RT()));
				return (*func)(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1),
					stack_helper<P3>::cast(L,index + 2)
					);

			}

			template<class P1,class P2,class P3,class P4> static RT call(RT (*func)(P1,P2,P3,P4),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1) && 
							stack_helper<P3>::check(L,index + 2) &&
							stack_helper<P4>::check(L,index + 3),
							(utils::print_script_info(L),RT()));
				return (*func)(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1),
					stack_helper<P3>::cast(L,index + 2),
					stack_helper<P4>::cast(L,index + 3)
					);

			}

			template<class P1,class P2,class P3,class P4,class P5> static RT call(RT (*func)(P1,P2,P3,P4,P5),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1) && 
							stack_helper<P3>::check(L,index + 2) &&
							stack_helper<P4>::check(L,index + 3) &&
							stack_helper<P5>::check(L,index + 4),
							(utils::print_script_info(L),RT()));
				return (*func)(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1),
					stack_helper<P3>::cast(L,index + 2),
					stack_helper<P4>::cast(L,index + 3),
					stack_helper<P5>::cast(L,index + 4)
					);

			}
		};
		
		// ******************************************************************************************
		
		template<class FN,class RT> struct slow_method_helper
		{
			static int invoke(lua_State* L)
			{
				typename method_slow<FN>::method_proxy* mproxy = (typename method_slow<FN>::method_proxy*)lua_touserdata(L,1);

				stack_helper<RT>::push(L,method_helper<FN,__lua_default_slot,RT>::call(mproxy->fn,L,2) );
				return 1;					
			}
		};

		template<class FN> struct slow_method_helper<FN,void>
		{
			static int invoke(lua_State* L)
			{
				typename method_slow<FN>::method_proxy* mproxy = (typename method_slow<FN>::method_proxy*)lua_touserdata(L,1);

				method_helper<FN,__lua_default_slot,void>::call(mproxy->fn,L,2);
				
				return 0;
			}
		};

	// ******************************************************************************************

		template<class FN,long N> struct method_helper<FN,N,void>
		{
			static int invoke(lua_State* L)
			{
				call(method<FN,N>::fn,L,1);
				return 0;
			}


			static void call(void (*func)(),lua_State* L,int index)
			{
				(*func)();
			}

			template<class P1> static void call(void (*func)(P1),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0),
							(utils::print_script_info(L),void()));
				(*func)(
					stack_helper<P1>::cast(L,index + 0)
					);

			}

			template<class P1,class P2> static void call(void (*func)(P1,P2),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1),
							(utils::print_script_info(L),void()));
				(*func)(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1)
					);

			}

			template<class P1,class P2,class P3> static void call(void (*func)(P1,P2,P3),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1) && 
							stack_helper<P3>::check(L,index + 2),
							(utils::print_script_info(L),void()));
				(*func)(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1),
					stack_helper<P3>::cast(L,index + 2)
					);

			}

			template<class P1,class P2,class P3,class P4> static void call(void (*func)(P1,P2,P3,P4),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1) && 
							stack_helper<P3>::check(L,index + 2) &&
							stack_helper<P4>::check(L,index + 3),
							(utils::print_script_info(L),void()));
				(*func)(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1),
					stack_helper<P3>::cast(L,index + 2),
					stack_helper<P4>::cast(L,index + 3)
					);

			}

			template<class P1,class P2,class P3,class P4,class P5> static void call(void (*func)(P1,P2,P3,P4,P5),lua_State* L,int index)
			{
				pwassertr(	stack_helper<P1>::check(L,index + 0) && 
							stack_helper<P2>::check(L,index + 1) && 
							stack_helper<P3>::check(L,index + 2) &&
							stack_helper<P4>::check(L,index + 3) &&
							stack_helper<P5>::check(L,index + 4),
							(utils::print_script_info(L),void()));
				(*func)(
					stack_helper<P1>::cast(L,index + 0),
					stack_helper<P2>::cast(L,index + 1),
					stack_helper<P3>::cast(L,index + 2),
					stack_helper<P4>::cast(L,index + 3),
					stack_helper<P5>::cast(L,index + 4)
					);

			}
		};

		// ***************************************************************************
		// ***************************************************************************
		// ***************************************************************************

		template<class T> struct constructor_helper0
		{
			static int create(lua_State* L)
			{
				static const bool is_refcounted_obj = conversion<T,refcounted_object>::exists == 1;

				typename object<T>::proxy* _proxy = (typename object<T>::proxy*)(lua_newuserdata(L,sizeof(typename object<T>::proxy)));
				_proxy->gc = true;
				_proxy->type = _type_object_;
				_proxy->offset = 0;
				_proxy->linked = false;
				_proxy->obj = new T();
				_proxy->meta = class_name<T>::meta;
				assert(!class_name<T>::linked);

				ref<T,is_refcounted_obj>::exec(_proxy->obj);
				
				lua_getref(L,class_name<T>::meta);
				lua_setmetatable(L,-2);
				return 1;
			}
		};

		template<class T,class P1> struct constructor_helper1
		{
			static int create(lua_State* L)
			{
				static const bool is_refcounted_obj = conversion<T,refcounted_object>::exists == 1;

				typename object<T>::proxy* _proxy = (typename object<T>::proxy*)lua_newuserdata(L,sizeof(typename object<T>::proxy));
				_proxy->gc = true;
				_proxy->offset = 0;
				_proxy->linked = false;
				_proxy->type = _type_object_;
				_proxy->meta = class_name<T>::meta;
				assert(!class_name<T>::linked_dtor);

				_proxy->obj = new T
					(
						stack_helper<P1>::cast(L,1)
					);

				ref<T,is_refcounted_obj>::exec(_proxy->obj);

				lua_getref(L,class_name<T>::meta);
				lua_setmetatable(L,-2);
				return 1;
			}
		};

		template<class T,class P1,class P2> struct constructor_helper2
		{
			static int create(lua_State* L,P1 p1,P2 p2)
			{
				static const bool is_refcounted_obj = conversion<T,refcounted_object>::exists == 1;

				typename object<T>::proxy* _proxy = (typename object<T>::proxy*)(lua_newuserdata(L,sizeof(object<T>::proxy)));
				_proxy->gc = true;
				_proxy->offset = 0;
				_proxy->linked = false;
				_proxy->type = _type_object_;
				_proxy->meta = class_name<T>::meta;
				assert(!class_name<T>::linked);

				_proxy->obj = new T
					(
						stack_helper<P1>::cast(L,1),
						stack_helper<P2>::cast(L,2)
					);

				ref<T,is_refcounted_obj>::exec(_proxy->obj);
				lua_getref(L,class_name<T>::meta);
				lua_setmetatable(L,-2);
				return 1;
			}
		};
	}
	

	// ---------------------------------------------------------------------------------------------------------

	template<class SRC,class DST> class cast_helper
	{
	public:
		static void* execute(void* s)
		{
			try
			{
				SRC* src = reinterpret_cast<SRC*>(s);
				return dynamic_cast<DST*>(src);
			}
			catch(...)
			{
				return NULL;
			}
		}
	};

	template<class T> class	class_helper
	{
		enum { MAX_PARENTS = 20, };
	public:
		class_helper(lua_State* _L,const char* _name)
		{
			static const bool is_linked_master = conversion<T,pwutils::linked_object_master>::exists;

			L = _L;
			pwassert(strlen(_name) < sizeof(class_name<T>::name));
		#ifdef _MSC_VER
			strcpy_s(class_name<T>::name,_name);
		#else
			strcpy(class_name<T>::name,_name);
		#endif

			lua_newtable(L);
			
			lua_pushstring(L,&class_name<T>::name[0]);
			lua_setfield(L,-2,"name");

			lua_setglobal(L,class_name<T>::name);

			lua_newtable(L);
			
			void* p = NULL;
			
			p = lua_newuserdata(L,sizeof(_detail::_class) * MAX_PARENTS);
			memset(p,0,sizeof(_detail::_class) * MAX_PARENTS);
			lua_setfield(L,-2,_base_classes);

			class_name<T>::parents = (_detail::_class*)p;

			p = lua_newuserdata(L,sizeof(_detail::_class) * MAX_PARENTS);
			memset(p,0,sizeof(_detail::_class) * MAX_PARENTS);
			lua_setfield(L,-2,_sub_classes);			

			class_name<T>::subs = (_detail::_class*)p;

			lua_pushcfunction(L,&class_helper<T>::cast);
			lua_setfield(L,-2,_cast);

			lua_pushcfunction(L,&class_helper<T>::cast_l);
			lua_setfield(L,-2,_cast_l);	

			lua_pushcfunction(L,&class_helper<T>::isNil);
			lua_setfield(L,-2,_IsNil_);				

			class_name<T>::meta = lua_ref(L,true);

			make_index();
			make_newindex();

			if(is_linked_master)
			{
				linked_dtor();
			}
		}

		template<class PARENT> class_helper<T>& inherit()
		{
			_detail::_class* subs = class_name<PARENT>::subs;
			while(subs->fn_index != NULL)
				++subs;

			subs->classname = &class_name<T>::name[0];
			subs->offset = _detail::offset<T,PARENT>();
			subs->fn_index = &class_helper<T>::_actual_index;
			subs->fn_castup = &class_helper<T>::cast_up;
			subs->fn_castdown = &class_helper<T>::cast_down;
			subs->fn_castlup = &class_helper<T>::cast_lup;
			subs->fn_castldown = &class_helper<T>::cast_ldown;
			subs->fn_dyncast = &cast_helper<PARENT,T>::execute;
			subs->meta = class_name<T>::meta;
			
			_detail::_class* parents = class_name<T>::parents;

			while(parents->fn_index != NULL)
				++parents;

			parents->fn_index = &class_helper<PARENT>::_actual_index;
			parents->offset = _detail::offset<PARENT,T>();
			parents->classname = &class_name<PARENT>::name[0];
			parents->fn_castup = &class_helper<PARENT>::cast_up;
			parents->fn_castdown = &class_helper<PARENT>::cast_down;
			parents->fn_castlup = &class_helper<PARENT>::cast_lup;
			parents->fn_castldown = &class_helper<PARENT>::cast_ldown;
			parents->fn_dyncast = &cast_helper<T,PARENT>::execute;
			parents->meta = class_name<PARENT>::meta;
			return *this;
		}

		class_helper<T>& make_index()
		{
			lua_getref(L,class_name<T>::meta);			
			lua_pushcfunction(L,&_index);
			lua_setfield(L,-2,"__index");
			lua_pop(L,1);

			return *this;
		}

		class_helper<T>& make_newindex()
		{
			lua_getref(L,class_name<T>::meta);			
			lua_pushcfunction(L,&_newindex);
			lua_setfield(L,-2,"__newindex");
			lua_pop(L,1);

			return *this;
		}
	public:
		class_helper<T>& dtor()
		{
			lua_getref(L,class_name<T>::meta);			
			
			lua_pushcfunction(L,&_gc);
			lua_setfield(L,-2,"__gc");

			lua_pushcfunction(L,&_setgc);
			lua_setfield(L,-2,"setgc");

			lua_pop(L,1);
			class_name<T>::linked_dtor = false;
			return *this;
		}

		class_helper<T>& linked_dtor()
		{
			lua_getref(L,class_name<T>::meta);			
			lua_pushcfunction(L,&_linked_gc);
			lua_setfield(L,-2,"__gc");
			lua_pop(L,1);
			class_name<T>::linked_dtor = true;
			return *this;
		}
	public:
		class_helper<T>& ctorctor()
		{
			lua_getglobal(L,class_name<T>::name);			
			lua_pushcfunction(L,&_detail::constructor_helper0<T>::create);
			lua_setfield(L,-2,"new");
			lua_pop(L,1);
			return *this;
		}

		template<class P1> class_helper<T>& ctor()
		{
			lua_getglobal(L,class_name<T>::name);			
			lua_CFunction lfn = &_detail::constructor_helper1<T,P1>::create;
			lua_pushcfunction(L,lfn);
			lua_setfield(L,-2,"new");
			lua_pop(L,1);
			return *this;
		}

		template<class P1,class P2> class_helper<T>& ctor()
		{
			lua_getglobal(L,class_name<T>::name);
			lua_CFunction lfn = &_detail::constructor_helper2<T,P1,P2>::create;
			lua_pushcfunction(L,lfn);
			lua_setfield(L,-2,"new");
			lua_pop(L,1);
			return *this;
		}

		template<class D,class DT> class_helper<T>& member(const char* name,DT dt)
		{
			lua_getref(L,class_name<T>::meta);

		#ifdef _MSC_VER
			_detail::object<T>::member_slow<D,DT>::member_proxy* _proxy = 
				(_detail::object<T>::member_slow<D,DT>::member_proxy*)
				lua_newuserdata(L,sizeof(_detail::object<T>::member_slow<D,DT>::member_proxy));
		#else
			typename _detail::object<T>::template member_slow<D,DT>::member_proxy* _proxy = 
				(typename _detail::object<T>::template member_slow<D,DT>::member_proxy*)
				lua_newuserdata(L,sizeof(typename _detail::object<T>::template member_slow<D,DT>::member_proxy));
		#endif	
			
			_proxy->dt = dt;
			_proxy->type = _type_member_;
			
		#ifdef _MSC_VER
			_proxy->getter = _detail::object<T>::member_slow<D,DT>::get;
			_proxy->setter = _detail::object<T>::member_slow<D,DT>::set;
		#else
			_proxy->getter = _detail::object<T>::template member_slow<D,DT>::get;
			_proxy->setter = _detail::object<T>::template member_slow<D,DT>::set;
		#endif

			lua_setfield(L,-2,name);
			lua_pop(L,1);

			return *this;
		}

		template<class D> class_helper<T>& member(const char* name,D (T::*fngetter)(),void (T::*fnsetter)(D))
		{
			lua_getref(L,class_name<T>::meta);
		#ifdef _MSC_VER
			_detail::object<T>::member<D>::member_proxy* _proxy = 
				(_detail::object<T>::member<D>::member_proxy*)
				lua_newuserdata(L,sizeof(_detail::object<T>::member<D>::member_proxy));

			_proxy->type = _type_member_;
			_proxy->getter = _detail::object<T>::member<D>::get;
			_proxy->setter = _detail::object<T>::member<D>::set;
			_proxy->fnget = fngetter;
			_proxy->fnset = fnsetter;
		#else
			typename _detail::object<T>::template member<D>::member_proxy* _proxy = 
				(typename _detail::object<T>::template member<D>::member_proxy*)
				lua_newuserdata(L,sizeof(typename _detail::object<T>::template member<D>::member_proxy));

			_proxy->type = _type_member_;
			_proxy->getter = &_detail::object<T>::template member<D>::get;
			_proxy->setter = &_detail::object<T>::template member<D>::set;
			_proxy->fnget = fngetter;
			_proxy->fnset = fnsetter;
		#endif
			lua_setfield(L,-2,name);
			lua_pop(L,1);
			return *this;
		}

		class_helper<T>& normal_method(const char* name,lua_CFunction fn)
		{
			lua_getref(L,class_name<T>::meta);
			lua_pushcfunction(L,fn);
			lua_setfield(L,-2,name);
			lua_pop(L,1);
			return *this;
		}

		template<long N, class RT,class FN> class_helper<T>& method_fast(const char* name,FN func)
		{

			assert((_detail::object_method<T,FN,N>::fn) == NULL
				|| (_detail::object_method<T,FN,N>::fn) == func);
			
			_detail::object_method<T,FN,N>::fn = func;

			lua_CFunction lfn = &_detail::object_method_helper<T,FN,N,RT>::invoke;

			lua_getref(L,class_name<T>::meta);
			lua_pushcfunction(L,lfn);
			lua_setfield(L,-2,name);
			lua_pop(L,1);
			return *this;
		}

		template<class RT,class FN> class_helper<T>& method(const char* name,FN fn)
		{		
			lua_CFunction lfn = _detail::object_slow_method_helper<T,FN,RT>::invoke;

			lua_getref(L,class_name<T>::meta);

			typename _detail::method_slow<FN>::method_proxy* _proxy = 
				(typename _detail::method_slow<FN>::method_proxy*)
				lua_newuserdata(L,sizeof(typename _detail::method_slow<FN>::method_proxy));
		
			_proxy->fn = fn;
			_proxy->type = _type_method_;
			lua_newtable(L);
			lua_pushcfunction(L,lfn);
			lua_setfield(L,-2,"__call");
			lua_setmetatable(L,-2);

			lua_setfield(L,-2,name);
			lua_pop(L,1);
			return *this;
		}
	public:
		static int _try_index_member(lua_State* L)
		{
			int type = lua_type(L,-1);

			if(type == LUA_TLIGHTUSERDATA || type == LUA_TUSERDATA)
			{
				char* _proxy_type = (char*)lua_touserdata(L,-1);
				if((*_proxy_type) == _type_member_)
				{
					lua_pop(L,1); // member userdata

					typename _detail::object<T>::member_proxy_base*  _proxy = (typename _detail::object<T>::member_proxy_base*)_proxy_type;
					
					lua_pushcfunction(L,_proxy->getter);
					lua_pushvalue(L,1);
					lua_pushvalue(L,2);
					lua_pushlightuserdata(L,_proxy);
					if(lua_pcall(L,3,1,0) != 0)
						lua_error(L);
					return 1;
				}
			}
			return 1;
		}

		static int _try_newindex_member(lua_State* L)
		{
			int type = lua_type(L,-1);

			if(type == LUA_TLIGHTUSERDATA || type == LUA_TUSERDATA)
			{
				char* _proxy_type = (char*)lua_touserdata(L,-1);
				if((*_proxy_type) == _type_member_)
				{
					lua_pop(L,1); // member userdata

					typename _detail::object<T>::member_proxy_base*  _proxy = (typename _detail::object<T>::member_proxy_base*)_proxy_type;

					lua_pushcfunction(L,_proxy->setter);
					lua_pushvalue(L,1);
					lua_pushvalue(L,2);
					lua_pushvalue(L,3);
					lua_pushlightuserdata(L,_proxy);
					if(lua_pcall(L,4,0,0) != 0)
						lua_error(L);
					return 0;
				}
			}
			lua_pushnil(L);
			return 1;
		}
	public:
		static int _newindex(lua_State* L)
		{
			void* _proxy = lua_touserdata(L,1);
			const char* name = lua_tostring(L,2);

			if(_actual_index(L,_proxy,name,0) == 1)
			{
				if(_try_newindex_member(L) == 0)
					return 0;
				lua_pop(L,1); // nil
			}

			char buf[128] = "";
			#ifdef _MSC_VER
				sprintf_s(buf,"__newindex can't find member,%s",lua_tostring(L,2));
			#else
				sprintf(buf,"__newindex can't find member,%s",lua_tostring(L,2));
			#endif
			
			lua_pushstring(L,buf);
			lua_error(L);

			return 0;
		}
		
	public:
		static int _index(lua_State* L)
		{
			void* _proxy = lua_touserdata(L,1);
			const char* name = lua_tostring(L,2);

			if(_actual_index(L,_proxy,name,0) == 1)
			{
				return _try_index_member(L);
			}

			typename _detail::object<T>::proxy* p = (typename _detail::object<T>::proxy*)_proxy;

			p->offset = 0;

			char buf[128] = "";
			#ifdef _MSC_VER
				sprintf_s(buf,"__index can't find member,%s",lua_tostring(L,2));
			#else
				sprintf(buf,"__index can't find member,%s",lua_tostring(L,2));
			#endif

			lua_pushstring(L,buf);
			lua_error(L);

			return 0;
		}

		static int _actual_index(lua_State* L,void* _prx,const char* name,int offset)
		{
			typename _detail::object<T>::proxy* _proxy = (typename _detail::object<T>::proxy*)_prx;

			if(strcmp(name,_class_name) == 0)
			{
				lua_pushstring(L,class_name<T>::name);
				return 1;
			}

			lua_getref(L,class_name<T>::meta);
			lua_getfield(L,-1,name);

			if( lua_type(L,-1) != LUA_TNIL)
			{
				_proxy->offset += offset;
				lua_remove(L,-2);
				return 1;
			}

			lua_pop(L,2); // nil && meta table

			_detail::_class* parents = class_name<T>::parents;

			while(parents->fn_index != NULL)
			{
				if(parents->fn_index(L,_prx,name,parents->offset) == 1)
				{
					return 1;
				}
				++parents;
			}

			return 0;
		}

		static int _linked_gc(lua_State* L)
		{
			typename _detail::object<T>::proxy* _proxy = (typename _detail::object<T>::proxy*)lua_touserdata(L,1);
			if(_proxy->linked)
			{
				_proxy->~proxy();
			}
			_proxy->obj = NULL;
			_proxy->gc = false;
			_proxy->linked = false;
			return 0;
		}

		static int _gc(lua_State* L)
		{
			static const bool is_refcounted_object = conversion<T,refcounted_object>::exists;

			typename _detail::object<T>::proxy* _proxy = (typename _detail::object<T>::proxy*)lua_touserdata(L,1);
			if(_proxy->gc)
			{
				if(is_refcounted_object)
					ref<T,is_refcounted_object>::unexec(_proxy->obj);
				else
					delete _proxy->obj;
			}
			_proxy->obj = NULL;
			_proxy->gc = false;
			return 0;
		}

		static int _setgc(lua_State* L)
		{
			static const bool is_refcounted_object = conversion<T,refcounted_object>::exists;

			typename _detail::object<T>::proxy* _proxy = (typename _detail::object<T>::proxy*)lua_touserdata(L,1);
			bool gc = lua_toboolean(L,2);

			if(!is_refcounted_object)
			{
				_proxy->gc = gc;
			}
			return 0;
		}
	public:
		static int cast(lua_State* L)
		{
			void* i = lua_touserdata(L,1);
			const char* classname = (const char*)lua_touserdata(L,2);

			if(cast_up(L,i,classname,0) != 1)
			{
				return cast_down(L,i,classname,0);
			}
			return 1;
		}

		static int cast_l(lua_State* L)
		{
			void* i = lua_touserdata(L,1);
			const char* classname = lua_tostring(L,2);

 			if(cast_lup(L,i,classname,0) == 1)
				return 1;
 			if(cast_ldown(L,i,classname,0) == 1)
				return 1;
 			lua_pushnil(L);
 			return 1;
		}
	public:
		static int isNil(lua_State* L)
		{
			void* i = lua_touserdata(L,1);
			if(i == NULL)
			{
				lua_pushboolean(L,true);
				return 1;
			}

			typename _detail::object<T>::proxy* _proxy = (typename _detail::object<T>::proxy*)i;
			if(_proxy == NULL || _proxy->obj == NULL)
			{
				lua_pushboolean(L,true);
				return 1;
			}
			lua_pushboolean(L,false);
			return 1;
		}
	public:
		static int cast_up(lua_State* L,void* obj,const char* classname,int offset)
		{
			if(classname == class_name<T>::name)
			{
				lua_pushlightuserdata(L,(char*)obj + offset);
				return 1;
			}

			_detail::_class* parents = class_name<T>::parents;

			while(parents->classname != NULL)
			{
				if(parents->fn_castup(L,obj,classname,parents->offset) == 1)
					return 1;
				++parents;
			}

			return 0;
		}

		static int cast_down(lua_State* L,void* obj,const char* classname,int offset)
		{
			if(classname == class_name<T>::name)
			{
				lua_pushlightuserdata(L,(char*)obj + offset);
				return 1;
			}

			_detail::_class* subs = class_name<T>::subs;

			while(subs->classname != NULL)
			{
				if(subs->fn_dyncast(obj) != NULL && subs->fn_castdown(L,obj,classname,subs->offset) == 1)
					return 1;
				++subs;
			}

			return 0;
		}

		static int cast_lup(lua_State* L,void* prx,const char* classname,int offset)
		{
			if(strcmp(classname,class_name<T>::name) == 0)
			{
				typename _detail::object<T>::proxy* p = (typename _detail::object<T>::proxy*)prx;

				_detail::stack_helper<T&>::push(L,*(T*)((char*)p->obj + offset));
				
				return 1;
			}

			_detail::_class* parents = class_name<T>::parents;			
			while(parents->classname != NULL)
			{
				if(parents->fn_castlup(L,prx,classname,parents->offset) == 1)
					return 1;
				++parents;
			}

			return 0;
		}

		static int cast_ldown(lua_State* L,void* prx,const char* classname,int offset)
		{
			typename _detail::object<T>::proxy* p = (typename _detail::object<T>::proxy*)prx;

			if(strcmp(classname,class_name<T>::name) == 0)
			{
				_detail::stack_helper<T&>::push(L,*(T*)((char*)p->obj + offset));

				return 1;
			}

			_detail::_class* subs = class_name<T>::subs;

			while(subs->classname != NULL)
			{
				if(subs->fn_dyncast(p->obj) != NULL && subs->fn_castldown(L,prx,classname,subs->offset) == 1)
					return 1;
				++subs;
			}
			return 0;
		}
	private:
		lua_State* L;
	};

	// ---------------------------------------------------------------------------------------------------------


	template<class T> class_helper<T> class_(lua_State* L,const char* name)
	{
		return class_helper<T>(L,name);
	}

	template<long N,class RT,class FN> void method_fast(lua_State* L,const char* name,FN fn)
	{
		if(_detail::method<FN,N>::fn != NULL)
		{
			assert((_detail::method<FN,N>::fn) == fn);
		}
		_detail::method<FN,N>::fn = fn;
		lua_CFunction lfn = &_detail::method_helper<FN,N,RT>::invoke;
		lua_pushcfunction(L,lfn);
		lua_setglobal(L,name);
	}

	template<class RT,class FN>  void method(lua_State* L,const char* name,FN fn)
	{
		lua_CFunction lfn = _detail::slow_method_helper<FN,RT>::invoke;

		
		typename _detail::method_slow<FN>::method_proxy* _proxy = 
			(typename _detail::method_slow<FN>::method_proxy*)
			lua_newuserdata(L,sizeof(typename _detail::method_slow<FN>::method_proxy));
		_proxy->type = _type_method_;
		_proxy->fn = fn;
		lua_newtable(L);
		lua_pushcfunction(L,lfn);
		lua_setfield(L,-2,"__call");
		lua_setmetatable(L,-2);

		lua_setglobal(L,name);
	}

	// ---------------------------------------------------------------------------------------------------------

	class reference
	{
	public:
		reference(lua_State* _L,const char* name)
			: L(_L)
		{
			lua_getglobal(L,name);
			ref = lua_ref(L,true);
		}

		reference(lua_State* _L)
			: L(_L)
		{
			ref = lua_ref(L,true);
		}

		~reference()
		{
			lua_unref(L,ref);
		}

		void push()
		{
			lua_getref(L,ref);
		}

		template<class T> T cast();
	private:
		reference(const reference& r);
		reference operator=(const reference&);
	private:
		lua_State* L;
		int ref;
	};

	// ---------------------------------------------------------------------------------------------------------

	class value
	{
	private:
		value(const value& r);
		value& operator =(const value& r);
		void* operator new(size_t size);
		void  operator delete(void* pp);
	public:
		value(lua_State* _L,reference& r)
		{
			L = _L;
			r.push();
			_stack_index = -1;
		}
		value(lua_State* _L,int stack_index)
		{
			L = _L;
			_stack_index = stack_index;
		}

		value(lua_State* _L,const char* name,int table = LUA_GLOBALSINDEX)
		{
			L = _L;
			
			if(!lua_istable(L,table) && !lua_isuserdata(L,table))
				lua_pushnil(L);
			else
				lua_getfield(L,table,name);
			_stack_index = -1;
		}

		value(lua_State* _L,const char* name,reference& r)
		{
			L = _L;

			r.push();

			if(!lua_istable(L,-1) && !lua_isuserdata(L,-1))
				lua_pushnil(L);
			else
				lua_getfield(L,-1,name);
			
			lua_remove(L,-2);

			_stack_index = -1;
		}

		~value()
		{
			if(_stack_index < 0)
				lua_pop(L,1);
		}
	public:
		inline int type() 
		{
			return lua_type(L,_stack_index);
		}

		inline int is_callable()
		{
			int t = type();
			return t == LUA_TFUNCTION || t == LUA_TUSERDATA;
		}
	public:
		template<class T> T cast()
		{
			return _detail::stack_helper<T>::cast(L,_stack_index);
		}

		template<class RT> int invoke(RT& result)
		{
			pwassertf(is_callable());
			lua_pushvalue(L,_stack_index);
			int result2 = lua_pcall(L,0,1,0);
			if(result2 == 0)
			{
				result = _detail::stack_helper<RT>::cast(L,-1);
				lua_pop(L,1);
			}
			return result2;
		}

		template<class RT,class P1> RT invoke(RT& result,P1 p1)
		{
			pwassertr(is_callable(),RT());
			lua_pushvalue(L,_stack_index);
			_detail::stack_helper<P1>::push(L,p1);
			int result2 = lua_pcall(L,1,1,0);
			if(result2 == 0)
			{
				result = _detail::stack_helper<RT>::cast(L,-1);
				lua_pop(L,1);
			}
			return result2;
		}

		template<class RT,class P1,class P2> RT invoke(RT& result,P1 p1,P2 p2)
		{
			pwassertr(is_callable(),RT());
			lua_pushvalue(L,_stack_index);
			_detail::stack_helper<P1>::push(L,p1);
			_detail::stack_helper<P2>::push(L,p2);
			int result2 = lua_pcall(L,2,1,0);
			if(result2 == 0)
			{
				result = _detail::stack_helper<RT>::cast(L,-1);
				lua_pop(L,1);
			}
			return result2;
		}

		template<class RT,class P1,class P2,class P3> RT invoke(RT& result,P1 p1,P2 p2,P3 p3)
		{
			pwassertr(is_callable(),RT());
			lua_pushvalue(L,_stack_index);
			_detail::stack_helper<P1>::push(L,p1);
			_detail::stack_helper<P2>::push(L,p2);
			_detail::stack_helper<P3>::push(L,p3);
			int result2 = lua_pcall(L,3,1,0);
			if(result2 == 0)
			{
				result = _detail::stack_helper<RT>::cast(L,-1);
				lua_pop(L,1);
			}
			return result2;
		}

		template<class RT,class P1,class P2,class P3,class P4> RT invoke(RT& result,P1 p1,P2 p2,P3 p3,P4 p4)
		{
			pwassertr(is_callable(),RT());
			lua_pushvalue(L,_stack_index);
			_detail::stack_helper<P1>::push(L,p1);
			_detail::stack_helper<P2>::push(L,p2);
			_detail::stack_helper<P3>::push(L,p3);
			_detail::stack_helper<P4>::push(L,p4);
			int result2 = lua_pcall(L,4,1,0);
			if(result2 == 0)
			{
				result = _detail::stack_helper<RT>::cast(L,-1);
				lua_pop(L,1);
			}
			return result2;
		}

		template<class RT,class P1,class P2,class P3,class P4,class P5> RT invoke(RT& result,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5)
		{
			pwassertr(is_callable(),RT());
			lua_pushvalue(L,_stack_index);
			_detail::stack_helper<P1>::push(L,p1);
			_detail::stack_helper<P2>::push(L,p2);
			_detail::stack_helper<P3>::push(L,p3);
			_detail::stack_helper<P4>::push(L,p4);
			_detail::stack_helper<P5>::push(L,p5);
			int result2 = lua_pcall(L,5,1,0);
			if(result2 == 0)
			{
				result = _detail::stack_helper<RT>::cast(L,-1);
				lua_pop(L,1);
			}
			return result2;
		}
	public:
		int invoke_nr()
		{
			pwassertf(is_callable());
			lua_pushvalue(L,_stack_index);
			return lua_pcall(L,0,0,0);
		}


		template<class P1> int invoke_nr(P1 p1)
		{
			pwassertf(is_callable());
			lua_pushvalue(L,_stack_index);
			_detail::stack_helper<P1>::push(L,p1);
			return lua_pcall(L,1,0,0);
		}

		template<class P1,class P2> int invoke_nr(P1 p1,P2 p2)
		{
			pwassertf(is_callable());
			lua_pushvalue(L,_stack_index);
			_detail::stack_helper<P1>::push(L,p1);
			_detail::stack_helper<P2>::push(L,p2);
			return lua_pcall(L,2,0,0);
		}

		template<class P1,class P2,class P3> int invoke_nr(P1 p1,P2 p2,P3 p3)
		{
			pwassertf(is_callable());
			lua_pushvalue(L,_stack_index);
			_detail::stack_helper<P1>::push(L,p1);
			_detail::stack_helper<P2>::push(L,p2);
			_detail::stack_helper<P3>::push(L,p3);
			return lua_pcall(L,3,0,0);
		}

		template<class P1,class P2,class P3,class P4> int invoke_nr(P1 p1,P2 p2,P3 p3,P4 p4)
		{
			pwassertf(is_callable());
			lua_pushvalue(L,_stack_index);
			_detail::stack_helper<P1>::push(L,p1);
			_detail::stack_helper<P2>::push(L,p2);
			_detail::stack_helper<P3>::push(L,p3);
			_detail::stack_helper<P4>::push(L,p4);
			return lua_pcall(L,4,0,0);
		}

		template<class P1,class P2,class P3,class P4,class P5> int invoke_nr(P1 p1,P2 p2,P3 p3,P4 p4,P5 p5)
		{
			pwassertf(is_callable());
			lua_pushvalue(L,_stack_index);
			_detail::stack_helper<P1>::push(L,p1);
			_detail::stack_helper<P2>::push(L,p2);
			_detail::stack_helper<P3>::push(L,p3);
			_detail::stack_helper<P4>::push(L,p4);
			_detail::stack_helper<P5>::push(L,p5);
			return lua_pcall(L,5,0,0);
		}
	private:
		int _stack_index;
		lua_State* L;
	};

	// *********************************************************************

	template<class T>
	T& pwlua::_detail::stack_helper<T&>::cast( lua_State* L,int index )
	{
		assert(lua_isuserdata(L,index) || lua_isnil(L,index));
		assert(class_name<T>::meta != LUA_NOREF && "class nofound");
		typename object<T>::proxy* _proxy = (typename object<T>::proxy*)(lua_touserdata(L,index));
		if(_proxy == NULL)
			return NULL;

		T* r = pwlua::_detail::stack_helper<T*>::cast(L,index);

		return *r;
	}


	template<class T>
	void pwlua::_detail::stack_helper<T&>::push( lua_State* L,T& val )
	{
		return pwlua::_detail::stack_helper<T*>::push(L,&val,false);
	}


	template<class T>
	T* pwlua::_detail::stack_helper<T*>::cast( lua_State* L,int index )
	{
		assert(lua_isuserdata(L,index) || lua_isnil(L,index));
		assert(class_name<T>::meta != LUA_NOREF && "class nofound");

		typename object<T>::proxy* _proxy = (typename object<T>::proxy*)(lua_touserdata(L,index));
		if(_proxy == NULL)
			return NULL;

		if(_proxy->meta == class_name<T>::meta)
		{
			return (T*)_proxy->obj;
		}
		else
		{
			lua_getref(L,_proxy->meta);
			lua_getfield(L,-1,_cast);
			lua_remove(L,-2);
			lua_pushlightuserdata(L,_proxy->obj);
			lua_pushlightuserdata(L,&class_name<T>::name[0]);
			lua_pcall(L,2,1,0);

			T* result = (T*)lua_touserdata(L,-1);
			lua_pop(L,1);
			return result;
		}
	}

	template<class T>
	void pwlua::_detail::stack_helper<T*>::push( lua_State* L,T* val, bool gc)
	{
		if(val != NULL)
		{
			static const bool is_refcounted_obj = conversion<T,refcounted_object>::exists == 1;
			static const bool is_linked_object  = conversion<T,pwutils::linked_object_master>::exists == 1;

			assert(class_name<T>::meta != LUA_NOREF && "class nofound");
			
			typename object<T>::proxy* _proxy = (typename object<T>::proxy*)lua_newuserdata(L,sizeof(typename object<T>::proxy));

			if(is_linked_object && class_name<T>::linked_dtor)
			{
				new(_proxy) typename object<T>::proxy();
				linked_init<T,typename object<T>::proxy,is_linked_object>::exec(val,_proxy);
			}
			_proxy->linked = is_linked_object && class_name<T>::linked_dtor;
			_proxy->gc = gc;
			_proxy->type = _type_object_;
			_proxy->offset = 0;
			_proxy->obj = val;
			_proxy->meta = class_name<T>::meta;

			if(!_proxy->linked && is_refcounted_obj && gc)
			{
				ref<T,is_refcounted_obj>::exec(_proxy->obj);
			}
			lua_getref(L,class_name<T>::meta);
			lua_setmetatable(L,-2);
		}
		else
		{
			lua_pushnil(L);
		}
	}
	
	template<class T> T reference::cast()
	{
		value t(L,*this);
		return t.cast<T>();
	}

	
}

#endif // _pw_lua_
