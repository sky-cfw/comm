#include <stdio.h>
#include "client.h"
#include "concrete_decorator.h"
#include "concrete_subject.h"

void CClient::DoSomething()
{
    CSubject *pCConcreteSubject = new CConcreteSubject();
    
    //单独增强功能性需求1
    printf(">>>>>> start to decorator1\n");
    CSubject *pCConcreteDecorator1 = new CConcreteDecorator1( pCConcreteSubject );
    pCConcreteDecorator1->Operator1();

    //单独增强功能性需求2
    printf("\n>>>>>> start to decorator2\n");
    CSubject *pCConcreteDecorator2 = new CConcreteDecorator2( pCConcreteSubject );
    pCConcreteDecorator2->Operator1();

    //同时增强功能性需求1和2
    printf("\n>>>>>> start to decorator1And2\n");
    CSubject *pCConcreteDecorator1And2 = new CConcreteDecorator2( pCConcreteDecorator1 );//此处组合CDecorator1进来即可
    pCConcreteDecorator1And2->Operator1();

    return ;
}