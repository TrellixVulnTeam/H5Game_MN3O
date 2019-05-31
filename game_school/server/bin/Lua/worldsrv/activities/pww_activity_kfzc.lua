-----------------------------------------------------------------
--问题
--小地图显示的中路塔的图标显示不对，等有小地图的时候，通知前端修改,脚本已经改完
--特效墙没搞
--塔模型死亡模型没有提
--右下角排行榜界面有信息残留，会保留上一场的数据

-- 活动:跨服战场跨服的
-- 世界服务器端
-----------------------------------------------------------------

CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
local R_Encampment_POS = {16.1,55.7,17.81}		--红方基地
local R_ResurrectPOS = {32.85,55.6,31.25}		--红方复活点
local R_NpcSpawnPos1 = {29.8,55.72,13.1}	--红方NPC刷怪点左
local R_NpcSpawnPos2 = {14.2,55.72,32.4}	--红方NPC刷怪点右
local R_NpcSpawnPos3 = {26.6,55.72,26.1}	--红方NPC刷怪点中
local R_Tower1_pos = {52.4,55,15.2}			--左路里
local R_Tower2_pos = {133.4,50,14.1}		--左路外1
local R_Tower3_pos = {236.2,50,17.5}		--左路外2
local R_Tower4_pos = {16.1,55,56}		--右路里
local R_Tower5_pos = {14.6,50,128.7}		--右路外1
local R_Tower6_pos = {18.7,50,223.9}		--右路外2
local R_Tower7_pos = {43.4,55,37.4}		--中路内
local R_Tower8_pos = {77,50,65.4}		--中路外1
local R_Tower9_pos = {118,50,110.6}		--中路外2


local B_Encampment_POS = {275.1,55.7,278.2}	--蓝方基地
local B_ResurrectPOS = {263.4,55.6,268.3}	--蓝方复活点
local B_NpcSpawnPos1 = {260.16,55.7,282.28}---刷怪点左
local B_NpcSpawnPos2 = {280.99,55.7,264.89}---刷怪点右
local B_NpcSpawnPos3 = {263.55,55.7,267.08}---刷怪点中
local B_Tower1_pos = {233,55,281.2}--左路里
local B_Tower2_pos = {164.1,50.2,279.6}--左路外1
local B_Tower3_pos = {76.2,50,281.5}--左路外2
local B_Tower4_pos = {284.5,55,243.7}--右路里
local B_Tower5_pos = {282.1,50.1,174.6}--右路外1
local B_Tower6_pos = {285.9,50,66.8}--右路外2
local B_Tower7_pos = {249,55,253.5}--中路内
local B_Tower8_pos = {216.7,51.8,214.5}--中路外1
local B_Tower9_pos = {171.9,50,170.6}--中路外2

local R_LWayPos = {277,50,39}	-----三条路的中点，小兵先寻到中点再去寻塔
local R_RWayPos = {23,50,265}
local R_ZWayPos = {140,50,140.9}
local B_LWayPos = {23,50,265}
local B_RWayPos = {277,50,39}
local B_ZWayPos = {140,50,140.9}

local WayRadius = 5				-----三条路中间创建圆形区域，用来给小兵添加标记
local WayBuff = 351  			-----标记buff

