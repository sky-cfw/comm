#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "refined_abstraction.h"
#include "concrete_implementor.h"

void CClient::DoSomething()
{
    // CImplementor *pCConcreteImplementor1 = new CConcreteImplementor1();
    std::shared_ptr<CImplementor> pCConcreteImplementor1 = std::make_shared<CConcreteImplementor1>();
    // CImplementor *pCConcreteImplementor2 = new CConcreteImplementor2();
    std::shared_ptr<CImplementor> pCConcreteImplementor2 = std::make_shared<CConcreteImplementor2>();

    // CAbstraction *pCRefinedAbstraction1And1 = new CRefinedAbstraction1( pCConcreteImplementor1 );
    std::shared_ptr<CAbstraction> pCRefinedAbstraction1And1 = std::make_shared<CRefinedAbstraction1>( pCConcreteImplementor1 );
    // CAbstraction *pCRefinedAbstraction1And2 = new CRefinedAbstraction1( pCConcreteImplementor2 );
    std::shared_ptr<CAbstraction> pCRefinedAbstraction1And2 = std::make_shared<CRefinedAbstraction1>( pCConcreteImplementor2 );
    // CAbstraction *pCRefinedAbstraction2And1 = new CRefinedAbstraction2( pCConcreteImplementor1 );
    std::shared_ptr<CAbstraction> pCRefinedAbstraction2And1 = std::make_shared<CRefinedAbstraction2>( pCConcreteImplementor1 );
    // CAbstraction *pCRefinedAbstraction2And2 = new CRefinedAbstraction2( pCConcreteImplementor2 );
    std::shared_ptr<CAbstraction> pCRefinedAbstraction2And2 = std::make_shared<CRefinedAbstraction2>( pCConcreteImplementor2 );

    // pCRefinedAbstraction1And1->Operator1();
    pCRefinedAbstraction1And1->Operator1();
    // pCRefinedAbstraction1And2->Operator1();
    pCRefinedAbstraction1And2->Operator1();
    // pCRefinedAbstraction2And1->Operator1();
    pCRefinedAbstraction2And1->Operator1();
    // pCRefinedAbstraction2And2->Operator1();
    pCRefinedAbstraction2And2->Operator1();

    // delete pCRefinedAbstraction1And1;//CRefinedAbstraction1实例里的ConcreteImplementor1实例，已经通过成员变量m_pCImplementor被析构
    // pCRefinedAbstraction1And1 = NULL;
    // delete pCRefinedAbstraction1And2;
    // pCRefinedAbstraction1And2 = NULL;
    // delete pCRefinedAbstraction2And1;//CRefinedAbstraction2实例里的ConcreteImplementor1实例，前面已经析构，此时CRefinedAbstraction2成员变量m_pCImplementor变成野指针，这里再次析构时会core掉
    // pCRefinedAbstraction2And1 = NULL;
    // delete pCRefinedAbstraction2And2;
    // pCRefinedAbstraction2And2 = NULL;

    // delete pCConcreteImplementor1;
    // pCConcreteImplementor1 = NULL;
    // delete pCConcreteImplementor2;
    // pCConcreteImplementor2 = NULL;

    return ;
}