#include "context.h"
#include "adapter.h"
#include "adaptee.h"
#include <stdio.h>

int CContext::DoSomething()
{
    CAdapter *pAdapter = new CAdapter( new CAdaptee() );

    pAdapter->DoSomething2();
    
    return 0;
}