--不同级别段的NPCID不一样
local PVP_NpcsTable = {
	[80] = {
		R_EncampmentId = 100001,	--红方大本营基地ID
		B_EncampmentId = 100021,    --蓝方大本营基地ID
		R_NpcId1 = {100008},		--红方小怪，左侧
		R_NpcId2 = {100009},		--红方小怪，右侧
		R_NpcId3 = {100010},		--红方小怪，中间
		B_NpcId1 = {100028},
		B_NpcId2 = {100029},
		B_NpcId3 = {100030},
		R_TowerId1 = 100002,		--红方塔，左、里
		R_TowerId2 = 100003,		--红方塔，左、外1
		R_TowerId3 = 100004,		--红方塔，左、外2
		R_TowerId4 = 100005,		--红方塔，右、里
		R_TowerId5 = 100006,		--红方塔，右、外1
		R_TowerId6 = 100007,		--红方塔，右、外2
		R_TowerId7 = 100011,		--红方塔，中、里
		R_TowerId8 = 100012,		--红方塔，右、外1
		R_TowerId9 = 100013,		--红方塔，右、外2
		B_TowerId1 = 100022,		---蓝方
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
		R_EncampmentId = 100101,	--红方大本营基地ID
		B_EncampmentId = 100121,    --蓝方大本营基地ID
		R_NpcId1 = {100108},		--红方小怪，左侧
		R_NpcId2 = {100109},		--红方小怪，右侧
		R_NpcId3 = {100110},		--红方小怪，中间
		B_NpcId1 = {100128},
		B_NpcId2 = {100129},
		B_NpcId3 = {100130},
		R_TowerId1 = 100102,		--红方塔，左、里
		R_TowerId2 = 100103,		--红方塔，左、外1
		R_TowerId3 = 100104,		--红方塔，左、外2
		R_TowerId4 = 100105,		--红方塔，右、里
		R_TowerId5 = 100106,		--红方塔，右、外1
		R_TowerId6 = 100107,		--红方塔，右、外2
		R_TowerId7 = 100111,		--红方塔，中、里
		R_TowerId8 = 100112,		--红方塔，右、外1
		R_TowerId9 = 100113,		--红方塔，右、外2
		B_TowerId1 = 100122,		---蓝方
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
		R_EncampmentId = 100201,	--红方大本营基地ID
		B_EncampmentId = 100221,    --蓝方大本营基地ID
		R_NpcId1 = {100208},		--红方小怪，左侧
		R_NpcId2 = {100209},		--红方小怪，右侧
		R_NpcId3 = {100210},		--红方小怪，中间
		B_NpcId1 = {100228},
		B_NpcId2 = {100229},
		B_NpcId3 = {100230},
		R_TowerId1 = 100202,		--红方塔，左、里
		R_TowerId2 = 100203,		--红方塔，左、外1
		R_TowerId3 = 100204,		--红方塔，左、外2
		R_TowerId4 = 100205,		--红方塔，右、里
		R_TowerId5 = 100206,		--红方塔，右、外1
		R_TowerId6 = 100207,		--红方塔，右、外2
		R_TowerId7 = 100211,		--红方塔，中、里
		R_TowerId8 = 100212,		--红方塔，右、外1
		R_TowerId9 = 100213,		--红方塔，右、外2
		B_TowerId1 = 100222,		---蓝方
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
		R_EncampmentId = 100301,	--红方大本营基地ID
		B_EncampmentId = 100321,    --蓝方大本营基地ID
		R_NpcId1 = {100308},		--红方小怪，左侧
		R_NpcId2 = {100309},		--红方小怪，右侧
		R_NpcId3 = {100310},		--红方小怪，中间
		B_NpcId1 = {100328},
		B_NpcId2 = {100329},
		B_NpcId3 = {100330},
		R_TowerId1 = 100302,		--红方塔，左、里
		R_TowerId2 = 100303,		--红方塔，左、外1
		R_TowerId3 = 100304,		--红方塔，左、外2
		R_TowerId4 = 100305,		--红方塔，右、里
		R_TowerId5 = 100306,		--红方塔，右、外1
		R_TowerId6 = 100307,		--红方塔，右、外2
		R_TowerId7 = 100311,		--红方塔，中、里
		R_TowerId8 = 100312,		--红方塔，右、外1
		R_TowerId9 = 100313,		--红方塔，右、外2
		B_TowerId1 = 100322,		---蓝方
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
	
	
--防御塔无敌BUFF
local Aura_wudi = 304


	
--防御塔和基地，被摧毁后的模型表现
local Dest_towerR = 100050
local Dest_towerB = 100052
local Dest_encamR = 100051
local Dest_encamB = 100053

--初始化开场的NPC等级为80
CurrentDungeonScript.CurrentLv = 80
local NpcSpawnTimer = 30	--场景小怪刷新间隔
CurrentDungeonScript.Wavenum = 1	--记录当前是第几波怪
local WaveMonsCount = 7		--每波怪刷几组怪--7

--塔被摧毁STR
local Str_TowerKilled1 = 100502	--我方上塔被摧毁
local Str_TowerKilled2 = 100503	--我方下塔被摧毁
local Str_TowerKilled3 = 100504	--敌方上塔被摧毁
local Str_TowerKilled4 = 100505	--敌方下塔被摧毁
local Str_TowerKilled5 = 100526	--我方中塔被摧毁
local Str_TowerKilled6 = 100527	--敌方中塔被摧毁
--获取BUFF消息str
local Str_getbuff_speed1 = 100506		--我方小怪加速度
local Str_getbuff_speed2 = 100507		--敌方小怪加速度
local Str_getbuff_blood1 = 100508		--我方小怪加血
local Str_getbuff_blood2 = 100509		--敌方小怪加血
local Str_getbuff_addnum1 = 100510		--我方小怪加数量
local Str_getbuff_addnum2 = 100511		--敌方小怪加数量




--场景静物相关
local Buff_SpawnTime = 100	--BUFF球刷新间隔
local Buff_PosTable = {	--场景BUFF坐标
	pos1 = {135.21,54.39,234.95},
	pos2 = {229.53,54.39,149.08},
	pos3 = {163.3,54.39,64.94},
	pos4 = {70.22,54.39,129.86},
	pos5 = {143.9,51.47,146.7},
	}
local Buff_IdTable = {	--场景BUFF静物
	id1 = 100041,	--加速度
	id2 = 100042,	--加血量
	id3 = 100043,}	--加刷怪
local BUFF_speed = 30400
local BUFF_blood1 = 30410
local BUFF_blood2 = 30411
local BUFF_addmons_num = 3	--摸BUFF球加的波数

	--各类阵营
local R_Faction_human = 3	--红方玩家阵营
local B_Faction_human = 4
local R_Faction_tower = 9	--红方塔阵营
local B_Faction_tower = 10
local R_Faction_npc = 11	--红方小怪阵营
local B_Faction_npc = 12

--小地图协议相关（需要前端配合修改等正式地图搞定了在搞这里把）GetMonsterInfo
local Map_type_human = 15	--玩家
local Map_type_monster = 16	--小怪
local Map_type_R_encam = 1	--红方基地
local Map_type_R_tower1 = 2	--红方塔，左侧，里
local Map_type_R_tower2 = 3	--红方塔，左侧，外1
local Map_type_R_tower3 = 4	--红方塔，左侧，外2
local Map_type_R_tower4 = 5	--红方塔，右侧，里
local Map_type_R_tower5 = 6	--红方塔，右侧，外1
local Map_type_R_tower6 = 7	--红方塔，右侧，外2
local Map_type_R_tower7 = 20	--红方塔，中间，里
local Map_type_R_tower8 = 21	--红方塔，中间，外1
local Map_type_R_tower9 = 22	--红方塔，中间，外2

local Map_type_B_encam = 8	--蓝方基地
local Map_type_B_tower1 = 9		--蓝方塔，左侧，里
local Map_type_B_tower2 = 10	--蓝方塔，左侧，外1
local Map_type_B_tower3 = 11	--蓝方塔，左侧，外2
local Map_type_B_tower4 = 12	--蓝方塔，右侧，里
local Map_type_B_tower5 = 13	--蓝方塔，右侧，外1
local Map_type_B_tower6 = 14	--蓝方塔，右侧，外2
local Map_type_B_tower7 = 23	--蓝方塔，中间，里
local Map_type_B_tower8 = 24	--蓝方塔，中间，外1
local Map_type_B_tower9 = 25	--蓝方塔，中间，外2

local Map_type_buff_speed = 17	--加速度水晶类型ID
local Map_type_buff_blood = 18	--加血水晶类型ID
local Map_type_buff_addmons = 19	--加刷怪水晶类型ID


local Map_state_dead = 0	--死亡	
local Map_state_live = 1	--存活
local Map_race_human = 1	--红方
local Map_race_spirit = 2	--蓝方


--记录塔的个数
CurrentDungeonScript.R_towercount = 10
CurrentDungeonScript.B_towercount = 10


--进攻小怪，按攻击顺序对应的塔1、塔2、基地
--默认填的30级是creatureID，后面根据玩家等级再重新赋值
CurrentDungeonScript.MonsVsTower = {}




CurrentDungeonScript.Timer_begain = 60		--开场倒计时-60
CurrentDungeonScript.Timer_checkenter = 40		--多长时间检测进场人数40S
local min_human_count = 3	--最低进场人数，单方--3
local fillmember_time = 180	--补人持续时间

CurrentDungeonScript.human_num = 0	--临时计数用，假数据，给玩家分配队伍阵营

--特效墙相关
--开启特效墙
function CurrentDungeonScript:BroadcastBlockEffectsStatus()
-- pwdist.log("特效墙开启")
    for k,v in pairs(self.BlockEffects) do
        self.Stage:GetModDetour():EnableBlockEffects(k,v)
    end
-- pwdist.log("特效墙开启end")
end
--关闭特效墙
function CurrentDungeonScript:DisableAllBlockEffects()
-- pwdist.log("特效墙关闭")
    for k,v in pairs(self.BlockEffects) do
        self.Stage:GetModDetour():EnableBlockEffects(k,false)
    end
    
    self.BlockEffects = {}
-- pwdist.log("特效墙关闭end")
end
--四个特效墙
CurrentDungeonScript.BlockEffects = {}
CurrentDungeonScript.BlockEffects[50] = true
CurrentDungeonScript.BlockEffects[51] = true
CurrentDungeonScript.BlockEffects[52] = true
CurrentDungeonScript.BlockEffects[53] = true
CurrentDungeonScript.BlockEffects[54] = true
CurrentDungeonScript.BlockEffects[55] = true

--角色进场、离场str
local Str_humanenter = 100512
local Str_humanleave = 100513

--战场玩法提示str
local Str_gamehint = {
	[1] = 13104,
	[2] = 13105,
	[3] = 13106,
	}

--根据杀人数给玩家加BUFF
local KillNum_AddBuff = {
[50] = {["buffid"] = 304 , ["strid"] = 100522},--["buffid"] = 304
[100] = {["buffid"] = 304 , ["strid"] = 100523},--["buffid"] = 304
[200] = {["buffid"] = 304 , ["strid"] = 100524},--["buffid"] = 304
[500] = {["buffid"] = 304 , ["strid"] = 100525},--["buffid"] = 304

}





function CurrentDungeonScript:Startup()
-- pwdist.log("场景创建")
    self.SModDungeonScript = self.Stage:GetModDungeonScript()
	self.SModCommon = self.Stage:GetModCommon()
	self.SModLogicBattle = self.Stage:GetModLogic():cast("SModLogicBattle")
	self.SModObjs = self.Stage:GetModObjs()
	--获取当前等级模式
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
-- pwdist.log("场景创建====="..self.CurrentLv.."     ")	

	self.MonsVsTower[1] = { MonsterT = PVP_NpcsTable[self.CurrentLv].R_NpcId1,	--红方左侧小怪组
							MonsterPos = R_NpcSpawnPos1,
							MonsterFac = 11,
							MonsterWay = R_LWayPos,
							Obj1 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId6,live = 1,pos = B_Tower6_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj2 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId5,live = 1,pos = B_Tower5_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj3 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId4,live = 1,pos = B_Tower4_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj4 = {id = PVP_NpcsTable[self.CurrentLv].B_EncampmentId,live = 1,pos = B_Encampment_POS,destid = Dest_encamB},
							
							}
	self.MonsVsTower[2] = { MonsterT = PVP_NpcsTable[self.CurrentLv].R_NpcId2,	--红方右侧小怪组
							MonsterPos = R_NpcSpawnPos2,
							MonsterFac = 11,
							MonsterWay = R_RWayPos,
							Obj1 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId3,live = 1,pos = B_Tower3_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj2 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId2,live = 1,pos = B_Tower2_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj3 = {id = PVP_NpcsTable[self.CurrentLv].B_TowerId1,live = 1,pos = B_Tower1_pos,fac = B_Faction_tower,destid = Dest_towerB},
							Obj4 = {id = PVP_NpcsTable[self.CurrentLv].B_EncampmentId,live = 1,pos = B_Encampment_POS,destid = Dest_encamB},
							}	
	self.MonsVsTower[3] = { MonsterT = PVP_NpcsTable[self.CurrentLv].R_NpcId3,	--红方中间小怪组
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
	
	--初始化队伍数据
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
	
	
	--创建大本营
	local R_Enc_obj = self.SModCommon:SpawnMonsterAt(R_Encampment_POS,{0.7,0,0.7},PVP_NpcsTable[self.CurrentLv].R_EncampmentId)	--刷大本营
		R_Enc_obj:ChangeFaction(R_Faction_tower)
		R_Enc_obj:GetModAura():Create(Aura_wudi) --无敌无表现
	local B_Enc_obj = self.SModCommon:SpawnMonsterAt(B_Encampment_POS,{-0.9,0,-0.5},PVP_NpcsTable[self.CurrentLv].B_EncampmentId)
		B_Enc_obj:ChangeFaction(B_Faction_tower)
		B_Enc_obj:GetModAura():Create(Aura_wudi) --无敌无表现
		
	--基地被摧毁
	SetEventHandler(StageEvents.CreatureKilled,"EncampmentKilled_R",{type = PVP_NpcsTable[self.CurrentLv].R_EncampmentId})	--基地被摧毁
	SetEventHandler(StageEvents.CreatureKilled,"EncampmentKilled_B",{type = PVP_NpcsTable[self.CurrentLv].B_EncampmentId})
	
	--小怪、塔被摧毁回调 Wavenum
	for k , v  in pairs(self.MonsVsTower) do
		for i , j in pairs(v.MonsterT) do	--记录NPC小怪刷新
			SetEventHandler(StageEvents.CreatureSpawn,"NpcSpawn_fight",{type = j})	--NPC出生就go
			SetEventHandler(StageEvents.CreatureKilled,"NpcKilled_forScore",{type = j})	--NPC被杀
		end
		--刷新各个位置的塔，修改阵营
		local obj1 = self.SModCommon:SpawnMonsterAt(v.Obj1.pos,{0.7,0,0.7},v.Obj1.id)
		obj1:ChangeFaction(v.Obj1.fac)
		--obj1:GetModAura():Create(Aura_wudi) --无敌无表现
		local obj2 = self.SModCommon:SpawnMonsterAt(v.Obj2.pos,{0.7,0,0.7},v.Obj2.id)
		obj2:ChangeFaction(v.Obj2.fac)
		obj2:GetModAura():Create(Aura_wudi) --无敌无表现
		local obj3 = self.SModCommon:SpawnMonsterAt(v.Obj3.pos,{0.7,0,0.7},v.Obj3.id)
		obj3:ChangeFaction(v.Obj3.fac)
		obj3:GetModAura():Create(Aura_wudi) --无敌无表现
		--记录防御塔被摧毁
		SetEventHandler(StageEvents.CreatureKilled,"Tower_Killed",{type = v.Obj1.id})
		SetEventHandler(StageEvents.CreatureKilled,"Tower_Killed",{type = v.Obj2.id})
		SetEventHandler(StageEvents.CreatureKilled,"Tower_Killed",{type = v.Obj3.id})
	end
	
	--刷BUFF球
	math.randomseed(os.time())	--随机种子
	math.random(1,3)
	math.random(1,3)
	self:Pos1_SpawnBuff()
	self:Pos2_SpawnBuff()
	self:Pos3_SpawnBuff()
	self:Pos4_SpawnBuff()
	self:Pos5_SpawnBuff()
	

	
	--开场提示
	self.SModDungeonScript:CreateTimer(self.Timer_begain - 40,"OnTimer_gamehint1")
	self.SModDungeonScript:CreateTimer(self.Timer_begain - 20,"OnTimer_gamehint2")
	self.SModDungeonScript:CreateTimer(self.Timer_begain,"OnTimer_gamehint3")
	
	self.trigger1 = self.Stage:CreateTriggerSphere(R_LWayPos,WayRadius,"OnTriggerEnter","")
	self.trigger1:AddAllowClsid(CLSID.Monster)  --允许怪物激活触发器
	self.trigger2 = self.Stage:CreateTriggerSphere(R_RWayPos,WayRadius,"OnTriggerEnter","")
	self.trigger2:AddAllowClsid(CLSID.Monster)  --允许怪物激活触发器
	self.trigger3 = self.Stage:CreateTriggerSphere(R_ZWayPos,WayRadius,"OnTriggerEnter","")
	self.trigger3:AddAllowClsid(CLSID.Monster)  --允许怪物激活触发器
	self.trigger4 = self.Stage:CreateTriggerSphere(B_LWayPos,WayRadius,"OnTriggerEnter","")
	self.trigger4:AddAllowClsid(CLSID.Monster)  --允许怪物激活触发器
	self.trigger5 = self.Stage:CreateTriggerSphere(B_RWayPos,WayRadius,"OnTriggerEnter","")
	self.trigger5:AddAllowClsid(CLSID.Monster)  --允许怪物激活触发器
	self.trigger6 = self.Stage:CreateTriggerSphere(B_ZWayPos,WayRadius,"OnTriggerEnter","")
	self.trigger6:AddAllowClsid(CLSID.Monster)  --允许怪物激活触发器
-- pwdist.log("场景创建end")
end

----给走到中间的小兵加标记buff
function CurrentDungeonScript:OnTriggerEnter(trigger,target)
-- pwdist.log("给走到中间的小兵加标记buff")
	local Mcreature = target:cast('Creature')
	if(Mcreature ~= nil)then
		Mcreature:GetModAura():Create(WayBuff)
	end	
-- pwdist.log("给走到中间的小兵加标记buff======end")
end
--开场提示
function CurrentDungeonScript:OnTimer_gamehint1()
-- pwdist.log("开场提示1")
	if self.HasFinishCompete == true then return end
	local humans = self.Stage:GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		v:Hint(Str_gamehint[1],2000)
	end
-- pwdist.log("开场提示1end")
end
function CurrentDungeonScript:OnTimer_gamehint2()
-- pwdist.log("开场提示2")
	if self.HasFinishCompete == true then return end
	local humans = self.Stage:GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		v:Hint(Str_gamehint[2],2000)
	end
-- pwdist.log("开场提示2end")
end
function CurrentDungeonScript:OnTimer_gamehint3()
-- pwdist.log("开场提示3")
	if self.HasFinishCompete == true then return end
	local humans = self.Stage:GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		v:Hint(Str_gamehint[3],2000)
	end
-- pwdist.log("开场提示3end")
end

--战场开启
function CurrentDungeonScript:Timer_start()
-- pwdist.log("战场开启")
	self:DisableAllBlockEffects()
	self.Stage:GetModDetour():EnableMotionBlock(1,true)
	self.Stage:GetModDetour():EnableMotionBlock(0,true)
	self:BeginCompete()
	self.SModDungeonScript:PlotClean()
	--self.SModDungeonScript:CreateTimer(fillmember_time,"OnTimer_stopfillmem")	--XX时间后停止补人
	self.SModCommon:BroadcastClientOperation(UI_WARN,tostring(13111))			--文字提示：战斗开始，开始出兵
	self.SModDungeonScript:CreateTimer(2,"TimerStart_CloseEffects")	--2秒后再删一次特效墙
	self.SModLogicBattle:StartBattle()	--通知服务器开场了
	self.SModLogicBattle:UpdateBattleInfo(self.RTeamId,self.R_towercount)
	self.SModLogicBattle:UpdateBattleInfo(self.BTeamId,self.B_towercount)
	
	self.SModDungeonScript:CreateTimer(1800,"OnTimer_gameover") --时间统计，30分钟结束
	self.SModDungeonScript:CreateTimer(1500,"OnTimer_gameoverhint") --时间统计，25分钟提醒
	
	self.timer_upklist = self.SModDungeonScript:CreatePeriodTimer(5,5,-1,"OnTimer_upklist")	--更新排行榜
-- pwdist.log("战场开启end")
end
function CurrentDungeonScript:TimerStart_CloseEffects()
-- pwdist.log("关闭特效墙2")
	self.Stage:GetModDetour():EnableBlockEffects(50,false)
	self.Stage:GetModDetour():EnableBlockEffects(51,false)	
	self.Stage:GetModDetour():EnableBlockEffects(52,false)	
	self.Stage:GetModDetour():EnableBlockEffects(53,false)	
	self.Stage:GetModDetour():EnableBlockEffects(54,false)
	self.Stage:GetModDetour():EnableBlockEffects(55,false)
-- pwdist.log("关闭特效墙2end")
end
--停止补人
function CurrentDungeonScript:OnTimer_stopfillmem()
-- pwdist.log("停止补人")
	self.SModLogicBattle:CloseFillMember()
-- pwdist.log("停止补人end")
end

--更新排行榜
function CurrentDungeonScript:OnTimer_upklist()
-- pwdist.log("更新排行榜")
	local R_Teamnum = self.SModLogicBattle:GetBattleTeamNum(self.RTeamId)
	local B_Teamnum = self.SModLogicBattle:GetBattleTeamNum(self.BTeamId)
	if(B_Teamnum > 0 and R_Teamnum > 0)then
		self.SModLogicBattle:UpdateBattleRanklist()
	end	
-- pwdist.log("更新排行榜end")
end

--检测进场人数
function CurrentDungeonScript:OnTimer_checkenter()
-- pwdist.log("检查进场人数")
	local R_Teamnum = self.SModLogicBattle:GetBattleTeamNum(self.RTeamId)
	local B_Teamnum = self.SModLogicBattle:GetBattleTeamNum(self.BTeamId)
	if R_Teamnum < min_human_count or B_Teamnum < min_human_count then	--人数不足
		self.HasFinishCompete = true
		self:AbortCompete()	--异常结束
		
		self.SModObjs:BroadcastNotifyWithFaction(100518,ChannelType.Announcement,2,R_Faction_human,"60")
		self.SModObjs:BroadcastNotifyWithFaction(100518,ChannelType.Announcement,2,B_Faction_human,"60")
		
		self.SModDungeonScript:CreateTimer(20,"GameOver_leavedungeon_hint2")
		self.SModDungeonScript:CancelTimer(self.timerstart)
	else
		--可以开场，执行补人
		self.SModLogicBattle:StartFillMember()
	end
-- pwdist.log("检查进场人数end")		
end

function CurrentDungeonScript:GameOver_leavedungeon_hint2()
-- pwdist.log("离场2")
	self.SModObjs:BroadcastNotifyWithFaction(100518,ChannelType.Announcement,2,R_Faction_human,"40")
	self.SModObjs:BroadcastNotifyWithFaction(100518,ChannelType.Announcement,2,B_Faction_human,"40")
	self.SModDungeonScript:CreateTimer(20,"GameOver_leavedungeon_hint3")
-- pwdist.log("离场2end")
end
function CurrentDungeonScript:GameOver_leavedungeon_hint3()
-- pwdist.log("离场3")
	self.SModObjs:BroadcastNotifyWithFaction(100518,ChannelType.Announcement,2,R_Faction_human,"20")
	self.SModObjs:BroadcastNotifyWithFaction(100518,ChannelType.Announcement,2,B_Faction_human,"20")
-- pwdist.log("离场3end")
end

function CurrentDungeonScript:OnHumanEnter(human)
-- pwdist.log("玩家进场")
	human:GetModMisc():SetBitEx(2,2000)
	
	local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
	local hid = tostring(human:GetID())
-- pwdist.log("玩家进场===="..hid)	
	--初始化队员数据
	self.TeamMembersTable[tid][hid] = {}
	human:ChangeFaction(self.TeamsTable[tid]["camp"])
	human:GetModMotionMaster():ChangePosition(self.TeamsTable[tid]["spawn"])
	human:GetModLansquenet():ChangeLansFaction()---改变侍从阵营
	self.TeamMembersTable[tid][hid]["kill_npc"] = 0
	self.TeamMembersTable[tid][hid]["kill_hum"] = 0
	self.TeamMembersTable[tid][hid]["get_buff"] = 0
	self.TeamMembersTable[tid][hid]["be_killed"] = 0
	--双方队伍计数
	self.TeamMembersnum[tid]["humannum"] = self.TeamMembersnum[tid]["humannum"] + 1
	
	--比赛已经结束或终止了，加载太慢了
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
	--给队友发消息
	self.SModObjs:BroadcastNotifyWithFaction(Str_humanenter,ChannelType.General,2,human:GetFaction(),human:GetName(),human:GetServerName())
-- pwdist.log("玩家进场end")	
end

function CurrentDungeonScript:OnHumanLeave(human)
-- pwdist.log("玩家离开")
	--离开，删除地图显示
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
	
	--单方人数为空后，就结束比赛
	self.TeamMembersnum[tid]["humannum"] = self.TeamMembersnum[tid]["humannum"] - 1
	if self.TeamMembersnum[tid]["humannum"] == 0 then --人数为0，结束
		if tid == self.RTeamId then
			self.WinTeamId = self.BTeamId
			self.LoseTeamId = self.RTeamId
			
			self.SModObjs:BroadcastNotifyWithFaction(100519,ChannelType.Announcement,2,R_Faction_human)
			self.SModObjs:BroadcastNotifyWithFaction(100519,ChannelType.Announcement,2,B_Faction_human)
			self.SModDungeonScript:CreateTimer(10,"OntimerEndedCompete")		
		end
	else
		--给队友发消息
		self.SModObjs:BroadcastNotifyWithFaction(Str_humanleave,ChannelType.General,2,human:GetFaction(),human:GetName(),human:GetServerName())
	end 
-- pwdist.log("玩家离开end")
end

function CurrentDungeonScript:OntimerEndedCompete()
-- pwdist.log("OntimerEndedCompete")
	self:EndedCompete()
-- pwdist.log("OntimerEndedCompeteEND")
end

--玩家死亡
function CurrentDungeonScript:OnHumanKilled(human,killer)
-- pwdist.log("玩家被杀")
	--human:GetModRealive():HideRealiveButton(true)
	local hid = tostring(human:GetID())
	local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
	--human:GetModRealive():Realive(self.TeamsTable[tid]["resurrect"],20000)
	human:GetModRealive():SetRealiveDelay(5000)
	self.TeamMembersTable[tid][hid]["be_killed"] = self.TeamMembersTable[tid][hid]["be_killed"] + 1
	
	
	--给击杀者计算杀人数
	if killer:IsKindOf(CLSID.Human) then 
		local human= killer:cast("Human")
		local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
		local hid = tostring(human:GetID())
		self.TeamMembersTable[tid][hid]["kill_hum"] = self.TeamMembersTable[tid][hid]["kill_hum"] + 1
		
		--给击杀队伍计数
		--[[
		self.TeamsTable[tid]["killnum"] = self.TeamsTable[tid]["killnum"] + 1
		for k ,v in pairs(KillNum_AddBuff) do
			if self.TeamsTable[tid]["killnum"] == k then
				local humans = GetCurrentStage():GetModObjs():GetHumans()
				for i , j in pairs(humans) do
					if j:GetFaction() == self.TeamsTable[tid]["camp"] then
						--加光环
						human:GetModAura():Create(v.buffid)
						--广播
						self.SModObjs:BroadcastNotifyWithFaction(v.strid,ChannelType.Announcement,2,j:GetFaction(),tostring(k))
					end
				end
			end
		end
		]]
	end
	--发送各个玩家积分情况
	for k , v in pairs(self.TeamMembersTable) do
		for i , j in pairs(v) do
			self.SModLogicBattle:AddBattleScore(i,j.kill_hum,j.kill_npc,j.get_buff,j.be_killed)
		end
	end
-- pwdist.log("玩家被杀end")	
end
--玩家复活
function CurrentDungeonScript:OnHumanResurrect(human)
-- pwdist.log("玩家复活")	
	local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
	human:GetModMotionMaster():ChangePosition(self.TeamsTable[tid]["resurrect"])
	human:GetModLansquenet():ChangeLansFaction()---改变侍从阵营
	
	local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
	human:GetModMotionMaster():ChangePosition(self.TeamsTable[tid]["resurrect"])
	human:GetModLansquenet():ChangeLansFaction()---改变侍从阵营
-- pwdist.log("玩家复活end")	
end

function CurrentDungeonScript:BeginCompete()
-- pwdist.log("开始计时")
	self.Begin_clock = os.time()

	self.HasStartCompete = true
	
	self.spawnmons_cycle = self.SModDungeonScript:CreatePeriodTimer(1,NpcSpawnTimer,-1,"Timer_spawnmons_cycle")
	self.mons_vs_tower = self.SModDungeonScript:CreatePeriodTimer(1,2,-1,"OnTimer_mons_vs_tower")
	--地图显示塔和水晶
	self:UpdateMapInfo()
-- pwdist.log("开始计时end")
end


--循环刷怪
function CurrentDungeonScript:Timer_spawnmons_cycle()
-- pwdist.log("刷怪11111")
	for i = 1, WaveMonsCount do
		self.SModDungeonScript:CreateTimer(i,"OntimerSpawnMons")
	end
	self.SModDungeonScript:CreateTimer(WaveMonsCount,"OntimerSpawnMons_add")	--额外刷怪
	self.Wavenum = self.Wavenum + 1
-- pwdist.log("刷怪11111end")
end
function CurrentDungeonScript:OntimerSpawnMons()
-- pwdist.log("刷怪22222")
	for k , v in pairs(self.MonsVsTower) do
		for i , j in pairs(v.MonsterT) do
			--local monscount = math.ceil(self.Wavenum / 10)
			--for m = 1,monscount do
				local npc = self.SModCommon:SpawnMonsterAt(v.MonsterPos,{1,0,0},j)
				npc:ChangeFaction(v.MonsterFac)
			--end	
		end
	end
-- pwdist.log("刷怪22222end")
end
--额外刷怪
function CurrentDungeonScript:OntimerSpawnMons_add()
-- pwdist.log("额外刷怪")
	if self.TeamsTable[self.RTeamId]["addmons"] ~= 0 then	--红方加小怪
		for m = 1,self.TeamsTable[self.RTeamId]["addmons"] do
			self.SModDungeonScript:CreateTimer(m,"OntimerSpawnMons_AddR")
		end
		self.TeamsTable[self.RTeamId]["addmons"] = 0	--清空红方额外刷怪
	elseif self.TeamsTable[self.BTeamId]["addmons"] ~= 0 then	--蓝方加小怪
		for m = 1,self.TeamsTable[self.BTeamId]["addmons"] do
			self.SModDungeonScript:CreateTimer(m,"OntimerSpawnMons_AddB")
		end
		self.TeamsTable[self.BTeamId]["addmons"] = 0	--清空蓝方额外刷怪
	end
-- pwdist.log("额外刷怪end")
end
--额外刷怪，红方
function CurrentDungeonScript:OntimerSpawnMons_AddR()
-- pwdist.log("红方额外刷怪")
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
-- pwdist.log("红方额外刷怪end")	
end
--额外刷怪，蓝方
function CurrentDungeonScript:OntimerSpawnMons_AddB()
-- pwdist.log("蓝方额外刷怪")
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
-- pwdist.log("蓝方额外刷怪end")
end

--结束 
function CurrentDungeonScript:EndedCompete()
-- pwdist.log("结束")
	self.SModLogicBattle:CloseFillMember()
	if self.HasFinishCompete == true then
		return
	end
	if(self.spawnmons_cycle ~=nil)then
		self.SModDungeonScript:CancelTimer(self.spawnmons_cycle)	--取消刷怪计时器
	end
	
	--self.SModDungeonScript:CancelTimer(self.timer_updatemap)	--取消刷新地图计时器
	if(self.mons_vs_tower ~=nil)then
		self.SModDungeonScript:CancelTimer(self.mons_vs_tower)	--取消循环控制小怪走向塔
	end
	if(self.timer_upklist~=nil)then
		self.SModDungeonScript:CancelTimer(self.timer_upklist)	--取消排行榜刷新
	end
	
	 
	 
	--删除所有小怪
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k , v in pairs(CreatureTab) do
		if v:GetFaction() == B_Faction_npc or v:GetFaction() == R_Faction_npc then
			v:LeaveWorld(0)
		end	
	end
	
    
    local humans = self.Stage:GetModObjs():GetHumans()
	--复活所有死亡玩家
	for k , v in pairs(humans) do
		if v:IsDead() then
			v:GetModRealive():Realive(v:GetPosition(), 1)
		end
	end	
	--发送各个玩家积分情况
	for k , v in pairs(self.TeamMembersTable) do
		for i , j in pairs(v) do
			self.SModLogicBattle:AddBattleScore(i,j.kill_hum,j.kill_npc,j.get_buff,j.be_killed)
		end
	end
	--发结束消息
	self.SModLogicBattle:EndedBattle(self.WinTeamId,self.LoseTeamId)
	
	
	-- 复活所有人，恢复阵营
	self:CleanCompete()
	
	-- 进入关闭倒计时
	self.SModDungeonScript:CreateTimer(20,"CloseCompete")
	--self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(20))
	self.HasFinishCompete = true
-- pwdist.log("结束end")	
end

function CurrentDungeonScript:AbortCompete()
-- pwdist.log("关闭倒计时")
	self.SModLogicBattle:CloseFillMember()
	self.SModLogicBattle:AbortBattle()
	-- 进入关闭倒计时
	self.SModDungeonScript:CreateTimer(60,"CloseCompete")
-- pwdist.log("关闭倒计时end")
end

function CurrentDungeonScript:CloseCompete()
-- pwdist.log("关闭竞争")
	local humans = self.Stage:GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		self.SModLogicBattle:LeaveBattle(v:GetID())
	end
-- pwdist.log("关闭竞争end")
end

function CurrentDungeonScript:CleanCompete()
-- pwdist.log("清理竞争")
	local humans = GetCurrentStage():GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		v:ChangeFaction(FactionType.Human)
		v:GetModLansquenet():ChangeLansFaction()---改变侍从阵营
		if v:IsDead() then
			v:GetModRealive():Realive(v:GetPosition(), 1)
		end
	end
-- pwdist.log("清理竞争end")
end

--基地被摧毁
function CurrentDungeonScript:EncampmentKilled_R(creature,killer)
-- pwdist.log("红方基地死亡")
	self.R_towercount = self.R_towercount - 1
	self.SModLogicBattle:UpdateBattleInfo(self.RTeamId,self.R_towercount)
	
	self.Stage:SetAIEnable(false)	--关闭地图AI
	self.WinTeamId = self.BTeamId
	self.LoseTeamId = self.RTeamId
	self.SModCommon:SpawnMonsterAt(R_Encampment_POS,{1,0,0},Dest_encamR)
	self:EndedCompete()
-- pwdist.log("红方基地死亡end")
end
function CurrentDungeonScript:EncampmentKilled_B(creature,killer)
-- pwdist.log("蓝方基地死亡")
	self.B_towercount = self.B_towercount - 1 
	self.SModLogicBattle:UpdateBattleInfo(self.BTeamId,self.B_towercount)
	
	self.Stage:SetAIEnable(false)	--关闭地图AI
	self.WinTeamId = self.RTeamId
	self.LoseTeamId = self.BTeamId
	self.SModCommon:SpawnMonsterAt(B_Encampment_POS,{1,0,0},Dest_encamB)
	self:EndedCompete()
-- pwdist.log("蓝方基地死亡end")
end

--25分钟后提醒新规则，30分钟结束战斗
function CurrentDungeonScript:OnTimer_gameoverhint()
-- pwdist.log("25分钟后提醒新规则，30分钟结束战斗")
	self.SModObjs:BroadcastNotifyWithFaction(100520,ChannelType.Announcement,2,R_Faction_human)
	self.SModObjs:BroadcastNotifyWithFaction(100520,ChannelType.Announcement,2,B_Faction_human)
-- pwdist.log("25分钟后提醒新规则，30分钟结束战斗end")
end

--30分钟后战斗结束
function CurrentDungeonScript:OnTimer_gameover()
-- pwdist.log("30分钟后战斗结束")
	if self.R_towercount < self.B_towercount then
		self.Stage:SetAIEnable(false)	--关闭地图AI
		self.WinTeamId = self.BTeamId
		self.LoseTeamId = self.RTeamId
		self:EndedCompete()
	elseif self.B_towercount < self.R_towercount then
		self.Stage:SetAIEnable(false)	--关闭地图AI
		self.WinTeamId = self.RTeamId
		self.LoseTeamId = self.BTeamId
		self:EndedCompete()
	else
		self.timercut_gameover = self.SModDungeonScript:CreatePeriodTimer(1,1,-1,"OnTimerCut_gameover")	--塔数相同，等少的一方出现就结束
		self.SModObjs:BroadcastNotifyWithFaction(100521,ChannelType.Announcement,2,R_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(100521,ChannelType.Announcement,2,B_Faction_human)
	end
-- pwdist.log("30分钟后战斗结束end")
end
--塔数相同，等少的一方出现就结束
function CurrentDungeonScript:OnTimerCut_gameover()
-- pwdist.log("塔数相同，等少的一方出现就结束")
	if self.R_towercount < self.B_towercount then
		self.Stage:SetAIEnable(false)	--关闭地图AI
		self.WinTeamId = self.BTeamId
		self.LoseTeamId = self.RTeamId
		self:EndedCompete()
		self.SModDungeonScript:CancelTimer(self.timercut_gameover)	--取消统计塔数的倒计时
	elseif self.B_towercount < self.R_towercount then
		self.Stage:SetAIEnable(false)	--关闭地图AI
		self.WinTeamId = self.RTeamId
		self.LoseTeamId = self.BTeamId
		self:EndedCompete()
		self.SModDungeonScript:CancelTimer(self.timercut_gameover)	--取消统计塔数的倒计时
	end
-- pwdist.log("塔数相同，等少的一方出现就结束end")
end

--NPC出生后朝对方塔、基地走
function CurrentDungeonScript:NpcSpawn_fight(Mcreature)
	local creature = Mcreature:cast('Creature')
--pwdist.log("NPC出生后朝对方塔、基地走")
	local MonsId = creature:GetCreatureType()
	for k , v in pairs(self.MonsVsTower) do
		for i , j in pairs(v.MonsterT) do
			if MonsId == j then
				if v.Obj1.live == 1 then
-- pwdist.log("NPC出生后朝对方塔、基地走1======="..tostring(v.Obj1.pos[1]).."  "..tostring(v.Obj1.pos[2]).."  "..tostring(v.Obj1.pos[3]))
					creature:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)				
-- pwdist.log("NPC出生后朝对方塔、基地走2")
				elseif v.Obj1.live == 0 and v.Obj2.live == 1 then
					creature:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
-- pwdist.log("NPC出生后朝对方塔、基地走3")
				elseif v.Obj1.live == 0 and v.Obj2.live == 0 and v.Obj3.live == 1 then
-- pwdist.log("NPC出生后朝对方塔、基地走4")
					creature:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
-- pwdist.log("NPC出生后朝对方塔、基地走5")
				elseif v.Obj1.live == 0 and v.Obj2.live == 0 and v.Obj3.live == 0 and v.Obj4.live == 1 then
-- pwdist.log("NPC出生后朝对方塔、基地走6")
				--虽然小兵是按顺序攻击，不过每次都判断前面塔死亡，再判断后面
				--因为担心有的大R会越过前面塔之间干后面的 o(╯□╰)o
					creature:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
				else
-- pwdist.log("NPC出生后朝对方塔、基地走7")
					creature:LeaveWorld(0)
				end
				return
			end
		end
	end	
-- pwdist.log("NPC出生后朝对方塔、基地走end")
end

--循环计时器，NPC朝塔走
function CurrentDungeonScript:OnTimer_mons_vs_tower()
-- pwdist.log("循环计时器，NPC朝塔走")
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for m , n in pairs(CreatureTab) do
		if n:GetFaction() == B_Faction_npc or n:GetFaction() == R_Faction_npc then
			if n:GetBitEx(1) == 0 and not n:IsDead() then	--不在移动中
				local MonsId = n:GetCreatureType()
				for k , v in pairs(self.MonsVsTower) do
					for i , j in pairs(v.MonsterT) do
						if MonsId == j then
							if v.Obj1.live == 1 then
								if not n:GetModAura():Exists(WayBuff) then
									-- pwdist.log("我要往中跑啦==========")
									n:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
								else
									-- pwdist.log("我要往塔跑")
									n:GetModMotionMaster():NavigatePositionEx(v.Obj1.pos,"",1)
								end
							elseif v.Obj1.live == 0 and v.Obj2.live == 1 then
								if not n:GetModAura():Exists(WayBuff) then
									-- pwdist.log("我要往中跑啦")
									n:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
								else				
									-- pwdist.log("我要往塔跑")
									n:GetModMotionMaster():NavigatePositionEx(v.Obj2.pos,"",1)
								end
							elseif v.Obj1.live == 0 and v.Obj2.live == 0 and v.Obj3.live == 1 then
								if not n:GetModAura():Exists(WayBuff) then
									-- pwdist.log("我要往中跑啦")
									n:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
								else
									-- pwdist.log("我要往塔跑")
									n:GetModMotionMaster():NavigatePositionEx(v.Obj3.pos,"",1)
								end
							elseif v.Obj1.live == 0 and v.Obj2.live == 0 and v.Obj3.live == 0 and v.Obj4.live == 1 then
							--虽然小兵是按顺序攻击，不过每次都判断前面塔死亡，再判断后面
							--因为担心有的大R会越过前面塔之间干后面的 o(╯□╰)o
								if not n:GetModAura():Exists(WayBuff) then
									-- pwdist.log("我要往中跑啦")
									n:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
								else			
									-- pwdist.log("我要往塔跑")
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
-- pwdist.log("循环计时器，NPC朝塔走end")
end

--NPC被杀，统计给玩家得分
function CurrentDungeonScript:NpcKilled_forScore(creature,killer)
-- pwdist.log("NPC被杀，统计给玩家得分")
	--给击杀者计算杀怪数
	if killer and killer:IsKindOf(CLSID.Human) then 
		local human= killer:cast("Human")
		local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
		local hid = tostring(human:GetID())
		self.TeamMembersTable[tid][hid]["kill_npc"] = self.TeamMembersTable[tid][hid]["kill_npc"] + 1
	end
	--[[更新地图信息
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
-- pwdist.log("NPC被杀，统计给玩家得分end")
end


--机关塔被摧毁后标记状态
function CurrentDungeonScript:Tower_Killed(creature,killer)
-- pwdist.log("机关塔被摧毁后标记状态")
	local TowerId = creature:GetCreatureType()
	for k , v in pairs(self.MonsVsTower) do 
		if TowerId == v.Obj1.id then	--假如摧毁的是1号塔
			--种一个新模型，被破坏的塔
			self.SModCommon:SpawnMonsterAt(v.Obj1.pos,{1,0,0},v.Obj1.destid)
			
			v.Obj1.live = 0 	--1号塔状态修改
			--删除2号塔的无敌BUFF
			local TowerTab_s = self.Stage:GetModAOI():CollectCreatureInStage(v.Obj2.id)
			TowerTab_s[1]:GetModAura():Delete(Aura_wudi)
			if v.Obj2.live == 1 then	--2号塔还在
				local CreatureTab = {}
				for m , n in pairs(v.MonsterT) do
					local CreatureTab_s = self.Stage:GetModAOI():CollectCreatureInStage(n)
					for q , s in pairs(CreatureTab_s) do
						table.insert(CreatureTab,s)	--获取已经刷新的对应小怪
					end
				end
				for i , j in pairs(CreatureTab) do
					if not j:IsDead() then
						if not j:GetModAura():Exists(WayBuff) then
							j:GetModMotionMaster():NavigatePositionEx(v.MonsterWay,"",1)
						else
							j:GetModMotionMaster():NavigatePositionEx(v.Obj2.pos,"",1)	--改变寻路状态，去2号塔
						end
						
					end
				end
			elseif v.Obj2.live == 0 and v.Obj3.live == 1 then	--2号塔不再，3号塔还在
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
							j:GetModMotionMaster():NavigatePositionEx(v.Obj3.pos,"",1)	--攻击3号塔
						end
					end
				end
			elseif v.Obj2.live == 0 and v.Obj3.live == 0 and v.Obj4.live == 1 then	--2,3号塔不再，基地还在
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
							j:GetModMotionMaster():NavigatePositionEx(v.Obj4.pos,"",1)	--攻击基地
						end
					end
				end
			end
		elseif TowerId == v.Obj2.id then	--如果摧毁的是2号塔
			--种一个新模型，被破坏的塔
			self.SModCommon:SpawnMonsterAt(v.Obj2.pos,{1,0,0},v.Obj2.destid)
			v.Obj2.live = 0 	--修改状态
			--删除3号塔的无敌BUFF
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
		elseif TowerId == v.Obj3.id then	--如果摧毁的是3号塔
			--种一个新模型，被破坏的塔
			self.SModCommon:SpawnMonsterAt(v.Obj3.pos,{1,0,0},v.Obj2.destid)			
			v.Obj3.live = 0 	--修改状态
			--删除基地的无敌BUFF
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
	--播放广播
	for k , v in pairs(self.MonsVsTower) do 
		if TowerId == v.Obj1.id or TowerId == v.Obj2.id or TowerId == v.Obj3.id  then 		
			if k == 1 or k == 4 then
-- pwdist.log("上路被攻击")
				if v.Obj1.fac == R_Faction_tower then
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled1,ChannelType.Announcement,2,R_Faction_human)
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled3,ChannelType.Announcement,2,B_Faction_human)
				else
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled1,ChannelType.Announcement,2,B_Faction_human)
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled3,ChannelType.Announcement,2,R_Faction_human)
				end	
			elseif k == 2 or k == 5 then
