#include "adapter.h"
#include <stdio.h>

CObjectAdapter::CObjectAdapter( CAdaptee *pAdaptee )
{
    m_pAdaptee = pAdaptee;
}

CObjectAdapter::~CObjectAdapter()
{
    if ( NULL != m_pAdaptee )
    {
        delete m_pAdaptee;
        m_pAdaptee = NULL;
    }
}

int CObjectAdapter::DoSomething1()
{
    m_pAdaptee->DoSomething1();
    Transform();
    printf("output 5V\n");

    return 0;
}

int CObjectAdapter::Transform()
{
    printf("transform 220V to 5V\n");
    
    return 0;
}

CClassAdapter::~CClassAdapter()
{

}

int CClassAdapter::DoSomething1()
{
    CAdaptee::DoSomething1();
    Transform();
    printf("output 5V\n");

    return 0;
}

int CClassAdapter::Transform()
{
    printf("transform 220V to 5V\n");
    
    return 0;
}