#ifndef _pwdist_dispatcher_
#define _pwdist_dispatcher_

#include "pwdist_common.h"
#include "pwdist_method_gen.h"
#include "pwdist_method_helper.h"

namespace pwdist
{
	class Dispatcher
	{
	public:
		virtual ~Dispatcher();
	public:
		int Dispatch(MethodCall& call);
	public:
		template<class FN> int Impl(const char* name,FN fn)
		{
			StaticMethodImpl<FN>* impl = new StaticMethodImpl<FN>();			pwdist::StaticMethod_GenDef::GenMethodDef(impl->mdef,fn);

 			strncpy(impl->name,name,_countof(impl->name));			impl->type = METHOD_TYPE_STATIC;			impl->fun = fn;			impl->pfn = StaticMethodHelper::Helper<FN>::Invoke;			impl->enabled = true;			bool succ = m_mapMethods.insert(std::make_pair(name,impl)).second;
			if( !succ )
			{
				delete impl;
				assert(false && "rpc name exists");
				return -1;
			}
			return 0;
		}

		template<class T,class FN> int Impl(const char* name,FN fn)
		{
 			ObjectMethodImpl<T,FN>* impl = new ObjectMethodImpl<T,FN>();
			pwdist::ObjectMethod_GenDef<T>::GenMethodDef(impl->mdef,fn);

			strncpy(impl->name,name,_countof(impl->name));
			impl->type = METHOD_TYPE_OBJECT;
			impl->fun = fn;
			impl->pfn = ObjectMethodHelper::Helper<T,FN>::Invoke;
			impl->enabled = true;
			bool succ = m_mapMethods.insert(std::make_pair(name,impl)).second;
			if( !succ )
			{
				delete impl;
				assert(false && "rpc name exists");
				return -1;
			}
			return 0;
		}

		virtual int OnUnknownCall(MethodCall& call);
	protected:
		typedef std_unordered_map<std::string,MethodImpl*> CollectionMethodsT;
	protected:
		CollectionMethodsT m_mapMethods;
	};
}

#endif // _pwdist_dispatcher_