#ifndef OBSERVER_H
#define OBSERVER_H

#include <stdio.h>
#include "subject.h"

class CSubject;

class CObserver
{
public:
    virtual ~CObserver() {}

    //When you pass a pointer by a non-const reference, you are telling the compiler that you are going to modify that pointer's value. 
    //Your code does not do that, but the compiler thinks that it does, or plans to do it in the future.
    virtual void Update(CSubject * const &pS);
};

#endif
