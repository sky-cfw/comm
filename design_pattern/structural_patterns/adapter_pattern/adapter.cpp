#include "adapter.h"
#include <stdio.h>

CAdapter::CAdapter( CAdaptee *pAdaptee )
{
    m_pAdaptee = pAdaptee;
}

CAdapter::~CAdapter()
{
    if ( NULL != m_pAdaptee )
    {
        delete m_pAdaptee;
        m_pAdaptee = NULL;
    }
}

int CAdapter::DoSomething2()
{
    m_pAdaptee->DoSomething1();
    Transform();
    printf("output 5V\n");

    return 0;
}

int CAdapter::Transform()
{
    printf("transform 220V to 5V\n");
    
    return 0;
}