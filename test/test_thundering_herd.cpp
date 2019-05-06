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


int test_thunding_herd( const std::string &sHost, const uint16_t &ui16Port, const int &iProcNum )
{
	#define MAX_SOCKQUEUE_LEN 1024

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
    		for ( ; ; )
    		{
    			memset(&rCliAddr, 0, sizeof(rCliAddr));
    			iConnFd = accept( iSockFd, (struct sockaddr*) &rCliAddr, &nLenCliAddr );
    			if ( iConnFd < 0 )
		        {
		            if ( EINTR == errno )
		                continue;
		            else
		                return -1;
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
    		break;
    	}
    	printf("wait pid=%d succ\n", iRet);
    }

	return 0;
}


int main(int argc, char const *argv[])
{
	if ( argc < 2 )
	{
		printf( "./test_thunding_herd <1> proc_num\n" );
		return 0;
	}
	
	int iOption = atoi(argv[1]);
	if ( 1 == iOption )
	{
		if ( argc < 5 )
		{
			printf( "./test_thunding_herd <1> host port proc_num\n" );
			return 0;
		}
		std::string sHost = argv[2];
		uint16_t ui16Port = strtoul( argv[3], NULL, 10 );
		int iProcNum = atoi(argv[4]);
		test_thunding_herd( sHost, ui16Port, iProcNum );
	}

	return 0;
}
