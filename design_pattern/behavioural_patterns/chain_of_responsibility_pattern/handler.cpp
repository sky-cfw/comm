#include "handler.h"

void CHandler::DoHandle( stRequest &tRequest )
{
    this->HandleRequest( tRequest );

    //将请求转发给链上的下一个handler对象
    if ( NULL != m_pCHandler )
        m_pCHandler->DoHandle( tRequest );
    
    return ;
}

void CHandler::SetNext(CHandler *&pCHandler)
{
    m_pCHandler = pCHandler;

    return ;
}