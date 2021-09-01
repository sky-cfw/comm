#ifndef SUBJECT_H
#define SUBJECT_H

//定义需要被代理的接口
class CSubject
{
public:
    virtual ~CSubject() {}

    virtual void Operator1() = 0;//需要被代理的方法
    //......
    virtual void Operator2() = 0;//
};

#endif //