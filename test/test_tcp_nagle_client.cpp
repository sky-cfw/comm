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

/*
Nagle算法策略
+ 当第一次发送数据时不用等待，就算是 1byte 的小包也立即发送；
+ 没有已发送未确认报文时，立刻发送数据；
+ 存在未确认报文时，直到「没有已发送未确认报文」或「数据长度达到 MSS 大小」时，再发送数据；
nagle算法默认开启，对于时延比较敏感的场景，应当关闭nagle算法，比如：ssh客户端；
*/

int main(int argc, char *argv[])
{
	int client_sockfd;
	int len;
	struct sockaddr_in remote_addr; //服务器端网络地址结构体
	char buf[BUFSIZ];  //数据传送的缓冲区
	memset(&remote_addr,0,sizeof(remote_addr)); //数据初始化--清零
	remote_addr.sin_family=AF_INET; //设置为IP通信
	remote_addr.sin_addr.s_addr=inet_addr("66.98.117.197");//服务器IP地址
	remote_addr.sin_port=htons(9999); //服务器端口号

	/*创建客户端套接字--IPv4协议，面向连接通信，TCP协议*/
	if((client_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
	{
		perror("socket error");
		return 1;
	}

	/*将套接字绑定到服务器的网络地址上*/
	if(connect(client_sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)
	{
		perror("connect error");
		return 1;
	}
	printf("connected to server\n");
	// len=recv(client_sockfd,buf,BUFSIZ,0);//接收服务器端信息
	// buf[len]='/0';
	// printf("%s",buf); //打印服务器端信息

	/*循环的发送接收信息并打印接收信息（可以按需发送）--recv返回接收到的字节数，send返回发送的字节数*/
	while(1)
	{
		// printf("Enter string to send:");
		// scanf("%s",buf);
		// if(!strcmp(buf,"quit"))
		// 	break;
		snprintf(buf, sizeof(buf), "test_tcp_nagle");
		len=send(client_sockfd,buf,strlen(buf),0);
		len=send(client_sockfd,buf,strlen(buf),0);
		len=send(client_sockfd,buf,strlen(buf),0);
		len=send(client_sockfd,buf,strlen(buf),0);//不存在未确认报文，这里没模拟出来
		len=recv(client_sockfd,buf,BUFSIZ,0);
		buf[len]='\0';
		printf("received:%s\n",buf);

		sleep(100000);
	}

	/*关闭套接字*/
	close(client_sockfd);

	return 0;
}
