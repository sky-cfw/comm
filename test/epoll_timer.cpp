#include <stdio.h>
#include <stdlib.h>
#include "reactor.h"
#include "date_time.h"

using namespace boss;

class CTestTimeHandler : public CTimeHandler
{
public:
	CTestTimeHandler() {}
	~CTestTimeHandler() {}
	

};

class CTestTimeHandler1 : public CTimeHandler
{
public:
	CTestTimeHandler1() {}
	~CTestTimeHandler1(){}
	
	int HandlerTimeout( uint64_t ui64Seconds, uint64_t ui64MilliSeconds )
	{
		boss::util::CDateTime cDateTime( time(NULL) );
		printf( "CTestTimeHandler1: %s\n", cDateTime.GetGMTDateTime().c_str() );
		return 0;
	}

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
	CTestTimeHandler1 cTestTimeHandler1;
	CEpollReactor cReactor;

	cReactor.RegisterTimerHandler( iIntervalExprSeconds, iIntervalExprMilliSeconds, &cTestTimeHandler );
	cReactor.RegisterTimerHandler( 5, 0, &cTestTimeHandler1 );

	cReactor.RunEventLoop();

	return 0;
}