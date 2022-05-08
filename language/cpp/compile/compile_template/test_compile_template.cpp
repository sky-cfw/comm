/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-07 21:12:48
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-08 13:16:36
 * @FilePath: /comm/language/cpp/compile/compile_template/main.cpp
 * @Description: 为什么模板函数/模板类的实现要放在头文件中
 */
#include <iostream>
#include <stdio.h>
#include "compile_template.h"
#include "template_use1.h"
#include "template_use2.h"

using namespace std;

int main(int argc, char const *argv[])
{
    
    cout << "3 + 2 = " << add(3, 2) << endl;
    // cout << "4 + 5 = " << add_int(4, 5) << endl;
    // cout << "1.2 + 2.3 = " << add_float(1.2, 2.3) << endl;

    return 0;
}
