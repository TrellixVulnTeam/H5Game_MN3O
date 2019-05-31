#ifndef _pw_signal_
#define _pw_signal_

#include <deque>
#include <algorithm>
#include "pw_functional.h"

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

	signal0<int> s0;

	s0.connect(&testfn0);
	s0();
	s0.disconnect(&testfn0);

	s0 += &testfn0;
	s0();
	s0 -= &testfn0;

	s0.connect(&test,&Test::testfn0);
	s0();
	s0.disconnect(&test,&Test::testfn0);

	s0 += function0<int>(&test,&Test::testfn0);
	s0();
	s0 -= function0<int>(&test,&Test::testfn0);


	return 0;
}
*/

namespace pwutils
{
	template<class T> struct signal
	{
		std::deque<T> m_slots;

		template<class U,class F> void connect(U* u,F f)
		{
			connect(T(u,f));
		}

		template<class U,class F> void disconnect(U* u,F f)
		{
			disconnect(T(u,f));
		}

		void connect(const T& v)
		{
			m_slots.push_back(v);
		}

		bool disconnect(const T& v)
		{
			std::deque<T>::iterator iter = std::remove(m_slots.begin(),m_slots.end(),v);
			bool result = iter != m_slots.end();
			if(result)
				m_slots.erase(iter,m_slots.end());
			return result;
		}

		void operator+=(const T& v)
		{
			this->connect(v);
		}

		void operator-=(const T& v)
		{
			this->disconnect(v);
		}

		inline bool empty()
		{
			return m_slots.empty();
		}
	};

	template<class RT> struct signal0 : public signal< function0<RT> >
	{
		void operator()()
		{
			for(size_t i = 0; i < m_slots.size(); ++i)
				m_slots[i]();
		}
	};

	template<class RT,class P1> struct signal1 : public signal< function1<RT,P1> >
	{
		void operator()(P1 p1)
		{
			for(size_t i = 0; i < m_slots.size(); ++i)
				m_slots[i](p1);
		}
	};

	template<class RT,class P1,class P2> struct signal2 : public signal< function2<RT,P1,P2> >
	{
		void operator()(P1 p1,P2 p2)
		{
			for(size_t i = 0; i < m_slots.size(); ++i)
				m_slots[i](p1,p2);
		}
	};

	template<class RT,class P1,class P2,class P3> struct signal3 : public signal< function3<RT,P1,P2,P3> >
	{
		void operator()(P1 p1,P2 p2,P3 p3)
		{
			for(size_t i = 0; i < m_slots.size(); ++i)
				m_slots[i](p1,p2,p3);
		}
	};

	template<class RT,class P1,class P2,class P3,class P4> struct signal4 : public signal< function4<RT,P1,P2,P3,P4> >
	{
		void operator()(P1 p1,P2 p2,P3 p3,P4 p4)
		{
			for(size_t i = 0; i < m_slots.size(); ++i)
				m_slots[i](p1,p2,p3,p4);
		}
	};

	template<class RT,class P1,class P2,class P3,class P4,class P5> struct signal5 : public signal< function5<RT,P1,P2,P3,P4,P5> >
	{
		void operator()(P1 p1,P2 p2,P3 p3,P4 p4,P5 p45)
		{
			for(size_t i = 0; i < m_slots.size(); ++i)
				m_slots[i](p1,p2,p3,p4,p5);
		}
	};
}

#endif // _pw_signal_