#include "pwdist_common.h"

namespace pwdist
{
	size_t Parameters::BytePtr()
	{
		size_t result = 0;

		for(size_t i = 0; i < paramsNum; ++i)
		{
			switch(params[i].type)
			{
			case PARAMETER_TYPE_STR:
			case PARAMETER_TYPE_BUF:
				{
					result += params[i].size;
				}
				break;
			default:
				break;
			}
		}
		return result;
	}

	size_t Parameters::LoadPtr(char* buf,size_t len)
	{
		size_t result = 0;

		for(size_t i = 0; i < paramsNum; ++i)
		{
			switch(params[i].type)
			{
			case PARAMETER_TYPE_STR:
			case PARAMETER_TYPE_BUF:
				{
					result += params[i].size;
					params[i].valbuf = buf;
					buf += params[i].size;
					if(params[i].size == 0)
					{
						params[i].valbuf = NULL;
					}
				}
				break;
			default:
				break;
			}
		}
		return result;
	}

	size_t Parameters::SavePtr( char* buf,size_t len )
	{
		size_t result = 0;

		for(size_t i = 0; i < paramsNum; ++i)
		{
			switch(params[i].type)
			{
			case PARAMETER_TYPE_STR:
			case PARAMETER_TYPE_BUF:
				{
					result += params[i].size;
					memcpy(buf,params[i].valbuf,params[i].size);
					buf += params[i].size;
				}
				break;
			default:
				break;
			}
		}
		return result;
	}

	size_t MsgCall::Bytes()
	{
		return sizeof(MsgCall) + params.BytePtr();
	}

	size_t MsgCall::Load( char* buf,size_t len )
	{
		size_t result = sizeof(MsgCall);
		
		memcpy(this,buf,sizeof(MsgCall));

		buf += result;
		len -= result;
		
		result += params.LoadPtr(buf,len);

		return result;
	}

	size_t MsgCall::Save( char* buf,size_t len )
	{
		size_t result = sizeof(MsgCall);

		memcpy(buf,this,sizeof(MsgCall));

		buf += result;
		len -= result;

		result += params.SavePtr(buf,len);

		return result;
	}

	void CallEndpoint::initial( const char* _node,const char* _port,int64* _hierarchies,int32 num )
	{
		if(_node)
			strncpy(node,_node,_countof(node));
		
		if(_port)
			strncpy(port,_port,_countof(port));

		hierarchiesNum = num;
		if(num > 0)
			memcpy(hierarchies,_hierarchies,num * sizeof(int64));
	}

}