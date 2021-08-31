/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     泛化关系 在C++代码中的表现
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				  
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/

#include <stdio.h>

/*
泛化关系 用于描述类的继承关系，表示的是 ‘is a’ 的关系。
泛化关系 采用空心三角箭头 + 实线表示，空心三角箭头指向基类。
*/
class CBase
{
public:
    virtual ~CBase() {};

    virtual void func1() { printf("base func1\n"); }
};

class CDerived : public CBase
{
public:
    void func1() { printf("derived func1\n"); }
};

int main(int argc, char const *argv[])
{
    CBase *pCBase = new CDerived();

    pCBase->func1();

    return 0;
}
