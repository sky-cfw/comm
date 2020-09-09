/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     模拟accept队列溢出
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				  
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    if ( argc != 3 )
    {
        printf( "usage ./test_accept_queue_overflow <port> <backlog>\n");
        return 0;
    }
    
    uint16_t port = strtoul( argv[1], NULL, 10 );
    int backlog = atoi( argv[2] );
    printf( "port:%hu, backlog: %d\n", port, backlog );

    struct sockaddr_in serv_addr;
    int listen_fd = 0;
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        exit(1);
    }
    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    if (bind(listen_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) 
    {
        exit(1);
    }
    
    // 设置 backlog 为 50
    if (listen(listen_fd, backlog) == -1) 
    {
        exit(1);
    }
    sleep(100000000);
    
    return 0;
}