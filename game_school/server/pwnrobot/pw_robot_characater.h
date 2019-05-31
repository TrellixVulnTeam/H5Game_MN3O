#ifndef _pw_robot_characater_
#define _pw_robot_characater_

#include "pw_def.h"
#include "pw_robot_def.h"
#include "pw_bitset.h"
#include "pw_class_query.h"

namespace google
{
	namespace protobuf
	{
		class Message;
	}
}

namespace pwngs
{
	class RModMotion;

	class RobotCharacter : public IClassQuery
	{
		CLSID(RobotCharacter,IClassQuery,RCLSID_Character);
	public:
		RobotCharacter();
		virtual ~RobotCharacter();
	public:
		virtual int Update();
		virtual int UpdatePer1Sec();
		virtual int EnterWorld();
		virtual int LeaveWorld(const char* caller);
		virtual int DiscardObject();
	public:
		virtual const char* GetUniqueName();
		virtual int SendMsg(int msgid,google::protobuf::Message& msg);
	public:
		inline bool IsBitSet(int index)
		{
			return m_bitset.Get(index);
		}

		inline void SetBit(int index,bool value)
		{
			m_bitset.Set(index,value);
		}

		inline int64 GetID()
		{
			return m_nId;
		}

		inline const G3D::Vector3& GetPosition()
		{
			return m_vLoc;
		}

		inline const G3D::Vector3& GetOrientation()
		{
			return m_vDir;
		}

		inline void ChangePosition(const G3D::Vector3& pos)
		{
			m_vLoc = pos;
		}

		inline void ChangeOrientation(const G3D::Vector3& dir)
		{
			m_vDir = dir;
		}

		inline RModMotion* GetModMotion()
		{
			return m_pModMotion;
		}
	protected:
		int64 m_nId;
	protected:
		BitsetEx<32> m_bitset;
	protected:
		G3D::Vector3 m_vLoc;
		G3D::Vector3 m_vDir;
	protected:
		RModMotion* m_pModMotion;
	protected:
		char m_szUniqueName[50];
	};
}

#endif // _pw_robot_characater_