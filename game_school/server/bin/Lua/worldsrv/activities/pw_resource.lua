--Ĭ�ϳ�ʼ�����ã�����Լ��
----------------------------------------------------------------------
CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .


----------------------------------------------------------------------
--���ݳ�ʼ��
----------------------------------------------------------------------
local AutoBattle                = true                                                                            --�Զ�ս����ʼ����Ϊ����
local SceneIDSM                 = 3003                                                                               --����,��������ID
local SceneIDIE                 = 3004                                                                               --ǿ��ʯ,���������ID

local PlayerEnterPos 		    = {184.1,53.1,155.8}                                                               --��ҳ�����λ��
local PlayerEnterOra 		    = {0.3,0.0,-0.9}	                                                              --��ҳ����㳯��

local StonePos 		            = {185.9683,53.62904,162.3802}	                                                  --ʯ�����������
local StoneOra		            = {1.0,0.0,0.0}     	                                                          --ʯ����

local PrizeR 				    = 5                                                                               --������λ�õ�뾶

local FinishSTR1                = 195023                                                                         --����1�ɹ���ɱstr
local FinishSTR3                = 195032                                                                         --����2�ɹ���ɱstr
local FinishSTR2                = 195022                                                                         --����1ʱ�䵽δ�ɹ���ɱstr
local FinishSTR4                = 195031                                                                         --����2ʱ�䵽δ�ɹ���ɱstr
local sliver600016              = 1000
local sliver600017              = 10000
local shuli600001               = 10000
local shuli600002               = 100000

