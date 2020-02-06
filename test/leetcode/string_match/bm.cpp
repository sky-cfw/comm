/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     单模式字符串匹配之BM算法
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				     2020/01/28
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#include "bm.h"

CBmMatch::CBmMatch( const std::string &sText, const std::string &sPattern ):
m_sText(sText),
m_sPattern(sPattern),
m_piSuffix(NULL)
{
    cout << "sizeof(m_iBCHTable) = " << sizeof(m_iBCHTable) << endl;
    memset( m_iBCHTable, -1, sizeof(m_iBCHTable)/sizeof(int) );
    InitBCHTable( m_sPattern, m_iBCHTable );
    InitGSF( m_sPattern, m_piSuffix );
}

CBmMatch::~CBmMatch()
{
}

/**********************************************************************************************************
* Function:				
* Description:		    初始化坏字符hash表(预处理表，以提升查找效率)
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:					
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
void CBmMatch::InitBCHTable( const std::string &sPattern, int *iBCHTable )
{
    for ( int i = 0; i < sPattern.size(); i++)
    {
        cout << "iBCHTable[" << (int)sPattern[i] << "] = " << i << endl;
        iBCHTable[(int)sPattern[i]] = i;
    }

    return ;
}

/**********************************************************************************************************
* Function:				
* Description:		    初始化好后缀数组(预处理，以提升查找效率)
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:					
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
void CBmMatch::InitGSF( const std::string &sPattern, int *&piSuffix )
{
    int m = sPattern.size();
    piSuffix = new int[m];
    for ( size_t i = 0; i < m; i++ )
    {
        piSuffix[i] = -1;
    }
    
    int j = 0, k = 0;//前缀子串尾部字符位置，后缀子串长度
    //好后缀子串的长度最大为m-1，否则就出现匹配啦，就不会走到这里啦。
    for ( size_t i = 0; i < m-1; i++ )
    {
        j = i;
        k = 0;//公共后缀子串长度
        while ( j >= 0 && sPattern[j] == sPattern[m-1-k] )
        {
            j--;//最大前缀子串开始依次向前推进
            k++;//后缀子串长度
            piSuffix[k] = j+1;
            cout << "k="<< k << ", j+1=" << j+1 << endl;
        }
    }

    cout << "好后缀子串在模式串中匹配情况如下:" << endl;
    for ( int i = 0; i < m; i++ )
    {
        cout << i << ": " << piSuffix[i] << endl;
    }

    return ;
}

/**********************************************************************************************************
* Function:				
* Description:		   单模式字符串匹配之BM算法
* Access Level:			
* Input:					
* Output:					
* Return:					
* Others:				实现关键点：
                        1.依据坏字符规则，计算滑动位数a;
                        2.依据好后缀规则，计算滑动位数b；
                            2.1如果好后缀在模式串中反向能够找到时，移动相应的位数即可
                            2.2如果好后缀在模式串中反向无法找到时，在好后缀的后缀子串中，找一个最长的并且能跟模式串的前缀子串匹配的
                        3.取a和b中大的数作为最终的滑动位数，重复上述过程，直到匹配为止 或者 不匹配为止
                        1. Date:           2. Author:          3.Modification:
**********************************************************************************************************/
int CBmMatch::BMMatch()
{
    int n = m_sText.size();//主串长度
    int m = m_sPattern.size(), j = m-1, iStep = 1, iBCStep = 1, iGSFStep = 1;//模式串长度，匹配索引，滑动位数, 坏字符滑动位数，好后缀滑动位数
    for (int i = 0; i < n-m+1; i=i+iStep)
    {
        for ( j = m-1; j >= 0 && m_sText[i+j] == m_sPattern[j]; j--)//模式串从后往前匹配
        {
            
        }
        
        //匹配到模式串
        if ( j < 0 )
        {
            cout << "match succ, start pos: " << i << endl;
            return i;// 匹配成功，返回主串与模式串第一个匹配的字符的位置
        }
        
        //存在坏字符，坏字符在模式串中的位置为j
        iBCStep = j - m_iBCHTable[int(m_sText[i+j])];
        cout << "坏字符位置: " << j << ", 坏字符在模式串从上一次出现的位置: " << m_iBCHTable[int(m_sText[i+j])] << ", 坏字符滑动位数: " << iBCStep << endl;
        
        //(j+1)~(m-1)为好后缀子串，长度为m-j-1
        //好后缀串是否在模式串中再次出现
        //好后缀本身也是模式串的后缀子串，可以预处理模式串，预先计算好模式串中的每个后缀子串，对应另外一个可匹配子串的位置
        int iSuffixStrLen = (m-1)-(j+1)+1;//好后缀长度
        cout << "好后缀字符串的长度为: " << iSuffixStrLen << endl;
        if ( 0 == iSuffixStrLen )
        {
            iStep = iBCStep;
            continue;
        }

        //存在好后缀子串
        if ( -1 != m_piSuffix[iSuffixStrLen] )//模式串中有匹配到好后缀的子串
        {
            iGSFStep = (j+1)-m_piSuffix[iSuffixStrLen];
            cout << "好后缀子串起始位置: " << (j+1) << ", 好后缀串在模式串中上一次出现的位置: " << m_piSuffix[iSuffixStrLen] << ", 好后缀规则滑动的位数为: " << iGSFStep << endl;
        }
        else
        {
            int k = iSuffixStrLen-1;
            while ( k > 0 && m_piSuffix[k] != 0 )
            {
                k--;
            }
            
            //没有最大公共后缀子串
            if ( 0 == k )
            {
                iGSFStep = (m-1)-(-1);
                cout << "没有找到最大公共后缀子串，好后缀滑动位数: " << iGSFStep << endl;
            }
            else
            {
                iGSFStep = m-k;
                cout << "找到最大公共后缀子串, 好后缀滑动位数: " << iGSFStep << endl;
            }
        }
        
        iStep = ((iBCStep > iGSFStep) ? iBCStep : iGSFStep);
        cout << "iBCStep: " << iBCStep << ", iGSFStep: " << iGSFStep << ", 滑动位数: " << iStep << endl << endl;
    }

    //没有匹配
    return -1;
}


int main()
{
    //std::string sText = "abcacabcbcbacabc", sPattern = "cbacabc";
    std::string sText = "abcacabcbcbacabc", sPattern = "abacabc";
    CBmMatch cBmMatch( sText, sPattern );
    cout << "text: " << sText << ", pattern: " << sPattern << ", match result: " << cBmMatch.BMMatch() << endl;

    return 0;
}