-- pwdist.log("下路被攻击")
				if v.Obj1.fac == R_Faction_tower then
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled2,ChannelType.Announcement,2,R_Faction_human)
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled4,ChannelType.Announcement,2,B_Faction_human)
				else
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled2,ChannelType.Announcement,2,B_Faction_human)
					self.SModObjs:BroadcastNotifyWithFaction(Str_TowerKilled4,ChannelType.Announcement,2,R_Faction_human)
				end
			else
-- pwdist.log("中路被攻击")
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
	--更新地图信息
	self:UpdateUnitinfo(creature)
	self.SModLogicBattle:CommitMapInfoUpdate()
	
	--通知服务器塔的数量变更
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
-- pwdist.log("机关塔被摧毁后标记状态end")
end

--BUFF点刷BUFF球
function CurrentDungeonScript:Pos1_SpawnBuff()
-- pwdist.log("BUFF点刷BUFF球111111")
	local rand = math.random(1,3)
	if rand == 1 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos1,{1,0,0},Buff_IdTable.id1,2,"OnTouchSt_pos1_id1")
	elseif rand == 2 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos1,{1,0,0},Buff_IdTable.id2,2,"OnTouchSt_pos1_id2")
	else
		self.Stage:CreateStaticObject(Buff_PosTable.pos1,{1,0,0},Buff_IdTable.id3,2,"OnTouchSt_pos1_id3")
	end
