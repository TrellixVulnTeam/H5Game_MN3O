-----------------------------------------------------------------
--����
--С��ͼ��ʾ����·����ͼ����ʾ���ԣ�����С��ͼ��ʱ��֪ͨǰ���޸�,�ű��Ѿ�����
--��Чǽû��
--��ģ������ģ��û����
--���½����а��������Ϣ�������ᱣ����һ��������

-- �:���ս�������
-- �����������
-----------------------------------------------------------------

CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
local R_Encampment_POS = {16.1,55.7,17.81}		--�췽����
local R_ResurrectPOS = {32.85,55.6,31.25}		--�췽�����
local R_NpcSpawnPos1 = {29.8,55.72,13.1}	--�췽NPCˢ�ֵ���
local R_NpcSpawnPos2 = {14.2,55.72,32.4}	--�췽NPCˢ�ֵ���
local R_NpcSpawnPos3 = {26.6,55.72,26.1}	--�췽NPCˢ�ֵ���
local R_Tower1_pos = {52.4,55,15.2}			--��·��
local R_Tower2_pos = {133.4,50,14.1}		--��·��1
local R_Tower3_pos = {236.2,50,17.5}		--��·��2
local R_Tower4_pos = {16.1,55,56}		--��·��
local R_Tower5_pos = {14.6,50,128.7}		--��·��1
local R_Tower6_pos = {18.7,50,223.9}		--��·��2
local R_Tower7_pos = {43.4,55,37.4}		--��·��
local R_Tower8_pos = {77,50,65.4}		--��·��1
local R_Tower9_pos = {118,50,110.6}		--��·��2


local B_Encampment_POS = {275.1,55.7,278.2}	--��������
local B_ResurrectPOS = {263.4,55.6,268.3}	--���������
local B_NpcSpawnPos1 = {260.16,55.7,282.28}---ˢ�ֵ���
local B_NpcSpawnPos2 = {280.99,55.7,264.89}---ˢ�ֵ���
local B_NpcSpawnPos3 = {263.55,55.7,267.08}---ˢ�ֵ���
local B_Tower1_pos = {233,55,281.2}--��·��
local B_Tower2_pos = {164.1,50.2,279.6}--��·��1
local B_Tower3_pos = {76.2,50,281.5}--��·��2
local B_Tower4_pos = {284.5,55,243.7}--��·��
local B_Tower5_pos = {282.1,50.1,174.6}--��·��1
local B_Tower6_pos = {285.9,50,66.8}--��·��2
local B_Tower7_pos = {249,55,253.5}--��·��
local B_Tower8_pos = {216.7,51.8,214.5}--��·��1
local B_Tower9_pos = {171.9,50,170.6}--��·��2

local R_LWayPos = {277,50,39}	-----����·���е㣬С����Ѱ���е���ȥѰ��
local R_RWayPos = {23,50,265}
local R_ZWayPos = {140,50,140.9}
local B_LWayPos = {23,50,265}
local B_RWayPos = {277,50,39}
local B_ZWayPos = {140,50,140.9}

local WayRadius = 5				-----����·�м䴴��Բ������������С����ӱ��
local WayBuff = 351  			-----���buff

--��ͬ����ε�NPCID��һ��
local PVP_NpcsTable = {
	[80] = {
		R_EncampmentId = 100001,	--�췽��Ӫ����ID
		B_EncampmentId = 100021,    --������Ӫ����ID
		R_NpcId1 = {100008},		--�췽С�֣����
		R_NpcId2 = {100009},		--�췽С�֣��Ҳ�
		R_NpcId3 = {100010},		--�췽С�֣��м�
		B_NpcId1 = {100028},
		B_NpcId2 = {100029},
		B_NpcId3 = {100030},
		R_TowerId1 = 100002,		--�췽��������
		R_TowerId2 = 100003,		--�췽��������1
		R_TowerId3 = 100004,		--�췽��������2
		R_TowerId4 = 100005,		--�췽�����ҡ���
		R_TowerId5 = 100006,		--�췽�����ҡ���1
		R_TowerId6 = 100007,		--�췽�����ҡ���2
		R_TowerId7 = 100011,		--�췽�����С���
		R_TowerId8 = 100012,		--�췽�����ҡ���1
		R_TowerId9 = 100013,		--�췽�����ҡ���2
		B_TowerId1 = 100022,		---����
		B_TowerId2 = 100023,
		B_TowerId3 = 100024,
		B_TowerId4 = 100025,
		B_TowerId5 = 100026,
		B_TowerId6 = 100027,
		B_TowerId7 = 100031,
		B_TowerId8 = 100032,
		B_TowerId9 = 100033,
		},
	[120] = {
		R_EncampmentId = 100101,	--�췽��Ӫ����ID
		B_EncampmentId = 100121,    --������Ӫ����ID
		R_NpcId1 = {100108},		--�췽С�֣����
		R_NpcId2 = {100109},		--�췽С�֣��Ҳ�
		R_NpcId3 = {100110},		--�췽С�֣��м�
		B_NpcId1 = {100128},
		B_NpcId2 = {100129},
		B_NpcId3 = {100130},
		R_TowerId1 = 100102,		--�췽��������
		R_TowerId2 = 100103,		--�췽��������1
		R_TowerId3 = 100104,		--�췽��������2
		R_TowerId4 = 100105,		--�췽�����ҡ���
		R_TowerId5 = 100106,		--�췽�����ҡ���1
		R_TowerId6 = 100107,		--�췽�����ҡ���2
		R_TowerId7 = 100111,		--�췽�����С���
		R_TowerId8 = 100112,		--�췽�����ҡ���1
		R_TowerId9 = 100113,		--�췽�����ҡ���2
		B_TowerId1 = 100122,		---����
		B_TowerId2 = 100123,
		B_TowerId3 = 100124,
		B_TowerId4 = 100125,
		B_TowerId5 = 100126,
		B_TowerId6 = 100127,
		B_TowerId7 = 100131,
		B_TowerId8 = 100132,
		B_TowerId9 = 100133,
		},
	[160] = {
		R_EncampmentId = 100201,	--�췽��Ӫ����ID
		B_EncampmentId = 100221,    --������Ӫ����ID
		R_NpcId1 = {100208},		--�췽С�֣����
		R_NpcId2 = {100209},		--�췽С�֣��Ҳ�
		R_NpcId3 = {100210},		--�췽С�֣��м�
		B_NpcId1 = {100228},
		B_NpcId2 = {100229},
		B_NpcId3 = {100230},
		R_TowerId1 = 100202,		--�췽��������
		R_TowerId2 = 100203,		--�췽��������1
		R_TowerId3 = 100204,		--�췽��������2
		R_TowerId4 = 100205,		--�췽�����ҡ���
		R_TowerId5 = 100206,		--�췽�����ҡ���1
		R_TowerId6 = 100207,		--�췽�����ҡ���2
		R_TowerId7 = 100211,		--�췽�����С���
		R_TowerId8 = 100212,		--�췽�����ҡ���1
		R_TowerId9 = 100213,		--�췽�����ҡ���2
		B_TowerId1 = 100222,		---����
		B_TowerId2 = 100223,
		B_TowerId3 = 100224,
		B_TowerId4 = 100225,
		B_TowerId5 = 100226,
		B_TowerId6 = 100227,
		B_TowerId7 = 100231,
		B_TowerId8 = 100232,
		B_TowerId9 = 100233,
		},
	[200] = {
		R_EncampmentId = 100301,	--�췽��Ӫ����ID
		B_EncampmentId = 100321,    --������Ӫ����ID
		R_NpcId1 = {100308},		--�췽С�֣����
		R_NpcId2 = {100309},		--�췽С�֣��Ҳ�
		R_NpcId3 = {100310},		--�췽С�֣��м�
		B_NpcId1 = {100328},
		B_NpcId2 = {100329},
		B_NpcId3 = {100330},
		R_TowerId1 = 100302,		--�췽��������
		R_TowerId2 = 100303,		--�췽��������1
		R_TowerId3 = 100304,		--�췽��������2
		R_TowerId4 = 100305,		--�췽�����ҡ���
		R_TowerId5 = 100306,		--�췽�����ҡ���1
		R_TowerId6 = 100307,		--�췽�����ҡ���2
		R_TowerId7 = 100311,		--�췽�����С���
		R_TowerId8 = 100312,		--�췽�����ҡ���1
		R_TowerId9 = 100313,		--�췽�����ҡ���2
		B_TowerId1 = 100322,		---����
		B_TowerId2 = 100323,
		B_TowerId3 = 100324,
		B_TowerId4 = 100325,
		B_TowerId5 = 100326,
		B_TowerId6 = 100327,
		B_TowerId7 = 100331,
		B_TowerId8 = 100332,
		B_TowerId9 = 100333,
		},
	}
	
	
--�������޵�BUFF
local Aura_wudi = 304


	
--�������ͻ��أ����ݻٺ��ģ�ͱ���
local Dest_towerR = 100050
local Dest_towerB = 100052
local Dest_encamR = 100051
local Dest_encamB = 100053

--��ʼ��������NPC�ȼ�Ϊ80
CurrentDungeonScript.CurrentLv = 80
local NpcSpawnTimer = 30	--����С��ˢ�¼��
CurrentDungeonScript.Wavenum = 1	--��¼��ǰ�ǵڼ�����
local WaveMonsCount = 7		--ÿ����ˢ�����--7

--�����ݻ�STR
local Str_TowerKilled1 = 100502	--�ҷ��������ݻ�
local Str_TowerKilled2 = 100503	--�ҷ��������ݻ�
local Str_TowerKilled3 = 100504	--�з��������ݻ�
local Str_TowerKilled4 = 100505	--�з��������ݻ�
local Str_TowerKilled5 = 100526	--�ҷ��������ݻ�
local Str_TowerKilled6 = 100527	--�з��������ݻ�
--��ȡBUFF��Ϣstr
local Str_getbuff_speed1 = 100506		--�ҷ�С�ּ��ٶ�
local Str_getbuff_speed2 = 100507		--�з�С�ּ��ٶ�
local Str_getbuff_blood1 = 100508		--�ҷ�С�ּ�Ѫ
local Str_getbuff_blood2 = 100509		--�з�С�ּ�Ѫ
local Str_getbuff_addnum1 = 100510		--�ҷ�С�ּ�����
local Str_getbuff_addnum2 = 100511		--�з�С�ּ�����




--�����������
local Buff_SpawnTime = 100	--BUFF��ˢ�¼��
local Buff_PosTable = {	--����BUFF����
	pos1 = {135.21,54.39,234.95},
	pos2 = {229.53,54.39,149.08},
	pos3 = {163.3,54.39,64.94},
	pos4 = {70.22,54.39,129.86},
	pos5 = {143.9,51.47,146.7},
	}
