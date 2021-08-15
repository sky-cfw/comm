#ifndef STRATEGY_H
#define STRATEGY_H

class CStrategy
{
public:
    virtual ~CStrategy() {}

    virtual int DoStrategy();//根据实际使用场景，决定是否定义为纯虚函数
};

#endif