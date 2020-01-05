#include <set>
#include <map>
#include <stdint.h>
#include <climits>
#include <iostream>
#include "facility.h"
#include "murmur_hash3.h"
using namespace std;
using namespace boss::util;

class CConsistentHash
{
public:
	CConsistentHash( const int &iNumOfReplicas, const std::set<std::string> &setNode );
	virtual ~CConsistentHash();

//Method
public:
	std::set<uint32_t> AddNode( const std::string &sNode );//添加服务节点
	std::set<uint32_t> DelNode( const std::string &sNode );//删除服务节点
	std::string GetNode( const std::string &sKey );//返回关键字key所属的服务节点
	size_t GetSize();//返回虚拟节点个数
	void DebugNodeDis();//顺时间打印相邻两虚拟节点的间距

private:
	uint32_t BKDRHash( const std::string &sStr );
	uint32_t DJBHash( const std::string &sStr);

//Attr
private:
	int m_iNumOfReplicas;//一个服务节点对应的虚拟节点个数
	std::set<uint32_t> m_setCircle;//存储虚拟节点
	std::map<uint32_t, std::string> m_mapV2R;//存储环上的虚拟节点到真实服务的映射关系
};


CConsistentHash::CConsistentHash( const int &iNumOfReplicas, const std::set<std::string> &setNode )
{
	m_iNumOfReplicas = iNumOfReplicas;
	//m_setCircle.insert( ULONG_MAX );//哨兵
	std::set<std::string>::const_iterator itr = setNode.begin();
	for ( ; itr != setNode.end(); ++itr )
	{
		AddNode( *itr );
	}
}

CConsistentHash::~CConsistentHash()
{

}

uint32_t CConsistentHash::BKDRHash( const std::string &sStr )
{
	uint32_t ui32Seed = 131; // 31 131 1313 13131 131313 etc..
    uint32_t ui32Hash = 0;
 	
 	char *pStr = const_cast<char *>(sStr.c_str());
    while (*pStr)
    {
        ui32Hash = ui32Hash * ui32Seed + (*pStr++);
    }
 
    return (ui32Hash & 0x7FFFFFFF);
}

// DJB Hash Function
uint32_t CConsistentHash::DJBHash( const std::string &sStr )
{
    uint32_t uiHash = 5381;
 	
 	char *pStr = const_cast<char *>(sStr.c_str());
    while (*pStr)
    {
        uiHash += (uiHash << 5) + (*pStr++);
    }
 
    return (uiHash & 0x7FFFFFFF);
}

std::set<uint32_t> CConsistentHash::AddNode( const std::string &sNode )
{
	uint32_t ui32Hash = 0;
	std::string sTmp = "";
	for ( int i = 0; i < m_iNumOfReplicas; ++i )
	{
		sTmp = sNode + "#" + ConvertToString(i);
		MurmurHash3_x64_128( sTmp.c_str(), sTmp.length(), 0, &ui32Hash );//此处即不能使用BKDRHash，也不能使用DJBHash，因为使用上述两个散列函数对有规律的key散列不匀均。
		// cout << "node:" << sTmp << ", hash:" << ui32Hash << endl;
		m_setCircle.insert( ui32Hash );
		m_mapV2R.insert( std::pair<uint32_t, std::string>( ui32Hash, sNode ) );
	}

	return m_setCircle;
}

std::set<uint32_t> CConsistentHash::DelNode( const std::string &sNode )
{
	uint32_t ui32Hash = 0;
	std::string sTmp = "";
	for ( int i = 0; i < m_iNumOfReplicas; ++i )
	{
		sTmp = sNode + "#" + ConvertToString(i);
		MurmurHash3_x64_128( sTmp.c_str(), sTmp.length(), 0, &ui32Hash );
		m_setCircle.erase( ui32Hash );
		m_mapV2R.erase( ui32Hash );
	}

	return m_setCircle;
}

std::string CConsistentHash::GetNode( const std::string &sKey )
{
	if ( 0 == m_setCircle.size() )
	{
		return "";
	}

	uint32_t ui32Hash = 0, ui32VirPot = 0;
	MurmurHash3_x64_128( sKey.c_str(), sKey.length(), 0, &ui32Hash );
	cout << "key:" << sKey << ", hash:" << ui32Hash << endl;
	do
	{
		if ( m_setCircle.count( ui32Hash ) > 0 )
		{
			ui32VirPot = ui32Hash;
			break;
		}

		std::set<uint32_t>::iterator itr = m_setCircle.upper_bound( ui32Hash );
		if ( itr != m_setCircle.end() )
		{
			ui32VirPot = *itr;
			break;
		}

		ui32Hash = 0;
	}
	while(1);
	
	return m_mapV2R[ui32VirPot];
}

size_t CConsistentHash::GetSize()
{
	return m_setCircle.size();
}

void CConsistentHash::DebugNodeDis()
{
	if ( 0 == m_setCircle.size() )
	{
		return ;
	}

	std::set<uint32_t>::iterator itr_pre = m_setCircle.begin();
	std::set<uint32_t>::iterator itr_cur = itr_pre;
	itr_cur++;

	std::map<std::string, uint32_t> mapHotWeight;//统计服务节点的权重(服务节点--->节点所能容纳的范围)
	// cout << "ULONG_MAX:" << ULONG_MAX << endl;

	// cout << "ULONG_MAX-(*m_setCircle.rbegin()):" << ULONG_MAX-(*m_setCircle.rbegin()) << endl;
	// cout << "(*m_setCircle.begin()):" << (*m_setCircle.begin()) << endl;

	//第一个节点
	// cout << "virtual pot:" << (*itr_pre) << ", distance:" << (ULONG_MAX-(*m_setCircle.rbegin())+(*m_setCircle.begin())) << endl;
	mapHotWeight[m_mapV2R[*itr_pre]] += (ULONG_MAX-(*m_setCircle.rbegin())+(*m_setCircle.begin()));

	//后续节点
	for ( ; itr_cur != m_setCircle.end(); ++itr_pre, ++itr_cur )
	{
		// cout << "virtual pot:" << (*itr_cur) << ", distance:" << ((*itr_cur) - (*itr_pre)) << endl;
		mapHotWeight[m_mapV2R[*itr_cur]] += ((*itr_cur) - (*itr_pre));
	}

	//输出每个服务节点的权重
	std::map<std::string, uint32_t>::iterator itr = mapHotWeight.begin();
	for ( ; itr != mapHotWeight.end(); itr++ )
	{
		cout << "service pot:" << itr->first << ", weight:" << (double)itr->second/ULONG_MAX << endl;
	}
	
}


int main(int argc, char const *argv[])
{
	if ( argc < 2 )
	{
		cout << "./consistence_hash numOfReplicas" << endl;
		return -1;
	}

	int iNumOfReplicas = atoi(argv[1]);

	std::set<std::string> setNode;
	setNode.insert( "10.198.133.242:8190" );
	setNode.insert( "10.190.8.206:8080" );
	setNode.insert( "100.108.234.46:8080" );

	CConsistentHash cConsistentHash( iNumOfReplicas, setNode );
	cout << "size:" << cConsistentHash.GetSize() << endl;
	cConsistentHash.DebugNodeDis();

	cout << "GetNode(\"test_key\") = " << cConsistentHash.GetNode( "test_key" ) << endl;

	cConsistentHash.AddNode( "100.116.172.101:8080" );
	cout << "size:" << cConsistentHash.GetSize() << endl;
	cConsistentHash.DebugNodeDis();

	cout << "GetNode(\"test_key\") = " << cConsistentHash.GetNode( "test_key" ) << endl;

	return 0;
}