#include <stdlib.h>
#include "abstraction.h"

CAbstraction::CAbstraction( std::shared_ptr<CImplementor> &pCImplementor ):
m_pCImplementor(pCImplementor)//unique指针同一时刻，只能有一个指向对象
{

}

CAbstraction::~CAbstraction()
{
    
}