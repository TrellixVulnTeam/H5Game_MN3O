require "./Lua/worldsrv/dungeon/pw_dungeon_config"

CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------
function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
	self.SModCommon = self.Stage:GetModCommon()
	self.SModObjs = self.Stage:GetModObjs()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	self.DungeonId = self.Stage:GetBaseMapID()
	for k ,v in pairs(DUNGEON_ID) do
		if self.DungeonId == toll(v) then
			self.DungeonConfig = DUNGEON_CONFIG[v]
		end
	end
	if self.DungeonConfig ~= nil then
		--注册NPC死亡事件，针对副本通关的NPC死亡
		if self.DungeonConfig["NpcKilled_CrossDungeon"] ~= nil then
			--pwdist.log(self.DungeonConfig["NpcKilled_CrossDungeon"][1][1])
			self.count_crossdungeon = 0
			for k , v in pairs(self.DungeonConfig["NpcKilled_CrossDungeon"]) do
				SetEventHandler(StageEvents.CreatureKilled,"NpcKilled_CrossDungeon",{type = v[1]})
				self.count_crossdungeon = self.count_crossdungeon + v[2]
				--pwdist.log("v[1]=="..v[1])
				--pwdist.log("v[2]=="..v[2])
			end
		end
		--注册NPC死亡事件，针对副本通关的NPC死亡(这个只处理多种怪物总数固定，但每种怪物不确定数量，随机刷怪)
		if self.DungeonConfig["NpcKilled_CrossDungeonRandom"] ~= nil then
			self.count_crossdungeonRandom = self.DungeonConfig["NpcKilled_CrossDungeonRandom"][2]
			for k , v in pairs(self.DungeonConfig["NpcKilled_CrossDungeonRandom"][1]) do
				SetEventHandler(StageEvents.CreatureKilled,"NpcKilled_CrossDungeonRandom",{type = v})
			end
		end
		---------------------------------------------------------------------------------
		--注册NPC死亡事件，针对按波数一波波杀怪，杀一波刷一波，全部杀完通关。剧情副本用
		if self.DungeonConfig["NpcKilled_CrossDungeonWava"] ~= nil then
			self.jq_corrent_count = self.DungeonConfig["NpcKilled_CrossDungeonWava"][1]["count"]
			self.jq_corrent_maxcount = 0
			for k , v in pairs(self.DungeonConfig["JQ_CrossDungeonNpcid"]) do
				if #v > 0 then
					for i,j in pairs(v) do
						SetEventHandler(StageEvents.CreatureKilled,"NpcKilled_CrossDungeonWava",{type = j})
					end
				end
			end
			self.msg = { targetlist = {} }
			self.msg.timesec = self.DungeonConfig["JQ_DungeonMaxTime"]-----3 * 60	----副本总时长
			if #self.DungeonConfig["JQ_CrossDungeonNpcid"]["bossid"] == 0 then --没有BOSS计数，只算总数
				local dungeon_maxcount = 0
				for k,v in pairs(self.DungeonConfig["NpcKilled_CrossDungeonWava"]) do
					dungeon_maxcount = dungeon_maxcount + v.count
				end
				self.msg.targetlist[1] = 
				{
					type = 1,
					strid = self.DungeonConfig["JQ_DungeonObj"]["monsterstr"],
					count = 0,
					maxcount = dungeon_maxcount,
				}
			else	
				for k ,v in pairs(self.DungeonConfig["JQ_CrossDungeonNpcid"]["bossid"]) do
					self.msg.targetlist[k] = 
					{
						type = 1,
						strid = self.DungeonConfig["JQ_DungeonObj"]["bossstr"][k],
						count = 0,
						maxcount = 1,
					}
				end
			end
		end
		-------------------------------------------------------------------------------------------
		--BOSS死亡杀死召唤的小弟
		if self.DungeonConfig["NpcKilled_KillPet"] ~= nil then
			for k,v in pairs(self.DungeonConfig["NpcKilled_KillPet"]) do
				if self.DungeonConfig["NpcKilled_CrossDungeon"] ~= nil then
					local CrossDungeonTAB = self.DungeonConfig["NpcKilled_CrossDungeon"]
					local sum = #CrossDungeonTAB
					local num = 0
					for i , j in pairs(CrossDungeonTAB) do
						if v ~= j[1] then
							num = num + 1 
							if num == sum then
								SetEventHandler(StageEvents.CreatureKilled,"NpcKilled_KillPet",{type = v})
							end
						end
					end
				else
					SetEventHandler(StageEvents.CreatureKilled,"NpcKilled_KillPet",{type = v})
				end
			end
		end
		--注册NPC死亡事件，针对杀死怪物触发剧情
		if self.DungeonConfig["NpcKilled_PlotStart"] ~= nil then
			self.count_PlotStart = {}
			for k , v in pairs(self.DungeonConfig["NpcKilled_PlotStart"]) do
				self.count_PlotStart[k] = 0
				for i , j in pairs(v[1]) do
					SetEventHandler(StageEvents.CreatureKilled,"NpcKilled_PlotStart",{type = j[1]})
					self.count_PlotStart[k] = self.count_PlotStart[k] + j[2]
				end
			end
		end
	end
