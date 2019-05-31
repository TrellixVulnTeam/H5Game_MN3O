#ifndef _pw_gdb_synchronous_client_
#define _pw_gdb_synchronous_client_

#include "pw_gdb_client_interface.h"

namespace gdb
{
	class SynchronousClient : public ClientInterface
	{
	public:
		bool IsSuccessful();
		bool IsSuccessfulButNoFound();
	public:
		inline Response* GetResponse()
		{
			return &m_mLastResponse;
		}
	protected:
		virtual void OnRequstPerformed(Request& req);
	protected:
		Response m_mLastResponse;
	};
}

#endif // _pw_gdb_synchronous_client_