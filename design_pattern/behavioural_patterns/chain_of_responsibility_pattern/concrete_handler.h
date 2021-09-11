#ifndef CONCRETE_HANDLER_H
#define CONCRETE_HANDLER_H

#include "handler.h"

class CConcreteHandler1 : public CHandler 
{
public:
    virtual ~CConcreteHandler1();

    void HandleRequest(stRequest &tRequest);
};

class CConcreteHandler2 : public CHandler 
{
public:
    virtual ~CConcreteHandler2();

    void HandleRequest(stRequest &tRequest);
};

class CConcreteHandler3 : public CHandler 
{
public:
    virtual ~CConcreteHandler3();

    void HandleRequest(stRequest &tRequest);
};

#endif