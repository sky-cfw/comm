#include <stdio.h>
#include "client.h"
#include "real_subject.h"
#include "proxy.h"

void CClient::DoSomething()
{
    CSubject *pCSubject = new CRealSubject();
    CProxy *pCProxy = new CProxy( pCSubject );//依赖注入

    pCProxy->Operator1();
    pCProxy->Operator2();

    delete pCSubject;
    pCSubject = NULL;

    delete pCProxy;
    pCProxy = NULL;

    return ;
}