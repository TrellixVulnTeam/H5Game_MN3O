#ifndef _pwdist_method_helper_
#define _pwdist_method_helper_

#include "pwdist_common.h"

namespace pwdist
{
	// 静态方法 无返回值
	struct StaticMethodInvoker
	{
		static void Invoke( MethodCall* ctx,void (*func)())
		{
			(*func)();
		}

		template <class P1>
		static void Invoke( MethodCall* ctx,void (*func)(P1))
		{
			
			(*func)(
				pwdist::ParameterHelper<P1>::Get(ctx->call->params.params[0])
				);
		}

		template <class P1,class P2>
		static void Invoke( MethodCall* ctx,void (*func)(P1,P2))
		{
			(*func)(
				pwdist::ParameterHelper<P1>::Get(ctx->call->params.params[0]),
				pwdist::ParameterHelper<P2>::Get(ctx->call->params.params[1])
				);
		}

		template <class P1,class P2,class P3>
		static void Invoke( MethodCall* ctx,void (*func)(P1,P2,P3))
		{
			(*func)(
				pwdist::ParameterHelper<P1>::Get(ctx->call->params.params[0]),
				pwdist::ParameterHelper<P2>::Get(ctx->call->params.params[1]),
				pwdist::ParameterHelper<P3>::Get(ctx->call->params.params[2])
				);
		}

		template <class P1,class P2,class P3,class P4>
		static void Invoke( MethodCall* ctx,void (*func)(P1,P2,P3,P4))
		{
			(*func)(
				pwdist::ParameterHelper<P1>::Get(ctx->call->params.params[0]),
				pwdist::ParameterHelper<P2>::Get(ctx->call->params.params[1]),
				pwdist::ParameterHelper<P3>::Get(ctx->call->params.params[2]),
				pwdist::ParameterHelper<P4>::Get(ctx->call->params.params[3])
				);
		}

		template <class P1,class P2,class P3,class P4,class P5>
		static void Invoke( MethodCall* ctx,void (*func)(P1,P2,P3,P4,P5))
		{
			(*func)(
				pwdist::ParameterHelper<P1>::Get(ctx->call->params.params[0]),
				pwdist::ParameterHelper<P2>::Get(ctx->call->params.params[1]),
				pwdist::ParameterHelper<P3>::Get(ctx->call->params.params[2]),
				pwdist::ParameterHelper<P4>::Get(ctx->call->params.params[3]),
				pwdist::ParameterHelper<P5>::Get(ctx->call->params.params[4])
				);
		}

		template <class P1,class P2,class P3,class P4,class P5,class P6>
		static void Invoke( MethodCall* ctx,void (*func)(P1,P2,P3,P4,P5,P6))
		{
			(*func)(
				pwdist::ParameterHelper<P1>::Get(ctx->call->params.params[0]),
				pwdist::ParameterHelper<P2>::Get(ctx->call->params.params[1]),
				pwdist::ParameterHelper<P3>::Get(ctx->call->params.params[2]),
				pwdist::ParameterHelper<P4>::Get(ctx->call->params.params[3]),
				pwdist::ParameterHelper<P5>::Get(ctx->call->params.params[4]),
				pwdist::ParameterHelper<P6>::Get(ctx->call->params.params[5])
				);
		}
	};

	// 静态方法入口
	namespace StaticMethodHelper
	{
		template<class FN> struct Helper
		{
			static void Invoke(MethodCall* ctx)
			{
				StaticMethodImpl<FN>* impl = (StaticMethodImpl<FN>*)ctx->method;
				StaticMethodInvoker::Invoke(ctx,impl->fun);
			}
		};
	};

	// -----------------------------------------------------------------

	// 成员方法 无返回值

	struct ObjectMethodInvoker
	{
		template<class T>
		static void Invoke( MethodCall* ctx,T& callee,void (T::*func)())
		{
			(callee.*func)();
		}

		template <class T,class P1>
		static void Invoke( MethodCall* ctx,T& callee,void (T::*func)(P1))
		{
			(callee.*func)(
				pwdist::ParameterHelper<P1>::Get(ctx->call->params.params[0])
				);
		}

		template <class T,class P1,class P2>
		static void Invoke( MethodCall* ctx,T& callee,void (T::*func)(P1,P2))
		{
			(callee.*func)(
				pwdist::ParameterHelper<P1>::Get(ctx->call->params.params[0]),
				pwdist::ParameterHelper<P2>::Get(ctx->call->params.params[1])
				);
		}

		template <class T,class P1,class P2,class P3>
		static void Invoke( MethodCall* ctx,T& callee,void (T::*func)(P1,P2,P3))
		{
			(callee.*func)(
				pwdist::ParameterHelper<P1>::Get(ctx->call->params.params[0]),
				pwdist::ParameterHelper<P2>::Get(ctx->call->params.params[1]),
				pwdist::ParameterHelper<P3>::Get(ctx->call->params.params[2])
				);
		}

		template <class T,class P1,class P2,class P3,class P4>
		static void Invoke( MethodCall* ctx,T& callee,void (T::*func)(P1,P2,P3,P4))
		{
			(callee.*func)(
				pwdist::ParameterHelper<P1>::Get(ctx->call->params.params[0]),
				pwdist::ParameterHelper<P2>::Get(ctx->call->params.params[1]),
				pwdist::ParameterHelper<P3>::Get(ctx->call->params.params[2]),
				pwdist::ParameterHelper<P4>::Get(ctx->call->params.params[3])
				);
		}

		template <class T,class P1,class P2,class P3,class P4,class P5>
		static void Invoke( MethodCall* ctx,T& callee,void (T::*func)(P1,P2,P3,P4,P5))
		{
			(callee.*func)(
				pwdist::ParameterHelper<P1>::Get(ctx->call->params.params[0]),
				pwdist::ParameterHelper<P2>::Get(ctx->call->params.params[1]),
				pwdist::ParameterHelper<P3>::Get(ctx->call->params.params[2]),
				pwdist::ParameterHelper<P4>::Get(ctx->call->params.params[3]),
				pwdist::ParameterHelper<P5>::Get(ctx->call->params.params[4])
				);
		}

		template <class T,class P1,class P2,class P3,class P4,class P5,class P6>
		static void Invoke( MethodCall* ctx,T& callee,void (T::*func)(P1,P2,P3,P4,P5,P6))
		{
			(callee.*func)(
				pwdist::ParameterHelper<P1>::Get(ctx->call->params.params[0]),
				pwdist::ParameterHelper<P2>::Get(ctx->call->params.params[1]),
				pwdist::ParameterHelper<P3>::Get(ctx->call->params.params[2]),
				pwdist::ParameterHelper<P4>::Get(ctx->call->params.params[3]),
				pwdist::ParameterHelper<P5>::Get(ctx->call->params.params[4]),
				pwdist::ParameterHelper<P6>::Get(ctx->call->params.params[5])
				);
		}
	};

	// 成员方法入口
	namespace ObjectMethodHelper
	{
		template<class T,class FN> struct Helper
		{
			static void Invoke(MethodCall* ctx)
			{
				T* object = static_cast<T*>(ctx->obj);

				ObjectMethodImpl<T,FN>* impl = (ObjectMethodImpl<T,FN>*)ctx->method;
				ObjectMethodInvoker::Invoke(ctx,*object,impl->fun);
			}
		};
	};
}

#endif // _pwdist_method_helper_