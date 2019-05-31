#include "pwdist_dispatcher.h"
#include "pw_logger.h"

namespace pwdist
{
	Dispatcher::~Dispatcher()
	{
		for(CollectionMethodsT::iterator iter = m_mapMethods.begin();iter != m_mapMethods.end(); ++iter)
			_safe_delete(iter->second);
		m_mapMethods.clear();
	}

	int Dispatcher::Dispatch( MethodCall& call )
	{
		CollectionMethodsT::iterator iter = m_mapMethods.find(call.call->method);
		if(iter == m_mapMethods.end())
		{
			if(OnUnknownCall(call) == 0)
				return 0;

			gErrorStream( "Dispatcher::Dispatch method nofound " << call.call->method
				<< " fromnode=" << call.call->sender.node
				<< " fromport=" << call.call->sender.port);

			return -1;
		}

		call.method = iter->second;

		if(!call.method->enabled)
		{
			gErrorStream( "Dispatcher::Dispatch enabled = false:" << call.call->method
				<< " fromnode=" << call.call->sender.node
				<< " fromport=" << call.call->sender.port
				<< " rpc=" << call.method->name
				);
			return -2;
		}

		if(strlen(call.call->def) != strlen(call.method->mdef))
		{
			gErrorStream( "Dispatcher::Dispatch params error:" << call.call->method
				<< " fromnode=" << call.call->sender.node
				<< " fromport=" << call.call->sender.port
				<< " expected=" << call.method->mdef
				<< " rpc=" << call.method->name
				<< " got=" << call.call->def);
			return -3;
		}

		call.method->pfn(&call);

		return 0;
	}

	int Dispatcher::OnUnknownCall( MethodCall& call )
	{
		return -1;
	}
}
