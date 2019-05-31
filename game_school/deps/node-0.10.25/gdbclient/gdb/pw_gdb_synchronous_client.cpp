#include "pw_gdb_synchronous_client.h"
#include "pw_gdb_def.h"
#include <iostream>

namespace gdb
{
	void SynchronousClient::OnRequstPerformed( Request& req )
	{
		ClientInterface::OnRequstPerformed(req);

		FetchResponse(req.requestId,&m_mLastResponse);

		if(m_mLastResponse.packets.size() == 0)
		{
			std::cerr << __FUNCTION__ << " can't get response:" << req.cmd << std::endl;
		}
	}

	bool SynchronousClient::IsSuccessful()
	{
		return m_mLastResponse.GetErrorCode() == FAILED_SUCCESSFUL;
	}

	bool SynchronousClient::IsSuccessfulButNoFound()
	{
		return m_mLastResponse.GetErrorCode() == FAILED_NOFOUND;
	}

}