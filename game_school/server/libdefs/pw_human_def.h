#ifndef _pw_human_xxdef_
#define _pw_human_xxdef_

namespace pwngs
{
	enum
	{
		HUMAN_DBFLAGS_GM = 0x01, // gm
		HUMAN_DBFLAGS_PLANT = 0x02, // ��
		HUMAN_DBFLAGS_FIRSTLOGIN_DONE = 0x04, // �״ε�¼�ѳ�ʼ��
		HUMAN_DBFLAGS_FAKE = 0x08, // ����Ӣ�۽�ɫ
	};


	enum EHumanClientType
	{
		HUMAN_CLIENT_TYPE_FULL, // ������
		HUMAN_CLIENT_TYPE_LITE, // ΢��
		HUMAN_CLIENT_TYPE_WEB,  // ҳ��
		HUMAN_CLIENT_TYPE_NUM,

		HUMAN_CLIENT_TYPE_MIN = HUMAN_CLIENT_TYPE_FULL,
		HUMAN_CLIENT_TYPE_MAX = HUMAN_CLIENT_TYPE_WEB,
	};

	extern const char* cst_szHumanClientTypeNames[];

	const int cst_max_human_level = 300; // ������ȼ�
}

#endif // _pw_human_xxdef_