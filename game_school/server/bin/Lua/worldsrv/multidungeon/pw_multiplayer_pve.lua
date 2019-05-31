CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")

-----------------------------------------------------------��������
local DungeonState = 0									-----����״̬ 		 -1-����ʧ�ܷ��Ž����׶�  0-��������	1-����׼���׶�   2-������ʼ�׶�  3-�������Ž����׶� 4-�������Ž��������������׶�
local DungeonMaxTime = 48000							-----�������ʱ������
local DungeonReadyTime = 60							    -----��������׼��ʱ��60
local WaveNumTime = 20									-----ÿ���ֵ�ˢ��ʱ��20
local TouMuTime = 60									-----СͷĿ��ˢ��ʱ��
local TouMuWaveNum = 10									-----�ڼ�����СͷĿ
local AttackTime = 150									-----��һ��͵Ϯ�ֵ�ˢ��ʱ��,ÿ���ֵ�ˢ��ʱ��150
local SpecialTime = 210									-----����ֵ�ˢ��ʱ��,ÿ���ֵ�ˢ��ʱ��210
local MaxHumNum = 20									-----�������������
local MaxWaveNum = 50									-----���ˢ��50����-ֻ����10�ı���
local AttackMaxWaveNum = 7								-----͵Ϯ�����ˢ��7��
local SpecialMaxWaveNum = 5								-----����֣����ˢ��5��
local RecordWaveNum = 0								    -----��¼���ﲨ��
local RecordAttack = 1									-----��¼͵Ϯ�ֲ���
local RecordSpecial = 1									-----����ֲ���
local OldTime = 0										-----��¼��������ʱ��
local DungeonDiffcuity = 0								-----�����Ѷ�
local DungeonInfo = {13203,13204,13205,13206,13207,13209,13212,13213,13216,13217,13218,13214,13215,13219,13220,13221,13222,}-----������ʾ��Ϣ����1-ÿ���ֵ�ˢ����ʾ��2-СͷĿ��ʾ 3-͵Ϯ�֣�4����֣�5-boss
local DungeonStrInfo = {3400,3401,3402,3403,3404,3405,3406,3407,3408,3409,3410,3411,3412,3413,3414,}-----����Ƶ������˵�Ļ�
local PeriodTimer = 0				----��¼ÿ������ָ��������ֵ�ļ�ʱ��
local PeriodTime = 5				----ÿ��5��ָ�ȫ�����������ֵ
local IntegralID = {1,2,3,4,5,6,7,8,9}----��ɱ����Ļ���


local DungeonNpcID = {NpcID = {},NpcIDOrg = {},NpcIDPos = {}}							-----����NPC��ID
DungeonNpcID.NpcID[1] = {50301,50302,50303,50306,50305,50307,50304,}	-----1��Ҫ�ػ���NPC   2����  3����   4Բ̨����Զ�� 5����ʿ����ս  6�ξ����� 7�����
-- DungeonNpcID.NpcID[2] = {50301,50302,50303,50306,50305,50304,50307,}	
-- DungeonNpcID.NpcID[3] = {50301,50302,50303,50306,50305,50304,50307,}
-- DungeonNpcID.NpcID[4] = {50301,50302,50303,50306,50305,50304,50307,}
-- DungeonNpcID.NpcID[5] = {50301,50302,50303,50306,50305,50304,50307,}
-- DungeonNpcID.NpcID[6] = {50301,50302,50303,50306,50305,50304,50307,}
local R_DungeonNpcID = {}				------��NPC������
DungeonNpcID.NpcIDOrg[1] = {{0,0,-1},}			-----ÿ��NPCID�ĳ���
DungeonNpcID.NpcIDOrg[2] = {{0,0,-1},}
DungeonNpcID.NpcIDOrg[3] = {{0,0,-1},}
DungeonNpcID.NpcIDOrg[4] = 
						{
							{1,0,0},	{1,0,0},	{1,0,0},	{-1,0,0},	{-1,0,0},	{-1,0,0},	
							{1,0,0},	{1,0,0},	{1,0,0},	
							{-1,0,0},	{-1,0,0},	{-1,0,0},	
							{1,0,0},	{-1,0,0},	
						}
DungeonNpcID.NpcIDOrg[5] = 
						{
							{0,0,-1},	{0,0,-1},	
							{0,0,-1},	{1,0,0},	
							{0,0,-1},	{0,0,-1},		
						}
-- DungeonNpcID.NpcIDOrg[6] = {{-0.8,0,0.6},}
DungeonNpcID.NpcIDOrg[6] = {{0,0,-1},	{-1,0,0},	{0,0,1},}
DungeonNpcID.NpcIDOrg[7] = {{0.1,0,-1},}

DungeonNpcID.NpcIDPos[1] = {{128.0,55.8,237.3},}			-----���ĵ�
DungeonNpcID.NpcIDPos[2] = {{132.7,55.8,229.2},}			-----����
DungeonNpcID.NpcIDPos[3] = {{122.7,55.8,229.2},}			-----����
DungeonNpcID.NpcIDPos[4] = 
						{
							{120.4,55.8,238.6},		{120.4,55.8,234.6},		{120.4,55.8,230.6},		{136.3,55.8,238.6},		{136.3,55.8,234.6},		{136.3,55.8,230.6},	
							{139.3,54.4,219.4},		{139.3,54.4,215.4},		{139.3,54.4,211.4},
							{116.5,54.4,219.4},		{116.5,54.4,215.4},		{116.5,54.4,211.4},	
							{150.4,54.4,211.1},		{105.5,54.4,210.5},
						}									-----Զ���α�
DungeonNpcID.NpcIDPos[5] = 
						{
							{134.2,52.3,193.7},	{121.7,52.3,193.7},
							{171.1,52.3,218.2},	{161.5,52.3,208.1},	
							{84.4,52.3,220.1},	{92.3,52.3,211.0},
						}									-----�����α�	
DungeonNpcID.NpcIDPos[6] = {{135.4,52.3,172.1},	{64.0,52.3,202.8},	{188.8,52.3,201.9},}
DungeonNpcID.NpcIDPos[7] = {{124.7,55.8,236.3},	}
															-----�ξ�����
local RecordMonterID = { MonterID = {},
						BMonterIDData = {},BMonterIDData1 = {},BMonterIDData2 = {},BMonterIDData3 = {},BMonterIDData4 = {},BMonterIDData5 = {},
						BMonterIDData6 = {},BMonterIDData7 = {},BMonterIDData8 = {},BMonterIDData9 = {},BMonterIDData10 = {},BMonterIDData11 = {},
						BMonterIDData12 = {},BMonterIDData13 = {},
						NJMonterIDData = {},	TCMonterIDData = {},	BOSSMonterIDData = {},}			-----���йֵĹ���ID
RecordMonterID.MonterID[1] = {50308,50309,50310,50311,50312,50313,50314,50315,50316,}	-----����ID	1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���  6-�ɹ��ڼ�  7-����ֵ���ͷĿ 8-�����ɽ������  9-����BOSS������


