#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <time.h>
#include <unistd.h>			//read
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>        /* Definition of uint64_t */
#include <errno.h>
#include "reactor.h"
#include "date_time.h"

using namespace boss;

#define MAX_EVENTS 500

CTimeHandler::CTimeHandler():
m_ui64Seconds(0),
m_ui64MilliSeconds(0)
{

}

CTimeHandler::~CTimeHandler()
{

}


int CTimeHandler::HandlerTimeout( uint64_t ui64Seconds, uint64_t ui64MilliSeconds )
{
	boss::util::CDateTime cDateTime( time(NULL) );
	printf( "%s\n", cDateTime.GetGMTDateTime().c_str() );

	return 0;
}

void CTimeHandler::SetSeconds( const uint64_t &ui64Seconds )
{
	m_ui64Seconds = ui64Seconds;
}

void CTimeHandler::setMilliSeconds(const uint64_t &ui64MilliSeconds)
{
	m_ui64MilliSeconds = ui64MilliSeconds;
}

uint64_t CTimeHandler::GetSeconds()
{
	return m_ui64Seconds;
}
uint64_t CTimeHandler::GetMilliSeconds()
{
	return m_ui64MilliSeconds;
}

CEpollReactor::CEpollReactor()
{
	m_setTimeHanlder.clear();
	m_mapTimerFd2Hander.clear();
}

CEpollReactor::~CEpollReactor()
{

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
int CEpollReactor::NonBlockRead( const int &iFd, const int64_t &i64BytesToRead, char *pszRecvBuff )
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
				perror( "read err" );
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

int CEpollReactor::RegisterTimerHandler( const uint64_t &ui64Seconds, const uint64_t &ui64MilliSeconds, CTimeHandler *pTimeHandler )
{
	pTimeHandler->SetSeconds(ui64Seconds);
	pTimeHandler->setMilliSeconds(ui64MilliSeconds);

	m_setTimeHanlder.insert(pTimeHandler);

	return 0;
}

int CEpollReactor::RunEventLoop()
{
	//创建epoll文件描述符
	int iEpfd = epoll_create1(0);
	if ( -1 == iEpfd )
	{
		perror( "epoll_create1 failed" );
		return -1;
	}

	//获取当前时间
	struct timespec timeNow;
	if ( -1 == clock_gettime( CLOCK_REALTIME, &timeNow ) )
	{
		perror( "clock_gettime err" );
		return -1;
	}

	//
	std::set<CTimeHandler *>::iterator itr = m_setTimeHanlder.begin();
	for ( ; itr != m_setTimeHanlder.end(); ++itr )
	{
		int iFd = timerfd_create( CLOCK_REALTIME, TFD_NONBLOCK/*0*/ );
		if ( -1 == iFd )
		{
			/* code */
			perror( "timerfd_create failed" );
			return -1;
		}
		m_mapTimerFd2Hander[iFd] = (*itr);

		struct itimerspec itimerNew;
		itimerNew.it_value.tv_sec = timeNow.tv_sec + 0;
		itimerNew.it_value.tv_nsec = timeNow.tv_nsec + 0;
		itimerNew.it_interval.tv_sec = (*itr)->GetSeconds();
		itimerNew.it_interval.tv_nsec = (*itr)->GetMilliSeconds()*1000;
		int iRet = timerfd_settime( iFd, TFD_TIMER_ABSTIME, &itimerNew, NULL );
		if ( -1 == iRet )
		{
			perror( "timerfd_settime" );
			return -1;
		}

		struct epoll_event event;
		event.data.fd = iFd;//监听非阻塞定时器fd
		event.events = EPOLLIN | EPOLLET;	//读事件，边缘触发方式(边缘触发方式，监听的fd需设定为非阻塞，否则事件到来时)
		iRet = epoll_ctl( iEpfd, EPOLL_CTL_ADD, iFd, &event );
		if ( -1 == iRet )
		{
			perror( "epoll_ctl failed" );
			return -1;
		}
	}


	struct epoll_event *pEvents = NULL;
	pEvents = (struct epoll_event *)calloc( MAX_EVENTS, sizeof(epoll_event) );
	if ( NULL == pEvents )
	{
		perror( "calloc err" );
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
			perror( "epoll_wait err" );
			break;
		}

		for ( int i = 0; i < iReadyFds; i++ )
		{
			if ( EPOLLIN == (pEvents[i].events & EPOLLIN) )//单定时器多任务调度会有阻塞问题，后一个任务必需等待前一个任务执行完才能执行,定时器只做任务触发，执行由线程池来执行?
			{
				i64ReadBytes = NonBlockRead( pEvents[i].data.fd, sizeof( uint64_t ), szRecvBuff );//返回的是上一次到这一次read期间发生的超时次数
				if ( sizeof( uint64_t ) != i64ReadBytes )
				{
					printf( "NonBlockRead failed, read size:%lld, expect size:%lu", i64ReadBytes, sizeof(uint64_t) );
					continue;
				}

				//
				if ( 0 == m_mapTimerFd2Hander.count(pEvents[i].data.fd) )
				{
					printf( "cann't find fd's handler\n" );
					continue;
				}
				CTimeHandler *pTimeHandler = m_mapTimerFd2Hander[pEvents[i].data.fd];
				pTimeHandler->HandlerTimeout( pTimeHandler->GetSeconds(), pTimeHandler->GetMilliSeconds() );
			}
			
		}
	}

	std::map<int, CTimeHandler *>::iterator mItr = m_mapTimerFd2Hander.begin();
	for ( ; mItr != m_mapTimerFd2Hander.end(); ++mItr )
	{
		close( mItr->first );
	}
	close( iEpfd );

	return 0;
}
