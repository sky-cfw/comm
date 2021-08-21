#include <stdio.h>
#include "concrete1.h"
#include "concrete2.h"


int main(int argc, char const *argv[])
{
    /* code */
    CAbstract *pAbstract1 = new CConcrete1();
    CAbstract *pAbstract2 = new CConcrete1();

    pAbstract1->DoSomething();
    pAbstract2->DoSomething();

    return 0;
}