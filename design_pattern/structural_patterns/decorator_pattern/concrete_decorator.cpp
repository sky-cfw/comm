#include <stdio.h>
#include "concrete_decorator.h"

/*
Q：父类构造函数有参数的，这里子类的构造函数如何初始化？
需要在子类的构造函数中显示的调用父类的构造函数

错误写法1
CConcreteDecorator1::CConcreteDecorator1( CSubject *&pCSubject )
{
    CDecorator::CDecorator(pCSubject);
}

错误写法2
CConcreteDecorator1::CConcreteDecorator1( CSubject *&pCSubject ):
m_pCSubject( pCSubject )
{
    
}
*/
CConcreteDecorator1::CConcreteDecorator1( CSubject *&pCSubject ):
CDecorator( pCSubject )//显示调用父类的有参构造函数
{
}

CConcreteDecorator1::~CConcreteDecorator1()
{

}

void CConcreteDecorator1::Operator1()
{
    printf("concrete decorator1 enhance functional requirements 1\n");//增强功能性需求1
    m_pCSubject->Operator1();//委托

    return ;
}

CConcreteDecorator2::CConcreteDecorator2( CSubject *&pCSubject ):
CDecorator(pCSubject)
{

}

CConcreteDecorator2::~CConcreteDecorator2()
{
    
}

void CConcreteDecorator2::Operator1()
{
    printf("concrete decorator2 enhance functional requirements 2\n");//增强功能性需求1
    m_pCSubject->Operator1();//委托

    return ;
}