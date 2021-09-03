#include <stdio.h>
#include "client.h"
#include "decorator.h"
#include "concrete_subject.h"

void CClient::DoSomething()
{
    CSubject *pCConcreteSubject = new CConcreteSubject();
    
    //单独增强功能性需求1
    printf(">>>>>> start to decorator1\n");
    CSubject *pCDecorator1 = new CDecorator1( pCConcreteSubject );
    pCDecorator1->Operator1();

    //单独增强功能性需求2
    printf(">>>>>> start to decorator2\n");
    CSubject *pCDecorator2 = new CDecorator2( pCConcreteSubject );
    pCDecorator2->Operator1();

    //同时增强功能性需求1和2
    printf(">>>>>> start to decorator1 & decorator2\n");
    CSubject *pCDecorator1And2 = new CDecorator2( pCDecorator1 );//此处组合CDecorator1进来即可
    pCDecorator1And2->Operator1();

    return ;
}