-- pwdist.log("BUFF点刷BUFF球11111end")
end
function CurrentDungeonScript:Pos2_SpawnBuff()
-- pwdist.log("BUFF点刷BUFF球2222222")
	local rand = math.random(1,3)
	if rand == 1 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos2,{1,0,0},Buff_IdTable.id1,2,"OnTouchSt_pos2_id1")
	elseif rand == 2 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos2,{1,0,0},Buff_IdTable.id2,2,"OnTouchSt_pos2_id2")
	else
		self.Stage:CreateStaticObject(Buff_PosTable.pos2,{1,0,0},Buff_IdTable.id3,2,"OnTouchSt_pos2_id3")
	end
-- pwdist.log("BUFF点刷BUFF球2222222end")
end
function CurrentDungeonScript:Pos3_SpawnBuff()
-- pwdist.log("BUFF点刷BUFF球333333333333332")
	local rand = math.random(1,3)
	if rand == 1 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos3,{1,0,0},Buff_IdTable.id1,2,"OnTouchSt_pos3_id1")
	elseif rand == 2 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos3,{1,0,0},Buff_IdTable.id2,2,"OnTouchSt_pos3_id2")
	else
		self.Stage:CreateStaticObject(Buff_PosTable.pos3,{1,0,0},Buff_IdTable.id3,2,"OnTouchSt_pos3_id3")
	end
