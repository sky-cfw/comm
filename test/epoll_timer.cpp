#include <stdio.h>
#include <stdlib.h>
//#include "/home/sky/comm/utils/reactor.h"
#include "reactor.h"

using namespace boss;

class CTestTimeHandler : public CTimeHandler
{
public:
	CTestTimeHandler() {}
	~CTestTimeHandler() {}
	

};

int main(int argc, char const *argv[])
{
	if ( 3 != argc )
	{
		printf( "./epoll_timer <interval_expr_s> <interval_expr_ms>\n");
		return -1;
	}

	int iIntervalExprSeconds = atoi( argv[1] );// 周期超时时间
	int iIntervalExprMilliSeconds = atoi(argv[2]); //

	CTestTimeHandler cTestTimeHandler;
	CEpollReactor cReactor;

	cReactor.RegisterTimerHandler( iIntervalExprSeconds, iIntervalExprMilliSeconds, &cTestTimeHandler );
	cReactor.RunEventLoop();

	return 0;
}
