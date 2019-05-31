CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
	
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
pwngs_require("./Lua/worldsrv/activities/pw_challenge_LiveData.lua")

local MaxLevel = 1			----��ȡ�߻����õ���߲㣨�ģ�
local CurrentLevel = 1		----��ȡ�����߳ɹ���ս����(gai)
local MonsterInfo  = 0 		----ÿ��Ĺ�����Ϣ
local DownTime = 5			----ÿ��ĵ���ʱʱ��
local CurrWave = 1			--��ǰ��ˢС�ֵĲ���
local MonterNum = 0			----ÿ��Ĺ������
local BeginDownTime = 1		----����ʱ���ˢ��
local ExistTime = 0			-----��¼ÿ�㵹��ʱʱ��ı���
local WaveExistTime	= 0		-----��¼ÿ���ֵĴ���ʱ��
local CurrLevelFightActive = false 	--���ڷ�ֹ���翨ʱ���ˢ��
local StrInfo = {4040,4041,4042,4043,4044,4045,4046,4047,4048,}	----ÿ����������ʾ���һ���ڼ�ֶ���ʱ�䲻��������ͨ������������
local jinduIndex = 1											-----����ÿ�������ѭ����ʱ���������������õģ�����9��ʱ�򣬾Ͳ�����ʾ��
function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	-- SetEventHandler(StageEvents.CreatureKilled,"Monster_Die")
	self.SModCommon = self.Stage:GetModCommon()

	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	self.SModObjs = self.Stage:GetModObjs()

--pwdist.log("Ⱥ�ָ���----��������")		
end


----��ҽ��볡��
function CurrentDungeonScript:HumanEnterEvent(human) 
	local Hum = human:cast("Human")
	if(Hum == nil)then
		return
	end
	self.MainHuman:GetModStatistic():SetPercentHP(1)----��������������ֵ��Ϊ100%
	self.MainHuman:GetModMagic():ClearMagicCD()		----�����ҵļ���CD	

	MaxLevel = self.MainHuman:GetModChallengeLive():GetMaxLevel()----��ȡ�߻����õ���߲�
	CurrentLevel = self.MainHuman:GetModChallengeLive():GetCurrLevel()----��ȡ�����߳ɹ���ս����
	if(CurrentLevel == nil or CurrentLevel < 1)then
		return
	end
	local HumPos = ChallengeLive.MonsterTable[CurrentLevel]["hum_pos"]
	if(HumPos == nil)then
		self.MainHuman:GetModMotionMaster():ChangePosition(ChallengeLive.MonsterPosition[1][1])---������ҽ��볡���������
		self.MainHuman:GetModMotionMaster():ChangeOrientation(ChallengeLive.MonsterPosition[1][2])---������ҽ��볡���ĳ���
	end

	local pos_info = ChallengeLive.MonsterPosition[HumPos]
	if(HumPos ~=nil)then
	
		self.MainHuman:GetModMotionMaster():ChangePosition(pos_info[1])---������ҽ��볡���������
		self.MainHuman:GetModMotionMaster():ChangeOrientation(pos_info[2])---������ҽ��볡���ĳ���		
	end

	if(CurrentLevel <= MaxLevel)then
		self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(DownTime),tostring(UI_CHALLENGE_TIMER_BEGIN))---��Ļ�м䵹��ʱ��ʾ��
		self.SModCommon:CreateTimer(DownTime, "OnFightBegin")	----����ʱ��ʼս��
		self.SModCommon:CreateTimer(BeginDownTime, "SpawnMonster")	----����ʱ���ˢ��
		self.MainHuman:GetModChallengeLive():OnStart()	--֪ͨ������ˢ�³���
		--self.SModDungeonScript:PlotStart()---����������
		self.BroadcastTimer = self.Stage:GetModCommon():CreatePeriodTimer(5,5,0,"OnTimerStrInfo")
	else
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,4015)
		self.SModDungeonScript:CreateTimer(9,"Leave")	------X���Զ���������뿪����		
	end
----------���ͻ��˷���ʱ��
	local Wtime = ChallengeLive.MonsterTable[CurrentLevel]["winTime"]	----ÿ���ʱ�����
	if(Wtime == nil)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,4016)
		return
	end
	if(Wtime > 0 and CurrentLevel >= 1)then
		local msg = { time = Wtime }
		self.MainHuman:SendMsg(msgids.SCChallengeLiveExistTime,msg)		---���ͻ��˷���ʱ��
