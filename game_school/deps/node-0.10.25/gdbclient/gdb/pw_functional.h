#ifndef _pw_functional_
#define _pw_functional_

#include <string.h>
#include <assert.h>
#include <new>

#ifdef __linux
	#include <sys/types.h>
#endif

/*
#include "pw_functional.h"
#include "pw_signal.h"
#include <stdio.h>

using namespace  pwutils;

int testfn0() { printf("%s\n",__FUNCTION__); return 1; }
int testfn1(int v) {printf("%s\n",__FUNCTION__); return 1;}
int testfn2(int v,int v1) {printf("%s\n",__FUNCTION__); return 1;}
int testfn3(int v,int v1,int v2) {printf("%s\n",__FUNCTION__); return 1;}
int testfn4(int v,int v1,int v2,int v3) {printf("%s\n",__FUNCTION__); return 1;}
int testfn5(int v,int v1,int v2,int v3,int v4) {printf("%s\n",__FUNCTION__); return 1;}

class Test
{
public:
	int testfn0() {printf("%s\n",__FUNCTION__); return 1;}
	int testfn1(int v) {printf("%s\n",__FUNCTION__); return 1;}
	int testfn2(int v,int v1) {printf("%s\n",__FUNCTION__); return 1;}
	int testfn3(int v,int v1,int v2) {printf("%s\n",__FUNCTION__); return 1;}
	int testfn4(int v,int v1,int v2,int v3) {printf("%s\n",__FUNCTION__); return 1;}
	int testfn5(int v,int v1,int v2,int v3,int v4) {printf("%s\n",__FUNCTION__); return 1;}

	int v;
};

int main(int argc, char* argv[])
{
	Test test;
	test.v = 349005435;

	function0<int> v0(&testfn0);
	function1<int,int> v1(&testfn1);;
	function2<int,int,int> v2(&testfn2);;
	function3<int,int,int,int> v3(&testfn3);;
	function4<int,int,int,int,int> v4(&testfn4);;
	function5<int,int,int,int,int,int> v5(&testfn5);;

	function0<int> vv0;
	function1<int,int> vv1;
	function2<int,int,int> vv2;
	function3<int,int,int,int> vv3;
	function4<int,int,int,int,int> vv4;
	function5<int,int,int,int,int,int> vv5;

	v0();
	v1(1);
	v2(1,2);
	v3(1,2,3);
	v4(1,2,3,4);
	v5(1,2,3,4,5);

	v0.bind(&testfn0);
	v1.bind(&testfn1);
	v2.bind(&testfn2);
	v3.bind(&testfn3);
	v4.bind(&testfn4);
	v5.bind(&testfn5);

	{
		vv0 = v0;
		vv1 = v1;
		vv2 = v2;
		vv3 = v3;
		vv4 = v4;
		vv5 = v5;

		if(vv0 == v0) printf("0 equal ok\n");
		if(vv1 == v1) printf("1 equal ok\n");
		if(vv2 == v2) printf("2 equal ok\n");
		if(vv3 == v3) printf("3 equal ok\n");
		if(vv4 == v4) printf("4 equal ok\n");
		if(vv5 == v5) printf("5 equal ok\n");

		vv0();
		vv1(1);
		vv2(1,2);
		vv3(1,2,3);
		vv4(1,2,3,4);
		vv5(1,2,3,4,5);
	}

	v0();
	v1(1);
	v2(1,2);
	v3(1,2,3);
	v4(1,2,3,4);
	v5(1,2,3,4,5);

	v0.bind(&test,&Test::testfn0);
	v1.bind(&test,&Test::testfn1);
	v2.bind(&test,&Test::testfn2);
	v3.bind(&test,&Test::testfn3);
	v4.bind(&test,&Test::testfn4);
	v5.bind(&test,&Test::testfn5);

	{
		vv0 = v0;
		vv1 = v1;
		vv2 = v2;
		vv3 = v3;
		vv4 = v4;
		vv5 = v5;

		vv0();
		vv1(1);
		vv2(1,2);
		vv3(1,2,3);
		vv4(1,2,3,4);
		vv5(1,2,3,4,5);
	}
	v0();
	v1(1);
	v2(1,2);
	v3(1,2,3);
	v4(1,2,3,4);
	v5(1,2,3,4,5);


	return 0;
}
*/

namespace pwutils
{

	// ------------------------------------------------------------