-- pwdist.log("BUFF点刷BUFF球33333333333333end")
end
function CurrentDungeonScript:Pos4_SpawnBuff()
-- pwdist.log("BUFF点刷BUFF球444444444444444444")
	local rand = math.random(1,3)
	if rand == 1 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos4,{1,0,0},Buff_IdTable.id1,2,"OnTouchSt_pos4_id1")
	elseif rand == 2 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos4,{1,0,0},Buff_IdTable.id2,2,"OnTouchSt_pos4_id2")
	else
		self.Stage:CreateStaticObject(Buff_PosTable.pos4,{1,0,0},Buff_IdTable.id3,2,"OnTouchSt_pos4_id3")
	end
-- pwdist.log("BUFF点刷BUFF球444444444444444444end")
end
function CurrentDungeonScript:Pos5_SpawnBuff()
-- pwdist.log("BUFF点刷BUFF球555555555555555555")
	local rand = math.random(1,3)
	if rand == 1 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos5,{1,0,0},Buff_IdTable.id1,2,"OnTouchSt_pos5_id1")
	elseif rand == 2 then
		self.Stage:CreateStaticObject(Buff_PosTable.pos5,{1,0,0},Buff_IdTable.id2,2,"OnTouchSt_pos5_id2")
	else
		self.Stage:CreateStaticObject(Buff_PosTable.pos5,{1,0,0},Buff_IdTable.id3,2,"OnTouchSt_pos5_id3")
	end
