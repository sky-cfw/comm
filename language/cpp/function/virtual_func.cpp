/*
 * @Author: sky
 * @Date: 2022-05-01 18:52:53
 * @LastEditTime: 2022-05-02 11:43:34
 * @LastEditors: Please set LastEditors
 * @Description: 
 * 1）虚函数表父子类独有还是共享？
 * 2）
 * @FilePath: /comm/language/cpp/function/virtual_func.cpp
 */

#include <iostream>
#include <stdio.h>

using namespace std;

class CBase {
public:
    CBase() { cout << "CBase::CBase() called" << endl; }
    virtual ~CBase() { cout << "CBase::~CBase() called" << endl; }

    virtual void sing() { cout << "CBase::sing() called" << endl; }  
    virtual void song() { cout << "CBase::song() called" << endl; }  
};

class CDerived : public CBase {
public:
    CDerived() { cout << "CDerived::CDerived() called" << endl; }
    virtual ~CDerived() { cout << "CDerived::~CDerived() called" << endl; }

    virtual void sing() { cout << "CDerived::sing() called" << endl; }  
    virtual void song() { cout << "CDerived::song() called" << endl; } 
};

typedef void (*f) (void);

int main(int argc, char const *argv[]){
    cout << "-------------------- 虚函数表类的多个实例是共用的吗 ----------------------" << endl;
    CBase *pB1 = new CBase();
    CBase *pB2 = new CBase();
    unsigned long *tmp1 = reinterpret_cast<unsigned long *>(pB1);//tmp1指向vptr1
    unsigned long *tmp2 = reinterpret_cast<unsigned long *>(pB2);//tmp2指向vptr2
    unsigned long *pBVtable1 = reinterpret_cast<unsigned long *>(*tmp1);//*tmp1 表示vptr1内容的值，也就是虚函数表首地址
    unsigned long *pBVtable2 = reinterpret_cast<unsigned long *>(*tmp2);//*tmp2 表示vptr2内容的值，也就是虚函数表首地址
    printf( "指针占用空间大小：%lu\n", sizeof(pB1) );
    printf( "父类实例化对象pB1虚函数指针指向地址: 0x%016x\n", *(unsigned long *)pB1 );
    printf( "父类实例化对象pB2虚函数指针指向地址: 0x%016x\n", *(unsigned long *)pB2 );
    printf( "父类实例化对象pB1虚函数指针指向地址: %p\n", pBVtable1 );
    printf( "父类实例化对象pB2虚函数指针指向地址: %p\n", pBVtable2 );

    cout << endl << "-------------------- 子类和父类共用虚函数表吗 ----------------------" << endl;
    CDerived *pD1 = new CDerived();
    CDerived *pD2 = new CDerived();
    printf( "子类实例化对象pD1虚函数指针指向地址: 0x%016x\n", *(unsigned long *)pD1 );
    printf( "子类实例化对象pD2虚函数指针指向地址: 0x%016x\n", *(unsigned long *)pD2 );
    
    cout << endl << "-------------------- 模拟调用虚函数 -----------------------" << endl;
    f *f1 = reinterpret_cast<f *>(pBVtable1);
    printf("f1: %p\n", f1);
    printf("f1+2: %p\n", f1+2);
    (*(f1+2))();
    printf("f1+3: %p\n", f1+3);
    (*(f1+3))();

    return 0;
}