	template<class RT> struct __method_0
	{
		virtual RT invoke() = 0;
	};

	template<class RT,class P1> struct __method_1
	{
		virtual RT invoke(P1) = 0;
	};

	template<class RT,class P1,class P2> struct __method_2
	{
		virtual RT invoke(P1,P2) = 0;
	};

	template<class RT,class P1,class P2,class P3> struct __method_3
	{
		virtual RT invoke(P1,P2,P3) = 0;
	};

	template<class RT,class P1,class P2,class P3,class P4> struct __method_4
	{
		virtual RT invoke(P1,P2,P3,P4) = 0;
	};

	template<class RT,class P1,class P2,class P3,class P4,class P5> struct __method_5
	{
		virtual RT invoke(P1,P2,P3,P4,P5) = 0;
	};

	// ------------------------------------------------------------

	template<class T,class RT> struct object_method_0 : public __method_0<RT>
	{
		typedef RT (T::*FuncType)();

		T* t;
		FuncType fn;

		virtual RT invoke()
		{
			return (t->*fn)();
		}
	};

	template<class T,class RT,class P1> struct object_method_1 : public __method_1<RT,P1>
	{
		typedef RT (T::*FuncType)(P1);

		T* t;
		FuncType fn;

		virtual RT invoke(P1 p1)
		{
			return (t->*fn)(p1);
		}
	};

	template<class T,class RT,class P1,class P2> struct object_method_2 : public __method_2<RT,P1,P2>
	{
		typedef RT (T::*FuncType)(P1,P2);

		T* t;
		FuncType fn;

		virtual RT invoke(P1 p1,P2 p2)
		{
			return (t->*fn)(p1,p2);
		}
	};

	template<class T,class RT,class P1,class P2,class P3> struct object_method_3 : public __method_3<RT,P1,P2,P3>
	{
		typedef RT (T::*FuncType)(P1,P2,P3);

		T* t;
		FuncType fn;

		virtual RT invoke(P1 p1,P2 p2,P3 p3)
		{
			return (t->*fn)(p1,p2,p3);
		}
	};

	template<class T,class RT,class P1,class P2,class P3,class P4> struct object_method_4 : public __method_4<RT,P1,P2,P3,P4>
	{
		typedef RT (T::*FuncType)(P1,P2,P3,P4);

		T* t;
		FuncType fn;

		virtual RT invoke(P1 p1,P2 p2,P3 p3,P4 p4)
		{
			return (t->*fn)(p1,p2,p3,p4);
		}
	};

	template<class T,class RT,class P1,class P2,class P3,class P4,class P5> struct object_method_5 : public __method_5<RT,P1,P2,P3,P4,P5>
	{
		typedef RT (T::*FuncType)(P1,P2,P3,P4,P5);

		T* t;
		FuncType fn;

		virtual RT invoke(P1 p1,P2 p2,P3 p3,P4 p4,P5 p5)
		{
			return (t->*fn)(p1,p2,p3,p4,p5);
		}
	};

	// ------------------------------------------------------------

	template<class RT> struct static_method_0 : public __method_0<RT>
	{
		typedef RT (*FuncType)();

		FuncType fn;

		virtual RT invoke()
		{
			return fn();
		}
	};

	template<class RT,class P1> struct static_method_1 : public __method_1<RT,P1>
	{
		typedef RT (*FuncType)(P1);

		FuncType fn;

		virtual RT invoke(P1 p1)
		{
			return fn(p1);
		}
	};

	template<class RT,class P1,class P2> struct static_method_2 : public __method_2<RT,P1,P2>
	{
		typedef RT (*FuncType)(P1,P2);

		FuncType fn;

		virtual RT invoke(P1 p1,P2 p2)
		{
			return fn(p1,p2);
		}
	};

	template<class RT,class P1,class P2,class P3> struct static_method_3 : public __method_3<RT,P1,P2,P3>
	{
		typedef RT (*FuncType)(P1,P2,P3);

		FuncType fn;

		virtual RT invoke(P1 p1,P2 p2,P3 p3)
		{
			return fn(p1,p2,p3);
		}
	};

	template<class RT,class P1,class P2,class P3,class P4> struct static_method_4 : public __method_4<RT,P1,P2,P3,P4>
	{
		typedef RT (*FuncType)(P1,P2,P3,P4);

		FuncType fn;

		virtual RT invoke(P1 p1,P2 p2,P3 p3,P4 p4)
		{
			return fn(p1,p2,p3,p4);
		}
	};

