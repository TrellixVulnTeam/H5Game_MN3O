CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------

------------------------����һ�����ξ���

--ˢ����ֺ�����NPC
local Boss1EnterPos 		= {49.6,50,62}
local Boss1EnterOra 		= {1.0,0.0,0.0}	
local Boss1ID = 10119

local Boss2EnterPos 		= {52,50,65}    --boss������λ��
local Boss2EnterOra 		= {1.0,0.0,0.0}		     --boss�����㳯��
local Boss2ID = 10119

local Boss3EnterPos 		= {52,50,59}
local Boss3EnterOra 		= {1.0,0.0,0.0}		
local Boss3ID = 10119

local HumPos 		= {100.6,51.6,66.7}      ---�뿪�ξ�����λ��
local HumPos1 		= {100.6,51.6,66.7}      ---�뿪�ξ�����λ��

local MengQuestID = {1398,}--------------�ξ������ʶ����
------------------------------------------------------------------
-----�ξ�������Ϣ
local Dream = {Pos = {},PosX = {},PosZ = {},ID= {},TriggerEnter = {},}
Dream.Pos[1] =	{53.08,49.83,63.62}
Dream.PosX[1] = 35
Dream.PosZ[1] = 35
Dream.ID[1] = 10693 ---NPCID

Dream.TriggerEnter[1] = {}-----�����ļ�ʱ�����ݴ������
local Humdata = {}
--Dream.Monster[Dream.Humdata[i]] = {}
local Monster = {}

local DreamStrID = {104500,}    ---���״̬���ξ���ʾ

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript() 
	self.SModCommon = self.Stage:GetModCommon()	
	self.SModObjs = self.Stage:GetModObjs()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanResurrect,"HumanResurrect")

	SetEventHandler(StageEvents.QuestLeaveDream,"QuestLeaveDream")----������ҵ��뿪��ť	
-----�����ξ�����
	self.Stage:CreateTriggerRect(Dream.Pos[1],Dream.PosX[1],Dream.PosZ[1],"OnTriggerEnter_Dream","OnTriggerLeave_Dream")


end

function CurrentDungeonScript:HumanEnterEvent(human)

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




----�ξ����


function CurrentDungeonScript:QuestLeaveDream(human)       --����뿪��ť
	human:GetModStatistic():SetViewTag(0)   ----ȥ���˵ı�ʶ 6.26
    human:GetModMotionMaster():ChangePosition(HumPos)	
	human:GetModMotionMaster():MovePosition(HumPos1,"")	
end

--��ҽ����ξ�����
function CurrentDungeonScript:OnTriggerEnter_Dream(trigger,target)
pwdist.log('����=====')
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
	if Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 0     and  (tostring(Gamerteam) == tostring(0) )   then     --������ ����-----�����Ƿ�ˢ���ξ��� ������ξ����������Ƿ��� 0δ����״̬ ����Ǿ�ˢ��
		pwdist.log('ˢ��=====1111111111111')
		Gamercreature:GetModQuest():EnterDream()
		target:ChangeFaction(13)   ---����ҵ���Ӫ�ó�13
		Gamercreature:GetModLansquenet():ChangeLansFaction()    ----����ҵ��̴���Ӫ���ó�13
	-----ˢ��
		pwdist.log('ˢ��=====')
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
		
		
		
		pwdist.log('ˢ��=====end')
	elseif Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 4 and	(tostring(Gamerteam) > tostring(0) ) then		--	û�������״̬
		return		
	elseif Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 0 and 	(tostring(Gamerteam) > tostring(0) ) then		--  ���������״̬		
		target:SendNotifyMsgTo(DreamStrID[1] ,CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(2617))
		return					
	end	

	
	
end

function CurrentDungeonScript:OnTriggerLeave_Dream(trigger,target)
pwdist.log('�뿪����')
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
		pwdist.log('ȥ����ʶ��')
	end
	----Gamercreature:GetModQuest():LeaveDream()
	if(Monster[GamerId] ~= nil and #Monster[GamerId] > 0) then
			for k = 1, table.getn(Monster[GamerId]) do
				pwdist.log('��ʼɾ������==='..tostring(Monster[GamerId][k]))
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

