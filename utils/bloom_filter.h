/**********************************************************************************************************
* Copyright:             Tech.co,Ltd. 2015-. All rights reserved
* File name:		     布隆过滤器实现(支持动态扩容)
* Description:		     
* Author:                sky
* Version:               V1.0
* Date:				     2020/03/31
* History:
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <stdint.h>
#include <string>

namespace boss
{
    namespace util
    {
        class CBitMap
        {
            public:
                CBitMap();
                virtual ~CBitMap();

                //位图支持的基本操作
                int32_t Init( const uint64_t &ui64Size );//位图(长度)初始化
                uint64_t Count();//返回位图当前容量
                uint64_t Size();//返回位图长度
                uint64_t ReSize();//重置位图大小
                bool operator [] (const uint64_t &ui64Pos);//返回指定位置的值
                void Set(const uint64_t &ui64Pos);//设定指定位置的值
                void Reset();//复位所有位
                void Reset(const uint64_t &ui64Pos);//复位指定位
                bool Test(const uint64_t &ui64Pos);//测试某一位是否被置位

            private:
                uint64_t *m_pData;//存储bit数据
                uint64_t m_ui64Capacity;//容量
                uint64_t m_ui64Size;//大小
                int m_iExpandedTimes;//当前已扩容次数
        };

        class CBloomFilter
        {
            public:
                CBloomFilter( const uint64_t &ui64ExpectCapacity, const float &fExpectErrRate );
                virtual ~CBloomFilter();

                //bf基本操作
                void Add( const std::string &sItem );//添加元素
                bool Exists( const std::string &sItem );//判断元素是否存在与集合中

            public:
                float m_fExpectErrRate;//能够容忍的假阳性概率
                uint64_t m_ui64ExpectCapacity;//预期存放元素的总个数
                uint32_t m_uiHashFuncNum;//hash函数个数
                CBitMap m_cBitMap;//位图
        };

    }
}


#endif