end

function CurrentDungeonScript:HumanEnterEvent(human) 
	self.TrgSpMonster_Timer = {}	--触发器延时刷怪存储表，存储计时器ID跟对应的刷怪索引
	self.TrgDoneQuest_Timer = {}	--触发器延时交任务存储表，存储计时器ID跟对应的任务ID
	self.TrgLaunchPolt_Timer = {}	--触发器延时播剧情存储表，存储计时器ID跟对应的剧情ID
	self.PlotEndDoneQuest_Timer = {}	--剧情结束完成任务延时
	self.PlotEndSpawnMonster_Timer = {}	--剧情结束刷怪延时
	self.PlotEndLaunchPolt_Timer = {}	--剧情结束播放剧情延时
	self.NpcKilledPlotStart_Timer = {}	--NPC被杀后播放剧情
	self.Stage:SetAIEnable(false)	--关闭地图AI
	self.ModQuest = human:GetModQuest()--获取任务模块
	if self.DungeonConfig ~= nil then
		--角色进场，完成XX任务
		--pwdist.log("角色进场")
		if self.DungeonConfig["HumanEnter_DoneQuest"] ~= nil then
			for k , v in pairs(self.DungeonConfig["HumanEnter_DoneQuest"]) do
				if self.ModQuest:GetQuestStatus(v) == 2 then
					self.ModQuest:DoneQuest(v)
					--pwdist.log("done_questid==="..v)
				end
			end
		end
		--角色进场，播放XX剧情
		if self.DungeonConfig["HumanEnter_PlotStart"] ~= nil then
			local questid_forplot = self.DungeonConfig["HumanEnter_PlotStart"][2] or 0
			if questid_forplot~= 0 and self.ModQuest:GetQuestStatus(questid_forplot) ~= 4 then
				self.SModDungeonScript:PlotStart()
				self.SModDungeonScript:LaunchPolt(self.DungeonConfig["HumanEnter_PlotStart"][1],0,"Plot_HumanEnter")

				
			elseif questid_forplot == 0 then
				self.SModDungeonScript:PlotStart()
				self.SModDungeonScript:LaunchPolt(self.DungeonConfig["HumanEnter_PlotStart"][1],0,"Plot_HumanEnter")
			else
				--没有进场剧情的话，直接播放副本开启特效
				self.timer_start = self.SModDungeonScript:CreateTimer(DUNGEON_START_TIME,"Timer_start")
				self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DUNGEON_START_TIME))
				--pwdist.log("timerid_Timer_start==="..tostring(self.timer_start))
				self.SModDungeonScript:PlotStart()--锁操作
			end
		else
			--没有进场剧情的话，直接播放副本开启特效
			self.timer_start = self.SModDungeonScript:CreateTimer(DUNGEON_START_TIME,"Timer_start")
			self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DUNGEON_START_TIME))
			--pwdist.log("timerid_Timer_start==="..tostring(self.timer_start))
			self.SModDungeonScript:PlotStart()--锁操作
		end
		--创建用来刷怪的触发器
		if self.DungeonConfig["CreateTrigger_SpawnMonster"] ~= nil then
			for k , v in pairs(self.DungeonConfig["CreateTrigger_SpawnMonster"]) do
				self.trigger = self.Stage:CreateTriggerRect(v[1],v[2],v[3],"Trigger_SpawnMonster","")
				self.trigger:SetContext({k})
				--pwdist.log("trigger==="..v[2])
			end
		end
		--创建用来完成任务的触发器
		if self.DungeonConfig["CreateTrigger_DoneQuest"] ~= nil then
			for k , v in pairs(self.DungeonConfig["CreateTrigger_DoneQuest"]) do
				self.trigger = self.Stage:CreateTriggerRect(v[1],v[2],v[3],"Trigger_DoneQuest","")
				self.trigger:SetContext({k})
				--pwdist.log("trigger==="..v[2])
			end
		end		
		--创建用来播放剧情的触发器
		if self.DungeonConfig["CreateTrigger_LaunchPolt"] ~= nil then
			for k , v in pairs(self.DungeonConfig["CreateTrigger_LaunchPolt"]) do
				self.trigger = self.Stage:CreateTriggerRect(v[1],v[2],v[3],"Trigger_LaunchPolt","")
				self.trigger:SetContext({k})
				--pwdist.log("trigger==="..v[2])
			end
		end	
		--角色进场播放弱提示
		if self.DungeonConfig["HumanEnter_StartHint"] ~= nil then
			self.MainHuman:Hint(self.DungeonConfig["HumanEnter_StartHint"][1],30000)
		end
		if self.DungeonConfig["HumanEnter_OpenEffectWalls"] ~= nil then
			for k , v in pairs(self.DungeonConfig["HumanEnter_OpenEffectWalls"]) do
				self.Stage:GetModDetour():EnableBlockEffects(v,true)	--打开特效墙
			end
		end
		if self.DungeonConfig["HumanEnter_CreateFinger"] ~= nil then
			local finger_pos = self.DungeonConfig["HumanEnter_CreateFinger"][1]
			local finger_angle = self.DungeonConfig["HumanEnter_CreateFinger"][2]
			self.Stage:CreateStaticObject(finger_pos,finger_angle,CREATURE_FINGER,0,"")
		end
		-----------------------------------------------------------------------------------
		--剧情本，全部用脚本刷怪的节奏
		if self.DungeonConfig["NpcKilled_CrossDungeonWava"] ~= nil then
			self.SModObjs:Broadcast(msgids.SCDungeonTargetList, self.msg)
			self.SModCommon:CreateTimer(self.msg.timesec,"JQ_EndTime")
			self.HumanOldTime = os.time()

			self.SModDungeonScript:SpawnMultiMonster(self.DungeonConfig["NpcKilled_CrossDungeonWava"][1]["method"])---刷第一组怪
			self.jq_correntwave = 1		

		end	
		-----------------------------------------------------------------------------------
		
		--角色进场打开阻挡
		if self.DungeonConfig["HumanEnterEnableMotionBlock"] ~= nil then
			for k , v in pairs(self.DungeonConfig["HumanEnterEnableMotionBlock"]) do
				self.Stage:GetModDetour():EnableMotionBlock(v[1],v[2])
			end
		end
		---------------------------------------------------
	end