local Buff_IdTable = {	--����BUFF����
	id1 = 100041,	--���ٶ�
	id2 = 100042,	--��Ѫ��
	id3 = 100043,}	--��ˢ��
local BUFF_speed = 30400
local BUFF_blood1 = 30410
local BUFF_blood2 = 30411
local BUFF_addmons_num = 3	--��BUFF��ӵĲ���

	--������Ӫ
local R_Faction_human = 3	--�췽�����Ӫ
local B_Faction_human = 4
local R_Faction_tower = 9	--�췽����Ӫ
local B_Faction_tower = 10
local R_Faction_npc = 11	--�췽С����Ӫ
local B_Faction_npc = 12

--С��ͼЭ����أ���Ҫǰ������޸ĵ���ʽ��ͼ�㶨���ڸ�����ѣ�GetMonsterInfo
local Map_type_human = 15	--���
local Map_type_monster = 16	--С��
local Map_type_R_encam = 1	--�췽����
local Map_type_R_tower1 = 2	--�췽������࣬��
local Map_type_R_tower2 = 3	--�췽������࣬��1
local Map_type_R_tower3 = 4	--�췽������࣬��2
local Map_type_R_tower4 = 5	--�췽�����Ҳ࣬��
local Map_type_R_tower5 = 6	--�췽�����Ҳ࣬��1
local Map_type_R_tower6 = 7	--�췽�����Ҳ࣬��2
local Map_type_R_tower7 = 20	--�췽�����м䣬��
local Map_type_R_tower8 = 21	--�췽�����м䣬��1
local Map_type_R_tower9 = 22	--�췽�����м䣬��2

local Map_type_B_encam = 8	--��������
local Map_type_B_tower1 = 9		--����������࣬��
local Map_type_B_tower2 = 10	--����������࣬��1
local Map_type_B_tower3 = 11	--����������࣬��2
local Map_type_B_tower4 = 12	--���������Ҳ࣬��
local Map_type_B_tower5 = 13	--���������Ҳ࣬��1
local Map_type_B_tower6 = 14	--���������Ҳ࣬��2
local Map_type_B_tower7 = 23	--���������м䣬��
local Map_type_B_tower8 = 24	--���������м䣬��1
local Map_type_B_tower9 = 25	--���������м䣬��2

local Map_type_buff_speed = 17	--���ٶ�ˮ������ID
local Map_type_buff_blood = 18	--��Ѫˮ������ID
local Map_type_buff_addmons = 19	--��ˢ��ˮ������ID


local Map_state_dead = 0	--����	
local Map_state_live = 1	--���
local Map_race_human = 1	--�췽
local Map_race_spirit = 2	--����


--��¼���ĸ���
CurrentDungeonScript.R_towercount = 10
CurrentDungeonScript.B_towercount = 10


--����С�֣�������˳���Ӧ����1����2������
--Ĭ�����30����creatureID�����������ҵȼ������¸�ֵ
CurrentDungeonScript.MonsVsTower = {}




CurrentDungeonScript.Timer_begain = 60		--��������ʱ-60
CurrentDungeonScript.Timer_checkenter = 40		--�೤ʱ�����������40S
local min_human_count = 3	--��ͽ�������������--3
local fillmember_time = 180	--���˳���ʱ��

CurrentDungeonScript.human_num = 0	--��ʱ�����ã������ݣ�����ҷ��������Ӫ

--��Чǽ���
--������Чǽ
function CurrentDungeonScript:BroadcastBlockEffectsStatus()
-- pwdist.log("��Чǽ����")
    for k,v in pairs(self.BlockEffects) do
        self.Stage:GetModDetour():EnableBlockEffects(k,v)
    end
-- pwdist.log("��Чǽ����end")
end
--�ر���Чǽ
function CurrentDungeonScript:DisableAllBlockEffects()
-- pwdist.log("��Чǽ�ر�")
    for k,v in pairs(self.BlockEffects) do
        self.Stage:GetModDetour():EnableBlockEffects(k,false)
    end
    
    self.BlockEffects = {}
-- pwdist.log("��Чǽ�ر�end")
end
--�ĸ���Чǽ
CurrentDungeonScript.BlockEffects = {}
CurrentDungeonScript.BlockEffects[50] = true
CurrentDungeonScript.BlockEffects[51] = true
CurrentDungeonScript.BlockEffects[52] = true
CurrentDungeonScript.BlockEffects[53] = true
CurrentDungeonScript.BlockEffects[54] = true
CurrentDungeonScript.BlockEffects[55] = true

--��ɫ�������볡str
local Str_humanenter = 100512
local Str_humanleave = 100513

--ս���淨��ʾstr
local Str_gamehint = {
	[1] = 13104,
	[2] = 13105,
	[3] = 13106,
	}

--����ɱ��������Ҽ�BUFF
local KillNum_AddBuff = {
[50] = {["buffid"] = 304 , ["strid"] = 100522},--["buffid"] = 304
[100] = {["buffid"] = 304 , ["strid"] = 100523},--["buffid"] = 304
[200] = {["buffid"] = 304 , ["strid"] = 100524},--["buffid"] = 304
[500] = {["buffid"] = 304 , ["strid"] = 100525},--["buffid"] = 304

}





function CurrentDungeonScript:Startup()
-- pwdist.log("��������")
    self.SModDungeonScript = self.Stage:GetModDungeonScript()
	self.SModCommon = self.Stage:GetModCommon()
	self.SModLogicBattle = self.Stage:GetModLogic():cast("SModLogicBattle")
	self.SModObjs = self.Stage:GetModObjs()
	--��ȡ��ǰ�ȼ�ģʽ
	self.CurrentLv = 80
	if self.SModLogicBattle:GetBattleMode() == BattleMode.BattleMode40 then
		self.CurrentLv = 80
	elseif self.SModLogicBattle:GetBattleMode() == BattleMode.BattleMode50 then
		self.CurrentLv = 120
	elseif self.SModLogicBattle:GetBattleMode() == BattleMode.BattleMode60 then
		self.CurrentLv = 160
	elseif self.SModLogicBattle:GetBattleMode() == BattleMode.BattleMode70 then
		self.CurrentLv = 200
	end
-- pwdist.log("��������====="..self.CurrentLv.."     ")	

	self.MonsVsTower[1] = { MonsterT = PVP_NpcsTable[self.CurrentLv].R_NpcId1,	--�췽���С����
							MonsterPos = R_NpcSpawnPos1,
							MonsterFac = 11,
							MonsterWay = R_LWayPos,
							Obj1 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId6,live = 1,pos = B_Tower6_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj2 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId5,live = 1,pos = B_Tower5_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj3 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId4,live = 1,pos = B_Tower4_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj4 = {id = PVP_NpcsTable[self.CurrentLv].B_EncampmentId,live = 1,pos = B_Encampment_POS,destid = Dest_encamB},
							
							}
	self.MonsVsTower[2] = { MonsterT = PVP_NpcsTable[self.CurrentLv].R_NpcId2,	--�췽�Ҳ�С����
							MonsterPos = R_NpcSpawnPos2,
							MonsterFac = 11,
							MonsterWay = R_RWayPos,
							Obj1 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId3,live = 1,pos = B_Tower3_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj2 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId2,live = 1,pos = B_Tower2_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj3 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId1,live = 1,pos = B_Tower1_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj4 = {id = PVP_NpcsTable[self.CurrentLv].B_EncampmentId,live = 1,pos = B_Encampment_POS,destid = Dest_encamB},
							}	
	self.MonsVsTower[3] = { MonsterT = PVP_NpcsTable[self.CurrentLv].R_NpcId3,	--�췽�м�С����
							MonsterPos = R_NpcSpawnPos3,
							MonsterFac = 11,
							MonsterWay = R_ZWayPos,
							Obj1 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId9,live = 1,pos = B_Tower9_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj2 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId8,live = 1,pos = B_Tower8_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj3 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId7,live = 1,pos = B_Tower7_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj4 = {id = PVP_NpcsTable[self.CurrentLv].B_EncampmentId,live = 1,pos = B_Encampment_POS,destid = Dest_encamB},
							}						
