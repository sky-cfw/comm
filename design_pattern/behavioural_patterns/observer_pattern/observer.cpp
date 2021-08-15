#include "observer.h"

void CObserver::Update(CSubject * const &pS)
{
    //todo
    pS->GetStatus();
    printf("observer update!\n");
}