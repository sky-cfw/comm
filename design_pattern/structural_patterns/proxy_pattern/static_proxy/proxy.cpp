#include <stdio.h>
#include "proxy.h"

CProxy::CProxy( CSubject *&pCSubject ):
m_pCSubject( pCSubject )
{
    
}

void CProxy::PreProcess()
{
    printf("pre process something\n");

    return ;
}

void CProxy::PostProcess()
{
    printf("post process something\n");

    return ;
}

void CProxy::Operator1()
{
    PreProcess();
    m_pCSubject->Operator1();//委托
    PostProcess();

    return ;
}

void CProxy::Operator2()
{
    PreProcess();
    m_pCSubject->Operator2();//委托
    PostProcess();

    return ;
}
