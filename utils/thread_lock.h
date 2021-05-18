#ifndef THREAD_LOCK_H
#define THREAD_LOCK_H

#include <pthread.h>

class CThreadBaseLock
{
	public:
		CThreadBaseLock() {}
		virtual ~CThreadBaseLock() {}

		//
		virtual int Lock() = 0;
		virtual int Unlock() = 0;
};

class CThreadExclusiveLock : public CThreadBaseLock
{
	public:
		CThreadExclusiveLock();
		virtual ~CThreadExclusiveLock();
	
		
		virtual int Init();
		virtual int Destory();
		virtual int Lock();
		virtual int Unlock();

	protected:
		pthread_mutex_t mutex;
};

class CThreadAutoLock
{
	public:
		CThreadAutoLock( CThreadBaseLock *pThreadBaseLock );
		~CThreadAutoLock();
	
	private:
		CThreadBaseLock *m_pThreadBaseLock;
};


#endif