--pwdist.log("             ������սʱ��======="..Wtime.."    "..tostring(pos_info[1]).."    "..tostring(HumPos))
	end

--pwdist.log("Ⱥ�ָ���----��ҽ��뵱ǰ����===="..CurrentLevel.."     ��߲���=="..MaxLevel)
end
----��ʼս��
function CurrentDungeonScript:OnFightBegin()	--����XXʱ���ʼˢ��

	if(CurrLevelFightActive == true)then
		return
	end
	local Wtime = ChallengeLive.MonsterTable[CurrentLevel]["winTime"]
	if(Wtime == nil or Wtime <= 0)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,4016)
		return
	end	
	ExistTime = self.SModCommon:CreateTimer(Wtime, "DungeonEndTime")
	--self.SModDungeonScript:PlotClean()	------�ر�������	
	self.SModObjs:ResumeCreaturesAI()---�ָ����й����AI
	-- self.MainHuman:OpenAutoCombat()----�����Զ�ս��	
end
------ѭ����ʾ��Ҽ�ֲ�����ͨ��
function CurrentDungeonScript:OnTimerStrInfo()
	if(jinduIndex <= 9) then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,StrInfo[jinduIndex])
	end
	jinduIndex = jinduIndex+1
end

------ˢ��
function CurrentDungeonScript:SpawnMonster()
	CurrLevelFightActive = true
--pwdist.log("��ʼˢ��")
	if(CurrLevelFightActive == false or CurrentLevel > MaxLevel)then
		return
	end
	local win_type = ChallengeLive.MonsterTable[CurrentLevel]["win_type"]
	if(win_type == nil)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,4016)
		return
	end
	if(win_type == ChallengeLive.WIN_TYPE_KILLALL)then	-----����ˢ������ȷ��ˢ�ַ�ʽ
		self:SpawnCommonCreature(ChallengeLive.MonsterTable[CurrentLevel]["monster_table"][1])	
	elseif(win_type == ChallengeLive.WIN_TYPE_KILLBYWAVE)then	
		self:SpawnCommonCreature(ChallengeLive.MonsterTable[CurrentLevel]["monster_table"][1])
		local timeLength = ChallengeLive.MonsterTable[CurrentLevel]["time_nodes"]
		WaveExistTime = self.SModCommon:CreateTimer(timeLength[1], "SpawnWaveMonster")
	end
	
	self.SModObjs:SuspendCreaturesAI()	----ˢ�ֵ�ʱ��ֹͣ���й���AI
	CurrLevelFightActive = false
--pwdist.log("ˢ�ֽ���")
end

