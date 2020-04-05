/**********************************************************************************************************
* Copyright:             XX Tech.co,Ltd. 2015-. All rights reserved
* File name:		     布隆过滤器实现
* Description:		      
* Author:                sky
* Version:               V1.0
* Date:				     2020/03/31
* History:					  
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#include <math.h>//pow
#include <cstring>//memmove
#include "bloom_filter.h"
#include "murmur_hash3.h"
#include "facility.h"
#include <iostream>

using namespace boss::util;
using namespace std;

CBitMap::CBitMap():
m_ui64Size(0),
m_ui64Capacity(0),
m_iExpandedTimes(0)
{

}

CBitMap::~CBitMap()
{
    if ( NULL != m_pData )
    {
        delete [] m_pData;
        m_pData = NULL;
    }
}

int32_t CBitMap::Init( const uint64_t &ui64Size )
{
    m_ui64Size = ui64Size/sizeof(uint64_t);
    m_pData = new uint64_t[m_ui64Size];
    if ( NULL == m_pData )
    {
        return -1;
    }
    
    return 0;
}

uint64_t CBitMap::Count()
{
    uint64_t ui64Cnt = 0;
    for ( size_t i = 0; i < m_ui64Size; i++ )
    {
        ui64Cnt += boss::util::BitCount( m_pData[i] );
    }
    
    return ui64Cnt;
}

uint64_t CBitMap::Size()
{
    return (m_ui64Size * sizeof(uint64_t));
}

uint64_t CBitMap::ReSize()
{
    uint64_t ui64NewSize = m_ui64Size << 1;
    
    uint64_t *pTmp = m_pData;
    m_pData = new uint64_t[ui64NewSize];
    memmove( m_pData, pTmp, m_ui64Size );
    if ( NULL != pTmp )
    {
        delete pTmp;
        pTmp = NULL;
    }
    m_ui64Size = ui64NewSize;
    m_iExpandedTimes++;

    return m_ui64Size;
}

bool CBitMap::operator [] (const uint64_t &ui64Pos)
{
    uint64_t ui64Index = ui64Pos/sizeof(uint64_t);
    uint64_t ui64Offset = ui64Pos % sizeof(uint64_t);

    return (m_pData[ui64Index] & (0x01 << ui64Offset));
}

void CBitMap::Set(const uint64_t &ui64Pos)
{
    uint64_t ui64Index = ui64Pos/sizeof(uint64_t);
    uint64_t ui64Offset = ui64Pos % sizeof(uint64_t);

    m_pData[ui64Index] |= (0x01 << ui64Offset);

    m_ui64Capacity = Count();
}

void CBitMap::Reset()
{
    memset( m_pData, 0, m_ui64Size*sizeof(uint64_t) );
    m_ui64Capacity = 0;
}

void CBitMap::Reset(const uint64_t &ui64Pos)
{
    uint64_t ui64Index = ui64Pos/sizeof(uint64_t);
    uint64_t ui64Offset = ui64Pos % sizeof(uint64_t);

    m_pData[ui64Index] ^= (0x01 << ui64Offset);
    m_ui64Capacity = Count();
}

bool CBitMap::Test(const uint64_t &ui64Pos)
{
    uint64_t ui64Index = ui64Pos/sizeof(uint64_t);
    uint64_t ui64Offset = ui64Pos % sizeof(uint64_t);

    return (m_pData[ui64Index] & (0x01 << ui64Offset));
}

CBloomFilter::CBloomFilter( const uint64_t &ui64ExpectCapacity, const float &fExpectErrRate ):
m_ui64ExpectCapacity(ui64ExpectCapacity),
m_fExpectErrRate(fExpectErrRate)
{   
    // 计算位向量长度、hash函数个数
    // m=-(n * lg(p)) / (lg(2)^2)
    // n : int 
    //         number of items expected to be stored in filter 
    // p : float 
    //         False Positive probability in decimal 
    float fSize = -( ui64ExpectCapacity * log(fExpectErrRate) ) / pow(log(2), 2);
    uint64_t ui64Size = ceil(fSize);
    m_cBitMap.Init( ui64Size );
    m_uiHashFuncNum = ui64Size * log(2)/ui64ExpectCapacity;
}

CBloomFilter::~CBloomFilter()
{

}

void CBloomFilter::Add( const std::string &sItem )
{
    uint64_t ui64HashVal1 = 0;
    for (size_t i = 0; i < m_uiHashFuncNum; i++)
    {
        MurmurHash3_x64_128( sItem.c_str(), sItem.length(), i, &ui64HashVal1 );
        ui64HashVal1 = (ui64HashVal1 % m_cBitMap.Size());
        m_cBitMap.Set( ui64HashVal1 );
    }

    //是否需要扩容
    // if ( m_cBitMap.Count() >= m_ui64ExpectCapacity )
    // {
    //     m_cBitMap.ReSize();
    // }
}

bool CBloomFilter::Exists( const std::string &sItem )
{
    uint64_t ui64HashVal1 = 0;
    for (size_t i = 0; i < m_uiHashFuncNum; i++)
    {
        MurmurHash3_x64_128( sItem.c_str(), sItem.length(), i, &ui64HashVal1 );
        ui64HashVal1 = (ui64HashVal1 % m_cBitMap.Size());
        if ( !m_cBitMap.Test( ui64HashVal1 ) )
        {
            return false;
        }
    }

    return true;
}

// int main()
// {
//     #define RATE 0.05
//     #define CAPACITY 10000
    
//     CBloomFilter cBloomFilter( CAPACITY, RATE );
//     cout << "Hash Func Num: " << cBloomFilter.m_uiHashFuncNum << endl;
//     cout << "BitMap size: " << cBloomFilter.m_cBitMap.Size() << endl;

//     for ( size_t i = 0; i < CAPACITY; i++ )
//     {
//         cBloomFilter.Add( std::to_string(i) );
//     }
//     cout << "BitMap capacity: " << cBloomFilter.m_cBitMap.Count() << endl;
    
//     int count = 0;
//     for ( size_t i = 0; i < CAPACITY+100; i++ )
//     {
//         if ( cBloomFilter.Exists( std::to_string(i) ) )
//         {
//             cout << i << endl;
//             count++;
//         }
//     }
//     cout << "false positive rate: " << float(count-CAPACITY)/CAPACITY << endl;

//     return 0;
// }