CurrentDungeonScript.Resources = {
[0] = {                                                                                                           --����,��������
	    [1] = {                                                                                                   --��ҵȼ���:20
		        ["Monster"]  = {20007,1},                                                                         --����ID������
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                               --��ͨ������
				["RankS"]    = {80,50},                                                                           --���⽱����
				["RewardR1"] = {600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2},                                                                         
				["RewardS1"] = {600002,1,600002,3},                                                               --���⽱������
				["RewardR2"] = {600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2},                                                                         
				["RewardS2"] = {600017,1,600017,3},                                                               --���⽱������
				["LvRange"]  = {0,30},                                                                            --��Ч�ȼ���
		 },
		[2] = {                                                                                                   --��ҵȼ���:30                                                                         
				["Monster"]  = {20008,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                               --��ͨ������
				["RankS"]    = {80,50},                                                                           --���⽱����
				["RewardR1"] = {600001,2,600001,3,600001,2,600001,2,600001,3,600001,2,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,2,600001,3,600001,2},                                                                         
				["RewardS1"] = {600002,2,600002,4},                                                               --���⽱������
				["RewardR2"] = {600016,2,600016,3,600016,2,600016,2,600016,3,600016,2,600016,3,600016,2,600016,2,600016,3,600016,2,600016,3,600016,2,600016,3,600016,2,600016,3,600016,2,600016,3,600016,2,600016,3,600016,2,600016,2,600016,3,600016,2,600016,2,600016,3,600016,2,600016,3,600016,2,600016,2},                                                                         
				["RewardS2"] = {600017,2,600017,4}, 				
				["LvRange"]  = {30,40},
		},
		[3] = {                                                                                                   --��ҵȼ���:40                                                                         
				["Monster"]  = {20009,1},                                                                   
                ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --��ͨ������
				["RankS"]    = {80,50},                                                                           --���⽱����
				["RewardR1"] = {600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3},                                                                         
				["RewardS1"] = {600002,2,600002,4},                                                               --���⽱������
				["RewardR2"] = {600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3},                                                                         
				["RewardS2"] = {600017,2,600017,4},
				["LvRange"]  = {40,50},
		},
		[4] = {                                                                                                   --��ҵȼ���:50                                                                         
				["Monster"]  = {20010,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --��ͨ������
				["RankS"]    = {80,50},                                                                           --���⽱����
				["RewardR1"] = {600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4},                                                                         
				["RewardS1"] = {600002,2,600002,6},                                                               --���⽱������
				["RewardR2"] = {600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4},                                                                         
				["RewardS2"] = {600017,2,600017,6},
				["LvRange"]  = {50,60},
		},
		[5] = {                                                                                                   --��ҵȼ���:60                                                                         
				["Monster"]  = {20011,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --��ͨ������
				["RankS"]    = {80,50},                                                                           --���⽱����
				["RewardR1"] = {600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4},                                                                         
				["RewardS1"] = {600002,2,600002,6},                                                               --���⽱������
				["RewardR2"] = {600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4},                                                                         
				["RewardS2"] = {600017,2,600017,6},
				["LvRange"]  = {60,70},
		},
		[6] = {                                                                                                   --��ҵȼ���:70                                                                         
				["Monster"]  = {20012,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --��ͨ������
				["RankS"]    = {80,50},                                                                           --���⽱����
				["RewardR1"] = {600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5},                                                                         
				["RewardS1"] = {600002,2,600002,7},                                                               --���⽱������
				["RewardR2"] = {600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5},                                                                         
				["RewardS2"] = {600017,2,600017,7},
				["LvRange"]  = {70,81},
		},
    },
[1] = {                                                                                                           --�������ǿ��ʯ����
		[1] = {                                                                                                   --��ҵȼ���:20
		        ["Monster"]  = {20001,1},                                                                         --����ID������
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --��ͨ������
				["RankS"]    = {80,50},                                                                           --���⽱����
				["RewardR1"] = {400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3},                                                                         
				["RewardS1"] = {400014,6,400014,8},                                                               --���⽱������
				["RewardR2"] = {410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0},                                                                         
				["RewardS2"] = {410103,0,410103,1},                                                               --���⽱������
				["LvRange"]  = {0,30},                                                                            --��Ч�ȼ���
		 },
		[2] = {                                                                                                   --��ҵȼ���:30                                                                         
				["Monster"]  = {20002,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --��ͨ������
				["RankS"]    = {80,50},                                                                           --���⽱����
				["RewardR1"] = {400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3},                                                                         
				["RewardS1"] = {400014,8,400014,12},                                                               --���⽱������
				["RewardR2"] = {410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0},                                                                         
				["RewardS2"] = {410103,0,410103,1}, 				
				["LvRange"]  = {30,40},
		},
		[3] = {                                                                                                   --��ҵȼ���:40                                                                         
				["Monster"]  = {20003,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --��ͨ������
				["RankS"]    = {80,50},                                                                           --���⽱����
				["RewardR1"] = {400014,3,400014,4,400014,3,400014,4,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,4,400014,4,400014,3,400014,3,400014,3,400014,3},                                                                         
				["RewardS1"] = {400014,10,400014,16},                                                               --���⽱������
				["RewardR2"] = {410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0},                                                                         
				["RewardS2"] = {410103,1,410103,1},
				["LvRange"]  = {40,50},
		},
		[4] = {                                                                                                   --��ҵȼ���:50                                                                         
				["Monster"]  = {20004,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --��ͨ������
				["RankS"]    = {80,50},                                                                           --���⽱����
				["RewardR1"] = {400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4},                                                                         
				["RewardS1"] = {400014,12,400014,18},                                                               --���⽱������
				["RewardR2"] = {410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0},                                                                         
				["RewardS2"] = {410103,1,410103,1},
				["LvRange"]  = {50,60},
		},
		[5] = {                                                                                                   --��ҵȼ���:60                                                                         
				["Monster"]  = {20005,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --��ͨ������
				["RankS"]    = {80,50},                                                                           --���⽱����
				["RewardR1"] = {400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,6,400014,4,400014,4,400014,4,400014,6,400014,4,400014,4,400014,4,400014,4,400014,4,400014,6},                                                                         
				["RewardS1"] = {400014,14,400014,20},                                                               --���⽱������
				["RewardR2"] = {410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0},                                                                         
				["RewardS2"] = {410103,1,410103,2},
				["LvRange"]  = {60,70},
		},
		[6] = {                                                                                                   --��ҵȼ���:70                                                                         
				["Monster"]  = {20006,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --��ͨ������
				["RankS"]    = {80,50},                                                                           --���⽱����
				["RewardR1"] = {400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,5,400014,5,400014,6,400014,5,400014,6,400014,5,400014,6,400014,5},                                                                         
				["RewardS1"] = {400014,16,400014,24},                                                               --���⽱������
				["RewardR2"] = {410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0},                                                                         
				["RewardS2"] = {410103,1,410103,3},
				["LvRange"]  = {70,81},
		},
    },
}
-----------------------------------------------------------
--��������
-----------------------------------------------------------
CurrentDungeonScript.CurrLv = 1			--����
CurrentDungeonScript.SceneID = -1	    --����ID
CurrentDungeonScript.CurrItem1 = 0		--��ǰ������ƷID1
CurrentDungeonScript.CurrItem2 = 0		--��ǰ������ƷID2
CurrentDungeonScript.CurrItem3 = -1		--��ǰ������ƷID2
CurrentDungeonScript.CurrNum1 = 0	    --��ǰ����1����
CurrentDungeonScript.CurrNum2 = 0	    --��ǰ����2����
CurrentDungeonScript.CurrNum3 = 0	    --��ǰ����2����
CurrentDungeonScript.stone = nil		--��������
CurrentDungeonScript.CurrLevelFightActive = false --���ڷ�ֹ���翨ʱ���ˢ��
CurrentDungeonScript.Time = 300         --����ʱ��5����

-----------------------------------------------------------
--����������ر�
-----------------------------------------------------------
function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()
	self.SModCommon = self.Stage:GetModCommon()
	
	SetEventHandler(StageEvents.HumanEnter,			"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,			"HumanLeaveEvent")
	SetEventHandler(StageEvents.CreatureKilled,		"CreatureKilled")
	for k ,v in pairs(self.Resources) do
		for i,j in pairs(v) do		
			SetEventHandler(StageEvents.CreatureSpawn,		"CreatureSpawn",{type = j.Monster[1]})
		end
	end
end

function CurrentDungeonScript:Cleanup()
end


-----------------------------------------------------------
--��ҽ������뿪,�����븴��
-----------------------------------------------------------
function CurrentDungeonScript:HumanEnterEvent(human)
    self.SceneID = self:StageChoose()
	self.CurrLv  = self:LevelChoose()
	if self.SceneID == 0 then
	     self.CurrItem1 = 810097
	     self.CurrItem2 = 100014
	else
	     self.CurrItem1 = self.Resources[self.SceneID][self.CurrLv]["RewardR1"][1]
	     self.CurrItem2 = self.Resources[self.SceneID][self.CurrLv]["RewardR2"][1]
	     self.CurrItem3 = self.Resources[self.SceneID][self.CurrLv]["RewardS2"][1]
	end
	human:GetModMotionMaster():ChangePosition(PlayerEnterPos)
	human:GetModMotionMaster():ChangeOrientation(PlayerEnterOra)
	self:SpawnStone()
	self.Stage:GetModDetour():EnableMotionBlock(1,true)
	self.Stage:GetModDetour():EnableMotionBlock(0,true)
end

function CurrentDungeonScript:StageChoose()                                                                       --���ݳ���ID�ж�����                    
    if toint32(self.Stage:GetBaseMapID()) == SceneIDSM then
	    return 0
	end
    if toint32(self.Stage:GetBaseMapID()) == SceneIDIE then
		return 1
	end	
end

function CurrentDungeonScript:LevelChoose()                                                                       --���ݵȼ��ж��������                    
    local Lv = self.MainHuman:GetLevel()
	for i = 1,8,1 do
	    if Lv >= self.Resources[self.SceneID][i]["LvRange"][1] and Lv < self.Resources[self.SceneID][i]["LvRange"][2] then
		   return i
		end
	end
end

function CurrentDungeonScript:SpawnStone()                                                                        --��ʾ��������ʼ�Զ�ս��
	if self.CurrLevelFightActive == true then	                                                                  --����Զ�ս��        
	    --self.MainHuman:OpenAutoCombat()
	end
	self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(5))                                      --5���ʼս��
	self.SModCommon:CreateTimer(5, "OnFightBegin")
end

function CurrentDungeonScript:OnFightBegin()	                                                                  --����XXʱ���ʼˢ��
                                                                                                                   --��ֹ���翨��������ˢ��
	if self.CurrLevelFightActive then
		pwdist.log(self.MainHuman:GetName() .. ',Fight already begin')
		return
	end
	self.CurrLevelFightActive = true
	
	self.SModDungeonScript:PlotStart()	
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(41597))			                          --������ʾ����ʼ��ս
	self.Stage:GetModObjs():SuspendCreaturesAI()
	self.stone = self.Stage:GetModCommon():SpawnMonsterAt(StonePos, StoneOra, self.Resources[self.SceneID][self.CurrLv]["Monster"][1])
	self.Stage:GetModObjs():ResumeCreaturesAI()
	self.SModDungeonScript:PlotClean()
	--self.MainHuman:GetModBabel():OnWaveStart(self.CurrLv)	                                                      --֪ͨ������ս����
	
	local msg = { time_count = self.Time,resources1_id = self.CurrItem1,resources1_count = self.CurrNum1,resources2_id = self.CurrItem2,resources2_count = self.CurrNum2,resources3_id = self.CurrItem3,resources3_count = self.CurrNum3}
	self.MainHuman:SendMsg(msgids.SCResourcesUpdate,msg)
    self.SModCommon:CreateTimer(self.Time, "OnTimeFightEnd")	                                                  --����Ϣ���������
end

function CurrentDungeonScript:HumanLeaveEvent(human)
	self.Stage:GetModDungeonScript():Cleanup()                                                                 	  --*����뿪����������о�������߼������������
	self.Stage:GetModObjs():ClearItemCharacter()		--��������ڵ���
	self.Stage:GetModObjs():ClearBreakableObject()		--��������ڿ��ƻ�����ӣ�
	self.Stage:GetModObjs():ClearTrap()
	self.Stage:GetModObjs():ClearPuppet() 
end
function CurrentDungeonScript:CreatureKilled(creature,killer, hurttype)	--�������ﱻɱ�¼�
    luaE_drop(self.MainHuman,nil,PrizeR,{self.Resources[self.SceneID][self.CurrLv]["RewardR1"][59]},{self.Resources[self.SceneID][self.CurrLv]["RewardR1"][60]},-1)
	luaE_drop(self.MainHuman,nil,PrizeR,{self.Resources[self.SceneID][self.CurrLv]["RewardR2"][59]},{self.Resources[self.SceneID][self.CurrLv]["RewardR2"][60]},-1)
	if self.SceneID == 0 then
		self.CurrNum1  = self.CurrNum1 + self.Resources[self.SceneID][self.CurrLv]["RewardR1"][60] * shuli600001
	    self.CurrNum2  = self.CurrNum2 + self.Resources[self.SceneID][self.CurrLv]["RewardR2"][60] * sliver600016
	else
		self.CurrNum1  = self.CurrNum1 + self.Resources[self.SceneID][self.CurrLv]["RewardR1"][60] 
	    self.CurrNum2  = self.CurrNum2 + self.Resources[self.SceneID][self.CurrLv]["RewardR2"][60]
	end
	self.SModCommon:CreateTimer(1, "OnFightEnd")
	
end


function CurrentDungeonScript:CreatureSpawn(creature)                                          --��������Ѫ�������¼�
	self.MainHuman:OpenAutoCombat()
    local i = 1;
	local j = 1;
	local Hp1 = 100
	local Hp2 = 100
	for i = 1,#self.Resources[self.SceneID][self.CurrLv]["RankR"],1 do
	     Hp1 = self.Resources[self.SceneID][self.CurrLv]["RankR"][i]
	     creature:GetModStatistic():ListenHPChanged(1, Hp1, "OntRankAchieveR")
    end	
	for j = 1,#self.Resources[self.SceneID][self.CurrLv]["RankS"],1 do
	     Hp2 = self.Resources[self.SceneID][self.CurrLv]["RankS"][j]
	     creature:GetModStatistic():ListenHPChanged(1, Hp2, "OntRankAchieveS")
    end
end

function CurrentDungeonScript:OntRankAchieveR(owner,condi,value)
    local i = 1 
	while value ~= self.Resources[self.SceneID][self.CurrLv]["RankR"][i] do
	     i = i + 1
	end
    luaE_drop(self.MainHuman,nil,PrizeR,{self.Resources[self.SceneID][self.CurrLv]["RewardR1"][2*i-1]},{self.Resources[self.SceneID][self.CurrLv]["RewardR1"][2*i]},-1)
	luaE_drop(self.MainHuman,nil,PrizeR,{self.Resources[self.SceneID][self.CurrLv]["RewardR2"][2*i-1]},{self.Resources[self.SceneID][self.CurrLv]["RewardR2"][2*i]},-1)
	if self.SceneID == 0 then
	     self.CurrNum1  = self.CurrNum1 + self.Resources[self.SceneID][self.CurrLv]["RewardR1"][2*i] * shuli600001
	     self.CurrNum2  = self.CurrNum2 + self.Resources[self.SceneID][self.CurrLv]["RewardR2"][2*i] * sliver600016
	else
	     self.CurrNum1  = self.CurrNum1 + self.Resources[self.SceneID][self.CurrLv]["RewardR1"][2*i]
	     self.CurrNum2  = self.CurrNum2 + self.Resources[self.SceneID][self.CurrLv]["RewardR2"][2*i]
	end
	local msg = { time_count = self.Time,resources1_id = self.CurrItem1,resources1_count = self.CurrNum1,resources2_id = self.CurrItem2,resources2_count = self.CurrNum2,resources3_id = self.CurrItem3,resources3_count = self.CurrNum3}
	self.MainHuman:SendMsg(msgids.SCResourcesUpdate,msg)
end

function CurrentDungeonScript:OntRankAchieveS(owner,condi,value)
    local j = 1
	while value ~= self.Resources[self.SceneID][self.CurrLv]["RankS"][j] do
	     j = j + 1
	end
    luaE_drop(self.MainHuman,nil,PrizeR,{self.Resources[self.SceneID][self.CurrLv]["RewardS1"][2*j-1]},{self.Resources[self.SceneID][self.CurrLv]["RewardS1"][2*j]},-1)
	luaE_drop(self.MainHuman,nil,PrizeR,{self.Resources[self.SceneID][self.CurrLv]["RewardS2"][2*j-1]},{self.Resources[self.SceneID][self.CurrLv]["RewardS2"][2*j]},-1)
	if self.SceneID == 0 then
	     self.CurrNum1  = self.CurrNum1 + self.Resources[self.SceneID][self.CurrLv]["RewardS1"][2*j] * shuli600002
	     self.CurrNum2  = self.CurrNum2 + self.Resources[self.SceneID][self.CurrLv]["RewardS2"][2*j] * sliver600017
	else
		 self.CurrNum1  = self.CurrNum1 + self.Resources[self.SceneID][self.CurrLv]["RewardS1"][2*j]
	     self.CurrNum3  = self.CurrNum3 + self.Resources[self.SceneID][self.CurrLv]["RewardS2"][2*j]
	end
	local msg = { time_count = self.Time,resources1_id = self.CurrItem1,resources1_count = self.CurrNum1,resources2_id = self.CurrItem2,resources2_count = self.CurrNum2,resources3_id = self.CurrItem3,resources3_count = self.CurrNum3}
	self.MainHuman:SendMsg(msgids.SCResourcesUpdate,msg)
end

function CurrentDungeonScript:OnTimeFightEnd()
    if self.SceneID == 0 then
	     local msg = { leave_str = FinishSTR2,resources1_id = self.CurrItem1,resources1_count = self.CurrNum1,resources2_id = self.CurrItem2,resources2_count = self.CurrNum2,resources3_id = self.CurrItem3,resources3_count = self.CurrNum3}
	     self.MainHuman:SendMsg(msgids.SCResourcesLeave,msg)
	else
	     local msg = { leave_str = FinishSTR4,resources1_id = self.CurrItem1,resources1_count = self.CurrNum1,resources2_id = self.CurrItem2,resources2_count = self.CurrNum2,resources3_id = self.CurrItem3,resources3_count = self.CurrNum3}
	     self.MainHuman:SendMsg(msgids.SCResourcesLeave,msg)
	 end
	 
	 --ʯ����ʧ
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k , v in pairs(CreatureTab) do
		v:LeaveWorld(0)
	end
end

function CurrentDungeonScript:OnFightEnd() 
    local msg = { time_count = self.Time,resources1_id = self.CurrItem1,resources1_count = self.CurrNum1,resources2_id = self.CurrItem2,resources2_count = self.CurrNum2,resources3_id = self.CurrItem3,resources3_count = self.CurrNum3}
	self.MainHuman:SendMsg(msgids.SCResourcesUpdate,msg)
	if self.SceneID == 0 then
	     local msg = { leave_str = FinishSTR1,resources1_id = self.CurrItem1,resources1_count = self.CurrNum1,resources2_id = self.CurrItem2,resources2_count = self.CurrNum2,resources3_id = self.CurrItem3,resources3_count = self.CurrNum3}
	     self.MainHuman:SendMsg(msgids.SCResourcesLeave,msg)
	else
	     local msg = { leave_str = FinishSTR3,resources1_id = self.CurrItem1,resources1_count = self.CurrNum1,resources2_id = self.CurrItem2,resources2_count = self.CurrNum2,resources3_id = self.CurrItem3,resources3_count = self.CurrNum3}
	     self.MainHuman:SendMsg(msgids.SCResourcesLeave,msg) 
	end
end













































































