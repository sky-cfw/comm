/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-03 11:11:54
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-03 19:50:17
 * @FilePath: /comm/language/cpp/data_type/empty_class.cpp
 * @Description: 
 * a）空类占用的内存空间大小
 * b）为什么占用这么大空间？
 * c）什么场景会用到空类？
 */
#include <stdio.h>
#include <iostream>
#include "print_memory_layout.h"

using namespace std;

#define PRINT_TYPE_SIZE(s, x) do {\
    printf("size of [%s:%lu]\n", s, sizeof(x));\
}while(0)

//空基类
class empty_cls {};

//空基类优化
class d1 : public empty_cls  {
public:
    d1(int _a):a(_a) {}
    int a;
};

//空基类优化被禁止
class d2 : public empty_cls {
public:
    d2(empty_cls c, int _a):ept_cls(c),a(_a){}
    empty_cls ept_cls;
    int a;
};

class d3 : public empty_cls {
public:
    d3(d1 _d, int _a):d(_d),a(_a){}
    d1 d;
    int a;
};

class d4 : public empty_cls {
public:
    d4(d2 _d, int _a):d(_d),a(_a){}
    d2 d;
    int a;
};

class d21 : public empty_cls {
public:
    d21(empty_cls c, int _a):a(_a),ept_cls(c){}
    int a;
    empty_cls ept_cls;
};

class d31 : public empty_cls {
public:
    d31(d1 _d, int _a):a(_a),d(_d){}
    int a;
    d1 d;
};

class d41 : public empty_cls {
public:
    d41(d2 _d, int _a):a(_a),d(_d){}
    int a;
    d2 d;
};


int main(int argc, char const *argv[]) {
    
    PRINT_TYPE_SIZE( "empty class", empty_cls );
    
    //验证同一类的不同实例都有唯一的地址
    empty_cls ept_cls1, ept_cls2;
    boss::show_bytes( reinterpret_cast<unsigned char *>(&ept_cls1), sizeof(ept_cls1) );
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

    //空基类优化(当空类作为基类时，空类所占用的 `1` 字节空间会被优化掉)
    PRINT_TYPE_SIZE( "derived empty class1", d1 );
    d1 o1(1);
    boss::show_bytes( reinterpret_cast<unsigned char *>(&o1), sizeof(o1) );
    
    //空基类优化被禁止(当空基类本身 或 空基类的子类 是类的第一个非静态数据成员时，空基类优化将被禁止)
    PRINT_TYPE_SIZE( "derived empty class2", d2 );
    d2 o2(ept_cls1, 2);
    PRINT_TYPE_SIZE( "d2.ept_cls", o2.ept_cls );
    boss::show_bytes( reinterpret_cast<unsigned char *>(&o2), sizeof(o2) );

    PRINT_TYPE_SIZE( "derived empty class3", d3 );
    d3 o3(o1, 3);
    PRINT_TYPE_SIZE( "d3.d1", o3.d );
    boss::show_bytes( reinterpret_cast<unsigned char *>(&o3), sizeof(o3) );

    PRINT_TYPE_SIZE( "derived empty class4", d4 );
    d4 o4(o2, 4);
    PRINT_TYPE_SIZE( "d4.d2", o4.d );
    boss::show_bytes( reinterpret_cast<unsigned char *>(&o4), sizeof(o4) );

    //上述强调的是第一个非静态数据成员，如果不是第一个，是不是就使用上了空基类优化
    PRINT_TYPE_SIZE( "derived empty class21", d21 );
    d21 o21(ept_cls1, 21);
    PRINT_TYPE_SIZE( "d21.ept_cls", o21.ept_cls );
    boss::show_bytes( reinterpret_cast<unsigned char *>(&o21), sizeof(o2) );
    
    PRINT_TYPE_SIZE( "derived empty class31", d31 );
    d31 o31(o1, 31);
    PRINT_TYPE_SIZE( "d21.d1", o31.d );
    boss::show_bytes( reinterpret_cast<unsigned char *>(&o31), sizeof(o31) );
    
    PRINT_TYPE_SIZE( "derived empty class41", d41 );
    d41 o41(o2, 41);
    PRINT_TYPE_SIZE( "d41.d2", o41.d );
    boss::show_bytes( reinterpret_cast<unsigned char *>(&o41), sizeof(o41) );

    return 0;
}
