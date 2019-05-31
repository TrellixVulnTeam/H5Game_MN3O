#ifndef _pw_gdb_socket_base_connection_
#define _pw_gdb_socket_base_connection_

namespace gdb
{
	class SocketReactor;

	class SocketBaseConnection
	{
	public:
		enum
		{
			SOCKET_FLAGS_CLOSE_POSTED = 0x0001,
			SOCKET_FLAGS_CLOSED = 0x0002,
		};
	public:
		SocketBaseConnection(int sock = -1);
		virtual ~SocketBaseConnection();
	public:
		virtual int GetSocket()
		{
			return m_nSocket;
		}
	public:
		void PostClose();
	public:
		virtual int OnReactorAttached(SocketReactor* reactor);
		virtual int OnReactorDetached(SocketReactor* reactor);
	public:
		virtual int OnDataIncoming();
		virtual int OnDataOutgoing();
		virtual int OnClose();
		virtual int OnPostClose();
	public:
		virtual int doref() = 0;
		virtual int unref() = 0;		
	protected:
		int m_nSocket;
	protected:
		SocketReactor* m_pReactor;
	protected:
		unsigned int m_nFlags;
	};
}

#endif // _pw_socket_base_connection_