-------------------------------------------------------------------------------------------------------------------------------------------------------------------							

	self.MonsVsTower[4] = { MonsterT = PVP_NpcsTable[self.CurrentLv].B_NpcId1,	
							MonsterPos = B_NpcSpawnPos1,
							MonsterFac = 12,
							MonsterWay = B_LWayPos,
							Obj1 = {id = PVP_NpcsTable[self.CurrentLv].R_TowerId6,live = 1,pos = R_Tower6_pos,fac = R_Faction_tower,destid = Dest_towerR},
							Obj2 = {id = PVP_NpcsTable[self.CurrentLv].R_TowerId5,live = 1,pos = R_Tower5_pos,fac = R_Faction_tower,destid = Dest_towerR},
							Obj3 = {id = PVP_NpcsTable[self.CurrentLv].R_TowerId4,live = 1,pos = R_Tower4_pos,fac = R_Faction_tower,destid = Dest_towerR},
							Obj4 = {id = PVP_NpcsTable[self.CurrentLv].R_EncampmentId,live = 1,pos = R_Encampment_POS,destid = Dest_encamR},
							}
	self.MonsVsTower[5] = { MonsterT = PVP_NpcsTable[self.CurrentLv].B_NpcId2,	
							MonsterPos = B_NpcSpawnPos2,
							MonsterFac = 12,
							MonsterWay = B_RWayPos,
							Obj1 = {id = PVP_NpcsTable[self.CurrentLv].R_TowerId3,live = 1,pos = R_Tower3_pos,fac = R_Faction_tower,destid = Dest_towerR},
							Obj2 = {id = PVP_NpcsTable[self.CurrentLv].R_TowerId2,live = 1,pos = R_Tower2_pos,fac = R_Faction_tower,destid = Dest_towerR},
							Obj3 = {id = PVP_NpcsTable[self.CurrentLv].R_TowerId1,live = 1,pos = R_Tower1_pos,fac = R_Faction_tower,destid = Dest_towerR},
							Obj4 = {id = PVP_NpcsTable[self.CurrentLv].R_EncampmentId,live = 1,pos = R_Encampment_POS,destid = Dest_encamR},
							}
	self.MonsVsTower[6] = { MonsterT = PVP_NpcsTable[self.CurrentLv].B_NpcId3,	
							MonsterPos = B_NpcSpawnPos3,
							MonsterFac = 12,
							MonsterWay = B_ZWayPos,
							Obj1 = {id = PVP_NpcsTable[self.CurrentLv].R_TowerId9,live = 1,pos = R_Tower9_pos,fac = R_Faction_tower,destid = Dest_towerR},
							Obj2 = {id = PVP_NpcsTable[self.CurrentLv].R_TowerId8,live = 1,pos = R_Tower8_pos,fac = R_Faction_tower,destid = Dest_towerR},
							Obj3 = {id = PVP_NpcsTable[self.CurrentLv].R_TowerId7,live = 1,pos = R_Tower7_pos,fac = R_Faction_tower,destid = Dest_towerR},
							Obj4 = {id = PVP_NpcsTable[self.CurrentLv].R_EncampmentId,live = 1,pos = R_Encampment_POS,destid = Dest_encamR},
							}
    SetEventHandler(StageEvents.HumanEnter,"OnHumanEnter")
    SetEventHandler(StageEvents.HumanLeave,"OnHumanLeave")
    SetEventHandler(StageEvents.HumanKilled,"OnHumanKilled")
    SetEventHandler(StageEvents.HumanResurrect,"OnHumanResurrect")

	
	self.timerstart = self.SModDungeonScript:CreateTimer(self.Timer_begain,"Timer_start")
	self.SModDungeonScript:CreateTimer(self.Timer_checkenter,"OnTimer_checkenter")
	self.Game_start_clock = os.time() + self.Timer_begain
	self.HasFinishCompete = false
	self.HasStartCompete = false
	self.WinTeamId = 0
	self.LoseTeamId = 0
	
	--��ʼ����������
	self.RTeamId = tostring(self.SModLogicBattle:GetBattleRTeam())
	self.BTeamId = tostring(self.SModLogicBattle:GetBattleBTeam())
	
	self.TeamsTable = {}
	self.TeamsTable[self.RTeamId] = {}
	self.TeamsTable[self.BTeamId] = {}
	
	self.TeamsTable[self.RTeamId]["camp"] = R_Faction_human
	self.TeamsTable[self.RTeamId]["spawn"] = R_ResurrectPOS
	self.TeamsTable[self.RTeamId]["resurrect"] = R_ResurrectPOS
	self.TeamsTable[self.RTeamId]["addmons"] = 0
	
	self.TeamsTable[self.BTeamId]["camp"] = B_Faction_human
	self.TeamsTable[self.BTeamId]["spawn"] = B_ResurrectPOS
	self.TeamsTable[self.BTeamId]["resurrect"] = B_ResurrectPOS
	self.TeamsTable[self.BTeamId]["addmons"] = 0
	self.TeamsTable[self.RTeamId]["killnum"] = 0
	self.TeamsTable[self.BTeamId]["killnum"] = 0
	
	
	self.TeamMembersTable = {}
	self.TeamMembersTable[self.RTeamId] = {}
	self.TeamMembersTable[self.BTeamId] = {}
	
	
	
	self.TeamMembersnum = {}
	self.TeamMembersnum[self.RTeamId] = {}
	self.TeamMembersnum[self.BTeamId] = {}
	self.TeamMembersnum[self.RTeamId]["humannum"] = 0
	self.TeamMembersnum[self.BTeamId]["humannum"] = 0
	
	
	--������Ӫ
	local R_Enc_obj = self.SModCommon:SpawnMonsterAt(R_Encampment_POS,{0.7,0,0.7},PVP_NpcsTable[self.CurrentLv].R_EncampmentId)	--ˢ��Ӫ
		R_Enc_obj:ChangeFaction(R_Faction_tower)
		R_Enc_obj:GetModAura():Create(Aura_wudi) --�޵��ޱ���
	local B_Enc_obj = self.SModCommon:SpawnMonsterAt(B_Encampment_POS,{-0.9,0,-0.5},PVP_NpcsTable[self.CurrentLv].B_EncampmentId)
		B_Enc_obj:ChangeFaction(B_Faction_tower)
		B_Enc_obj:GetModAura():Create(Aura_wudi) --�޵��ޱ���
		
	--���ر��ݻ�
	SetEventHandler(StageEvents.CreatureKilled,"EncampmentKilled_R",{type = PVP_NpcsTable[self.CurrentLv].R_EncampmentId})	--���ر��ݻ�
	SetEventHandler(StageEvents.CreatureKilled,"EncampmentKilled_B",{type = PVP_NpcsTable[self.CurrentLv].B_EncampmentId})
	
	--С�֡������ݻٻص� Wavenum
	for k , v  in pairs(self.MonsVsTower) do
		for i , j in pairs(v.MonsterT) do	--��¼NPCС��ˢ��
			SetEventHandler(StageEvents.CreatureSpawn,"NpcSpawn_fight",{type = j})	--NPC������go
			SetEventHandler(StageEvents.CreatureKilled,"NpcKilled_forScore",{type = j})	--NPC��ɱ
		end
		--ˢ�¸���λ�õ������޸���Ӫ
		local obj1 = self.SModCommon:SpawnMonsterAt(v.Obj1.pos,{0.7,0,0.7},v.Obj1.id)
		obj1:ChangeFaction(v.Obj1.fac)
		--obj1:GetModAura():Create(Aura_wudi) --�޵��ޱ���
		local obj2 = self.SModCommon:SpawnMonsterAt(v.Obj2.pos,{0.7,0,0.7},v.Obj2.id)
		obj2:ChangeFaction(v.Obj2.fac)
		obj2:GetModAura():Create(Aura_wudi) --�޵��ޱ���
		local obj3 = self.SModCommon:SpawnMonsterAt(v.Obj3.pos,{0.7,0,0.7},v.Obj3.id)
		obj3:ChangeFaction(v.Obj3.fac)
		obj3:GetModAura():Create(Aura_wudi) --�޵��ޱ���
		--��¼���������ݻ�
		SetEventHandler(StageEvents.CreatureKilled,"Tower_Killed",{type = v.Obj1.id})
		SetEventHandler(StageEvents.CreatureKilled,"Tower_Killed",{type = v.Obj2.id})
		SetEventHandler(StageEvents.CreatureKilled,"Tower_Killed",{type = v.Obj3.id})
	end
	
	--ˢBUFF��
	math.randomseed(os.time())	--�������
	math.random(1,3)
	math.random(1,3)
	self:Pos1_SpawnBuff()
	self:Pos2_SpawnBuff()
	self:Pos3_SpawnBuff()
	self:Pos4_SpawnBuff()
	self:Pos5_SpawnBuff()
	

	
	--������ʾ
	self.SModDungeonScript:CreateTimer(self.Timer_begain - 40,"OnTimer_gamehint1")
	self.SModDungeonScript:CreateTimer(self.Timer_begain - 20,"OnTimer_gamehint2")
	self.SModDungeonScript:CreateTimer(self.Timer_begain,"OnTimer_gamehint3")
	
	self.trigger1 = self.Stage:CreateTriggerSphere(R_LWayPos,WayRadius,"OnTriggerEnter","")
	self.trigger1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger2 = self.Stage:CreateTriggerSphere(R_RWayPos,WayRadius,"OnTriggerEnter","")
	self.trigger2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger3 = self.Stage:CreateTriggerSphere(R_ZWayPos,WayRadius,"OnTriggerEnter","")
	self.trigger3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger4 = self.Stage:CreateTriggerSphere(B_LWayPos,WayRadius,"OnTriggerEnter","")
	self.trigger4:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger5 = self.Stage:CreateTriggerSphere(B_RWayPos,WayRadius,"OnTriggerEnter","")
	self.trigger5:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger6 = self.Stage:CreateTriggerSphere(B_ZWayPos,WayRadius,"OnTriggerEnter","")
	self.trigger6:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
-- pwdist.log("��������end")
end

----���ߵ��м��С���ӱ��buff
function CurrentDungeonScript:OnTriggerEnter(trigger,target)
-- pwdist.log("���ߵ��м��С���ӱ��buff")
	local Mcreature = target:cast('Creature')
	if(Mcreature ~= nil)then
		Mcreature:GetModAura():Create(WayBuff)
	end	
-- pwdist.log("���ߵ��м��С���ӱ��buff======end")
end
--������ʾ
function CurrentDungeonScript:OnTimer_gamehint1()
-- pwdist.log("������ʾ1")
	if self.HasFinishCompete == true then return end
	local humans = self.Stage:GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		v:Hint(Str_gamehint[1],2000)
	end
-- pwdist.log("������ʾ1end")
end
function CurrentDungeonScript:OnTimer_gamehint2()
-- pwdist.log("������ʾ2")
	if self.HasFinishCompete == true then return end
	local humans = self.Stage:GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		v:Hint(Str_gamehint[2],2000)
	end
-- pwdist.log("������ʾ2end")
end
function CurrentDungeonScript:OnTimer_gamehint3()
-- pwdist.log("������ʾ3")
	if self.HasFinishCompete == true then return end
	local humans = self.Stage:GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		v:Hint(Str_gamehint[3],2000)
	end
-- pwdist.log("������ʾ3end")
end

--ս������
function CurrentDungeonScript:Timer_start()
-- pwdist.log("ս������")
	self:DisableAllBlockEffects()
	self.Stage:GetModDetour():EnableMotionBlock(1,true)
	self.Stage:GetModDetour():EnableMotionBlock(0,true)
	self:BeginCompete()
	self.SModDungeonScript:PlotClean()
	--self.SModDungeonScript:CreateTimer(fillmember_time,"OnTimer_stopfillmem")	--XXʱ���ֹͣ����
	self.SModCommon:BroadcastClientOperation(UI_WARN,tostring(13111))			--������ʾ��ս����ʼ����ʼ����
	self.SModDungeonScript:CreateTimer(2,"TimerStart_CloseEffects")	--2�����ɾһ����Чǽ
	self.SModLogicBattle:StartBattle()	--֪ͨ������������
	self.SModLogicBattle:UpdateBattleInfo(self.RTeamId,self.R_towercount)
	self.SModLogicBattle:UpdateBattleInfo(self.BTeamId,self.B_towercount)
	
	self.SModDungeonScript:CreateTimer(1800,"OnTimer_gameover") --ʱ��ͳ�ƣ�30���ӽ���
	self.SModDungeonScript:CreateTimer(1500,"OnTimer_gameoverhint") --ʱ��ͳ�ƣ�25��������
	
	self.timer_upklist = self.SModDungeonScript:CreatePeriodTimer(5,5,-1,"OnTimer_upklist")	--�������а�
-- pwdist.log("ս������end")
end
function CurrentDungeonScript:TimerStart_CloseEffects()
-- pwdist.log("�ر���Чǽ2")
	self.Stage:GetModDetour():EnableBlockEffects(50,false)
	self.Stage:GetModDetour():EnableBlockEffects(51,false)	
	self.Stage:GetModDetour():EnableBlockEffects(52,false)	
	self.Stage:GetModDetour():EnableBlockEffects(53,false)	
	self.Stage:GetModDetour():EnableBlockEffects(54,false)
	self.Stage:GetModDetour():EnableBlockEffects(55,false)
