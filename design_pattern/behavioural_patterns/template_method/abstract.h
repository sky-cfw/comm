#ifndef ABSTRACT_H
#define ABSTRACT_H

class CAbstract
{
public:
    virtual ~CAbstract() {}
    
    //定义算法执行框架
    int DoSomething();

    virtual int Start();
    virtual int Step1();//执行步骤1 可延迟到子类
    virtual int Step2();//执行步骤2
    //....
    virtual int StepN();//执行步骤N
    virtual int End();
};

#endif