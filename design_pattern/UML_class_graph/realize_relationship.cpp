/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     实现关系在C++代码中的体现
* Description:		     
* Author:                sky
* Version:               V1.0
* Date:				  
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/

#include <stdio.h>

/*
实现关系描述的是 UML类图中 元素 接口与类之间的关系
*/

/*
接口特点：
1. 只有方法没有数据
2. 除编译器为类默认生成的5个函数外，所有方法均为纯虚函数
*/
class CInterface
{
public:
    virtual ~CInterface() {};

    virtual int func1() = 0;
    //...
    virtual int func2() = 0;
};

class CImplementation : public CInterface
{
public:
    virtual ~CImplementation() {}

    int func1() { printf("do something1\n"); return 0; }
    int func2() { printf("do something2\n"); return 0; }
};

int main(int argc, char const *argv[])
{
    CInterface *pCIntf = new CImplementation();

    pCIntf->func1();

    return 0;
}
