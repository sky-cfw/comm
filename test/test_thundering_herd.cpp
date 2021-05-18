/**********************************************************************************************************
* Copyright:             Tech.co,Ltd. 2015-. All rights reserved
* File name:		     
* Description:		     
* Author:                sky
* Version:               V1.0
* Date:				     
* History:
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include "nonblockio.h"
#include "defs.h"

using namespace boss::container;
using namespace boss::comm;

/**********************************************************************************************************
* Function:
* Description:		    accept惊群测试
* Access Level:		
* Input:
* Output:
* Return:
* Others:
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
int TestAcceptThundingHerd( const std::string &sHost, const uint16_t &ui16Port, const int &iProcNum )
{
	int         iSockFd;
    int         nRetSetOpt;
    int         nRetBnd;
    int         nOne;
    struct  sockaddr_in rServaddr;
    pid_t       pid;

    memset(&rServaddr, 0, sizeof(rServaddr));
    rServaddr.sin_family = AF_INET;
    rServaddr.sin_port   = htons(ui16Port);

    if ( sHost.empty() )
    {
        rServaddr.sin_addr.s_addr = htonl(INADDR_ANY);	//	监听本机所有网卡(ip地址)上的port端口
    }
    else
    {
        rServaddr.sin_addr.s_addr = inet_addr(sHost.c_str());
    }
    if ( (iSockFd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )	//	创建套接字
    {
        return -1;
    }
    // if ( SetSockNonBlock(iSockFd) < 0 )						//	设置为非阻塞模式
    // {
    //     close(iSockFd);
    //     return -1;
    // }
    nOne = 1;
    if ( (nRetSetOpt = setsockopt(iSockFd, SOL_SOCKET, SO_REUSEADDR, (char *) & nOne, sizeof(nOne))) != 0 )	//	开启标志选项 - SO_REUSEADDR 这个套接字选项通知内核，如果端口忙，但TCP状态位于 TIME_WAIT ，可以重用端口。如果端口忙，而TCP状态位于其他状态，重用端口时依旧得到一个错误信息，指明"地址已经使用中"。如果你的服务程序停止后想立即重启，而新套接字依旧使用同一端口，此时SO_REUSEADDR 选项非常有用
    {
        close(iSockFd);
        return -1;
    }
    
    if ( (nRetBnd = bind(iSockFd, (struct sockaddr*) & rServaddr, sizeof(rServaddr))) < 0 )
    {
        close(iSockFd);
        return -1;
    }
    /*
    if ( listen(iSockFd, MAX_SOCKQUEUE_LEN) < 0 )		//	监听套接字连接队列大小  未完成连接队列(SYN_REVD状态) + 已完成连接队列(ESTABLISHED状态)
    {
        close(iSockFd);
        return -1;
    }
    */

    int             iConnFd;
    struct sockaddr_in rCliAddr;
    socklen_t       nLenCliAddr = sizeof(rCliAddr);
    char            szBuf[128] = {'\0'};
    for ( int i = 0; i < iProcNum; ++i )
    {
    	pid = fork();
    	if ( 0 == pid )
    	{
		    if ( listen(iSockFd, /*MAX_SOCKQUEUE_LEN*/1) < 0 )		//	监听套接字连接队列大小  未完成连接队列(SYN_REVD状态) + 已完成连接队列(ESTABLISHED状态)
		    {
		        close(iSockFd);
		        printf("listen failed, errmsg:%s\n", strerror(errno) );
		        return -1;
		    }

    		for ( ; ; )
    		{
    			
    			memset(&rCliAddr, 0, sizeof(rCliAddr));
    			iConnFd = accept( iSockFd, (struct sockaddr*) &rCliAddr, &nLenCliAddr );
    			if ( iConnFd < 0 )
		        {
		            if ( EINTR == errno )
		                continue;
		            else
		                break;
		        }
//		        for ( ; ; )
//		        {
//		        	read( iConnFd, szBuf, 1024 );
			        //snprintf(szBuf, sizeof(szBuf), "accept pid=%d\n", getpid());
//			        write( iConnFd, szBuf, strlen(szBuf)+1 );
//		        }
		        read( iConnFd, szBuf, 1024 );
		        //snprintf(szBuf, sizeof(szBuf), "accept pid=%d\n", getpid());
		        write( iConnFd, szBuf, strlen(szBuf)+1 );
		        //printf( "accept pid=%d, buflen=%lu\n", getpid(), strlen(szBuf)+1 );
		        close(iConnFd);
		        //sleep(1000000);//测试
    		}
    	}
    }

    //回收所有子进程
    int iRet = 0;
    for ( ; ; )
    {
    	iRet = wait( NULL );//阻塞等待回收
    	if ( -1 == iRet )
    	{
    		if ( EINTR == errno )//被信号中断
    		{
    			continue;
    		}
    		//没有子进程了
			printf("no child to wait, break\n");
    		break;
    	}
    	printf("wait pid=%d succ\n", iRet);
    }

	return 0;
}

