#ifndef _pw_class_query_
#define _pw_class_query_

// #include "pw_clsid.h"

// 接口部份
const unsigned int IID_ClassQuery           =    0;

#define CLSID(thisclass,baseclass,fid) 	CLSID2(baseclass::_CLSID,fid)
#define CLSID2(cid,fid) 	public:\
									enum { _CLSID = (fid | cid), _CLSFID = fid, }; \
									virtual bool IsKindOf(TCLSID cls) { return (_CLSID & cls) > 0; } \
									virtual TCLSID GetClsid() { return fid; }


// #define QueryObjectSupported(T) if(_type == T::CLSID) { return *result = (T*)this,0; }

namespace pwngs
{
	/**
	 * @class IClassQuery
	 * @author cbh
	 * @date 2011年09月14日
	 * @file pw_class_query.h
	 * @brief 自定义的rtti基类，用于对象组件查询
	 */
	class IClassQuery
	{
		CLSID2(0,IID_ClassQuery);
	public:
		virtual ~IClassQuery(void) {}
	public:
		template<class T> T* QueryObjectEx()
		{
			if(!IsKindOf(T::_CLSFID))
				return NULL;
			return (T*)this;
		}
	};
}

#endif //_pw_class_query_
