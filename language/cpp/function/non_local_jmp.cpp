/*
 * @Author: sky
 * @Date: 2022-02-05 14:48:07
 * @LastEditTime: 2022-02-05 16:00:04
 * @LastEditors: Please set LastEditors
 * @Description: 非本地跳转应用场景 1.
 * @FilePath: /comm/language/cpp/function/non_local_jmp.cpp
 */
#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

int B()
{
    //todo
    //...
    int ret = -1;//逻辑执行结果
    if ( ret != 0 )
    {
        longjmp( env, 2 );
    }

    return 0;
}

int A()
{
    //todo
    //...
    int ret = 0;//逻辑执行结果
    if ( ret != 0 )
    {
        longjmp( env, 1 );
    }
    
    ret = B();
    printf( "func B returned to A\n" );
    return ret;
}

int main(int argc, char const *argv[])
{
    int ret = setjmp( env );
    if ( 0 == ret )//直接调用返回
    {
        A();
        printf( "call A success!\n" );
    }
    else if ( 1 == ret )//A函数内部的 longjmp 非本地跳转返回
    {
        printf( "func A returned error\n" );
    }
    else if ( 2 == ret )//B函数内部的 longjmp 非本地跳转返回
    {
        printf("func B returned error\n");
    }

    return ret;
}