end


function CurrentDungeonScript:HumanLeaveEvent(human)
    self.Stage:GetModDungeonScript():Cleanup()	--*玩家离开场景清空所有剧情相关逻辑，以免出问题*
end
function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end

function CurrentDungeonScript:HumanKilled(human,killer)  	--角色死亡
	self:G_InterHumanKilledEvent(human,killer)
end
--角色进场剧情
function CurrentDungeonScript:Plot_HumanEnter(plotid)
	self.SModDungeonScript:PlotClean()
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"dungeon_start")
	local NewTime = os.time()
	local SurTime = self.HumanOldTime + self.DungeonConfig["JQ_DungeonMaxTime"] - NewTime		----副本剩余时间
	self.msg.timesec = SurTime
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, self.msg)
	if self.DungeonConfig["PlotEnd_DoneQuest"] ~= nil then	--剧情结束后完成XX任务
		for k , v in pairs(self.DungeonConfig["PlotEnd_DoneQuest"]) do 
			if plotid == v[1] then
				self.ModQuest:DoneQuest(v[2])
			end
		end
	end
end
--触发器，刷怪
function CurrentDungeonScript:Trigger_SpawnMonster(trigger,target)
	local Tab = trigger:GetContext()
	local Timer = self.DungeonConfig["CreateTrigger_SpawnMonster"][Tab[1]]["Timer"]
	if Timer == nil then
		self.SModDungeonScript:SpawnMonster(self.DungeonConfig["CreateTrigger_SpawnMonster"][Tab[1]][4])
	else
		self.timerid = self.SModDungeonScript:CreateTimer(Timer,"TriggerSpawnMonster_OnTimer")
		self.TrgSpMonster_Timer[tostring(self.timerid)] = self.DungeonConfig["CreateTrigger_SpawnMonster"][Tab[1]][4]
	end
	trigger:LeaveWorld(0)
