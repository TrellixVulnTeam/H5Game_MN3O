--------------------------
--�������ű���������
--------------------------

--�������Ͷ���
BAG_TYPE = 1 				--����
EQUIP_TYPE = 2				--װ��
STORAGE_TYPE = 3 			--�ֿ�
ASTROLOGY_TYPE = 4 			--ռ��
RUNE_TYPE = 5  				--���˷�����
SOULSTONE_TYPE = 6			--��ʯ��
BLESSING_TYPE = 7 			--ף����

--�������þ�����
DUNGEON_START = 9000		--�ؿ���ʼ
DUNGEON_END = 9001			--�ؿ�����

--�ٻ�ʦ�������ٻ���С�ܱ��ű�ɱ��������ID
PET_KILLSELF_SKILLID = 1050
PET_KILLSELF_EFFECT = 1050

--�ؿ���ʼ�������Ĵ���ʱ��
DUNGEON_START_TIME = 4
DUNGEON_END_TIME = 2

--�����ؿ��Ĳ�����Ч
PLOT_WAVE1 = 9002
PLOT_WAVE2 = 9003
PLOT_WAVE3 = 9004
PLOT_WAVE4 = 9005
PLOT_WAVE5 = 9006

--���õ�creatureid
CREATURE_FINGER = 80009	--����ָ·��NPCid

--ħ�������õ���ʾstr
STR_MULTI_SUCCEED = 41733
STR_MULTI_FAILD = 41732
STR_MULTI_SUCCEED_ALL = 41734

--Ƶ�����Ͷ���
--[[
ChannelType.Screen			--��Ļ�м���ʾ
ChannelType.System			--ϵͳ��ʾ
ChannelType.Guide			--������ʾ
ChannelType.Prompt			--��ʾ��
ChannelType.PromptAutoHide	--�Զ��ر���ʾ��
ChannelType.Award			--��ý�����ʾ
ChannelType.Announcement	--ϵͳ����
ChannelType.General			--�ۺ�Ƶ��
ChannelType.World			--����Ƶ��
ChannelType.Guild			--����Ƶ��
ChannelType.Horn			--����Ƶ��
ChannelType.Gm				--GMƵ��
--]]

--��������UI����Լ��ID
UI_WARN = 1			--��Ļ�м侯������
UI_TIMER = 2		--����ʱ
UI_BLACK_WHITE = 3	--��Ļ��ڰף��ξ�ģʽ
UI_TIMECOUNTDOWN = 4	--�������ֱ��䵹��ʱ
UI_DTS_SUBLIME = 5 --����ɱ����id[1-N]
UI_DARKARENA_CRAZY= 6 --���ھ������ֿ񱩵���ʱ
UI_LONGYU= 7 --����
UI_TRIAL_LAND = 8 --����֮��
UI_CHALLENGE_TIMER = 9 --��ս��������ʱ
UI_COMBAT_BEGIN = 13	--ս����ʼ
UI_COMBAT_END = 14		--ս������
UI_COLOR = 15					--��ɫ�仯
UI_GRAY = 16			--ȫ���û�

--��������UI����Լ������(��ս��������ʱ)
UI_CHALLENGE_TIMER_BEGIN = 1 -- ��ʼ
UI_CHALLENGE_TIMER_NEXT = 2 -- ���ؽ�������ʼ��һ��
UI_CHALLENGE_TIMER_END = 3 -- ͨ��ȫ���ؿ�

-- ��ʾ��Ϣ����
CHAT_MODE_SCREEN			= 0x0001    --��Ļ�м���ʾ
CHAT_MODE_SYSTEM			= 0x0002    --ϵͳ��ʾ
CHAT_MODE_GUIDE				= 0x0004    --������ʾ
CHAT_MODE_PROMPT_NORMAL		= 0x0008    --��ʾ��
CHAT_MODE_PROMPT_AUTO_HIDE	= 0x0010    --�Զ��ر���ʾ��
CHAT_MODE_AWARD				= 0x0020    --��ý�����ʾ
CHAT_MODE_ANNOUNCEMENT		= 0x0040    --ϵͳ����
-- ����Ƶ������
CHAT_MODE_GENERAL			= 0x0100    --�ۺ�Ƶ��
CHAT_MODE_WORLD				= 0x0200    --����Ƶ��
CHAT_MODE_GUILD				= 0x0400    --����Ƶ��
CHAT_MODE_HORN				= 0x0800    --����Ƶ��
CHAT_MODE_GM				= 0x1000    --GMƵ��
CHAT_MODE_STAGE				= 0x2000    --����Ƶ��
CHAT_MODE_TEAM				= 0x4000    --����Ƶ��
CHAT_MODE_WHISPER			= 0x8000    --˽��Ƶ��


-- ��Ϣ���ͷ���
CHAT_TEXT_UNKNOWN 			= 0		-- ��Ч��Ϣ
CHAT_TEXT_SYSTEM			= 1		-- ϵͳ��Ϣ
CHAT_TEXT_PUBLIC_NOTIFY		= 2		-- ������Ϣ
CHAT_TEXT_ACTIVITY_NOTIFY	= 3		-- ͨ����Ϣ
CHAT_TEXT_MAIL_NOTIFY		= 4		-- �ʼ���Ϣ
CHAT_TEXT_WORLD				= 5		-- ������Ϣ
CHAT_TEXT_GUILD				= 6		-- ������Ϣ
CHAT_TEXT_LOG				= 7		-- ��־��Ϣ
CHAT_TEXT_WHISPER			= 8		-- ˽����Ϣ


----------------------------------ս��ϵͳ�ӷ�-----------------------------------------------------------------------------------------
----�õ��ĺ�����AddMilitaryScore����1��ʾ1V1��2��ʾ3V3��3��ʾ15V15��4��ʾҰ�⣬5��ʾ����ս�Ϳ������ս
BattleGod = {YW = {},BBZ = {},}
BattleGod.YW[1] = 20----Ұ��ɱ���߻�õ�ս�������

BattleGod.BBZ[1] = 100 -----��������ս����ӵ�ս��Ļ�����

-----------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------��������Թ����Ӿ��鹫ʽ����-------------------------------------------------------------------------------------
MULTIPLE1 = 750	------1���ÿ��������飬���鱶��Ϊ�ȼ��ķֶκ���
MULTIPLE2 = 1250 ------2���ÿ��������飬���鱶��Ϊ�ȼ��ķֶκ���
EXPTIME = 10	-------ÿ����ø������һ�ξ���,����ֶ�д���˻�ű���@����
-----------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------
