/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-08 14:19:52
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-08 20:43:52
 * @FilePath: /comm/language/cpp/compile/global_var/global_var.cpp
 * @Description: 多个cpp引用全局变量的情况下，如何正确定义全局变量？
 */
#include <iostream>
#include <stdio.h>
#include "global_var_use1.h"
#include "global_var_use2.h"
#include "define.h"

using namespace std;

#define PRINT_INT( a ) do {\
    cout << "a = " << a << endl;\
}while(0)

int main(int argc, char const *argv[])
{
    PRINT_INT( global_int );
    add( 1 );
    PRINT_INT( global_int );
    sub( 1 );
    PRINT_INT( global_int );

    return 0;
}
