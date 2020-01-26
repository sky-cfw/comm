/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     深度优先搜索
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				     2020/01/25
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#include "dfs.h"

CIndirectGraph::CIndirectGraph()
{

}

CIndirectGraph::~CIndirectGraph()
{
    
}

/**********************************************************************************************************
* Function:				
* Description:		   无向图给两个顶点添加边
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:					
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
void CIndirectGraph::AddEdge(const int &a, const int &b)
{
    m_mapAdjList[a].push_back( b );
    m_mapAdjList[b].push_back( a );
}

/**********************************************************************************************************
* Function:				
* Description:		    无向图顶点个数
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:					
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
size_t CIndirectGraph::GetVertexSize()
{
    return m_mapAdjList.size();
}

CDfs::CDfs()
{

}
CDfs::~CDfs()
{

}

/**********************************************************************************************************
* Function:				
* Description:		    打印访问路径
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:					
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
void CDfs::PrintPath( std::stack<int> &stackPath )
{
    cout << endl;
    while( !stackPath.empty() )
    {
        cout << stackPath.top() << endl;
        stackPath.pop();
    }

    return ;
}

/**********************************************************************************************************
* Function:				
* Description:		    深度优先搜索
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:				关键点：
                        1.怎么存储图？ ====> 邻接表
                        2.怎么防止同一个顶点被访问多次？ ====> 每访问一个顶点，则标记该顶点
                        3.发现无路可走时，如何返回到上一个顶点 ====> 借助栈来存储访问路径，当无路可走时，弹出栈顶顶点
                        4.如何打印访问路径？===> 直接打印存储访问路径的栈即可
                        5.搜索停止条件是什么？ ====> 所有顶点已访问 或者 找到顶点b
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
void CDfs::DFSearch(const int &a, const int &b)
{
    bool bIsFind = false;//标记是否找到
    std::stack<int> stackPath;//存储访问路径
    std::set<int> setVisited;//存储已访问过的顶点
    int iCurrentVertex = a;//记录当前范围的顶点

    stackPath.push(iCurrentVertex);
    setVisited.insert(iCurrentVertex);
    cout << "search process: " << endl << iCurrentVertex << endl;
    do
    {
        std::list<int>::iterator itr = m_cIndirectGraph.m_mapAdjList[iCurrentVertex].begin();
        for ( ; itr != m_cIndirectGraph.m_mapAdjList[iCurrentVertex].end(); itr++ )
        {
            //找到顶点b，结束
            if ( b == (*itr) )
            {
                cout << "find " << b << endl;
                bIsFind = true;
                stackPath.push(b);
                break;
            }
            
            //有没有访问的顶点，加入访问路径，打标
            if ( 0 == setVisited.count( *itr ) )
            {
                cout << *itr << endl;
                iCurrentVertex = (*itr);
                stackPath.push(iCurrentVertex);
                setVisited.insert(iCurrentVertex);
                break;
            }
        }

        //当前顶点走不通，回退到上一个顶点
        if ( m_cIndirectGraph.m_mapAdjList[iCurrentVertex].end() == itr )
        {
            stackPath.pop();
            iCurrentVertex = stackPath.top();
            cout << "back to " << iCurrentVertex << endl;
        }
        
        if ( bIsFind )
        {
            break;
        }

    } while ( m_cIndirectGraph.GetVertexSize() != setVisited.size() );
    
    PrintPath( stackPath );

    return ;
}


int main(int argc, char const *argv[])
{
    //构造无向图
    CDfs cDfs;
    cDfs.m_cIndirectGraph.AddEdge(1, 2);
    cDfs.m_cIndirectGraph.AddEdge(1, 4);
    cDfs.m_cIndirectGraph.AddEdge(2, 5);
    cDfs.m_cIndirectGraph.AddEdge(2, 3);
    cDfs.m_cIndirectGraph.AddEdge(4, 5);
    cDfs.m_cIndirectGraph.AddEdge(5, 6);
    cDfs.m_cIndirectGraph.AddEdge(5, 7);
    cDfs.m_cIndirectGraph.AddEdge(3, 6);
    cDfs.m_cIndirectGraph.AddEdge(6, 8);
    cDfs.m_cIndirectGraph.AddEdge(8, 7);

    cDfs.DFSearch( 1, 7 );

    return 0;
}
