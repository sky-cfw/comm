/**********************************************************************************************************
* Copyright:             JD Tech.co,Ltd. 2015-. All rights reserved
* File name:		     基础工具函数库
* Description:		     
* Author:                sky
* Version:               V1.0
* Date:				     2018/12/25
* History:
                         1. Date:          2. Author:         3. Modification:
**********************************************************************************************************/
#ifndef FACILITY_H
#define FACILITY_H

#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sstream>

namespace boss
{
	namespace util
	{
		/**********************************************************************************************************
		* Function:
		* Description:		    daemonize
		* Access Level:		
		* Input:
		* Output:
		* Return:
		* Others:
		                        1. Date:           2. Author:          3.Modification:
		**********************************************************************************************************/
		int daemon_init()
		{
			pid_t pid = 0;

			//	
			pid = fork();
			if ( pid < 0 )
			{
				exit( EXIT_FAILURE );
			}
			else if ( pid > 0 )
			{
				exit( EXIT_SUCCESS );
			}

			//
			if ( setsid() < 0 )
			{
				exit(EXIT_FAILURE);
			}
        	
        	//	
        	signal( SIGCHLD, SIG_IGN );
    		signal( SIGHUP, SIG_IGN );

    		//	
    		pid = fork();
    		if ( pid < 0 )
			{
				exit( EXIT_FAILURE );
			}
			else if ( pid > 0 )
			{
				exit( EXIT_SUCCESS );
			}

			//
			umask(0);

			//	
			chdir("/");

			//	
			int iMaxFd = sysconf( _SC_OPEN_MAX );
			for ( int i = 0; i <= iMaxFd; i++ )
		    {
		        close (i);
		    }


			return 0;
		}

		/**********************************************************************************************************
		* Copyright:             Tencent Tech.co,Ltd. 2015-. All rights reserved
		* File name:		     convert to str
		* Description:		     
		* Author:                sky
		* Version:               V1.0
		* Date:				     
		* History:
		                         1. Date:          2. Author:         3. Modification:
		**********************************************************************************************************/
		template <class _T>
		std::string ConvertToString( const _T &obj )
		{
			std::stringstream ssContent;
			ssContent << obj;

			return ssContent.str();
		}

		/**********************************************************************************************************
		* Copyright:             Tencent Tech.co,Ltd. 2015-. All rights reserved
		* File name:		     calc bitmap's capacity
		* Description:		     
		* Author:                sky
		* Version:               V1.0
		* Date:				     
		* History:
		                         1. Date:          2. Author:         3. Modification:
		**********************************************************************************************************/
		uint64_t BitCount( uint64_t n )
		{
			uint64_t ui64Cnt = 0;
			while(n)
			{
				n &= (n-1);
				ui64Cnt++;
			}

			return ui64Cnt;
		}
	}
}

#endif
