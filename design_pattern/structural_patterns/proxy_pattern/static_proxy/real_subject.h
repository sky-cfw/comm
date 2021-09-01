#ifndef REAL_SUBJECT_H
#define REAL_SUBJECT_H

#include "subject.h"

class CRealSubject : public CSubject
{
public:
    virtual ~CRealSubject();

    void Operator1();
    void Operator2();
};

#endif