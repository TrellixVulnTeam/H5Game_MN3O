#ifndef _pw_global_event_
#define _pw_global_event_

namespace pwngs
{
	enum
	{
		GLOBAL_EVENT_DAILY_CHARGE_CHANGED = 1, // �����ۼƳ�ֵ
		GLOBAL_EVENT_DAILY_SPEND_CHANGED, // �����ۼ�����
	};

	enum
	{
		GLOBAL_EVENT_FLAGS_SYNC = 0x0001,
	};
}

#endif // _pw_global_event_