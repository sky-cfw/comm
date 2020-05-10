/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     test_struct.c
* Description:		     测试struct和typedef struct的区别 
* Author:                sky
* Version:               V1.0
* Date:				     2020/05/10
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#include <stdio.h>

/*
struct student
{
    //注意：纯c语言没有构造函数的概念
    int iAge;
    float fScore;
};

int main()
{
    student a = {30, 99.99};//C语言没有构造函数的概念，可使用初始化列表来实现成员初始化

    printf("%d, %f\n", a.iAge, a.fScore);

    return 0;
}
*/



struct student
{
    //注意：纯c语言没有构造函数的概念
    int iAge;
    float fScore;
};

int main()
{
    struct student a = {30, 99.99};//C语言没有构造函数的概念，可使用初始化列表来实现成员初始化

    printf("%d, %.2f\n", a.iAge, a.fScore);

    return 0;
}