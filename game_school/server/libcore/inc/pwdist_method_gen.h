#ifndef _pwdist_method_gen_
#define _pwdist_method_gen_

namespace pwdist
{
	template<class T> struct DefaultGen
	{
		static void GenDef(char* def)
		{
			char buf[2] = {0};
			buf[0] = ParameterHelper<T>::GetName();

			strcat(def,buf);
		}
	};

	// 静态方法 无返回值
	struct StaticMethod_GenDef
	{
		static void GenMethodDef(char* buf,void (*func)())
		{
			buf[0] = '\0';
		}

		template <class P1>
		static void GenMethodDef( char* buf,void (*func)(P1))
		{
			buf[0] = '\0';
			DefaultGen<P1>::GenDef(buf);
		}

		template <class P1,class P2>
		static void GenMethodDef( char* buf,void (*func)(P1,P2))
		{
			buf[0] = '\0';
			DefaultGen<P1>::GenDef(buf);
			DefaultGen<P2>::GenDef(buf);
		}

		template <class P1,class P2,class P3>
		static void GenMethodDef( char* buf,void (*func)(P1,P2,P3))
		{
			buf[0] = '\0';
			DefaultGen<P1>::GenDef(buf);
			DefaultGen<P2>::GenDef(buf);
			DefaultGen<P3>::GenDef(buf);
		}

		template <class P1,class P2,class P3,class P4>
		static void GenMethodDef( char* buf,void (*func)(P1,P2,P3,P4))
		{
			buf[0] = '\0';		
			DefaultGen<P1>::GenDef(buf);
			DefaultGen<P2>::GenDef(buf);
			DefaultGen<P3>::GenDef(buf);
			DefaultGen<P4>::GenDef(buf);
		}

		template <class P1,class P2,class P3,class P4,class P5>
		static void GenMethodDef( char* buf,void (*func)(P1,P2,P3,P4,P5))
		{
			buf[0] = '\0';
			DefaultGen<P1>::GenDef(buf);
			DefaultGen<P2>::GenDef(buf);
			DefaultGen<P3>::GenDef(buf);
			DefaultGen<P4>::GenDef(buf);
			DefaultGen<P5>::GenDef(buf);
		}

		template <class P1,class P2,class P3,class P4,class P5,class P6>
		static void GenMethodDef( char* buf,void (*func)(P1,P2,P3,P4,P5,P6))
		{
			buf[0] = '\0';
			DefaultGen<P1>::GenDef(buf);
			DefaultGen<P2>::GenDef(buf);
			DefaultGen<P3>::GenDef(buf);
			DefaultGen<P4>::GenDef(buf);
			DefaultGen<P5>::GenDef(buf);
			DefaultGen<P6>::GenDef(buf);
		}
	};

	// 无返回值
	template<class T> struct ObjectMethod_GenDef
	{
		static void GenMethodDef(char* buf,void (T::*func)())
		{
			buf[0] = '\0';
		}

		template <class P1>
		static void GenMethodDef( char* buf,void (T::*func)(P1))
		{
			buf[0] = '\0';
			DefaultGen<P1>::GenDef(buf);
		}

		template <class P1,class P2>
		static void GenMethodDef( char* buf,void (T::*func)(P1,P2))
		{
			buf[0] = '\0';
			DefaultGen<P1>::GenDef(buf);
			DefaultGen<P2>::GenDef(buf);
		}

		template <class P1,class P2,class P3>
		static void GenMethodDef( char* buf,void (T::*func)(P1,P2,P3))
		{
			buf[0] = '\0';
			DefaultGen<P1>::GenDef(buf);
			DefaultGen<P2>::GenDef(buf);
			DefaultGen<P3>::GenDef(buf);
		}

		template <class P1,class P2,class P3,class P4>
		static void GenMethodDef( char* buf,void (T::*func)(P1,P2,P3,P4))
		{
			buf[0] = '\0';
			DefaultGen<P1>::GenDef(buf);
			DefaultGen<P2>::GenDef(buf);
			DefaultGen<P3>::GenDef(buf);
			DefaultGen<P4>::GenDef(buf);
		}

		template <class P1,class P2,class P3,class P4,class P5>
		static void GenMethodDef( char* buf,void (T::*func)(P1,P2,P3,P4,P5))
		{
			buf[0] = '\0';
			DefaultGen<P1>::GenDef(buf);
			DefaultGen<P2>::GenDef(buf);
			DefaultGen<P3>::GenDef(buf);
			DefaultGen<P4>::GenDef(buf);
			DefaultGen<P5>::GenDef(buf);
		}

		template <class P1,class P2,class P3,class P4,class P5,class P6>
		static void GenMethodDef( char* buf,void (T::*func)(P1,P2,P3,P4,P5,P6))
		{
			buf[0] = '\0';
			DefaultGen<P1>::GenDef(buf);
			DefaultGen<P2>::GenDef(buf);
			DefaultGen<P3>::GenDef(buf);
			DefaultGen<P4>::GenDef(buf);
			DefaultGen<P5>::GenDef(buf);
			DefaultGen<P6>::GenDef(buf);
		}
	};
}

#endif // _pwdist_method_gen_