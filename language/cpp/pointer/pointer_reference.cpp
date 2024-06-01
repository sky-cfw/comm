/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2024-06-01 23:36:40
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2024-06-01 23:39:51
 * @FilePath: /comm/language/cpp/pointer/pointer_reference.cpp
 * @Description: 指针和引用的区别(指针是地址，引用是别名)
 */
#include <iostream>

using namespace std;

void testReference(int &b) {
    cout << "a的引用b的地址: " << &b << endl;
}

void testPointer(int *c) {
    cout << "a的指针c的地址: " << &c << endl;
}

int main()
{
    int a = 10;
    cout << "a的地址: " << &a << endl; // a的地址: 0x7fff714f0f64
    testReference(a); // a的引用b的地址: 0x7fff714f0f64
    testPointer(&a); // a的指针c的地址: 0x7fff714f0f48
    return 0;
}