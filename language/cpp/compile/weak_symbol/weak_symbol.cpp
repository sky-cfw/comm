/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-08 13:41:54
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-08 13:44:27
 * @FilePath: /comm/language/cpp/compile/weak_symbol/weak_symbol.cpp
 * @Description: 强弱符号探究
 */
#include <iostream>
#include <stdio.h>

using namespace std;

int a = 0;
int b;
static int c;

int add( int m, int n )
{
    return m + n;
}

int main(int argc, char const *argv[])
{
    int i = 0;
    int j;
    static int k; 

    return 0;
}
