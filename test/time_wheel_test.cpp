//#include "tlog.h"
#include <stdio.h>
#include "time_wheel.h"


using namespace util::timer;

class CMyTimer : public CTimer
{
	public:
		CMyTimer( int secs, int milisecs, bool cycle );
		~CMyTimer();
		int HandlerTimeout(); 
};

CMyTimer::CMyTimer( int secs, int milisecs, bool cycle ):
CTimer( secs, milisecs, cycle )
{
	
}

CMyTimer::~CMyTimer()
{
	
}


int CMyTimer::HandlerTimeout() 
{ 
	printf( "CMyTimer HandlerTimeout!\n" ); 
	return 0;
}


int main()
{
	printf("aaa\n");
	CMyTimer cMyTimer( 10, 0, true );
	printf("bbb\n");
	CTimeWheel cTimeWheel( 1000, 1000, 0 );
	printf("CCC\n");

	cTimeWheel.AddTimer(&cMyTimer);
	printf("ddd\n");
	cTimeWheel.Dispatch();
	
	return 0;
}
