#ifndef CONCRETE_SUBJECT_H
#define CONCRETE_SUBJECT_H

#include "subject.h"

/*
具体的被装饰类
*/
class CConcreteSubject : public CSubject
{
public:
    virtual ~CConcreteSubject();

    void Operator1();
};

#endif