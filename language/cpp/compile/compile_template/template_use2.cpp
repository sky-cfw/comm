/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-08 11:50:30
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-08 11:52:41
 * @FilePath: /comm/language/cpp/compile/compile_template/template_use1.cpp
 * @Description: 多编译单元同一类型实例化模板探究
 */
#include "compile_template.h"

float add_float( const float &a, const float &b )
{
    return add(a, b);
}