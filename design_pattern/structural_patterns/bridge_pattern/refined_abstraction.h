#ifndef REFINED_ABSTRACTION_H
#define REFINED_ABSTRACTION_H

#include "abstraction.h"

class CRefinedAbstraction1 : public CAbstraction
{
public:
    CRefinedAbstraction1( std::shared_ptr<CImplementor> &pCImplementor );

    void Operator1();
};

class CRefinedAbstraction2 : public CAbstraction
{
public:
    CRefinedAbstraction2( std::shared_ptr<CImplementor> &pCImplementor );

    void Operator1();
};

#endif