end
--触发器，延时刷怪
function CurrentDungeonScript:TriggerSpawnMonster_OnTimer(timerid)
	if self.TrgSpMonster_Timer[tostring(timerid)] ~= nil then
		self.SModDungeonScript:SpawnMonster(self.TrgSpMonster_Timer[tostring(timerid)])
	end
end
--触发器，完成任务
function CurrentDungeonScript:Trigger_DoneQuest(trigger,target)
	local Tab = trigger:GetContext()
	local Timer = self.DungeonConfig["CreateTrigger_DoneQuest"][Tab[1]]["Timer"]
	local questid = self.DungeonConfig["CreateTrigger_DoneQuest"][Tab[1]][4]
	--pwdist.log("questid===="..questid)
	if Timer == nil then
		if self.ModQuest:GetQuestStatus(questid) == 2 then
			self.ModQuest:DoneQuest(questid)
		end
	else
		self.timerid = self.SModDungeonScript:CreateTimer(Timer,"TriggerDoneQuest_OnTimer")
		self.TrgDoneQuest_Timer[tostring(self.timerid)] = questid
	end
end
--触发器，延时完成任务
function CurrentDungeonScript:TriggerDoneQuest_OnTimer(timerid)
	if self.TrgDoneQuest_Timer[tostring(timerid)] ~= nil then
		if self.ModQuest:GetQuestStatus(self.TrgDoneQuest_Timer[tostring(timerid)]) == 2 then
			self.ModQuest:DoneQuest(self.TrgDoneQuest_Timer[tostring(timerid)])
		end
	end
end
--触发器，播放剧情
function CurrentDungeonScript:Trigger_LaunchPolt(trigger,target)
	local Tab = trigger:GetContext()
	local Timer = self.DungeonConfig["CreateTrigger_LaunchPolt"][Tab[1]]["Timer"]
	local questid = self.DungeonConfig["CreateTrigger_LaunchPolt"][Tab[1]]["questid"] or 0
	local plotid = self.DungeonConfig["CreateTrigger_LaunchPolt"][Tab[1]][4]
	--pwdist.log("plotid===="..plotid)
	if questid ~= 0 then
		if self.ModQuest:GetQuestStatus(questid) == 2 then	
			if Timer == nil then
				self.SModDungeonScript:PlotStart()
				self.MainHuman:GetModMotionMaster():StopMotion()
				self.Stage:GetModObjs():SuspendCreaturesAI()
				self.SModDungeonScript:LaunchPolt(plotid,0,"LaunchPolt")
			else
				self.timerid = self.SModDungeonScript:CreateTimer(Timer,"TriggerLaunchPolt_OnTimer")
				self.TrgLaunchPolt_Timer[tostring(self.timerid)] = plotid
			end
		end
	else
		if Timer == nil then
			self.SModDungeonScript:PlotStart()
			self.MainHuman:GetModMotionMaster():StopMotion()
			self.Stage:GetModObjs():SuspendCreaturesAI()
			self.SModDungeonScript:LaunchPolt(plotid,0,"LaunchPolt")
		else
			self.timerid = self.SModDungeonScript:CreateTimer(Timer,"TriggerLaunchPolt_OnTimer")
			self.TrgLaunchPolt_Timer[tostring(self.timerid)] = plotid
		end
	end
	trigger:LeaveWorld(0)
