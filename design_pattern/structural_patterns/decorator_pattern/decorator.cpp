#include <stdio.h>
#include "decorator.h"

CDecorator1::CDecorator1( CSubject *&pCSubject ):
m_pCSubject(pCSubject)
{

}

CDecorator1::~CDecorator1()
{
    if ( m_pCSubject != NULL )
    {
        delete m_pCSubject;
        m_pCSubject = NULL;
    }
}

void CDecorator1::Operator1()
{
    printf("decorator1 enhance functional requirements 1\n");//增强功能性需求1
    m_pCSubject->Operator1();//委托

    return ;
}

CDecorator2::CDecorator2( CSubject *&pCSubject ):
m_pCSubject(pCSubject)
{

}

CDecorator2::~CDecorator2()
{
    if ( m_pCSubject != NULL )
    {
        delete m_pCSubject;
        m_pCSubject = NULL;
    }
}

void CDecorator2::Operator1()
{
    printf("decorator2 enhance functional requirements 2\n");//增强功能性需求1
    m_pCSubject->Operator1();//委托

    return ;
}