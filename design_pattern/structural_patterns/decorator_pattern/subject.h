#ifndef SUBJECT_H
#define SUBJECT_H

/*
定义被装饰的目标接口
*/

class CSubject
{
public:
    virtual ~CSubject() {}

    virtual void Operator1() = 0;//被装饰的目标接口
};

#endif