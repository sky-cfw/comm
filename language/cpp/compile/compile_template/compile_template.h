/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-07 21:12:22
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-08 12:21:09
 * @FilePath: /comm/language/cpp/compile/compile_template/compile_template.h
 * @Description: 
 */
#ifndef COMPILE_TEMPLATE_H
#define COMPILE_TEMPLATE_H

// template<typename T>
// T add(const T &a, const T &b);
template<typename T>
T add(const T &a, const T &b)
{
    return a + b;
}

#endif