----------------------------------------------------------------------
--GetModChallenge():GetCurrLevel()				��ȡ��ǰ��ս����
--GetModChallenge():GetBossID()					��ȡ���bossid
--GetModChallenge():GetExistTime()				��ȡ��������ʱ�䣨����Ϊ��λ��
--GetModChallenge():OnStart()					������ʼ
--GetModChallenge():OnEnd(int32 nResult)		��������0-ʧ�� 1-�ɹ�
--GetModChallenge():OnLeave()					����뿪����
----------------------------------------------------------------------
CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
-----------------------------------------------------------


-----------------------------------------------------------
--��������
-----------------------------------------------------------
ChallengeConfig = {}
ChallengeConfig.PlayerEnterPos 		= {45.6, 61.5, 40.2}     --��ҳ�����λ��-
ChallengeConfig.PlayerEnterOra 		= {0.0,0.0,1.0}	    --��ҳ����㳯��-
ChallengeConfig.BossEnterPos 		= {45.4, 61.5, 50.2}     --boss������λ��-
ChallengeConfig.BossEnterOra 		= {0.0,0.0,-1.0}	     --boss�����㳯��-
ChallengeConfig.MovePos				= {45.1,61.5,58.7}

CurrentDungeonScript.CurrLevel = 1			--����
CurrentDungeonScript.BossID = 0				--bossid
CurrentDungeonScript.ExistTime = 60		--��������ʱ��
CurrentDungeonScript.ExistTimer = 0			--�������ڶ�ʱ��
CurrentDungeonScript.Result = 0				--�������0-ʧ�� 1-�ɹ�
CurrentDungeonScript.CurrLevelFightActive = false --���ڷ�ֹ���翨ʱ���ˢ��

local QuestID = {1404}
-----------------------------------------------------------
--����������ر�
-----------------------------------------------------------
function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()
	self.SModCommon = self.Stage:GetModCommon()
	
	SetEventHandler(StageEvents.HumanEnter,			"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,			"HumanLeaveEvent")
    SetEventHandler(StageEvents.CreatureKilled,		"CreatureKilled")
    SetEventHandler(StageEvents.HumanKilled,		"HumanKilled")
	
	for i = 1,#QuestID, 1 do
		SetEventHandler(StageEvents.QuestCompleted,"Quest_Completed",{id = QuestID[i]})
	end
end

function CurrentDungeonScript:Cleanup()
end

------��������¼�
function CurrentDungeonScript:Quest_Completed(Qhuman,questid)
	self.SModDungeonScript:CreateTimer(4,"Leave")
end
-----------------------------------------------------------
--��ҽ������뿪,�����븴��
-----------------------------------------------------------
function CurrentDungeonScript:HumanEnterEvent(human)
	--pwdist.log("��ս����CurrentDungeonScript:HumanEnterEvent")
	if(human == nil)then
		return
	end
	self.MainHuman:GetModStatistic():SetPercentHP(1)
	self.MainHuman:GetModMagic():ClearMagicCD()
	human:GetModMotionMaster():ChangePosition(ChallengeConfig.PlayerEnterPos)
	human:GetModMotionMaster():ChangeOrientation(ChallengeConfig.PlayerEnterOra)
	self.CurrLevel = human:GetModChallenge():GetCurrLevel()
	self.BossID = human:GetModChallenge():GetBossID()
	self.ExistTime = human:GetModChallenge():GetExistTime()
	self.MainHuman:GetModChallenge():OnStart()	--֪ͨ������ˢ�³���
	self.Stage:GetModDetour():EnableMotionBlock(1,true)
	self.Stage:GetModDetour():EnableMotionBlock(0,true)
	self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(5),tostring(UI_CHALLENGE_TIMER_BEGIN))
	self.SModCommon:CreateTimer(5, "OnFightBegin")
	self.SModCommon:CreateTimer(0, "BeginSpawnMonster")
	self.SModDungeonScript:CancelTimer(self.ExistTimer)
	self.ExistTimer = self.SModCommon:CreateTimer(self.ExistTime + 5, "OnExistTimeOver")
	self.SModDungeonScript:PlotStart()
end

function CurrentDungeonScript:HumanLeaveEvent(human)
	self.SModDungeonScript:CancelTimer(self.ExistTimer)
    human:GetModChallenge():OnLeave()
	self.Stage:GetModDungeonScript():Cleanup()	--*����뿪����������о�������߼������������
end

function CurrentDungeonScript:HumanKilled(human,killer)
	self.SModDungeonScript:CancelTimer(self.ExistTimer)
	self.Result = 0
	human:GetModRealive():HideRealiveButton(true)
	self.SModDungeonScript:CreateTimer(3,"Timer_Realive")
	self.MainHuman:GetModChallenge():OnEnd(0)
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
	if(CreatureTab ~=nil)then
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end
	end
	
end

function CurrentDungeonScript:Timer_Realive()
	self.MainHuman:GetModRealive():Realive(self.MainHuman:GetPosition(), 0)
	self.SModDungeonScript:CreateTimer(7,"Leave")

end
function CurrentDungeonScript:Leave()
	self.MainHuman:LeaveDungeon()
end
function CurrentDungeonScript:OnExistTimeOver()
	self.SModDungeonScript:CancelTimer(self.ExistTimer)
	self.MainHuman:GetModMotionMaster():StopMotion()
	self.Stage:GetModObjs():ClearTrap()
	self.Stage:GetModObjs():ClearPuppet()
	self.MainHuman:CloseHint(0)
	self.Result = 0
	self.MainHuman:GetModChallenge():OnEnd(0)
	self.MainHuman:LeaveDungeon()
