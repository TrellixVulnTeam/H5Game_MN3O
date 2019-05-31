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

local Quest_NPC = {NpcID = {},Quest = {},QuestData = {},}-----单个的NPC和怪物杀了碰一下就能完成任务
Quest_NPC.NpcID[1] = 10003
Quest_NPC.Quest[1] = {1002,1127,1128,}	-------赶走面首 任务ID,可能会分职业，所以用表
Quest_NPC.QuestData[1] = {}				-------储存的数据表

Quest_NPC.NpcID[2] = 10005
Quest_NPC.Quest[2] = {1005,}			-------横行侍卫 任务ID,可能会分职业，所以用表
Quest_NPC.QuestData[2] = {}				-------储存的数据表

Quest_NPC.NpcID[3] = 10007
Quest_NPC.Quest[3] = {1007,}			-------赶走柳色 任务ID,可能会分职业，所以用表
Quest_NPC.QuestData[3] = {}				-------储存的数据表

Quest_NPC.NpcID[4] = 10013
Quest_NPC.Quest[4] = {1044,}			-------挑战花错 任务ID,可能会分职业，所以用表
Quest_NPC.QuestData[4] = {}				-------储存的数据表

Quest_NPC.NpcID[5] = 10087
Quest_NPC.Quest[5] = {1038,}			-------消失无踪 任务ID,可能会分职业，所以用表
Quest_NPC.QuestData[5] = {}				-------储存的数据表

Quest_NPC.NpcID[6] = 10030
Quest_NPC.Quest[6] = {1056,}			-------较量任务 ID,可能会分职业，所以用表
Quest_NPC.QuestData[6] = {}				-------储存的数据表

Quest_NPC.NpcID[7] = 10036
Quest_NPC.Quest[7] = {1066,}			-------劫持方丈 任务ID,可能会分职业，所以用表
Quest_NPC.QuestData[7] = {}				-------储存的数据表

Quest_NPC.NpcID[8] = 10044
Quest_NPC.Quest[8] = {1077,}			-------劫持首领 任务ID,可能会分职业，所以用表
Quest_NPC.QuestData[8] = {}				-------储存的数据表

Quest_NPC.NpcID[9] = 10057
Quest_NPC.Quest[9] = {1095,}			-------惩戒道士 任务ID,可能会分职业，所以用表
Quest_NPC.QuestData[9] = {}				-------储存的数据表

Quest_NPC.NpcID[10] = 10078
Quest_NPC.Quest[10] = {1101,}			-------逼供道士 任务ID,可能会分职业，所以用表
Quest_NPC.QuestData[10] = {}				-------储存的数据表

Quest_NPC.NpcID[11] = 10064
Quest_NPC.Quest[11] = {1104,}			-------受蛊男子 任务ID,可能会分职业，所以用表
Quest_NPC.QuestData[11] = {}			-------储存的数据表

Quest_NPC.NpcID[12] = 10072
Quest_NPC.Quest[12] = {1115,}			-------柳色受蛊 任务ID,可能会分职业，所以用表
Quest_NPC.QuestData[12] = {}			-------储存的数据表

Quest_NPC.NpcID[13] = 10075
Quest_NPC.Quest[13] = {1118,}			-------惩戒女子 任务ID,可能会分职业，所以用表
Quest_NPC.QuestData[13] = {}			-------储存的数据表

------------------------下面一段是梦境用

--刷任务怪和任务NPC
local Boss1EnterPos 		= {89.35,51.22,195.74}
local Boss1EnterOra 		= {1.0,0.0,0.0}	
local Boss1ID = 10121

local Boss2EnterPos 		= {92.65,51.22,189.72}    --boss出生点位置
local Boss2EnterOra 		= {1.0,0.0,0.0}		     --boss出生点朝向
local Boss2ID = 10122



local HumPos 		= {92.65,54.31,220.6}      ---离开梦境传送位置
local HumPos1 		= {92.61,54.31,220.6}

local MengQuestID = {1144,1146,1147,}--------------梦境区域标识任务

