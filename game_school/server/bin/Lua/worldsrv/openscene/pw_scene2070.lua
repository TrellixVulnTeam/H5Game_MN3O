CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
pwngs_require("./Lua/worldsrv/activities/pw_activity_wabao.lua")
-----------------------------------------------------------
----下面一段是野外BOSS用
-----野外BOSS 活跃度计数  **如果换BOSS了或者换位置了需要跟着换
local WorldBossID = {46025,46026,46027,46028,46029,46030,46031,46032,46033,46034,46035,46036,46037,46038,46039,46040,46041,46042,46043,46044,46045,46046,46047,46048,46049,46050,46051,46052,46053,46054,}
--野外2PK区域坐标，大小,全场景pk模式，不用加
--BOSS死亡提示
local BossID = {45001,45002,45003,45004,45005,45006,45007,45008,45009,45010,45011,45012,45013,45014,45015}----BOSS编号
local StrID = {15001,15002,15003,15004,15005,15006,15007,15008,15009,15010,15011,15012,15013,15014,15015}----BOSS提示

local QuestID = {40000,40001,40002,40003,40004,40005,40006,40007,40008,40009,40010,40011,40012,40013,40014,40015,40016,40017,40018,40019}


function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript() 
	self.SModCommon = self.Stage:GetModCommon()	
	self.SModObjs = self.Stage:GetModObjs()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanResurrect,"HumanResurrect")
	SetEventHandler(StageEvents.HumanKilled,"OnHumanKilled")
		
	SetEventHandler(StageEvents.UseTreasure,"OnUseTreasure")----挖宝触发的场景事件

--监视BOSS死亡
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled1",{type = BossID[1]})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled2",{type = BossID[2]})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled3",{type = BossID[3]})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled4",{type = BossID[4]})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled5",{type = BossID[5]})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled6",{type = BossID[6]})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled7",{type = BossID[7]})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled8",{type = BossID[8]})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled9",{type = BossID[9]})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled10",{type = BossID[10]})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled11",{type = BossID[11]})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled12",{type = BossID[12]})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled13",{type = BossID[13]})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled14",{type = BossID[14]})
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled15",{type = BossID[15]})

	for i = 1,#QuestID, 1 do
		SetEventHandler(StageEvents.QuestCompleted,"Quest_Completed",{id = QuestID[i]})
	end

----监视野外BOSS受击 活跃度计数
	for m = 1,#WorldBossID, 1 do
		SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHit",{type = WorldBossID[m]})
	end

end

------任务完成事件
function CurrentDungeonScript:Quest_Completed(Qhuman,questid)
	--增加活跃度
	local humanquest = Qhuman:cast('Human')
	humanquest:GetModDailyBonus():InjectActivityComplete(26,1)
	--pwdist.log("+一次活跃度")
end


function CurrentDungeonScript:NpcKilled1()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[1]))	
end 
function CurrentDungeonScript:NpcKilled2()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[2]))	
end 
function CurrentDungeonScript:NpcKilled3()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[3]))	
end 
function CurrentDungeonScript:NpcKilled4()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[4]))	
end 
function CurrentDungeonScript:NpcKilled5()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[5]))	
end 
function CurrentDungeonScript:NpcKilled6()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[6]))	
end 
function CurrentDungeonScript:NpcKilled7()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[7]))	
end 
function CurrentDungeonScript:NpcKilled8()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[8]))	
end 
function CurrentDungeonScript:NpcKilled9()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[9]))	
end 
function CurrentDungeonScript:NpcKilled10()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[10]))	
end 
function CurrentDungeonScript:NpcKilled11()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[11]))	
end 
function CurrentDungeonScript:NpcKilled12()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[12]))	
end 
function CurrentDungeonScript:NpcKilled13()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[13]))	
end 
function CurrentDungeonScript:NpcKilled14()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[14]))	
end 
function CurrentDungeonScript:NpcKilled15()
    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[15]))	
end 






function CurrentDungeonScript:HumanEnterEvent(human)
-- pwdist.log("我进入了副本")
	human:GetModCombat():SetPkmode(3,0)
end
function CurrentDungeonScript:HumanLeaveEvent(human)
    --self.Stage:GetModDungeonScript():Cleanup()	--*玩家离开场景清空所有剧情相关逻辑，以免出问题*
-- pwdist.log("我离开了场景")
  human:GetModCombat():SetPkmode(0,0)
	
end
function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
end

-----玩家死亡
function CurrentDungeonScript:OnHumanKilled(human,killer)
	if(killer == nil)then
		return
	end
	if killer:IsKindOf(CLSID.Human) then			------判断是不是玩家
		local humankiller = killer:cast('Human')
		local HLevel = humankiller:GetLevel()	----取玩家的等级
		if(HLevel~=nil and HLevel >= 60)then
			humankiller:AddMilitaryScore(4,BattleGod.YW[1])
		end	
	end	
end

function CurrentDungeonScript:HumanResurrect(human)  
	--这个是临时的，所有的复活都是回到指定复活点
	--human:GetModMotionMaster():ChangePosition(self.ResurrectPos)
end

-- PK区域触发器处理，玩家进出切换PK状态
function CurrentDungeonScript:OnTriggerEnter_PK(trigger,target)
-- pwdist.log("我进入了区域")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK(trigger,target)
-- pwdist.log("我离开了副本区域")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
	end
end



-- 攻击世界BOSS加活跃度
function CurrentDungeonScript:CreatureMagicHit(killer,creature)
	if(killer == nil)then
		return
	end
    if not killer:IsKindOf(CLSID.Human) then
		--pwdist.log("侍从攻击")
        return
    end
	--pwdist.log("确认不为空")
	-- 增加活跃度
	local humankill = killer:cast('Human')
	humankill:GetModDailyBonus():InjectActivityComplete(10,1)
	--pwdist.log("+一次活跃度")
end


-------------------挖宝触发事件-------------------------------
function CurrentDungeonScript:OnUseTreasure(human,itemid)---------玩家对象和使用的道具ID
  math.randomseed(os.time())  --随机种子
  local rand = math.random(10,20)
  rand = math.random(1,100)
  if(rand>0 and rand <=30)then
    self:W_Box(human)
  elseif(rand>30 and rand <=60)then
    self:W_OneMonter(human)
  elseif(rand>60 and rand <=80)then
    self:W_ManyMonter(human)
  elseif(rand>80 and rand <=90)then
    self:W_Dungeon(human)
  else
    self:W_Buff(human)
  end
end

