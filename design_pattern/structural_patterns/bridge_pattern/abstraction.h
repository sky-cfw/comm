#ifndef ABSTRACTION_H
#define ABSTRACTION_H

#include <memory>
#include "implementor.h"

/*
定义抽象类的接口
*/
class CAbstraction
{
public:
    CAbstraction(std::shared_ptr<CImplementor> &pCImplementor);
    virtual ~CAbstraction();

    virtual void Operator1() = 0;

//访问属性为 protected，便于子类访问，否则提供一个公有方法也行。
protected:
    // std::unique_ptr<CImplementor> m_pCImplementor;//unique指针同一时刻，同一时刻只能有1个指向对象
    std::shared_ptr<CImplementor> m_pCImplementor;
    //CImplementor *m_pCImplementor;
};

#endif