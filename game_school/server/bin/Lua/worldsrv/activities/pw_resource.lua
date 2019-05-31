--默认初始化设置，程序约定
----------------------------------------------------------------------
CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .


----------------------------------------------------------------------
--数据初始化
----------------------------------------------------------------------
local AutoBattle                = true                                                                            --自动战斗初始设置为开启
local SceneIDSM                 = 3003                                                                               --银币,术力场景ID
local SceneIDIE                 = 3004                                                                               --强化石,冰火果场景ID

local PlayerEnterPos 		    = {184.1,53.1,155.8}                                                               --玩家出生点位置
local PlayerEnterOra 		    = {0.3,0.0,-0.9}	                                                              --玩家出生点朝向

local StonePos 		            = {185.9683,53.62904,162.3802}	                                                  --石像出生点坐标
local StoneOra		            = {1.0,0.0,0.0}     	                                                          --石像朝向

local PrizeR 				    = 5                                                                               --爆奖励位置点半径

local FinishSTR1                = 195023                                                                         --副本1成功击杀str
local FinishSTR3                = 195032                                                                         --副本2成功击杀str
local FinishSTR2                = 195022                                                                         --副本1时间到未成功击杀str
local FinishSTR4                = 195031                                                                         --副本2时间到未成功击杀str
local sliver600016              = 1000
local sliver600017              = 10000
local shuli600001               = 10000
local shuli600002               = 100000

