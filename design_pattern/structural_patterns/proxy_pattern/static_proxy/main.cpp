/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     结构型设计模式之静态代理设计模式 
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				  
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#include <stdio.h>
#include "proxy.h"
#include "real_subject.h"

int main(int argc, char const *argv[])
{
    CSubject *pCSubject = new CRealSubject();
    
    CProxy *pCProxy = new CProxy( pCSubject );//依赖注入
    pCProxy->Operator1();
    pCProxy->Operator2();

    delete pCProxy;
    pCProxy = NULL;

    return 0;
}
