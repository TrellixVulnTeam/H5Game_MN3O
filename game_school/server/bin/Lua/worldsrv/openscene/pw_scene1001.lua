CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
pwngs_require("./Lua/worldsrv/activities/pw_activity_wabao.lua")
-----------------------------------------------------------

local Quest_NPC = {NpcID = {},Quest = {},QuestData = {},}-----������NPC�͹���ɱ����һ�¾����������
Quest_NPC.NpcID[1] = 10003
Quest_NPC.Quest[1] = {1002,1127,1128,}	-------�������� ����ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[1] = {}				-------��������ݱ�

Quest_NPC.NpcID[2] = 10005
Quest_NPC.Quest[2] = {1005,}			-------�������� ����ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[2] = {}				-------��������ݱ�

Quest_NPC.NpcID[3] = 10007
Quest_NPC.Quest[3] = {1007,}			-------������ɫ ����ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[3] = {}				-------��������ݱ�

Quest_NPC.NpcID[4] = 10013
Quest_NPC.Quest[4] = {1044,}			-------��ս���� ����ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[4] = {}				-------��������ݱ�

Quest_NPC.NpcID[5] = 10087
Quest_NPC.Quest[5] = {1038,}			-------��ʧ���� ����ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[5] = {}				-------��������ݱ�

Quest_NPC.NpcID[6] = 10030
Quest_NPC.Quest[6] = {1056,}			-------�������� ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[6] = {}				-------��������ݱ�

Quest_NPC.NpcID[7] = 10036
Quest_NPC.Quest[7] = {1066,}			-------�ٳַ��� ����ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[7] = {}				-------��������ݱ�

Quest_NPC.NpcID[8] = 10044
Quest_NPC.Quest[8] = {1077,}			-------�ٳ����� ����ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[8] = {}				-------��������ݱ�

Quest_NPC.NpcID[9] = 10057
Quest_NPC.Quest[9] = {1095,}			-------�ͽ��ʿ ����ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[9] = {}				-------��������ݱ�

Quest_NPC.NpcID[10] = 10078
Quest_NPC.Quest[10] = {1101,}			-------�ƹ���ʿ ����ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[10] = {}				-------��������ݱ�

Quest_NPC.NpcID[11] = 10064
Quest_NPC.Quest[11] = {1104,}			-------�ܹ����� ����ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[11] = {}			-------��������ݱ�

Quest_NPC.NpcID[12] = 10072
Quest_NPC.Quest[12] = {1115,}			-------��ɫ�ܹ� ����ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[12] = {}			-------��������ݱ�

Quest_NPC.NpcID[13] = 10075
Quest_NPC.Quest[13] = {1118,}			-------�ͽ�Ů�� ����ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[13] = {}			-------��������ݱ�

------------------------����һ�����ξ���

--ˢ����ֺ�����NPC
local Boss1EnterPos 		= {89.35,51.22,195.74}
local Boss1EnterOra 		= {1.0,0.0,0.0}	
local Boss1ID = 10121

local Boss2EnterPos 		= {92.65,51.22,189.72}    --boss������λ��
local Boss2EnterOra 		= {1.0,0.0,0.0}		     --boss�����㳯��
local Boss2ID = 10122



local HumPos 		= {92.65,54.31,220.6}      ---�뿪�ξ�����λ��
local HumPos1 		= {92.61,54.31,220.6}

local MengQuestID = {1144,1146,1147,}--------------�ξ������ʶ����

------------------------------------------------------------------
-----�ξ�������Ϣ
local Dream = {Pos = {},PosX = {},PosZ = {},ID= {},TriggerEnter = {},}
Dream.Pos[1] =	{92.8,51.31,195.06}
Dream.PosX[1] = 18
Dream.PosZ[1] = 18
Dream.ID[1] = 10693 ---NPCID

--[[Dream.Pos[2] =	{369.71,56.79,364.16}
Dream.PosX[2] = 60
Dream.PosZ[2] = 23
Dream.ID[2] = 10693 ---NPCID--]]

Dream.TriggerEnter[1] = {}-----�����ļ�ʱ�����ݴ������
local Humdata = {}
--Dream.Monster[Dream.Humdata[i]] = {}
local Monster = {}

local DreamStrID = {104500,}    ---���״̬���ξ���ʾ

local PoltConfig = {3,4,5,}     -----Ԥ���ؾ���

local QuestID = {1101,1105}  -----��ȡ����������BUFF

