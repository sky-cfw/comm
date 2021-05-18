#include <iostream>
#include <pthread.h>
#include "thread_lock.h"
using namespace std;

class CSingleton
{
	private:
		CSingleton() {}//防止外部创建类的实例
		CSingleton(const CSingleton &rhs);//防止外部调用复制构造函数创建类的实例
		const CSingleton & operator = ( const CSingleton &rhs);//防止外部通过赋值操作符来构造类的实例
	public:
		~CSingleton() {}//保证类的实例能够正常释放
		static CSingleton *GetInstance()
		{
			if ( NULL == m_pInstance )
			{
				CThreadAutoLock Lock(&m_cThreadExclusiveLock );
				if ( NULL == m_pInstance )	
				{
					CSingleton *pTmp = new CSingleton();
					//barrier

					m_pInstance = pTmp;
				}
			}
			return m_pInstance;
		}

		void Log( const std::string &sMsg )
		{
			cout << sMsg.c_str() << m_pInstance << endl;
		}

	public:
		static CSingleton *m_pInstance;
		static CThreadExclusiveLock m_cThreadExclusiveLock;
};

CSingleton* CSingleton::m_pInstance = NULL;
CThreadExclusiveLock CSingleton::m_cThreadExclusiveLock;

#define SINGLETON CSingleton::GetInstance()


void *thread_fun_1(void *arg)
{
	int i = 500;
	while( i-- >= 0 )
		SINGLETON->Log( "thread_func_1 instance address:" );
}

void *thread_fun_2(void *arg)
{
	int i = 500;
	while( i-- >= 0 )
		SINGLETON->Log( "thread_func_2 instance address:" );
}


int main()
{
	pthread_t tid1, tid2;
	
	// 创建 2 个线程
	pthread_create(&tid1, NULL, thread_fun_1, NULL);
	pthread_create(&tid2, NULL, thread_fun_2, NULL);

	// 等待线程结束，回收其资源
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
