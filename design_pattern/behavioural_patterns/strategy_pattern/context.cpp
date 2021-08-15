#include <stdio.h>
#include "context.h"

int CContext::DoSomething(CStrategy * const & pCS)
{
    pCS->DoStrategy();
    return 0;
}