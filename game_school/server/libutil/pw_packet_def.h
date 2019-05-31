#ifndef _pw_packet_def_
#define _pw_packet_def_

namespace pwutils
{
#pragma pack(push,1)

	const int msgid_packet_rpc = -100;
	const int msgid_packet_rpc_result = -101;

	const int msgflags_except_result = 0x0001;

	struct SPacketHeader
	{
		int msglen;
		int msgid;
	};

	struct MsgRpcCommon : public SPacketHeader
	{
		int64 cid;
		int32 mid;
		int32 flags;
	};


#pragma pack(pop)
}

#endif // _pw_packet_def_