local SpeedBuff = 10041050       -----����BUFF

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript() 
	self.SModCommon = self.Stage:GetModCommon()	
	self.SModObjs = self.Stage:GetModObjs()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanResurrect,"HumanResurrect")
	
	SetEventHandler(StageEvents.UseTreasure,"OnUseTreasure")----�ڱ������ĳ����¼�	
	
	--------------ֻ��һ���ֵ�����
	for k = 1, table.getn(Quest_NPC.NpcID) do
		SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHit",{type = Quest_NPC.NpcID[k]})
	end
	for m = 1, table.getn(Quest_NPC.NpcID) do
		SetEventHandler(StageEvents.CreatureKilled,"OnCreatureKilled",{type = Quest_NPC.NpcID[m]})
	end	
--�����ξ�
	SetEventHandler(StageEvents.QuestLeaveDream,"QuestLeaveDream")----������ҵ��뿪��ť	
--�����ξ�����
	self.Stage:CreateTriggerRect(Dream.Pos[1],Dream.PosX[1],Dream.PosZ[1],"OnTriggerEnter_Dream","OnTriggerLeave_Dream")
	--self.Stage:CreateTriggerRect(Dream.Pos[2],Dream.PosX[2],Dream.PosZ[2],"OnTriggerEnter_Dream","OnTriggerLeave_Dream")

-----���ӽ�ȡ����������
	for i = 1,#QuestID, 1 do
		SetEventHandler(StageEvents.QuestAccepted,"Quest_Accepted",{id = QuestID[i]})
	end
end

------�����ȡ����
function CurrentDungeonScript:Quest_Accepted(Qhuman,questid)
	--����BUFF
	local humanquest = Qhuman:cast('Human')
	humanquest:GetModAura():Create(SpeedBuff) --�Ӹ�BUFF
	--pwdist.log("��ü���BUFF")
end


function CurrentDungeonScript:HumanEnterEvent(human)
	if(human == nil)then
		return
	end
	local HuMan= human:cast('Human')	
	local HLevel = HuMan:GetLevel()	----ȡ������ҵ�����״̬
	if(HLevel == nil)then
		return
	end
	local HumID = HuMan:GetID()
	if(HumID == nil)then
		return
	end
-----Ԥ���ؾ���
	self.ModMisc = HuMan:GetModMisc()
	if(HLevel <= 30)then	----�ս��볡��û��ȡ������״̬��ֻ���õȼ���û��
		for i = 1 ,table.getn(PoltConfig) do
			if(PoltConfig[i] ~= nil)then
				self.ModMisc:PrelaodPolts(PoltConfig[i])
				--pwdist.log('���ؾ籾����')
			else
				return
			end
		end
	end	
	human:GetModCombat():SetPkmode(0,0)-----Ϊ��ֹ�������PKģʽ��ʱ���������ﵥ����һ��
end


function CurrentDungeonScript:HumanLeaveEvent(human)
    --self.Stage:GetModDungeonScript():Cleanup()	--*����뿪����������о�������߼������������*
end
function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
end

function CurrentDungeonScript:HumanResurrect(human)  
	--�������ʱ�ģ����еĸ���ǻص�ָ�������
	--human:GetModMotionMaster():ChangePosition(self.ResurrectPos)
end

-- ---------Ұ�ⳡ����Ӣ�ֱ������¼�---------------
function CurrentDungeonScript:CreatureMagicHit(caster,creaturer)	--��������������
	if caster:IsKindOf(CLSID.Human) then			------�ж��ǲ������
		local humankill = caster:cast('Human')
		if(humankill ~= nil and creaturer ~= nil)then
			for k = 1, #Quest_NPC.NpcID,1 do	-------���ж��ٸ�����Ҫ���ű��ж�
				for m = 1, #Quest_NPC.Quest[k],1 do	-------����Ҫɱ����ֵ������м���
					if(humankill:GetModQuest():GetQuestStatus(Quest_NPC.Quest[k][m]) == 2 ) then	----�ж���������Ƿ���Ҫ�ű���ɵ�����
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
-- ---------Ұ�ⳡ����Ӣ������---------------
function CurrentDungeonScript:OnCreatureKilled(Lcreature,killer)
	if(Lcreature ~= nil)then
		local Mcreature = Lcreature:cast('Creature')
		if(Mcreature~=nil)then
			local MonterTypeID = Mcreature:GetCreatureType()
			for k = 1, #Quest_NPC.NpcID,1 do		----#Quest_NPC.NpcIDȷ�ϳ���
				for m = 1, #Quest_NPC.QuestData[k],1 do	----#Quest_NPC.QuestData[k]ȷ�ϴ洢����ҵĳ���
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


