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

// #define	SO_DEBUG	0x0001		/* turn on debugging info recording */
// #define	SO_ACCEPTCONN	0x0002		/* socket has had listen() */
// #define	SO_REUSEADDR	0x0004		/* allow local address reuse */
// #define	SO_KEEPALIVE	0x0008		/* keep connections alive */
// #define	SO_DONTROUTE	0x0010		/* just use interface addresses */
// #define	SO_BROADCAST	0x0020		/* permit sending of broadcast msgs */
// #if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
// #define	SO_USELOOPBACK	0x0040		/* bypass hardware when possible */
// #define	SO_LINGER	0x0080		/* linger on close if data present (in ticks) */
// #else
// #define	SO_LINGER	0x1080		/* linger on close if data present (in seconds) */
// #endif	/* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */
// #define	SO_OOBINLINE	0x0100		/* leave received OOB data in line */
// #if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
// #define	SO_REUSEPORT	0x0200		/* allow local address & port reuse */
// #define	SO_TIMESTAMP	0x0400		/* timestamp received dgram traffic */
// #define	SO_TIMESTAMP_MONOTONIC	0x0800	/* Monotonically increasing timestamp on rcvd dgram */
// #ifndef __APPLE__
// #define	SO_ACCEPTFILTER	0x1000		/* there is an accept filter */
// #else
// #define	SO_DONTTRUNC	0x2000		/* APPLE: Retain unread data */
// 					/*  (ATOMIC proto) */
// #define	SO_WANTMORE	0x4000		/* APPLE: Give hint when more data ready */
// #define	SO_WANTOOBFLAG	0x8000		/* APPLE: Want OOB in MSG_FLAG on receive */


// #endif  /* (!__APPLE__) */
// #endif	/* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */

// /*
//  * Additional options, not kept in so_options.
//  */
// #define	SO_SNDBUF	0x1001		/* send buffer size */
// #define	SO_RCVBUF	0x1002		/* receive buffer size */
// #define	SO_SNDLOWAT	0x1003		/* send low-water mark */
// #define	SO_RCVLOWAT	0x1004		/* receive low-water mark */
// #define	SO_SNDTIMEO	0x1005		/* send timeout */
// #define	SO_RCVTIMEO	0x1006		/* receive timeout */
// #define	SO_ERROR	0x1007		/* get error status and clear */
// #define	SO_TYPE		0x1008		/* get socket type */
// #if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
// #define	SO_LABEL	0x1010		/* socket's MAC label */
// #define	SO_PEERLABEL    0x1011		/* socket's peer MAC label */
// #ifdef __APPLE__
// #define	SO_NREAD	0x1020		/* APPLE: get 1st-packet byte count */
// #define	SO_NKE		0x1021		/* APPLE: Install socket-level NKE */
// #define	SO_NOSIGPIPE	0x1022		/* APPLE: No SIGPIPE on EPIPE */
// #define	SO_NOADDRERR	0x1023		/* APPLE: Returns EADDRNOTAVAIL when src is not available anymore */
// #define	SO_NWRITE	0x1024		/* APPLE: Get number of bytes currently in send socket buffer */
// #define	SO_REUSESHAREUID	0x1025		/* APPLE: Allow reuse of port/socket by different userids */
// #ifdef __APPLE_API_PRIVATE
// #define	SO_NOTIFYCONFLICT	0x1026	/* APPLE: send notification if there is a bind on a port which is already in use */
// #define	SO_UPCALLCLOSEWAIT	0x1027	/* APPLE: block on close until an upcall returns */
// #endif
// #define	SO_LINGER_SEC	0x1080		/* linger on close if data present (in seconds) */
// #define	SO_RANDOMPORT   0x1082  /* APPLE: request local port randomization */
// #define	SO_NP_EXTENSIONS	0x1083	/* To turn off some POSIX behavior */
// #endif

// #define	SO_NUMRCVPKT		0x1112	/* number of datagrams in receive socket buffer */

static int gsDictSockopt[5] = {0x0000,SO_REUSEADDR,SO_REUSEPORT,SO_KEEPALIVE,SO_LINGER};

