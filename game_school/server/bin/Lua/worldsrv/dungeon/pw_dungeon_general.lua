require "./Lua/worldsrv/dungeon/pw_dungeon_config"

CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
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
		--ע��NPC�����¼�����Ը���ͨ�ص�NPC����
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
		--ע��NPC�����¼�����Ը���ͨ�ص�NPC����(���ֻ������ֹ��������̶�����ÿ�ֹ��ﲻȷ�����������ˢ��)
		if self.DungeonConfig["NpcKilled_CrossDungeonRandom"] ~= nil then
			self.count_crossdungeonRandom = self.DungeonConfig["NpcKilled_CrossDungeonRandom"][2]
			for k , v in pairs(self.DungeonConfig["NpcKilled_CrossDungeonRandom"][1]) do
				SetEventHandler(StageEvents.CreatureKilled,"NpcKilled_CrossDungeonRandom",{type = v})
			end
		end
		---------------------------------------------------------------------------------
		--ע��NPC�����¼�����԰�����һ����ɱ�֣�ɱһ��ˢһ����ȫ��ɱ��ͨ�ء����鸱����
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
			self.msg.timesec = self.DungeonConfig["JQ_DungeonMaxTime"]-----3 * 60	----������ʱ��
			if #self.DungeonConfig["JQ_CrossDungeonNpcid"]["bossid"] == 0 then --û��BOSS������ֻ������
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
		--BOSS����ɱ���ٻ���С��
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
		--ע��NPC�����¼������ɱ�����ﴥ������
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
	self.TrgSpMonster_Timer = {}	--��������ʱˢ�ִ洢���洢��ʱ��ID����Ӧ��ˢ������
	self.TrgDoneQuest_Timer = {}	--��������ʱ������洢���洢��ʱ��ID����Ӧ������ID
	self.TrgLaunchPolt_Timer = {}	--��������ʱ������洢���洢��ʱ��ID����Ӧ�ľ���ID
	self.PlotEndDoneQuest_Timer = {}	--����������������ʱ
	self.PlotEndSpawnMonster_Timer = {}	--�������ˢ����ʱ
	self.PlotEndLaunchPolt_Timer = {}	--����������ž�����ʱ
	self.NpcKilledPlotStart_Timer = {}	--NPC��ɱ�󲥷ž���
	self.Stage:SetAIEnable(false)	--�رյ�ͼAI
	self.ModQuest = human:GetModQuest()--��ȡ����ģ��
	if self.DungeonConfig ~= nil then
		--��ɫ���������XX����
		--pwdist.log("��ɫ����")
		if self.DungeonConfig["HumanEnter_DoneQuest"] ~= nil then
			for k , v in pairs(self.DungeonConfig["HumanEnter_DoneQuest"]) do
				if self.ModQuest:GetQuestStatus(v) == 2 then
					self.ModQuest:DoneQuest(v)
					--pwdist.log("done_questid==="..v)
				end
			end
		end
		--��ɫ����������XX����
		if self.DungeonConfig["HumanEnter_PlotStart"] ~= nil then
			local questid_forplot = self.DungeonConfig["HumanEnter_PlotStart"][2] or 0
			if questid_forplot~= 0 and self.ModQuest:GetQuestStatus(questid_forplot) ~= 4 then
				self.SModDungeonScript:PlotStart()
				self.SModDungeonScript:LaunchPolt(self.DungeonConfig["HumanEnter_PlotStart"][1],0,"Plot_HumanEnter")

				
			elseif questid_forplot == 0 then
				self.SModDungeonScript:PlotStart()
				self.SModDungeonScript:LaunchPolt(self.DungeonConfig["HumanEnter_PlotStart"][1],0,"Plot_HumanEnter")
			else
				--û�н�������Ļ���ֱ�Ӳ��Ÿ���������Ч
				self.timer_start = self.SModDungeonScript:CreateTimer(DUNGEON_START_TIME,"Timer_start")
				self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DUNGEON_START_TIME))
				--pwdist.log("timerid_Timer_start==="..tostring(self.timer_start))
				self.SModDungeonScript:PlotStart()--������
			end
		else
			--û�н�������Ļ���ֱ�Ӳ��Ÿ���������Ч
			self.timer_start = self.SModDungeonScript:CreateTimer(DUNGEON_START_TIME,"Timer_start")
			self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DUNGEON_START_TIME))
			--pwdist.log("timerid_Timer_start==="..tostring(self.timer_start))
			self.SModDungeonScript:PlotStart()--������
		end
		--��������ˢ�ֵĴ�����
		if self.DungeonConfig["CreateTrigger_SpawnMonster"] ~= nil then
			for k , v in pairs(self.DungeonConfig["CreateTrigger_SpawnMonster"]) do
				self.trigger = self.Stage:CreateTriggerRect(v[1],v[2],v[3],"Trigger_SpawnMonster","")
				self.trigger:SetContext({k})
				--pwdist.log("trigger==="..v[2])
			end
		end
		--���������������Ĵ�����
		if self.DungeonConfig["CreateTrigger_DoneQuest"] ~= nil then
			for k , v in pairs(self.DungeonConfig["CreateTrigger_DoneQuest"]) do
				self.trigger = self.Stage:CreateTriggerRect(v[1],v[2],v[3],"Trigger_DoneQuest","")
				self.trigger:SetContext({k})
				--pwdist.log("trigger==="..v[2])
			end
		end		
		--�����������ž���Ĵ�����
		if self.DungeonConfig["CreateTrigger_LaunchPolt"] ~= nil then
			for k , v in pairs(self.DungeonConfig["CreateTrigger_LaunchPolt"]) do
				self.trigger = self.Stage:CreateTriggerRect(v[1],v[2],v[3],"Trigger_LaunchPolt","")
				self.trigger:SetContext({k})
				--pwdist.log("trigger==="..v[2])
			end
		end	
		--��ɫ������������ʾ
		if self.DungeonConfig["HumanEnter_StartHint"] ~= nil then
			self.MainHuman:Hint(self.DungeonConfig["HumanEnter_StartHint"][1],30000)
		end
		if self.DungeonConfig["HumanEnter_OpenEffectWalls"] ~= nil then
			for k , v in pairs(self.DungeonConfig["HumanEnter_OpenEffectWalls"]) do
				self.Stage:GetModDetour():EnableBlockEffects(v,true)	--����Чǽ
			end
		end
		if self.DungeonConfig["HumanEnter_CreateFinger"] ~= nil then
			local finger_pos = self.DungeonConfig["HumanEnter_CreateFinger"][1]
			local finger_angle = self.DungeonConfig["HumanEnter_CreateFinger"][2]
			self.Stage:CreateStaticObject(finger_pos,finger_angle,CREATURE_FINGER,0,"")
		end
		-----------------------------------------------------------------------------------
		--���鱾��ȫ���ýű�ˢ�ֵĽ���
		if self.DungeonConfig["NpcKilled_CrossDungeonWava"] ~= nil then
			self.SModObjs:Broadcast(msgids.SCDungeonTargetList, self.msg)
			self.SModCommon:CreateTimer(self.msg.timesec,"JQ_EndTime")
			self.HumanOldTime = os.time()

			self.SModDungeonScript:SpawnMultiMonster(self.DungeonConfig["NpcKilled_CrossDungeonWava"][1]["method"])---ˢ��һ���
			self.jq_correntwave = 1		

		end	
		-----------------------------------------------------------------------------------
		
		--��ɫ�������赲
		if self.DungeonConfig["HumanEnterEnableMotionBlock"] ~= nil then
			for k , v in pairs(self.DungeonConfig["HumanEnterEnableMotionBlock"]) do
				self.Stage:GetModDetour():EnableMotionBlock(v[1],v[2])
			end
		end
		---------------------------------------------------
	end
