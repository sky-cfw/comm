/*
 * @Author: sky
 * @Date: 2021-12-19 21:52:08
 * @LastEditTime: 2021-12-19 22:25:34
 * @LastEditors: Please set LastEditors
 * @Description: 尾递归调用
 * @FilePath: /comm/language/cpp/function/tail_recursion.cpp
 */

/*
$ gcc -O3 -S tail_recursion.cpp -o tail_recursion_o3.s
$ gcc -S tail_recursion.cpp -o tail_recursion.s

开启O3等级优化情况下，编译器内部  factorial1 和 factorial2 是等价的。都是通过跳转执行替换调用指令，达到优化的目的。
*/
#include <stdio.h>

//非尾递归调用
int factorial1( int n ) 
{ 
    if (n == 1 || n == 0) 
    {
        return 1; 
    }

    return n * factorial1(n - 1);
}

//尾递归调用
int factorial2( int n, int r ) 
{ 
    if ( n == 0 ) 
    {
        return r;
    }
    else
    {
        return factorial2( n-1, n*r );
    }
}

int main(int argc, char const *argv[])
{
    printf( "non tail recursion, 5! = %d\n", factorial1(5) );
    printf( "tail recursion, 5! = %d\n", factorial2(5,1) );

    return 0;
}
