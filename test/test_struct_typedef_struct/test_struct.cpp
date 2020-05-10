/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     测试struct和typedef struct的区别
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				  
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

struct student
{
    int iAge;
    float fScore;

    student( const int &_iAge, const float &_fScore ):
    iAge(_iAge),
    fScore(_fScore)
    {

    }
};

int main()
{
    student a(30, 99.99);
    
    cout << a.iAge << " " << a.fScore << endl;

    return 0;
}