-- pwdist.log("BUFF点刷BUFF球555555555555555555end")
end



--BUFF球触摸函数
--pos1
function CurrentDungeonScript:OnTimer_SpawnBuff_pos1()
-- pwdist.log("BUFF球触摸函数1111111111111")
	self:Pos1_SpawnBuff()
-- pwdist.log("BUFF球触摸函数1111111111111end")
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

--BUFF球效果，加速度
function CurrentDungeonScript:Buff_addspeed(human)
-- pwdist.log("BUFF球效果，加速度")
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
	--播报消息
	if human:GetFaction() == R_Faction_human then
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_speed1,ChannelType.Announcement,2,R_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_speed2,ChannelType.Announcement,2,B_Faction_human)
	else
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_speed1,ChannelType.Announcement,2,B_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_speed2,ChannelType.Announcement,2,R_Faction_human)
	end
end


--BUFF球效果，加血
function CurrentDungeonScript:Buff_addblood(human)
-- pwdist.log("BUFF球效果，加血")
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
	--播报消息
	if human:GetFaction() == R_Faction_human then
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_blood1,ChannelType.Announcement,2,R_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_blood2,ChannelType.Announcement,2,B_Faction_human)
	else
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_blood1,ChannelType.Announcement,2,B_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_blood2,ChannelType.Announcement,2,R_Faction_human)
	end
