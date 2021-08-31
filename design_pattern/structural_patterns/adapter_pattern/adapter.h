#ifndef ADAPTER_H
#define ADAPTER_H

#include "target.h"
#include "adaptee.h"

//对象适配器
class CObjectAdapter : public CTarget
{
public:
    CObjectAdapter(CAdaptee *pAdaptee);//对象适配器，通过组合 被适配对象 的方式，更灵活的实现适配
    virtual ~CObjectAdapter();

    int DoSomething1();

private:
    int Transform();

private:
    CAdaptee *m_pAdaptee;
};

//类适配器
class CClassAdapter : public CTarget, public CAdaptee 
{
public:
    virtual ~CClassAdapter();

    int DoSomething1();

private:
    int Transform();
};

#endif