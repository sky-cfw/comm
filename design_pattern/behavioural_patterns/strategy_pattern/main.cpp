#include <stdio.h>

#include "context.h"

int main(int argc, char const *argv[])
{
    CConcreteStrategy1 *pCS1 = new CConcreteStrategy1();
    CConcreteStrategy2 *pCS2 = new CConcreteStrategy2();

    CContext cContext;
    cContext.DoSomething(pCS1);
    // cContext.DoSomething(pCS2);

    return 0;
}
