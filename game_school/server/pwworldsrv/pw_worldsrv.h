#ifndef _pw_worldsrv_
#define _pw_worldsrv_

#include "pw_xml.h"
#include "pwdist_node.h"

namespace pwworldsrv
{
	enum
	{
		MODE_GM_RELAXED = 0x0001,
	};
	extern int g_nServerId;
	extern int g_nServerMode;
	extern std::string g_strServerName;

	extern int InitialWorld(pwutils::Xml& params);
	extern int StartupWorld(pwdist::Node* node,pwutils::Xml& xml, int threadNum = 5);
	extern int UpdateWorld();
	extern int CleanupWorld();
}

#endif //_pw_worldsrv_