
#ifndef _pwdbsrv_def_
#define _pwdbsrv_def_

namespace pwdbsrv
{
	enum ELoginOperCode
	{
		LOGIN_FAILED_SUCCESS = 0,

		LOGIN_FAILED_CHARACTER_CREATE_NAME_TOO_LONG = 1,
		LOGIN_FAILED_CHARACTER_CREATE_NAME_ALREADY_EXISTS,
		LOGIN_FAILED_CHARACTER_CREATE_DB_SERVER_BUSY,
		LOGIN_FAILED_CHARACTER_CREATE_INTERNAL_ERROR,

		LOGIN_FAILED_KICK_SAME_CHARACTER_LOGIN = 50,
		LOGIN_FAILED_KICK_CHARACTER_LOGIN_RESULT1_TIMEOUT,
		LOGIN_FAILED_KICK_CHARACTER_LOGIN_RESULT2_TIMEOUT,
		LOGIN_FAILED_KICK_CHARACTER_LOGIN_RESULT3_TIMEOUT,
		LOGIN_FAILED_KICK_CHARACTER_LOGIN_RESULT3_ERROR,

	};
}

#endif // _pwdbsrv_def_