end


function CurrentDungeonScript:HumanLeaveEvent(human)
    self.Stage:GetModDungeonScript():Cleanup()	--*����뿪����������о�������߼������������*
end
function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end

function CurrentDungeonScript:HumanKilled(human,killer)  	--��ɫ����
	self:G_InterHumanKilledEvent(human,killer)
end
--��ɫ��������
function CurrentDungeonScript:Plot_HumanEnter(plotid)
	self.SModDungeonScript:PlotClean()
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"dungeon_start")
	local NewTime = os.time()
	local SurTime = self.HumanOldTime + self.DungeonConfig["JQ_DungeonMaxTime"] - NewTime		----����ʣ��ʱ��
	self.msg.timesec = SurTime
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, self.msg)
	if self.DungeonConfig["PlotEnd_DoneQuest"] ~= nil then	--������������XX����
		for k , v in pairs(self.DungeonConfig["PlotEnd_DoneQuest"]) do 
			if plotid == v[1] then
				self.ModQuest:DoneQuest(v[2])
			end
		end
	end
end
--��������ˢ��
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
--����������ʱˢ��
function CurrentDungeonScript:TriggerSpawnMonster_OnTimer(timerid)
	if self.TrgSpMonster_Timer[tostring(timerid)] ~= nil then
		self.SModDungeonScript:SpawnMonster(self.TrgSpMonster_Timer[tostring(timerid)])
	end
end
--���������������
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
--����������ʱ�������
function CurrentDungeonScript:TriggerDoneQuest_OnTimer(timerid)
	if self.TrgDoneQuest_Timer[tostring(timerid)] ~= nil then
		if self.ModQuest:GetQuestStatus(self.TrgDoneQuest_Timer[tostring(timerid)]) == 2 then
			self.ModQuest:DoneQuest(self.TrgDoneQuest_Timer[tostring(timerid)])
		end
	end
