#ifndef _pw_chat_def_
#define _pw_chat_def_

namespace pwngs
{
	const sint32 cst_chat_max_cached_item_num = 500;
	const sint32 cst_max_contact_num = 10;

	// ��������Ƽ��б�CDʱ�䣬��λ��
	const sint32 cst_recommend_request_cd = 3 ;

	enum EQueryPlayerType
	{
		QUERY_PLAYER_EQUIPMENT = 0,
		QUERY_PLAYER_ITEM,
		QUERY_PLAYER_ACHIEVEMENT,
		QUERY_PLAYER_HERO,
		QUERY_PLAYER_BLOOD,
		QUERY_PLAYER_RIDE,
		QUERY_PLAYER_INFO,
		QUERY_PLAYER_HOLY_WEAPON,
		QUERY_PLAYER_HERO_CARD,
		QUERY_PLAYER_LANSQUENET,
		QUERY_PLAYER_MAGIC_WEAPON,
		QUERY_PLAYER_PET,

		QUERY_PLAYER_MAX,
	};

	// ����Ƶ������ʾ��Ϣ
	enum EChatMode
	{
		CHAT_MODE_UNKNOWN			= 0x0000,		// δ֪Ƶ��(��ѡ��ͻ��˶���ȡmod)

		// ��ʾ��Ϣ����
		CHAT_MODE_SCREEN			= 0x0001,		// ��Ļ�м���ʾ		--1
		CHAT_MODE_SYSTEM			= 0x0002,		// ϵͳ��ʾ			--2
		CHAT_MODE_GUIDE				= 0x0004,		// ������ʾ			--4	
		CHAT_MODE_PROMPT_NORMAL		= 0x0008,		// ��ʾ��			--8
		CHAT_MODE_PROMPT_AUTO_HIDE	= 0x0010,		// �Զ��ر���ʾ��		--16
		CHAT_MODE_AWARD				= 0x0020,		// ��ý�����ʾ		--32
		CHAT_MODE_ANNOUNCEMENT		= 0x0040,		// ϵͳ����			--64

		// ����Ƶ������
		CHAT_MODE_GENERAL			= 0x0100,		// �ۺ�Ƶ��			--256
		CHAT_MODE_WORLD				= 0x0200,		// ����Ƶ��			--512
		CHAT_MODE_GUILD				= 0x0400,		// ����Ƶ��			--1024
		CHAT_MODE_HORN				= 0x0800,		// ����Ƶ��			--2048
		CHAT_MODE_GM				= 0x1000,		// GMƵ��			--4096
		CHAT_MODE_STAGE				= 0x2000,		// ����Ƶ��			--8192
		CHAT_MODE_TEAM				= 0x4000,		// ����Ƶ��			--16384
		CHAT_MODE_WHISPER			= 0x8000,		// ˽��Ƶ��			--32768
		CHAT_MODE_LADDER_HORN		= 0x10000,		// �������	
	};

	// ��Ϣ���ͷ���
	enum EChatText
	{
		CHAT_TEXT_UNKNOWN = 0,				// ��Ч��Ϣ
		CHAT_TEXT_SYSTEM,					// ϵͳ��Ϣ
		CHAT_TEXT_PUBLIC_NOTIFY,			// ������Ϣ
		CHAT_TEXT_ACTIVITY_NOTIFY,			// ͨ����Ϣ
		CHAT_TEXT_MAIL_NOTIFY,				// �ʼ���Ϣ
		CHAT_TEXT_WORLD,					// ������Ϣ
		CHAT_TEXT_GUILD,					// ������Ϣ
		CHAT_TEXT_LOG,						// ��־��Ϣ
		CHAT_TEXT_WHISPER,					// ˽����Ϣ
		CHAT_TEXT_STAGE,					// ������Ϣ
		CHAT_TEXT_TEAM,						// ������Ϣ

	};

	const sint32 cst_chat_invalid_human_text_type[] = 
	{
		CHAT_TEXT_UNKNOWN,
		CHAT_TEXT_SYSTEM,
		CHAT_TEXT_PUBLIC_NOTIFY,
		CHAT_TEXT_ACTIVITY_NOTIFY,
		CHAT_TEXT_MAIL_NOTIFY,
		CHAT_TEXT_LOG,
	};

	// ������ϵ�˻�����Ϣ
	//struct SChatHumanInfo
	//{
	//	sint32 nSex;
	//	sint32 nPro;
	//	sint32 nLevel;
	//	sint32 nTitle;
	//};

	struct SRelationMemberInfo
	{
		int64 rid;
		int32 sex;
		int32 pro;
		bool isOnline;
		int32 state;
		int32 map_id;
		int32 level;
		int32 fight_point;

		SRelationMemberInfo()
		{
			memset(this,0,sizeof(*this));
		}
	};
}

#endif // _pw_chat_def_