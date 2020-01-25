/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     广度优先搜索实现
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				     2020/01/20
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#include "bfs.h"

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


CBfs::CBfs(/* args */)
{
}

CBfs::~CBfs()
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
void CBfs::PrintPath( const std::map<int, int> &mapPreVertex, const int &a, const int &b )
{
    /*
    if ( a == b )
    {
        cout << "path:" << endl << a << endl;
        return ;
    }
    
    std::map<int , int>::const_iterator itr = mapPreVertex.find( b );
    //cout << "a: " << a << ", itr->second: " << itr->second << endl;
    PrintPath(mapPreVertex, a, itr->second);
    cout << b << endl;
    */
    std::stack<int> stackPath;
    stackPath.push( b );

    std::map<int, int>::const_iterator itr = mapPreVertex.find( b );
    while( itr->second != a )
    {
        stackPath.push( itr->second );
        itr = mapPreVertex.find( itr->second );
    }
    stackPath.push(a);

    while( !stackPath.empty() )
    {
        cout << stackPath.top() << endl;
        stackPath.pop();
    }

    return ;
}

/**********************************************************************************************************
* Function:				
* Description:		    广度优先搜索
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:				关键点：
                        1.怎么存储图？ ===> 邻接表
                        2.怎么逐层向外访问？ ====> 借助队列
                        3.怎么存储和打印访问路径 ====> 每访问一个顶点时，保存当前顶点的前一个顶点。这样当访问到目标顶点后，
                        依次逆向打印即可
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
void CBfs::BFSearch( const int &a, const int &b )
{
    if ( a == b )
    {
        return ;
    }

    std::queue<int> q;//借助队列
    std::map<int, bool> mapVisit;//标记节点是否已经被访问过
    std::map<int, int> mapPreVertex;//存储当前顶点的上一顶点

    //搜索起始顶点入队列
    q.push( a );
    mapVisit[a] = true;

    //开始搜索
    bool bIsFind = false;
    int iVertext = 0;
    while ( !q.empty() )
    {
        iVertext = q.front();
        q.pop();

        //未访问的相连顶点入队列
        std::list<int>::iterator itr = m_cIndirectGraph.m_mapAdjList[iVertext].begin();
        for ( ; itr != m_cIndirectGraph.m_mapAdjList[iVertext].end(); itr++ )
        {
            if ( b == *itr )
            {
                mapPreVertex[*itr] = iVertext;
                bIsFind = true;
                break;
            }

            if ( !mapVisit[*itr] )
            {
                mapPreVertex[*itr] = iVertext;
                cout << "vertex: " << iVertext << ", follow: " << (*itr) << endl;
                mapVisit[*itr] = true;
                q.push( *itr );
            }
        }

        if ( bIsFind )
        {
            break;
        }
    }
    
    cout << "mapPreVertex.size: " << mapPreVertex.size() << endl;
    PrintPath( mapPreVertex, a, b );
    return ;
}

int main(int argc, char const *argv[])
{
    //构造无向图
    CBfs cBfs;
    cBfs.m_cIndirectGraph.AddEdge(0, 1);
    cBfs.m_cIndirectGraph.AddEdge(0, 4);
    cBfs.m_cIndirectGraph.AddEdge(1, 2);
    cBfs.m_cIndirectGraph.AddEdge(1, 5);
    cBfs.m_cIndirectGraph.AddEdge(4, 5);
    cBfs.m_cIndirectGraph.AddEdge(4, 7);
    cBfs.m_cIndirectGraph.AddEdge(5, 8);
    cBfs.m_cIndirectGraph.AddEdge(5, 6);
    cBfs.m_cIndirectGraph.AddEdge(8, 7);
    cBfs.m_cIndirectGraph.AddEdge(8, 9);
    cBfs.m_cIndirectGraph.AddEdge(6, 9);
    cBfs.m_cIndirectGraph.AddEdge(6, 2);
    cBfs.m_cIndirectGraph.AddEdge(2, 3);
    cout << cBfs.m_cIndirectGraph.GetVertexSize() << endl;

    cBfs.BFSearch( 0, 9 );

    return 0;
}
