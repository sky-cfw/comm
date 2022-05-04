/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-05 00:24:19
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-05 00:59:46
 * @FilePath: /comm/language/cpp/data_type/type_cast.cpp
 * @Description: 强制类型转换操作符
 */
#include <iostream>
#include <stdio.h>

using namespace std;

class cb {

};

class cd : public cb {

};

//static_cast 强制转换操作符
void static_cast_test() {
    //1.基本数据类型转换
    printf("-------------------- static_cast 强制类型转换操作符 --------------------\n");
    printf("1.基本数据类型转换\n");
    int a = 128;
    short b = static_cast<short>(a);//
    char c = static_cast<char>(a);

    printf("有符号整形a[%d]\n", a);
    printf("采用static_cast操作符强制转换为short后的值b为[%hd]\n", b);
    printf("采用static_cast操作符强制转换为char后的值c为[%d]\n", c);

    printf("\n2.void类型指针与目标类型指针转换\n");
    void *pa = &a;
    short *pb = static_cast<short *>(pa);
    long *pc = static_cast<long *>(pa);
    printf("void * 采用static_cast操作符强制转换为 short * 后的值为[%hd]\n", (*pb));
    printf("void * 采用static_cast操作符强制转换为 long * 后的值为[%ld]\n", (*pc));

    printf("\n3.父子类层级中，父子类指针或引用的转换\n");
    cb o1;
    cd *po2 = static_cast<cd *>(&o1);

}

void dynamic_cast_test() { 

}

void const_cast_test() { 
    
}

void reinterpret_cast_test() { 
    
}

int main(int argc, char const *argv[]) {
    
    if ( argc < 2 ) {
        printf( "Usage: ./type_cast <opt>\n" );
        printf( "opt: 1-static_cast 2-dynamic_cast 3-const_cast 4-reinterpret_cast\n" );
        return 0;
    }

    int opt = atoi( argv[1] );
    switch ( opt ) {
        case 1: {
            static_cast_test();
            break;
        }

        case 2: {
            dynamic_cast_test();
            break;
        }

        case 3: {
            const_cast_test();
            break;
        }

        case 4: {
            reinterpret_cast_test();
            break;
        }

        default: {
            printf( "not support opt, break\n" );
            break;
        }
    }

    return 0;
}
