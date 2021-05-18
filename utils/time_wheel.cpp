#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "time_wheel.h"
#include <stdio.h>
//#include "tlog.h"

using namespace util::timer;

CTimer::CTimer(int secs, int milisecs, bool cycle):
m_iSecs(secs),
m_iMiliSecs(milisecs),
m_bCycle(cycle)
{
	
}

CTimer::~CTimer()
{
	
}

int CTimer::GetSecs()
{
	return m_iSecs;
}

int CTimer::GetMiliSecs()
{
	return m_iMiliSecs;
}

int CTimer::GetSlot()
{
	return m_iSlot;
}

int CTimer::GetRound()
{
	return m_iRound;
}

int CTimer::SetSlotRound( int slot, int round )
{
	m_iSlot = slot;
	m_iRound = round;
	return 0;
}

int CTimer::DecreaseRound()
{
	m_iRound--;
	return 0;
}

bool CTimer::IsCycle()
{
	return m_bCycle;
}

CTimeWheel::CTimeWheel(int slots, int ticktime, int currslot):
m_iSlots(slots),
m_iTicktime(ticktime),
m_iCurrSlot(currslot)
{
	m_vecWheel.reserve(slots);
	for ( int i = 0; i < slots; i++ )
	{
		std::list<CTimer *> listCTimer;
		printf("i:%d\n",i);
		m_vecWheel.push_back( listCTimer );
	}
}

CTimeWheel::~CTimeWheel()
{
	
}

int CTimeWheel::AddTimer(CTimer *pCTimer)
{
	int iMiliSecs = pCTimer->GetSecs() * 1000 + pCTimer->GetMiliSecs();
	int iTicks = iMiliSecs / m_iTicktime;

	int iRound = iTicks / m_iSlots;
	int iSlot = (iTicks+m_iCurrSlot) % m_iSlots;
	pCTimer->SetSlotRound( iSlot, iRound );
	printf( "iRound[%d] iCurrSlot[%d] iSlot[%d]\n", iRound, m_iCurrSlot, iSlot );
	
	m_vecWheel[iSlot].push_back(pCTimer);//会core掉 why？
	printf("add succ\n");

	return 0;
}

int CTimeWheel::DelTimer( CTimer *pCTimer )
{
	std::list<CTimer *> &listCTimer = m_vecWheel[pCTimer->GetSlot()];
	std::list<CTimer *>::iterator itr = listCTimer.begin();
	for ( ; itr != listCTimer.end(); itr++ )
	{
		if ( *itr == pCTimer )
		{
			itr = listCTimer.erase( itr );
			printf( "delete timer succ!" );
			break;
		}
	}
	printf( "not find timer" );

	return 0;
}

int CTimeWheel::Dispatch()
{
	struct timeval tv;
	//tv.tv_sec = (m_iTicktime / 1000);
	//tv.tv_usec = ((m_iTicktime % 1000)*1000);
	int iRet;
	for ( ; ; )
	{
		do
		{
			tv.tv_sec = (m_iTicktime / 1000);
			tv.tv_usec = ((m_iTicktime % 1000)*1000);
			iRet = select( 0, NULL, NULL, NULL, &tv );
		}while( iRet < 0 && errno == EINTR );

		//time_t timeCurr = time();
		printf( "tick!\n" );
		Ticker();
	}
	return 0;
}

int CTimeWheel::Ticker()
{
	m_iCurrSlot = ((++m_iCurrSlot) % m_iSlots);
	std::list<CTimer *> &listCTimer = m_vecWheel[m_iCurrSlot];
	std::list<CTimer *>::iterator itr = listCTimer.begin();
	for ( ; itr != listCTimer.end(); itr++ )
	{
		CTimer *pCTimer = *itr;
		if ( pCTimer->GetRound() <= 0 )
		{
			printf( "start to exec timeout event\n" );
			pCTimer->HandlerTimeout();
			if ( pCTimer->IsCycle() )
			{
				AddTimer( pCTimer );
			}
			itr = listCTimer.erase( itr );
		}
		else
		{
			pCTimer->DecreaseRound();
		}
	}

	return 0;
}
