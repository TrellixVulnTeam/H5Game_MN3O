#ifndef _pw_logic_utils_
#define _pw_logic_utils_

#include "pw_def.h"

namespace pwngs
{
	PreDefineMsgW(SVector3);
	PreDefineMsgW(SCastTarget);
	PreDefineMsgW(SMotion);
	PreDefineMsgW(STencentUserInfo);

	struct SMotionInfo;
	struct STencentUserInfo;
	
	/**
	 * @class LogicUtils
	 * @author cbh
	 * @date 2011年12月13日
	 * @file pw_logic_utils.h
	 * @brief 逻辑助手类
	 */
	class LogicUtils
	{
	public:
		/*static int TranslateStruct(const ::pwngs::protocol::worldsrv::SCastTarget& src,SCastTarget& target);
		static int TranslateStruct(const SCastTarget& src,::pwngs::protocol::worldsrv::SCastTarget& target);
		static int TranslateStruct(const ::pwngs::protocol::worldsrv::SVector3& src,G3D::Vector3& target);
		static int TranslateStruct(const G3D::Vector3& src,::pwngs::protocol::worldsrv::SVector3& target);
		
		static int TranslateStruct(const SMotionInfo& motion,pwngs::protocol::worldsrv::SMotion& info);
		static int TranslateStruct(const pwngs::protocol::worldsrv::SMotion& info,SMotionInfo& motion);*/
	};
}

#endif // _pw_logic_utils_