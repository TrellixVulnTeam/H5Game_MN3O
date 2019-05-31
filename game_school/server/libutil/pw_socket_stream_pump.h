#ifndef _pw_socket_stream_pump_
#define _pw_socket_stream_pump_

#include "pw_circle_buffer.h"
#include "pw_packet_def.h"

namespace pwutils
{
	class SocketStreamPump
	{
	public:
		SocketStreamPump(int bufsize,int maxPacketSize);
	public:
		bool Put(char* buf,size_t len);
		bool Get(char* buf,size_t len,bool networkOrder = false);
	public:
		inline int GetLength()
		{
			return m_objBuffer.length();
		}
	protected:
		int m_nMaxPacketSize;
		CircleBuffer m_objBuffer;
	};

}

#endif // _pw_socket_stream_pump_