-- pwdist.log("�ر���Чǽ2end")
end
--ֹͣ����
function CurrentDungeonScript:OnTimer_stopfillmem()
-- pwdist.log("ֹͣ����")
	self.SModLogicBattle:CloseFillMember()
-- pwdist.log("ֹͣ����end")
end

--�������а�
function CurrentDungeonScript:OnTimer_upklist()
-- pwdist.log("�������а�")
	local R_Teamnum = self.SModLogicBattle:GetBattleTeamNum(self.RTeamId)
	local B_Teamnum = self.SModLogicBattle:GetBattleTeamNum(self.BTeamId)
	if(B_Teamnum > 0 and R_Teamnum > 0)then
		self.SModLogicBattle:UpdateBattleRanklist()
	end	
-- pwdist.log("�������а�end")
end

--����������
function CurrentDungeonScript:OnTimer_checkenter()
-- pwdist.log("����������")
	local R_Teamnum = self.SModLogicBattle:GetBattleTeamNum(self.RTeamId)
	local B_Teamnum = self.SModLogicBattle:GetBattleTeamNum(self.BTeamId)
	if R_Teamnum < min_human_count or B_Teamnum < min_human_count then	--��������
		self.HasFinishCompete = true
		self:AbortCompete()	--�쳣����
		
		self.SModObjs:BroadcastNotifyWithFaction(100518,ChannelType.Announcement,2,R_Faction_human,"60")
		self.SModObjs:BroadcastNotifyWithFaction(100518,ChannelType.Announcement,2,B_Faction_human,"60")
		
		self.SModDungeonScript:CreateTimer(20,"GameOver_leavedungeon_hint2")
		self.SModDungeonScript:CancelTimer(self.timerstart)
	else
		--���Կ�����ִ�в���
		self.SModLogicBattle:StartFillMember()
	end
-- pwdist.log("����������end")		
end

function CurrentDungeonScript:GameOver_leavedungeon_hint2()
-- pwdist.log("�볡2")
	self.SModObjs:BroadcastNotifyWithFaction(100518,ChannelType.Announcement,2,R_Faction_human,"40")
	self.SModObjs:BroadcastNotifyWithFaction(100518,ChannelType.Announcement,2,B_Faction_human,"40")
	self.SModDungeonScript:CreateTimer(20,"GameOver_leavedungeon_hint3")
-- pwdist.log("�볡2end")
end
function CurrentDungeonScript:GameOver_leavedungeon_hint3()
-- pwdist.log("�볡3")
	self.SModObjs:BroadcastNotifyWithFaction(100518,ChannelType.Announcement,2,R_Faction_human,"20")
	self.SModObjs:BroadcastNotifyWithFaction(100518,ChannelType.Announcement,2,B_Faction_human,"20")
-- pwdist.log("�볡3end")
end

function CurrentDungeonScript:OnHumanEnter(human)
-- pwdist.log("��ҽ���")
	human:GetModMisc():SetBitEx(2,2000)
	
	local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
	local hid = tostring(human:GetID())
-- pwdist.log("��ҽ���===="..hid)	
	--��ʼ����Ա����
	self.TeamMembersTable[tid][hid] = {}
	human:ChangeFaction(self.TeamsTable[tid]["camp"])
	human:GetModMotionMaster():ChangePosition(self.TeamsTable[tid]["spawn"])
	human:GetModLansquenet():ChangeLansFaction()---�ı��̴���Ӫ
	self.TeamMembersTable[tid][hid]["kill_npc"] = 0
	self.TeamMembersTable[tid][hid]["kill_hum"] = 0
	self.TeamMembersTable[tid][hid]["get_buff"] = 0
	self.TeamMembersTable[tid][hid]["be_killed"] = 0
	--˫���������
	self.TeamMembersnum[tid]["humannum"] = self.TeamMembersnum[tid]["humannum"] + 1
	
	--�����Ѿ���������ֹ�ˣ�����̫����
	if self.HasFinishCompete == true then
		self:CloseCompete()
		return
	end
	if self.HasStartCompete == false then
		self.SModCommon:BroadcastClientOperation(UI_TIMER,tostring(self.Game_start_clock - os.time()))
		self:BroadcastBlockEffectsStatus()
	else
		self.SModLogicBattle:UpdateBattleInfo(self.RTeamId,self.R_towercount)
		self.SModLogicBattle:UpdateBattleInfo(self.BTeamId,self.B_towercount)
		self:UpdateMapInfo()
	end
	self.SModLogicBattle:AddBattleScore(hid,0,0,0,0)
	--�����ѷ���Ϣ
	self.SModObjs:BroadcastNotifyWithFaction(Str_humanenter,ChannelType.General,2,human:GetFaction(),human:GetName(),human:GetServerName())
-- pwdist.log("��ҽ���end")	
end

function CurrentDungeonScript:OnHumanLeave(human)
-- pwdist.log("����뿪")
	--�뿪��ɾ����ͼ��ʾ
	local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
	local hid = tostring(human:GetID())
	local state = Map_state_dead
	local dir = Map_race_human
	if tid == self.RTeamId then
		dir = Map_race_human
	else
		dir = Map_race_spirit
	end
	--self.SModLogicBattle:UpdateBattleMapInfo(tid,hid,Map_type_human,state,dir)
	--self.SModLogicBattle:CommitMapInfoUpdate()
	
	self.TeamMembersTable[tid][hid]["kill_npc"] = 0
	self.TeamMembersTable[tid][hid]["kill_hum"] = 0
	self.TeamMembersTable[tid][hid]["get_buff"] = 0
	self.TeamMembersTable[tid][hid]["be_killed"] = 0
	
	--��������Ϊ�պ󣬾ͽ�������
	self.TeamMembersnum[tid]["humannum"] = self.TeamMembersnum[tid]["humannum"] - 1
	if self.TeamMembersnum[tid]["humannum"] == 0 then --����Ϊ0������
		if tid == self.RTeamId then
			self.WinTeamId = self.BTeamId
			self.LoseTeamId = self.RTeamId
			
			self.SModObjs:BroadcastNotifyWithFaction(100519,ChannelType.Announcement,2,R_Faction_human)
			self.SModObjs:BroadcastNotifyWithFaction(100519,ChannelType.Announcement,2,B_Faction_human)
			self.SModDungeonScript:CreateTimer(10,"OntimerEndedCompete")		
		end
	else
		--�����ѷ���Ϣ
		self.SModObjs:BroadcastNotifyWithFaction(Str_humanleave,ChannelType.General,2,human:GetFaction(),human:GetName(),human:GetServerName())
	end 
-- pwdist.log("����뿪end")
end

function CurrentDungeonScript:OntimerEndedCompete()
-- pwdist.log("OntimerEndedCompete")
	self:EndedCompete()
-- pwdist.log("OntimerEndedCompeteEND")
end

--�������
function CurrentDungeonScript:OnHumanKilled(human,killer)
-- pwdist.log("��ұ�ɱ")
	--human:GetModRealive():HideRealiveButton(true)
	local hid = tostring(human:GetID())
	local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
	--human:GetModRealive():Realive(self.TeamsTable[tid]["resurrect"],20000)
	human:GetModRealive():SetRealiveDelay(5000)
	self.TeamMembersTable[tid][hid]["be_killed"] = self.TeamMembersTable[tid][hid]["be_killed"] + 1
	
	
	--����ɱ�߼���ɱ����
	if killer:IsKindOf(CLSID.Human) then 
		local human= killer:cast("Human")
		local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
		local hid = tostring(human:GetID())
		self.TeamMembersTable[tid][hid]["kill_hum"] = self.TeamMembersTable[tid][hid]["kill_hum"] + 1
		
		--����ɱ�������
		--[[
		self.TeamsTable[tid]["killnum"] = self.TeamsTable[tid]["killnum"] + 1
		for k ,v in pairs(KillNum_AddBuff) do
			if self.TeamsTable[tid]["killnum"] == k then
				local humans = GetCurrentStage():GetModObjs():GetHumans()
				for i , j in pairs(humans) do
					if j:GetFaction() == self.TeamsTable[tid]["camp"] then
						--�ӹ⻷
						human:GetModAura():Create(v.buffid)
						--�㲥
						self.SModObjs:BroadcastNotifyWithFaction(v.strid,ChannelType.Announcement,2,j:GetFaction(),tostring(k))
					end
				end
			end
		end
		]]
	end
	--���͸�����һ������
	for k , v in pairs(self.TeamMembersTable) do
		for i , j in pairs(v) do
			self.SModLogicBattle:AddBattleScore(i,j.kill_hum,j.kill_npc,j.get_buff,j.be_killed)
		end
	end
-- pwdist.log("��ұ�ɱend")	
end
--��Ҹ���
function CurrentDungeonScript:OnHumanResurrect(human)
-- pwdist.log("��Ҹ���")	
	local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
	human:GetModMotionMaster():ChangePosition(self.TeamsTable[tid]["resurrect"])
	human:GetModLansquenet():ChangeLansFaction()---�ı��̴���Ӫ
	
	local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
	human:GetModMotionMaster():ChangePosition(self.TeamsTable[tid]["resurrect"])
	human:GetModLansquenet():ChangeLansFaction()---�ı��̴���Ӫ
-- pwdist.log("��Ҹ���end")	
end

function CurrentDungeonScript:BeginCompete()
-- pwdist.log("��ʼ��ʱ")
	self.Begin_clock = os.time()

	self.HasStartCompete = true
	
	self.spawnmons_cycle = self.SModDungeonScript:CreatePeriodTimer(1,NpcSpawnTimer,-1,"Timer_spawnmons_cycle")
	self.mons_vs_tower = self.SModDungeonScript:CreatePeriodTimer(1,2,-1,"OnTimer_mons_vs_tower")
	--��ͼ��ʾ����ˮ��
	self:UpdateMapInfo()
-- pwdist.log("��ʼ��ʱend")
end


--ѭ��ˢ��
function CurrentDungeonScript:Timer_spawnmons_cycle()
-- pwdist.log("ˢ��11111")
	for i = 1, WaveMonsCount do
		self.SModDungeonScript:CreateTimer(i,"OntimerSpawnMons")
	end
	self.SModDungeonScript:CreateTimer(WaveMonsCount,"OntimerSpawnMons_add")	--����ˢ��
	self.Wavenum = self.Wavenum + 1
-- pwdist.log("ˢ��11111end")
end
function CurrentDungeonScript:OntimerSpawnMons()
-- pwdist.log("ˢ��22222")
	for k , v in pairs(self.MonsVsTower) do
		for i , j in pairs(v.MonsterT) do
			--local monscount = math.ceil(self.Wavenum / 10)
			--for m = 1,monscount do
				local npc = self.SModCommon:SpawnMonsterAt(v.MonsterPos,{1,0,0},j)
				npc:ChangeFaction(v.MonsterFac)
			--end	
		end
	end
