#ifndef CONCRETE_SUBJECT_H
#define CONCRETE_SUBJECT_H

#include "subject.h"

class CConcreteSubject : public CSubject 
{
public:
    virtual ~CConcreteSubject() {}

    int DoSomething();
    int GetStatus();//获取状态
};


#endif