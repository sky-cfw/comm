#ifndef ADAPTEE_H
#define ADAPTEE_H

//需要适配的类(已存在的，与现有使用场景不兼容)
class CAdaptee
{
public:
    virtual ~CAdaptee() {}

    int DoSomething1();//需要适配的方法
};

#endif
