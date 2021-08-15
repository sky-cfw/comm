#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>
#include "observer.h"

class CObserver;

class CSubject
{
public:
    virtual ~CSubject() {}

    virtual void Attach( CObserver *&pO );//注册观察者
    virtual void Detach( CObserver *&pO );//移除观察者

    virtual int DoSomething();
    virtual int GetStatus();//获取状态

protected:
    virtual void Notify();//通知观察者

public:
    std::list<CObserver *> m_listObserver;//观察者列表
};


#endif