-- pwdist.log("ˢ��22222end")
end
--����ˢ��
function CurrentDungeonScript:OntimerSpawnMons_add()
-- pwdist.log("����ˢ��")
	if self.TeamsTable[self.RTeamId]["addmons"] ~= 0 then	--�췽��С��
		for m = 1,self.TeamsTable[self.RTeamId]["addmons"] do
			self.SModDungeonScript:CreateTimer(m,"OntimerSpawnMons_AddR")
		end
		self.TeamsTable[self.RTeamId]["addmons"] = 0	--��պ췽����ˢ��
	elseif self.TeamsTable[self.BTeamId]["addmons"] ~= 0 then	--������С��
		for m = 1,self.TeamsTable[self.BTeamId]["addmons"] do
			self.SModDungeonScript:CreateTimer(m,"OntimerSpawnMons_AddB")
		end
		self.TeamsTable[self.BTeamId]["addmons"] = 0	--�����������ˢ��
	end
-- pwdist.log("����ˢ��end")
end
--����ˢ�֣��췽
function CurrentDungeonScript:OntimerSpawnMons_AddR()
-- pwdist.log("�췽����ˢ��")
	for k , v in pairs(self.MonsVsTower) do
		if v.MonsterFac == R_Faction_npc then
			for i , j in pairs(v.MonsterT) do
				local monscount = math.ceil(self.Wavenum / 10)
				for m = 1,monscount do
					local npc = self.SModCommon:SpawnMonsterAt(v.MonsterPos,{1,0,0},j)
					npc:ChangeFaction(v.MonsterFac)
				end
			end
		end
	end
-- pwdist.log("�췽����ˢ��end")	
end
--����ˢ�֣�����
function CurrentDungeonScript:OntimerSpawnMons_AddB()
-- pwdist.log("��������ˢ��")
	for k , v in pairs(self.MonsVsTower) do
		if v.MonsterFac == B_Faction_npc then
			for i , j in pairs(v.MonsterT) do
				local monscount = math.ceil(self.Wavenum / 10)
				for m = 1,monscount do
					local npc = self.SModCommon:SpawnMonsterAt(v.MonsterPos,{1,0,0},j)
					npc:ChangeFaction(v.MonsterFac)
				end
			end
		end
	end
-- pwdist.log("��������ˢ��end")
end

--���� 
function CurrentDungeonScript:EndedCompete()
-- pwdist.log("����")
	self.SModLogicBattle:CloseFillMember()
	if self.HasFinishCompete == true then
		return
	end
	if(self.spawnmons_cycle ~=nil)then
		self.SModDungeonScript:CancelTimer(self.spawnmons_cycle)	--ȡ��ˢ�ּ�ʱ��
	end
	
	--self.SModDungeonScript:CancelTimer(self.timer_updatemap)	--ȡ��ˢ�µ�ͼ��ʱ��
	if(self.mons_vs_tower ~=nil)then
		self.SModDungeonScript:CancelTimer(self.mons_vs_tower)	--ȡ��ѭ������С��������
	end
	if(self.timer_upklist~=nil)then
		self.SModDungeonScript:CancelTimer(self.timer_upklist)	--ȡ�����а�ˢ��
	end
	
	 
	 
	--ɾ������С��
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k , v in pairs(CreatureTab) do
		if v:GetFaction() == B_Faction_npc or v:GetFaction() == R_Faction_npc then
			v:LeaveWorld(0)
		end	
	end
	
    
    local humans = self.Stage:GetModObjs():GetHumans()
	--���������������
	for k , v in pairs(humans) do
		if v:IsDead() then
			v:GetModRealive():Realive(v:GetPosition(), 1)
		end
	end	
	--���͸�����һ������
	for k , v in pairs(self.TeamMembersTable) do
		for i , j in pairs(v) do
			self.SModLogicBattle:AddBattleScore(i,j.kill_hum,j.kill_npc,j.get_buff,j.be_killed)
		end
	end
	--��������Ϣ
	self.SModLogicBattle:EndedBattle(self.WinTeamId,self.LoseTeamId)
	
	
	-- ���������ˣ��ָ���Ӫ
	self:CleanCompete()
	
	-- ����رյ���ʱ
	self.SModDungeonScript:CreateTimer(20,"CloseCompete")
	--self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(20))
	self.HasFinishCompete = true
-- pwdist.log("����end")	
end

function CurrentDungeonScript:AbortCompete()
-- pwdist.log("�رյ���ʱ")
	self.SModLogicBattle:CloseFillMember()
	self.SModLogicBattle:AbortBattle()
	-- ����رյ���ʱ
	self.SModDungeonScript:CreateTimer(60,"CloseCompete")
-- pwdist.log("�رյ���ʱend")
end

function CurrentDungeonScript:CloseCompete()
-- pwdist.log("�رվ���")
	local humans = self.Stage:GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		self.SModLogicBattle:LeaveBattle(v:GetID())
	end
-- pwdist.log("�رվ���end")
end

function CurrentDungeonScript:CleanCompete()
-- pwdist.log("������")
	local humans = GetCurrentStage():GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		v:ChangeFaction(FactionType.Human)
		v:GetModLansquenet():ChangeLansFaction()---�ı��̴���Ӫ
		if v:IsDead() then
			v:GetModRealive():Realive(v:GetPosition(), 1)
		end
	end
-- pwdist.log("������end")
end

--���ر��ݻ�
function CurrentDungeonScript:EncampmentKilled_R(creature,killer)
-- pwdist.log("�췽��������")
	self.R_towercount = self.R_towercount - 1
	self.SModLogicBattle:UpdateBattleInfo(self.RTeamId,self.R_towercount)
	
	self.Stage:SetAIEnable(false)	--�رյ�ͼAI
	self.WinTeamId = self.BTeamId
	self.LoseTeamId = self.RTeamId
	self.SModCommon:SpawnMonsterAt(R_Encampment_POS,{1,0,0},Dest_encamR)
	self:EndedCompete()
-- pwdist.log("�췽��������end")
end
function CurrentDungeonScript:EncampmentKilled_B(creature,killer)
-- pwdist.log("������������")
	self.B_towercount = self.B_towercount - 1 
	self.SModLogicBattle:UpdateBattleInfo(self.BTeamId,self.B_towercount)
	
	self.Stage:SetAIEnable(false)	--�رյ�ͼAI
	self.WinTeamId = self.RTeamId
	self.LoseTeamId = self.BTeamId
	self.SModCommon:SpawnMonsterAt(B_Encampment_POS,{1,0,0},Dest_encamB)
	self:EndedCompete()
-- pwdist.log("������������end")
end

--25���Ӻ������¹���30���ӽ���ս��
function CurrentDungeonScript:OnTimer_gameoverhint()
-- pwdist.log("25���Ӻ������¹���30���ӽ���ս��")
	self.SModObjs:BroadcastNotifyWithFaction(100520,ChannelType.Announcement,2,R_Faction_human)
	self.SModObjs:BroadcastNotifyWithFaction(100520,ChannelType.Announcement,2,B_Faction_human)
-- pwdist.log("25���Ӻ������¹���30���ӽ���ս��end")
end

--30���Ӻ�ս������
function CurrentDungeonScript:OnTimer_gameover()
-- pwdist.log("30���Ӻ�ս������")
	if self.R_towercount < self.B_towercount then
		self.Stage:SetAIEnable(false)	--�رյ�ͼAI
		self.WinTeamId = self.BTeamId
		self.LoseTeamId = self.RTeamId
		self:EndedCompete()
	elseif self.B_towercount < self.R_towercount then
		self.Stage:SetAIEnable(false)	--�رյ�ͼAI
		self.WinTeamId = self.RTeamId
		self.LoseTeamId = self.BTeamId
		self:EndedCompete()
	else
		self.timercut_gameover = self.SModDungeonScript:CreatePeriodTimer(1,1,-1,"OnTimerCut_gameover")	--������ͬ�����ٵ�һ�����־ͽ���
		self.SModObjs:BroadcastNotifyWithFaction(100521,ChannelType.Announcement,2,R_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(100521,ChannelType.Announcement,2,B_Faction_human)
	end
-- pwdist.log("30���Ӻ�ս������end")
end
--������ͬ�����ٵ�һ�����־ͽ���
function CurrentDungeonScript:OnTimerCut_gameover()
-- pwdist.log("������ͬ�����ٵ�һ�����־ͽ���")
	if self.R_towercount < self.B_towercount then
		self.Stage:SetAIEnable(false)	--�رյ�ͼAI
		self.WinTeamId = self.BTeamId
		self.LoseTeamId = self.RTeamId
		self:EndedCompete()
		self.SModDungeonScript:CancelTimer(self.timercut_gameover)	--ȡ��ͳ�������ĵ���ʱ
	elseif self.B_towercount < self.R_towercount then
		self.Stage:SetAIEnable(false)	--�رյ�ͼAI
		self.WinTeamId = self.RTeamId
		self.LoseTeamId = self.BTeamId
		self:EndedCompete()
		self.SModDungeonScript:CancelTimer(self.timercut_gameover)	--ȡ��ͳ�������ĵ���ʱ
	end
-- pwdist.log("������ͬ�����ٵ�һ�����־ͽ���end")
end

--NPC�����󳯶Է�����������
function CurrentDungeonScript:NpcSpawn_fight(Mcreature)
	local creature = Mcreature:cast('Creature')
--pwdist.log("NPC�����󳯶Է�����������")
	local MonsId = creature:GetCreatureType()
	for k , v in pairs(self.MonsVsTower) do
		for i , j in pairs(v.MonsterT) do
			if MonsId == j then
				if v.Obj1.live == 1 then
-- pwdist.log("NPC�����󳯶Է�����������1======="..tostring(v.Obj1.pos[1]).."  "..tostring(v.Obj1.pos[2]).."  "..tostring(v.Obj1.pos[3]))
					creature:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)				
-- pwdist.log("NPC�����󳯶Է�����������2")
				elseif v.Obj1.live == 0 and v.Obj2.live == 1 then
					creature:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
-- pwdist.log("NPC�����󳯶Է�����������3")
				elseif v.Obj1.live == 0 and v.Obj2.live == 0 and v.Obj3.live == 1 then
-- pwdist.log("NPC�����󳯶Է�����������4")
					creature:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
-- pwdist.log("NPC�����󳯶Է�����������5")
				elseif v.Obj1.live == 0 and v.Obj2.live == 0 and v.Obj3.live == 0 and v.Obj4.live == 1 then
-- pwdist.log("NPC�����󳯶Է�����������6")
				--��ȻС���ǰ�˳�򹥻�������ÿ�ζ��ж�ǰ�������������жϺ���
				--��Ϊ�����еĴ�R��Խ��ǰ����֮��ɺ���� o(�s���t)o
					creature:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
				else
