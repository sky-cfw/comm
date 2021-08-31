#include "client.h"
#include "adapter.h"
#include "adaptee.h"
#include <stdio.h>

int CClient::DoSomething()
{
    CObjectAdapter *pObjectAdapter = new CObjectAdapter( new CAdaptee() );

    pObjectAdapter->DoSomething1();
    
    CClassAdapter cClassAdapter;
    cClassAdapter.DoSomething1();
    
    return 0;
}