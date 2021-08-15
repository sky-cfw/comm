#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void *thread_func(void *)
{
    //让线程循环不退出
    while(true)
    {
        sleep(1);
    }

    return NULL;
}

// cat /proc/sys/kernel/pid_max
// cat /proc/sys/kernel/threads-max
// cat /proc/sys/vm/max_map_count
int main(int argc, char const *argv[])
{
    int err = 0, cnt = 1;
    pthread_t tid;
    while( err == 0 )
    {
        err = pthread_create(&tid, NULL, thread_func, NULL);
        ++cnt;
    }

    //输出错误信息、线程数
    printf("err[%s], max thread cnt[%d]\n", strerror(errno), cnt );

    //输入回车键，程序才退出，方便观察创建完线程后，进程的top情况
    getchar();

    return 0;
}
