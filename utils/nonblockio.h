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
        //�׽�������Ϊ������ģʽ
        int     SetSockNonBlock(int );
        //������tcp����
        int     NonBlockTcpListen(const char *,int);
        //������tcp accept
        int     NonBlockTcpAccept(int ,char* ,int *);
        //������tcp����
        int     NonBlockTcpConnect(const char *,int);
        //������tcp ��ȡ
        int     NonBlockTcpRead(int ,char *,int );
        //������tcp д��
        int     NonBlockTcpWrite(int,char *,int);
        //��鴫������Ƿ�Ϊip��ַ
        int     IsIPAddr(const char *);
        //������unix �׽��ּ���
        int     NonBlockUnixSockListen(const char *);
        //unix �׽���accept
        int     NonBlockUnixAccept(int);
        //unix �׽�������
        int     NonBlockUnixRead(int ,char *,int );

        int     NonBlockUnixWrite(int,char *,int);

        int     LocalUnixConn(const char *sUnixSockFile);

        int     NonBlockUdpListen(const char *ip,unsigned short usPort);

        int     NonBlockUdpRead(int iSockFd,void *pData,int iLen,char * szIp,int * pPort);

        int     NonBlockUdpWrite(int iSockFd,void *pData,int iLen,const char * szIp,int iPort);
    }
}

#endif
