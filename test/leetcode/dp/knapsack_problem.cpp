/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     动态规划之0/1背包问题
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				  
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
/*
问题1：
对于一组不同重量、不可分隔的物品，我们选择将某些装入背包，在满足背包最大重量限制的前提下，背包可装入物品的最大重量为多少？

问题2： 
对于一组不同重量、不同价值、不可分隔的物品，我们选择将某些装入背包，在满足背包最大重量限制的前提下，背包可装入物品的最大总价值为多少？
*/

#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <cstring>
using namespace std;

int w[] = {2,2,3,4,6};//物品重量列表
int v[] = {9,2,7,3,3};//物品对应的价值列表
int wm = 9;//背包容量
int maxV = INT_MIN;//背包总所装物品的最大价值

//--------------- 回溯算法 ---------------
//i:准备放入第i个物品(物品编号从0开始)
//n:物品个数
//cw:决策第i个物品是否放入前，当前背包总重量
//cv:决策第i个物品是否放入前，当前背包总物品总价值
void func(int i, int n, int cw, int cv)
{
    //如果背包已满，或者 物品已考察完
    if (cw == wm//注意这里不会出现>w的情况
    || n == i )
    {
        if ( cv > maxV )
        {
            maxV = cv;
        }
        return ;
    }

    //不放入第i个物品
    func( i+1, n, cw, cv );
    if ( cw + w[i] <= wm )//小于背包重要的情况下，放入第i个物品
    {
        func( i+1, n, cw+w[i], cv+v[i] );
    }
}

//------------- 动态规划 -------------
//关键点：1.怎么定义状态
//n:物品总个数
//w:物品重量列表
//v:物品价值列表，同w一一对应
//wm:背包可容纳的最大重量
void f(int n, int wm, int *w, int *v)
{
    //pState[决策阶段][物品重量] = 物品价值
    int **pState = new int*[n];
    for ( int i = 0; i < n ; i++ )
    {
        pState[i] = new int[wm+1];
        memset( pState[i], -1, (wm+1)*sizeof(int) );//这里要初始化为<0的数，否则区分不出来放还是没有放(比如：初始z h不放为0)
    }

    //多阶段决策最优模型 - 初始化状态 ===> 第一次决策
    pState[0][0] = 0;//不放第一个物品
    if ( w[0] <= wm )
    {
        pState[0][w[0]] = v[0];//放第一物品
    }

    //动态规划状态转移
    for ( int i = 1; i < n; i++ )//决策阶段递推
    {
        for ( int j = 0; j <= wm; j++ )//不放第i个物品
        {
            if ( pState[i-1][j] >= 0 )//上一决策阶段之后的状态
            {
                pState[i][j] = pState[i-i][j];
                printf("pState[%d][%d] = %d 不放====> pState[%d][%d] = %d\n", i-1, j, pState[i-1][j], i, j, pState[i][j]);
            }
            //下一决策状态只依赖于上一决策之后的状态
        }
        
        for ( int j = 0; j <= wm; j++ )//放第i个物品
        {
            if ( pState[i-1][j] >= 0 && j + w[i] <= wm )//上一决策阶段之后的状态
            {
                int val1 = pState[i-1][j] + v[i];//本处存放后的value值
                int val2 = pState[i][j+w[i]];//本次存放后的状态可能和本处决策阶段不放物品的状态重合，这里要取最大值
                pState[i][j+w[i]] = val1 > val2 ? val1 : val2;
                printf("pState[%d][%d] = %d 放====> pState[%d][%d] = %d\n", i-1, j, pState[i-1][j], i, j+w[i], pState[i][j+w[i]]);
            }
            
        }
    }

    //输出最大值
    maxV = INT_MIN; 
    for ( int i = wm; i >= 0; i-- )
    {
        printf( "pState[%d][%d] = %d\n", n-1, i, pState[n-1][i] );
        maxV = pState[n-1][i] > maxV ? pState[n-1][i] : maxV;
    }
    cout << "背包可以装的最大价值为: " << maxV << endl;
    
    return ;
}


int main(int argc, char **argv)
{
    func(0, 5, 0, 0);
    
    cout << "背包可以装的最大价值为: " << maxV << endl;

    f(5, wm, w, v);

    return 0;
}