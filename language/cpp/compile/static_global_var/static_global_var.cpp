/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-08 14:19:52
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-08 22:29:43
 * @FilePath: /comm/language/cpp/compile/global_var/global_var.cpp
 * @Description: 多文件引用静态全局变量
 */
#include <iostream>
#include <stdio.h>
#include "static_global_var_use1.h"
#include "static_global_var_use2.h"
#include "static_define.h"

using namespace std;

#define PRINT_INT( a ) do {\
    cout << "a = " << a << endl;\
}while(0)

int main(int argc, char const *argv[])
{
    PRINT_INT( static_global_int );
    add( 1 );
    PRINT_INT( static_global_int );
    sub( 1 );
    PRINT_INT( static_global_int );

    return 0;
}
