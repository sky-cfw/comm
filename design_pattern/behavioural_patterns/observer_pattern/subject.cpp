#include "subject.h"

void CSubject::Attach( CObserver *&pO )
{
    m_listObserver.push_back(pO);
}

void CSubject::Detach( CObserver *&pO )
{
    m_listObserver.remove(pO);
}

void CSubject::Notify()
{
    for (auto &pO : m_listObserver)
    {
        pO->Update(this);//把自己(观察目标)回传给观察者，让观察者获取观察目标的相关属性做相应动作
    }
}

int CSubject::DoSomething()
{
    printf("subject do something\n");
    Notify();//通知各个观察者
    return 0;
}

int CSubject::GetStatus()
{
    printf("get subject status\n");
    return 0;
}