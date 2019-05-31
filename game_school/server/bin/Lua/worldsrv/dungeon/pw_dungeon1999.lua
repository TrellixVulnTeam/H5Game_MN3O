CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")

local Dungeon_Stare = 0			----0��������1-��ҽ���2-���鲥�Ž���
local SecenLaunch = {116,}
local DungeonTime = 1			---���������õ��������
-- local BMonter = {"scn1999_benpaodeshibing",}
local kezhene = 80057
local diziID = {80059,80056,80060,80073,}
local diziTalk = {}
function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	self.SModCommon = self.Stage:GetModCommon()
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	self.SModObjs = self.Stage:GetModObjs()
	self.Stage:SetAIEnable(false)	--�رյ�ͼAI
	self.DungeonStartClock = os.time()
	------ˢ��
	self.Stage:GetModCommon():CreatePeriodTimer(0,5,0,"BrushMonter")
	self.Stage:GetModCommon():CreatePeriodTimer(0,5,0,"BrushMonter1")
	self.Stage:GetModCommon():CreatePeriodTimer(0,8,0,"BrushMonter2")
	----NPC˵��
	SetEventHandler(StageEvents.CreatureSpawn,"kezhneeSpawn",{type = kezhene})
	for i = 1,#diziID, 1 do
		SetEventHandler(StageEvents.CreatureSpawn,"diziSpawn",{type = diziID[i]})
	end
	SetEventHandler(StageEvents.PoltEvent,"PoltEvent_KaiChang")
	--self.Stage:GetModCommon():CreatePeriodTimer(0,10,0,"Talk")
end
----���ڰ�Ч��
function CurrentDungeonScript:HeiBaiKai()
	--self.Stage:GetModCommon():BroadcastClientOperation(UI_COLOR,tostring(1))
end
----��ҽ��볡��
function CurrentDungeonScript:HumanEnterEvent(human)
	
	self:G_DungeonStart()
	self.SModDungeonScript:PlotStart()	----��������ӽ�
	self.SModDungeonScript:LaunchPolt(SecenLaunch[1], 0,"DungeonStart")	----�����볡����	
	self.Stage:SetAIEnable(true)	--������ͼAI
	Dungeon_Stare = 1	
	self.Stage:GetModCommon():CreateTimer(2,"HeiBaiKai")
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COLOR,tostring(1))
end

------ˢ�½��
function CurrentDungeonScript:BrushMonter()
	self.SModDungeonScript:SpawnMultiMonster({"scn1999_cunnei_jinbing",})---��ˢ����
end
function CurrentDungeonScript:BrushMonter1()
	self.SModDungeonScript:SpawnMultiMonster({"scn1999_pubu_jinbing",})---��ˢ����
end
function CurrentDungeonScript:BrushMonter2()
		self.SModDungeonScript:SpawnMultiMonster({"scn1999_cunkou_jinbing",})---��ˢ����
end
------NPC ����
function CurrentDungeonScript:kezhneeSpawn(creature)
	self.KeZhenE = creature
end
function CurrentDungeonScript:diziSpawn(creature)
	table.insert(diziTalk,creature)
end
-----NPC˵��
function CurrentDungeonScript:Talk()

	for j= 1, table.getn(diziTalk) do
		local creature = diziTalk[j]:cast('Creature')
		if(creature~=nil)then
			local rand  = math.random(1,100)
			if(rand <= 30)then
				creature:TalkByConfig(117)
			end
		end
	end
	local Mkezhene = self.KeZhenE:cast('Creature')
	if(Mkezhene~=nil)then
		local rand  = math.random(1,100)
		if(rand <= 30)then
			Mkezhene:TalkByConfig(118)
		end
	end
end
-----�������
function CurrentDungeonScript:DungeonStart()
	self.SModDungeonScript:PlotClean()
	if(self.MainHuman~= nil and Dungeon_Stare ~= 2)then
		self.MainHuman:LeaveDungeon()	--��������
		Dungeon_Stare = 3
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_COLOR,tostring(0))
	end
end
function CurrentDungeonScript:Timer_DungeonEnd()
	self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"PlotDungeonEnd")
end
function CurrentDungeonScript:PlotDungeonEnd()
	local clearTime = os.time() - self.DungeonStartClock
	self.SModDungeonScript:CalcScore(clearTime)
end
------�����д�������
function CurrentDungeonScript:PoltEvent_KaiChang(human,plotid,eventstr,eventdata)
	if(eventstr == "chuchang")then
		if(self.MainHuman~=nil)then
			self.MainHuman:LeaveDungeon()	--��������
			--self.Stage:GetModCommon():BroadcastClientOperation(UI_COLOR,tostring(0))
			Dungeon_Stare = 2
		end	
	end
	
end
----�����������
function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)		----�����������
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

