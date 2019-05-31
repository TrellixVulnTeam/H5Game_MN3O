#include "pwdist_port_generic.h"
#include "pw_time.h"

namespace pwdist
{
	// -------------------------------------------------------------------------------------------------------

	GenericPort::GenericPort()
	{
	}

	int GenericPort::DispatchChunk( ICallableObject* obj,char* buf,size_t len )
	{
		MsgCall* call = (MsgCall*)buf;
		assert((size_t)call->msglen == len);

		call->params.LoadPtr(buf + sizeof(MsgCall),len - sizeof(MsgCall));

		MethodCall callinfo = {0};
		callinfo.call = call;
		callinfo.obj = obj;
		callinfo.port = this;

		m_lstIncomingCalls.push_back(ManagedMsgCallPtr(new ManagedMsgCall(call,m_nCurrentTick)));
		int result = this->Dispatch(callinfo);
		m_lstIncomingCalls.pop_back();

		return result;
	}

	Port* GenericPort::self()
	{
		return (Port*)i_GetCurrentPort();
	}

}