#include "concrete_subject.h"

int CConcreteSubject::DoSomething()
{
    printf("concrete subject do something\n");
    Notify();//通知各个观察者
    return 0;
}

int CConcreteSubject::GetStatus()
{
    printf("get concrete subject status\n");
    return 0;
}