end
--�����������ž���
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
--����������ʱ���ž���
function CurrentDungeonScript:TriggerLaunchPolt_OnTimer(timerid)
	if self.TrgLaunchPolt_Timer[tostring(timerid)] ~= nil then
		self.SModDungeonScript:PlotStart()
		self.MainHuman:GetModMotionMaster():StopMotion()
		self.Stage:GetModObjs():SuspendCreaturesAI()
		self.SModDungeonScript:LaunchPolt(self.TrgLaunchPolt_Timer[tostring(timerid)],0,"LaunchPolt")
	end
end
--����ص�����
function CurrentDungeonScript:LaunchPolt(plotid)
	--pwdist.log("����ص�����==="..plotid)
	self.Stage:GetModObjs():ResumeCreaturesAI()
	self.SModDungeonScript:PlotClean()
	if self.DungeonConfig["PlotEnd_DoneQuest"] ~= nil then	--������������XX����
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
	if self.DungeonConfig["PlotEnd_SpawnMonster"] ~= nil then	--���������ˢ��
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
	if self.DungeonConfig["PlotEnd_LaunchPolt"] ~= nil then	--���������������ž���
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
--�����������ʱ�������
function CurrentDungeonScript:PoltEndDoneQuest_OnTimer(timerid)
	if self.PlotEndDoneQuest_Timer[tostring(timerid)] ~= nil then
		if self.ModQuest:GetQuestStatus(self.PlotEndDoneQuest_Timer[tostring(timerid)]) == 2 then
			self.ModQuest:DoneQuest(self.PlotEndDoneQuest_Timer[tostring(timerid)])
		end
	end
end
--�����������ʱˢ��
function CurrentDungeonScript:PlotEndSpawnMonster_OnTimer(timerid)
	if self.PlotEndSpawnMonster_Timer[tostring(timerid)] ~= nil then
		self.SModDungeonScript:SpawnMonster(self.PlotEndSpawnMonster_Timer[tostring(timerid)])
	end
end
--�����������ʱ���ž���
function CurrentDungeonScript:PlotEndLaunchPolt_OnTimer(timerid)
	if self.PlotEndLaunchPolt_Timer[tostring(timerid)] ~= nil then
		self.SModDungeonScript:PlotStart()
		self.MainHuman:GetModMotionMaster():StopMotion()
		self.Stage:GetModObjs():SuspendCreaturesAI()
		self.SModDungeonScript:LaunchPolt(self.PlotEndLaunchPolt_Timer[tostring(timerid)],0,"LaunchPolt")
	end
end
--��ʱ����������ʼ
function CurrentDungeonScript:Timer_start(timerid)
	--pwdist.log("timerid_Timer_start==="..tostring(timerid))

	self.SModDungeonScript:CancelTimer(self.timer_start)
	
	self:G_DungeonStart()
	self.Stage:SetAIEnable(true)	--������ͼ����AI
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_BEGIN,tostring(0))
	self.SModDungeonScript:PlotClean()
	self.Stage:GetModObjs():ResumeCreaturesAI()-----�ָ�����AI
	self.MainHuman:OpenAutoCombat()-----�����Զ�ս��
end
--������ʼ��������¼������ÿ�����������ĵ�����
function CurrentDungeonScript:dungeon_start(plotid)
    self:G_DungeonStart()
	self.Stage:SetAIEnable(true)	--������ͼ����AI
	if self.DungeonConfig ~= nil then
		if self.DungeonConfig["EnableMotionBlock"] ~= nil then
			for k , v in pairs(self.DungeonConfig["EnableMotionBlock"]) do
				self.Stage:GetModDetour():EnableMotionBlock(v[1],v[2])
			end
		end
	end
end
--NPC��ɱ�¼������ø���ͨ��
function CurrentDungeonScript:NpcKilled_CrossDungeon(creature,killer)
	self.count_crossdungeon = self.count_crossdungeon - 1
	if self.count_crossdungeon == 0 then--���ﱻɱ�꣬����������ͨ��
		self:G_DungeonEnd(DUNGEON_END_TIME)
		--local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
		--for k , v in pairs(CreatureTab) do
		--	v:GetModCombat():KillSelf(PET_KILLSELF_SKILLID,PET_KILLSELF_EFFECT)
		--end		
	end
	if self.DungeonConfig["NpcKilled_KillPet"] ~= nil then	--ɱ��ͨ��BOSS��С��
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

