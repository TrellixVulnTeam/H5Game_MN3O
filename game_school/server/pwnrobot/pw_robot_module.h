#ifndef _pw_robot_module_
#define _pw_robot_module_


namespace pwngs
{
	class RobotCharacter;
	
	class RobotModule
	{
	public:
		RobotModule(RobotCharacter* owner)
		{
			m_pOwner = owner;
		}

		inline RobotCharacter* GetOwner()
		{
			return m_pOwner;
		}
	protected:
		RobotCharacter* m_pOwner;
	};
}

#endif // _pw_robot_module_