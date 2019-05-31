CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------

------------------------下面一段是梦境用

--刷任务怪和任务NPC
local Boss1EnterPos 		= {49.6,50,62}
local Boss1EnterOra 		= {1.0,0.0,0.0}	
local Boss1ID = 10119

local Boss2EnterPos 		= {52,50,65}    --boss出生点位置
local Boss2EnterOra 		= {1.0,0.0,0.0}		     --boss出生点朝向
local Boss2ID = 10119

local Boss3EnterPos 		= {52,50,59}
local Boss3EnterOra 		= {1.0,0.0,0.0}		
local Boss3ID = 10119

local HumPos 		= {100.6,51.6,66.7}      ---离开梦境传送位置
local HumPos1 		= {100.6,51.6,66.7}      ---离开梦境传送位置

local MengQuestID = {1398,}--------------梦境区域标识任务
------------------------------------------------------------------
-----梦境区域信息
local Dream = {Pos = {},PosX = {},PosZ = {},ID= {},TriggerEnter = {},}
Dream.Pos[1] =	{53.08,49.83,63.62}
Dream.PosX[1] = 35
Dream.PosZ[1] = 35
Dream.ID[1] = 10693 ---NPCID

Dream.TriggerEnter[1] = {}-----创建的计时器数据储存变量
local Humdata = {}
--Dream.Monster[Dream.Humdata[i]] = {}
local Monster = {}

local DreamStrID = {104500,}    ---组队状态进梦境提示

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript() 
	self.SModCommon = self.Stage:GetModCommon()	
	self.SModObjs = self.Stage:GetModObjs()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanResurrect,"HumanResurrect")

	SetEventHandler(StageEvents.QuestLeaveDream,"QuestLeaveDream")----监视玩家点离开按钮	
-----监视梦境区域
	self.Stage:CreateTriggerRect(Dream.Pos[1],Dream.PosX[1],Dream.PosZ[1],"OnTriggerEnter_Dream","OnTriggerLeave_Dream")


end

function CurrentDungeonScript:HumanEnterEvent(human)

end
function CurrentDungeonScript:HumanLeaveEvent(human)
    --self.Stage:GetModDungeonScript():Cleanup()	--*玩家离开场景清空所有剧情相关逻辑，以免出问题*
end
function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
end

function CurrentDungeonScript:HumanResurrect(human)  
	--这个是临时的，所有的复活都是回到指定复活点
	--human:GetModMotionMaster():ChangePosition(self.ResurrectPos)
end




----梦境相关


function CurrentDungeonScript:QuestLeaveDream(human)       --点击离开按钮
	human:GetModStatistic():SetViewTag(0)   ----去掉人的标识 6.26
    human:GetModMotionMaster():ChangePosition(HumPos)	
	human:GetModMotionMaster():MovePosition(HumPos1,"")	
end