/**********************************************************************************************************
* Function:
* Description:		    测试套接字功能选项参数 - 
* Access Level:		
* Input:
* Output:
* Return:
* Others:
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
int TestSetSockOpt( const int &iSockOpt, const std::string &sHost, const uint16_t &ui16Port, const int &iProcNum )
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
    	printf("create socket failed, errmsg:%s\n", strerror(errno) );
        return -1;
    }
    // if ( SetSockNonBlock(iSockFd) < 0 )						//	设置为非阻塞模式
    // {
    //     close(iSockFd);
    //     return -1;
    // }
    if ( 0 != iSockOpt )
    {
    	nOne = 1;
	    if ( (nRetSetOpt = setsockopt(iSockFd, SOL_SOCKET, iSockOpt, (char *) & nOne, sizeof(nOne))) != 0 )	//	开启标志选项 - SO_REUSEADDR 这个套接字选项通知内核，如果端口忙，但TCP状态位于 TIME_WAIT ，可以重用端口。如果端口忙，而TCP状态位于其他状态，重用端口时依旧得到一个错误信息，指明"地址已经使用中"。如果你的服务程序停止后想立即重启，而新套接字依旧使用同一端口，此时SO_REUSEADDR 选项非常有用
	    {
	    	printf("setsockopt failed, errmsg:%s\n", strerror(errno) );
	        close(iSockFd);
	        return -1;
	    }
    }
    /*
    if ( (nRetBnd = bind(iSockFd, (struct sockaddr*) & rServaddr, sizeof(rServaddr))) < 0 )
    {
    	printf("bind failed, errmsg:%s\n", strerror(errno) );
        close(iSockFd);
        return -1;
    }
    
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
    		if ( (nRetBnd = bind(iSockFd, (struct sockaddr*) & rServaddr, sizeof(rServaddr))) < 0 )
		    {
		    	printf("bind failed, errmsg:%s\n", strerror(errno) );
		        close(iSockFd);
		        return -1;
		    }
    		
		    if ( listen(iSockFd, MAX_SOCKQUEUE_LEN) < 0 )		//	监听套接字连接队列大小  未完成连接队列(SYN_REVD状态) + 已完成连接队列(ESTABLISHED状态)
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
		        snprintf(szBuf, sizeof(szBuf), "accept pid=%d\n", getpid());
		        write( iConnFd, szBuf, strlen(szBuf)+1 );
		        printf( "accept pid=%d, buflen=%lu\n", getpid(), strlen(szBuf)+1 );
		        close(iConnFd);
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
* Description:		    测试套接字功能选项参数 - 
* Access Level:		
* Input:
* Output:
* Return:
* Others:
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
int TestSetSockOpt_2( const int &iSockOpt, const std::string &sHost, const uint16_t &ui16Port, const int &iProcNum )
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
    	printf("create socket failed, errmsg:%s\n", strerror(errno) );
        return -1;
    }
    // if ( SetSockNonBlock(iSockFd) < 0 )						//	设置为非阻塞模式
    // {
    //     close(iSockFd);
    //     return -1;
    // }
    if ( 0 != iSockOpt )
    {
    	nOne = 1;
	    if ( (nRetSetOpt = setsockopt(iSockFd, SOL_SOCKET, iSockOpt, (char *) & nOne, sizeof(nOne))) != 0 )	//	开启标志选项 - SO_REUSEADDR 这个套接字选项通知内核，如果端口忙，但TCP状态位于 TIME_WAIT ，可以重用端口。如果端口忙，而TCP状态位于其他状态，重用端口时依旧得到一个错误信息，指明"地址已经使用中"。如果你的服务程序停止后想立即重启，而新套接字依旧使用同一端口，此时SO_REUSEADDR 选项非常有用
	    {
	    	printf("setsockopt failed, errmsg:%s\n", strerror(errno) );
	        close(iSockFd);
	        return -1;
	    }
    }
    
    if ( (nRetBnd = bind(iSockFd, (struct sockaddr*) & rServaddr, sizeof(rServaddr))) < 0 )
    {
    	printf("bind failed, errmsg:%s\n", strerror(errno) );
        close(iSockFd);
        return -1;
    }
    
    if ( listen(iSockFd, MAX_SOCKQUEUE_LEN) < 0 )		//	监听套接字连接队列大小  未完成连接队列(SYN_REVD状态) + 已完成连接队列(ESTABLISHED状态)
    {
        close(iSockFd);
        return -1;
    }
    

    int             iConnFd;
    struct sockaddr_in rCliAddr;
    socklen_t       nLenCliAddr = sizeof(rCliAddr);
    char            szBuf[128] = {'\0'};
    for ( int i = 0; i < iProcNum; ++i )
    {
    	pid = fork();
    	if ( 0 == pid )
    	{
    		if ( (nRetBnd = bind(iSockFd, (struct sockaddr*) & rServaddr, sizeof(rServaddr))) < 0 )
		    {
		    	printf("bind failed, errmsg:%s\n", strerror(errno) );
		        close(iSockFd);
		        return -1;
		    }
    		
		    if ( listen(iSockFd, MAX_SOCKQUEUE_LEN) < 0 )		//	监听套接字连接队列大小  未完成连接队列(SYN_REVD状态) + 已完成连接队列(ESTABLISHED状态)
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
		        snprintf(szBuf, sizeof(szBuf), "accept pid=%d\n", getpid());
		        write( iConnFd, szBuf, strlen(szBuf)+1 );
		        printf( "accept pid=%d, buflen=%lu\n", getpid(), strlen(szBuf)+1 );
		        close(iConnFd);
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


int main(int argc, char const *argv[])
{
	if ( argc < 6 )
	{
		printf( "./TestSetSockOpt <1> opt host port proc_num\n" );
		printf( "opt desc: 0:DEF 1:SO_REUSEADDR 2:SO_REUSEPORT 3:SO_KEEPALIVE 4:SO_LINGER\n" );
		return 0;
	}
	
	int iOption = atoi( argv[1] );
	if ( 1 == iOption )
	{
		if ( argc < 6 )
		{
			printf( "./TestSetSockOpt <1> opt host port proc_num\n" );
			printf( "opt desc: 0:DEF 1:SO_REUSEADDR 2:SO_REUSEPORT 3:SO_KEEPALIVE 4:SO_LINGER\n" );
			return 0;
		}
		int iSockOpt = gsDictSockopt[atoi( argv[2] )];
		std::string sHost = argv[3];
		uint16_t ui16Port = strtoul( argv[4], NULL, 10 );
		int iProcNum = atoi( argv[5] );
		printf("iSockOpt:%04x, SO_REUSEADDR:%04x, host:%s, port:%hu, proc_num:%d\n", iSockOpt, SO_REUSEADDR, sHost.c_str(), ui16Port, iProcNum);
		TestSetSockOpt( iSockOpt, sHost, ui16Port, iProcNum );
	}
	else if ( 2 == iOption )
	{
		
	}

	return 0;
}