-----��·1�ż��ֹ�- 1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���
local R_BMonterIDData1 = {}	-----��¼����С�ֵ�Unity 
RecordMonterID.BMonterIDData1[1] = {ID = {RecordMonterID.MonterID[1][1],},PointOrg = {0,0,1},Pos = {127.35,52.4,46.57},Route1 = {{131.31,52.4,99.33},{125.71,52.4,94.5},{118.42,52.4,97.78}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 3,}
RecordMonterID.BMonterIDData1[2] = {ID = {RecordMonterID.MonterID[1][2],},PointOrg = {0,0,1},Pos = {127.35,52.4,46.57},Route1 = {{131.31,52.4,99.33},{125.71,52.4,94.5},{118.42,52.4,97.78}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData1[3] = {ID = {RecordMonterID.MonterID[1][3],},PointOrg = {0,0,1},Pos = {127.35,52.4,46.57},Route1 = {{131.31,52.4,99.33},{125.71,52.4,94.5},{118.42,52.4,97.78}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData1[4] = {ID = {RecordMonterID.MonterID[1][4],},PointOrg = {0,0,1},Pos = {127.35,52.4,46.57},Route1 = {{131.31,52.4,99.33},{125.71,52.4,94.5},{118.42,52.4,97.78}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData1[5] = {ID = {RecordMonterID.MonterID[1][5],},PointOrg = {0,0,1},Pos = {127.35,52.4,46.57},Route1 = {{131.31,52.4,99.33},{125.71,52.4,94.5},{118.42,52.4,97.78}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}

-----��·2�ż��ֹ�- 1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���
local R_BMonterIDData2 = {}	-----��¼����С�ֵ�Unity 
RecordMonterID.BMonterIDData2[1] = {ID = {RecordMonterID.MonterID[1][1],},PointOrg = {0,0,1},Pos = {151.45,52.4,83.38},Route1 = {{144.54,52.4,98.17},{146.36,52.4,102.27},{149.5,52.4,100.74}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData2[2] = {ID = {RecordMonterID.MonterID[1][2],},PointOrg = {0,0,1},Pos = {151.45,52.4,83.38},Route1 = {{144.54,52.4,98.17},{146.36,52.4,102.27},{149.5,52.4,100.74}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData2[3] = {ID = {RecordMonterID.MonterID[1][3],},PointOrg = {0,0,1},Pos = {151.45,52.4,83.38},Route1 = {{144.54,52.4,98.17},{146.36,52.4,102.27},{149.5,52.4,100.74}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData2[4] = {ID = {RecordMonterID.MonterID[1][4],},PointOrg = {0,0,1},Pos = {151.45,52.4,83.38},Route1 = {{144.54,52.4,98.17},{146.36,52.4,102.27},{149.5,52.4,100.74}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}
RecordMonterID.BMonterIDData2[5] = {ID = {RecordMonterID.MonterID[1][5],},PointOrg = {0,0,1},Pos = {151.45,52.4,83.38},Route1 = {{144.54,52.4,98.17},{146.36,52.4,102.27},{149.5,52.4,100.74}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}

-----��·3�ż��ֹ�- 1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���
local R_BMonterIDData3 = {}	-----��¼����С�ֵ�Unity 
RecordMonterID.BMonterIDData3[1] = {ID = {RecordMonterID.MonterID[1][1],},PointOrg = {0,0,1},Pos = {103.88,52.4,153.98},Route1 = {{117.05,52.4,155.5},{124.64,52.4,155.04},{130.64,52.4,154.88}},Route2 = {{126.61,52.4,177.93},{128.45,52.4,171.49},{129.88,52.4,178.12}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData3[2] = {ID = {RecordMonterID.MonterID[1][2],},PointOrg = {0,0,1},Pos = {103.88,52.4,153.98},Route1 = {{117.05,52.4,155.5},{124.64,52.4,155.04},{130.64,52.4,154.88}},Route2 = {{126.61,52.4,177.93},{128.45,52.4,171.49},{129.88,52.4,178.12}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData3[3] = {ID = {RecordMonterID.MonterID[1][3],},PointOrg = {0,0,1},Pos = {103.88,52.4,153.98},Route1 = {{117.05,52.4,155.5},{124.64,52.4,155.04},{130.64,52.4,154.88}},Route2 = {{126.61,52.4,177.93},{128.45,52.4,171.49},{129.88,52.4,178.12}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData3[4] = {ID = {RecordMonterID.MonterID[1][4],},PointOrg = {0,0,1},Pos = {103.88,52.4,153.98},Route1 = {{117.05,52.4,155.5},{124.64,52.4,155.04},{130.64,52.4,154.88}},Route2 = {{126.61,52.4,177.93},{128.45,52.4,171.49},{129.88,52.4,178.12}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}
RecordMonterID.BMonterIDData3[5] = {ID = {RecordMonterID.MonterID[1][5],},PointOrg = {0,0,1},Pos = {103.88,52.4,153.98},Route1 = {{117.05,52.4,155.5},{124.64,52.4,155.04},{130.64,52.4,154.88}},Route2 = {{126.61,52.4,177.93},{128.45,52.4,171.49},{129.88,52.4,178.12}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}

-----��·4�ż��ֹ�- 1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���
local R_BMonterIDData4 = {}	-----��¼����С�ֵ�Unity 
RecordMonterID.BMonterIDData4[1] = {ID = {RecordMonterID.MonterID[1][1],},PointOrg = {0,0,1},Pos = {48.38,52.4,37.06},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 3,}
RecordMonterID.BMonterIDData4[2] = {ID = {RecordMonterID.MonterID[1][2],},PointOrg = {0,0,1},Pos = {48.38,52.4,37.06},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData4[3] = {ID = {RecordMonterID.MonterID[1][3],},PointOrg = {0,0,1},Pos = {48.38,52.4,37.06},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData4[4] = {ID = {RecordMonterID.MonterID[1][4],},PointOrg = {0,0,1},Pos = {48.38,52.4,37.06},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData4[5] = {ID = {RecordMonterID.MonterID[1][5],},PointOrg = {0,0,1},Pos = {48.38,52.4,37.06},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}

-----��·5�ż��ֹ�- 1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���
local R_BMonterIDData5 = {}	-----��¼����С�ֵ�Unity 
RecordMonterID.BMonterIDData5[1] = {ID = {RecordMonterID.MonterID[1][1],},PointOrg = {0,0,1},Pos = {70.4,52.4,57.5},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData5[2] = {ID = {RecordMonterID.MonterID[1][2],},PointOrg = {0,0,1},Pos = {70.4,52.4,57.5},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData5[3] = {ID = {RecordMonterID.MonterID[1][3],},PointOrg = {0,0,1},Pos = {70.4,52.4,57.5},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData5[4] = {ID = {RecordMonterID.MonterID[1][4],},PointOrg = {0,0,1},Pos = {70.4,52.4,57.5},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}
RecordMonterID.BMonterIDData5[5] = {ID = {RecordMonterID.MonterID[1][5],},PointOrg = {0,0,1},Pos = {70.4,52.4,57.5},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}

-----��·6�ż��ֹ�- 1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���
local R_BMonterIDData6 = {}	-----��¼����С�ֵ�Unity 
RecordMonterID.BMonterIDData6[1] = {ID = {RecordMonterID.MonterID[1][1],},PointOrg = {0,0,1},Pos = {45.83,52.4,64.66},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData6[2] = {ID = {RecordMonterID.MonterID[1][2],},PointOrg = {0,0,1},Pos = {45.83,52.4,64.66},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData6[3] = {ID = {RecordMonterID.MonterID[1][3],},PointOrg = {0,0,1},Pos = {45.83,52.4,64.66},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData6[4] = {ID = {RecordMonterID.MonterID[1][4],},PointOrg = {0,0,1},Pos = {45.83,52.4,64.66},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}
RecordMonterID.BMonterIDData6[5] = {ID = {RecordMonterID.MonterID[1][5],},PointOrg = {0,0,1},Pos = {45.83,52.4,64.66},Route1 = {{48.6,52.4,109},{54.53,52.4,114.6},{59.65,52.4,109.84}},Route2 = {{65.06,52.4,195.09},{67.46,52.4,190.17},{69.02,52.4,196.26}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}

-----��·7�ż��ֹ�- 1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���
local R_BMonterIDData7 = {}	-----��¼����С�ֵ�Unity 
RecordMonterID.BMonterIDData7[1] = {ID = {RecordMonterID.MonterID[1][1],},PointOrg = {0,0,1},Pos = {29.39,52.4,111.56},Route1 = {{131.31,52.4,99.33},{125.71,52.4,94.5},{118.42,52.4,97.78}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData7[2] = {ID = {RecordMonterID.MonterID[1][2],},PointOrg = {0,0,1},Pos = {29.39,52.4,111.56},Route1 = {{131.31,52.4,99.33},{125.71,52.4,94.5},{118.42,52.4,97.78}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData7[3] = {ID = {RecordMonterID.MonterID[1][3],},PointOrg = {0,0,1},Pos = {29.39,52.4,111.56},Route1 = {{131.31,52.4,99.33},{125.71,52.4,94.5},{118.42,52.4,97.78}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData7[4] = {ID = {RecordMonterID.MonterID[1][4],},PointOrg = {0,0,1},Pos = {29.39,52.4,111.56},Route1 = {{131.31,52.4,99.33},{125.71,52.4,94.5},{118.42,52.4,97.78}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}
RecordMonterID.BMonterIDData7[5] = {ID = {RecordMonterID.MonterID[1][5],},PointOrg = {0,0,1},Pos = {29.39,52.4,111.56},Route1 = {{131.31,52.4,99.33},{125.71,52.4,94.5},{118.42,52.4,97.78}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}

-----��·8�ż��ֹ�- 1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���
local R_BMonterIDData8 = {}	-----��¼����С�ֵ�Unity 
RecordMonterID.BMonterIDData8[1] = {ID = {RecordMonterID.MonterID[1][1],},PointOrg = {0,0,1},Pos = {38.45,52.4,166.58},Route1 = {{65.96,52.4,176.7},{67.37,52.4,183.28},{61.98,52.4,183.18}},Route2 = {{86.74,52.4,214.88},{87.24,52.4,212.88},{85.15,52.4,217.23}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData8[2] = {ID = {RecordMonterID.MonterID[1][2],},PointOrg = {0,0,1},Pos = {38.45,52.4,166.58},Route1 = {{65.96,52.4,176.7},{67.37,52.4,183.28},{61.98,52.4,183.18}},Route2 = {{86.74,52.4,214.88},{87.24,52.4,212.88},{85.15,52.4,217.23}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData8[3] = {ID = {RecordMonterID.MonterID[1][3],},PointOrg = {0,0,1},Pos = {38.45,52.4,166.58},Route1 = {{65.96,52.4,176.7},{67.37,52.4,183.28},{61.98,52.4,183.18}},Route2 = {{86.74,52.4,214.88},{87.24,52.4,212.88},{85.15,52.4,217.23}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData8[4] = {ID = {RecordMonterID.MonterID[1][4],},PointOrg = {0,0,1},Pos = {38.45,52.4,166.58},Route1 = {{65.96,52.4,176.7},{67.37,52.4,183.28},{61.98,52.4,183.18}},Route2 = {{86.74,52.4,214.88},{87.24,52.4,212.88},{85.15,52.4,217.23}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}
RecordMonterID.BMonterIDData8[5] = {ID = {RecordMonterID.MonterID[1][5],},PointOrg = {0,0,1},Pos = {38.45,52.4,166.58},Route1 = {{65.96,52.4,176.7},{67.37,52.4,183.28},{61.98,52.4,183.18}},Route2 = {{86.74,52.4,214.88},{87.24,52.4,212.88},{85.15,52.4,217.23}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}

-----��·9�ż��ֹ�- 1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���
local R_BMonterIDData9 = {}	-----��¼����С�ֵ�Unity 
RecordMonterID.BMonterIDData9[1] = {ID = {RecordMonterID.MonterID[1][1],},PointOrg = {0,0,1},Pos = {29.36,52.4,222.43},Route1 = {{66.14,52.4,197.76},{69.05,52.4,195.95},{65.94,52.4,195.84}},Route2 = {{86.74,52.4,214.88},{87.24,52.4,212.88},{85.15,52.4,217.23}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData9[2] = {ID = {RecordMonterID.MonterID[1][2],},PointOrg = {0,0,1},Pos = {29.36,52.4,222.43},Route1 = {{66.14,52.4,197.76},{69.05,52.4,195.95},{65.94,52.4,195.84}},Route2 = {{86.74,52.4,214.88},{87.24,52.4,212.88},{85.15,52.4,217.23}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData9[3] = {ID = {RecordMonterID.MonterID[1][3],},PointOrg = {0,0,1},Pos = {29.36,52.4,222.43},Route1 = {{66.14,52.4,197.76},{69.05,52.4,195.95},{65.94,52.4,195.84}},Route2 = {{86.74,52.4,214.88},{87.24,52.4,212.88},{85.15,52.4,217.23}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData9[4] = {ID = {RecordMonterID.MonterID[1][4],},PointOrg = {0,0,1},Pos = {29.36,52.4,222.43},Route1 = {{66.14,52.4,197.76},{69.05,52.4,195.95},{65.94,52.4,195.84}},Route2 = {{86.74,52.4,214.88},{87.24,52.4,212.88},{85.15,52.4,217.23}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}
RecordMonterID.BMonterIDData9[5] = {ID = {RecordMonterID.MonterID[1][5],},PointOrg = {0,0,1},Pos = {29.36,52.4,222.43},Route1 = {{66.14,52.4,197.76},{69.05,52.4,195.95},{65.94,52.4,195.84}},Route2 = {{86.74,52.4,214.88},{87.24,52.4,212.88},{85.15,52.4,217.23}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}

-----��·10�ż��ֹ�- 1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���
local R_BMonterIDData10 = {}	-----��¼����С�ֵ�Unity 
RecordMonterID.BMonterIDData10[1] = {ID = {RecordMonterID.MonterID[1][1],},PointOrg = {0,0,1},Pos = {207.66,52.4,35.57},Route1 = {{204.6,52.4,109.1},{200.23,52.4,113.82},{206.8,52.4,107.86}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 3,}
RecordMonterID.BMonterIDData10[2] = {ID = {RecordMonterID.MonterID[1][2],},PointOrg = {0,0,1},Pos = {207.66,52.4,35.57},Route1 = {{204.6,52.4,109.1},{200.23,52.4,113.82},{206.8,52.4,107.86}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData10[3] = {ID = {RecordMonterID.MonterID[1][3],},PointOrg = {0,0,1},Pos = {207.66,52.4,35.57},Route1 = {{204.6,52.4,109.1},{200.23,52.4,113.82},{206.8,52.4,107.86}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData10[4] = {ID = {RecordMonterID.MonterID[1][4],},PointOrg = {0,0,1},Pos = {207.66,52.4,35.57},Route1 = {{204.6,52.4,109.1},{200.23,52.4,113.82},{206.8,52.4,107.86}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData10[5] = {ID = {RecordMonterID.MonterID[1][5],},PointOrg = {0,0,1},Pos = {207.66,52.4,35.57},Route1 = {{204.6,52.4,109.1},{200.23,52.4,113.82},{206.8,52.4,107.86}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}

-----��·11�ż��ֹ�- 1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���
local R_BMonterIDData11 = {}	-----��¼����С�ֵ�Unity 
RecordMonterID.BMonterIDData11[1] = {ID = {RecordMonterID.MonterID[1][1],},PointOrg = {0,0,1},Pos = {228.44,52.4,92.04},Route1 = {{204.6,52.4,109.1},{200.23,52.4,113.82},{206.8,52.4,107.86}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData11[2] = {ID = {RecordMonterID.MonterID[1][2],},PointOrg = {0,0,1},Pos = {228.44,52.4,92.04},Route1 = {{204.6,52.4,109.1},{200.23,52.4,113.82},{206.8,52.4,107.86}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData11[3] = {ID = {RecordMonterID.MonterID[1][3],},PointOrg = {0,0,1},Pos = {228.44,52.4,92.04},Route1 = {{204.6,52.4,109.1},{200.23,52.4,113.82},{206.8,52.4,107.86}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData11[4] = {ID = {RecordMonterID.MonterID[1][4],},PointOrg = {0,0,1},Pos = {228.44,52.4,92.04},Route1 = {{204.6,52.4,109.1},{200.23,52.4,113.82},{206.8,52.4,107.86}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}
RecordMonterID.BMonterIDData11[5] = {ID = {RecordMonterID.MonterID[1][5],},PointOrg = {0,0,1},Pos = {228.44,52.4,92.04},Route1 = {{204.6,52.4,109.1},{200.23,52.4,113.82},{206.8,52.4,107.86}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}

-----��·12�ż��ֹ�- 1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���
local R_BMonterIDData12 = {}	-----��¼����С�ֵ�Unity
RecordMonterID.BMonterIDData12[1] = {ID = {RecordMonterID.MonterID[1][1],},PointOrg = {0,0,1},Pos = {182.3,52.4,129.73},Route1 = {{201.9,52.4,145.01},{197.27,52.4,144.8},{199.58,52.4,136.06}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData12[2] = {ID = {RecordMonterID.MonterID[1][2],},PointOrg = {0,0,1},Pos = {182.3,52.4,129.73},Route1 = {{201.9,52.4,145.01},{197.27,52.4,144.8},{199.58,52.4,136.06}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData12[3] = {ID = {RecordMonterID.MonterID[1][3],},PointOrg = {0,0,1},Pos = {182.3,52.4,129.73},Route1 = {{201.9,52.4,145.01},{197.27,52.4,144.8},{199.58,52.4,136.06}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData12[4] = {ID = {RecordMonterID.MonterID[1][4],},PointOrg = {0,0,1},Pos = {182.3,52.4,129.73},Route1 = {{201.9,52.4,145.01},{197.27,52.4,144.8},{199.58,52.4,136.06}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}
RecordMonterID.BMonterIDData12[5] = {ID = {RecordMonterID.MonterID[1][5],},PointOrg = {0,0,1},Pos = {182.3,52.4,129.73},Route1 = {{201.9,52.4,145.01},{197.27,52.4,144.8},{199.58,52.4,136.06}},Route2 = {{190.78,52.4,175.11},{196.39,52.4,173.51},{193.52,52.4,168.78}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}

-----��·13�ż��ֹ�- 1-�ɹŲ��� 2-�ɹž���  3-�ɹŹ����� 4-��Ѧ��2  5--СͷĿ�ɹŽ���
local R_BMonterIDData13 = {}	-----��¼����С�ֵ�Unity
RecordMonterID.BMonterIDData13[1] = {ID = {RecordMonterID.MonterID[1][1],},PointOrg = {0,0,1},Pos = {212.25,52.4,188.99},Route1 = {{189.09,52.4,194.23},{187.08,52.4,191.08},{184.87,52.4,196.57}},Route2 = {{162.07,52.4,215.41},{166.98,52.4,216.05},{162.12,52.4,214.09}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 2,}
RecordMonterID.BMonterIDData13[2] = {ID = {RecordMonterID.MonterID[1][2],},PointOrg = {0,0,1},Pos = {212.25,52.4,188.99},Route1 = {{189.09,52.4,194.23},{187.08,52.4,191.08},{184.87,52.4,196.57}},Route2 = {{162.07,52.4,215.41},{166.98,52.4,216.05},{162.12,52.4,214.09}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData13[3] = {ID = {RecordMonterID.MonterID[1][3],},PointOrg = {0,0,1},Pos = {212.25,52.4,188.99},Route1 = {{189.09,52.4,194.23},{187.08,52.4,191.08},{184.87,52.4,196.57}},Route2 = {{162.07,52.4,215.41},{166.98,52.4,216.05},{162.12,52.4,214.09}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}
RecordMonterID.BMonterIDData13[4] = {ID = {RecordMonterID.MonterID[1][4],},PointOrg = {0,0,1},Pos = {212.25,52.4,188.99},Route1 = {{189.09,52.4,194.23},{187.08,52.4,191.08},{184.87,52.4,196.57}},Route2 = {{162.07,52.4,215.41},{166.98,52.4,216.05},{162.12,52.4,214.09}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}
RecordMonterID.BMonterIDData13[5] = {ID = {RecordMonterID.MonterID[1][5],},PointOrg = {0,0,1},Pos = {212.25,52.4,188.99},Route1 = {{189.09,52.4,194.23},{187.08,52.4,191.08},{184.87,52.4,196.57}},Route2 = {{162.07,52.4,215.41},{166.98,52.4,216.05},{162.12,52.4,214.09}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 0,}

-------�ڼ��
local R_NJMonterIDData = {}	-----��¼�ڼ��Unity
RecordMonterID.NJMonterIDData[1] = {ID = {RecordMonterID.MonterID[1][6],},PointOrg = {0,0,-1},Pos = {174.6,52.3,225.23},Route1 = {{161.36,52.4,215.53},},Route2 = {{129.17,54.95,215.62},},Route3 = {{128.0,55.8,227.7},},Num = 1,}	
RecordMonterID.NJMonterIDData[2] = {ID = {RecordMonterID.MonterID[1][6],},PointOrg = {0,0,-1},Pos = {82.89,52.3,232.68},Route1 = {{93.09,52.4,215.08},},Route2 = {{129.17,54.95,215.62},},Route3 = {{128.0,55.8,227.7},},Num = 1,}	

local R_TCMonterIDData = {}------��¼buff�ֵ�unity
------�����
RecordMonterID.TCMonterIDData[1] = {ID = RecordMonterID.MonterID[1][7],PointOrg = {-0.5,0,-0.9}, Pos = {160,54.32,119},}
RecordMonterID.TCMonterIDData[2] = {ID = RecordMonterID.MonterID[1][7],PointOrg = {-0.5,0,-0.9}, Pos = {98.47,54.32,117.72},}
RecordMonterID.TCMonterIDData[3] = {ID = RecordMonterID.MonterID[1][8],PointOrg = {1,0,0}, Pos = {84.92,52.93,174.89},}
RecordMonterID.TCMonterIDData[4] = {ID = RecordMonterID.MonterID[1][8],PointOrg = {0.6,0,-0.8}, Pos = {172.6,52.9,174.44},}

-----����BOSS
local R_BOSSMonterIDData = {}	-----��¼BOSS��Unity
RecordMonterID.BOSSMonterIDData[1] = {ID = RecordMonterID.MonterID[1][9],PointOrg = {0,0,1},Pos = {127.35,52.4,46.57},Route1 = {{131.31,52.4,99.33},{125.71,52.4,94.5},{118.42,52.4,97.78}},Route2 = {{117.33,52.4,152.1},{128.41,52.4,152.1},{128.41,52.4,163.03}},Route3 = {{128.0,55.8,227.7},{132.0,55.8,227.7},{124.0,55.8,227.7}},Num = 1,}


local MonterBuff = {71000200,71000201,71000202,}	-----------����ֿ��Ը���ҵ�BUFF
local EnterBuff = 71000100																-----------ȫ��ҽ���BUFF
local RecordHumID = {}																	-----------��¼���볡�������hid����¼��ӦID�����ɱ�˶���ֻ��
local MinLevelStage = {1,120,160,200,240,280,}											-----------��ҽ���Ĳ�ͬ�ȼ��ε���͵ȼ�
local MaxLevelStage = {119,159,199,239,279,500,}										-----------��ҽ���Ĳ�ͬ�ȼ��ε���ߵȼ�
-------------------------------------------------------------------------------------------------------------------------------------------------------------------������Ϣ�б�
local msgStageTime = { times = {} }						-----�������ֵ���ʱ��ʼ��
msgStageTime.times[1] = { type = 0, sectime = 0, }	-----��������ʱʱ��
msgStageTime.times[2] = { type = 1, sectime = 0, }	-----��������ʱʱ��
msgStageTime.times[3] = { type = 2, sectime = 0, }	-----��������ʱʱ��
msgStageTime.times[4] = { type = 3, sectime = 0, }	-----��������
msgStageTime.times[5] = { type = 4, sectime = 0, }	-----���������

local DungeonFinish = { Finish = {} }						-----��������
DungeonFinish.Finish[1] = { type = 0, rank = 1 }

local msgStageHumanInfo = { human_infos = {} }	-----������������Ϣ
msgStageHumanInfo.rank = 0				----����Լ�����������������
msgStageHumanInfo.kill_count = 0		----�Լ�ɱ�˶��ٹַ���������
msgStageHumanInfo.human_count = 0		----������������������


local Maxtargetlist = {100,200,300,}	----����Ŀ��ÿ�������ֵ
local NFintargetlist = {13250,13251,13252,}-----����Ŀ����Ϣ����


local msg = { targetlist = {} }		
	msg.timesec = 0	----������ʼʱ��	
    local newtime = 0
    local oldtime = 0			
	msg.targetlist[1] = 
	{
		type = 1,
		strid = NFintargetlist[1],
		count = 0,
		maxcount = Maxtargetlist[1],
	}
	msg.targetlist[2] = 
	{
		type = 1,
		strid = NFintargetlist[2],
		count = 0,
		maxcount = Maxtargetlist[2],
	}	
	msg.targetlist[3] = 
	{
		type = 1,
		strid = NFintargetlist[3],
		count = 0,
		maxcount = Maxtargetlist[3],
	}


function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
	self.SModCommon = self.Stage:GetModCommon()
	local SModLogic = self.Stage:GetModLogic()	
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
    self.SModLogicMDPVE = SModLogic:cast("SModLogicMDPVE")
	
	self.SModObjs = self.Stage:GetModObjs()
	-----��������ʱ��ʱ��
	-- self.MaxTime = self.SModDungeonScript:CreateTimer(DungeonMaxTime,"EndTime")
	----����׼��ʱ���ʱ��
	self.MaxTime1 = self.SModDungeonScript:CreateTimer(DungeonReadyTime+WaveNumTime,"ReadyTime")	---��һ��С��ˢ��ʱ��
	self.MaxTime2 = self.SModDungeonScript:CreateTimer(AttackTime+DungeonReadyTime,"AttackTimeTime")			---��һ��͵Ϯ��ˢ��ʱ��
	self.MaxTime3 = self.SModDungeonScript:CreateTimer(SpecialTime+DungeonReadyTime,"SpecialTimeTime")		---��һ�������ˢ��ʱ��
	self.MaxTimeG = self.SModDungeonScript:CreatePeriodTimer(60,20,12,"guojinghanhua")		---��һ�������ˢ��ʱ��
	

	-----����ˢ��
	for k = 1,#RecordMonterID.MonterID,1 do
		for i = 1,#RecordMonterID.MonterID[k],1 do
			SetEventHandler(StageEvents.CreatureSpawn,"Monter_Spawn",{type = RecordMonterID.MonterID[k][i]})
		end
	end	
	----������������
	for g = 1,#RecordMonterID.MonterID,1 do
		for h = 1,#RecordMonterID.MonterID[g],1 do
			SetEventHandler(StageEvents.CreatureKilled,"MonterKilled",{type = RecordMonterID.MonterID[g][h]})
		end
	end	
	-----NPCˢ��
	for m = 1,#DungeonNpcID.NpcID,1 do
		for n = 1,#DungeonNpcID.NpcID[m],1 do
			SetEventHandler(StageEvents.CreatureSpawn,"NPC_Spawn",{type = DungeonNpcID.NpcID[m][n]})
		end
	end
	----��Ҫ�ػ���Npc��������
	for g = 1,#DungeonNpcID.NpcID,1 do
		SetEventHandler(StageEvents.CreatureKilled,"NPCKilled",{type = DungeonNpcID.NpcID[g][1]})
	end		
-------1�Ź���·���㴥����
	self.trigger_Bxiaoguaib1_1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData1[1].Route1[1],2,"BMonterIDData1_2","")
	self.trigger_Bxiaoguaib1_1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib1_1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData1[1].Route1[2],2,"BMonterIDData1_2","")
	self.trigger_Bxiaoguaib1_1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib1_1_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData1[1].Route1[3],2,"BMonterIDData1_2","")
	self.trigger_Bxiaoguaib1_1_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib1_2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData1[1].Route2[1],2,"BMonterIDData1_3","")
	self.trigger_Bxiaoguaib1_2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib1_2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData1[1].Route2[2],2,"BMonterIDData1_3","")
	self.trigger_Bxiaoguaib1_2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib1_2_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData1[1].Route2[3],2,"BMonterIDData1_3","")
	self.trigger_Bxiaoguaib1_2_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����

-------2�Ź���·���㴥����
	self.trigger_Bxiaoguaib2_1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData2[1].Route1[1],2,"BMonterIDData2_2","")
	self.trigger_Bxiaoguaib2_1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib2_1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData2[1].Route1[2],2,"BMonterIDData2_2","")
	self.trigger_Bxiaoguaib2_1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib2_1_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData2[1].Route1[3],2,"BMonterIDData2_2","")
	self.trigger_Bxiaoguaib2_1_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib2_2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData2[1].Route2[1],2,"BMonterIDData2_3","")
	self.trigger_Bxiaoguaib2_2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib2_2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData2[1].Route2[2],2,"BMonterIDData2_3","")
	self.trigger_Bxiaoguaib2_2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib2_2_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData2[1].Route2[3],2,"BMonterIDData2_3","")
	self.trigger_Bxiaoguaib2_2_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����

-------3�Ź���·���㴥����
	self.trigger_Bxiaoguaib3_1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData3[1].Route1[1],2,"BMonterIDData3_2","")
	self.trigger_Bxiaoguaib3_1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib3_1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData3[1].Route1[2],2,"BMonterIDData3_2","")
	self.trigger_Bxiaoguaib3_1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib3_1_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData3[1].Route1[3],2,"BMonterIDData3_2","")
	self.trigger_Bxiaoguaib3_1_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib3_2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData3[1].Route2[1],2,"BMonterIDData3_3","")
	self.trigger_Bxiaoguaib3_2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib3_2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData3[1].Route2[2],2,"BMonterIDData3_3","")
	self.trigger_Bxiaoguaib3_2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib3_2_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData3[1].Route2[3],2,"BMonterIDData3_3","")
	self.trigger_Bxiaoguaib3_2_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����

-------4�Ź���·���㴥����
	self.trigger_Bxiaoguaib4_1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData4[1].Route1[1],2,"BMonterIDData4_2","")
	self.trigger_Bxiaoguaib4_1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ���
	self.trigger_Bxiaoguaib4_1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData4[1].Route1[2],2,"BMonterIDData4_2","")
	self.trigger_Bxiaoguaib4_1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib4_1_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData4[1].Route1[3],2,"BMonterIDData4_2","")
	self.trigger_Bxiaoguaib4_1_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib4_2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData4[1].Route2[1],2,"BMonterIDData4_3","")
	self.trigger_Bxiaoguaib4_2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib4_2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData4[1].Route2[2],2,"BMonterIDData4_3","")
	self.trigger_Bxiaoguaib4_2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib4_2_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData4[1].Route2[3],2,"BMonterIDData4_3","")
	self.trigger_Bxiaoguaib4_2_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����

-------5�Ź���·���㴥����
	self.trigger_Bxiaoguaib5_1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData5[1].Route1[1],2,"BMonterIDData5_2","")
	self.trigger_Bxiaoguaib5_1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ���
	self.trigger_Bxiaoguaib5_1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData5[1].Route1[2],2,"BMonterIDData5_2","")
	self.trigger_Bxiaoguaib5_1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib5_1_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData5[1].Route1[3],2,"BMonterIDData5_2","")
	self.trigger_Bxiaoguaib5_1_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib5_2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData5[1].Route2[1],2,"BMonterIDData5_3","")
	self.trigger_Bxiaoguaib5_2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib5_2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData5[1].Route2[2],2,"BMonterIDData5_3","")
	self.trigger_Bxiaoguaib5_2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib5_2_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData5[1].Route2[3],2,"BMonterIDData5_3","")
	self.trigger_Bxiaoguaib5_2_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
-------6�Ź���·���㴥����
	self.trigger_Bxiaoguaib6_1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData6[1].Route1[1],2,"BMonterIDData6_2","")
	self.trigger_Bxiaoguaib6_1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ���
	self.trigger_Bxiaoguaib6_1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData6[1].Route1[2],2,"BMonterIDData6_2","")
	self.trigger_Bxiaoguaib6_1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib6_1_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData6[1].Route1[3],2,"BMonterIDData6_2","")
	self.trigger_Bxiaoguaib6_1_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib6_2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData6[1].Route2[1],2,"BMonterIDData6_3","")
	self.trigger_Bxiaoguaib6_2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib6_2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData6[1].Route2[2],2,"BMonterIDData6_3","")
	self.trigger_Bxiaoguaib6_2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib6_2_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData6[1].Route2[3],2,"BMonterIDData6_3","")
	self.trigger_Bxiaoguaib6_2_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����	
-------7�Ź���·���㴥����
	self.trigger_Bxiaoguaib7_1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData7[1].Route1[1],2,"BMonterIDData7_2","")
	self.trigger_Bxiaoguaib7_1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ���
	self.trigger_Bxiaoguaib7_1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData7[1].Route1[2],2,"BMonterIDData7_2","")
	self.trigger_Bxiaoguaib7_1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib7_1_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData7[1].Route1[3],2,"BMonterIDData7_2","")
	self.trigger_Bxiaoguaib7_1_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib7_2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData7[1].Route2[1],2,"BMonterIDData7_3","")
	self.trigger_Bxiaoguaib7_2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib7_2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData7[1].Route2[2],2,"BMonterIDData7_3","")
	self.trigger_Bxiaoguaib7_2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib7_2_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData7[1].Route2[3],2,"BMonterIDData7_3","")
	self.trigger_Bxiaoguaib7_2_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����	
-------8�Ź���·���㴥����
	self.trigger_Bxiaoguaib8_1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData8[1].Route1[1],2,"BMonterIDData8_2","")
	self.trigger_Bxiaoguaib8_1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ���
	self.trigger_Bxiaoguaib8_1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData8[1].Route1[2],2,"BMonterIDData8_2","")
	self.trigger_Bxiaoguaib8_1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib8_1_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData8[1].Route1[3],2,"BMonterIDData8_2","")
	self.trigger_Bxiaoguaib8_1_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib8_2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData8[1].Route2[1],2,"BMonterIDData8_3","")
	self.trigger_Bxiaoguaib8_2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib8_2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData8[1].Route2[2],2,"BMonterIDData8_3","")
	self.trigger_Bxiaoguaib8_2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib8_2_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData8[1].Route2[3],2,"BMonterIDData8_3","")
	self.trigger_Bxiaoguaib8_2_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����	
-------9�Ź���·���㴥����
	self.trigger_Bxiaoguaib9_1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData9[1].Route1[1],2,"BMonterIDData9_2","")
	self.trigger_Bxiaoguaib9_1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�
	self.trigger_Bxiaoguaib9_1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData9[1].Route1[2],2,"BMonterIDData9_2","")
	self.trigger_Bxiaoguaib9_1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib9_1_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData9[1].Route1[3],2,"BMonterIDData9_2","")
	self.trigger_Bxiaoguaib9_1_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib9_2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData9[1].Route2[1],2,"BMonterIDData9_3","")
	self.trigger_Bxiaoguaib9_2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib9_2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData9[1].Route2[2],2,"BMonterIDData9_3","")
	self.trigger_Bxiaoguaib9_2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib9_2_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData9[1].Route2[3],2,"BMonterIDData9_3","")
	self.trigger_Bxiaoguaib9_2_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����	
-------10�Ź���·���㴥����
	self.trigger_Bxiaoguaib10_1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData10[1].Route1[1],2,"BMonterIDData10_2","")
	self.trigger_Bxiaoguaib10_1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�
	self.trigger_Bxiaoguaib10_1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData10[1].Route1[2],2,"BMonterIDData10_2","")
	self.trigger_Bxiaoguaib10_1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib10_1_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData10[1].Route1[3],2,"BMonterIDData10_2","")
	self.trigger_Bxiaoguaib10_1_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib10_2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData10[1].Route2[1],2,"BMonterIDData10_3","")
	self.trigger_Bxiaoguaib10_2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib10_2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData10[1].Route2[2],2,"BMonterIDData10_3","")
	self.trigger_Bxiaoguaib10_2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib10_2_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData10[1].Route2[3],2,"BMonterIDData10_3","")
	self.trigger_Bxiaoguaib10_2_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����	
-------11�Ź���·���㴥����
	self.trigger_Bxiaoguaib11_1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData11[1].Route1[1],2,"BMonterIDData11_2","")
	self.trigger_Bxiaoguaib11_1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�
	self.trigger_Bxiaoguaib11_1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData11[1].Route1[2],2,"BMonterIDData11_2","")
	self.trigger_Bxiaoguaib11_1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib11_1_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData11[1].Route1[3],2,"BMonterIDData11_2","")
	self.trigger_Bxiaoguaib11_1_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib11_2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData11[1].Route2[1],2,"BMonterIDData11_3","")
	self.trigger_Bxiaoguaib11_2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib11_2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData11[1].Route2[2],2,"BMonterIDData11_3","")
	self.trigger_Bxiaoguaib11_2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib11_2_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData11[1].Route2[3],2,"BMonterIDData11_3","")
	self.trigger_Bxiaoguaib11_2_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����	
-------12�Ź���·���㴥����
	self.trigger_Bxiaoguaib12_1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData12[1].Route1[1],2,"BMonterIDData12_2","")
	self.trigger_Bxiaoguaib12_1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�
	self.trigger_Bxiaoguaib12_1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData12[1].Route1[2],2,"BMonterIDData12_2","")
	self.trigger_Bxiaoguaib12_1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib12_1_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData12[1].Route1[3],2,"BMonterIDData12_2","")
	self.trigger_Bxiaoguaib12_1_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib12_2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData12[1].Route2[1],2,"BMonterIDData12_3","")
	self.trigger_Bxiaoguaib12_2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib12_2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData12[1].Route2[2],2,"BMonterIDData12_3","")
	self.trigger_Bxiaoguaib12_2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib12_2_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData12[1].Route2[3],2,"BMonterIDData12_3","")
	self.trigger_Bxiaoguaib12_2_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����	
-------12�Ź���·���㴥����
	self.trigger_Bxiaoguaib13_1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData13[1].Route1[1],2,"BMonterIDData13_2","")
	self.trigger_Bxiaoguaib13_1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�
	self.trigger_Bxiaoguaib13_1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData13[1].Route1[2],2,"BMonterIDData13_2","")
	self.trigger_Bxiaoguaib13_1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib13_1_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData13[1].Route1[3],2,"BMonterIDData13_2","")
	self.trigger_Bxiaoguaib13_1_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib13_2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData13[1].Route2[1],2,"BMonterIDData13_3","")
	self.trigger_Bxiaoguaib13_2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib13_2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData13[1].Route2[2],2,"BMonterIDData13_3","")
	self.trigger_Bxiaoguaib13_2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Bxiaoguaib13_2_3 = self.Stage:CreateTriggerSphere(RecordMonterID.BMonterIDData13[1].Route2[3],2,"BMonterIDData13_3","")
	self.trigger_Bxiaoguaib13_2_3:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
-----------------------------------------------------------------------------------------------------------------------------------------
	----͵Ϯ��

	self.trigger_touxi1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.NJMonterIDData[1].Route1[1],2,"NJMonterRoute2_1","")
	self.trigger_touxi1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_touxi1_2 = self.Stage:CreateTriggerSphere(RecordMonterID.NJMonterIDData[1].Route2[1],2,"NJMonterRoute3_1","")
	self.trigger_touxi1_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_touxi2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.NJMonterIDData[2].Route1[1],2,"NJMonterRoute2_2","")
	self.trigger_touxi2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_touxi2_2 = self.Stage:CreateTriggerSphere(RecordMonterID.NJMonterIDData[2].Route2[1],2,"NJMonterRoute3_2","")
	-- self.trigger_touxi2_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	-- self.trigger_touxi3_1 = self.Stage:CreateTriggerSphere(RecordMonterID.NJMonterIDData[3].Route1[1],2,"NJMonterRoute2_3","")
	-- self.trigger_touxi3_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	-- self.trigger_touxi3_2 = self.Stage:CreateTriggerSphere(RecordMonterID.NJMonterIDData[3].Route2[1],2,"NJMonterRoute3_3","")
	-- self.trigger_touxi3_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	-- self.trigger_touxi4_1 = self.Stage:CreateTriggerSphere(RecordMonterID.NJMonterIDData[4].Route1[1],2,"NJMonterRoute2_4","")
	-- self.trigger_touxi4_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	-- self.trigger_touxi4_2 = self.Stage:CreateTriggerSphere(RecordMonterID.NJMonterIDData[4].Route2[1],2,"NJMonterRoute3_4","")
	-- self.trigger_touxi4_2:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
-----------------------------------------------------------------------------------------------------------------------------------------
----BOSS
	self.trigger_Boss1_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BOSSMonterIDData[1].Route1[1],2,"BOSSMonterRoute2","")
	self.trigger_Boss1_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����	
	self.trigger_Boss2_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BOSSMonterIDData[1].Route1[2],2,"BOSSMonterRoute2","")
	self.trigger_Boss2_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Boss3_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BOSSMonterIDData[1].Route1[3],2,"BOSSMonterRoute2","")
	self.trigger_Boss3_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Boss4_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BOSSMonterIDData[1].Route2[1],2,"BOSSMonterRoute3","")
	self.trigger_Boss4_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����	
	self.trigger_Boss5_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BOSSMonterIDData[1].Route2[2],2,"BOSSMonterRoute3","")
	self.trigger_Boss5_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	self.trigger_Boss6_1 = self.Stage:CreateTriggerSphere(RecordMonterID.BOSSMonterIDData[1].Route2[3],2,"BOSSMonterRoute3","")
	self.trigger_Boss6_1:AddAllowClsid(CLSID.Monster)  --������Ｄ�����
	OldTime = os.time()
	PeriodTimer = self.Stage:GetModCommon():CreatePeriodTimer(0,PeriodTime,0,"HumHP")
-- pwdist.log('=============��ʼ����������============')
end
----���������¼�
function CurrentDungeonScript:EventCreateProcess()
	
end
function CurrentDungeonScript:Bdiyigedian1_1()
end
--------------------------------------------------------��ҽ���--------------------------------------------------------
function CurrentDungeonScript:HumanEnterEvent(human)
-- pwdist.log('=============��ҽ���=============')
	local HuMan= human:cast('Human')
	if HuMan == nil then
		return
	end
	HuMan:SendMsg(msgids.SCDungeonTargetList, msg)
	local humanID = tostring(HuMan:GetID())
	table.insert(RecordHumID,humanID)
	
	local Level = HuMan:GetLevel()
	if(Level == nil) then
		Level = 80
	end
	-----���ø����Ѷȶ�
	-- for i = 1,#MinLevelStage,1 do
		-- if(Level <= MaxLevelStage[i] and Level >= MinLevelStage[i]) then
			-- DungeonDiffcuity = 1
		-- end
	-- end
	-----ˢ��NPC
	if(DungeonState == 0)then
		self:RefreshNPC()
		DungeonState = 1
	end

	if (msgStageHumanInfo.human_count <= MaxHumNum) then
		----����ʱ�䵹��ʱ
		local Time1 = DungeonReadyTime - (os.time() - OldTime) + WaveNumTime
		local Time2 = DungeonReadyTime - (os.time() - OldTime) + AttackTime
		local Time3 = DungeonReadyTime - (os.time() - OldTime) + SpecialTime
		self:CoumtDown(Time1,Time2,Time3,RecordWaveNum)
		----���¸���������
		msgStageHumanInfo.human_count = msgStageHumanInfo.human_count + 1
		self.SModObjs:Broadcast(msgids.SCPVEStageHumanInfo, msgStageHumanInfo)
		self:SortTable()
	end
-- pwdist.log("��ҽ�ȥ�˸��������ݣ���������Ϣ")
	HuMan:SendNotifyMsgTo(DungeonStrInfo[1],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
	HuMan:SendNotifyMsgTo(DungeonStrInfo[2],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
	HuMan:SendNotifyMsgTo(DungeonStrInfo[3],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
	--HuMan:Hint(DungeonInfo[6],5000)
-- pwdist.log("�������������===="..msgStageHumanInfo.human_count.."    �Ѷȶ�==="..DungeonDiffcuity.."			������ҵȼ�=="..Level)
	--HuMan:GetModAura():Create(EnterBuff)-----����Ҽ�BUFF
	
end
-----ȫ�����������ֵ��Ϊ100%
function CurrentDungeonScript:HumHP()
	if(DungeonState >= 2)then
		return
	end
	local stage = GetCurrentStage()
    local humans = stage:GetModObjs():GetHumans()
    for _,v in pairs(humans) do
        v:GetModStatistic():SetPercentHP(1)
    end
-- pwdist.log("����ֵ��Ϊ1")
end
-----ȫ�����������Ƶ������XX��
function CurrentDungeonScript:SenceTalk(Talk)
	local stage = GetCurrentStage()
    local humans = stage:GetModObjs():GetHumans()
    for _,v in pairs(humans) do
        v:SendNotifyMsgTo(Talk,CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
    end

end
--------------------------------------------------------ˢ�µ�һ��С��--------------------------------------------------------
function CurrentDungeonScript:ReadyTime()
-- pwdist.log('===============����ˢ�ֽ׶�===============')
	DungeonState = 2
	if(DungeonState ~= 2)then
		return
	end
	self:Refresh_XiaoGuai()
	if(PeriodTimer ~=0 and PeriodTimer ~=nil)then
		self.SModDungeonScript:CancelTimer(PeriodTimer)
	end
	
-- pwdist.log('===============����ˢ�ֽ׶ν���===============')
end
--------------------------------------------------------ˢ�µ�һ��͵Ϯ��--------------------------------------------------------
function CurrentDungeonScript:AttackTimeTime()
	DungeonState = 2
	if(DungeonState ~= 2)then
		return
	end
	self:Refresh_TouXiGuai()
end
--------------------------------------------------------ˢ�µ�һ�������--------------------------------------------------------
function CurrentDungeonScript:SpecialTimeTime()
	DungeonState = 2
	if(DungeonState ~= 2)then
		return
	end
	self:Refresh_BuffGuai()
end
--------------------------------------------------------׼��ʱ���ڹ���˵��--------------------------------------------------------
function CurrentDungeonScript:guojinghanhua()
	self:NPC_Talk(DungeonNpcID.NpcID[DungeonDiffcuity][2],math.random(13208,13211))
end

--------------------------------------------------------���¸�������ʱ�������--------------------------------------------------------
function CurrentDungeonScript:CoumtDown(Time1,Time2,Time3,Num)
		msgStageTime.times[1].sectime = Time1 
		msgStageTime.times[2].sectime = Time2
		msgStageTime.times[3].sectime = Time3	
		msgStageTime.times[4].sectime = Num
		msgStageTime.times[5].sectime = MaxWaveNum
		self.SModObjs:Broadcast(msgids.SCPVEStageTimeInfo, msgStageTime)
end
--------------------------------------------------------���¸�������������--------------------------------------------------------
function CurrentDungeonScript:SortTable()
-- pwdist.log("===============���¸�������������==============="..DungeonState)
	if(DungeonState == 4 or DungeonState == 1 )then
		return
	end
-- pwdist.log("===============���¸�������������111==============="..DungeonState)
-- MaxSort

	local MaxSort = 5									----���а���ʾ�������
	local stage = GetCurrentStage()
	local humans = stage:GetModObjs():GetHumans()
	local tmpRank = {RankInfo = {}}
	local Index = 0
	for k , v in pairs(humans) do
		local Humid = 0
		Humid = tostring(v:GetID())
		if (RecordHumID[Humid] == nil) then
			RecordHumID[Humid] = 0
		end
		Index = Index + 1
		tmpRank.RankInfo[Index] = 
		{
			Hid = Humid,
			Name = v:GetName(),
			KillCount = RecordHumID[Humid],
		}

	end
	----���򣨣�
	-- for i = 1,#tmpRank.RankInfo,1 do
		-- local Num = 0
		-- for j = i+1,#tmpRank.RankInfo,1 do
			-- if(tmpRank.RankInfo[i].KillCount < tmpRank.RankInfo[j].KillCount)then
				-- Num = tmpRank.RankInfo[i]
				-- tmpRank.RankInfo[i] = tmpRank.RankInfo[j]
				-- tmpRank.RankInfo[j] = Num
			-- end
		-- end	

	-- end

	-----�����������С�����а���ʾ�����ý���������
	if(#tmpRank.RankInfo < MaxSort)then
		MaxSort = #tmpRank.RankInfo
	end
	---�ų�ǰ��������
	-- msgStageHumanInfo.human_infos = {}
	-- for m = 1,MaxSort,1 do	
		-- msgStageHumanInfo.human_infos[m] = { rank = m, hid = tmpRank.RankInfo[m].Hid, name = tmpRank.RankInfo[m].Name, kill_count = tmpRank.RankInfo[m].KillCount, }
	-- end
	-- self.SModObjs:Broadcast(msgids.SCPVEStageHumanInfo, msgStageHumanInfo)	

-----����û�ϰ�������Ϣ������������ 	
	for g , h in pairs(humans) do
		local NoHumid = tostring(h:GetID())
		local Name = h:GetName()
		for p = 1,#tmpRank.RankInfo,1 do
			if(NoHumid == tmpRank.RankInfo[p].Hid)then
				local aHid = h:GetID()
				msgStageHumanInfo.rank = p
				msgStageHumanInfo.kill_count = tmpRank.RankInfo[p].KillCount
				
				for m = 1,#msg.targetlist,1 do
					msg.targetlist[m].count = msgStageHumanInfo.kill_count				
					if(msg.targetlist[m].count >= msg.targetlist[m].maxcount)then
						msg.targetlist[m].count = msg.targetlist[m].maxcount					
					end
-- pwdist.log(" "..Name.."�ĵ�"..m.."�����ַ���===="..msg.targetlist[m].count)
				end

-- pwdist.log("===============���¸����������������==============="..tmpRank.RankInfo[p].KillCount)
				---h:SendMsg(msgids.SCPVEStageHumanInfo, msgStageHumanInfo)
				h:SendMsg(msgids.SCDungeonTargetList, msg)
				---self.SModObjs:Broadcast(msgids.SCPVEStageHumanInfo, msgStageHumanInfo)
				
				if(DungeonState == 3 and aHid ~=nil)then	
					self:FinishReward(aHid,msgStageHumanInfo.kill_count,1)
					local sMsg = {rank = 0, kill_count = msgStageHumanInfo.kill_count, succ = true}
					h:SendMsg(msgids.SCPVEStageFinish, sMsg)
				elseif (DungeonState == -1 and aHid ~=nil)then
					self:FinishReward(aHid,msgStageHumanInfo.kill_count,0)
					local sMsg = {rank = 0, kill_count = msgStageHumanInfo.kill_count, succ = false}
					h:SendMsg(msgids.SCPVEStageFinish, sMsg)
				end
			end
		end	
	end
	if (DungeonState == 3 or DungeonState == -1)then
			local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
			for k , v in pairs(CreatureTab) do
				v:LeaveWorld(0)
			end	
			--self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_END,tostring(0))
			DungeonState = 4
	end
-- pwdist.log("===============���¸����������������===============")
end
--------------------------------------------------------NPC�����¼�--------------------------------------------------------
function CurrentDungeonScript:NPC_Spawn(creature)
	local Mcreature = creature:cast('Creature')
	local MonterTypeID = Mcreature:GetCreatureType()------�ػ���bossѪ����أ��ﵽĳһ��Ѫ��˵��
	if(MonterTypeID == DungeonNpcID.NpcID[DungeonDiffcuity][1])then
		Mcreature:GetModStatistic():ListenHPChanged(1, 75, "HP_Talk1")
		Mcreature:GetModStatistic():ListenHPChanged(1, 50, "HP_Talk2")
		Mcreature:GetModStatistic():ListenHPChanged(1, 25, "HP_Talk3")
		Mcreature:GetModStatistic():ListenHPChanged(1, 10, "HP_Talk4")
	end
end
function CurrentDungeonScript:HP_Talk1()
	self:NPC_Talk(DungeonNpcID.NpcID[DungeonDiffcuity][1],DungeonInfo[14])
	self:SenceTalk(DungeonStrInfo[12])
end
function CurrentDungeonScript:HP_Talk2()
	self:NPC_Talk(DungeonNpcID.NpcID[DungeonDiffcuity][1],DungeonInfo[15])
	self:SenceTalk(DungeonStrInfo[13])
end
function CurrentDungeonScript:HP_Talk3()
	self:NPC_Talk(DungeonNpcID.NpcID[DungeonDiffcuity][1],DungeonInfo[16])
	self:SenceTalk(DungeonStrInfo[14])
end
function CurrentDungeonScript:HP_Talk4()
	self:NPC_Talk(DungeonNpcID.NpcID[DungeonDiffcuity][1],DungeonInfo[17])
	self:SenceTalk(DungeonStrInfo[15])
end
--------------------------------------------------------NPCˢ���¼�--------------------------------------------------------
function CurrentDungeonScript:RefreshNPC()
--pwdist.log("ˢ��NPC==="..DungeonDiffcuity)
	if(DungeonDiffcuity == 0) then
		DungeonDiffcuity = 1
	end
	for i = 1,#DungeonNpcID.NpcID[DungeonDiffcuity],1 do
		for j = 1,#DungeonNpcID.NpcIDOrg[i],1 do
			local BOJ = self.SModCommon:SpawnMonsterAt(DungeonNpcID.NpcIDPos[i][j],DungeonNpcID.NpcIDOrg[i][j],DungeonNpcID.NpcID[DungeonDiffcuity][i])
			table.insert(R_DungeonNpcID,BOJ)
-- pwdist.log("ˢ�µ�"..i.."��NPC��ID     ˢ���˵�"..j.."��")
		end
	end
--pwdist.log("ˢ��NPC����")
end
--------------------------------------------------------��Ҫ�ػ���NPC����--------------------------------------------------------
function CurrentDungeonScript:NPCKilled(creature,killer)
	DungeonState = -1
	self:SortTable()
	--self.MainHuman:SendNotifyMsgToStage(DungeonStrInfo[11],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
	self:NPC_Talk(DungeonNpcID.NpcID[DungeonDiffcuity][1],DungeonInfo[11])
	self:SortTable()
end

--------------------------------------------------------��������¼�--------------------------------------------------------
function CurrentDungeonScript:Monter_Spawn(creature)

end

--------------------------------------------------------С��ˢ���¼�--------------------------------------------------------
function CurrentDungeonScript:Refresh_XiaoGuai()
-- pwdist.log("Refresh_XiaoGuai()")
	if(DungeonState ~= 2)then
		return
	end
	if(DungeonDiffcuity == 0) then
		DungeonDiffcuity = 1
	end
	if(RecordWaveNum < MaxWaveNum)then
		RecordWaveNum = RecordWaveNum + 1			-----����С�ֲ���
	end
-- pwdist.log("����ˢ�²���===================="..RecordWaveNum)	
	if(RecordWaveNum%TouMuWaveNum ~= 0 and RecordWaveNum < MaxWaveNum) then		-----	С��
		-----ˢ��1�Ź����ˢСͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData1,R_BMonterIDData1,-1)    
		-----ˢ��2�Ź����ˢСͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData2,R_BMonterIDData2,-1)   
		-----ˢ��3�Ź����ˢСͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData3,R_BMonterIDData3,-1)   
		-----ˢ��4�Ź����ˢСͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData4,R_BMonterIDData4,-1)   
		-----ˢ��5�Ź����ˢСͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData5,R_BMonterIDData5,-1)   
		-----ˢ��6�Ź����ˢСͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData6,R_BMonterIDData6,-1)   
		-----ˢ��7�Ź����ˢСͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData7,R_BMonterIDData7,-1)   
		-----ˢ��8�Ź����ˢСͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData8,R_BMonterIDData8,-1)   
		-----ˢ��9�Ź����ˢСͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData9,R_BMonterIDData9,-1)   
		-----ˢ��10�Ź����ˢСͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData10,R_BMonterIDData10,-1)   
		-----ˢ��11�Ź����ˢСͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData11,R_BMonterIDData11,-1)   
		-----ˢ��12�Ź����ˢСͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData12,R_BMonterIDData12,-1)   
		-----ˢ��13�Ź����ˢСͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData13,R_BMonterIDData13,-1)   
		
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(DungeonInfo[1]))
		--self.MainHuman:SendNotifyMsgToStage(DungeonStrInfo[5],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
		self:NPC_Talk(DungeonNpcID.NpcID[DungeonDiffcuity][7],DungeonInfo[7])
		self:SenceTalk(DungeonStrInfo[5])
		local WaveNum = RecordWaveNum + 1
		----������һ���ֵ�ˢ��ʱ��
		if(WaveNum%TouMuWaveNum ~= 0) then
			self.GuaiTime1 = self.SModDungeonScript:CreateTimer(WaveNumTime,"Refresh_XiaoGuai")
			if(RecordAttack >= AttackMaxWaveNum)then
				RecordAttack = AttackMaxWaveNum
			end
			local aAttackTime = RecordAttack*AttackTime
			local Time2 = aAttackTime + DungeonReadyTime - (os.time() - OldTime)
			if(RecordSpecial >= SpecialMaxWaveNum)then
				RecordSpecial = SpecialMaxWaveNum
			end			
			local bAttackTime = RecordSpecial *SpecialTime
			local Time3 = bAttackTime + DungeonReadyTime - (os.time() - OldTime)
			
			self:CoumtDown(WaveNumTime,Time2,Time3,RecordWaveNum)	
		---����СͷĿ��ˢ��ʱ��
		else
			self.GuaiTime2 = self.SModDungeonScript:CreateTimer(TouMuTime,"Refresh_XiaoGuai")
			if(RecordAttack >= AttackMaxWaveNum)then
				RecordAttack = AttackMaxWaveNum
			end
			local aAttackTime = RecordAttack*AttackTime
			local Time2 = aAttackTime + DungeonReadyTime - (os.time() - OldTime)
			if(RecordSpecial >= SpecialMaxWaveNum)then
				RecordSpecial = SpecialMaxWaveNum
			end			
			local bAttackTime = RecordSpecial *SpecialTime
			local Time3 = bAttackTime + DungeonReadyTime - (os.time() - OldTime)
			self:CoumtDown(TouMuTime,Time2,Time3,RecordWaveNum)
		end
		
	elseif (RecordWaveNum%TouMuWaveNum == 0 and RecordWaveNum < MaxWaveNum) then	-----ˢ��СͷĿ	
		-----ˢ��1�Ź��ˢ��СͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData1,R_BMonterIDData1,0) 	
		-----ˢ��2�Ź��ˢ��СͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData2,R_BMonterIDData2,0) 
		-----ˢ��3�Ź��ˢ��СͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData3,R_BMonterIDData3,0) 
		-----ˢ��4�Ź��ˢ��СͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData4,R_BMonterIDData4,0) 
		-----ˢ��5�Ź��ˢ��СͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData5,R_BMonterIDData5,0) 
		-----ˢ��6�Ź��ˢ��СͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData6,R_BMonterIDData6,0) 
		-----ˢ��7�Ź��ˢ��СͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData7,R_BMonterIDData7,0) 
		-----ˢ��8�Ź��ˢ��СͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData8,R_BMonterIDData8,0) 
		-----ˢ��9�Ź��ˢ��СͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData9,R_BMonterIDData9,0) 
		-----ˢ��10�Ź��ˢ��СͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData10,R_BMonterIDData10,0) 
		-----ˢ��11�Ź��ˢ��СͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData11,R_BMonterIDData11,0) 
		-----ˢ��12�Ź��ˢ��СͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData12,R_BMonterIDData12,0) 
		-----ˢ��13�Ź��ˢ��СͷĿ
		self:RefreshMonter(RecordMonterID.BMonterIDData13,R_BMonterIDData13,0) 
