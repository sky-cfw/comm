/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     huffman编码实现
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				  
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#include "huffman.h"
#include "facility.h"

CHuffmanCode::CHuffmanCode()
{

}

CHuffmanCode::~CHuffmanCode()
{

}

/**********************************************************************************************************
* Function:				
* Description:		    打印各个字符的编码
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:					
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
void CHuffmanCode::PrintEnode( stNode *pRoot, std::string sCode )
{
    //递归终止条件 叶子节点
    if ( NULL == pRoot->pLeft || NULL == pRoot->pRight )
    {
        sCode += boss::util::ConvertToString(pRoot->sBit);
        cout << pRoot->cData << ": " << sCode << endl;
        return ;
    }

    sCode += boss::util::ConvertToString(pRoot->sBit);
    PrintEnode(pRoot->pLeft, sCode);
    PrintEnode(pRoot->pRight, sCode);

    return ;
}

/**********************************************************************************************************
* Function:				
* Description:		    Huffman编码
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:					
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
int CHuffmanCode::Encode( char szData[], int iFre[], size_t size )
{
    //初始化需要编码的集合
    cout << "size: " << size << endl;
    for ( int i = size-1; i >= 0; i--/*size_t i = 0; i < size; i++*/ )
    {
        stNode *pNode = new _tNode( szData[i], iFre[i] );
        m_priorityQueue.push( pNode );
    }
    
    //开始遍历优先级队列
    stNode *pRightNode = NULL, *pLeftNode = NULL, *pVirtualNode = NULL;
    while( m_priorityQueue.size() > 1 )
    {
        pRightNode = m_priorityQueue.top();//第一个节点为右节点
        pRightNode->sBit = "1";//右节点编码为1
        cout << pRightNode->cData << " " << pRightNode->iFre << " " << pRightNode->sBit<< endl;
        m_priorityQueue.pop();

        pLeftNode = m_priorityQueue.top();//第二个节点为左节点
        pLeftNode->sBit = "0";//左节点编码为0
        cout << pLeftNode->cData << " " << pLeftNode->iFre << " " << pLeftNode->sBit<< endl;
        m_priorityQueue.pop();

        //构造虚拟节点，并加入到结合中
        pVirtualNode = new _tNode( ' ', (pLeftNode->iFre+pRightNode->iFre) );
        pVirtualNode->pLeft = pLeftNode;
        pVirtualNode->pRight = pRightNode;
        m_priorityQueue.push( pVirtualNode );
    }

    //开始打印各个字符的编码
    std::string sCode = "";
    PrintEnode( m_priorityQueue.top(), sCode );

    return 0;
}

int main(int argc, char const *argv[])
{
    //
    char szData[] = {'e','a','f','h','i','m','n','s','c','d','l','o','p','t','u','x'};
    int iFre[] = {4,3,2,2,2,2,2,2,1,1,1,1,1,1,1,1};

    CHuffmanCode cHuffmanCode;
    cHuffmanCode.Encode( szData, iFre, sizeof(szData)/sizeof(char) );

    return 0;
}
