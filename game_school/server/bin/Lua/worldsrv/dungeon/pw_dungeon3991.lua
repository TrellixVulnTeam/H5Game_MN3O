CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
----------------------------------------------------------������Ϣ�б�


	local msg = { targetlist = {} }
		
	msg.timesec = 600-----1 * 60	----������ʱ��
	
	msg.targetlist[1] = 
	{
		type = 1,
		strid = 50001,
		count = 0,
		maxcount = 1,
	}
	
	msg.targetlist[3] = 
	{
		type = 1,
		strid = 50001,
		count = 0,
		maxcount = 1,
	}
	
	
	msg.targetlist[2] = 
	{
		type = 1,
		strid = 50001,
		count = 0,
		maxcount = 1,
	}
local Dungeon_Stare = 0				----����״̬
	
	
	
	
----�볡ָ��
local ruchangGuidePos = { Pos = {} }
ruchangGuidePos.Pos[1] = {125.7,11.4,230.6}
ruchangGuidePos.Pos[2] = {125.7,11.4,218.3}
ruchangGuidePos.Pos[3] = {137.5,11.4,212}
ruchangGuidePos.Pos[4] = {146.2,11.4,192.6}
ruchangGuidePos.Pos[5] = {139.7,11.4,167.4}
ruchangGuidePos.Pos[6] = {126.2,11.4,165}
ruchangGuidePos.Pos[7] = {125.7,11.4,146}
local ruchangGuideOrg = { Org = {} }
ruchangGuideOrg.Org[1] = {0.0,0.0,-1.0}
ruchangGuideOrg.Org[2] = {0.0,0.0,-1.0}
ruchangGuideOrg.Org[3] = {1.0,0.0,0.0}
ruchangGuideOrg.Org[4] = {0.0,0.0,-1.0}
ruchangGuideOrg.Org[5] = {-1.0,0.0,0.0}
ruchangGuideOrg.Org[6] = {0.0,0.0,-1.0}	
ruchangGuideOrg.Org[7] = {0.0,0.0,-1.0}



----2BOSSָ��
local BossGuidePos = { Pos = {} }
BossGuidePos.Pos[1] = {115.7,11.4,157}
BossGuidePos.Pos[2] = {160.7,11.4,176.6}
BossGuidePos.Pos[3] = {90,11.4,192}
BossGuidePos.Pos[4] = {68.5,11.4,202.8}
BossGuidePos.Pos[5] = {43,11.4,218.2}
BossGuidePos.Pos[6] = {31.5,11.4,201.8}
BossGuidePos.Pos[7] = {76.4,11.4,144}
local BossGuideOrg = { Org = {} }
BossGuideOrg.Org[1] = {0.0,0.0,1.0}
BossGuideOrg.Org[2] = {-0.6,0.0,0.8}
BossGuideOrg.Org[3] = {-1.0,0.0,0.0}
BossGuideOrg.Org[4] = {-0.8,0.0,0.6}
BossGuideOrg.Org[5] = {-1.0,0.0,0.0}
BossGuideOrg.Org[6] = {0.0,0.0,-1.0}	
BossGuideOrg.Org[7] = {0.0,0.0,-1.0}



local GuideObj = {}					-----����ָ������ʱ����
local GuideID = 80001				-----ָ����ͷID	
	


	
	
	
function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	self.SModCommon = self.Stage:GetModCommon()
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled1",{type = 11017})
    SetEventHandler(StageEvents.CreatureKilled,"NpcKilled2",{type = 11014})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled3",{type = 49002})
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	self.SModObjs = self.Stage:GetModObjs()
    self.SModDungeonScript:CreateTimer(1,"Timer_Finger")-----------------------------------��������

end



function CurrentDungeonScript:Timer_Finger()
	--[[self:CreatGuide({125.7,11.4,230.6},{0.0,0.0,-1.0},80001)		-----------------��������--]]
	

	self:CreatGuide(ruchangGuidePos.Pos,ruchangGuideOrg.Org,GuideID)





--[[	self.SModDungeonScript:CreateTimer(1,"Timer_Hint")--]]----------------------------------���ԼӸ��������ߵ���ʾ
end



local Boss2EnterPos 		= {36,12.4,218}     --boss������λ��
local Boss2EnterOra 		= {0.0,0.0,1.0}	     --boss�����㳯��
local Boss2ID = 11014				--bossid


