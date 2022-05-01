/*
 * @Author: sky
 * @Date: 2022-03-19 22:04:31
 * @LastEditTime: 2022-03-27 15:12:12
 * @LastEditors: Please set LastEditors
 * @Description: malloc 内存分配原理
 * @FilePath: /comm/linux/memory/malloc.cpp
 */

/*
Q1：malloc(1) 会分配多大的内存？
Q2：free释放内存，会归还给操作系统吗？
*/

#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf( "使用 cat /proc/%d/maps 查看程序启动时内存分配\n", getpid() );
    getchar();

    //申请1字节的内存空间
    //void *addr = malloc(1);
    //void *addr = malloc(127*1024);
    void *addr = malloc( 128*1024 );
    printf( "此1字节的内存起始地址为: %p\n", addr );
    printf( "使用 cat /proc/%d/maps 查看内存分配\n", getpid() );

    //将程序阻塞，当输入任意字符时才往下执行
    getchar();

    //释放内存
    free(addr);
    printf( "释放了1字节的堆内存，但并不会归还给操作系统\n" );
    getchar();

    //申请1字节的内存空间
    //addr = malloc(1);
    //addr = malloc( 127*1024 );
    addr = malloc( 128*1024 );
    printf( "此1字节的内存起始地址为: %p\n", addr );
    printf( "使用 cat /proc/%d/maps查看内存分配\n", getpid() );
    getchar();
    
    return 0;
}
