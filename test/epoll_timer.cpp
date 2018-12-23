#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <time.h>
#include <unistd.h>			//read
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>        /* Definition of uint64_t */
#include <errno.h>
#include "date_time.h"


#define MAX_EVENTS 500

#define HandlerErr( szErrmsg )\
{\
	perror( szErrmsg );\
	return -1;\
}

/**********************************************************************************************************
* Function:
* Description:		    非阻塞读
* Access Level:		
* Input:
* Output:
* Return:				< 0 exception
						= 0 end-of-file
						> 0 读取的字节数
* Others:
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
int NonBlockRead( const int &iFd, const int64_t &i64BytesToRead, char *pszRecvBuff )
{
	int64_t i64Left = i64BytesToRead;//剩余待读字节数
	int64_t i64OneRead = 0;//本次read读取的字节数

	while ( i64Left > 0 )
	{
		i64OneRead = read( iFd, pszRecvBuff, i64BytesToRead );
		if ( i64OneRead < 0 )
		{
			if ( EAGAIN == errno )
			{
				printf( "read finished\n" );
				break;
			}
			else if ( EINTR == errno )//被信号中断了
			{
				i64OneRead = 0;
				printf( "interrupted by a signal" );
				continue;
			}
			else
			{
				HandlerErr( "read err" );
				return -1;
			}
		}
		
		if ( 0 == i64OneRead )
		{
			printf( "hit epoll, but read returns 0\n" );
			return -1;
		}

		i64Left -= i64OneRead;
	}

	return (i64BytesToRead-i64Left);
}

/**********************************************************************************************************
* Function:
* Description:		    
* Access Level:		
* Input:
* Output:
* Return:
* Others:
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
int HandlerTimeout( int iExprSeconds, int iExprMilliSeconds )
{
	boss::util::CDateTime cDateTime( time(NULL) );
	printf( "%s\n", cDateTime.GetGMTDateTime().c_str() );

	return 0;
}

int main(int argc, char const *argv[])
{
	if ( 4 != argc )
	{
		printf( "./epoll_timer <init_expr_ms> <interval_expr_ms> <repeat_num_ms>\n");
		return -1;
	}

	int iInitExprTime = atoi( argv[1] );//	初始超时时间(ms)
	int iIntervalExprTime = atoi( argv[2] );// 周期超时时间
	int iRepeatNum = atoi(argv[3]); //	执行次数

	//获取当前时间
	struct timespec timeNow;
	if ( -1 == clock_gettime( CLOCK_REALTIME, &timeNow ) )
	{
		HandlerErr( "clock_gettime err" );
		return -1;
	}

	//	非阻塞定时器文件描述符
	int iFd = timerfd_create( CLOCK_REALTIME, TFD_NONBLOCK/*0*/ );
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

	//	创建epoll文件描述符
	int iEpfd = epoll_create1(0);
	if ( -1 == iEpfd )
	{
		HandlerErr( "epoll_create1 failed" );
		return -1;
	}

	//	
	struct epoll_event event;
	event.data.fd = iFd;//监听非阻塞定时器fd
	event.events = EPOLLIN | EPOLLET;	//读事件，边缘触发方式(边缘触发方式，监听的fd需设定为非阻塞，否则事件到来时)
	iRet = epoll_ctl( iEpfd, EPOLL_CTL_ADD, iFd, &event );
	if ( -1 == iRet )
	{
		HandlerErr( "epoll_ctl failed" );
		return -1;
	}

	struct epoll_event *pEvents = NULL;
	pEvents = (struct epoll_event *)calloc( MAX_EVENTS, sizeof(epoll_event) );
	if ( NULL == pEvents )
	{
		HandlerErr( "calloc err" );
		return -1;
	}

	int iReadyFds = 0;
	char szRecvBuff[sizeof(uint64_t)] = {'\0'};
	int64_t i64ReadBytes = 0;
	for ( ; ; )
	{
		iReadyFds = epoll_wait( iEpfd, pEvents, MAX_EVENTS, -1 );//阻塞等待事件到来
		if ( -1 == iReadyFds )
		{
			HandlerErr( "epoll_wait err" );
			break;
		}

		for ( int i = 0; i < iReadyFds; i++ )
		{
			if ( iFd == pEvents[i].data.fd )
			{
				if ( EPOLLIN == (pEvents[i].events & EPOLLIN) )
				{
					i64ReadBytes = NonBlockRead( pEvents[i].data.fd, sizeof( uint64_t ), szRecvBuff );
					if ( sizeof( uint64_t ) != i64ReadBytes )
					{
						printf( "NonBlockRead failed, read size:%lld, expect size:%lu", i64ReadBytes, sizeof(uint64_t) );
						continue;
					}

					//
					HandlerTimeout( iIntervalExprTime/1000, iIntervalExprTime%1000 );
				}
			}
			else
			{
				//
				printf( "unrecognized fd\n" );
			}
		}
	}

	close( iFd );
	close( iEpfd );

	return 0;
}