	template<class RT,class P1,class P2,class P3,class P4,class P5> struct static_method_5 : public __method_5<RT,P1,P2,P3,P4,P5>
	{
		typedef RT (*FuncType)(P1,P2,P3,P4,P5);

		FuncType fn;

		virtual RT invoke(P1 p1,P2 p2,P3 p3,P4 p4,P5 p5)
		{
			return fn(p1,p2,p3,p4,p5);
		}
	};

	// ------------------------------------------------------------

	template<class RT> struct function0
	{
		__method_0<RT>* m;
		char buf[sizeof(void*)*5];

		template<class T> function0(T* t,RT (T::*fn)()) { clear(); bind(t,fn); }
		function0(RT (*fn)()) { clear(); bind(fn); }

		function0() { clear(); }
		function0(const function0<RT>& r) { memcpy(buf,r.buf,sizeof(buf)); m = (__method_0<RT>*)buf; }
		function0<RT>& operator=(const function0<RT>& r) { memcpy(buf,r.buf,sizeof(buf)); m = (__method_0<RT>*)buf; return *this; }
		bool operator==(const function0<RT>& r) { return memcmp(r.buf,buf,sizeof(buf)) == 0; }

		inline bool valid() { return m != 0; }
		inline void clear() { m = 0; memset(buf,0,sizeof(buf)); }

		template<class T> void bind(T* t,RT (T::*fn)())
		{
			size_t s = sizeof(object_method_0<T,RT>);
			assert(s <= sizeof(buf));
			object_method_0<T,RT>* r = (object_method_0<T,RT>*)buf;
			new(r) object_method_0<T,RT>();

			r->t = t;
			r->fn = fn;
			m = r;
		}

		void bind(RT (*fn)())
		{
			size_t s = sizeof(static_method_0<RT>);
			assert(s <= sizeof(buf));
			static_method_0<RT>* r = (static_method_0<RT>*)buf;
			new(r) static_method_0<RT>();

			r->fn = fn;
			m = r;
		}

		RT operator()()
		{
			if(m == 0)
				return RT();
			return m->invoke();
		}
	};

	template<class RT,class P1> struct function1
	{
		__method_1<RT,P1>* m;
		char buf[sizeof(void*)*5];

		template<class T> function1(T* t,RT (T::*fn)(P1)) { clear(); bind(t,fn); }
		function1(RT (*fn)(P1)) { clear(); bind(fn); }

		function1() { clear(); }
		function1(const function1<RT,P1>& r) { memcpy(buf,r.buf,sizeof(buf)); m = (__method_1<RT,P1>*)buf; }
		function1<RT,P1>& operator=(const function1<RT,P1>& r) { memcpy(buf,r.buf,sizeof(buf)); m = (__method_1<RT,P1>*)buf; return *this; }
		bool operator==(const function1<RT,P1>& r) { return memcmp(r.buf,buf,sizeof(buf)) == 0; }

		inline bool valid() { return m != 0; }
		inline void clear() { m = 0; memset(buf,0,sizeof(buf)); }

		template<class T> void bind(T* t,RT (T::*fn)(P1))
		{
			size_t s = sizeof(object_method_1<T,RT,P1>);
			assert(s <= sizeof(buf));
			object_method_1<T,RT,P1>* r = (object_method_1<T,RT,P1>*)buf;
			new(r) object_method_1<T,RT,P1>();

			r->t = t;
			r->fn = fn;
			m = r;
		}

		void bind(RT (*fn)(P1))
		{
			size_t s = sizeof(static_method_1<RT,P1>);
			assert(s <= sizeof(buf));
			static_method_1<RT,P1>* r = (static_method_1<RT,P1>*)buf;
			new(r) static_method_1<RT,P1>();

			r->fn = fn;
			m = r;
		}

		RT operator()(P1 p1)
		{
			if(m == 0)
				return RT();
			return m->invoke(p1);
		}
	};