-- pwdist.log("NPC�����󳯶Է�����������7")
					creature:LeaveWorld(0)
				end
				return
			end
		end
	end	
-- pwdist.log("NPC�����󳯶Է�����������end")
end

--ѭ����ʱ����NPC������
function CurrentDungeonScript:OnTimer_mons_vs_tower()
-- pwdist.log("ѭ����ʱ����NPC������")
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for m , n in pairs(CreatureTab) do
		if n:GetFaction() == B_Faction_npc or n:GetFaction() == R_Faction_npc then
			if n:GetBitEx(1) == 0 and not n:IsDead() then	--�����ƶ���
				local MonsId = n:GetCreatureType()
				for k , v in pairs(self.MonsVsTower) do
					for i , j in pairs(v.MonsterT) do
						if MonsId == j then
							if v.Obj1.live == 1 then
								if not n:GetModAura():Exists(WayBuff) then
									-- pwdist.log("��Ҫ��������==========")
									n:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
								else
									-- pwdist.log("��Ҫ������")
									n:GetModMotionMaster():NavigatePositionEx(v.Obj1.pos,"",1)
								end
							elseif v.Obj1.live == 0 and v.Obj2.live == 1 then
								if not n:GetModAura():Exists(WayBuff) then
									-- pwdist.log("��Ҫ��������")
									n:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
								else				
									-- pwdist.log("��Ҫ������")
									n:GetModMotionMaster():NavigatePositionEx(v.Obj2.pos,"",1)
								end
							elseif v.Obj1.live == 0 and v.Obj2.live == 0 and v.Obj3.live == 1 then
								if not n:GetModAura():Exists(WayBuff) then
									-- pwdist.log("��Ҫ��������")
									n:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
								else
									-- pwdist.log("��Ҫ������")
									n:GetModMotionMaster():NavigatePositionEx(v.Obj3.pos,"",1)
								end
							elseif v.Obj1.live == 0 and v.Obj2.live == 0 and v.Obj3.live == 0 and v.Obj4.live == 1 then
							--��ȻС���ǰ�˳�򹥻�������ÿ�ζ��ж�ǰ�������������жϺ���
							--��Ϊ�����еĴ�R��Խ��ǰ����֮��ɺ���� o(�s���t)o
								if not n:GetModAura():Exists(WayBuff) then
									-- pwdist.log("��Ҫ��������")
									n:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
								else			
									-- pwdist.log("��Ҫ������")
									n:GetModMotionMaster():NavigatePositionEx(v.Obj4.pos,"",1)
								end
							else
								n:LeaveWorld(0)
							end
						end
					end
				end	
			end
		end	
	end
-- pwdist.log("ѭ����ʱ����NPC������end")
end

--NPC��ɱ��ͳ�Ƹ���ҵ÷�
function CurrentDungeonScript:NpcKilled_forScore(creature,killer)
-- pwdist.log("NPC��ɱ��ͳ�Ƹ���ҵ÷�")
	--����ɱ�߼���ɱ����
	if killer and killer:IsKindOf(CLSID.Human) then 
		local human= killer:cast("Human")
		local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
		local hid = tostring(human:GetID())
		self.TeamMembersTable[tid][hid]["kill_npc"] = self.TeamMembersTable[tid][hid]["kill_npc"] + 1
	end
	--[[���µ�ͼ��Ϣ
	local tid,hid,typem = self:GetMonsterInfo(creature)
	local state = Map_state_dead
	local dir = Map_race_human
	if tid == self.RTeamId then
		dir = Map_race_human
	else
		dir = Map_race_spirit
	end
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typem,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()]]
-- pwdist.log("NPC��ɱ��ͳ�Ƹ���ҵ÷�end")
end


--���������ݻٺ���״̬
function CurrentDungeonScript:Tower_Killed(creature,killer)
-- pwdist.log("���������ݻٺ���״̬")
	local TowerId = creature:GetCreatureType()
	for k , v in pairs(self.MonsVsTower) do 
		if TowerId == v.Obj1.id then	--����ݻٵ���1����
			--��һ����ģ�ͣ����ƻ�����
			self.SModCommon:SpawnMonsterAt(v.Obj1.pos,{1,0,0},v.Obj1.destid)
			
			v.Obj1.live = 0 	--1����״̬�޸�
			--ɾ��2�������޵�BUFF
			local TowerTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v.Obj2.id)
			TowerTab_s[1]:GetModAura():Delete(Aura_wudi)
			if v.Obj2.live == 1 then	--2��������
				local CreatureTab = {}
				for m , n in pairs(v.MonsterT) do
					local CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(n)
					for q , s in pairs(CreatureTab_s) do
						table.insert(CreatureTab,s)	--��ȡ�Ѿ�ˢ�µĶ�ӦС��
					end
				end
				for i , j in pairs(CreatureTab) do
					if not j:IsDead() then
						if not j:GetModAura():Exists(WayBuff) then
							j:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
						else
							j:GetModMotionMaster():NavigatePositionEx(v.Obj2.pos,"",1)	--�ı�Ѱ·״̬��ȥ2����
						end
						
					end
				end
			elseif v.Obj2.live == 0 and v.Obj3.live == 1 then	--2�������٣�3��������
				local CreatureTab = {}
				for m , n in pairs(v.MonsterT) do
					local CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(n)
					for q , s in pairs(CreatureTab_s) do
						table.insert(CreatureTab,s)
					end
				end
				for i , j in pairs(CreatureTab) do
					if not j:IsDead() then
						if not j:GetModAura():Exists(WayBuff) then
							j:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
						else
							j:GetModMotionMaster():NavigatePositionEx(v.Obj3.pos,"",1)	--����3����
						end
					end
				end
			elseif v.Obj2.live == 0 and v.Obj3.live == 0 and v.Obj4.live == 1 then	--2,3�������٣����ػ���
				local CreatureTab = {}
				for m , n in pairs(v.MonsterT) do
					local CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(n)
					for q , s in pairs(CreatureTab_s) do
						table.insert(CreatureTab,s)
					end
				end
				for i , j in pairs(CreatureTab) do
					if not j:IsDead() then
						if not j:GetModAura():Exists(WayBuff) then
							j:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
						else
							j:GetModMotionMaster():NavigatePositionEx(v.Obj4.pos,"",1)	--��������
						end
					end
				end
			end
		elseif TowerId == v.Obj2.id then	--����ݻٵ���2����
			--��һ����ģ�ͣ����ƻ�����
			self.SModCommon:SpawnMonsterAt(v.Obj2.pos,{1,0,0},v.Obj2.destid)
			v.Obj2.live = 0 	--�޸�״̬
			--ɾ��3�������޵�BUFF
			local TowerTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v.Obj3.id)
			TowerTab_s[1]:GetModAura():Delete(Aura_wudi)
			if v.Obj1.live == 1 then
				local CreatureTab = {}
				for m , n in pairs(v.MonsterT) do
					local CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(n)
					for q , s in pairs(CreatureTab_s) do
						table.insert(CreatureTab,s)
					end
				end
				for i , j in pairs(CreatureTab) do
					if not j:IsDead() then
						if not j:GetModAura():Exists(WayBuff) then
							j:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
						else					
							j:GetModMotionMaster():NavigatePositionEx(v.Obj1.pos,"",1)
						end
					end
				end
			elseif v.Obj1.live == 0 and v.Obj3.live == 1 then
				local CreatureTab = {}
				for m , n in pairs(v.MonsterT) do
					local CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(n)
					for q , s in pairs(CreatureTab_s) do
						table.insert(CreatureTab,s)
					end
				end
				for i , j in pairs(CreatureTab) do
					if not j:IsDead() then
						if not j:GetModAura():Exists(WayBuff) then
							j:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
						else					
							j:GetModMotionMaster():NavigatePositionEx(v.Obj3.pos,"",1)
						end
					end
				end
			elseif v.Obj1.live == 0 and v.Obj3.live == 0 and v.Obj4.live == 1 then
				local CreatureTab = {}
				for m , n in pairs(v.MonsterT) do
					local CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(n)
					for q , s in pairs(CreatureTab_s) do
						table.insert(CreatureTab,s)
					end
				end
				for i , j in pairs(CreatureTab) do
					if not j:IsDead() then
						if not j:GetModAura():Exists(WayBuff) then
							j:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
						else					
							j:GetModMotionMaster():NavigatePositionEx(v.Obj4.pos,"",1)
						end
					end
				end
			end
		elseif TowerId == v.Obj3.id then	--����ݻٵ���3����
			--��һ����ģ�ͣ����ƻ�����
			self.SModCommon:SpawnMonsterAt(v.Obj3.pos,{1,0,0},v.Obj2.destid)			
			v.Obj3.live = 0 	--�޸�״̬
			--ɾ�����ص��޵�BUFF
			local TowerTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v.Obj4.id)
			TowerTab_s[1]:GetModAura():Delete(Aura_wudi)
			if v.Obj1.live == 1 then
				local CreatureTab = {}
				for m , n in pairs(v.MonsterT) do
					local CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(n)
					for q , s in pairs(CreatureTab_s) do
						table.insert(CreatureTab,s)
					end
				end
				for i , j in pairs(CreatureTab) do
					if not j:IsDead() then
						if not j:GetModAura():Exists(WayBuff) then
							j:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
						else					
							j:GetModMotionMaster():NavigatePositionEx(v.Obj1.pos,"",1)
						end
					end
				end
			elseif v.Obj1.live == 0 and v.Obj2.live == 1 then
				local CreatureTab = {}
				for m , n in pairs(v.MonsterT) do
					local CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(n)
					for q , s in pairs(CreatureTab_s) do
						table.insert(CreatureTab,s)
					end
				end
				for i , j in pairs(CreatureTab) do
					if not j:IsDead() then
						if not j:GetModAura():Exists(WayBuff) then
							j:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
						else
							j:GetModMotionMaster():NavigatePositionEx(v.Obj2.pos,"",1)
						end
					end
				end
			elseif v.Obj1.live == 0 and v.Obj2.live == 0 and v.Obj4.live == 1 then
				local CreatureTab = {}
				for m , n in pairs(v.MonsterT) do
					local CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(n)
					for q , s in pairs(CreatureTab_s) do
						table.insert(CreatureTab,s)
					end
				end
				for i , j in pairs(CreatureTab) do
					if not j:IsDead() then
						if not j:GetModAura():Exists(WayBuff) then
							j:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
						else
							j:GetModMotionMaster():NavigatePositionEx(v.Obj4.pos,"",1)
						end
					end
				end
			end
		end
	end
	--���Ź㲥
	for k , v in pairs(self.MonsVsTower) do 
		if TowerId == v.Obj1.id or TowerId == v.Obj2.id or TowerId == v.Obj3.id  then 		
			if k == 1 or k == 4 then
