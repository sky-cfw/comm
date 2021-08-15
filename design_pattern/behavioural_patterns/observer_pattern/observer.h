#ifndef OBSERVER_H
#define OBSERVER_H

#include <stdio.h>
#include "subject.h"

class CSubject;

class CObserver
{
public:
    virtual ~CObserver() {}

    //When you pass a pointer by a non-const reference, you are telling the compiler that you are going to modify that pointer's value. 
    //Your code does not do that, but the compiler thinks that it does, or plans to do it in the future.
    //pull模式观察者模式，将观察目标对象回传给观察者； 优点：状态变化时，observer可根据需要取对应数据 缺点：observer与subject耦合度增加
    //push模式观察者模式，定义一个需要回传的信息结构体，update时传给观察者 优点：大大降低了observer与subject的耦合度，缺点：当变化的状态繁多时，observer将收到许多无用的数据
    //参考：https://www.youtube.com/watch?v=REOUgHfjR2w&list=PLGmd9-PCMLhb16ZxeSy00qUsBazXgJyfM&index=20
    virtual void Update(CSubject * const &pS);
};

#endif