	template<class RT,class P1,class P2> struct function2
	{
		__method_2<RT,P1,P2>* m;
		char buf[sizeof(void*)*5];

		template<class T> function2(T* t,RT (T::*fn)(P1,P2)) { clear(); bind(t,fn); }
		function2(RT (*fn)(P1,P2)) { clear(); bind(fn); }

		function2() { clear(); }
		function2(const function2<RT,P1,P2>& r) { memcpy(buf,r.buf,sizeof(buf)); m = (__method_2<RT,P1,P2>*)buf; }
		function2<RT,P1,P2>& operator=(const function2<RT,P1,P2>& r) { memcpy(buf,r.buf,sizeof(buf)); m = (__method_2<RT,P1,P2>*)buf; return *this; }
		bool operator==(const function2<RT,P1,P2>& r) { return memcmp(r.buf,buf,sizeof(buf)) == 0; }

		inline bool valid() { return m != 0; }
		inline void clear() { m = 0; memset(buf,0,sizeof(buf)); }

		template<class T> void bind(T* t,RT (T::*fn)(P1,P2))
		{
			size_t s = sizeof(object_method_2<T,RT,P1,P2>);
			assert(s <= sizeof(buf));
			object_method_2<T,RT,P1,P2>* r = (object_method_2<T,RT,P1,P2>*)buf;
			new(r) object_method_2<T,RT,P1,P2>();

			r->t = t;
			r->fn = fn;
			m = r;
		}

		void bind(RT (*fn)(P1,P2))
		{
			size_t s = sizeof(static_method_2<RT,P1,P2>);
			assert(s <= sizeof(buf));
			static_method_2<RT,P1,P2>* r = (static_method_2<RT,P1,P2>*)buf;
			new(r) static_method_2<RT,P1,P2>();

			r->fn = fn;
			m = r;
		}

		RT operator()(P1 p1,P2 p2)
		{
			if(m == 0)
				return RT();
			return m->invoke(p1,p2);
		}
	};

	template<class RT,class P1,class P2,class P3> struct function3
	{
		__method_3<RT,P1,P2,P3>* m;
		char buf[sizeof(void*)*5];

		template<class T> function3(T* t,RT (T::*fn)(P1,P2,P3)) { clear(); bind(t,fn); }
		function3(RT (*fn)(P1,P2,P3)) { clear(); bind(fn); }

		function3() { clear(); }
		function3(const function3<RT,P1,P2,P3>& r) { memcpy(buf,r.buf,sizeof(buf)); m = (__method_3<RT,P1,P2,P3>*)buf; }
		function3<RT,P1,P2,P3>& operator=(const function3<RT,P1,P2,P3>& r) { memcpy(buf,r.buf,sizeof(buf)); m = (__method_3<RT,P1,P2,P3>*)buf; return *this; }
		bool operator==(const function3<RT,P1,P2,P3>& r) { return memcmp(r.buf,buf,sizeof(buf)) == 0; }

		inline bool valid() { return m != 0; }
		inline void clear() { m = 0; memset(buf,0,sizeof(buf)); }

		template<class T> void bind(T* t,RT (T::*fn)(P1,P2,P3))
		{
			size_t s = sizeof(object_method_3<T,RT,P1,P2,P3>);
			assert(s <= sizeof(buf));
			object_method_3<T,RT,P1,P2,P3>* r = (object_method_3<T,RT,P1,P2,P3>*)buf;
			new(r) object_method_3<T,RT,P1,P2,P3>();

			r->t = t;
			r->fn = fn;
			m = r;
		}

		void bind(RT (*fn)(P1,P2,P3))
		{
			size_t s = sizeof(static_method_3<RT,P1,P2,P3>);
			assert(s <= sizeof(buf));
			static_method_3<RT,P1,P2,P3>* r = (static_method_3<RT,P1,P2,P3>*)buf;
			new(r) static_method_3<RT,P1,P2,P3>();

			r->fn = fn;
			m = r;
		}

		RT operator()(P1 p1,P2 p2,P3 p3)
		{
			if(m == 0)
				return RT();
			return m->invoke(p1,p2,p3);
		}
	};

