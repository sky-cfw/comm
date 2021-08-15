#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//终端设备io
void fork_and_terminal_io()
{
	int var = 6;
	char buf[] = "write to stdout\n";

    //不带缓冲的OS IO函数
	if ( sizeof(buf)-1 != write( STDOUT_FILENO, buf, sizeof(buf)-1 ) )
	{
		printf("write error\n");
		return ;
	}

    //标准输出指向终端设备(行缓冲)
	printf("before fork\n");
	// printf("before fork");

	int pid = fork();
	if ( pid < 0 )
	{
		printf("fork error\n");
		return ;
	}
	else if ( 0 == pid )
	{
		var++;
	}
	else
	{
		sleep(2);
	}

	printf("pid=%ld, var=%d\n", pid, var);

	return ;
}

//fork与文件io
void fork_and_file_io()
{
	int var = 6;
	char buf[] = "before fork\n";

	//file指向文件IO流(全缓冲)
	//对于能够定位流位置的
	FILE *file = fopen("~/fork_and_file_io.txt", "a+");

	//全缓冲
	if ( sizeof(buf)/sizeof(char) != fwrite( buf, sizeof(char), sizeof(buf)/sizeof(char), file ) )
	{
		printf("fwrite error\n");
		return ;
	}

	int pid = fork();
	if ( pid < 0 )
	{
		printf("fork error\n");
		return ;
	}
	else if ( 0 == pid )
	{
		var++;
	}
	else
	{
		sleep(2);
	}

	//不带缓冲的OS IO函数
	if ( sizeof(buf)/sizeof(char) != fwrite( buf, sizeof(char), sizeof(buf)/sizeof(char), file ) )
	{
		printf("fwrite error\n");
		return ;
	}

	return ;
}

void fork_and_usock_io()
{

}

void fork_and_net_socket_io()
{

}

int main(int argc, char const *argv[])
{
	if ( argc < 2 )
	{
		printf("usage:\n");
		printf("./fork_and_io 1 : test terminal io\n");
		printf("./fork_and_io 2 : test file io\n");
		printf("./fork_and_io 3 : test unix socket io\n");
		printf("./fork_and_io 4 : test net socket io\n");
		return 0;
	}
	
	int iOption = atoi( argv[1] );
	if ( 1 == iOption )
	{
		fork_and_terminal_io();
	}
	else if ( 2 == iOption )
	{
		fork_and_file_io();
	}
	else if ( 3 == iOption )
	{
		fork_and_usock_io();
	}
	else if ( 4 == iOption )
	{
		fork_and_net_socket_io();
	}

	return 0;
}
