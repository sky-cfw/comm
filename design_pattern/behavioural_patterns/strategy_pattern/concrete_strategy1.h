#ifndef CONCRETE_STRATEGY1_H
#define CONCRETE_STRATEGY1_H

#include "strategy.h"

class CConcreteStrategy1 : public CStrategy 
{
public:
    virtual ~CConcreteStrategy1() {}

    //override 
    virtual int DoStrategy();
};

#endif