#include <stdio.h>
#include "pw_time.h"
#include "pw_platform.h"
#include "pw_error_handler.h"
#include "pw_utils.h"
#include "pw_client_moniter.h"
#include "pw_client_logger.h"
#include "pw_logger.h"

#define MAX_THREADS 4

//��ȡ�ͻ��˷��͵�������Ϣ���Ҽ�¼��log

int main(int argc,char** argv)
{
	platform::init();
	pwutils::clientlog::InitClientLog();
	pwutils::logger::Initial("pwclientlog_");

#ifdef __linux
	pwngs::MySigHandler_Init();
#endif

	if(argc != 2)
	{
		printf("usage localport \n");
		return 1;
	}

	int localport = pwutils::atoi(argv[1]);
	printf("listen port = %d\n", localport);

	pwutils::ClientLogServerMultiThread* pThreads = new pwutils::ClientLogServerMultiThread(MAX_THREADS);
	if(pThreads->ListenAndServer(NULL,localport) != 0)
	{
		printf("bind on %d failed\n",localport);
		return 1;
	}

	//��ʱ��Ϊ��Ϸ�������˹رպ�ֹͣ�������Ҫһֱ��������Ϊwhile(1)
	while(!pwngs::gClosed)
	{
		pwutils::time::sleep(1);
	}

	pwutils::clientlog::ShutDownLog();
	platform::fini();
	return 0;
}