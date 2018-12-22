#include <sys/timerfd.h>
#include <time.h>
#include <unistd.h>			//read
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>        /* Definition of uint64_t */
#include "date_time.h"


#define HandlerErr( szErrmsg )\
{\
	perror( szErrmsg );\
	return -1;\
}


int main(int argc, char const *argv[])
{
	if ( 4 != argc )
	{
		printf( "./epoll_timer <init_expr> <interval_expr> <repeat_num>\n");
		return -1;
	}

	int iInitExprTime = atoi( argv[1] );//	初始超时时间(ms)
	int iIntervalExprTime = atoi( argv[2] );// 周期超时时间
	int iRepeatNum = atoi(argv[3]); //	重复执行次数

	//获取当前时间
	struct timespec timeNow;
	if ( -1 == clock_gettime( CLOCK_REALTIME, &timeNow ) )
	{
		HandlerErr( "clock_gettime err" );
		return -1;
	}

	//	非阻塞定时器文件描述符
	int iFd = timerfd_create( CLOCK_REALTIME, /*TFD_NONBLOCK*/0 );
	if ( -1 == iFd )
	{
		/* code */
		HandlerErr( "timerfd_create failed" );
		return -1;
	}

	struct itimerspec itimerNew;
	itimerNew.it_value.tv_sec = timeNow.tv_sec + (iInitExprTime/1000);
	itimerNew.it_value.tv_nsec = timeNow.tv_nsec + (iInitExprTime%1000)*1000;
	itimerNew.it_interval.tv_sec = (iIntervalExprTime/1000);
	itimerNew.it_interval.tv_nsec = (iIntervalExprTime%1000)*1000;
	int iRet = timerfd_settime( iFd, TFD_TIMER_ABSTIME, &itimerNew, NULL );
	if ( -1 == iRet )
	{
		HandlerErr( "timerfd_settime" );
		return -1;
	}

	boss::util::CDateTime cDateTime;
	uint64_t ui64Buff = 0;
	ssize_t llen = 0;
	for ( int i = 0; i < iRepeatNum; ++i )
	{
		llen = read( iFd, &ui64Buff, sizeof(uint64_t) );
		if ( sizeof(uint64_t) != llen )
		{
			HandlerErr("read err");
			return -1;
		}

		cDateTime.SetSeconds( time(NULL) );
		printf( "%s\n", cDateTime.GetGMTDateTime().c_str() );
	}

	return 0;
}