end

--BUFF球效果，加刷怪
function CurrentDungeonScript:Buff_addmons(human)
-- pwdist.log("BUFF球效果，加刷怪")
	local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
	self.TeamsTable[tid]["addmons"] = self.TeamsTable[tid]["addmons"] + BUFF_addmons_num
	
	--播报消息
	if human:GetFaction() == R_Faction_human then
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_addnum1,ChannelType.Announcement,2,R_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_addnum2,ChannelType.Announcement,2,B_Faction_human)
	else
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_addnum1,ChannelType.Announcement,2,B_Faction_human)
		self.SModObjs:BroadcastNotifyWithFaction(Str_getbuff_addnum2,ChannelType.Announcement,2,R_Faction_human)
	end
end

--BUFF球触摸后，给触摸的玩家加一个计数
function CurrentDungeonScript:AddScore_buffnum(target)
-- pwdist.log("BUFF球触摸后，给触摸的玩家加一个计数")
	if target:IsKindOf(CLSID.Human) then 
		local human= target:cast("Human")
		local tid = tostring(self.SModLogicBattle:GetBattleTeam(human:GetID()))
		local hid = tostring(human:GetID())
		self.TeamMembersTable[tid][hid]["get_buff"] = self.TeamMembersTable[tid][hid]["get_buff"] + 1
	end
end

--逻辑函数，执行unit对象地图信息获取更新
function CurrentDungeonScript:UpdateUnitinfo(creature)
-- pwdist.log("逻辑函数，执行unit对象地图信息获取更新")
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



--更新小地图信息
function CurrentDungeonScript:UpdateMapInfo()
-- pwdist.log("更新小地图信息")
	--更新塔
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
	--更新水晶BUFF
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

--根据一个水晶BUFF对象，判断该水晶所属、UID、类型、状态
function CurrentDungeonScript:GetBuffInfo(obj)
-- pwdist.log("根据一个水晶BUFF对象，判断该水晶所属、UID、类型、状态")
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
-- pwdist.log("根据一个水晶BUFF对象，判断该水晶所属、UID、类型、状态end")
	return hid,typeobj,state,dir
end

--根据一个怪物对象，判断该怪物所属队伍、UID、类型
function CurrentDungeonScript:GetMonsterInfo(creature)
-- pwdist.log("根据一个怪物对象，判断该怪物所属队伍、UID、类型")
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
