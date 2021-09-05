#include <stdio.h>
#include "refined_abstraction.h"

CRefinedAbstraction1::CRefinedAbstraction1( std::shared_ptr<CImplementor> &pCImplementor ):
CAbstraction( pCImplementor )
{

}

void CRefinedAbstraction1::Operator1()
{
    printf(">>>> refined abstraction1 start to degrate implementor method1\n");
    m_pCImplementor->Method1();//委托
    printf("do something others ......\n");
    printf("refined abstraction1 Operator1 finnished\n\n");

    return ;
}

CRefinedAbstraction2::CRefinedAbstraction2( std::shared_ptr<CImplementor> &pCImplementor ):
CAbstraction( pCImplementor )
{

}

void CRefinedAbstraction2::Operator1()
{
    printf(">>>> refined abstraction2 start to degrate implementor method1\n");
    m_pCImplementor->Method1();//委托
    printf("do something others ......\n");
    printf("refined abstraction2 Operator1 finnished\n\n");

    return ;
}