-- pwdist.log('ˢ��С��+ˢ��СͷĿ')	
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(DungeonInfo[2]))
		--self.MainHuman:SendNotifyMsgToStage(DungeonStrInfo[6],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
		self:NPC_Talk(DungeonNpcID.NpcID[DungeonDiffcuity][7],DungeonInfo[8])	
		self:SenceTalk(DungeonStrInfo[6])
		----������һ���ֵ�ˢ��ʱ��
		self.GuaiTime3 = self.SModDungeonScript:CreateTimer(WaveNumTime,"Refresh_XiaoGuai")
		if(RecordAttack >= AttackMaxWaveNum)then
			RecordAttack = AttackMaxWaveNum
		end
		local aAttackTime = RecordAttack*AttackTime
		local Time2 = aAttackTime + DungeonReadyTime - (os.time() - OldTime)
		if(RecordSpecial >= SpecialMaxWaveNum)then
			RecordSpecial = SpecialMaxWaveNum
		end			
		local bAttackTime = RecordSpecial *SpecialTime
		local Time3 = bAttackTime + DungeonReadyTime - (os.time() - OldTime)
		self:CoumtDown(WaveNumTime,Time2,Time3,RecordWaveNum)
	elseif (RecordWaveNum%TouMuWaveNum == 0 and RecordWaveNum == MaxWaveNum) then	-----ˢ������BOSS
		-- for i = 1,#RecordMonterID.MonterIDOrg[5],1 do
			-- local BOJ = self.SModCommon:SpawnMonsterAt(RecordMonterID.MonterIDPos[5][i],RecordMonterID.MonterIDOrg[5][i],RecordMonterID.MonterID[DungeonDiffcuity][5])
		-- end		
		local BOJ = self.SModCommon:SpawnMonsterAt(RecordMonterID.BOSSMonterIDData[1].Pos,RecordMonterID.BOSSMonterIDData[1].PointOrg,RecordMonterID.MonterID[DungeonDiffcuity][9])
		local creature = BOJ:cast('Creature')
		if(creature ~= nil)then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BOSSMonterIDData[1].Route1[math.random(1,#RecordMonterID.BOSSMonterIDData[1].Route1)],"",0)
			table.insert(R_BOSSMonterIDData,creature)
		end

		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(DungeonInfo[5]))
		--self.MainHuman:SendNotifyMsgToStage(DungeonStrInfo[9],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
		self:SenceTalk(DungeonStrInfo[9])
		self:NPC_Talk(DungeonNpcID.NpcID[DungeonDiffcuity][1],DungeonInfo[9])
		self:CoumtDown(0,0,0,MaxWaveNum)
	end	

-- pwdist.log('=============�´�ˢ�µ�'..RecordWaveNum.."����")
end
------ˢ��С�ֵ�ͨ�ú���
function CurrentDungeonScript:RefreshMonter(MONTERNUM,DATA,IDXNUM)----(���ֹֺ���������Ҫ��¼����ı���,�Ƿ�Ӽ�1)
	for i = 1,#MONTERNUM+IDXNUM,1 do
		for j = 1,MONTERNUM[i].Num,1 do
			local BOJ = self.SModCommon:SpawnMonsterAt(MONTERNUM[i].Pos,MONTERNUM[i].PointOrg,MONTERNUM[i].ID[1])
			local creature = BOJ:cast('Creature')
			if(creature ~= nil)then
				local ret = creature:GetModMotionMaster():NavigatePositionEx(MONTERNUM[i].Route1[math.random(1,#MONTERNUM[i].Route1)],"",0)
				table.insert(DATA,creature)
			end
		end
	end

end
--------------------------------------------------------͵Ϯ��ˢ���¼�--------------------------------------------------------
function CurrentDungeonScript:Refresh_TouXiGuai()
	if(DungeonState ~= 2)then
		return
	end
	if(DungeonDiffcuity == 0) then
		DungeonDiffcuity = 1
	end	
	if(RecordAttack <= AttackMaxWaveNum)then
		-- for i = 1,#RecordMonterID.MonterIDOrg[3],1 do
			-- local BOJ = self.SModCommon:SpawnMonsterAt(RecordMonterID.MonterIDPos[3][i],RecordMonterID.MonterIDOrg[3][i],RecordMonterID.MonterID[DungeonDiffcuity][3])
		-- end	
		for i = 1,#RecordMonterID.NJMonterIDData,1 do
			local BOJ = self.SModCommon:SpawnMonsterAt(RecordMonterID.NJMonterIDData[i].Pos,RecordMonterID.NJMonterIDData[i].PointOrg,RecordMonterID.MonterID[DungeonDiffcuity][6])
			local creature = BOJ:cast('Creature')
			if(creature ~=nil)then
				creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.NJMonterIDData[i].Route1[1],"",0)
				table.insert(R_NJMonterIDData,creature)
			end	
		end
		self.MaxTime4 = self.SModDungeonScript:CreateTimer(AttackTime,"Refresh_TouXiGuai")			---���ٷ��Ӻ���ˢ��
		
		local a = 0
		local zTime,xTime = 0,0
			if(RecordWaveNum >=10)then
				a = RecordWaveNum/TouMuWaveNum
				zTime,xTime = math.modf(a)
			end
		local VTime = zTime*(TouMuTime-WaveNumTime)+RecordWaveNum*WaveNumTime + DungeonReadyTime  -----СͷĿ����ʱ��+С�ֲ���ʱ��+�ȴ�ʱ��
		local Time1= VTime - (os.time() - OldTime)	-----СͷĿ����ʱ��+С�ֲ���ʱ��+�ȴ�ʱ��-������ʼʱ��
		local aRecordSpecial = AttackMaxWaveNum
		if(RecordAttack < AttackMaxWaveNum) then
			aRecordAttack = RecordAttack + 1
		end		
		local Time2 = aRecordAttack*AttackTime + DungeonReadyTime - (os.time() - OldTime)
		local Time3 = RecordSpecial*SpecialTime + DungeonReadyTime - (os.time() - OldTime)
		self:CoumtDown(Time1,Time2,Time3,RecordWaveNum)
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(DungeonInfo[3]))
		--self.MainHuman:SendNotifyMsgToStage(DungeonStrInfo[7],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
		self:NPC_Talk(DungeonNpcID.NpcID[DungeonDiffcuity][7],DungeonInfo[12])
		self:SenceTalk(DungeonStrInfo[7])
	end	

	RecordAttack = RecordAttack + 1					-----����͵Ϯ�ֲ���
-- pwdist.log('=============����͵Ϯ��ˢ�½�������һ��ˢ�µ�'..RecordAttack.."��")
end
--------------------------------------------------------�����ˢ���¼�--------------------------------------------------------
function CurrentDungeonScript:Refresh_BuffGuai()
	if(DungeonState ~= 2)then
		return
	end	
	if(DungeonDiffcuity == 0) then
		DungeonDiffcuity = 1
	end	
	if(RecordSpecial <= SpecialMaxWaveNum)then
		if(#R_TCMonterIDData<=0)then
			for i = 1,#RecordMonterID.TCMonterIDData,1 do
				local BOJ = self.SModCommon:SpawnMonsterAt(RecordMonterID.TCMonterIDData[i].Pos,RecordMonterID.TCMonterIDData[i].PointOrg,RecordMonterID.TCMonterIDData[i].ID)			
				table.insert(R_TCMonterIDData,BOJ)	
			end	
		else
			for u = 1,#R_TCMonterIDData,1 do
				if(R_TCMonterIDData[u] ~=nil)then
					R_TCMonterIDData[u]:LeaveWorld(0)
				end				
			end
			R_TCMonterIDData = {}	
			
			for i = 1,#RecordMonterID.TCMonterIDData,1 do
				local BOJ = self.SModCommon:SpawnMonsterAt(RecordMonterID.TCMonterIDData[i].Pos,RecordMonterID.TCMonterIDData[i].PointOrg,RecordMonterID.TCMonterIDData[i].ID)
				table.insert(R_TCMonterIDData,BOJ)
			end				
		end
		-- for i = 1,#RecordMonterID.TCMonterIDData,1 do
			-- local BOJ = self.SModCommon:SpawnMonsterAt(RecordMonterID.TCMonterIDData[i].Pos,RecordMonterID.TCMonterIDData[i].PointOrg,RecordMonterID.TCMonterIDData[i].ID)
			-- if(#R_TCMonterIDData<=0)then			
				-- table.insert(R_TCMonterIDData,BOJ)
			-- else
				-- for u = 1,#R_TCMonterIDData,1 do
					-- R_TCMonterIDData[u]:LeaveWorld(0)
				-- end
				-- R_TCMonterIDData = {}
			-- end
			
		-- end	
		self.MaxTime5 = self.SModDungeonScript:CreateTimer(SpecialTime,"Refresh_BuffGuai")		---���ٷ��Ӻ���ˢ��
		
		local a = 0
		local zTime,xTime = 0,0
			if(RecordWaveNum >=10)then
				a = RecordWaveNum/TouMuWaveNum
				zTime,xTime = math.modf(a)
			end
		local VTime = zTime*(TouMuTime-WaveNumTime)+RecordWaveNum*WaveNumTime + DungeonReadyTime  -----СͷĿ����ʱ��+С�ֲ���ʱ��+�ȴ�ʱ��
		local Time1= VTime - (os.time() - OldTime)	-----СͷĿ����ʱ��+С�ֲ���ʱ��+�ȴ�ʱ��-������ʼʱ��
		local Time2 = RecordAttack*AttackTime + DungeonReadyTime - (os.time() - OldTime)
		local aRecordSpecial = SpecialMaxWaveNum
		if(RecordSpecial < SpecialMaxWaveNum) then
			aRecordSpecial = RecordSpecial+1
		end
		local Time3 = aRecordSpecial*SpecialTime + DungeonReadyTime - (os.time() - OldTime)
		self:CoumtDown(Time1,Time2,Time3,RecordWaveNum)
		
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(DungeonInfo[4]))
		--self.MainHuman:SendNotifyMsgToStage(DungeonStrInfo[8],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
		self:NPC_Talk(DungeonNpcID.NpcID[DungeonDiffcuity][7],DungeonInfo[13])
		self:SenceTalk(DungeonStrInfo[8])
	end
	RecordSpecial = RecordSpecial + 1		-----��������ֲ���
-- pwdist.log('=============���������ˢ�½�������һ��ˢ�µ�'..RecordSpecial.."��")
end


--------------------------------------------------------���������¼�--------------------------------------------------------
function CurrentDungeonScript:MonterKilled(creatureM,killer)
-- pwdist.log('=============��������=============')
	local KillerID = tostring(killer:GetID())
	local creature = creatureM:cast('Creature')
	local MonterTypeID = creature:GetCreatureType()

	if(MonterTypeID ~=nil)then
		if(MonterTypeID ~= RecordMonterID.MonterID[DungeonDiffcuity][9])then
			local IsHum = killer:IsKindOf(CLSID.Human)	------����BOSS�Ҳ��Ǳ���һ�ɱ�����Ļ����Ͳ�������һ���
			if(IsHum == false)then
				return
			end			
		end
		if(MonterTypeID == RecordMonterID.MonterID[DungeonDiffcuity][7] or MonterTypeID == RecordMonterID.MonterID[DungeonDiffcuity][8])then
			local rand = math.random(1,#MonterBuff)
--killer:GetModAura():Create(MonterBuff[rand])���θĻ���
		end
		if(MonterTypeID == RecordMonterID.MonterID[DungeonDiffcuity][9])then
			---self.MainHuman:SendNotifyMsgToStage(DungeonStrInfo[10],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
			self:NPC_Talk(DungeonNpcID.NpcID[DungeonDiffcuity][1],DungeonInfo[10])
			self:SenceTalk(DungeonStrInfo[10])
			DungeonState = 3
-- pwdist.log("==========================BOSS��������������==========================")		
		end
	end
	local stage = GetCurrentStage()
	local humans = stage:GetModObjs():GetHumans()
	local Humid = 0
	for k , v in pairs(humans) do
		Humid = tostring(v:GetID())
		if(RecordHumID[Humid] == nil)then
			RecordHumID[Humid] = 0
		end
		if (Humid == KillerID) then
			for i = 1,#RecordMonterID.MonterID[DungeonDiffcuity],1 do
				if(MonterTypeID == RecordMonterID.MonterID[DungeonDiffcuity][i])then
					RecordHumID[KillerID] = RecordHumID[KillerID] + IntegralID[i]
-- pwdist.log('=============���������ӵķ���============='..RecordHumID[KillerID])	
				end				
			end

			
		end
	end
	self:SortTable()
-- pwdist.log('=============������������=============')	
end

function CurrentDungeonScript:Cleanup()  
	---pwdist.log('=============pve Cleanup')
end


function CurrentDungeonScript:EventDestroyProcess()
  --- pwdist.log('=============pve EventDestroyProcess')
end
-----������	1ʤ����0ʧ��	hid = GetID()
function CurrentDungeonScript:FinishReward(hid, rank, result)
	if nil == self.SModLogicMDPVE then
		return
	end

	local teamid = self.SModLogicMDPVE:ilua_GetTeamId()
	local teammgrid = self.SModLogicMDPVE:ilua_GetTeamMgrId()
	
	pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.pve, teammgrid)
    pwdist.call(nil, pwngs_rpcnames.ctrlsrv.TeamMgr.TeamReward, teamid, hid, rank, result)
end
--------------------------------------------------------����뿪--------------------------------------------------------
function CurrentDungeonScript:HumanLeaveEvent(human)
	if (msgStageHumanInfo.human_count > 0) then
		msgStageHumanInfo.human_count = msgStageHumanInfo.human_count - 1
		self.SModObjs:Broadcast(msgids.SCPVEStageHumanInfo, msgStageHumanInfo)	
		self:SortTable()
	end

	----pwdist.log('����뿪����ʣ��������===='..msgStageHumanInfo.human_count)
end

--------------------------------------------------------��������--------------------------------------------------------
function CurrentDungeonScript:EndTime()  
----���������T������
end

-----1����2·����
function CurrentDungeonScript:BMonterIDData1_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData1) do
		local creature = R_BMonterIDData1[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData1[1].Route2[math.random(1,#RecordMonterID.BMonterIDData1[1].Route2)],"",0)
		end
	end
end
-----1����3·����
function CurrentDungeonScript:BMonterIDData1_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData1) do
		local creature = R_BMonterIDData1[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData1[1].Route3[math.random(1,#RecordMonterID.BMonterIDData1[1].Route3)],"",0)
		end
	end
end
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----2����2·����
function CurrentDungeonScript:BMonterIDData2_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData2) do
		local creature = R_BMonterIDData2[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData2[1].Route2[math.random(1,#RecordMonterID.BMonterIDData2[1].Route2)],"",0)
		end
	end
end
-----2����3·����
function CurrentDungeonScript:BMonterIDData2_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData2) do
		local creature = R_BMonterIDData2[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData2[1].Route3[math.random(1,#RecordMonterID.BMonterIDData2[1].Route3)],"",0)
		end
	end
end
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----3����2·����
function CurrentDungeonScript:BMonterIDData3_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData3) do
		local creature = R_BMonterIDData3[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData3[1].Route2[math.random(1,#RecordMonterID.BMonterIDData3[1].Route2)],"",0)
		end
	end
end
-----3����3·����
function CurrentDungeonScript:BMonterIDData3_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData3) do
		local creature = R_BMonterIDData3[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData3[1].Route3[math.random(1,#RecordMonterID.BMonterIDData3[1].Route3)],"",0)
		end
	end
end
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----4����2·����
function CurrentDungeonScript:BMonterIDData4_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData4) do
		local creature = R_BMonterIDData4[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData4[1].Route2[math.random(1,#RecordMonterID.BMonterIDData4[1].Route2)],"",0)
		end
	end
end
-----4����3·����
function CurrentDungeonScript:BMonterIDData4_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData4) do
		local creature = R_BMonterIDData4[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData4[1].Route3[math.random(1,#RecordMonterID.BMonterIDData4[1].Route3)],"",0)
		end
	end
end
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----5����2·����
function CurrentDungeonScript:BMonterIDData5_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData5) do
		local creature = R_BMonterIDData5[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData5[1].Route2[math.random(1,#RecordMonterID.BMonterIDData5[1].Route2)],"",0)
		end
	end
end
-----5����3·����
function CurrentDungeonScript:BMonterIDData5_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData5) do
		local creature = R_BMonterIDData5[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData5[1].Route3[math.random(1,#RecordMonterID.BMonterIDData5[1].Route3)],"",0)
		end
	end
end
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----6����2·����
function CurrentDungeonScript:BMonterIDData6_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData6) do
		local creature = R_BMonterIDData6[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData6[1].Route2[math.random(1,#RecordMonterID.BMonterIDData6[1].Route2)],"",0)
		end
	end
end
-----6����3·����
function CurrentDungeonScript:BMonterIDData6_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData6) do
		local creature = R_BMonterIDData6[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData6[1].Route3[math.random(1,#RecordMonterID.BMonterIDData6[1].Route3)],"",0)
		end
	end
end
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----7����2·����
function CurrentDungeonScript:BMonterIDData7_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData7) do
		local creature = R_BMonterIDData7[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData7[1].Route2[math.random(1,#RecordMonterID.BMonterIDData7[1].Route2)],"",0)
		end
	end
end
-----7����3·����
function CurrentDungeonScript:BMonterIDData7_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData7) do
		local creature = R_BMonterIDData7[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData7[1].Route3[math.random(1,#RecordMonterID.BMonterIDData7[1].Route3)],"",0)
		end
	end
end
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----8����2·����
function CurrentDungeonScript:BMonterIDData8_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData8) do
		local creature = R_BMonterIDData8[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData8[1].Route2[math.random(1,#RecordMonterID.BMonterIDData8[1].Route2)],"",0)
		end
	end
end
-----8����3·����
function CurrentDungeonScript:BMonterIDData8_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData8) do
		local creature = R_BMonterIDData8[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData8[1].Route3[math.random(1,#RecordMonterID.BMonterIDData8[1].Route3)],"",0)
		end
	end
end
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----9����2·����
function CurrentDungeonScript:BMonterIDData9_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData9) do
		local creature = R_BMonterIDData9[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData9[1].Route2[math.random(1,#RecordMonterID.BMonterIDData9[1].Route2)],"",0)
		end
	end
end
-----9����3·����
function CurrentDungeonScript:BMonterIDData9_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData9) do
		local creature = R_BMonterIDData9[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData9[1].Route3[math.random(1,#RecordMonterID.BMonterIDData9[1].Route3)],"",0)
		end
	end
end

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----10����2·����
function CurrentDungeonScript:BMonterIDData10_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData10) do
		local creature = R_BMonterIDData10[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData10[1].Route2[math.random(1,#RecordMonterID.BMonterIDData10[1].Route2)],"",0)
		end
	end
end
-----10����3·����
function CurrentDungeonScript:BMonterIDData10_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData10) do
		local creature = R_BMonterIDData10[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData10[1].Route3[math.random(1,#RecordMonterID.BMonterIDData10[1].Route3)],"",0)
		end
	end
end
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----11����2·����
function CurrentDungeonScript:BMonterIDData11_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData11) do
		local creature = R_BMonterIDData11[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData11[1].Route2[math.random(1,#RecordMonterID.BMonterIDData11[1].Route2)],"",0)
		end
	end
end
-----11����3·����
function CurrentDungeonScript:BMonterIDData11_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData11) do
		local creature = R_BMonterIDData11[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData11[1].Route3[math.random(1,#RecordMonterID.BMonterIDData11[1].Route3)],"",0)
		end
	end
end
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----12����2·����
function CurrentDungeonScript:BMonterIDData12_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData12) do
		local creature = R_BMonterIDData12[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData12[1].Route2[math.random(1,#RecordMonterID.BMonterIDData12[1].Route2)],"",0)
		end
	end
end
-----12����3·����
function CurrentDungeonScript:BMonterIDData12_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData12) do
		local creature = R_BMonterIDData12[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData12[1].Route3[math.random(1,#RecordMonterID.BMonterIDData12[1].Route3)],"",0)
		end
	end
end
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----13����2·����
function CurrentDungeonScript:BMonterIDData13_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData13) do
		local creature = R_BMonterIDData13[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData13[1].Route2[math.random(1,#RecordMonterID.BMonterIDData13[1].Route2)],"",0)
		end
	end
end
-----13����3·����
function CurrentDungeonScript:BMonterIDData13_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BMonterIDData13) do
		local creature = R_BMonterIDData13[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BMonterIDData13[1].Route3[math.random(1,#RecordMonterID.BMonterIDData13[1].Route3)],"",0)
		end
	end
end


-----�ڼ����·����
function CurrentDungeonScript:NJMonterRoute2_1(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_NJMonterIDData) do
		local creature = R_NJMonterIDData[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.NJMonterIDData[1].Route2[1],"",0)
		end
	end	
end	
-----�ڼ����·����
function CurrentDungeonScript:NJMonterRoute3_1(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_NJMonterIDData) do
		local creature = R_NJMonterIDData[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.NJMonterIDData[1].Route3[1],"",0)
		end
	end	
end	
-----�ڼ����·����
function CurrentDungeonScript:NJMonterRoute2_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_NJMonterIDData) do
		local creature = R_NJMonterIDData[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.NJMonterIDData[2].Route2[1],"",0)
		end
	end	
end	
-----�ڼ����·����
function CurrentDungeonScript:NJMonterRoute3_2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_NJMonterIDData) do
		local creature = R_NJMonterIDData[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.NJMonterIDData[2].Route3[1],"",0)
		end
	end	
end	
-----�ڼ����·����
function CurrentDungeonScript:NJMonterRoute2_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_NJMonterIDData) do
		local creature = R_NJMonterIDData[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.NJMonterIDData[3].Route2[1],"",0)
		end
	end	
end	
-----�ڼ����·����
function CurrentDungeonScript:NJMonterRoute3_3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_NJMonterIDData) do
		local creature = R_NJMonterIDData[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.NJMonterIDData[3].Route3[1],"",0)
		end
	end	
end	
-----�ڼ����·����
function CurrentDungeonScript:NJMonterRoute2_4(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_NJMonterIDData) do
		local creature = R_NJMonterIDData[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.NJMonterIDData[4].Route2[1],"",0)
		end
	end	
end	
-----�ڼ����·����
function CurrentDungeonScript:NJMonterRoute3_4(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_NJMonterIDData) do
		local creature = R_NJMonterIDData[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.NJMonterIDData[4].Route3[1],"",0)
		end
	end	
end	
-----BOSS����·����
function CurrentDungeonScript:BOSSMonterRoute2(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BOSSMonterIDData) do
		local creature = R_BOSSMonterIDData[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId ) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BOSSMonterIDData[1].Route2[math.random(1,#RecordMonterID.BOSSMonterIDData[1].Route2)],"",0)
		end
	end	  
end	
-----BOSS����·����
function CurrentDungeonScript:BOSSMonterRoute3(Trigger,Unit)
	local Mcreature = Unit:cast('Creature')
	local MId = 0
	if(Mcreature ~=nil) then
		MId = tostring(Mcreature:GetID())
	end
	for i= 1, table.getn(R_BOSSMonterIDData) do
		local creature = R_BOSSMonterIDData[i]:cast('Creature')
		local Id = 1
		if(creature ~= nil) then
			Id = tostring(creature:GetID())
		end
		if(Id == MId) then
			creature:GetModMotionMaster():NavigatePositionEx(RecordMonterID.BOSSMonterIDData[1].Route3[math.random(1,#RecordMonterID.BOSSMonterIDData[1].Route3)],"",0)
		end
	end	  
end	

-----NPCͨ�ú�������
function CurrentDungeonScript:NPC_Talk(Npc_id,Str_ID)
	for i = 1,#R_DungeonNpcID,1 do
		local creature = R_DungeonNpcID[i]:cast('Creature')
		if(creature ~= nil)then
			local MonterTypeID = creature:GetCreatureType()
			if(MonterTypeID ~= nil and MonterTypeID == Npc_id)then
				creature:Talk(Str_ID)
			end
		end
	end
end