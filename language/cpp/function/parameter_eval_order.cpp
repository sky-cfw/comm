/*
 * @Author: 函数参数求值顺序
 * @Date: 2021-12-18 20:36:48
 * @LastEditTime: 2021-12-19 20:52:00
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /comm/language/cpp/function/parameter_eval_order.cpp
 */
/*
极客时间《深入理解C语言与程序运行原理》

1. C标准并没有规定 函数调用时 实参的求值顺序，由实现C标准的编译器自行实现；
2. 对于GCC编译器，由右向左求值。对于Clang编译器，由左向右求值。
*/
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n = 1;

    printf( "%d %d %d\n", n++, n++, n++ );
    
    return 0;
}

