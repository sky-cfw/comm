/**********************************************************************************************************
* Copyright:             Tencent Tech.co,Ltd. 2015-. All rights reserved
* File name:		     测试 等值比较 与 大小比较的耗时情况
* Description:		     
* Author:                sky
* Version:               V1.0
* Date:				     
* History:
                         1. Date: 2019／11/28         2. Author: skycfwu        3. Modification:
**********************************************************************************************************/
#include <iostream>
#include "date_time.h"
using namespace std;
using namespace boss::util;


int main(int argc, char const *argv[])
{
	CDateTime cDateTime;
	int iLoop = 10000000;

	uint64_t ui64TimeStart = cDateTime.GetCurrentTus();
	int i = 0;
	while( i != iLoop )
	{
		i++;
	}
	uint64_t ui64TimeEnd = cDateTime.GetCurrentTus();
	printf( "eq cmp cost:%lu\n", ui64TimeEnd - ui64TimeStart );

	i = 0;
	ui64TimeStart = cDateTime.GetCurrentTus();
	while( i < iLoop )
	{
		if ( i == iLoop )
		{
			break;
		}
		i++;
	}
	ui64TimeEnd = cDateTime.GetCurrentTus();
	printf( "max cmp cost:%lu\n", ui64TimeEnd - ui64TimeStart );

	return 0;
}