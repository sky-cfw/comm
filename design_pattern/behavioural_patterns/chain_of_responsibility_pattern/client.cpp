#include "client.h"
#include "concrete_handler.h"

#define RELEASE_RESOURCE(p) \
do {\
    if (p) \
    {      \
        delete p;\
        p = NULL;\
    }\
}while(0);

void CClient::DoSomething()
{
    CHandler *pConcreteHandler1 = new CConcreteHandler1();
    CHandler *pConcreteHandler2 = new CConcreteHandler2();
    CHandler *pConcreteHandler3 = new CConcreteHandler3();

    //构造处理责任链，注意顺序 (这里处理顺序是1->2->3)
    pConcreteHandler1->SetNext( pConcreteHandler2 );//依赖注入/组合/委托
    pConcreteHandler2->SetNext( pConcreteHandler3 );

    stRequest tRequest;
    pConcreteHandler1->DoHandle( tRequest );

    RELEASE_RESOURCE(pConcreteHandler1)
    RELEASE_RESOURCE(pConcreteHandler2)
    RELEASE_RESOURCE(pConcreteHandler3)

    return ;
}