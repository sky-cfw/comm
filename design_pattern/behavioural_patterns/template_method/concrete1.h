#ifndef CONCRETE1_H
#define CONCRETE1_H

#include "abstract.h"

class CConcrete1 : public CAbstract
{
public:
    virtual ~CConcrete1() {}

    //override step2
    virtual int Step2();
};

#endif