-- pwdist.log("��·������")
				if v.Obj1.fac == R_Faction_tower then
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled1,ChannelType.Announcement,2,R_Faction_human)
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled3,ChannelType.Announcement,2,B_Faction_human)
				else
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled1,ChannelType.Announcement,2,B_Faction_human)
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled3,ChannelType.Announcement,2,R_Faction_human)
				end	
			elseif k == 2 or k == 5 then
-- pwdist.log("��·������")
				if v.Obj1.fac == R_Faction_tower then
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled2,ChannelType.Announcement,2,R_Faction_human)
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled4,ChannelType.Announcement,2,B_Faction_human)
				else
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled2,ChannelType.Announcement,2,B_Faction_human)
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled4,ChannelType.Announcement,2,R_Faction_human)
				end
			else
-- pwdist.log("��·������")
				if v.Obj1.fac == R_Faction_tower then
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled5,ChannelType.Announcement,2,R_Faction_human)
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled6,ChannelType.Announcement,2,B_Faction_human)
				else
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled5,ChannelType.Announcement,2,B_Faction_human)
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled6,ChannelType.Announcement,2,R_Faction_human)
				end	
			end
		end
	end
	--���µ�ͼ��Ϣ
	self:UpdateUnitinfo(creature)
	self.SModLogicBattle:CommitMapInfoUpdate()
	
	--֪ͨ�����������������
	for k , v in pairs(self.MonsVsTower) do 
		if TowerId == v.Obj1.id or TowerId == v.Obj2.id or TowerId == v.Obj3.id then
			if v.Obj1.fac == R_Faction_tower then
				self.R_towercount = self.R_towercount - 1
				self.SModLogicBattle:UpdateBattleInfo(self.RTeamId,self.R_towercount)
			else
				self.B_towercount = self.B_towercount - 1 
				self.SModLogicBattle:UpdateBattleInfo(self.BTeamId,self.B_towercount)
			end
		end
	end
-- pwdist.log("���������ݻٺ���״̬end")
end

--BUFF��ˢBUFF��
function CurrentDungeonScript:Pos1_SpawnBuff()
-- pwdist.log("BUFF��ˢBUFF��111111")
	local rand = math.random(1,3)
	if rand == 1 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos1,{1,0,0},Buff_IdTable.id1,2,"OnTouchSt_pos1_id1")
	elseif rand == 2 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos1,{1,0,0},Buff_IdTable.id2,2,"OnTouchSt_pos1_id2")
	else
		self.Stage:CreateStaticObject(Buff_PosTable.pos1,{1,0,0},Buff_IdTable.id3,2,"OnTouchSt_pos1_id3")
	end
-- pwdist.log("BUFF��ˢBUFF��11111end")
end
function CurrentDungeonScript:Pos2_SpawnBuff()
-- pwdist.log("BUFF��ˢBUFF��2222222")
	local rand = math.random(1,3)
	if rand == 1 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos2,{1,0,0},Buff_IdTable.id1,2,"OnTouchSt_pos2_id1")
	elseif rand == 2 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos2,{1,0,0},Buff_IdTable.id2,2,"OnTouchSt_pos2_id2")
	else
		self.Stage:CreateStaticObject(Buff_PosTable.pos2,{1,0,0},Buff_IdTable.id3,2,"OnTouchSt_pos2_id3")
	end
-- pwdist.log("BUFF��ˢBUFF��2222222end")
end
function CurrentDungeonScript:Pos3_SpawnBuff()
-- pwdist.log("BUFF��ˢBUFF��333333333333332")
	local rand = math.random(1,3)
	if rand == 1 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos3,{1,0,0},Buff_IdTable.id1,2,"OnTouchSt_pos3_id1")
	elseif rand == 2 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos3,{1,0,0},Buff_IdTable.id2,2,"OnTouchSt_pos3_id2")
	else
		self.Stage:CreateStaticObject(Buff_PosTable.pos3,{1,0,0},Buff_IdTable.id3,2,"OnTouchSt_pos3_id3")
	end
-- pwdist.log("BUFF��ˢBUFF��33333333333333end")
end
function CurrentDungeonScript:Pos4_SpawnBuff()
-- pwdist.log("BUFF��ˢBUFF��444444444444444444")
	local rand = math.random(1,3)
	if rand == 1 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos4,{1,0,0},Buff_IdTable.id1,2,"OnTouchSt_pos4_id1")
	elseif rand == 2 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos4,{1,0,0},Buff_IdTable.id2,2,"OnTouchSt_pos4_id2")
	else
		self.Stage:CreateStaticObject(Buff_PosTable.pos4,{1,0,0},Buff_IdTable.id3,2,"OnTouchSt_pos4_id3")
	end
-- pwdist.log("BUFF��ˢBUFF��444444444444444444end")
end
function CurrentDungeonScript:Pos5_SpawnBuff()
-- pwdist.log("BUFF��ˢBUFF��555555555555555555")
	local rand = math.random(1,3)
	if rand == 1 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos5,{1,0,0},Buff_IdTable.id1,2,"OnTouchSt_pos5_id1")
	elseif rand == 2 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos5,{1,0,0},Buff_IdTable.id2,2,"OnTouchSt_pos5_id2")
	else
		self.Stage:CreateStaticObject(Buff_PosTable.pos5,{1,0,0},Buff_IdTable.id3,2,"OnTouchSt_pos5_id3")
	end
-- pwdist.log("BUFF��ˢBUFF��555555555555555555end")
end



--BUFF��������
--pos1
function CurrentDungeonScript:OnTimer_SpawnBuff_pos1()
-- pwdist.log("BUFF��������1111111111111")
	self:Pos1_SpawnBuff()
-- pwdist.log("BUFF��������1111111111111end")
end
function CurrentDungeonScript:OnTouchSt_pos1_id1(staticobj,target)
-- pwdist.log("OnTouchSt_pos1_id1")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addspeed(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos1")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
function CurrentDungeonScript:OnTouchSt_pos1_id2(staticobj,target)
-- pwdist.log("OnTouchSt_pos1_id2")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addblood(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos1")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
function CurrentDungeonScript:OnTouchSt_pos1_id3(staticobj,target)
-- pwdist.log("OnTouchSt_pos1_id3")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addmons(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos1")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
--pos2
function CurrentDungeonScript:OnTimer_SpawnBuff_pos2()
-- pwdist.log("pos2")
	self:Pos2_SpawnBuff()
end
function CurrentDungeonScript:OnTouchSt_pos2_id1(staticobj,target)
-- pwdist.log("OnTouchSt_pos2_id1")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addspeed(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos2")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
function CurrentDungeonScript:OnTouchSt_pos2_id2(staticobj,target)
-- pwdist.log("OnTouchSt_pos2_id2")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addblood(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos2")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
function CurrentDungeonScript:OnTouchSt_pos2_id3(staticobj,target)
-- pwdist.log("OnTouchSt_pos2_id3")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addmons(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos2")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
--pos3
function CurrentDungeonScript:OnTimer_SpawnBuff_pos3()
-- pwdist.log("OnTimer_SpawnBuff_pos3")
	self:Pos3_SpawnBuff()
end
function CurrentDungeonScript:OnTouchSt_pos3_id1(staticobj,target)
-- pwdist.log("OnTouchSt_pos3_id1")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addspeed(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos3")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
function CurrentDungeonScript:OnTouchSt_pos3_id2(staticobj,target)
-- pwdist.log("OnTouchSt_pos3_id2")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addblood(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos3")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
function CurrentDungeonScript:OnTouchSt_pos3_id3(staticobj,target)
-- pwdist.log("OnTouchSt_pos3_id3")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addmons(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos3")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
--pos4
function CurrentDungeonScript:OnTimer_SpawnBuff_pos4()
-- pwdist.log("OnTimer_SpawnBuff_pos4")
	self:Pos4_SpawnBuff()
end
function CurrentDungeonScript:OnTouchSt_pos4_id1(staticobj,target)
-- pwdist.log("OnTouchSt_pos4_id1")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addspeed(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos4")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
function CurrentDungeonScript:OnTouchSt_pos4_id2(staticobj,target)
-- pwdist.log("OnTouchSt_pos4_id2")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addblood(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos4")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
function CurrentDungeonScript:OnTouchSt_pos4_id3(staticobj,target)
-- pwdist.log("OnTouchSt_pos4_id3")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addmons(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos4")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
--pos5
function CurrentDungeonScript:OnTimer_SpawnBuff_pos5()
-- pwdist.log("pos5")
	self:Pos5_SpawnBuff()
end
function CurrentDungeonScript:OnTouchSt_pos5_id1(staticobj,target)
-- pwdist.log("OnTouchSt_pos5_id1")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addspeed(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos5")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
function CurrentDungeonScript:OnTouchSt_pos5_id2(staticobj,target)
-- pwdist.log("OnTouchSt_pos5_id2")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addblood(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos5")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end
function CurrentDungeonScript:OnTouchSt_pos5_id3(staticobj,target)
-- pwdist.log("OnTouchSt_pos5_id3")
	if not staticobj:IsInWorld() then return end
	local human = target:cast('Human')
	self:Buff_addmons(human)
	self.SModDungeonScript:CreateTimer(Buff_SpawnTime,"OnTimer_SpawnBuff_pos5")
	self:AddScore_buffnum(target)
	staticobj:LeaveWorld(0)
	local hid,typeobj,state,dir = self:GetBuffInfo(staticobj)
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
	self.SModLogicBattle:CommitMapInfoUpdate()
end

--BUFF��Ч�������ٶ�
function CurrentDungeonScript:Buff_addspeed(human)
-- pwdist.log("BUFF��Ч�������ٶ�")
	local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
	if self.TeamsTable[tid]["camp"] == R_Faction_human then
		for k , v in pairs(PVP_NpcsTable[self.CurrentLv].R_NpcId1) do
			local CreatureTab_s = {}
			CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v)
			if #CreatureTab_s > 0 then
				for i , j in pairs(CreatureTab_s) do
					j:GetModAura():Create(BUFF_speed)
				end
			end
		end
		for k , v in pairs(PVP_NpcsTable[self.CurrentLv].R_NpcId2) do
			local CreatureTab_s = {}
			CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v)
			if #CreatureTab_s > 0 then
				for i , j in pairs(CreatureTab_s) do
					j:GetModAura():Create(BUFF_speed)
				end
			end
		end	
		for k , v in pairs(PVP_NpcsTable[self.CurrentLv].R_NpcId3) do
			local CreatureTab_s = {}
			CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v)
			if #CreatureTab_s > 0 then
				for i , j in pairs(CreatureTab_s) do
					j:GetModAura():Create(BUFF_speed)
				end
			end
		end			
	else
		for k , v in pairs(PVP_NpcsTable[self.CurrentLv].B_NpcId1) do
			local CreatureTab_s = {}
			CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v)
			if #CreatureTab_s > 0 then
				for i , j in pairs(CreatureTab_s) do
					j:GetModAura():Create(BUFF_speed)
				end
			end
		end
		for k , v in pairs(PVP_NpcsTable[self.CurrentLv].B_NpcId2) do
			local CreatureTab_s = {}
			CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v)
			if #CreatureTab_s > 0 then
				for i , j in pairs(CreatureTab_s) do
					j:GetModAura():Create(BUFF_speed)
				end
			end
		end
		for k , v in pairs(PVP_NpcsTable[self.CurrentLv].B_NpcId3) do
			local CreatureTab_s = {}
			CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v)
			if #CreatureTab_s > 0 then
				for i , j in pairs(CreatureTab_s) do
					j:GetModAura():Create(BUFF_speed)
				end
			end
		end
	end
	--������Ϣ
	if human:GetFaction() == R_Faction_human then
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_speed1,ChannelType.Announcement,2,R_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_speed2,ChannelType.Announcement,2,B_Faction_human)
	else
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_speed1,ChannelType.Announcement,2,B_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_speed2,ChannelType.Announcement,2,R_Faction_human)
	end
end


--BUFF��Ч������Ѫ
function CurrentDungeonScript:Buff_addblood(human)
-- pwdist.log("BUFF��Ч������Ѫ")
	local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
	if self.TeamsTable[tid]["camp"] == R_Faction_human then
		for k , v in pairs(PVP_NpcsTable[self.CurrentLv].R_NpcId1) do
			local CreatureTab_s = {}
			CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v)
			if #CreatureTab_s > 0 then
				for i , j in pairs(CreatureTab_s) do
					j:GetModAura():Create(BUFF_blood1)
					j:GetModAura():Create(BUFF_blood2)
				end
			end
		end
		for k , v in pairs(PVP_NpcsTable[self.CurrentLv].R_NpcId2) do
			local CreatureTab_s = {}
			CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v)
			if #CreatureTab_s > 0 then
				for i , j in pairs(CreatureTab_s) do
					j:GetModAura():Create(BUFF_blood1)
					j:GetModAura():Create(BUFF_blood2)
				end
			end
		end
		for k , v in pairs(PVP_NpcsTable[self.CurrentLv].R_NpcId3) do
			local CreatureTab_s = {}
			CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v)
			if #CreatureTab_s > 0 then
				for i , j in pairs(CreatureTab_s) do
					j:GetModAura():Create(BUFF_blood1)
					j:GetModAura():Create(BUFF_blood2)
				end
			end
		end
	else
		for k , v in pairs(PVP_NpcsTable[self.CurrentLv].B_NpcId1) do
			local CreatureTab_s = {}
			CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v)
			if #CreatureTab_s > 0 then
				for i , j in pairs(CreatureTab_s) do
					j:GetModAura():Create(BUFF_blood1)
					j:GetModAura():Create(BUFF_blood2)
				end
			end
		end
		for k , v in pairs(PVP_NpcsTable[self.CurrentLv].B_NpcId2) do
			local CreatureTab_s = {}
			CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v)
			if #CreatureTab_s > 0 then
				for i , j in pairs(CreatureTab_s) do
					j:GetModAura():Create(BUFF_blood1)
					j:GetModAura():Create(BUFF_blood2)
				end
			end
		end
		for k , v in pairs(PVP_NpcsTable[self.CurrentLv].B_NpcId3) do
			local CreatureTab_s = {}
			CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v)
			if #CreatureTab_s > 0 then
				for i , j in pairs(CreatureTab_s) do
					j:GetModAura():Create(BUFF_blood1)
					j:GetModAura():Create(BUFF_blood2)
				end
			end
		end
	end
	--������Ϣ
	if human:GetFaction() == R_Faction_human then
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_blood1,ChannelType.Announcement,2,R_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_blood2,ChannelType.Announcement,2,B_Faction_human)
	else
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_blood1,ChannelType.Announcement,2,B_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_blood2,ChannelType.Announcement,2,R_Faction_human)
	end
