#include "pw_socket_stream_pump.h"
#include "pw_def.h"
#include "pw_logger.h"
#include "pw_byte_order.h"

namespace pwutils
{
	SocketStreamPump::SocketStreamPump( int bufsize,int maxPacketSize )
	{
		m_nMaxPacketSize = maxPacketSize;
		m_objBuffer.initial(__max(maxPacketSize,bufsize));
	}

	bool SocketStreamPump::Put( char* buf,size_t len )
	{
		if(m_objBuffer.space() < len)
			return false;
		m_objBuffer.put(buf,len);
		return true;
	}

	bool SocketStreamPump::Get( char* buf,size_t len,bool networkOrder/* = false*/)
	{
		if(m_objBuffer.length() <= sizeof(SPacketHeader))
			return false;

		SPacketHeader header = {0};
		m_objBuffer.peek((char*)&header,sizeof(SPacketHeader));

		if(networkOrder)
		{
			pwutils::Convert<int>::ToHostOrder( header.msgid);
			pwutils::Convert<int>::ToHostOrder( header.msglen);
		}

		if(header.msglen <= 0 || header.msglen >= m_nMaxPacketSize || header.msglen <= 0)
		{
			pwasserte(false && "SocketStreamPump::Get invalid packet len");
			m_objBuffer.skip(m_objBuffer.length());
			return false;
		}

		if(header.msglen > m_objBuffer.length())
			return false;

		pwassertr(len >= header.msglen,false);
		
		m_objBuffer.get(buf,header.msglen);

		return true;
	}
}