function CurrentDungeonScript:SpawnCommonCreature(param)
	if param == nil then
		return
	end
	for k = 1, #param,1 do
			local j = 1
			local m = 1
			local creature_id	= param[k]["MonterID"]
			local creature_cnt	= param[k]["cnt"]
			local creature_buffs = param[k]["buffs"]
			local creature_poslist	 = param[k]["pos"]
			
			for i = 1, creature_cnt, 1 do
				if(#creature_poslist > 0)then
					local pos_info = ChallengeLive.MonsterPosition[creature_poslist[j]]
					local OBJ = self.SModCommon:SpawnMonsterAt(pos_info[1], pos_info[2],creature_id)
					MonterNum = MonterNum + 1
--pwdist.log("ˢ����"..MonterNum.."ֻ��")
					if(#creature_buffs > 0)then
						OBJ:GetModAura():Create(creature_buffs[m])
					end	
				end							
				if m < #creature_buffs then
					m = m + 1					
				else
					m = 1
				end
				
				if j < #creature_poslist then
					j = j + 1
				else
					j = 1
				end
			end
	end
end	
-----ˢ�²�����
function CurrentDungeonScript:SpawnWaveMonster()
	CurrWave = CurrWave + 1
--pwdist.log("��ǰ�Ƕನ�ֲ㣬ˢ�µ�"..CurrWave.."����")	
	local win_type = ChallengeLive.MonsterTable[CurrentLevel]["win_type"]
	if(win_type == ChallengeLive.WIN_TYPE_KILLALL )then	
		return
	end
	if(CurrWave <= ChallengeLive.MonsterTable[CurrentLevel]["win_param"])then
		self:SpawnCommonCreature(ChallengeLive.MonsterTable[CurrentLevel]["monster_table"][CurrWave])
		local timeLength = ChallengeLive.MonsterTable[CurrentLevel]["time_nodes"]
		self.SModDungeonScript:CancelTimer(WaveExistTime)-----ȡ�������ļ�ʱ��
		WaveExistTime = self.SModCommon:CreateTimer(timeLength[CurrWave-1], "SpawnWaveMonster")	
		self.SModDungeonScript:CancelTimer(self.BroadcastTimer)		
	end
end		
	

------��������	
function CurrentDungeonScript:Monster_Die(creature,killer)
	MonterNum = MonterNum -1
	local win_type = ChallengeLive.MonsterTable[CurrentLevel]["win_type"]
	if(MonterNum <= 0 and CurrentLevel <= MaxLevel)then
		
		if(win_type == ChallengeLive.WIN_TYPE_KILLALL)then		
			self.SModCommon:CreateTimer(6, "NextLayer")
			--self.MainHuman:GetModChallengeLive():OnEnd(1)-----�����ɹ�
-- pwdist.log("   ��"..CurrentLevel.."����ս�ɹ�   ")
			MonterNum = 0
			if(ExistTime ~= 0)then
				self.SModDungeonScript:CancelTimer(ExistTime)-----֮ǰ���в�ļ�ʱ��
				self.MainHuman:CloseAutoCombat()-----�ر��Զ�ս��
				self.SModDungeonScript:CancelTimer(self.BroadcastTimer)
--pwdist.log("ȡ�������ʱ��")
			end
		elseif(win_type == ChallengeLive.WIN_TYPE_KILLBYWAVE)then		
			if(CurrWave < ChallengeLive.MonsterTable[CurrentLevel]["win_param"])then	
				self:SpawnWaveMonster()
			else
				self.SModCommon:CreateTimer(6, "NextLayer")
				--self.MainHuman:GetModChallengeLive():OnEnd(1)-----�����ɹ�
				self.MainHuman:CloseAutoCombat()-----�ر��Զ�ս��
-- pwdist.log("    ��"..CurrentLevel.."����ս�ɹ�")				
				if(ExistTime ~= 0)then				
					self.SModDungeonScript:CancelTimer(ExistTime)-----֮ǰ���в�ļ�ʱ��
					self.SModDungeonScript:CancelTimer(WaveExistTime)	-----ȡ����ǰ���ʱ��
					self.SModDungeonScript:CancelTimer(self.BroadcastTimer)
--pwdist.log("ȡ������Ͳ�����ʱ��")
				end	
				CurrWave = 1
				WaveExistTime = 0
				MonterNum = 0		
				jinduIndex = 1
			end
		end
		CurrLevelFightActive = false
	end
--pwdist.log("������������ ʣ�������=="..MonterNum)

end

	-------������һ�� 
function CurrentDungeonScript:NextLayer()
	if(CurrentLevel < MaxLevel)then
		self.SModDungeonScript:PlotClean()
		self:HumanEnterEvent(self.MainHuman)	--����ִ�н�ɫ����
		jinduIndex = 1
--pwdist.log("������½���     ��һ��")
	else
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,4015)
		self.SModDungeonScript:CreateTimer(9,"Leave")	------X���Զ���������뿪����
--pwdist.log("�Ѵ���߲㣬�ȴ�����")
	end

end

-- [[------��������	
-- function CurrentDungeonScript:Monster_Die(creature,killer)
	-- if( CurrentLevel <= MaxLevel)then			
		-- self.SModCommon:CreateTimer(6, "NextLayer")
		-- self.MainHuman:GetModChallengeLive():OnEnd(1)-----�����ɹ�
		-- self.MainHuman:CloseAutoCombat()-----�ر��Զ�ս��
-- pwdist.log("    ��"..CurrentLevel.."����ս�ɹ�")				
		-- if(ExistTime ~= 0)then				
			-- self.SModDungeonScript:CancelTimer(ExistTime)-----֮ǰ���в�ļ�ʱ��
			-- self.SModDungeonScript:CancelTimer(WaveExistTime)	-----ȡ����ǰ���ʱ��
-- pwdist.log("ȡ������Ͳ�����ʱ��")
		-- end	
		-- CurrWave = 1
		-- WaveExistTime = 0
		-- MonterNum = 0				
		-- CurrLevelFightActive = false
	-- end
-- pwdist.log("������������ ʣ�������=="..MonterNum)

-- end
-- ]]

------ÿ�㵽�����ʱ��
function CurrentDungeonScript:DungeonEndTime()
	if( CurrentLevel <= MaxLevel)then			
		self.SModCommon:CreateTimer(6, "NextLayer")
		self.MainHuman:GetModChallengeLive():OnEnd(1)-----�����ɹ�
		self.MainHuman:CloseAutoCombat()-----�ر��Զ�ս��
--pwdist.log("    ��"..CurrentLevel.."����ս�ɹ�")				
		if(ExistTime ~= 0)then				
			self.SModDungeonScript:CancelTimer(ExistTime)-----֮ǰ���в�ļ�ʱ��
			self.SModDungeonScript:CancelTimer(WaveExistTime)	-----ȡ����ǰ���ʱ��
			self.SModDungeonScript:CancelTimer(self.BroadcastTimer)
--pwdist.log("ȡ������Ͳ�����ʱ��")
		end	
		CurrWave = 1
		WaveExistTime = 0
		MonterNum = 0		
		jinduIndex = 1
		CurrLevelFightActive = false
	end
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
	if(CreatureTab ~=nil)then
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end
	end
end

--[[ 
------ÿ�㵽�����ʱ��         ---�������ȷ�ı���
function CurrentDungeonScript:DungeonEndTime()
	if(ExistTime ~= 0 )then
		self.SModDungeonScript:CancelTimer(ExistTime)-----֮ǰ���в�ļ�ʱ��
--pwdist.log("ȡ�������ʱ��")
	end
	if(WaveExistTime ~= 0)then
		self.SModDungeonScript:CancelTimer(WaveExistTime)	-----ȡ����ǰ���ʱ��
--pwdist.log("ȡ�����㲨����ʱ��")
	end
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
	if(CreatureTab ~=nil)then
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end
	end
	self.MainHuman:GetModChallengeLive():OnEnd(0)-----����ʧ��
	self.MainHuman:CloseAutoCombat()-----�ر��Զ�ս��
	self.SModDungeonScript:CreateTimer(9,"Leave")	------X���Զ���������뿪����
--pwdist.log("��ǰ��ʣ��ʱ��Ϊ0    ����ʧ��")
end
--]]

----�����������
function CurrentDungeonScript:HumanKilled(human,killer)  

	if(ExistTime ~= 0 )then
		self.SModDungeonScript:CancelTimer(ExistTime)-----֮ǰ���в�ļ�ʱ��	
		self.SModDungeonScript:CancelTimer(self.BroadcastTimer)
--pwdist.log("ȡ�������ʱ��")
	end
	if(WaveExistTime ~= 0)then
		self.SModDungeonScript:CancelTimer(WaveExistTime)	-----ȡ����ǰ���ʱ��
		self.SModDungeonScript:CancelTimer(self.BroadcastTimer)
--pwdist.log("ȡ�����㲨����ʱ��")
	end
	human:GetModRealive():HideRealiveButton(true)
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
	if(CreatureTab ~= nil)then
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end
	end
	self.SModDungeonScript:CreateTimer(3,"RealiveTime")
	self.MainHuman:GetModChallengeLive():OnEnd(0)	-----����ʧ��
	self.MainHuman:CloseAutoCombat()-----�ر��Զ�ս��
--pwdist.log("�����������ʧ��")
end


----��������󸴻����
function CurrentDungeonScript:RealiveTime()
	self.MainHuman:GetModRealive():Realive(self.MainHuman:GetPosition(), 0)
	self.SModDungeonScript:CreateTimer(9,"Leave")	------X���Զ���������뿪����
end
-----����뿪����
function CurrentDungeonScript:Leave()
	self.MainHuman:LeaveDungeon()
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

