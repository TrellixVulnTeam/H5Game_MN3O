#ifndef _pw_message_builder_
#define _pw_message_builder_


namespace pwngs
{
	class MessageBuilder
	{
	public:
		virtual int SerializeToArray(char* buf,size_t len) = 0;
	};
}
#endif // _pw_message_builder_