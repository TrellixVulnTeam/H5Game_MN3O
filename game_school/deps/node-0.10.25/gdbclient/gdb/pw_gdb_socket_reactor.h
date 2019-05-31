#ifndef _pw_gdb_socket_reactor_
#define _pw_gdb_socket_reactor_

#include <list>
#include "pw_gdb_refcounted.h"
#include "pw_gdb_socket_base_connection.h"

namespace gdb
{
	class SocketReactor
	{
	public:
		enum 
		{
			MASK_READ	= 0x0001,
			MASK_WRITE	= 0x0002,
			MASK_EXCEPT	= 0x0004,
			MASK_ACCEPT	= 0x0008,
			MASK_ET		= 0x0010,

			MASK_DEFAULT = MASK_READ | MASK_WRITE | MASK_EXCEPT | MASK_ET,
		};
	public:
		SocketReactor()
			: m_nWaitTimeMS(5)
		{
		}

		virtual ~SocketReactor()
		{
			this->UpdatePosted();
		}
	public:
		virtual int Startup() = 0;
		virtual int Cleanup() = 0;
	public:
		virtual int Add(SocketBaseConnection* connection,int mask) = 0;
		virtual int Del(SocketBaseConnection* connection) = 0;
		virtual int Mod(SocketBaseConnection* connection,int mask) = 0;
	public:
		virtual int Update() = 0;
	public:
		void PostClose(SocketBaseConnection* connection)
		{
			connection->doref();
			m_vClosePosted.push_back(connection);
		}
	public:
		void SetWaitTimeMS(int ms)
		{
			m_nWaitTimeMS = ms;
		}
	public:
		void UpdatePosted()
		{
			while(!m_vClosePosted.empty())
			{
				SocketBaseConnection* connection = m_vClosePosted.front();
				m_vClosePosted.pop_front();

				connection->OnPostClose();
				connection->unref();
			}
		}
	protected:
		std::list<SocketBaseConnection*> m_vClosePosted;
		int m_nWaitTimeMS;
	};

}

#endif // _pw_socket_reactor_
