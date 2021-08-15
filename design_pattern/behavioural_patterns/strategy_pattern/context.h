#ifndef CONTEXT_H
#define CONTEXT_H

#include "concrete_strategy1.h"
#include "concrete_strategy2.h"

//定义使用算法的对象
class CContext
{
public:
    int DoSomething( CStrategy * const & pCS );
};

#endif //