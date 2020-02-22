/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     贪心算法思想 之 huffman编码
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				     2020/02/08
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <iostream>
#include <queue>

using namespace std;

//huffman树节点
typedef struct _tNode
{
    char cData;//节点值
    int iFre;//节点频率
    _tNode *pLeft;//left指针
    _tNode *pRight;//right指针
    std::string sBit;//二进制编码
    //bool bLeaf;//是否叶子节点

    _tNode( const char &data, const int &fre/*, _tNode *&left, _tNode *&right, const bool &bit, const bool &leaf*/ ):
    cData(data),
    iFre(fre),
    pLeft(NULL),
    pRight(NULL),
    sBit("")/*,
    bLeaf(leaf)*/
    {

    }

    void clear()
    {
        cData = 0;
        iFre = 0;
        pLeft = NULL;
        pRight = NULL;
        sBit = "";
        //bLeaf = 0;
    }

    // //override < 操作符
    // bool operator < ( const _tNode *&pRight ) const
    // {
    //     return this->iFre < pRight->iFre;
    // }
}stNode;

// For comparison of 
// two heap nodes (needed in min heap) 
struct compare { 
    bool operator()(stNode* l, stNode* r) 
    { 
        return (l->iFre > r->iFre); 
    } 
}; 
class CHuffmanCode
{
public:
    CHuffmanCode();
    virtual ~CHuffmanCode();

    int Encode( char szData[], int iFre[], size_t size );
    void PrintEnode( stNode *pRoot, std::string sEncode );
private:
    std::priority_queue<stNode *, std::vector<stNode *>, compare > m_priorityQueue;//优先级队列 存放需要编码的节点
};


#endif
