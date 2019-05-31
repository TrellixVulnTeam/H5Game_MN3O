#ifndef _pw_warlord_def_
#define _pw_warlord_def_

#include "pw_def.h"
#include "pw_ngs_def.h"
#include "kvdb/pw_fixed_string.h"
#include "kvorm/pw_orm_warlordcombatresult.h"

namespace pwngs
{
	const int32 cst_warlord_top_start = 1;
	const int32 cst_warlord_top_end = 3;

	const int32 cst_warlord_rival_max = 3;			// ����ս���������

	const int32	cst_warlord_broadcast_top = 1;			// ͷ���㲥 
	const int32	cst_warlord_broadcast_win_idx = 5;		// ��ʤ�㲥���
	const int32	cst_warlord_broadcast_win_start = 10;	// ��ʤ�㲥��ʼ
	const int32	cst_warlord_broadcast_worship = 10;		// Ĥ�ݹ㲥

	const int32 cst_warlord_special_rank = 10;	// ����10���������⴦��

	enum EWarlordOperCode
	{
		WARLORD_NOTIFY_SUCCESS = 0,
		
		WARLORD_NOTIFY_ENTER = 56300,					// ����

		WARLORD_NOTIFY_COMBAT_CANNOT_CHALLENGE	= 56301,	//������ս
		WARLORD_NOTIFY_COMBAT_CD_ING			= 56302,	// ��ս-CD��

		WARLORD_NOTIFY_NOT_RESET_CD				= 56303,	//û������CD
		WARLORD_NOTIFY_RESET_CD_NOT_GOLD		= 56304,	//û���㹻�Ľ������CD

		WARLORD_NOTIFY_COMBAT_RIVAL_NOT_EXIST = 56310,	// ��ս-����ս�߲�����
		WARLORD_NOTIFY_COMBAT_SELF,						// ��ս-��ս�Լ�
		WARLORD_NOTIFY_COMBAT_CNT_LIMIT,				// ��ս-�����ս��������
		WARLORD_NOTIFY_COMBAT_ADD_NOT_ENOUGH_GOLD,		// ��ս-���ν�Ҳ���
		WARLORD_NOTIFY_COMBAT_ADD_CNT_LIMIT,			// ��ս-�����������
		WARLORD_NOTIFY_COMBAT_TOP_LIMIT,				// ��ս-������սǰ����
		
		
		WARLORD_NOTIFY_DRAW_NO_AWARD = 56330,			// �콱-�޿��콱��
		WARLORD_NOTIFY_DRAW_BAG_LIMIT,					// �콱-�����ռ䲻��

		WARLORD_NOTIFY_BROADCAST_WIN = 56340,			// �㲥-��ʤ
		WARLORD_NOTIFY_BROADCAST_TOP,					// �㲥-ͷ��
		WARLORD_NOTIFY_BROADCAST_WORSHIP,				// �㲥-Ĥ��

		WARLORD_NOTIFY_HONOR_INVALID_ARGS = 56350,		// ����-��������
		WARLORD_NOTIFY_HONOR_NOT_ENOUGH,				// ����-��������

		WARLORD_NOTIFY_WORSHIP_NOT_EXIST = 56360,		// Ĥ��-��Ҳ�����
		WARLORD_NOTIFY_WORSHIP_CNT_LIMIT,				// Ĥ��-��������
		WARLORD_NOTIFY_WORSHIP_SELF,					// Ĥ��-Ĥ���Լ�
		WARLORD_NOTIFY_WORSHIP_RANK_LIMIT,				// Ĥ��-��������(��ǰ����)
	};

	enum EWarlordBroadcastType
	{ 
		WARLORD_BROADCAST_WIN = 0,		// ��ʤ�㲥
		WARLORD_BROADCAST_TOP,			// ͷ���㲥
		WARLORD_BROADCAST_WORSHIP,		// Ĥ�ݹ㲥

		WARLORD_BROADCAST_MAX,
	};

	enum EWarlordCombatResultType
	{
		WARLORD_COMBAT_RESULT_ERROR = -1,			// ����

		WARLORD_COMBAT_SUCC_RANK_NOT_CHANGE = 0,	// �ɹ���������
		WARLORD_COMBAT_SUCC_RANK_CHANGE,			// �ɹ������仯
		WARLORD_COMBAT_FAIL,						// ʧ��
	};

	enum EWarlordModCombatType
	{
		WARLORD_MOD_COMBAT_TYPE_REDUCE = 0,			// ���ٴ���
		WARLORD_MOD_COMBAT_TYPE_ADD,				// ���Ӵ���
	};

	enum EWarlordGrantRankAwardType
	{
		WARLORD_GRANT_RANK_AWARD_TYPE_CTRL_TIMER = 0,		// ctrl��ʱ����
		WARLORD_GRANT_RANK_AWARD_TYPE_RPC,					// rpc����
	};

	typedef orm::WarlordCombatResult SWarlordCombatResult;

	enum
	{
		EType_Human = 1,	//Human
		EType_NPC = 2,	//npc
	};

	struct SWarlordCombatResultData
	{
		int32 type;
		uint8 src_type;
		int64 src_id;
		int64 src_rank;
		pwutils::fixed_string<64> src_name;
		uint8 dst_type;
		int64 dst_id;
		int64 dst_rank;
		pwutils::fixed_string<64> dst_name;
		int64 combat_time;

		SWarlordCombatResultData()
		{
			type = -1;
			src_type = 0;
			src_id = 0;
			src_rank = 0;
			src_name = "";
			dst_type = 0;
			dst_id = 0;
			dst_rank = 0;
			dst_name = "";
			combat_time = 0;
		}
	};

	struct SWarlordData
	{
		int64 id;
		uint8 type;
		int64 hid;
		int64 win_count;
		int64 worship_today;
		int64 worship_total;
		int32 last_worship_date;
		SWarlordCombatResultData results[20];

		SWarlordData()
		{
			id = 0;
			type = 0;
			hid = 0;
			win_count = 0;
			worship_total = 0;
			worship_total = 0;
			last_worship_date = 0;
		}
	};

	// ��ȡ��ս�б����
	struct SWarlordParam
	{
		SWarlordParam() 
			: bRefresh(false)
			, bFirstCombat(false)
		{}

		bool bRefresh;	//�Ƿ����
		int64 arrRanks[3];
		bool bFirstCombat;	//�״���ս
	};

	struct SChallengeInfo
	{
		SChallengeInfo()
			: rank(0)
			, type(0)
			, hid(0)
		{}

		int64 rank;
		uint8 type;
		int64 hid;
	};

	struct SChallengeWarlordInfo
	{
		SChallengeWarlordInfo()
		{}

		static const int size = 3;

		SChallengeInfo arrChallengeInfo[size];
	};
}

#endif // _pw_warlord_def_