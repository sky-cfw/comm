#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t pid = 0;
    int err = 0, cnt = 1;
    while( err == 0 )
    {
        err = fork();
        ++cnt;
    }

    //输出错误信息、线程数
    printf("err[%s], max fork cnt[%d]\n", strerror(errno), cnt );

    //输入回车键，程序才退出，方便观察创建完线程后，进程的top情况
    getchar();

    return 0;
}
