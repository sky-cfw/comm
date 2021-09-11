#ifndef HANDLER_H
#define HANDLER_H

#include <string>

typedef struct _tRequest
{
    std::string sReqMember1;
    std::string sReqMember2;
}stRequest;

class CHandler
{
public:
    virtual ~CHandler() {}

    void DoHandle(stRequest &tRequest);//这里使用模版模式，定义执行步骤，主要是为了防止子类在处理请求时，忘记转发给链上的下一个handler对象
    virtual void HandleRequest(stRequest &tRequest) = 0;
    virtual void SetNext( CHandler *&pCHandler );

private:
    CHandler *m_pCHandler;
};

#endif