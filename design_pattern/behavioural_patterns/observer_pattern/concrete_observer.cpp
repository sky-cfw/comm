#include <stdio.h>
#include "concrete_observer.h"


CConcreteObserver::CConcreteObserver()
{

}

CConcreteObserver::~CConcreteObserver()
{

}

void CConcreteObserver::Update(CSubject * const &pS)
{
    //todo 获取目标的状态，根据状态做相应动作
    pS->GetStatus();
    printf("concrete observer update!\n");
}