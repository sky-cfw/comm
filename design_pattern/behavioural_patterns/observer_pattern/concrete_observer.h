#ifndef CONCRETE_OBSERVER_H
#define CONCRETE_OBSERVER_H

#include "subject.h"

class CConcreteObserver : public CObserver
{
public:
    CConcreteObserver();
    ~CConcreteObserver();

    void Update(CSubject * const &pS);
};

#endif