end
--触发器，延时播放剧情
function CurrentDungeonScript:TriggerLaunchPolt_OnTimer(timerid)
	if self.TrgLaunchPolt_Timer[tostring(timerid)] ~= nil then
		self.SModDungeonScript:PlotStart()
		self.MainHuman:GetModMotionMaster():StopMotion()
		self.Stage:GetModObjs():SuspendCreaturesAI()
		self.SModDungeonScript:LaunchPolt(self.TrgLaunchPolt_Timer[tostring(timerid)],0,"LaunchPolt")
	end
end
--剧情回调函数
function CurrentDungeonScript:LaunchPolt(plotid)
	--pwdist.log("剧情回调函数==="..plotid)
	self.Stage:GetModObjs():ResumeCreaturesAI()
	self.SModDungeonScript:PlotClean()
	if self.DungeonConfig["PlotEnd_DoneQuest"] ~= nil then	--剧情结束后完成XX任务
		for k , v in pairs(self.DungeonConfig["PlotEnd_DoneQuest"]) do 
			if plotid == v[1] then
				if v.Timer == nil then
					self.ModQuest:DoneQuest(v[2])
				else
					self.timerid = self.SModDungeonScript:CreateTimer(v.Timer,"PoltEndDoneQuest_OnTimer")
					self.PlotEndDoneQuest_Timer[tostring(self.timerid)] = v[2]
				end
			end
		end
	end
	if self.DungeonConfig["PlotEnd_SpawnMonster"] ~= nil then	--剧情结束后刷怪
		for k , v in pairs(self.DungeonConfig["PlotEnd_SpawnMonster"]) do 
			if plotid == v[1] then
				if v.Timer == nil then
					self.SModDungeonScript:SpawnMonster(v[2])
				else
					self.timerid = self.SModDungeonScript:CreateTimer(v.Timer,"PlotEndSpawnMonster_OnTimer")
					self.PlotEndSpawnMonster_Timer[tostring(self.timerid)] = v[2]
				end
			end
		end
	end
	if self.DungeonConfig["PlotEnd_LaunchPolt"] ~= nil then	--剧情结束后继续播放剧情
		for k , v in pairs(self.DungeonConfig["PlotEnd_LaunchPolt"]) do 
			if plotid == v[1] then
				if v.Timer == nil then
					self.SModDungeonScript:PlotStart()
					self.MainHuman:GetModMotionMaster():StopMotion()
					self.Stage:GetModObjs():SuspendCreaturesAI()
					self.SModDungeonScript:LaunchPolt(plotid,0,"LaunchPolt")
				else
					self.timerid = self.SModDungeonScript:CreateTimer(v.Timer,"PlotEndLaunchPolt_OnTimer")
					self.PlotEndLaunchPolt_Timer[tostring(self.timerid)] = v[2]
				end
			end
		end
	end
end
--剧情结束，延时完成任务
function CurrentDungeonScript:PoltEndDoneQuest_OnTimer(timerid)
	if self.PlotEndDoneQuest_Timer[tostring(timerid)] ~= nil then
		if self.ModQuest:GetQuestStatus(self.PlotEndDoneQuest_Timer[tostring(timerid)]) == 2 then
			self.ModQuest:DoneQuest(self.PlotEndDoneQuest_Timer[tostring(timerid)])
		end
	end
end
--剧情结束，延时刷怪
function CurrentDungeonScript:PlotEndSpawnMonster_OnTimer(timerid)
	if self.PlotEndSpawnMonster_Timer[tostring(timerid)] ~= nil then
		self.SModDungeonScript:SpawnMonster(self.PlotEndSpawnMonster_Timer[tostring(timerid)])
	end
end
--剧情结束，延时播放剧情
function CurrentDungeonScript:PlotEndLaunchPolt_OnTimer(timerid)
	if self.PlotEndLaunchPolt_Timer[tostring(timerid)] ~= nil then
		self.SModDungeonScript:PlotStart()
		self.MainHuman:GetModMotionMaster():StopMotion()
		self.Stage:GetModObjs():SuspendCreaturesAI()
		self.SModDungeonScript:LaunchPolt(self.PlotEndLaunchPolt_Timer[tostring(timerid)],0,"LaunchPolt")
	end
