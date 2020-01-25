/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     求百分位数
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				     2020/01/10
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "heap.h"
using namespace std;

int main(int argc, char const *argv[])
{
    if ( argc < 2 )
    {
        printf( "./percent <rate>\n" );
        return 0;
    }
    double fRate = atof( argv[1] );    
    cout << "rate:" << fRate << endl;

    char szBuff[1024] = {'\0'};
    int iCnt = 0, iMaxHeapCap = 0;
    CHeap cHeapMax( NULL, 0, CHeap::HEAP_TYPE_MAX );//构造一个最大堆
    CHeap cHeapMin( NULL, 0, CHeap::HEAP_TYPE_MIN );//构造一个最小堆
    while( cin.getline(szBuff, 1024), szBuff != "\n" )
    {
        iCnt++;
        iMaxHeapCap = iCnt * fRate;
        cout << "szBuff=" << szBuff << ", cnt=" << iCnt << ", maxHeapCap=" << iMaxHeapCap << ", maxHeapSize=" << cHeapMax.size() << endl;
        //注意这里 仅仅控制大堆和小堆的个数 来求百分位数的写法是错误的，比如现在有10个数，0，1，2，3，4，5，6，7，8，9，求9分位数
        //按照以下写法，如果数据是倒序来的，则大顶堆的堆顶元素为9，小顶堆的堆顶元素为0，此时大顶堆的堆顶元素并不是我们想要的百分位数。
        //正确的写法是：先建立大顶堆(或者小顶堆)，如果新来的元素小于等于大顶堆则加入大顶堆，否则加入小顶堆。然后再根据大顶堆的个数来决定需要挪动堆顶元素至小顶堆 还是 小顶堆的堆顶元素挪动至大顶堆。
        //比如现在有10个数，0，1，2，3，4，5，6，7，8，9，元素输入顺序为逆序，求9分位数。 如果先建立大顶堆当最后一个元素加入大顶堆后，此时大顶堆元素个数为10，多于预定元素个数9，于是将堆顶元素9挪动至小顶堆
        // if ( cHeapMax.size() < iMaxHeapCap )
        // {
        //     cHeapMax.push( atoi(szBuff) );
        //     cout << "max heap top element:" << cHeapMax.front() << endl;
        // }
        // else
        // {
        //     cHeapMin.push( atoi(szBuff) );
        // }
        
        //先建立大顶堆
        int a = atoi( szBuff );
        if ( 0 == cHeapMax.size()
        || a <= cHeapMax.front() )
        {
            cHeapMax.push( a );
            if ( cHeapMax.size() > iMaxHeapCap )
            {
                cHeapMin.push( cHeapMax.front() );
                cHeapMax.pop();
            }
        }
        else
        {
            cHeapMin.push( a );
            if ( cHeapMax.size() < iMaxHeapCap )
            {
                cHeapMax.push( cHeapMin.front() );
                cHeapMin.pop();
            }
        }

        cout << "max heap top element:" << cHeapMax.front() << ", maxHeapSize=" << cHeapMax.size() << endl;
        cout << "min heap top element:" << cHeapMin.front() << ", minHeapSize=" << cHeapMin.size() << endl << endl;
    }

    return 0;
}



