#ifndef _pw_gdb_socket_connection_
#define _pw_gdb_socket_connection_

#include "pw_gdb_socket_base_connection.h"
#include "pw_gdb_chunks.h"

namespace gdb
{
	class ChunksWriter;

	class SocketConnection : public SocketBaseConnection
	{
	public:
		SocketConnection(int sock = -1);
	public:
		virtual int OnDataIncoming();
		virtual int OnDataOutgoing();
		virtual int OnClose();
	public:
		void Close();
	public:
		void SendBuffer(const void* data,size_t size);
		void PushSendBuffer(SChunk* chunk);
		void PushSendBuffer(ChunksWriter* chunkwriter);
	public:
		enum EWaitResult
		{
			_WAIT_ERROR = 0x01,
			_WAIT_TIMEOUT = 0x02,
			_WAIT_CLOSE = 0x04,
			_WAIT_READ = 0x08,
			_WAIT_WRITE = 0x10,
		};
	public:
		std::string ToString();
	public:
		static unsigned WaitForReadable(int sock,int millsec = 10);
		static unsigned WaitForWriteable(int sock,int millsec = 10);
	public:
		inline Writer* GetWriter()
		{
			return &m_mWriter;
		}
	public:
		int CommitSendBuffer();
	public:
		int FlushSendBuffer();
	protected:
		bool m_bWriteEnable;
	protected:
		ChunksWriter m_mWriter;
		ChunksReader m_mReader;
	};
}

#endif // _pw_socket_connection_