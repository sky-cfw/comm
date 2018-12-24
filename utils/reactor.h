#ifndef REACTOR_H
#define REACTOR_H

#include <stdint.h>
#include <set>
#include <map>


namespace boss
{
	//时间处理基类
	class CTimeHandler
	{
	public:
		CTimeHandler();
		virtual ~CTimeHandler();
	
	//method
	public:
		virtual int HandlerTimeout( uint64_t ui64Seconds, uint64_t ui64MilliSeconds );
		
		void SetSeconds( const uint64_t &ui64Seconds );
		void setMilliSeconds( const uint64_t &ui64MilliSeconds );

		uint64_t GetSeconds();
		uint64_t GetMilliSeconds();
	private:
		uint64_t m_ui64Seconds;
		uint64_t m_ui64MilliSeconds;
	};

	class CEpollReactor
	{
	public:
		CEpollReactor();
		virtual ~CEpollReactor();
	
	//mechod
	public:
		virtual int RegisterTimerHandler( const uint64_t &ui64Seconds, const uint64_t &ui64MilliSeconds, CTimeHandler *pTimeHandler );
		virtual int RunEventLoop();
	private:
		int NonBlockRead( const int &iFd, const int64_t &i64BytesToRead, char *pszRecvBuff );

	private:
		std::set<CTimeHandler *> m_setTimeHanlder;//
		std::map<int, CTimeHandler *> m_mapTimerFd2Hander;
	};
}

#endif
