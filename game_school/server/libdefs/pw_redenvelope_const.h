#ifndef _pw_redenvelope_const_
#define _pw_redenvelope_const_

#include "pw_ngs_common.h"

namespace pwngs
{
	// 附言最大长度
	const int cst_redenvelope_postscript_max_len = 130;

	enum ERedEnvelopeLog
	{
		REDENVELOPE_LOG_NONE = 0,							// 未知类型

	};

	enum EUpdateRedEnvelopeInfo
	{
		UPDATE_REDENVELOPE_INFO_LOGIN = 0x0001,		// 发红包更新
	};

	enum ERedEnvelopeNotifyCode
	{
		REDENVELOPE_NOTIFY_SUCCESS = 0,
		REDENVELOPE_NOTIFY_SEND = 60202, //发红包

	};

}

#endif // _pw_redenvelope_const_
