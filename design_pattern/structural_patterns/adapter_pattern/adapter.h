#ifndef ADAPTER_H
#define ADAPTER_H

#include "target.h"
#include "adaptee.h"

class CAdapter : public CTarget
{
public:
    CAdapter(CAdaptee *pAdaptee);
    virtual ~CAdapter();

    int DoSomething2();

private:
    int Transform();

private:
    CAdaptee *m_pAdaptee;
};

#endif