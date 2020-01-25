/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     广度优先搜索
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				     2020/01/18
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <stack>

using namespace std;

//无向图
class CIndirectGraph
{
public:
    //是使用std::vector<std::list<int> > 还是std::list<std::list<int> >？
    //因为不会涉及频繁的删除顶点，因此这里选择std::vector<std::list<int> >
    std::map<int, std::list<int> > m_mapAdjList;//邻接表，用于存放每个顶点及其关联的顶点

public:
    CIndirectGraph();
    virtual ~CIndirectGraph();

    void AddEdge(const int &a, const int &b);//给两个顶点添加边
    size_t GetVertexSize();//获取无向图顶点数
};

//广度优先搜索
class CBfs
{
public:
    CIndirectGraph m_cIndirectGraph;//无向图

public:
    CBfs(/* args */);
    virtual ~CBfs();
    void PrintPath( const std::map<int, int> &mapPreVertex, const int &a, const int &b );
    void BFSearch(const int &a, const int &b);
};

