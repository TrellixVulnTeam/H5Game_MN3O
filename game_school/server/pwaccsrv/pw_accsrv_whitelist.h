#ifndef _pw_accsrv_whitelist_
#define _pw_accsrv_whitelist_

namespace pwngs
{
	extern void ReloadWhiteList(const char* filename);
	extern bool IsAcceptThisIp(const char* ip);
	extern void EnableWhiteList(bool enable);
}

#endif // _pw_accsrv_whitelist_