#include "thread_lock.h"

CThreadExclusiveLock::CThreadExclusiveLock()
{
	Init();
}


CThreadExclusiveLock::~CThreadExclusiveLock()
{
	Destory();
}

int CThreadExclusiveLock::Init()
{
	return pthread_mutex_init( &mutex, NULL );
}

int CThreadExclusiveLock::Destory()
{
	return pthread_mutex_destroy( &mutex );
}

int CThreadExclusiveLock::Lock()
{
	return pthread_mutex_lock( &mutex );
}

int CThreadExclusiveLock::Unlock()
{
	return pthread_mutex_unlock( &mutex );
}

CThreadAutoLock::CThreadAutoLock( CThreadBaseLock *pThreadBaseLock )
{
	m_pThreadBaseLock = pThreadBaseLock;
	pThreadBaseLock->Lock();
}

CThreadAutoLock::~CThreadAutoLock()
{
	m_pThreadBaseLock->Unlock();
}
