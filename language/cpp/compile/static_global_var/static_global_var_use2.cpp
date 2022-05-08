/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-08 14:20:17
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-08 22:30:59
 * @FilePath: /comm/language/cpp/compile/static_global_var/static_global_var_use2.cpp
 * @Description: 多文件引用静态全局变量
 */
#include "static_define.h"

void sub( int decr )
{
    static_global_int -= decr;
}