--玩家进出梦境区域
function CurrentDungeonScript:OnTriggerEnter_Dream(trigger,target)
pwdist.log('进入=====')
	----获取玩家ID
    if not target:IsKindOf(CLSID.Human) then --判断进入的是否是人
       return
    end

	local Gamercreature = target:cast('Human')
	local GamerId = 0
	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())
		target:GetModStatistic():SetViewTag(GamerId)   ----给人加个标识 	
	end
	-----存储玩家数据 
	for i = 1,#Dream.ID, 1 do
		table.insert(Humdata,GamerId)
	end	
	-----初始化怪物存储表
	if ( Monster[GamerId] == nil	)  then
		Monster[GamerId] = {}
	end
	local Gamerteam = -1 
    Gamerteam = Gamercreature:GetTeamId()
	if Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 0     and  (tostring(Gamerteam) == tostring(0) )   then     --有任务 单人-----控制是否刷出梦境怪 ，检查梦境后续任务是否是 0未接受状态 如果是就刷怪
		pwdist.log('刷怪=====1111111111111')
		Gamercreature:GetModQuest():EnterDream()
		target:ChangeFaction(13)   ---把玩家的阵营置成13
		Gamercreature:GetModLansquenet():ChangeLansFaction()    ----把玩家的侍从阵营设置成13
	-----刷怪
		pwdist.log('刷怪=====')
		local monster1 = self.SModCommon:SpawnMonsterAtInViewTag(Boss1EnterPos, Boss1EnterOra, Boss1ID, GamerId )
		table.insert(Monster[GamerId],monster1)
		local monster2 = self.SModCommon:SpawnMonsterAtInViewTag(Boss2EnterPos, Boss2EnterOra, Boss2ID, GamerId )
		table.insert(Monster[GamerId],monster2)
		local monster3 = self.SModCommon:SpawnMonsterAtInViewTag(Boss3EnterPos, Boss3EnterOra, Boss3ID, GamerId )
		table.insert(Monster[GamerId],monster3)
		
		local monster4 = self.SModCommon:SpawnMonsterAtInViewTag(Boss1EnterPos, Boss1EnterOra, Boss1ID, GamerId )
		table.insert(Monster[GamerId],monster4)
		local monster5 = self.SModCommon:SpawnMonsterAtInViewTag(Boss2EnterPos, Boss2EnterOra, Boss2ID, GamerId )
		table.insert(Monster[GamerId],monster5)
		local monster6 = self.SModCommon:SpawnMonsterAtInViewTag(Boss3EnterPos, Boss3EnterOra, Boss3ID, GamerId )
		table.insert(Monster[GamerId],monster6)		
		
		local monster7 = self.SModCommon:SpawnMonsterAtInViewTag(Boss1EnterPos, Boss1EnterOra, Boss1ID, GamerId )
		table.insert(Monster[GamerId],monster7)
		local monster8 = self.SModCommon:SpawnMonsterAtInViewTag(Boss2EnterPos, Boss2EnterOra, Boss2ID, GamerId )
		table.insert(Monster[GamerId],monster8)
		local monster9 = self.SModCommon:SpawnMonsterAtInViewTag(Boss3EnterPos, Boss3EnterOra, Boss3ID, GamerId )
		table.insert(Monster[GamerId],monster9)		
		
		local monster10 = self.SModCommon:SpawnMonsterAtInViewTag(Boss3EnterPos, Boss3EnterOra, Boss3ID, GamerId )
		table.insert(Monster[GamerId],monster10)				
		
		
		
		pwdist.log('刷怪=====end')
	elseif Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 4 and	(tostring(Gamerteam) > tostring(0) ) then		--	没任务组队状态
		return		
	elseif Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 0 and 	(tostring(Gamerteam) > tostring(0) ) then		--  有任务组队状态		
		target:SendNotifyMsgTo(DreamStrID[1] ,CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(2617))
		return					
	end	

	
	
end

function CurrentDungeonScript:OnTriggerLeave_Dream(trigger,target)
pwdist.log('离开区域')
	----获取玩家ID
    if not target:IsKindOf(CLSID.Human) then --判断离开的是否是人
        return
    end
	---target:ChangeFaction(1)   ---把玩家的阵营置成正常
	local Gamercreature = target:cast('Human')
	local GamerId = -1
	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())
		target:GetModStatistic():SetViewTag(0)   ----去掉人的标识 6.26
		pwdist.log('去掉标识了')
	end
	----Gamercreature:GetModQuest():LeaveDream()
	if(Monster[GamerId] ~= nil and #Monster[GamerId] > 0) then
			for k = 1, table.getn(Monster[GamerId]) do
				pwdist.log('开始删除怪物==='..tostring(Monster[GamerId][k]))
				local Mcreature = Monster[GamerId][k]:cast('Creature')			
				if Mcreature ~= nil then	
					Mcreature:LeaveWorld(0)
				end
				
			end	
		--Monster[GamerId] = {}---初始化	
		target:ChangeFaction(1)   ---把玩家的阵营置成正常
		Gamercreature:GetModLansquenet():ChangeLansFaction()    ---把玩家侍从的阵营置成正常
		Gamercreature:GetModQuest():LeaveDream()
		Monster[GamerId] = nil
	end	
end

