#ifndef _pw_ngs_logic_utils_
#define _pw_ngs_logic_utils_

#include "pw_tx_def.h"
#include "pw_lua.h"

namespace pwngs
{
	PreDefineMsgW(STencentUserInfo);
}

namespace pwutils
{
	/*extern void TranslateTencentUserInfoStruct(const orm::DTencentUserInfo& src,pwngs::STencentUserInfo& dst);
	extern void TranslateTencentUserInfoStruct(const pwngs::STencentUserInfo& src,orm::DTencentUserInfo& dst);

	extern void TranslateTencentUserInfoStruct(const orm::DTencentUserInfo& src,MsgW(STencentUserInfo)* dst);
	extern void TranslateTencentUserInfoStruct(const orm::DTencentUserInfo& src,lua_State* L);*/

	extern void TranslateTencentUserInfoStruct( const pwngs::STencentUserInfo& info,MsgW(STencentUserInfo)* msg );
}


#endif // _pw_ngs_logic_utils_