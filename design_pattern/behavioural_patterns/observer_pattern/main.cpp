#include <stdio.h>
#include "concrete_subject.h"
#include "concrete_observer.h"

int main(int argc, char const *argv[])
{
    CObserver *pO1 = new CConcreteObserver();
    CSubject *pS = new CConcreteSubject();

    pS->Attach(pO1);
    pS->DoSomething();

    return 0;
}
