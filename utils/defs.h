/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2021-06-03 00:34:14
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-28 17:46:00
 * @FilePath: /comm/utils/defs.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef DEFS_H
#define DEFS_H

namespace boss
{
	namespace comm
	{
		#define SUCCESS (0)
		#define FAILED (-1)

		//携带错误信息返回
		// #define RETURN_ON_ERROR_L2( _ret, _errcode1, _errcode2, _fmt, ... ) do {\
		// 	if ( TAOP_OK != _ret) {\
		// 		SET_ERROR_L2( _errcode1, _errcode2, fmt, ... );\
		// 		return ret;\
		// 	}\
		// }

		//直接返回
		#define RETURN_ON_ERROR( _ret ) do {\
			if ( SUCCESS != _ret) {\
				return _ret;\
			}\
		} while(0)

		#define RETURN_ON_ERROR_MSG( _ret, _fmt, ... ) do {\
			if ( SUCCESS != _ret) {\
				TLOG_ERR( _fmt, ##__VA_ARGS__ );\
				return _ret;\
			}\
		} while(0)

		//直接返回之bool
		#define RETURN_ON_BOOL_ERROR( _ret ) do {\
			if ( !_ret ) {\
				return _ret;\
			}\
		} while(0)

		#define RETURN_ON_BOOL_ERROR_MSG( _ret, _fmt, ... ) do {\
			if ( !_ret ) {\
				TLOG_ERR( _fmt, ##__VA_ARGS__ );\
				return _ret;\
			}\
		} while(0)
	}
}

#endif