local Boss3EnterPos 		= {77,12.4,132}     --boss������λ��
local Boss3EnterOra 		= {0.0,0.0,1.0}	     --boss�����㳯��
local Boss3ID = 49002				--bossid



--[[local GuaiEnterPos 		= {126,12.4,70}     --������λ��
local GuaiEnterbanjing 		= 10	     --�뾶
local GuaiID = 49001				--id
local GuaiEntershuliang   =    15   --����
--]]


function CurrentDungeonScript:SpawnMonster2()
	self.SModCommon:SpawnMonsterAt(Boss2EnterPos, Boss2EnterOra, Boss2ID)

end

--[[function CurrentDungeonScript:SpawnMonster3()
	self.SModCommon:SpawnMonsterAt(Boss3EnterPos, Boss3EnterOra, Boss3ID)

end--]]




--[[function CurrentDungeonScript:SpawnMonsterRandom()
	local xiaoguaiCreature = self.SModCommon:SpawnMonsterRandom(GuaiEnterPos, GuaiEnterbanjing, GuaiID, GuaiEntershuliang)
end
--]]


function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)

end

function CurrentDungeonScript:HumanEnterEvent(human)
	self.time9 = self.SModDungeonScript:CreateTimer(DUNGEON_START_TIME,"Timer9")
	self.SModDungeonScript:PlotStart()
	self.ModQuest = human:GetModQuest()
	--[[self:SpawnMonster()
	self:SpawnMonsterRandom()--]]
	self.SModCommon:CreateTimer(msg.timesec,"EndTime")
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)


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

function CurrentDungeonScript:Timer9()
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"dungeon_start")
	self.SModDungeonScript:PlotClean()
end

function CurrentDungeonScript:dungeon_start()
    self:G_DungeonStart()

end

----������ʱ����
function CurrentDungeonScript:EndTime()
	if(Dungeon_Stare == 0)then
		----��ʧ�ܽ���
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
	end

end

function CurrentDungeonScript:Timer_Hint()

end


function CurrentDungeonScript:NpcKilled1()
	Dungeon_Stare = 1----����һ��
	if(Dungeon_Stare ~= 0)then
	   msg.targetlist[1].count = 1
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self:SpawnMonster2()
	self:Guide()
	self:CreatGuide(BossGuidePos.Pos,BossGuideOrg.Org,GuideID)	
	
	
	
	end
end


--[[function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid)----1���µڼ���  2��Сֵ 3���ֵ  4��������str
----pwdist.log("���¸�������")
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----����ʣ��ʱ��
	msg.timesec = SurTime
	msg.targetlist[Index].count = Ucount
	msg.targetlist[Index].maxcount = Umaxcount
	msg.targetlist[Index].strid = Ustrid
----pwdist.log("msg.targetlist[Index].count===="..Ucount)
----pwdist.log("msg.targetlist[Index].maxcount===="..Umaxcount)
----pwdist.log("msg.targetlist[Index].strid===="..Ustrid)

    self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end
--]]






function CurrentDungeonScript:NpcKilled2()
	Dungeon_Stare = 2----����һ��
	if(Dungeon_Stare ~= 0)then
	   msg.targetlist[2].count = 1
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self.SModCommon:SpawnMonsterAt(Boss3EnterPos, Boss3EnterOra, Boss3ID)
	end
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end



function CurrentDungeonScript:NpcKilled3()
	self:Guide()
	Dungeon_Stare = 3----ʤ��
	if(Dungeon_Stare ~= 0)then
		msg.targetlist[3].count = 1
		msg.timesec = 10
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self:G_DungeonEnd(DUNGEON_END_TIME)
	end
end


----����ָ��
function CurrentDungeonScript:CreatGuide(Pos,Org,ID)
	for k = 1,#Pos,1 do
		local GBOJ = self.Stage:CreateStaticObject(Pos[k],Org[k],ID,0,"")
		table.insert(GuideObj,GBOJ)
	end	
end


----ɾ��ָ��
function CurrentDungeonScript:Guide()
	for j= 1, table.getn(GuideObj) do
		local GuideStaticObj = GuideObj[j]:cast('StaticObject')
		if(GuideStaticObj ~= nil) then
			GuideStaticObj:LeaveWorld(0)----���پ���
		end
	end
	GuideObj = {}---��ʼ�����ﴢ�����
end