------------------------------------------------------------------
-----梦境区域信息
local Dream = {Pos = {},PosX = {},PosZ = {},ID= {},TriggerEnter = {},}
Dream.Pos[1] =	{92.8,51.31,195.06}
Dream.PosX[1] = 18
Dream.PosZ[1] = 18
Dream.ID[1] = 10693 ---NPCID

--[[Dream.Pos[2] =	{369.71,56.79,364.16}
Dream.PosX[2] = 60
Dream.PosZ[2] = 23
Dream.ID[2] = 10693 ---NPCID--]]

Dream.TriggerEnter[1] = {}-----创建的计时器数据储存变量
local Humdata = {}
--Dream.Monster[Dream.Humdata[i]] = {}
local Monster = {}

local DreamStrID = {104500,}    ---组队状态进梦境提示

local PoltConfig = {3,4,5,}     -----预加载剧情

local QuestID = {1101,1105}  -----接取任务会给加速BUFF

local SpeedBuff = 10041050       -----加速BUFF

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript() 
	self.SModCommon = self.Stage:GetModCommon()	
	self.SModObjs = self.Stage:GetModObjs()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanResurrect,"HumanResurrect")
	
	SetEventHandler(StageEvents.UseTreasure,"OnUseTreasure")----挖宝触发的场景事件	
	
	--------------只有一个怪的任务
	for k = 1, table.getn(Quest_NPC.NpcID) do
		SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHit",{type = Quest_NPC.NpcID[k]})
	end
	for m = 1, table.getn(Quest_NPC.NpcID) do
		SetEventHandler(StageEvents.CreatureKilled,"OnCreatureKilled",{type = Quest_NPC.NpcID[m]})
	end	
--屏蔽梦境
	SetEventHandler(StageEvents.QuestLeaveDream,"QuestLeaveDream")----监视玩家点离开按钮	
--监视梦境区域
	self.Stage:CreateTriggerRect(Dream.Pos[1],Dream.PosX[1],Dream.PosZ[1],"OnTriggerEnter_Dream","OnTriggerLeave_Dream")
	--self.Stage:CreateTriggerRect(Dream.Pos[2],Dream.PosX[2],Dream.PosZ[2],"OnTriggerEnter_Dream","OnTriggerLeave_Dream")

-----监视接取任务给予加速
	for i = 1,#QuestID, 1 do
		SetEventHandler(StageEvents.QuestAccepted,"Quest_Accepted",{id = QuestID[i]})
	end
end

------任务接取加速
function CurrentDungeonScript:Quest_Accepted(Qhuman,questid)
	--增加BUFF
	local humanquest = Qhuman:cast('Human')
	humanquest:GetModAura():Create(SpeedBuff) --加个BUFF
	--pwdist.log("获得加速BUFF")
end


function CurrentDungeonScript:HumanEnterEvent(human)
	if(human == nil)then
		return
	end
	local HuMan= human:cast('Human')	
	local HLevel = HuMan:GetLevel()	----取不到玩家的任务状态
	if(HLevel == nil)then
		return
	end
	local HumID = HuMan:GetID()
	if(HumID == nil)then
		return
	end
-----预加载剧情
	self.ModMisc = HuMan:GetModMisc()
	if(HLevel <= 30)then	----刚进入场景没法取到任务状态，只能用等级了没辙
		for i = 1 ,table.getn(PoltConfig) do
			if(PoltConfig[i] ~= nil)then
				self.ModMisc:PrelaodPolts(PoltConfig[i])
				--pwdist.log('加载剧本动画')
			else
				return
			end
		end
	end	
	human:GetModCombat():SetPkmode(0,0)-----为防止设置玩家PK模式的时出错，在这里单加了一行
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

-- ---------野外场景精英怪被攻击事件---------------
function CurrentDungeonScript:CreatureMagicHit(caster,creaturer)	--场景怪物打击触发
	if caster:IsKindOf(CLSID.Human) then			------判断是不是玩家
		local humankill = caster:cast('Human')
		if(humankill ~= nil and creaturer ~= nil)then
			for k = 1, #Quest_NPC.NpcID,1 do	-------看有多少个怪需要做脚本判断
				for m = 1, #Quest_NPC.Quest[k],1 do	-------看需要杀这个怪的任务有几个
					if(humankill:GetModQuest():GetQuestStatus(Quest_NPC.Quest[k][m]) == 2 ) then	----判断玩家身上是否需要脚本完成的任务
						local Mcreature = creaturer:cast('Creature')
						local MonterTypeID = Mcreature:GetCreatureType()
						if(MonterTypeID == Quest_NPC.NpcID[k]) then					
							table.insert(Quest_NPC.QuestData[k],humankill)
						end
					end
				end
			end
		end
	end