--NPC��ɱ�¼������ø���ͨ��(���ɱ�֣�
function CurrentDungeonScript:NpcKilled_CrossDungeonRandom(creature,killer)
	--pwdist.log("����ʣ�����==="..self.count_crossdungeonRandom)
	self.count_crossdungeonRandom = self.count_crossdungeonRandom - 1
	if self.count_crossdungeonRandom == 0 then--���ﱻɱ�꣬����������ͨ��
		local questid = self.DungeonConfig["NpcKilled_CrossDungeonRandom"]["questid"] or 0
		if questid ~= 0 then
			self.ModQuest:DoneQuest(questid)
		end
		self:G_DungeonEnd(DUNGEON_END_TIME)
	end
end

-----------------------------------------------------------------------------------------------------------------------------------
--self:UpDateCondition(1,MonterDieNum,self.msg.targetlist[1].maxcount,DungeonConditionStr[1])
--NPC��ɱ�¼�����԰�����һ����ɱ�֣�ɱһ��ˢһ����ȫ��ɱ��ͨ�ء����鸱����
function CurrentDungeonScript:NpcKilled_CrossDungeonWava(creature,killer)
--pwdist.log("����ʣ�����==="..self.jq_corrent_count)
	self.jq_corrent_count = self.jq_corrent_count - 1
	self.jq_corrent_maxcount = self.jq_corrent_maxcount + 1
	--����Ŀ���б�
	if #self.DungeonConfig["JQ_CrossDungeonNpcid"]["bossid"] == 0 then --û��BOSS������ֻ������
		self:UpDateCondition(1,self.jq_corrent_maxcount,self.msg.targetlist[1].maxcount,self.msg.targetlist[1].strid)
	else
		local BossId = creature:GetCreatureType()
		for k,v in pairs(self.DungeonConfig["JQ_CrossDungeonNpcid"]["bossid"]) do
			if BossId == v then
				self:UpDateCondition(k,1,self.msg.targetlist[k].maxcount,self.msg.targetlist[k].strid)
			end
		end
	end	
	if self.jq_corrent_count == 0 then--���ﱻɱ�꣬ˢ��һ����ֱ��ˢ��
		
		--������
		if self.DungeonConfig["NpcKilled_CrossDungeonWava"][self.jq_correntwave]["str"] ~= 0 then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(self.DungeonConfig["NpcKilled_CrossDungeonWava"][self.jq_correntwave]["str"]))
		end
		--���������ٸ��²���
		self.jq_correntwave = self.jq_correntwave + 1
		if self.jq_correntwave <= #self.DungeonConfig["NpcKilled_CrossDungeonWava"] then
			self.jq_corrent_count = self.DungeonConfig["NpcKilled_CrossDungeonWava"][self.jq_correntwave]["count"]

			self.SModDungeonScript:SpawnMultiMonster(self.DungeonConfig["NpcKilled_CrossDungeonWava"][self.jq_correntwave]["method"])---ˢ��һ��

		else
			self:G_DungeonEnd(DUNGEON_END_TIME)
		end
	end
end
-----------------------------------------------------------------------------------------------------------------------------
--NPC����ɱ��С��
function CurrentDungeonScript:NpcKilled_KillPet(creature,killer)
	local PetTab = creature:GetModSummoner():GetSummonedUnits()
	if PetTab ~= nil then
		for k , v in pairs(PetTab) do
			v:GetModCombat():KillSelf(PET_KILLSELF_SKILLID,PET_KILLSELF_EFFECT)
		end
	end
end
--NPC������������
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
--NPC������ʱ��������
function CurrentDungeonScript:pcKilledPlotStart_OnTimer(timerid)
	if self.NpcKilledPlotStart_Timer[tostring(timerid)] ~= nil then
		self.SModDungeonScript:PlotStart()
		self.MainHuman:GetModMotionMaster():StopMotion()
		self.Stage:GetModObjs():SuspendCreaturesAI()
		self.SModDungeonScript:LaunchPolt(self.NpcKilledPlotStart_Timer[tostring(timerid)],0,"LaunchPolt")
	end
end

---���¸�������
function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid)----1���µڼ���  2��Сֵ 3���ֵ  4��������str
-- pwdist.log("���¸�������")
	local NewTime = os.time()
	local SurTime = self.HumanOldTime + self.DungeonConfig["JQ_DungeonMaxTime"] - NewTime		----����ʣ��ʱ��
	self.msg.timesec = SurTime
	self.msg.targetlist[Index].count = Ucount
	self.msg.targetlist[Index].maxcount = Umaxcount
	self.msg.targetlist[Index].strid = Ustrid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, self.msg)
end

----������ʱ����
function CurrentDungeonScript:JQ_EndTime()

	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
	for k , v in pairs(CreatureTab) do
		v:LeaveWorld(0)
	end	
	----��ʧ�ܽ���
	self.SModObjs:Broadcast(msgids.SCDungeonFailed, self.msg)

end