end

--BUFF��Ч������ˢ��
function CurrentDungeonScript:Buff_addmons(human)
-- pwdist.log("BUFF��Ч������ˢ��")
	local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
	self.TeamsTable[tid]["addmons"] = self.TeamsTable[tid]["addmons"] + BUFF_addmons_num
	
	--������Ϣ
	if human:GetFaction() == R_Faction_human then
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_addnum1,ChannelType.Announcement,2,R_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_addnum2,ChannelType.Announcement,2,B_Faction_human)
	else
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_addnum1,ChannelType.Announcement,2,B_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_addnum2,ChannelType.Announcement,2,R_Faction_human)
	end
end

--BUFF�����󣬸���������Ҽ�һ������
function CurrentDungeonScript:AddScore_buffnum(target)
-- pwdist.log("BUFF�����󣬸���������Ҽ�һ������")
	if target:IsKindOf(CLSID.Human) then 
		local human= target:cast("Human")
		local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
		local hid = tostring(human:GetID())
		self.TeamMembersTable[tid][hid]["get_buff"] = self.TeamMembersTable[tid][hid]["get_buff"] + 1
	end
end

--�߼�������ִ��unit�����ͼ��Ϣ��ȡ����
function CurrentDungeonScript:UpdateUnitinfo(creature)
-- pwdist.log("�߼�������ִ��unit�����ͼ��Ϣ��ȡ����")
	local tid,hid,typem = self:GetMonsterInfo(creature)
	local state = Map_state_live
	if creature:IsDead() then
		state = Map_state_dead
	end
	local dir = Map_race_human
	if tid == self.RTeamId then
		dir = Map_race_human
	else
		dir = Map_race_spirit
	end
	self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typem,state,dir)
end



--����С��ͼ��Ϣ
function CurrentDungeonScript:UpdateMapInfo()
-- pwdist.log("����С��ͼ��Ϣ")
	--������
	for k , v  in pairs(self.MonsVsTower) do
		local Tower1Tab_s = self.Stage:GetModAOI():CollectCreatureInStage(v.Obj1.id)
		if #Tower1Tab_s >= 1 then
			self:UpdateUnitinfo(Tower1Tab_s[1])
		end
		local Tower2Tab_s = self.Stage:GetModAOI():CollectCreatureInStage(v.Obj2.id)
		if #Tower2Tab_s >= 1 then
			self:UpdateUnitinfo(Tower2Tab_s[1])
		end
		local Tower3Tab_s = self.Stage:GetModAOI():CollectCreatureInStage(v.Obj3.id)
		if #Tower3Tab_s >= 1 then
			self:UpdateUnitinfo(Tower3Tab_s[1])
		end
		local Tower4Tab_s = self.Stage:GetModAOI():CollectCreatureInStage(v.Obj4.id)
		if #Tower4Tab_s >= 1 then
			self:UpdateUnitinfo(Tower4Tab_s[1])
		end
	end			
	--����ˮ��BUFF
	local BuffTab = self.Stage:GetModAOI():CollectCreatureInStageByType(3)
	for i , j in pairs(BuffTab) do
		local creatureid = j:GetCreatureType()
		if creatureid == Buff_IdTable.id1 or creatureid == Buff_IdTable.id2 or creatureid == Buff_IdTable.id3 then
			local hid,typeobj,state,dir = self:GetBuffInfo(j)
			self.SModLogicBattle:UpdateBattleMapInfo(0,hid,typeobj,state,dir)
		end
	end
	self.SModLogicBattle:CommitMapInfoUpdate()
end

--����һ��ˮ��BUFF�����жϸ�ˮ��������UID�����͡�״̬
function CurrentDungeonScript:GetBuffInfo(obj)
-- pwdist.log("����һ��ˮ��BUFF�����жϸ�ˮ��������UID�����͡�״̬")
	local hid = tostring(obj:GetID())
	local typeobj = 0
	if obj:GetCreatureType() == Buff_IdTable.id1 then
		typeobj = Map_type_buff_speed
	elseif obj:GetCreatureType() == Buff_IdTable.id2 then
		typeobj = Map_type_buff_blood
	elseif obj:GetCreatureType() == Buff_IdTable.id3 then
		typeobj = Map_type_buff_addmons
	end	
	local dir = Map_race_human
	local state = Map_state_live
	if not obj:IsInWorld() then 
		state = Map_state_dead
	end
-- pwdist.log("����һ��ˮ��BUFF�����жϸ�ˮ��������UID�����͡�״̬end")
	return hid,typeobj,state,dir
end

--����һ����������жϸù����������顢UID������
function CurrentDungeonScript:GetMonsterInfo(creature)
-- pwdist.log("����һ����������жϸù����������顢UID������")
	local creatureid = creature:GetCreatureType()
	local tid = 0
	local hid = tostring(creature:GetID())
	local typem = 0
	
	if creature:GetFaction() == R_Faction_tower or creature:GetFaction() == R_Faction_npc then
		tid = self.RTeamId
	else
		tid = self.BTeamId
	end
	if creature:GetFaction() == B_Faction_npc or creature:GetFaction() == R_Faction_npc then
		typem = Map_type_monster
	else
		for i , j in pairs(self.MonsVsTower) do
			if creatureid == j.Obj1.id then
				if i == 1 then
					typem = Map_type_B_tower6
				elseif i == 2 then
					typem = Map_type_B_tower3
				elseif i == 3 then
					typem = Map_type_B_tower9
				elseif i == 4 then
					typem = Map_type_R_tower6
				elseif i == 5 then
					typem = Map_type_R_tower3
				elseif i == 6 then
					typem = Map_type_R_tower9
				end
			elseif creatureid == j.Obj2.id then
				if i == 1 then
					typem = Map_type_B_tower5
				elseif i == 2 then
					typem = Map_type_B_tower2
				elseif i == 3 then
					typem = Map_type_B_tower8
				elseif i == 4 then
					typem = Map_type_R_tower5
				elseif i == 5 then
					typem = Map_type_R_tower2	
				elseif i == 6 then
					typem = Map_type_R_tower8					
				end
			elseif creatureid == j.Obj3.id then
				if i == 1 then
					typem = Map_type_B_tower4
				elseif i == 2 then
					typem = Map_type_B_tower1
				elseif i == 3 then
					typem = Map_type_B_tower7
				elseif i == 4 then
					typem = Map_type_R_tower4
				elseif i == 5 then
					typem = Map_type_R_tower1
				elseif i == 6 then
					typem = Map_type_R_tower7
				end
			elseif creatureid == j.Obj4.id then
				if i == 1 or i == 2 or i == 3 then
					typem = Map_type_B_encam
				else
					typem = Map_type_R_encam
				end
			end
		end
	end
	return tid,hid,typem
end