end
-- ---------野外场景精英怪死亡---------------
function CurrentDungeonScript:OnCreatureKilled(Lcreature,killer)
	if(Lcreature ~= nil)then
		local Mcreature = Lcreature:cast('Creature')
		if(Mcreature~=nil)then
			local MonterTypeID = Mcreature:GetCreatureType()
			for k = 1, #Quest_NPC.NpcID,1 do		----#Quest_NPC.NpcID确认长度
				for m = 1, #Quest_NPC.QuestData[k],1 do	----#Quest_NPC.QuestData[k]确认存储了玩家的长度
					local humankill = Quest_NPC.QuestData[k][m]:cast('Human')
					if(humankill~=nil)then
						if(Quest_NPC.NpcID[k] == MonterTypeID) then	
							for n = 1, #Quest_NPC.Quest[k],1 do
								if (humankill:GetModQuest():GetQuestStatus(Quest_NPC.Quest[k][n]) == 2) then
									humankill:GetModQuest():DoneQuest(Quest_NPC.Quest[k][n])
								end
							end
						end
					end
				end
				Quest_NPC.QuestData[k] = {}
			end
		end
	end
end


----梦境相关


function CurrentDungeonScript:QuestLeaveDream(human)       --点击离开按钮
	human:GetModStatistic():SetViewTag(0)   ----去掉人的标识 6.26
    human:GetModMotionMaster():ChangePosition(HumPos)	
	human:GetModMotionMaster():MovePosition(HumPos1,"")	
end

--玩家进出梦境区域
function CurrentDungeonScript:OnTriggerEnter_Dream(trigger,target)
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

	if Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[3]) == 4    then     --有任务 单人-----控制是否刷出梦境怪 ，检查梦境后续任务是否是 0未接受状态 如果是就刷怪
		return					
		--pwdist.log('已完成梦境任务return')
	end	


	if Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 4     and  (tostring(Gamerteam) == tostring(0) )   then     --有任务 单人-----控制是否刷出梦境怪 ，检查梦境后续任务是否是 0未接受状态 如果是就刷怪
		--pwdist.log('刷怪=====1111111111111')
		Gamercreature:GetModQuest():EnterDream()
		target:ChangeFaction(13)   ---把玩家的阵营置成13
		Gamercreature:GetModLansquenet():ChangeLansFaction()    ----把玩家的侍从阵营设置成13
		-----刷怪
		--pwdist.log('刷怪=====')
		local monster1 = self.SModCommon:SpawnMonsterAtInViewTag(Boss1EnterPos, Boss1EnterOra, Boss1ID, GamerId )
		table.insert(Monster[GamerId],monster1)
		local monster2 = self.SModCommon:SpawnMonsterAtInViewTag(Boss2EnterPos, Boss2EnterOra, Boss2ID, GamerId )
		table.insert(Monster[GamerId],monster2)
		
		--pwdist.log('刷怪=====end')
	elseif Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[3]) == 4 and	(tostring(Gamerteam) > tostring(0) ) then		--	没任务组队状态
		return		
	elseif Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 4 and (tostring(Gamerteam) > tostring(0) ) then		--  有任务组队状态		
		target:SendNotifyMsgTo(DreamStrID[1] ,CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(2617))
		return					
	end	
	
	
end

function CurrentDungeonScript:OnTriggerLeave_Dream(trigger,target)
--pwdist.log('离开区域')
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
		--pwdist.log('去掉标识了')
	end
	----Gamercreature:GetModQuest():LeaveDream()
	if(Monster[GamerId] ~= nil and #Monster[GamerId] > 0) then
			for k = 1, table.getn(Monster[GamerId]) do
				--pwdist.log('开始删除怪物==='..tostring(Monster[GamerId][k]))
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