end

-----------------------------------------------------------
--��ʼ������
-----------------------------------------------------------
function CurrentDungeonScript:OnFightBegin()	--����XXʱ���ʼˢ��
	--pwdist.log("��ս����CurrentDungeonScript:OnFightBegin")
	--֪ͨ�ͻ��˸�������ʱ��
	local msg = { time = self.ExistTime }
	self.MainHuman:SendMsg(msgids.SCChallengeExistTime,msg)
	--��ֹ���翨��������ˢ��
	if self.CurrLevelFightActive then
		pwdist.log(self.MainHuman:GetName() .. ',Fight already begin')
		return
	end
	self.CurrLevelFightActive = true
	
	self.SModDungeonScript:PlotStart()	
	if self.BossID > 0 then
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(41597))			--������ʾ����ʼ��ս
		self.Stage:GetModObjs():SuspendCreaturesAI()
		self.MainHuman:OpenAutoCombat()
		self.Stage:GetModObjs():ResumeCreaturesAI()
	end	
	self.SModDungeonScript:PlotClean()	
end
----��ǰˢ��
function CurrentDungeonScript:BeginSpawnMonster()
	if self.BossID > 0 then
		self:SpawnMonster()
		--self.BossCreature:SuspendAITimed(3)
		self.Stage:GetModObjs():SuspendCreaturesAI()
	end
end
-----------------------------------------------------------
--��������
-----------------------------------------------------------
function CurrentDungeonScript:SpawnMonster()
	--pwdist.log("��ս����CurrentDungeonScript:SpawnMonster")
	self.BossCreature = self.SModCommon:SpawnMonsterAt(ChallengeConfig.BossEnterPos, ChallengeConfig.BossEnterOra, self.BossID)
end

-----------------------------------------------------------
--ս������
-----------------------------------------------------------
function CurrentDungeonScript:CreatureKilled(creature,killer, hurttype)	--�������ﱻɱ�¼�
	--pwdist.log("��ս����CurrentDungeonScript:CreatureKilled")
	self.SModDungeonScript:CancelTimer(self.ExistTimer)
	self.Result = 1
	self.CurrLevelFightActive = false
	self.SModDungeonScript:CreateTimer(DUNGEON_END_TIME,"TimerFightEnd")
	self.MainHuman:GetModChallenge():OnEnd(1)
	self.MainHuman:CloseAutoCombat()--�ص��Զ�ս������ֹBOSS������ҷ��س�����
end

-----------------------------------------------------------
--ս����������
-----------------------------------------------------------
function CurrentDungeonScript:TimerFightEnd()
	if self.CurrLevel < self.MainHuman:GetModChallenge():GetMaxLevel() then
		--self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(5),tostring(UI_CHALLENGE_TIMER_NEXT))
		self.SModDungeonScript:CreateTimer(5,"DungeonHandle")
		self.SModDungeonScript:CreateTimer(4,"ChallengePos")
		self.SModDungeonScript:PlotStart()	----��������ӽ�
		local ret = self.MainHuman:GetModMotionMaster():MovePosition(ChallengeConfig.MovePos,"")
	else
		--self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(5),tostring(UI_CHALLENGE_TIMER_END))
		self.SModDungeonScript:CreateTimer(6,"PassAllDungeonHandle")
	end
	--֪ͨ�ͻ��������Ϣ����
	--local humanCurrLevel = self.MainHuman:GetModChallenge():GetCurrLevel()
	--local humanMaxPassLevel = self.MainHuman:GetModChallenge():GetMaxPassLevel() 	
	--local msg = { curr_level = humanCurrLevel, max_pass_level = humanMaxPassLevel }
	--self.MainHuman:SendMsg(msgids.SCChallengeQuery,msg)
end

function CurrentDungeonScript:ChallengePos()	--������
	self.MainHuman:CloseAutoCombat()-----�ر��Զ�ս��
	self.MainHuman:GetModMotionMaster():StopMotion()
	self.MainHuman:GetModMotionMaster():ChangePosition(ChallengeConfig.PlayerEnterPos)
end
function CurrentDungeonScript:DungeonHandle()	--������
	self.MainHuman:GetModMotionMaster():StopMotion()
	self.Stage:GetModObjs():ClearTrap()
	self.Stage:GetModObjs():ClearPuppet()
	self.MainHuman:CloseHint(0)
	self.SModDungeonScript:CreateTimer(1,"TimerPlotNextDungeon")	--1��󲥷ŵڶ�������
end

function CurrentDungeonScript:TimerPlotNextDungeon()
	self.SModDungeonScript:PlotClean()
	self:HumanEnterEvent(self.MainHuman)	--����ִ�н�ɫ����
end

function CurrentDungeonScript:PassAllDungeonHandle()
	self.MainHuman:GetModMotionMaster():StopMotion()
	self.Stage:GetModObjs():ClearTrap()
	self.Stage:GetModObjs():ClearPuppet()
	self.MainHuman:CloseHint(0)
	self.MainHuman:LeaveDungeon()
	self.MainHuman:GetModChallenge():OnLeave()
	self.Stage:GetModDungeonScript():Cleanup()	--*����뿪����������о�������߼������������
end
