#include <stdio.h>
#include "pw_def.h"
#include "pwdist_node.h"
#include "pwdist_port_generic.h"
#include "pwdist_node_runner.h"
#include "pw_logger.h"
#include "ace/OS_NS_unistd.h"
#include "pwdist_port_scripted.h"

extern void test_main();

volatile bool g_closed = false;
#ifndef _DEBUG
	pwdist::sint64  g_test_count = 1000000;
#else
	pwdist::sint64  g_test_count = 10000;
#endif
hrtime_t g_begin = ACE_OS::gethrtime();

#include "pw_memory.inl"


// 测试端口1
class CTestPort1 : public pwdist::PortEx
{
public:
	CTestPort1()
	{
// 		if(LoadScriptSupport("./Lua/pwdist.lua") != 0)
// 		{
// 			printf(lua_tostring(L,-1));
// 			return ;
// 		}

		this->initial();
	}

	void initial()
	{
		Impl<CTestPort1>("test1",&CTestPort1::test1);
	}
	
	void test1(pwdist::sint64 val,pwdist::Chunk buf)
	{
		if(val == g_test_count)
		{
			hrtime_t nn = pwutils::time::diff_ms(ACE_OS::gethrtime(),g_begin);

			std::cout << "finished:" << nn << "ms/" << g_test_count << std::endl;
			std::cout << double(nn)/g_test_count << " ms/per_call" << std::endl;
			g_closed = true;
		}
	}
	
};

// 测试端口2
class CTestPort2 : public pwdist::PortEx
{
public:
	CTestPort2()
	{
// 		if(LoadScriptSupport("./Lua/pwdist.lua") != 0)
// 		{
// 			printf(lua_tostring(L,-1));
// 			return ;
// 		}

		this->initial();
	}

	void initial()
	{
		Impl<CTestPort2>("test2",&CTestPort2::test);
	}
	
	void test(pwdist::sint64 result)
	{
		g_begin = ACE_OS::gethrtime();

		sint64 spec[] = { 0LL, };
		for(pwdist::sint64 i = 0; i <= result; ++i)
		{
			this->Prepare("node1","port1",spec,sizeof(spec)/sizeof(spec[0]));
			this->Call(this,"test1",i,pwdist::Chunk(NULL,0));
		}

		hrtime_t nn = pwutils::time::diff_ms(ACE_OS::gethrtime(),g_begin);

		std::cout << "send call done:" << nn << "ms/" << g_test_count << std::endl;

	}
};

// -------------------------------------------------------------------

void test1(pwdist::PortBase* port,void* context)
{
	CTestPort2* port2 = (CTestPort2*)port;
	port2->test(g_test_count);
}

// -------------------------------------------------------------------

void test()
{
	printf("111111111111\r\n");
}

#include <pthread.h>

int main(int argc, char **argv)
{
	pthread_spinlock_t t;
	pthread_spin_init(&t,0);
	pthread_spin_lock(&t);
	pthread_spin_unlock(&t);
	
	//test_main();

	
	
	ACE::init();
	pwutils::logger::Initial("pwdist_");

	pwdist::Node node1;
	pwdist::Node node2;
	CTestPort1 port1;
	CTestPort2 port2;

	PWCHECKF(node1.Startup("../pwdist/configure1.xml") == 0);
	PWCHECKF(node2.Startup("../pwdist/configure2.xml") == 0);

	pwdist::NodeRunner runner1(&node1);
	pwdist::NodeRunner runner2(&node2);;

	node1.Ping("node2","tcp://127.0.0.1:8801");
	node2.Ping("node1","tcp://127.0.0.1:8800");

	runner1.Startup(1);
	runner2.Startup(1);

	port1.Startup("port1",&node1);
	port2.Startup("port2",&node2);

	while(!node2.IsRemoteActive("node1"))
	{
		ACE_OS::sleep(ACE_Time_Value(1,0));
	}

	std::cout << "node actived" << std::endl;

	port2.PostProc(&test1,nullptr);

	while(!g_closed)
	{
// 		char i;
// 		std::cin >> i;
// 		if(i == 'q')
// 			break;
		ACE_OS::sleep(ACE_Time_Value(0,1000));
	}

	runner1.Cleanup();
	runner2.Cleanup();
	port1.Cleanup();
	port2.Cleanup();
	node1.Cleanup();
	node2.Cleanup();

	pwutils::logger::ShutDown();
	ACE::fini();

#ifdef _WIN32
	printf("g_ref_count = %d\r\n",pwutils::g_ref_count);
#endif
	return 0;
}
