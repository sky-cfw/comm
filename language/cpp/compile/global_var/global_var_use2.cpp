/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-08 14:20:17
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-08 20:41:52
 * @FilePath: /comm/language/cpp/compile/global_var/global_var_use2.cpp
 * @Description: 多个cpp引用全局变量的情况下，如何正确定义全局变量？
 */
#include "define.h"

void sub( int decr )
{
    global_int -= decr;
}