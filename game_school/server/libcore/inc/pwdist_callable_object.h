#ifndef _pwdist_callable_object_
#define _pwdist_callable_object_

#include "pwdist_def.h"

namespace pwdist
{
	class ICallableObject
	{
	public:
		virtual ~ICallableObject()
		{
		}
	public:
		virtual int64 GetID() = 0;
	public:
		virtual int GetObjectHierarchy(int64* buf,int& num)
		{
			buf[0] = GetID();
			num = 1;
			return 0;
		}
	public:
		virtual int Update()
		{
			return 0;
		}
	};
}

#endif // _pwdist_callable_object_