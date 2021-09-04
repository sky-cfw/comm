#ifndef CONCRETE_DECORATOR_H
#define CONCRETE_DECORATOR_H

#include "subject.h"
#include "decorator.h"

/*
注意：装饰器类和原始类继承同样的父类，这使得可以对原始类叠加多个装饰器类。代理模式也是，理论上代理类也可以叠加。
如果装饰器类和原始类不是继承同一父类，则要叠加多个装饰功能时，会出现类爆炸的情况。继承至同一父类后，使得可以叠加任意组合。
*/

/*
定义装饰器类1，附加功能性需求1
*/
class CConcreteDecorator1 : public CDecorator
{
public:
    CConcreteDecorator1( CSubject *&pCSubject );
    ~CConcreteDecorator1();

    virtual void Operator1();
};

/*
定义具体装饰器类2，附加功能性需求2
*/
class CConcreteDecorator2 : public CDecorator
{
public:
    CConcreteDecorator2( CSubject *&pCSubject );
    ~CConcreteDecorator2();

    virtual void Operator1();
};

#endif