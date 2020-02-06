/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     单模式字符串匹配 之 Boyer-Moore算法
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				  
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#ifndef BM_H
#define BM_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <map>

using namespace std;

class CBmMatch
{
private:
    std::string m_sText;//主串
    std::string m_sPattern;//模式串
    
    int m_iBCHTable[128];//模式串中每个字符最后出现的位置 坏字符哈希表 ascii码值 ---> 模式串位置
    int *m_piSuffix;//用于存储模式串的后缀子串，后缀子串长度 ---> 模式串中与后缀子串相同的子串的起始位置，如果起始位置为0，则表示后缀子串也是模式串的前缀子串
private:
    void InitBCHTable( const std::string &sPattern, int *iBCHTable );//初始化坏字符哈希表
    void InitGSF( const std::string &sPattern, int *&piSuffix );
public:
    CBmMatch( const std::string &sText, const std::string &sPattern );
    virtual ~CBmMatch();

    int BMMatch();
};

#endif
