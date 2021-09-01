#include <stdio.h>
#include "proxy.h"

CProxy::CProxy( CSubject *&pCSubject ):
m_pCSubject( pCSubject )
{
    
}

void CProxy::Operator1()
{
    printf("pre process something\n");
    m_pCSubject->Operator1();//委托
    printf("after process something\n");

    return ;
}

void CProxy::Operator2()
{
    printf("pre process something\n");
    m_pCSubject->Operator2();//委托
    printf("after process something\n");

    return ;
}
