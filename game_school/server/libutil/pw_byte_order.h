#ifndef _pw_byte_order_
#define _pw_byte_order_

#include "pw_def.h"
#include "pw_platform.h"

namespace pwutils
{
	extern uint64 ntohll(uint64 value);
	extern uint64 htonll(uint64 value);
	
	template<class T> struct Convert
	{
		
	};
	
	template<> struct Convert<uint16>
	{
		static void ToHostOrder(uint16& val)
		{
			val = ntohs(val);
		}

		static void ToNetworkOrder(uint16& val)
		{
			val = htons(val);
		}
	};

	template<> struct Convert<uint32>
	{
		static void ToHostOrder(uint32& val)
		{
			val = ntohl(val);
		}

		static void ToNetworkOrder(uint32& val)
		{
			val = htonl(val);
		}
	};

	template<> struct Convert<unsigned long>
	{
		static void ToHostOrder(unsigned long& val)
		{
			val = ntohl(val);
		}

		static void ToNetworkOrder(unsigned long& val)
		{
			val = htonl(val);
		}
	};
	
	template<> struct Convert<uint64>
	{
		static void ToHostOrder(uint64& val)
		{
			val = ntohll(val);
		}

		static void ToNetworkOrder(uint64& val)
		{
			val = htonll(val);
		}
	};

	template<> struct Convert<int>
	{
		static void ToHostOrder(int& val)
		{
			val = ntohl(val);
		}

		static void ToNetworkOrder(int& val)
		{
			val = htonl(val);
		}
	};
}

#endif //_pw_byte_order_
