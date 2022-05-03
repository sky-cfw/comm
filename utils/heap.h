/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     堆实现
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				     2020/01/08
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#ifndef HEAP_H
#define HEAP_H

#include <vector>

class CHeap
{
public:
    //堆类型
    enum eHeapType
    {
        HEAP_TYPE_MIN = 1,//最小堆
        HEAP_TYPE_MAX = 2//最大堆
    };

private:
    std::vector<int> m_vecBuff;//由于堆是一个完全二叉树，非常适合使用数组来存放 
    int m_iHeapType;//堆类型
    int m_iCnt;//堆中元素个数

public:
    CHeap();
    CHeap( const int a[], const int &size, const int &type );
    virtual ~CHeap();

    void push( const int &k );//往堆中插入一个元素
    void pop();//删除堆顶元素
    int front();//返回堆顶元素
    int size();//返回堆中元素个数
private:
    void heapify();//堆化
};

#endif