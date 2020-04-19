/* 测试kill(pid, 0)的作用
 * 结论：检测pid对应的进程是否存在以及是否有权限对其发送信号
 *
 *
*/
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    if ( argc != 3 )
    {
        printf( "usage: %s %d %s\n", argv[0], 1, "pid" );
        printf( "usage: %s %d %s\n", argv[0], 2, "file" );
        return 0;
    }

    int op = atoi( argv[1] );
    if ( 1 == op )
    {
        pid_t pid = atoi(argv[2]);
        /*
        * If  sig  is 0, then no signal is sent, but existence and permission checks are still performed; this can be used to check for existence of a process ID or process group ID that the caller is permitted to signal.
        */
        if ( -1 == kill( pid, 0 ) )
        {
            if ( errno == ESRCH )
            {
                perror("ESRCH error");
            }
            else
            {
                perror("error");
            }
        }
        else
        {
            printf("Pid[%d] is exist and allowed to be send signal.\n", pid);
        }
    }
    else
    {

    }

    return 0;
}
