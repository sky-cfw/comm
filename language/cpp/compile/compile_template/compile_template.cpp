/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-07 21:12:42
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-08 12:18:26
 * @FilePath: /comm/language/cpp/compile/compile_template/compile_template.cpp
 * @Description: 为什么模板函数/模板类的实现要放在头文件中
 */
#include "compile_template.h"

template<typename T>
T add(const T &a, const T &b)
{
    return a + b;
}

//函数模板显示实例化
template int add<int>(const int &, const int &);
template float add<float>(const float &, const float &);