end
--计时器：副本开始
function CurrentDungeonScript:Timer_start(timerid)
	--pwdist.log("timerid_Timer_start==="..tostring(timerid))

	self.SModDungeonScript:CancelTimer(self.timer_start)
	
	self:G_DungeonStart()
	self.Stage:SetAIEnable(true)	--解锁地图怪物AI
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_BEGIN,tostring(0))
	self.SModDungeonScript:PlotClean()
	self.Stage:GetModObjs():ResumeCreaturesAI()-----恢复所有AI
	self.MainHuman:OpenAutoCombat()-----开启自动战斗
end
--副本开始剧情结束事件，调用开启副本被封的导航块
function CurrentDungeonScript:dungeon_start(plotid)
    self:G_DungeonStart()
	self.Stage:SetAIEnable(true)	--解锁地图怪物AI
	if self.DungeonConfig ~= nil then
		if self.DungeonConfig["EnableMotionBlock"] ~= nil then
			for k , v in pairs(self.DungeonConfig["EnableMotionBlock"]) do
				self.Stage:GetModDetour():EnableMotionBlock(v[1],v[2])
			end
		end
	end
end
--NPC被杀事件，调用副本通关
function CurrentDungeonScript:NpcKilled_CrossDungeon(creature,killer)
	self.count_crossdungeon = self.count_crossdungeon - 1
	if self.count_crossdungeon == 0 then--怪物被杀完，副本结束，通关
		self:G_DungeonEnd(DUNGEON_END_TIME)
		--local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
		--for k , v in pairs(CreatureTab) do
		--	v:GetModCombat():KillSelf(PET_KILLSELF_SKILLID,PET_KILLSELF_EFFECT)
		--end		
	end
	if self.DungeonConfig["NpcKilled_KillPet"] ~= nil then	--杀死通关BOSS的小弟
		for k , v in pairs(self.DungeonConfig["NpcKilled_KillPet"]) do
			if creature:GetCreatureType() == v then
				local PetTab = creature:GetModSummoner():GetSummonedUnits()
				if PetTab ~= nil then
					for k , v in pairs(PetTab) do
						v:GetModCombat():KillSelf(PET_KILLSELF_SKILLID,PET_KILLSELF_EFFECT)
					end
				end
			end
		end
	end
end

--NPC被杀事件，调用副本通关(随机杀怪）
function CurrentDungeonScript:NpcKilled_CrossDungeonRandom(creature,killer)
	--pwdist.log("怪物剩余个数==="..self.count_crossdungeonRandom)
	self.count_crossdungeonRandom = self.count_crossdungeonRandom - 1
	if self.count_crossdungeonRandom == 0 then--怪物被杀完，副本结束，通关
		local questid = self.DungeonConfig["NpcKilled_CrossDungeonRandom"]["questid"] or 0
		if questid ~= 0 then
			self.ModQuest:DoneQuest(questid)
		end
		self:G_DungeonEnd(DUNGEON_END_TIME)
	end
end

-----------------------------------------------------------------------------------------------------------------------------------
--self:UpDateCondition(1,MonterDieNum,self.msg.targetlist[1].maxcount,DungeonConditionStr[1])
--NPC被杀事件，针对按波数一波波杀怪，杀一波刷一波，全部杀完通关。剧情副本用
function CurrentDungeonScript:NpcKilled_CrossDungeonWava(creature,killer)
--pwdist.log("怪物剩余个数==="..self.jq_corrent_count)
	self.jq_corrent_count = self.jq_corrent_count - 1
	self.jq_corrent_maxcount = self.jq_corrent_maxcount + 1
	--更新目标列表
	if #self.DungeonConfig["JQ_CrossDungeonNpcid"]["bossid"] == 0 then --没有BOSS计数，只算总数
		self:UpDateCondition(1,self.jq_corrent_maxcount,self.msg.targetlist[1].maxcount,self.msg.targetlist[1].strid)
	else
		local BossId = creature:GetCreatureType()
		for k,v in pairs(self.DungeonConfig["JQ_CrossDungeonNpcid"]["bossid"]) do
			if BossId == v then
				self:UpDateCondition(k,1,self.msg.targetlist[k].maxcount,self.msg.targetlist[k].strid)
			end
		end
	end	
	if self.jq_corrent_count == 0 then--怪物被杀完，刷下一波，直至刷完
		
		--发提醒
		if self.DungeonConfig["NpcKilled_CrossDungeonWava"][self.jq_correntwave]["str"] ~= 0 then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(self.DungeonConfig["NpcKilled_CrossDungeonWava"][self.jq_correntwave]["str"]))
		end
		--发完提醒再更新波数
		self.jq_correntwave = self.jq_correntwave + 1
		if self.jq_correntwave <= #self.DungeonConfig["NpcKilled_CrossDungeonWava"] then
			self.jq_corrent_count = self.DungeonConfig["NpcKilled_CrossDungeonWava"][self.jq_correntwave]["count"]

			self.SModDungeonScript:SpawnMultiMonster(self.DungeonConfig["NpcKilled_CrossDungeonWava"][self.jq_correntwave]["method"])---刷下一组

		else
			self:G_DungeonEnd(DUNGEON_END_TIME)
		end
	end
