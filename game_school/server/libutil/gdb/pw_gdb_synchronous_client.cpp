#include "pw_gdb_synchronous_client.h"
#include "pw_gdb_def.h"
#include <iostream>

namespace gdb
{
	void SynchronousClient::OnRequstPerformed( Request& req )
	{
		if(this->IsConnected())
		{
			ClientInterface::OnRequstPerformed(req);

			if(this->FlushSendBuffer() != 0)
			{
				std::cerr << __FUNCTION__ << " FlushSendBuffer failed:" << req.cmd << std::endl;
				return ;
			}
			this->FetchResponse(req.requestId,&m_mLastResponse);

			if(m_mLastResponse.packets.size() == 0)
			{
				std::cerr << __FUNCTION__ << " can't get response:" << req.cmd << std::endl;
			}
		}
		else
		{
			m_mLastResponse.packets.clear();
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