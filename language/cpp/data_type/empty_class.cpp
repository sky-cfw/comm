/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-03 11:11:54
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-03 12:52:11
 * @FilePath: /comm/language/cpp/data_type/empty_class.cpp
 * @Description: 
 * a）空类占用的内存空间大小
 * b）为什么占用这么大空间？
 * c）什么场景会用到空类？
 */
#include <stdio.h>
#include <iostream>

using namespace std;

#define PRINT_TYPE_SIZE(s, x) do {\
    printf("size of [%s:%lu]\n", s, sizeof(x));\
}while(0)

//空基类
class empty_cls {};

//空基类优化
class d1 : public empty_cls  {
    int a;
};

//空基类优化被禁止
class d2 : public empty_cls {
    empty_cls ept_cls;
    int a;
};

class d3 : public empty_cls {
    d1 d;
    int a;
};

class d4 : public empty_cls {
    d2 d;
    int a;
};

class d21 : public empty_cls {
    int a;
    empty_cls ept_cls;
};

class d31 : public empty_cls {
    int a;
    d1 d;
};

class d41 : public empty_cls {
    int a;
    d2 d;
};


int main(int argc, char const *argv[]) {
    
    PRINT_TYPE_SIZE( "empty class", empty_cls );
    
    //验证同一类的不同实例都有唯一的地址
    empty_cls ept_cls1, ept_cls2;
    if ( &ept_cls1 == &ept_cls2 ) {
        printf("同一类的不同实例含有相同的内存地址！\n");
        return 0;
    }

    empty_cls *p_empty_cls1 = new empty_cls();
    empty_cls *p_empty_cls2 = new empty_cls();
    if ( p_empty_cls1 == p_empty_cls2 ) {
        printf("同一类的不同实例含有相同的内存地址！\n");
        return 0;
    }

    //空基类优化
    PRINT_TYPE_SIZE( "derived empty class1", d1 );
    
    //空基类优化被禁止
    PRINT_TYPE_SIZE( "derived empty class2", d2 );
    PRINT_TYPE_SIZE( "derived empty class3", d3 );
    PRINT_TYPE_SIZE( "derived empty class4", d4 );

    PRINT_TYPE_SIZE( "derived empty class21", d21 );
    PRINT_TYPE_SIZE( "derived empty class31", d31 );
    PRINT_TYPE_SIZE( "derived empty class41", d41 );

    return 0;
}
