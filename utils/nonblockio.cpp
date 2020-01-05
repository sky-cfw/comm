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
#include <sys/stat.h>
#include "nonblockio.h"

int boss::container::SetSockNonBlock(int    iSockFd)
{
    int    iOpts = 0;

    iOpts = fcntl(iSockFd, F_GETFL);
    if ( iOpts < 0 )
    {
        return -1;
    }
    iOpts = iOpts | O_NONBLOCK;
    if ( fcntl(iSockFd, F_SETFL, iOpts) < 0 )
    {
        return -1;
    }
    return 0;
}

int boss::container::NonBlockTcpListen(const char* sHost, int nServ)
{
    int         iSockFd;
    int         nRetSetOpt;
    int         nRetBnd;
    int         nOne;
    struct  sockaddr_in rServaddr;

    memset(&rServaddr, 0, sizeof(rServaddr));
    rServaddr.sin_family = AF_INET;
    rServaddr.sin_port   = htons((unsigned short)nServ);

    if ( sHost == NULL )
    {
        rServaddr.sin_addr.s_addr = htonl(INADDR_ANY);	//	����������������(ip��ַ)�ϵ�port�˿�
    }
    else
    {
        rServaddr.sin_addr.s_addr = inet_addr(sHost);
    }
    if ( (iSockFd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )	//	�����׽���
    {
        return -1;
    }
    if ( SetSockNonBlock(iSockFd) < 0 )						//	����Ϊ������ģʽ
    {
        close(iSockFd);
        return -1;
    }
    nOne = 1;
    if ( (nRetSetOpt = setsockopt(iSockFd, SOL_SOCKET, SO_REUSEADDR, (char *) & nOne, sizeof(nOne))) != 0 )	//	������־ѡ�� - SO_REUSEADDR ����׽���ѡ��֪ͨ�ںˣ�����˿�æ����TCP״̬λ�� TIME_WAIT ���������ö˿ڡ�����˿�æ����TCP״̬λ������״̬�����ö˿�ʱ���ɵõ�һ��������Ϣ��ָ��"��ַ�Ѿ�ʹ����"�������ķ������ֹͣ�������������������׽�������ʹ��ͬһ�˿ڣ���ʱSO_REUSEADDR ѡ��ǳ�����
    {
        close(iSockFd);
        return -1;
    }
    if ( (nRetBnd = bind(iSockFd, (struct sockaddr*) & rServaddr, sizeof(rServaddr))) < 0 )
    {
        close(iSockFd);
        return -1;
    }
    if ( listen(iSockFd, MAX_SOCKQUEUE_LEN) < 0 )		//	�����׽������Ӷ��д�С  δ������Ӷ���(SYN_REVD״̬) + ��������Ӷ���(ESTABLISHED״̬)
    {
        close(iSockFd);
        return -1;
    }
    return iSockFd;
}

int  boss::container::NonBlockUnixSockListen(const char *sUnixSockFile)
{
    int     iSockFd = -1;
    struct  sockaddr_un stSockAddr;

    bzero(&stSockAddr, sizeof(stSockAddr));
    stSockAddr.sun_family = AF_LOCAL;

    strncpy(stSockAddr.sun_path, sUnixSockFile, sizeof(stSockAddr.sun_path) - 1);
    remove(sUnixSockFile);

    if ( (iSockFd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0 )
        return -1;

    if ( SetSockNonBlock(iSockFd) < 0 )
    {
        close(iSockFd);
        return -1;
    }
    if ( bind(iSockFd, (struct sockaddr *)&stSockAddr, SUN_LEN(&stSockAddr)) < 0 )
    {
        close(iSockFd);
        return -1;
    }
    if ( listen(iSockFd, MAX_SOCKQUEUE_LEN) < 0 )
    {
        close(iSockFd);
        return -1;
    }
    chmod(sUnixSockFile,S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP |S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);	//	Q1:ΪʲôҪ���ļ�Ȩ������Ϊ777? A1:��ֹ�Բ�ͬ���û���������ʱ��ɾ���ļ�ʧ�ܣ���������ʧ��
    return iSockFd;
}

int  boss::container::NonBlockUnixAccept(int iUnixLsnSock)
{
    int             iSockFd;
    socklen_t       nLenCliAddr;
    struct sockaddr_un rCliAddr;

    bzero(&rCliAddr, sizeof(rCliAddr));
    while ( true )
    {
        nLenCliAddr = sizeof(rCliAddr);
        iSockFd = accept(iUnixLsnSock, (struct sockaddr*) & rCliAddr, &nLenCliAddr);
        if ( iSockFd < 0 )
        {
            if ( EINTR == errno )
                continue;
            else
                return -1;
        }
        break;
    }

    if ( SetSockNonBlock(iSockFd) < 0 )
    {
        close(iSockFd);
        return -1;
    }

//     if ( pPath ) {
//         strcpy(pPath, rCliAddr.sun_path);
//     }

    return iSockFd;
}

int  boss::container::LocalUnixConn(const char *sUnixSockFile)
{
    int     iSockFd;
    struct  sockaddr_un stAddr;

    iSockFd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if ( iSockFd < 0 )
        return -1;

    bzero(&stAddr, sizeof(stAddr));
    stAddr.sun_family = AF_LOCAL;
    strncpy(stAddr.sun_path, sUnixSockFile, sizeof(stAddr.sun_path) - 1);

    if ( connect(iSockFd, (struct sockaddr*)&stAddr, sizeof(stAddr)) < 0 )
    {
        close(iSockFd);
        return -1;
    }
    return iSockFd;
}


int  boss::container::NonBlockTcpAccept(int iListenfd, char* sIPClient, int * pPort)
{
    int             iSockFd;
    socklen_t       nLenCliAddr;
    struct linger   rLinger;
    struct sockaddr_in rCliAddr;

    nLenCliAddr = sizeof(rCliAddr);
    memset(&rCliAddr, 0, sizeof(rCliAddr));

    while ( true )
    {
        iSockFd = accept(iListenfd, (struct sockaddr*) & rCliAddr, &nLenCliAddr);
        if ( iSockFd < 0 )
        {
            if ( EINTR == errno )
                continue;
            else
                return -1;
        }
        break;
    }
    if ( sIPClient != NULL )
    {
        strncpy(sIPClient, (const char*)inet_ntoa(rCliAddr.sin_addr), 15);        
    }

    if ( pPort != NULL )
    {
        *pPort = ntohs(rCliAddr.sin_port);
    }

    rLinger.l_onoff  = 1;
    rLinger.l_linger = 0;
    setsockopt(iSockFd, SOL_SOCKET, SO_LINGER, (char *)&rLinger, sizeof(rLinger));

    if ( SetSockNonBlock(iSockFd) < 0 )
    {
        close(iSockFd);
        return -1;
    }

    return iSockFd;
}

int  boss::container::IsIPAddr(const char *sValue)
{
    if ( NULL == sValue )
        return -1;

    while ( *sValue != '\0' )
    {
        if ( (*sValue < '0' || *sValue > '9') && (*sValue != '.') )
            return -1;
        sValue++;
    }
    return 0;
}

int boss::container::NonBlockTcpConnect(const char *sHost, int iServPort)
{
    int     iSockFd  = -1;
    int     iRetCode = 0;
    int     iError   = 0;
    int     iLen     = 0;
    struct  sockaddr_in rServaddr;
    struct  timeval     stTime;
    fd_set  w_Set;
    struct  hostent* stHostent;

    memset(&rServaddr, 0, sizeof(rServaddr));
    if ( IsIPAddr(sHost) != 0 )
    {
        if ( !(stHostent = gethostbyname(sHost)) )
        {
            return -1;
        }
        bzero((char *)&rServaddr, sizeof(rServaddr));
        bcopy(stHostent->h_addr, &rServaddr.sin_addr, sizeof(rServaddr.sin_addr));
    }
    else
    {
        rServaddr.sin_addr.s_addr = inet_addr(sHost);
    }
    rServaddr.sin_family = AF_INET;
    rServaddr.sin_port = htons((unsigned short)iServPort);

    iSockFd = socket(AF_INET, SOCK_STREAM, 0);
    if ( iSockFd < 0 )
    {
        return -1;
    }
    if ( SetSockNonBlock(iSockFd) < 0 )
    {
        close(iSockFd);
        return -1;
    }
    iRetCode = connect(iSockFd, (struct sockaddr*) & rServaddr, sizeof(rServaddr));
    if ( iRetCode < 0 )
    {
        if ( errno == EINPROGRESS )
        {
            stTime.tv_sec = 5;
            stTime.tv_usec = 0;
            FD_ZERO(&w_Set);
            FD_SET(iSockFd, &w_Set);
            if ( select(iSockFd + 1, NULL, &w_Set, NULL, &stTime) > 0 )
            {
                iLen = sizeof(iError);
                iRetCode = getsockopt(iSockFd, SOL_SOCKET, SO_ERROR, &iError, (socklen_t *) & iLen);
                if ( iRetCode == 0 && iError == 0 )
                {
                    return iSockFd;
                }
                else
                {
                    close(iSockFd);
                    return -1;
                }
            }
            else
            {
                close(iSockFd);
                return -1;
            }
        }
        else
        {
            close(iSockFd);
            return -1;
        }
    }
    return iSockFd;
}

int  boss::container::NonBlockTcpRead(int iSockFd, char *pRecvBuff, int iRecvLen)
{
    int     iRet;
    int     iReadLen = 0;

    if ( pRecvBuff == NULL )
    {
        return -1;
    }
    while ( iReadLen < iRecvLen )
    {
        iRet = read(iSockFd, pRecvBuff + iReadLen, iRecvLen - iReadLen);
        if ( iRet < 0 )
        {
            if ( errno == EINTR )	//---�ź��ж�
            {
                continue;
            }
            else if ( errno == EAGAIN || errno == EWOULDBLOCK )	//---û�����ݿɶ�
            {
                break;
            }
            else if ( errno == ECONNRESET )	//---���ӱ�����
            {
                return -3;
            }
            else
            {
                return -2;
            }

        }
        if ( iRet == 0 )	//---�ͻ��˹ر�����ʱ�������read�᷵��0
        {
            return -3;
        }
        iReadLen += iRet;
    }
    return iReadLen;
}

int  boss::container::NonBlockTcpWrite(int iSockFd, char *pSendBuff, int iSendLen)
{
    int     iRet;
    int     iWritenLen = 0;

    if ( pSendBuff == NULL )
    {
        return -1;
    }
    while ( iWritenLen < iSendLen )
    {
        iRet = write(iSockFd, pSendBuff + iWritenLen, iSendLen - iWritenLen);
        if ( iRet < 0 )
        {
            if ( errno == EINTR )
            {
                continue;
            }
            else if ( errno == EAGAIN || errno == EWOULDBLOCK )//---Ϊɶ��break? ˵�����ʹ������ˣ��Ȼ�����д
            {
                break;
            }
            else
            {
                return -2;
            }
        }
        iWritenLen += iRet;
    }
    return iWritenLen;
}

int boss::container::NonBlockUdpListen(const char *ip, unsigned short usPort)
{
    int iFd = socket(AF_INET, SOCK_DGRAM, 0);
    if ( iFd < 0 )
    {
        return -1;
    }

    if ( SetSockNonBlock(iFd) < 0 )
    {
        return -2;
    }

    /*
    More than one process may bind to the same SOCK_DGRAM UDP port if the bind() is preceded by:
    int one = 1; setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one))
    In this case, every incoming multicast or broadcast UDP datagram destined to the shared port is delivered to all sockets bound to the port
    */
    int optval = 1;
    if ( setsockopt(iFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0 )	//---
    {
        return -3;
    }

    struct sockaddr_in svraddr;
    memset(&svraddr, 0, sizeof(svraddr));

    svraddr.sin_family = AF_INET;
    if ( !ip || strlen(ip) == 0 )
    {
        svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        svraddr.sin_addr.s_addr = inet_addr(ip);
    }
    svraddr.sin_port = htons(usPort);

    if ( -1 == bind(iFd, (struct sockaddr *)&svraddr, sizeof(svraddr)) )
    {
        close(iFd);
        iFd = -1;
        return -4;
    }

    return iFd;
}

int  boss::container::NonBlockUdpRead(int iSockFd, void *pData, int iLen, char * szIp, int * pPort)
{
    socklen_t iClientAddrLen = sizeof(sockaddr_in);
    int iRet = 0;
    int iReadLen = 0;
    struct sockaddr_in clientAddr;
    bzero(&clientAddr, sizeof(clientAddr));
    while ( true )
    {
        iRet = recvfrom(iSockFd, pData, iLen, 0, (sockaddr*) & clientAddr, &iClientAddrLen);
        if ( iRet < 0 )
        {
            if ( errno == EINTR )
            {
                continue;
            }
            else if ( errno == EAGAIN || errno == EWOULDBLOCK )
            {
                break;
            }
            else
            {
                return -2;
            }
        }

        if ( iRet > 0 )
        {
            if ( szIp )
            {
                strncpy(szIp, inet_ntoa(clientAddr.sin_addr), 15);
            }

            if ( pPort )
            {
                *pPort = ntohs(clientAddr.sin_port);
            }
        }
        /*
        if ( iRet == 0 ) udp �������������
        {
            return -3;
        }*/
        iReadLen = iRet;
        break;//��һ����
    }
    return iReadLen;
}


int boss::container::NonBlockUdpWrite(int iSockFd, void *pData, int iLen, const char * szIp, int iport)
{
    if ( iLen <= 0 )
    {
        return 0;
    }

    int iRet = 0;

    struct sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    inet_aton(szIp, &clientAddr.sin_addr);
    clientAddr.sin_port = htons(iport);

    while ( true )
    {
        iRet = sendto(iSockFd, pData, iLen, 0/*flag*/, (struct sockaddr *) & clientAddr, sizeof(clientAddr));
        if ( iRet < 0 && errno == EINTR )
        {
            continue;
        }
        break;
    }

    if ( iRet < 0 )
    {
        if ( errno == EAGAIN || errno == EWOULDBLOCK )
        {
            return 0; //����д��
        }
        else
        {
            return -2;
        }
    }
    return iRet;
}

int  boss::container::NonBlockUnixRead(int iSockFd, char *pRecvBuff, int iRecvLen)
{
    return NonBlockTcpRead(iSockFd, pRecvBuff, iRecvLen);
}


int boss::container::NonBlockUnixWrite(int iSockFd, char *pSendBuff, int iSendLen)
{
    return NonBlockTcpWrite(iSockFd, pSendBuff, iSendLen);
}
