--单人玩法，勇者试炼

CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------
CurrentDungeonScript.SpawnCraetureT = {
	[1] = {47101,47102,47103,47104,47105,47106,47107,47108,47109,47110,47111}, --小怪的ID组
	[2] = {47201,47202,47203,47204,47205,47206,47207,47208}, --小头目的ID组
	[3] = {47251,47252,47253,47254,47255,47256,47257,47258,47259,47260,47261,47262,47263,47264,47265,47266,47267,47268,47269,47270}, --BOSS的ID组
	[4] = {47151,47152,47153,47154,47155,47156,47157,47158}, --远程小怪的ID组
	}

CurrentDungeonScript.monster_kind = 3	--小怪的种类和数量
CurrentDungeonScript.monster_count = 4
CurrentDungeonScript.leader_kind = 2	--领队的种类和数量
CurrentDungeonScript.leader_count = 2
CurrentDungeonScript.boss_kind = 1	--BOSS的种类和数量
CurrentDungeonScript.boss_count = 1
CurrentDungeonScript.mons_L_kind = 1	--远程小怪的种类和数量
CurrentDungeonScript.mons_L_count = 3

CurrentDungeonScript.current_wave = 1 --记录当前挑战层数
CurrentDungeonScript.CurrentWaveStarttime = 0
CurrentDungeonScript.Time_fight = 30 --每轮战斗时间
CurrentDungeonScript.CurrentMonsCount = 0	--当前波数怪物数量
CurrentDungeonScript.MaxWave = 50 	--最大波数 50
CurrentDungeonScript.Total_time = 0	--计算挑战的总耗时

CurrentDungeonScript.Timer_begain = 5		--开场倒计时

CurrentDungeonScript.isdungeonend = 0


function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
	self.SModLogicYZSL = self.Stage:GetModLogic():cast("SModLogicYZSL")
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
	SetEventHandler(StageEvents.HumanLeave,"HumanLeave")
    SetEventHandler(StageEvents.HumanKilled,"OnHumanKilled")
	for k , v in pairs(self.SpawnCraetureT) do
		for i , j in pairs(v) do
			SetEventHandler(StageEvents.CreatureKilled,"OnMonsterKilled",{type = j})	
		end
	end
	SetEventHandler(StageEvents.CreatureSpawn,"OnMonsterSpawn")  --怪物刷新
end

function CurrentDungeonScript:HumanEnterEvent(human)
	self.Stage:GetModDetour():EnableMotionBlock(0,true)
	self.SModDungeonScript:PlotStart()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(self.Timer_begain))
	self.SModDungeonScript:CreateTimer(self.Timer_begain,"OnTimer_DungeonStart")
	--如果玩家曾挑战大于10波，修改初始波数
	local P_maxwave = self.SModLogicYZSL:GetMyRound()
	if P_maxwave > 10 then
		self.current_wave = P_maxwave - 10
	end	
	self.SModLogicYZSL:EndedRound(self.current_wave - 1,0,30)	--结束战斗，提交波数、时间
	
end
function CurrentDungeonScript:OnTimer_DungeonStart()
	
	
	self.SModDungeonScript:PlotClean()
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"")
	self:SpawnMonster()
	
end

