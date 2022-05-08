/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-08 14:20:08
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-08 21:25:39
 * @FilePath: /comm/language/cpp/compile/global_var/global_var_use1.cpp
 * @Description: 如何正确定义全局变量
 */
#include "define.h"

int global_int = 2;

void add( int incr )
{
    global_int += incr;
}