/**********************************************************************************************************
* Function:
* Description:		    测试epoll惊群
* Access Level:		
* Input:
* Output:
* Return:
* Others:
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
int TestEpollThundingHerd( const std::string &sHost, const uint16_t &ui16Port, const int &iProcNum )
{
	#define MAX_EVENTS 500

	int iListenFd = NonBlockTcpListen( sHost.c_str(), ui16Port );
	if ( iListenFd < 0 )
	{
		return FAILED;
	}

	int iEpollFd = epoll_create( 4096 );//---创建指向epoll实例的文件描述符(监听队列大小4096),2.6.8内核以上版本此参数不在使用
    if ( iEpollFd < 0 )
    {
        printf("epoll_create err [%d]",iEpollFd);
        return -1;
    }

    struct  epoll_event stEpollEvent;
    memset(&stEpollEvent,0x0,sizeof(stEpollEvent));
    stEpollEvent.data.fd = iListenFd;
    stEpollEvent.events   = EPOLLIN | EPOLLERR | EPOLLET;//---Error  condition  happened  on  the  associated  file descriptor.  epoll_wait(2) will always wait for this event; it is not necessary to set it in events.
    //stEpollEvent.events   = EPOLLIN | EPOLLERR | EPOLLEXCLUSIVE;//---Error  condition  happened  on  the  associated  file descriptor.  epoll_wait(2) will always wait for this event; it is not necessary to set it in events.
    epoll_ctl ( iEpollFd, EPOLL_CTL_ADD, iListenFd, &stEpollEvent );

    struct epoll_event *pEvents = NULL;
	pEvents = (struct epoll_event *)calloc( MAX_EVENTS, sizeof(epoll_event) );
	if ( NULL == pEvents )
	{
		printf( "calloc err" );
		return -1;
	}

	int iReadyFds = 0, iConnFd = 0;
	pid_t pid = 0;
	struct sockaddr_in rCliAddr;
    socklen_t       nLenCliAddr = sizeof(rCliAddr);
	for ( int i = 0; i < iProcNum; ++i )
	{
		pid = fork();
		if ( 0 == pid )
		{
			for ( ; ; )
			{
				iReadyFds = epoll_wait( iEpollFd, pEvents, MAX_EVENTS, -1 );
				if ( -1 == iReadyFds && errno == EINTR )
				{
					printf( "epoll_wait err" );
					continue;
				}

				for ( int i = 0; i < iReadyFds; i++ )
				{
					if ( EPOLLIN == (pEvents[i].events & EPOLLIN)
					&& iListenFd == pEvents[i].data.fd )//客户端连接到来
					{
						//printf( "epoll_wait pid=%d\n", getpid() );
						memset(&rCliAddr, 0, sizeof(rCliAddr));
		    			iConnFd = accept( iListenFd, (struct sockaddr*) &rCliAddr, &nLenCliAddr );
		    			if ( iConnFd < 0 )
				        {
				            if ( EINTR == errno || EAGAIN == errno )
				            {
				                continue;
				            }
				            else
				            {
				                return -1;
				            }
				        }
				        //printf( "accept pid=%d\n", getpid() );
		        		close(iConnFd);
					}
					
				}
			}
		}
	}
	

	//回收所有子进程
    int iRet = 0;
    for ( ; ; )
    {
    	iRet = wait( NULL );//阻塞等待回收
    	if ( -1 == iRet )
    	{
    		if ( EINTR == errno )//被信号中断
    		{
    			continue;
    		}
    		//没有子进程了
    		break;
    	}
    	printf("wait pid=%d succ\n", iRet);
    }

	return SUCCESS;
}

/**********************************************************************************************************
* Function:
* Description:		    测试epoll惊群2
* Access Level:		
* Input:
* Output:
* Return:
* Others:
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
int TestEpollThundingHerd2( const std::string &sHost, const uint16_t &ui16Port, const int &iProcNum )
{
	#define MAX_EVENTS 500

	int iListenFd = NonBlockTcpListen( sHost.c_str(), ui16Port );
	if ( iListenFd < 0 )
	{
		return FAILED;
	}

	

	int iReadyFds = 0, iConnFd = 0;
	pid_t pid = 0;
	struct sockaddr_in rCliAddr;
    socklen_t       nLenCliAddr = sizeof(rCliAddr);
	for ( int i = 0; i < iProcNum; ++i )
	{
		pid = fork();
		if ( 0 == pid )
		{
			int iEpollFd = epoll_create( 4096 );//---创建指向epoll实例的文件描述符(监听队列大小4096),2.6.8内核以上版本此参数不在使用
			if ( iEpollFd < 0 )
			{
				printf("epoll_create err [%d]",iEpollFd);
				return -1;
			}

			struct  epoll_event stEpollEvent;
			memset(&stEpollEvent,0x0,sizeof(stEpollEvent));
			stEpollEvent.data.fd = iListenFd;
			//stEpollEvent.events   = EPOLLIN | EPOLLERR;//---Error  condition  happened  on  the  associated  file descriptor.  epoll_wait(2) will always wait for this event; it is not necessary to set it in events.
			stEpollEvent.events   = EPOLLIN | EPOLLERR | EPOLLEXCLUSIVE;//---Error  condition  happened  on  the  associated  file descriptor.  epoll_wait(2) will always wait for this event; it is not necessary to set it in events.
			epoll_ctl ( iEpollFd, EPOLL_CTL_ADD, iListenFd, &stEpollEvent );

			struct epoll_event *pEvents = NULL;
			pEvents = (struct epoll_event *)calloc( MAX_EVENTS, sizeof(epoll_event) );
			if ( NULL == pEvents )
			{
				printf( "calloc err" );
				return -1;
			}
			
			for ( ; ; )
			{
				iReadyFds = epoll_wait( iEpollFd, pEvents, MAX_EVENTS, -1 );
				if ( -1 == iReadyFds && errno == EINTR )
				{
					printf( "epoll_wait err" );
					continue;
				}

				for ( int i = 0; i < iReadyFds; i++ )
				{
					if ( EPOLLIN == (pEvents[i].events & EPOLLIN)
					&& iListenFd == pEvents[i].data.fd )//客户端连接到来
					{
						//printf( "epoll_wait pid=%d\n", getpid() );
						memset(&rCliAddr, 0, sizeof(rCliAddr));
		    			iConnFd = accept( iListenFd, (struct sockaddr*) &rCliAddr, &nLenCliAddr );
		    			if ( iConnFd < 0 )
				        {
				            if ( EINTR == errno || EAGAIN == errno )
				            {
				                continue;
				            }
				            else
				            {
				                return -1;
				            }
				        }
				        //printf( "accept pid=%d\n", getpid() );
		        		close(iConnFd);
					}
					
				}
			}
		}
	}
	

	//回收所有子进程
    int iRet = 0;
    for ( ; ; )
    {
    	iRet = wait( NULL );//阻塞等待回收
    	if ( -1 == iRet )
    	{
    		if ( EINTR == errno )//被信号中断
    		{
    			continue;
    		}
    		//没有子进程了
    		break;
    	}
    	printf("wait pid=%d succ\n", iRet);
    }

	return SUCCESS;
}
int main(int argc, char const *argv[])
{
	if ( argc < 5 )
	{
		printf( "AcceptThundingHerd Usage: ./test_thundering_herd <1> host port proc_num\n" );
		printf( "EpollThundingHerd1 Usage: ./test_thundering_herd <2> host port proc_num\n" );
		printf( "EpollThundingHerd2 Usage: ./test_thundering_herd <3> host port proc_num\n" );
		return 0;
	}
	
	int iOption = atoi(argv[1]);
	std::string sHost = argv[2];
	uint16_t ui16Port = strtoul( argv[3], NULL, 10 );
	int iProcNum = atoi(argv[4]);
	
	if ( 1 == iOption )
	{
		TestAcceptThundingHerd( sHost, ui16Port, iProcNum );
	}
	else if ( 2 == iOption )
	{
		TestEpollThundingHerd( sHost, ui16Port, iProcNum );
	}
	else if ( 3 == iOption )
	{
		TestEpollThundingHerd2( sHost, ui16Port, iProcNum );
	}

	return 0;
}