--刷怪
function CurrentDungeonScript:SpawnMonster()
	self.MainHuman:CloseHint(0)
	local humanpos = self.MainHuman:GetPosition()
	self.Stage:GetModObjs():BroadcastNotifyWithFaction(102008,ChannelType.Announcement,2,1,self.current_wave)
	math.random(1,#self.SpawnCraetureT[1])
	self.CurrentMonsCount = 20
	for i = 1,self.monster_kind do
		self.SModDungeonScript:SpawnMonsterRandom(humanpos,15,self.SpawnCraetureT[1][math.random(1,#self.SpawnCraetureT[1])],self.monster_count)	
	end
	for k = 1,self.leader_kind do
		self.SModDungeonScript:SpawnMonsterRandom(humanpos,15,self.SpawnCraetureT[2][math.random(1,#self.SpawnCraetureT[2])],self.leader_count)	
	end
	for j = 1,self.boss_kind do
		self.SModDungeonScript:SpawnMonsterRandom(humanpos,15,self.SpawnCraetureT[3][math.random(1,#self.SpawnCraetureT[3])],self.boss_count)	
	end
	for l = 1,self.mons_L_kind do
		self.SModDungeonScript:SpawnMonsterRandom(humanpos,15,self.SpawnCraetureT[4][math.random(1,#self.SpawnCraetureT[4])],self.mons_L_count)	
	end
	
	self.SModLogicYZSL:StartRound(self.current_wave,30)	--开启战斗，提交波数
	self.CurrentWaveStarttime = os.time()	--记录开启时间
	self.Timer_fight = self.SModDungeonScript:CreateTimer(self.Time_fight,"OnTimer_DungeonFaild")	--限定时间挑战
end
--时间到 了，挑战失败
function CurrentDungeonScript:OnTimer_DungeonFaild()
	self:DungeonFaild()
end
--怪物被击杀
function CurrentDungeonScript:OnMonsterKilled(creature)
	self.CurrentMonsCount = self.CurrentMonsCount -1
	if self.CurrentMonsCount == 0 then
		--该层挑战结束
		if self.Timer_fight ~= nil then self.SModDungeonScript:CancelTimer(self.Timer_fight) end	--关闭计时器
		local TimeUse = os.time() - self.CurrentWaveStarttime
		self.Total_time = self.Total_time + TimeUse
		self.SModLogicYZSL:EndedRound(self.current_wave,self.Total_time,30)	--结束战斗，提交波数、时间
		if self.current_wave < self.MaxWave then	--还没通关
			self.SModDungeonScript:CreateTimer(3,"OnTimer_OpenNext")
			self.current_wave = self.current_wave + 1
			self.MainHuman:Hint(41881,30000)
		else --全部通关
			self.isdungeonend = 1
			self.MainHuman:GetModAura():Create(304) --无敌无表现
			self.SModLogicYZSL:Finish()	--通关，提交波数、时间
			self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"")
			self.MainHuman:Hint(41883,30000)
			self.Stage:GetModObjs():BroadcastNotifyWithFaction(102010,ChannelType.Announcement,2,1,self.current_wave)
		end
	end
end

--开启下一波
function CurrentDungeonScript:OnTimer_OpenNext()
	self:SpawnMonster()
end

--挑战失败
function CurrentDungeonScript:DungeonFaild()
	self.isdungeonend = 1
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k , v in pairs(CreatureTab) do
		v:LeaveWorld(0)
	end
	if self.MainHuman:IsDead() then
		self.MainHuman:GetModRealive():Realive(self.MainHuman:GetPosition(), 1)
		self.MainHuman:GetModAura():Create(304) --无敌无表现
	end
	self.MainHuman:Hint(41882,30000)
	local FinishWave = self.current_wave - 1
	self.SModLogicYZSL:Finish()	--通关，提交波数、时间
	self.Stage:GetModObjs():BroadcastNotifyWithFaction(102009,ChannelType.Announcement,2,1,FinishWave)
	self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"")
end



function CurrentDungeonScript:HumanLeave(human)  
	if human:GetModQuest():GetQuestStatus(10065) == 2 then
		human:GetModQuest():DoneQuest(10065)
	end
	self.Stage:GetModDungeonScript():Cleanup()
end
function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end

function CurrentDungeonScript:OnHumanKilled(human,killer)
	if self.isdungeonend == 1 then	
		human:GetModRealive():Realive(v:GetPosition(),1)
	else
		human:GetModRealive():SetRealiveDelay(5000)
	end
end

--怪物刷新 加属性
function CurrentDungeonScript:OnMonsterSpawn(creature)
	self.SModLogicYZSL:AdjustMonsterAttrs(creature,self.current_wave)	--修改怪物属性

end

