#include <stdio.h>
#include "concrete_handler.h"

CConcreteHandler1::~CConcreteHandler1()
{

}

void CConcreteHandler1::HandleRequest( stRequest &tRequest )
{
    printf("concrete handler1 handle request\n");

    return ;
}

CConcreteHandler2::~CConcreteHandler2()
{

}

void CConcreteHandler2::HandleRequest( stRequest &tRequest )
{
    printf("concrete handler2 handle request\n");

    return ;
}

CConcreteHandler3::~CConcreteHandler3()
{

}

void CConcreteHandler3::HandleRequest( stRequest &tRequest )
{
    printf("concrete handler3 handle request\n");

    return ;
}