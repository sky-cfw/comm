#ifndef TIME_WHEEL_H
#define TIME_WHEEL_H

#include <vector>
#include <list>

using namespace std;

namespace util
{
	namespace timer
	{
		//定时器基类
		class CTimer
		{
			public:
				CTimer( int secs, int milisecs, bool cycle );
				~CTimer();

			public:
				virtual int HandlerTimeout() = 0;//定时任务处理函数
				int GetSecs();
				int GetMiliSecs();
				int GetSlot();
				int GetRound();
				int DecreaseRound();
				bool IsCycle();

				int SetSlotRound( int slot, int round );

			protected:
				int m_iSecs;//秒
				int m_iMiliSecs;//毫秒
				bool m_bCycle;//是否周期性

				int m_iSlot;
				int m_iRound;

		};

		class CTimeWheel
		{
			public:
				CTimeWheel( int slots, int ticktime/*ms*/, int currslot );
				~CTimeWheel();

				int AddTimer( CTimer *pCTimer );
				int DelTimer( CTimer *pCTimer );
				int Dispatch();

			private:
				int Ticker();//指针往前走一步
				int FixTime();//时间校准
				int GetSlotRound( CTimer *pCTimer );//获取定时器应该放入的槽编号及环数

			private:
				std::vector<std::list<CTimer *>  > m_vecWheel;//vector的容量为槽的个数
				int m_iSlots;//总槽数
				int m_iTicktime;//指针步进的时间(ms)，决定定时器精度
				int m_iCurrSlot;//当前指针指向的槽编号
				int m_iLastTime;//最近一次tick前时间
		};
	}
}

#endif
