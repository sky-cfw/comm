/**********************************************************************************************************
 * * Copyright:             Tech.co,Ltd. 2015-. All rights reserved
 * * File name:             
 * * Description:             
 * * Author:                
 * * Version:               V1.0
 * * Date:                     
 * * History:
 *                          1. Date:          2. Author:         3. Modification:
 ***********************************************************************************************************/
#ifndef		__NONBLOCK_TCP_H
#define		__NONBLOCK_TCP_H

#include	<stdio.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<arpa/inet.h>
#include	<sys/un.h>
#include	<netdb.h>
#include	<errno.h>
#include	<string.h>

#define		MAX_SOCKQUEUE_LEN		4096
#define		SOCK_SEGMENT_LEN		4096

namespace boss
{
    namespace container
    {
        //套接字设置为非阻塞模式
        int     SetSockNonBlock(int );
        //非阻塞tcp监听
        int     NonBlockTcpListen(const char *,int);
        //非阻塞tcp accept
        int     NonBlockTcpAccept(int ,char* ,int *);
        //非阻塞tcp连接
        int     NonBlockTcpConnect(const char *,int);
        //非阻塞tcp 读取
        int     NonBlockTcpRead(int ,char *,int );
        //非阻塞tcp 写入
        int     NonBlockTcpWrite(int,char *,int);
        //检查传入参数是否为ip地址
        int     IsIPAddr(const char *);
        //非阻塞unix 套接字监听
        int     NonBlockUnixSockListen(const char *);
        //unix 套接字accept
        int     NonBlockUnixAccept(int);
        //unix 套接字连接
        int     NonBlockUnixRead(int ,char *,int );

        int     NonBlockUnixWrite(int,char *,int);

        int     LocalUnixConn(const char *sUnixSockFile);

        int     NonBlockUdpListen(const char *ip,unsigned short usPort);

        int     NonBlockUdpRead(int iSockFd,void *pData,int iLen,char * szIp,int * pPort);

        int     NonBlockUdpWrite(int iSockFd,void *pData,int iLen,const char * szIp,int iPort);
    }
}

#endif
