#ifndef CONCRETE2_H
#define CONCRETE2_H

#include "abstract.h"

class CConcrete2 : public CAbstract
{
public:
    virtual ~CConcrete2() {}

    //override step3
    virtual int StepN();
};

#endif