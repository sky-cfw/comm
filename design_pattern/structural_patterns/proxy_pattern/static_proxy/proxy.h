#ifndef PROXY_H
#define PROXY_H

#include "subject.h"
#include "proxy.h"

/*
定义代理类，该代理类与真实代理对象实现共同的接口
*/
class CProxy : public CSubject
{
public:
    CProxy( CSubject *&pCSubject );//组合/依赖注入

    void Operator1();
    void Operator2();

private:
    void PreProcess();
    void PostProcess();

private:
    CSubject *m_pCSubject;//通过组合的方式，
};

#endif