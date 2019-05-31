#include "kvdb/pw_kvorm.h"
#include "pw_utils.h"

namespace pwutils
{
	extern void KvormBuildSlaveTableName(char* destbuf,size_t destlen,const char* name,int64 ownerkey)
	{
		char keybuf[64] = "";
		destbuf[0] = 0;
		pwutils::itoa(keybuf,ownerkey);
		pwutils::strncpy(destbuf,name,destlen);
		pwutils::strncat(destbuf,".",destlen);
		pwutils::strncat(destbuf,keybuf,destlen);
	}

	extern void KvormBuildSlaveTableName(char* destbuf,size_t destlen,const char* name,const char* ownerkey)
	{
		destbuf[0] = 0;
		pwutils::strncpy(destbuf,name,destlen);
		pwutils::strncat(destbuf,".",destlen);
		pwutils::strncat(destbuf,ownerkey,destlen);
	}


	void KvormBase::from_obj( const KvormBase* r )
	{
		std::string tmpbson;
		r->to_bson(tmpbson);
		this->from_bson(tmpbson.c_str(),tmpbson.length());
	}

}