CurrentDungeonScript.Resources = {
[0] = {                                                                                                           --银币,术力配置
	    [1] = {                                                                                                   --玩家等级段:20
		        ["Monster"]  = {20007,1},                                                                         --怪物ID和数量
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                               --普通奖励段
				["RankS"]    = {80,50},                                                                           --特殊奖励段
				["RewardR1"] = {600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2,600001,2},                                                                         
				["RewardS1"] = {600002,1,600002,3},                                                               --特殊奖励数量
				["RewardR2"] = {600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2,600016,2},                                                                         
				["RewardS2"] = {600017,1,600017,3},                                                               --特殊奖励数量
				["LvRange"]  = {0,30},                                                                            --生效等级段
		 },
		[2] = {                                                                                                   --玩家等级段:30                                                                         
				["Monster"]  = {20008,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                               --普通奖励段
				["RankS"]    = {80,50},                                                                           --特殊奖励段
				["RewardR1"] = {600001,2,600001,3,600001,2,600001,2,600001,3,600001,2,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,3,600001,2,600001,2,600001,3,600001,2},                                                                         
				["RewardS1"] = {600002,2,600002,4},                                                               --特殊奖励数量
				["RewardR2"] = {600016,2,600016,3,600016,2,600016,2,600016,3,600016,2,600016,3,600016,2,600016,2,600016,3,600016,2,600016,3,600016,2,600016,3,600016,2,600016,3,600016,2,600016,3,600016,2,600016,3,600016,2,600016,2,600016,3,600016,2,600016,2,600016,3,600016,2,600016,3,600016,2,600016,2},                                                                         
				["RewardS2"] = {600017,2,600017,4}, 				
				["LvRange"]  = {30,40},
		},
		[3] = {                                                                                                   --玩家等级段:40                                                                         
				["Monster"]  = {20009,1},                                                                   
                ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --普通奖励段
				["RankS"]    = {80,50},                                                                           --特殊奖励段
				["RewardR1"] = {600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3,600001,3},                                                                         
				["RewardS1"] = {600002,2,600002,4},                                                               --特殊奖励数量
				["RewardR2"] = {600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3,600016,3},                                                                         
				["RewardS2"] = {600017,2,600017,4},
				["LvRange"]  = {40,50},
		},
		[4] = {                                                                                                   --玩家等级段:50                                                                         
				["Monster"]  = {20010,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --普通奖励段
				["RankS"]    = {80,50},                                                                           --特殊奖励段
				["RewardR1"] = {600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4,600001,3,600001,4},                                                                         
				["RewardS1"] = {600002,2,600002,6},                                                               --特殊奖励数量
				["RewardR2"] = {600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4,600016,3,600016,4},                                                                         
				["RewardS2"] = {600017,2,600017,6},
				["LvRange"]  = {50,60},
		},
		[5] = {                                                                                                   --玩家等级段:60                                                                         
				["Monster"]  = {20011,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --普通奖励段
				["RankS"]    = {80,50},                                                                           --特殊奖励段
				["RewardR1"] = {600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4,600001,4},                                                                         
				["RewardS1"] = {600002,2,600002,6},                                                               --特殊奖励数量
				["RewardR2"] = {600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4,600016,4},                                                                         
				["RewardS2"] = {600017,2,600017,6},
				["LvRange"]  = {60,70},
		},
		[6] = {                                                                                                   --玩家等级段:70                                                                         
				["Monster"]  = {20012,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --普通奖励段
				["RankS"]    = {80,50},                                                                           --特殊奖励段
				["RewardR1"] = {600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5,600001,4,600001,5},                                                                         
				["RewardS1"] = {600002,2,600002,7},                                                               --特殊奖励数量
				["RewardR2"] = {600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5,600016,4,600016,5},                                                                         
				["RewardS2"] = {600017,2,600017,7},
				["LvRange"]  = {70,81},
		},
    },
[1] = {                                                                                                           --冰火果，强化石配置
		[1] = {                                                                                                   --玩家等级段:20
		        ["Monster"]  = {20001,1},                                                                         --怪物ID和数量
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --普通奖励段
				["RankS"]    = {80,50},                                                                           --特殊奖励段
				["RewardR1"] = {400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,2,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3},                                                                         
				["RewardS1"] = {400014,6,400014,8},                                                               --特殊奖励数量
				["RewardR2"] = {410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0},                                                                         
				["RewardS2"] = {410103,0,410103,1},                                                               --特殊奖励数量
				["LvRange"]  = {0,30},                                                                            --生效等级段
		 },
		[2] = {                                                                                                   --玩家等级段:30                                                                         
				["Monster"]  = {20002,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --普通奖励段
				["RankS"]    = {80,50},                                                                           --特殊奖励段
				["RewardR1"] = {400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,2,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3},                                                                         
				["RewardS1"] = {400014,8,400014,12},                                                               --特殊奖励数量
				["RewardR2"] = {410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0},                                                                         
				["RewardS2"] = {410103,0,410103,1}, 				
				["LvRange"]  = {30,40},
		},
		[3] = {                                                                                                   --玩家等级段:40                                                                         
				["Monster"]  = {20003,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --普通奖励段
				["RankS"]    = {80,50},                                                                           --特殊奖励段
				["RewardR1"] = {400014,3,400014,4,400014,3,400014,4,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,3,400014,4,400014,4,400014,3,400014,3,400014,3,400014,3},                                                                         
				["RewardS1"] = {400014,10,400014,16},                                                               --特殊奖励数量
				["RewardR2"] = {410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0},                                                                         
				["RewardS2"] = {410103,1,410103,1},
				["LvRange"]  = {40,50},
		},
		[4] = {                                                                                                   --玩家等级段:50                                                                         
				["Monster"]  = {20004,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --普通奖励段
				["RankS"]    = {80,50},                                                                           --特殊奖励段
				["RewardR1"] = {400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,3,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4},                                                                         
				["RewardS1"] = {400014,12,400014,18},                                                               --特殊奖励数量
				["RewardR2"] = {410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0},                                                                         
				["RewardS2"] = {410103,1,410103,1},
				["LvRange"]  = {50,60},
		},
		[5] = {                                                                                                   --玩家等级段:60                                                                         
				["Monster"]  = {20005,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --普通奖励段
				["RankS"]    = {80,50},                                                                           --特殊奖励段
				["RewardR1"] = {400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,4,400014,6,400014,4,400014,4,400014,4,400014,6,400014,4,400014,4,400014,4,400014,4,400014,4,400014,6},                                                                         
				["RewardS1"] = {400014,14,400014,20},                                                               --特殊奖励数量
				["RewardR2"] = {410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0},                                                                         
				["RewardS2"] = {410103,1,410103,2},
				["LvRange"]  = {60,70},
		},
		[6] = {                                                                                                   --玩家等级段:70                                                                         
				["Monster"]  = {20006,1},                                                                   
			    ["RankR"]    = {97,94,91,88,85,82,76,73,70,67,64,61,58,55,52,46,43,40,37,34,30,26,22,19,16,12,8,5,2},                                                                                --普通奖励段
				["RankS"]    = {80,50},                                                                           --特殊奖励段
				["RewardR1"] = {400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,4,400014,5,400014,5,400014,5,400014,6,400014,5,400014,6,400014,5,400014,6,400014,5},                                                                         
				["RewardS1"] = {400014,16,400014,24},                                                               --特殊奖励数量
				["RewardR2"] = {410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0,410102,1,410102,0,410102,0},                                                                         
				["RewardS2"] = {410103,1,410103,3},
				["LvRange"]  = {70,81},
		},
    },
}
-----------------------------------------------------------
--副本变量
-----------------------------------------------------------
CurrentDungeonScript.CurrLv = 1			--层数
CurrentDungeonScript.SceneID = -1	    --场景ID
CurrentDungeonScript.CurrItem1 = 0		--当前奖励物品ID1
CurrentDungeonScript.CurrItem2 = 0		--当前奖励物品ID2
CurrentDungeonScript.CurrItem3 = -1		--当前奖励物品ID2
CurrentDungeonScript.CurrNum1 = 0	    --当前奖励1数量
CurrentDungeonScript.CurrNum2 = 0	    --当前奖励2数量
CurrentDungeonScript.CurrNum3 = 0	    --当前奖励2数量
CurrentDungeonScript.stone = nil		--副本怪物
CurrentDungeonScript.CurrLevelFightActive = false --用于防止网络卡时多次刷怪
CurrentDungeonScript.Time = 300         --副本时间5分钟

-----------------------------------------------------------
--副本开启与关闭
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
--玩家进入与离开,死亡与复活
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

function CurrentDungeonScript:StageChoose()                                                                       --根据场景ID判定副本                    
    if toint32(self.Stage:GetBaseMapID()) == SceneIDSM then
	    return 0
	end
    if toint32(self.Stage:GetBaseMapID()) == SceneIDIE then
		return 1
	end	
end

function CurrentDungeonScript:LevelChoose()                                                                       --根据等级判定奖励情况                    
    local Lv = self.MainHuman:GetLevel()
	for i = 1,8,1 do
	    if Lv >= self.Resources[self.SceneID][i]["LvRange"][1] and Lv < self.Resources[self.SceneID][i]["LvRange"][2] then
		   return i
		end
	end
end

function CurrentDungeonScript:SpawnStone()                                                                        --显示怪物，三秒后开始自动战斗
	if self.CurrLevelFightActive == true then	                                                                  --玩家自动战斗        
	    --self.MainHuman:OpenAutoCombat()
	end
	self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(5))                                      --5秒后开始战斗
	self.SModCommon:CreateTimer(5, "OnFightBegin")
end

function CurrentDungeonScript:OnFightBegin()	                                                                  --进场XX时间后开始刷怪
                                                                                                                   --防止网络卡的情况多次刷怪
	if self.CurrLevelFightActive then
		pwdist.log(self.MainHuman:GetName() .. ',Fight already begin')
		return
	end
	self.CurrLevelFightActive = true
	
	self.SModDungeonScript:PlotStart()	
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(41597))			                          --文字提示：开始挑战
	self.Stage:GetModObjs():SuspendCreaturesAI()
	self.stone = self.Stage:GetModCommon():SpawnMonsterAt(StonePos, StoneOra, self.Resources[self.SceneID][self.CurrLv]["Monster"][1])
	self.Stage:GetModObjs():ResumeCreaturesAI()
	self.SModDungeonScript:PlotClean()
	--self.MainHuman:GetModBabel():OnWaveStart(self.CurrLv)	                                                      --通知服务器战斗开
	
	local msg = { time_count = self.Time,resources1_id = self.CurrItem1,resources1_count = self.CurrNum1,resources2_id = self.CurrItem2,resources2_count = self.CurrNum2,resources3_id = self.CurrItem3,resources3_count = self.CurrNum3}
	self.MainHuman:SendMsg(msgids.SCResourcesUpdate,msg)
    self.SModCommon:CreateTimer(self.Time, "OnTimeFightEnd")	                                                  --发消息，报告参数
end

function CurrentDungeonScript:HumanLeaveEvent(human)
	self.Stage:GetModDungeonScript():Cleanup()                                                                 	  --*玩家离开场景清空所有剧情相关逻辑，以免出问题
	self.Stage:GetModObjs():ClearItemCharacter()		--清除场景内掉落
	self.Stage:GetModObjs():ClearBreakableObject()		--清除场景内可破坏物（箱子）
	self.Stage:GetModObjs():ClearTrap()
	self.Stage:GetModObjs():ClearPuppet() 
end
function CurrentDungeonScript:CreatureKilled(creature,killer, hurttype)	--场景怪物被杀事件
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


function CurrentDungeonScript:CreatureSpawn(creature)                                          --场景怪物血量监听事件
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
	 
	 --石像消失
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













































































