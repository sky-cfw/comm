#ifndef CONCRETE_STRATEGY2_H
#define CONCRETE_STRATEGY2_H

#include "strategy.h"

class CConcreteStrategy2 : public CStrategy 
{
public:
    virtual ~CConcreteStrategy2() {}

    //override 
    virtual int DoStrategy();
};

#endif