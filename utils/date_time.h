#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string>

namespace boss
{
	namespace util
	{
		class CDateTime
		{
		public:
			CDateTime()
			{
				m_tmSeconds = time(NULL);
			}

			CDateTime( const time_t &tmSeconds )
			{
				m_tmSeconds = tmSeconds;
			}

			~CDateTime()
			{

			}
			
			void SetSeconds( const time_t &tmSeconds )
			{
				m_tmSeconds = tmSeconds;
			}
			
		public:
			std::string GetGMTDateTime( const std::string &sFormat = "%Y-%m-%d %H:%M:%S" )
			{
				char szDate[32] = {'\0'};

				struct tm *timeinfo;
    			timeinfo = localtime(&m_tmSeconds);

    			strftime( szDate, sizeof(szDate), sFormat.c_str(), timeinfo );

				return std::string(szDate);
			}

		//attr
		private:
			time_t m_tmSeconds;
		};
	}
}

#endif