/*
 * @Author: sky
 * @Date: 2022-05-01 19:56:47
 * @LastEditTime: 2022-05-01 22:55:56
 * @LastEditors: Please set LastEditors
 * @Description: 
 * a）打印基本数据类型的大小
 * b）打印空类占用的存储空间大小
 * @FilePath: /comm/language/cpp/data_type/data_type_size.cpp
 */
#include <stdio.h>
#include <iostream>

using namespace std;

#define PRINT_TYPE_SIZE(s, x) do {\
    printf("size of [%s:%u]\n", s, sizeof(x));\
}while(0)

class a {
public:
    a() {}
    ~a() {}
};

int main(int argc, char const *argv[])
{
    //基本数据类型
    PRINT_TYPE_SIZE( "char", char );
    PRINT_TYPE_SIZE( "unsigned int", unsigned int );
    PRINT_TYPE_SIZE( "int", int );
    PRINT_TYPE_SIZE( "long", long );
    PRINT_TYPE_SIZE( "long long", long long );
    PRINT_TYPE_SIZE( "size_t", size_t );

    int a = 4;
    int *p = &a;
    printf("p=%p\n", p);
    PRINT_TYPE_SIZE( "pointer", p );

    //空类占用的存储空间
    PRINT_TYPE_SIZE( "empty class", a );

    return 0;
}
