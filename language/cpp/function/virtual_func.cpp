/*
 * @Author: sky
 * @Date: 2022-05-01 18:52:53
 * @LastEditTime: 2022-05-03 22:46:29
 * @LastEditors: sky wcf0118@gmail.com
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
    ~CDerived() { cout << "CDerived::~CDerived() called" << endl; }

    virtual void sing() { cout << "CDerived::sing() called" << endl; }  
    // virtual void song() { cout << "CDerived::song() called" << endl; } 
};

class COneVirtualFunc {
public:
    virtual void sing() { cout << "COneVirtualFunc::sing() called" << endl; }
};

typedef void (*f) (void);

int main(int argc, char const *argv[]){
    cout << "-------------------- 虚函数表类的多个实例是共用的吗 ----------------------" << endl;
    CBase *pB1 = new CBase();
    CBase *pB2 = new CBase();
    unsigned long *tmp1 = reinterpret_cast<unsigned long *>(pB1);//tmp1指向vptr1
    unsigned long *tmp2 = reinterpret_cast<unsigned long *>(pB2);//tmp2指向vptr2
    unsigned long *pB1Vtable = reinterpret_cast<unsigned long *>(*tmp1);//*tmp1 表示vptr1内容的值，也就是虚函数表首地址
    unsigned long *pB2Vtable = reinterpret_cast<unsigned long *>(*tmp2);//*tmp2 表示vptr2内容的值，也就是虚函数表首地址
    printf( "指针占用空间大小：%lu\n", sizeof(pB1) );
    printf( "父类实例化对象pB1虚指针vptr指向地址: 0x%016lx\n", *(unsigned long *)pB1 );
    printf( "父类实例化对象pB2虚指针vptr指向地址: 0x%016lx\n", *(unsigned long *)pB2 );
    printf( "父类实例化对象pB1虚指针vptr指向地址: %p\n", pB1Vtable );
    printf( "父类实例化对象pB2虚指针vptr指向地址: %p\n", pB2Vtable );

    cout << endl << "-------------------- 子类和父类共用虚函数表吗 ----------------------" << endl;
    CDerived *pD1 = new CDerived();
    CDerived *pD2 = new CDerived();
    tmp1 = reinterpret_cast<unsigned long *>(pD1);//tmp1指向vptr1
    tmp2 = reinterpret_cast<unsigned long *>(pD2);//tmp2指向vptr2
    unsigned long *pD1Vtable = reinterpret_cast<unsigned long *>(*tmp1);//*tmp1 表示vptr1内容的值，也就是虚函数表首地址
    unsigned long *pD2Vtable = reinterpret_cast<unsigned long *>(*tmp2);//*tmp2 表示vptr2内容的值，也就是虚函数表首地址
    printf( "子类实例化对象pD1虚指针vptr指向地址: %p\n", pD1Vtable );
    printf( "子类实例化对象pD2虚指针vptr指向地址: %p\n", pD2Vtable );
    
    cout << endl << "-------------------- 模拟调用基类虚函数 -----------------------" << endl;
    f *f1 = reinterpret_cast<f *>(pB1Vtable);
    printf("f1: %p, 基类vtable第一项值: %p\n", f1, reinterpret_cast<unsigned long *>(*f1));
    printf("f1+1: %p, 基类vtable第二项值: %p\n", f1+1, reinterpret_cast<unsigned long *>(*(f1+1)));
    printf("f1+2: %p, 基类vtable第三项值: %p\n", f1+2, reinterpret_cast<unsigned long *>(*(f1+2)));
    (*(f1+2))();
    printf("f1+3: %p, 基类vtable第四项值: %p\n", f1+3, reinterpret_cast<unsigned long *>(*(f1+3)));
    (*(f1+3))();

    cout << endl << "-------------------- 模拟调用子类虚函数 -----------------------" << endl;
    f1 = reinterpret_cast<f *>(pD1Vtable);
    printf("f1: %p, 子类vtable第一项值: %p\n", f1, reinterpret_cast<unsigned long *>(*f1));
    printf("f1+1: %p, 子类vtable第二项值: %p\n", f1+1, reinterpret_cast<unsigned long *>(*(f1+1)));
    printf("f1+2: %p, 子类vtable第三项值: %p\n", f1+2, reinterpret_cast<unsigned long *>(*(f1+2)));
    (*(f1+2))();
    printf("f1+3: %p, 子类vtable第四项值: %p\n", f1+3, reinterpret_cast<unsigned long *>(*(f1+3)));
    (*(f1+3))();

    cout << endl << "-------------------- 模拟调用只汗单个虚函数的虚函数 -----------------------" << endl;
    COneVirtualFunc *pCO1 = new COneVirtualFunc();
    tmp1 = reinterpret_cast<unsigned long *>(pCO1);
    unsigned long *pCO1Vtable = reinterpret_cast<unsigned long *>(*tmp1);
    f1 = reinterpret_cast<f *>( pCO1Vtable );
    printf("f1: %p, vtable第一项值: %p\n", f1, reinterpret_cast<unsigned long *>(*f1));
    (*f1)();
    printf("f1+1: %p, vtable第二项值: %p\n", f1+1, reinterpret_cast<unsigned long *>(*(f1+1)));
    // (*(f1+1))();
    printf("f1+2: %p, vtable第三项值: %p\n", f1+2, reinterpret_cast<unsigned long *>(*(f1+2)));
    // (*(f1+2))();

    return 0;
}
