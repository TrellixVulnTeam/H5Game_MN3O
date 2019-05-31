#ifndef _pw_robot_def_
#define _pw_robot_def_

#include "pw_def.h"
#include "G3D/G3D.h"

namespace pwngs
{
	enum
	{
		ROBOT_BITEX_MOTION,
		ROBOT_BITEX_INWORLD,
	};


	typedef uint64 TCLSID;

	const TCLSID RCLSID_Character = 0x00000001;
	const TCLSID RCLSID_Human = 0x00000002;

}

#endif // _pw_robot_def_