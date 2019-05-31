#ifndef _pw_robot_motion_def_
#define _pw_robot_motion_def_

#include "pw_robot_def.h"

namespace pwngs
{
	enum RMotionType
	{
		RMOTION_TYPE_NONE,
		RMOTION_TYPE_TARGET,
		RMOTION_TYPE_ORIENTATION,
		RMOTION_TYPE_POSITION,
		RMOTION_TYPE_PATH,
		RMOTION_TYPE_END,
	};

	class RMotionInfo
	{
	public:
		RMotionType nMotionType;
		G3D::Vector3 vMotionPosition;
	};
}


#endif // _pw_robot_motion_def_