	template<class RT,class P1,class P2,class P3,class P4> struct function4
	{
		__method_4<RT,P1,P2,P3,P4>* m;
		char buf[sizeof(void*)*5];

		template<class T> function4(T* t,RT (T::*fn)(P1,P2,P3,P4)) { clear(); bind(t,fn); }
		function4(RT (*fn)(P1,P2,P3,P4)) { clear(); bind(fn); }

		function4() { clear(); }
		function4(const function4<RT,P1,P2,P3,P4>& r) { memcpy(buf,r.buf,sizeof(buf)); m = (__method_4<RT,P1,P2,P3,P4>*)buf; }
		function4<RT,P1,P2,P3,P4>& operator=(const function4<RT,P1,P2,P3,P4>& r) { memcpy(buf,r.buf,sizeof(buf)); m = (__method_4<RT,P1,P2,P3,P4>*)buf; return *this; }
		bool operator==(const function4<RT,P1,P2,P3,P4>& r) { return memcmp(r.buf,buf,sizeof(buf)) == 0; }

		inline bool valid() { return m != 0; }
		inline void clear() { m = 0; memset(buf,0,sizeof(buf)); }

		template<class T> void bind(T* t,RT (T::*fn)(P1,P2,P3,P4))
		{
			size_t s = sizeof(object_method_4<T,RT,P1,P2,P3,P4>);
			assert(s <= sizeof(buf));
			object_method_4<T,RT,P1,P2,P3,P4>* r = (object_method_4<T,RT,P1,P2,P3,P4>*)buf;
			new(r) object_method_4<T,RT,P1,P2,P3,P4>();

			r->t = t;
			r->fn = fn;
			m = r;
		}

		void bind(RT (*fn)(P1,P2,P3,P4))
		{
			size_t s = sizeof(static_method_4<RT,P1,P2,P3,P4>);
			assert(s <= sizeof(buf));
			static_method_4<RT,P1,P2,P3,P4>* r = (static_method_4<RT,P1,P2,P3,P4>*)buf;
			new(r) static_method_4<RT,P1,P2,P3,P4>();

			r->fn = fn;
			m = r;
		}

		RT operator()(P1 p1,P2 p2,P3 p3,P4 p4)
		{
			if(m == 0)
				return RT();
			return m->invoke(p1,p2,p3,p4);
		}
	};

	template<class RT,class P1,class P2,class P3,class P4,class P5> struct function5
	{
		__method_5<RT,P1,P2,P3,P4,P5>* m;
		char buf[sizeof(void*)*5];

		template<class T> function5(T* t,RT (T::*fn)(P1,P2,P3,P4,P5)) { clear(); bind(t,fn); }
		function5(RT (*fn)(P1,P2,P3,P4,P5)) { clear(); bind(fn); }

		function5() { clear(); }
		function5(const function5<RT,P1,P2,P3,P4,P5>& r) { memcpy(buf,r.buf,sizeof(buf)); m = (__method_5<RT,P1,P2,P3,P4,P5>*)buf; }
		function5<RT,P1,P2,P3,P4,P5>& operator=(const function5<RT,P1,P2,P3,P4,P5>& r) { memcpy(buf,r.buf,sizeof(buf)); m = (__method_5<RT,P1,P2,P3,P4,P5>*)buf; return *this; }
		bool operator==(const function5<RT,P1,P2,P3,P4,P5>& r) { return memcmp(r.buf,buf,sizeof(buf)) == 0; }

		inline bool valid() { return m != 0; }
		inline void clear() { m = 0; memset(buf,0,sizeof(buf)); }

		template<class T> void bind(T* t,RT (T::*fn)(P1,P2,P3,P4,P5))
		{
			size_t s = sizeof(object_method_5<T,RT,P1,P2,P3,P4,P5>);
			assert(s <= sizeof(buf));
			object_method_5<T,RT,P1,P2,P3,P4,P5>* r = (object_method_5<T,RT,P1,P2,P3,P4,P5>*)buf;
			new(r) object_method_5<T,RT,P1,P2,P3,P4,P5>();

			r->t = t;
			r->fn = fn;
			m = r;
		}

		void bind(RT (*fn)(P1,P2,P3,P4,P5))
		{
			size_t s = sizeof(static_method_5<RT,P1,P2,P3,P4,P5>);
			assert(s <= sizeof(buf));
			static_method_5<RT,P1,P2,P3,P4,P5>* r = (static_method_5<RT,P1,P2,P3,P4,P5>*)buf;
			new(r) static_method_5<RT,P1,P2,P3,P4,P5>();

			r->fn = fn;
			m = r;
		}

		RT operator()(P1 p1,P2 p2,P3 p3,P4 p4,P5 p5)
		{
			if(m == 0)
				return RT();
			return m->invoke(p1,p2,p3,p4,p5);
		}
	};
}


#endif // _pw_functional_
