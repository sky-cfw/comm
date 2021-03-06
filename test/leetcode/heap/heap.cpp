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
#include "heap.h"
#include <iostream>
using namespace std;

CHeap::CHeap():
m_iHeapType(HEAP_TYPE_MAX),
m_iCnt(0)
{

}

CHeap::CHeap( const int a[], const int &size, const int &type ):
m_iHeapType(type),
m_iCnt(0)
{
    m_iHeapType = type;

    for( int i = 0; i < size; i++ )
    {
        push( a[i] );
    }
}

CHeap::~CHeap()
{
}

/**********************************************************************************************************
* Function:				
* Description:		    往堆中插入一个元素，插入后，仍维持堆的特性不变
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:					
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
void CHeap::push( const int &k )
{
    //先放入完全二叉树的尾部
    if ( 0 == m_iCnt && 0 == m_vecBuff.size() )
    {
        m_vecBuff.push_back(-999);//第一个位置元素废弃，这里填充一个元素   
    }
    m_vecBuff.push_back(k);//不能用push_back，否则删除堆顶元素后，下次再添加元素时，导致删除的元素仍存在
    ++m_iCnt;

    //开始向上堆化
    int i = m_iCnt;
    while( i/2 > 0 )
    {
        if ( (HEAP_TYPE_MAX == m_iHeapType && m_vecBuff[i] > m_vecBuff[i/2])
        || (HEAP_TYPE_MIN == m_iHeapType && m_vecBuff[i] < m_vecBuff[i/2]) )
        {
            std::swap( m_vecBuff[i], m_vecBuff[i/2] );
        }
        i = i/2;
    }
}

/**********************************************************************************************************
* Function:				
* Description:		    删除堆顶元素
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:					
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
void CHeap::pop()
{
    //
    if ( 0 == m_iCnt )
    {
        return ;
    }
    
    //交换堆顶与尾部元素
    std::swap( m_vecBuff[1], m_vecBuff[m_iCnt] );
    --m_iCnt;
    m_vecBuff.pop_back();

    //向下堆化
    heapify();

    return ;
}

/**********************************************************************************************************
* Function:				
* Description:		    堆化
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:					
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
void CHeap::heapify()
{
    int i = 1, iTmp = i;
    while( 1 )
    {
        if ( (2*i) <= m_iCnt
        && ( ( HEAP_TYPE_MAX == m_iHeapType && m_vecBuff[iTmp] < m_vecBuff[2*i] )//大顶堆
            || ( HEAP_TYPE_MIN == m_iHeapType && m_vecBuff[iTmp] > m_vecBuff[2*i] ) ) )//小顶堆
        {
            iTmp = 2*i;
        }
        
        if ( (2*i+1) <= m_iCnt
        && ( (HEAP_TYPE_MAX == m_iHeapType && m_vecBuff[iTmp] < m_vecBuff[2*i+1] )
            || (HEAP_TYPE_MIN == m_iHeapType && m_vecBuff[iTmp] > m_vecBuff[2*i+1] ) ) )
        {
            iTmp = 2*i+1;
        }

        if ( iTmp == i )
        {
            break;
        }

        std::swap( m_vecBuff[i], m_vecBuff[iTmp] );
        i = iTmp;
    }

    return ;
}

/**********************************************************************************************************
* Function:				
* Description:		    返回堆顶元素
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:					
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
int CHeap::front()
{
    if ( m_iCnt > 0 )
    {
        return m_vecBuff[1];
    }
    
    return -1;
}

/**********************************************************************************************************
* Function:				
* Description:		    返回堆中元素个数
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:					
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
int CHeap::size()
{
    return m_iCnt;
}

// int main(int argc, char const *argv[])
// {
//     int a[6] = {1,4,3,9,2,7};
//     CHeap cHeap( a, 6, CHeap::HEAP_TYPE_MAX );//建堆，时间复杂度O(logn)

//     cHeap.push( 5 );

//     //堆排序，堆顶元素出堆
//     while( 0 != cHeap.size() )
//     {
//         cout << cHeap.front() << endl;
//         cHeap.pop();//堆化，时间复杂度O(logn)
//     }

//     return 0;
// }
