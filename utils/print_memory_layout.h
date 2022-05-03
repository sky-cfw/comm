/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-03 14:34:39
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-03 14:36:19
 * @FilePath: /comm/utils/print_memory_layout.h
 * @Description: 打印c++程序变量的内存布局，支持16进制打印 和 2进制打印
 */
#ifndef PRINT_MEMORY_LAYOUT_H
#define PRINT_MEMORY_LAYOUT_H


#include <stdio.h>
#include <iostream>

using namespace std;

namespace boss {
    void char2bin(unsigned char);
    void show_bytes(unsigned char*, int);
}

#endif