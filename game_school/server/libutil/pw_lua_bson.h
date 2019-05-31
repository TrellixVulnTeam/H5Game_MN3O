#ifndef _pw_lua_bson_
#define _pw_lua_bson_

#include "pw_lua.h"

namespace pwutils
{
	extern int ilua_bson_decode( lua_State* L );
	extern int ilua_bson_encode( lua_State* L );

}

#endif // _pw_lua_utils_