----�ξ����


function CurrentDungeonScript:QuestLeaveDream(human)       --����뿪��ť
	human:GetModStatistic():SetViewTag(0)   ----ȥ���˵ı�ʶ 6.26
    human:GetModMotionMaster():ChangePosition(HumPos)	
	human:GetModMotionMaster():MovePosition(HumPos1,"")	
end

--��ҽ����ξ�����
function CurrentDungeonScript:OnTriggerEnter_Dream(trigger,target)
	----��ȡ���ID
    if not target:IsKindOf(CLSID.Human) then --�жϽ�����Ƿ�����
       return
    end

	local Gamercreature = target:cast('Human')
	local GamerId = 0
	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())
		target:GetModStatistic():SetViewTag(GamerId)   ----���˼Ӹ���ʶ 	
	end
	-----�洢������� 
	for i = 1,#Dream.ID, 1 do
		table.insert(Humdata,GamerId)
	end	
	-----��ʼ������洢��
	if ( Monster[GamerId] == nil	)  then
		Monster[GamerId] = {}
	end
	local Gamerteam = -1 
    Gamerteam = Gamercreature:GetTeamId()

	if Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[3]) == 4    then     --������ ����-----�����Ƿ�ˢ���ξ��� ������ξ����������Ƿ��� 0δ����״̬ ����Ǿ�ˢ��
		return					
		--pwdist.log('������ξ�����return')
	end	


	if Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 4     and  (tostring(Gamerteam) == tostring(0) )   then     --������ ����-----�����Ƿ�ˢ���ξ��� ������ξ����������Ƿ��� 0δ����״̬ ����Ǿ�ˢ��
		--pwdist.log('ˢ��=====1111111111111')
		Gamercreature:GetModQuest():EnterDream()
		target:ChangeFaction(13)   ---����ҵ���Ӫ�ó�13
		Gamercreature:GetModLansquenet():ChangeLansFaction()    ----����ҵ��̴���Ӫ���ó�13
		-----ˢ��
		--pwdist.log('ˢ��=====')
		local monster1 = self.SModCommon:SpawnMonsterAtInViewTag(Boss1EnterPos, Boss1EnterOra, Boss1ID, GamerId )
		table.insert(Monster[GamerId],monster1)
		local monster2 = self.SModCommon:SpawnMonsterAtInViewTag(Boss2EnterPos, Boss2EnterOra, Boss2ID, GamerId )
		table.insert(Monster[GamerId],monster2)
		
		--pwdist.log('ˢ��=====end')
	elseif Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[3]) == 4 and	(tostring(Gamerteam) > tostring(0) ) then		--	û�������״̬
		return		
	elseif Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 4 and (tostring(Gamerteam) > tostring(0) ) then		--  ���������״̬		
		target:SendNotifyMsgTo(DreamStrID[1] ,CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(2617))
		return					
	end	
	
	
end

function CurrentDungeonScript:OnTriggerLeave_Dream(trigger,target)
--pwdist.log('�뿪����')
	----��ȡ���ID
    if not target:IsKindOf(CLSID.Human) then --�ж��뿪���Ƿ�����
        return
    end
	---target:ChangeFaction(1)   ---����ҵ���Ӫ�ó�����
	local Gamercreature = target:cast('Human')
	local GamerId = -1
	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())
		target:GetModStatistic():SetViewTag(0)   ----ȥ���˵ı�ʶ 6.26
		--pwdist.log('ȥ����ʶ��')
	end
	----Gamercreature:GetModQuest():LeaveDream()
	if(Monster[GamerId] ~= nil and #Monster[GamerId] > 0) then
			for k = 1, table.getn(Monster[GamerId]) do
				--pwdist.log('��ʼɾ������==='..tostring(Monster[GamerId][k]))
				local Mcreature = Monster[GamerId][k]:cast('Creature')			
				if Mcreature ~= nil then	
					Mcreature:LeaveWorld(0)
				end
				
			end	
		--Monster[GamerId] = {}---��ʼ��	
		target:ChangeFaction(1)   ---����ҵ���Ӫ�ó�����
		Gamercreature:GetModLansquenet():ChangeLansFaction()    ---������̴ӵ���Ӫ�ó�����
		Gamercreature:GetModQuest():LeaveDream()
		Monster[GamerId] = nil
	end	
end


-------------------�ڱ������¼�-------------------------------
function CurrentDungeonScript:OnUseTreasure(human,itemid)---------��Ҷ����ʹ�õĵ���ID
  math.randomseed(os.time())  --�������
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
