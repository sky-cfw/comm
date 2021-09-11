#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include "handler.h"
class CClient
{
public:
    void DoSomething();

    //责任链模式变种，单独使用一个数组来存储handler链
    void AddHandler( CHandler *&pCHandler );
    void DoHandle( stRequest &tRequest );
    std::vector<CHandler *> m_vecHandler;
};

#endif