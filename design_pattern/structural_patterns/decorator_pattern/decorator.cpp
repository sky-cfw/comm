#include <stdlib.h>
#include "decorator.h"

CDecorator::CDecorator( CSubject *&pCSubject ):
m_pCSubject( pCSubject )
{

}

CDecorator::~CDecorator()
{
    if ( m_pCSubject != NULL )
    {
        delete m_pCSubject;
        m_pCSubject = NULL;
    }
}

void CDecorator::Operator1()
{
    if ( m_pCSubject != NULL )
        m_pCSubject->Operator1();
    
    return ;
}