end
-----------------------------------------------------------------------------------------------------------------------------
--NPC死亡杀死小弟
function CurrentDungeonScript:NpcKilled_KillPet(creature,killer)
	local PetTab = creature:GetModSummoner():GetSummonedUnits()
	if PetTab ~= nil then
		for k , v in pairs(PetTab) do
			v:GetModCombat():KillSelf(PET_KILLSELF_SKILLID,PET_KILLSELF_EFFECT)
		end
	end
end
--NPC死亡触发剧情
function CurrentDungeonScript:NpcKilled_PlotStart(creature,killer)
	local NpcId = creature:GetCreatureType()
	for k , v in pairs(self.DungeonConfig["NpcKilled_PlotStart"]) do
		for i , j in pairs(v[1]) do
			if NpcId == j[1] then
				self.count_PlotStart[k] = self.count_PlotStart[k] - 1
				if self.count_PlotStart[k] == 0 then
					if v.Timer == nil then
						self.SModDungeonScript:PlotStart()
						self.MainHuman:GetModMotionMaster():StopMotion()
						self.Stage:GetModObjs():SuspendCreaturesAI()
						self.SModDungeonScript:LaunchPolt(v[2],0,"LaunchPolt")
					else
						self.timerid = self.SModDungeonScript:CreateTimer(v.Timer,"pcKilledPlotStart_OnTimer")
						self.NpcKilledPlotStart_Timer[tostring(self.timerid)] = v[2]
					end
				end
			end
		end
	end
end
--NPC死亡延时触发剧情
function CurrentDungeonScript:pcKilledPlotStart_OnTimer(timerid)
	if self.NpcKilledPlotStart_Timer[tostring(timerid)] ~= nil then
		self.SModDungeonScript:PlotStart()
		self.MainHuman:GetModMotionMaster():StopMotion()
		self.Stage:GetModObjs():SuspendCreaturesAI()
		self.SModDungeonScript:LaunchPolt(self.NpcKilledPlotStart_Timer[tostring(timerid)],0,"LaunchPolt")
	end
end

---更新副本条件
function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid)----1更新第几条  2最小值 3最大值  4副本描述str
-- pwdist.log("更新副本数据")
	local NewTime = os.time()
	local SurTime = self.HumanOldTime + self.DungeonConfig["JQ_DungeonMaxTime"] - NewTime		----副本剩余时间
	self.msg.timesec = SurTime
	self.msg.targetlist[Index].count = Ucount
	self.msg.targetlist[Index].maxcount = Umaxcount
	self.msg.targetlist[Index].strid = Ustrid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, self.msg)
end

----副本到时间了
function CurrentDungeonScript:JQ_EndTime()

	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
	for k , v in pairs(CreatureTab) do
		v:LeaveWorld(0)
	end	
	----弹失败界面
	self.SModObjs:Broadcast(msgids.SCDungeonFailed, self.msg)

end