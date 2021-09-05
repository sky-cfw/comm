#ifndef IMPLEMENTOR_H
#define IMPLEMENTOR_H

/*
定义实现类的接口

注意 实现类的接口不一定与抽象类的接口一致，实现类定义的接口是更细粒度的基本操作，抽象类的定义的接口是更高层级的抽象接口
比如：告警消息的推送，抽象类是推送类，定义的接口为 推送，扩展抽象类之后是 具体渠道推送类，比如：微信推送类、邮箱推送类、电话推送类等。实现类是推送的告警等级，比如：提示、严重等
*/
class CImplementor
{
public:
    virtual ~CImplementor() {}

    virtual void Method1() = 0;//
};

#endif