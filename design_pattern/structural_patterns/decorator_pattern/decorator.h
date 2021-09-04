#ifndef DECORATOR_H
#define DECORATOR_H

#include "subject.h"

/*
Q：为什么不让装饰器类直接继承至目标类CSubject，而是再搞一个基类去继承至CSubject？
A：原因在于如果要装饰的接口很多，比如现在CConcreteDecorator只有Operator1()一个方法
*/
class CDecorator : public CSubject
{
public:
    CDecorator( CSubject *&pCSubject );
    virtual ~CDecorator();

    void Operator1();

protected:
    CSubject *m_pCSubject;//组合  
};

#endif