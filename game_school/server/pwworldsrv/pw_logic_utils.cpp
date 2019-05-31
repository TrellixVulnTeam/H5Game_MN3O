#include "pw_logic_utils.h"
#include "pw_logger.h"
#include "00000_00000_def.pb.h"
#include "pw_tx_def.h"

namespace pwngs
{
	/*int LogicUtils::TranslateStruct(const ::pwngs::protocol::worldsrv::SCastTarget& src,SCastTarget& target)
	{
		target.targetType = src.target_type();
		target.targetId = src.target_id();
		target.targetItem = src.target_item();
		TranslateStruct(src.target_position(),target.targetPosition);
		return 0;
	}

	int LogicUtils::TranslateStruct(const SCastTarget& src,::pwngs::protocol::worldsrv::SCastTarget& target)
	{
		target.set_target_type(src.targetType);
		target.set_target_id(src.targetId);
		target.set_target_item(src.targetItem);
		TranslateStruct(src.targetPosition,*target.mutable_target_position());
		return 0;
	}

	int LogicUtils::TranslateStruct(const ::pwngs::protocol::worldsrv::SVector3& src,G3D::Vector3& target)
	{
		target.x = src.x();
		target.y = src.y();
		target.z = src.z();
		return 0;
	}
	
	int LogicUtils::TranslateStruct(const G3D::Vector3& src,::pwngs::protocol::worldsrv::SVector3& target)
	{
		target.set_x(src.x);
		target.set_y(src.y);
		target.set_z(src.z);
		return 0;
	}


	int LogicUtils::TranslateStruct(const SMotionInfo& motion,pwngs::protocol::worldsrv::SMotion& info)
	{
		info.set_motion_type((int)motion.nMotionType);
		info.set_param(motion.fParam);
		switch(motion.nMotionType)
		{
		case MOTION_TYPE_NONE:
			break;
		case MOTION_TYPE_TARGET:
			info.set_motion_target(motion.nMotionTarget);
			TranslateStruct(motion.vMotionPosition,*info.mutable_motion_position());
			break;
		case MOTION_TYPE_ORIENTATION:
			TranslateStruct(motion.vMotionOrientation,*info.mutable_motion_orientation());
			break;
		case MOTION_TYPE_POSITION:
			TranslateStruct(motion.vMotionPosition,*info.mutable_motion_position());
			break;
		case MOTION_TYPE_PATH:
			for(size_t i = 0; i < motion.vtMotionPath.size(); ++i)
				TranslateStruct(motion.vtMotionPath[i],*info.add_motion_path());
			break;
		default:
			pwassertn(false && "invalid motion type");
			return -1;
		}

		return 0;
	}

	int LogicUtils::TranslateStruct( const pwngs::protocol::worldsrv::SMotion& motion,SMotionInfo& info )
	{
		info.nMotionType = (EMotionType)motion.motion_type();
		info.fParam = motion.param();
		switch(info.nMotionType)
		{
		case MOTION_TYPE_NONE:
			break;
		case MOTION_TYPE_TARGET:
			info.nMotionTarget = motion.motion_target();
			TranslateStruct(motion.motion_position(),info.vMotionPosition);
			break;
		case MOTION_TYPE_ORIENTATION:
			TranslateStruct(motion.motion_orientation(),info.vMotionOrientation);
			break;
		case MOTION_TYPE_POSITION:
			TranslateStruct(motion.motion_position(),info.vMotionPosition);
			break;
		case MOTION_TYPE_PATH:
			
			for(int i = 0; i < motion.motion_path_size(); ++i)
			{
				G3D::Vector3 pos;
				TranslateStruct(motion.motion_path(i),pos);
				info.vtMotionPath.push_back(pos);
			}
			break;
		default:
			pwassertn(false && "invalid motion type");
			return -1;
		}
		return 0;
	}*/
}
