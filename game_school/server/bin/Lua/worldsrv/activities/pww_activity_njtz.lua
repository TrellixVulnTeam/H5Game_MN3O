-----------------------------------------------------------------
-- �:����ս
-- �����������
-----------------------------------------------------------------

local NJTZ = {}

-----------------------------------------------------------------
SImplActivitiesClasses[2] = NJTZ
-----------------------------------------------------------------

NJTZ.TEAMPAIR_INDEX_RED = "r"
NJTZ.TEAMPAIR_INDEX_BLUE = "b"

NJTZ.FACTION_NEUTRAL = 7
NJTZ.FACTION_MONSTER = 2
NJTZ.FACTION_RED = 3
NJTZ.FACTION_BLUE = 4

NJTZ.CAMP_INDEX_RED = 1
NJTZ.CAMP_INDEX_BLUE = 2
NJTZ.CAMPS = { NJTZ.FACTION_RED, NJTZ.FACTION_BLUE }
NJTZ.AURA_CONFIG = {[NJTZ.FACTION_RED] = 60307,[NJTZ.FACTION_BLUE] = 60306}	--��ҽŵ׹⻷
NJTZ.RESSCORE = {1,2,3,4,5}
NJTZ.BigResScore = 1	--������÷�
NJTZ.MAXSCORE = 5000

NJTZ.RESOBJ = {
                ResId = {41102,41103,41103,41103,41103},
                ResDir = 
                {
                    {0,0,1},
                    {0,0,1},
                    {0,0,1},
                    {0,0,1},
                    {0,0,1},
                },
                ResPos = 
                {
                    {79.35,52.91,79.62},
                    {23.06,55.08,79.66},
                    {78.826,54.986,136.499},
                    {135.79,55.087,79.546},
                    {79.88,55.07,21.04},
                },
                ResRad = {10,5,5,5,5},
                ResBuf = {60810,60820,60820,60820,60820},
            }
            
NJTZ.TOWEROBJ = {
    TowerId = {41100,41100,41101,41101},
    TowerDir = {
        {0,0,1},
        {0,0,1},
        {0,0,1},
        {0,0,1},
        {0,0,1},
    },
    TowerPos = {
        {109.65,53.65,120.95},
        {120.44,53.65,111.11},
        {48.1,53.65,37.16},
        {38.26,53.65,48},
    },
    TowerFaction = {
        NJTZ.FACTION_RED,
        NJTZ.FACTION_RED,
        NJTZ.FACTION_BLUE,
        NJTZ.FACTION_BLUE,
    },
}

NJTZ.BUFFOBJ = {
                BuffId = {41104,41104,41104,41104},
                BuffDir = 
                {
                    {0,0,1},
                    {0,0,1},
                    {0,0,1},
                    {0,0,1},			   
                },
                BuffPos= 
                {
					{102.43,53.53,57.96},
					{100.3,53.53,101.9},
					{57.89,53.53,100.9},
					{57.9,53.53,57.3},
                },
            }
            
NJTZ.BUFF = {
	BUFF_ATTACK = 60201,
	BUFF_DEF = 60202,
	BUFF_SPEED = 60203,
	BUFF_INVINCIBLE = 60800,
	-- BUFF_HP = 60200,
	-- BUFF_EXP = 60204,
	-- BUFF_EXP1 = 60207,
	-- BUFF_EXP2 = 60208,
	-- BUFF_EXP3 = 60209
}

NJTZ.SERVER_STR = {
    ENEMY_OCCUPY_RES = 51358,   -- �з�ռ����Դ
    OUR_OCCUPY_RES = 51359,     -- �ҷ�ռ����Դ
    ENEMY_LOSE_RES = 51360,     -- �з���ʧ��Դ
    OUR_LOSE_RES = 51361,       -- �ҷ���ʧ��Դ
    
    BATTER_5 = 51362,          -- 5��ɱ
    BATTER_6 = 51363,          -- 6��ɱ
    BATTER_7 = 51364,          -- 7��ɱ
    BATTER_8 = 51365,          -- 8��ɱ
	BATTER_9 = 51366,          -- 9��ɱ
	BATTER_10 = 51367,			--10��ɱ
    
    BATTER_END = 51369,     -- >=5��ɱ���ս���
    
    ENEMY_SCORE_1000 = 51370,   -- �з��Ѿ�������4000������
    ENEMY_SCORE_1800 = 51371,   -- �з��Ѿ�������4800�����ˣ��ӽ�ʤ����
    OUR_SCORE_1000 = 51372,     -- �ҷ��Ѿ�������4000������
    OUR_SCORE_1800 = 51373,     -- �ҷ��Ѿ�������4800�����ˣ����Ͻӽ�ʤ����
}

-- NJTZ.CAMPPOS = { {381.1992,112.6813,131.8138}, {542.3467,112.6813,287.4841} }
NJTZ.CAMPPOS = { {126.071,54.599,125.28}, {31.83,54.653,32.22} }
NJTZ.ResurrectPos = { {{126.071,54.599,125.28},
					   {126.071,54.599,125.28},
						},
					{ {31.83,54.653,32.22},
					  {31.83,54.653,32.22},				
					} }




NJTZ.DRAGON_GLORY_BUFF = 3 -- ������BUFF

NJTZ.BROADCAST_BEFOR = {51354,51355,51356,51357}	--��ǰ�㲥��ʾ
NJTZ.BROADCAST_BEFOREND = 51374 -- ��ս2���Ӻ��������ʱ��Դ���һ����ʤ
NJTZ.BROADCAST_TYPE = 2

NJTZ.Timer_njtzstart = 120 --����120���ʼս��
NJTZ.Timer_Correct = 2		--��ʱ��ʱ�������

NJTZ.RESSCORE_ADDBASE = 0 -- ��Դ��ÿ�����ӻ���ֵ��ʵ������ֵΪ������+0����߲��ܳ���10
NJTZ.RESSCORE_ADDMAX = 10 -- ��Դ��ÿ���������ֵ
NJTZ.RESSCOREMAX = 100 -- ��Դ�ִﵽ-100�֣���Դ���췽��ռ����Դ�ִﵽ100�֣���Դ��������ռ

NJTZ.RANKADD_KILL = 5    -- ɱ�˵�10���� --ɱ�˻��ֵ���Ϊ5
NJTZ.RANKADD_OCCUPY = 10 -- ��ռ��Դ��10����

--NJTZ.RANKADD_WIN = 50    -- ��ʤ��50����
NJTZ.RANKADD_WIN = 0    -- ��ʤ�����ٵö������,@fangping
NJTZ.Game_start_clock = 0	--ս����ʼʱ��


local NjtzHumanlist = {}
-----------------------------------------------------------------

function NJTZ:GetCampIndex(guildid)
    if self.TeamPairTable[self.TEAMPAIR_INDEX_RED].id == guildid then
        return self.CAMP_INDEX_RED
    end
    return self.CAMP_INDEX_BLUE
end

function NJTZ:GetCampIndexByCamp(camp)
    if camp == self.CAMPS[self.CAMP_INDEX_RED] then
        return self.CAMP_INDEX_RED
    end
    return self.CAMP_INDEX_BLUE
end

function NJTZ:GetResScoreAddValue(diffnum)
    if diffnum == 0 then
        return 0
    end
    
    local addval = math.abs(diffnum) + self.RESSCORE_ADDBASE
    addval = math.min(addval,self.RESSCORE_ADDMAX)
    
    if diffnum > 0 then
        return addval
    else
        return 0 - addval
    end
end

function NJTZ:AddPersonScoreWhenOccupy(humanTab,camp)
    for _,human in ipairs(humanTab) do
        if human:GetFaction() == camp and (not human:IsDead()) then
            local strid = tostring(human:GetID())
            local humantable = self.Humans[camp][strid]
            if humantable ~= nil then
                humantable.Rank = humantable.Rank + self.RANKADD_OCCUPY
                humantable.OccupationNum = humantable.OccupationNum + 1
            else
                pwdist.log('OnHumanKilled humantable==nil',camp,strid)
            end
        end
    end
end

function NJTZ.MembersComparer(m1,m2)
    if m1.Rank ~= m2.Rank then
        return m1.Rank > m2.Rank
    else
        return m1.CombatPoint > m2.CombatPoint
    end
end

function NJTZ:GetRanklist()
    local members = {}
    for _,v in pairs(self.Humans[self.FACTION_RED]) do
        table.insert(members, v)
    end

    for _,v in pairs(self.Humans[self.FACTION_BLUE]) do
        table.insert(members, v)
    end

    table.sort(members, self.MembersComparer)
    return members
end

function NJTZ:GetFirstMemberIfCampWin(winnerCamp)
    local members = {}
    for _,v in pairs(self.Humans[self.FACTION_RED]) do
        local member = {}
        member.ID = v.ID
        member.Rank = v.Rank
        member.CombatPoint = v.CombatPoint

        if winnerCamp == FACTION_RED then
            member.Rank = member.Rank + self.RANKADD_WIN
        end

        table.insert(members,member)
    end

    for _,v in pairs(self.Humans[self.FACTION_BLUE]) do
        local member = {}
        member.ID = v.ID
        member.Rank = v.Rank
        member.CombatPoint = v.CombatPoint

        if winnerCamp == FACTION_BLUE then
            member.Rank = member.Rank + self.RANKADD_WIN
        end

        table.insert(members,member)
    end

    table.sort(members, self.MembersComparer)

    if members[1] then
        return members[1].ID
    else
        return 0
    end    
end

function NJTZ:GetMembers(camp)
    local memberids = {}
    for _,v in pairs(self.Humans[camp]) do
        table.insert(memberids, v.ID)
    end
    
    return memberids
end

function NJTZ:BroadcastBlockEffectsStatus()
    for k,v in pairs(self.BlockEffects) do
        self.Stage:GetModDetour():EnableBlockEffects(k,v)
    end
end

function NJTZ:DisableAllBlockEffects()
    for k,v in pairs(self.BlockEffects) do
        self.Stage:GetModDetour():EnableBlockEffects(k,false)
    end
    
    self.BlockEffects = {}
end

-----------------------------------------------------------------

function NJTZ:New(conf)
	local r = conf or {}
    setmetatable(r,self)
    self.__index = self
    return r
end

-----------------------------------------------------------------

function NJTZ:Start(stage,ref,id)
    self.ScriptRef = ref
    self.Stage = stage
    self.ConfId = id
	self.SModCommon = self.Stage:GetModCommon()
    self.SModAOI = self.Stage:GetModAOI()
    self.SModObjs = self.Stage:GetModObjs()
    
    self.Humans = {}
    self.Humans[self.FACTION_RED] = {}
    self.Humans[self.FACTION_BLUE] = {}

    self.CampResources = {}
    self.CampResources[self.CAMP_INDEX_RED] = 0
    self.CampResources[self.CAMP_INDEX_BLUE] = 0
    self.CampResources.Resources = {}
	
	self.CampResourcesBig = {}
	self.CampResourcesBig[self.CAMP_INDEX_RED] = 0
	self.CampResourcesBig[self.CAMP_INDEX_BLUE] = 0
    
    self.CampScores = {}
    self.CampScores[self.CAMP_INDEX_RED] = 0
    self.CampScores[self.CAMP_INDEX_BLUE] = 0
    
    self.BlockEffects = {}
    self.BlockEffects[121] = true
    self.BlockEffects[120] = true
    
    self.TencentUserInfos = {}
    self.Finished = false
end
-----------------------------------------------------------------
function NJTZ:Clean()
    pwdist.log('NJTZ:Clean')
end
-----------------------------------------------------------------
function NJTZ:_rpc_Initial(teamPairIndex,teamPairTable,round)
    pwdist.log('_rpc_Initial')

    SetEventHandler_for_ActivityPlay(StageEvents.HumanKilled, "OnHumanKilled")
    SetEventHandler_for_ActivityPlay(StageEvents.HumanResurrect, "OnHumanResurrect")
    -- ����Ҫ,��ض������������¼�
    -- SetEventHandler_for_ActivityPlay(StageEvents.OnHumanEnter, "OnHumanEnter")
    -- SetEventHandler_for_ActivityPlay(StageEvents.HumanLeave, "OnHumanLeave")
   
    self.TeamPairIndex = teamPairIndex
    self.TeamPairTable = teamPairTable
    self.Round = round
    self.DragonGloryAura = self.DRAGON_GLORY_BUFF
    
	self.Stage:GetModDetour():EnableMotionBlock(0, false)
	self.Stage:GetModDetour():EnableMotionBlock(1, false)
	self.Stage:GetModDetour():EnableMotionBlock(2, false)
	self.Stage:GetModDetour():EnableMotionBlock(3, false)


    -- ˢ����һ�ε�������Դ
    for k,v in ipairs(self.RESOBJ.ResId) do
        local res = self.SModCommon:SpawnMonsterAt(self.RESOBJ.ResPos[k],self.RESOBJ.ResDir[k],v)
        res:ChangeFaction(self.FACTION_NEUTRAL)
        
        local staticObject = res:cast("StaticObject")
        staticObject:Enable(false)

        local resTab = {
            ResObj = res,   -- ��Դ����
            Score = 0,      -- ��Դ��ǰ����
            Radius = self.RESOBJ.ResRad[k], -- ��Դ����뾶
            ResNo = k,      -- ��Դ���
            RedNum = 0,     -- ռ���������췽
            BlueNum = 0,    -- ռ������������
        }
        table.insert(self.CampResources.Resources,resTab)
    end
    
    -- ˢ��������
    for k,v in ipairs(self.TOWEROBJ.TowerId) do
        local tow = self.SModCommon:SpawnMonsterAt(self.TOWEROBJ.TowerPos[k],self.TOWEROBJ.TowerDir[k],v)
        tow:ChangeFaction(self.TOWEROBJ.TowerFaction[k])
        tow:SetBit(UnitBits.IMMUNIZING,true)
        
        pwdist.log('_rpc_Initial tower:',tostring(v))
    end



	--ÿ10���������̱߳�������
	self.SModCommon:CreatePeriodTimer(10,10,0,"_OnTimeUpdateHumanCount")
end

function NJTZ:_OnTimeUpdateHumanCount()
	--ÿ10���������̱߳�������
	self.Stage:ReportHumanCountToActivityManager(2)
end

function NJTZ:OnHumanKilled(human,killer)
    pwdist.log('NJTZ:OnHumanKilled')
    if self.Finished then
        return
    end
    
    if not killer:IsKindOf(CLSID.Human) then
        return
    end
    
    local killercamp = killer:GetFaction()
    local killercampindex = self:GetCampIndexByCamp(killercamp)
    local killerstrid = tostring(killer:GetID())    
   
    local killerhuman = killer:cast('Human')
    if killerhuman ~= nil then
        local humantable = self.Humans[killercamp][killerstrid]
        if humantable ~= nil then
            humantable.Rank = humantable.Rank + self.RANKADD_KILL
            humantable.KillCount = humantable.KillCount + 1
            humantable.BatterCount = humantable.BatterCount + 1
			if humantable.BatterCount > humantable.MaxBatterCount then
				humantable.MaxBatterCount = humantable.BatterCount
			end
            self:OnNotifyKiller(human,killerhuman,humantable.BatterCount)
        else
            pwdist.log('OnHumanKilled killertable==nil',killercamp,killerstrid)
        end
    end

    local killedcamp = human:GetFaction()
    local killedcampindex = self:GetCampIndexByCamp(killedcamp)
    local killedstrid = tostring(human:GetID())
    if human ~= nil then
        local humantable = self.Humans[killedcamp][killedstrid]
        if humantable ~= nil then
            self:OnNotifyKilled(killerhuman,human,humantable.BatterCount)
            humantable.BatterCount = 0
        else
            pwdist.log('OnHumanKilled killedtable==nil',killedcamp,killedstrid)
        end
    end
end

function NJTZ:OnNotifyKiller(killed,killer,killerbattercount)
    local msg = {
        mode = self.BROADCAST_TYPE,
        text_id = self.SERVER_STR.BATTER_5,
        text_args = {killer:GetName(),tostring(killer:GetID()),tostring(killer:GetSex())},
        text_type = ChannelType.Announcement,
        is_href = false,
    }   
    if killerbattercount == 5 then
        msg.text_id = self.SERVER_STR.BATTER_5
    elseif killerbattercount == 6 then
        msg.text_id = self.SERVER_STR.BATTER_6
    elseif killerbattercount == 7 then
        msg.text_id = self.SERVER_STR.BATTER_7
    elseif killerbattercount == 8 then
        msg.text_id = self.SERVER_STR.BATTER_8
	elseif killerbattercount == 9 then
        msg.text_id = self.SERVER_STR.BATTER_9
	elseif killerbattercount == 10 then
        msg.text_id = self.SERVER_STR.BATTER_10
    else
        return
    end

    self.SModObjs:Broadcast(msgids.SCNotify,msg)
end

function NJTZ:OnNotifyKilled(killer,killed,killedbattercount)
    local msg = {
        mode = self.BROADCAST_TYPE,
        text_id = self.SERVER_STR.BATTER_END,
        text_args = {killer:GetName(),tostring(killer:GetID()),tostring(killer:GetSex()),killed:GetName(),tostring(killed:GetID()),tostring(killed:GetSex())},
        text_type = ChannelType.Announcement,
        is_href = false,
    }
    if killedbattercount >= 5 then
        msg.text_id = self.SERVER_STR.BATTER_END
	else
		return
    end

    self.SModObjs:Broadcast(msgids.SCNotify,msg)
end

function NJTZ:OnHumanResurrect(human)
	pwdist.log('NJTZ:OnHumanResurrect',tostring(human:GetID()))
    
    local camp = human:GetFaction()
    local campindex = self:GetCampIndexByCamp(camp)
	math.randomseed(os.time())
	math.random(1, 2)
	local rand = math.random(1, 2)
    human:GetModMotionMaster():ChangePosition(self.ResurrectPos[campindex][rand])
    
    -- ��������5��
    human:GetModAura():Create(self.BUFF.BUFF_INVINCIBLE)
end

function NJTZ:OnHumanLeave(unit)
    local human = unit:cast('Human')
    if human ~= nil then
        local msg = { activityid = self.ConfId }
        human:SendMsg(msgids.SCLeaveActivity,msg) 

        if not self.Finished then
            local guildid = human:GetGuildId()
            local campindex = self:GetCampIndex(guildid)
            local camp = self.CAMPS[campindex]
            local strid = tostring(human:GetID())
            local humantable = self.Humans[camp][strid]
            if humantable then
                humantable.Dismissed = true
            end
        end
    end
end

function NJTZ:OnHumanEnter(unit)
    pwdist.log('NJTZ:OnHumanEnter',tostring(unit:GetID()))
    
    self:BroadcastBlockEffectsStatus()
    
    local human = unit:cast('Human')
	
	if nil == human then
		pwdist.log('nil == human')
		return 
	end
    
    if self.startTimer ~= nil then
        if self.Game_start_clock - os.time() > 0 then
		    self.SModCommon:ClientOperation(human,UI_TIMER,tostring(self.Game_start_clock - os.time()),"")
        end
    end
	
	-- ��������ʱ
	if self.Game_start_clock ~= 0 then
		if os.time() - self.Game_start_clock > 0 then
			local leaft_time = self.total_time - self.Timer_njtzstart - (os.time() - self.Game_start_clock) - self.Timer_Correct
			if leaft_time > 0 then
				local msg = { targetlist = {} }
				msg.timesec = leaft_time
				human:SendMsg(msgids.SCDungeonTargetList,msg)
				
				pwdist.log('leaft_time:'..tostring(leaft_time))
			end
		end
	end
    
    local guildid = human:GetGuildId()
    local campindex = self:GetCampIndex(guildid)
    local camp = self.CAMPS[campindex]
	
	pwdist.log('campindex:', tostring(campindex))
    
    local strid = tostring(human:GetID())
	if(NjtzHumanlist[strid] == nil or NjtzHumanlist[strid] ~= 1)then
		NjtzHumanlist[strid] = 0
	end
-- pwdist.log("�������ID==="..strid)
    if not self.Finished and self.Humans[camp][strid] == nil then
        self.Humans[camp][strid] = {}
        local humantable = self.Humans[camp][strid]
        humantable.Name = human:GetName()
        humantable.ID = human:GetID()
		humantable.GuildId = guildid
        humantable.Camp = camp
        humantable.CampIndex = campindex        
        humantable.Rank = 0
        humantable.Dismissed = false
        humantable.KillCount = 0
        humantable.OccupationNum = 0
        humantable.BatterCount = 0 -- ��ɱ������������
		humantable.MaxBatterCount = 0 -- �����ɱ
        humantable.CombatPoint = human:GetModCombatPoint():GetCombatPoint()
    end
	if self.Humans[camp][strid] then
		self.Humans[camp][strid].Dismissed = false
	end	
    human:GetModMotionMaster():ChangePosition(self.CAMPPOS[campindex])
    human:ChangeFaction(self.CAMPS[campindex])
    human:GetModAura():Create(self.AURA_CONFIG[self.CAMPS[campindex]]) --�ӹ⻷
	------ս��ϵͳ���ӵĻ�����ֵ
	local HumID = tostring(human:GetID())
	if(NjtzHumanlist[strid] == 0) then
		human:AddMilitaryScore(5,BattleGod.BBZ[1])
		NjtzHumanlist[strid] = 1
	end
    -- ���ӻ�Ծ��
		--human:GetModDailyBonus():InjectActivityComplete(19,1)
end

function NJTZ:UpdatePer1Sec()
    if self.Finished then
        return
    end
    
    self.CampResources[self.CAMP_INDEX_RED] = 0
    self.CampResources[self.CAMP_INDEX_BLUE] = 0
	self.CampResourcesBig[self.CAMP_INDEX_RED] = 0
	self.CampResourcesBig[self.CAMP_INDEX_BLUE] = 0
	
    for resIdx,resTab in ipairs(self.CampResources.Resources) do
        resTab.RedNum = 0
        resTab.BlueNum = 0
        local resObj = resTab.ResObj
        local humanTab = self.SModAOI:CollectHumanInAround(resObj:GetPosition(),resTab.Radius)
        for _,human in ipairs(humanTab) do
            if not human:IsDead() then
                if human:GetFaction() == self.FACTION_RED then
                    resTab.RedNum = resTab.RedNum + 1
                else
                    resTab.BlueNum = resTab.BlueNum + 1
                end
            end
        end
        
        -- ������Դ����
        local oldScore = resTab.Score
        resTab.Score = resTab.Score + self:GetResScoreAddValue(resTab.RedNum - resTab.BlueNum)
        resTab.Score = math.max(math.min(resTab.Score, self.RESSCOREMAX), -self.RESSCOREMAX)
        local newScore = resTab.Score
        
        -- �·���Դ��Ϣ���ͻ���
        local resObjId = resObj:GetID()
        for _,human in ipairs(humanTab) do
            local msg = 
            {
                resid = resObjId,
                score = newScore,
                resno = resIdx,
            }
            if human:GetFaction() == self.FACTION_BLUE then
                msg.score = 0 - msg.score
            end
            human:SendMsg(msgids.SCJTZNUpdateResource,msg)
            
            -- pwdist.log('NJTZ:UpdatePer1Sec,Res id:' .. tostring(resObjId) .. ',Res score:' .. tostring(newScore))
        end

        -- ռ��󣬸��ѷ���Ѫbuff
        local resBuf = self.RESOBJ.ResBuf[resIdx]
        
        local oldResCamp = resObj:GetFaction()
        -- ���������Դ
        if (oldScore > 0 and newScore <= 0) or (oldScore < 0 and newScore >= 0) then
            if oldResCamp ~= self.FACTION_NEUTRAL then
                resObj:ChangeFaction(self.FACTION_NEUTRAL)
                self:OnNotifyResCampChanged(oldResCamp,self.FACTION_NEUTRAL)

                resObj:GetModAura():Create(resBuf)
            end
        end
        
        -- ���������Դ
        if oldScore > -self.RESSCOREMAX and newScore <= -self.RESSCOREMAX then
            if oldResCamp ~= self.FACTION_BLUE then
                resObj:ChangeFaction(self.FACTION_BLUE)
                self:AddPersonScoreWhenOccupy(humanTab,self.FACTION_BLUE)
                self:OnNotifyResCampChanged(oldResCamp,self.FACTION_BLUE)

                resObj:GetModAura():Delete(resBuf)
                resObj:GetModAura():Create(resBuf)
            end
        end
        
        -- ��ɺ췽��Դ
        if oldScore < self.RESSCOREMAX and newScore >= self.RESSCOREMAX then
            if oldResCamp ~= self.FACTION_RED then
                resObj:ChangeFaction(self.FACTION_RED)
                self:AddPersonScoreWhenOccupy(humanTab,self.FACTION_RED)
                self:OnNotifyResCampChanged(oldResCamp,self.FACTION_RED)

                resObj:GetModAura():Delete(resBuf)
                resObj:GetModAura():Create(resBuf)
            end
        end
        
        -- ͳ��������Դ��
        local resCamp = resObj:GetFaction()
        if resCamp ~= self.FACTION_NEUTRAL then
            local campindex = self:GetCampIndexByCamp(resCamp)
			self.CampResources[campindex] = self.CampResources[campindex] + 1
			
			if 1 == resIdx then
				self.CampResourcesBig[campindex] = 1;
			end
        end
    end

    self:BroadcastResStatus()
end

function NJTZ:BroadcastResStatus()
    local rmsg = {resources = {}}
    for resIdx,resTab in ipairs(self.CampResources.Resources) do
        local resMsg = {}
        resMsg.resid = resTab.ResObj:GetID()
        resMsg.faction = resTab.ResObj:GetFaction()
        resMsg.friend_num = resTab.RedNum
        resMsg.enemy_num = resTab.BlueNum
        resMsg.resno = resIdx
        table.insert(rmsg.resources,resMsg)
    end

    self.SModObjs:BroadcastWithFaction(msgids.SCJTZNUpdateResourceStatus,rmsg,self.FACTION_RED)

    local bmsg = {resources = {}}
    for resIdx,resTab in ipairs(self.CampResources.Resources) do
        local resMsg = {}
        resMsg.resid = resTab.ResObj:GetID()
        resMsg.faction = resTab.ResObj:GetFaction()
        resMsg.friend_num = resTab.BlueNum
        resMsg.enemy_num = resTab.RedNum
        resMsg.resno = resIdx
        table.insert(bmsg.resources,resMsg)
    end

    self.SModObjs:BroadcastWithFaction(msgids.SCJTZNUpdateResourceStatus,bmsg,self.FACTION_BLUE)
end

function NJTZ:OnNotifyResCampChanged(oldCamp,newCamp)
    -- �췽��Դ����
    if oldCamp == self.FACTION_RED then
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.OUR_LOSE_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.ENEMY_LOSE_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
    end

    -- ������Դ����
    if oldCamp == self.FACTION_BLUE then
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.OUR_LOSE_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.ENEMY_LOSE_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
    end

    -- �췽ռ������Դ
    if newCamp == self.FACTION_RED then
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.OUR_OCCUPY_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.ENEMY_OCCUPY_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
    end

    -- ����ռ������Դ
    if newCamp == self.FACTION_BLUE then
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.OUR_OCCUPY_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.ENEMY_OCCUPY_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
    end
end

function NJTZ:UpdatePer5Sec()
    if self.Finished then
        return
    end
    
    local rnum = self.CampResources[self.CAMP_INDEX_RED]
    local bnum = self.CampResources[self.CAMP_INDEX_BLUE]
	local rbignum = self.CampResourcesBig[self.CAMP_INDEX_RED]
	local bbignum = self.CampResourcesBig[self.CAMP_INDEX_BLUE]

    local rOldScore = self.CampScores[self.CAMP_INDEX_RED]
    local bOldScore = self.CampScores[self.CAMP_INDEX_BLUE]

	if rnum > 0 then
		for i,v in pairs(self.Humans[self.FACTION_RED]) do
			if v.Dismissed == false then
				v.Rank = v.Rank + self.RESSCORE[rnum]
				if rbignum > 0 then
					v.Rank = v.Rank + self.BigResScore
				end
			end
		end
	end
	
	if bnum > 0 then
		for i,v in pairs(self.Humans[self.FACTION_BLUE]) do
			if v.Dismissed == false then
				v.Rank = v.Rank + self.RESSCORE[bnum]
				if bbignum > 0 then
					v.Rank = v.Rank + self.BigResScore
				end
			end
		end
	end
	
	local rNewScore = 0
	local bNewScore = 0
	
	for i,v in pairs(self.Humans[self.FACTION_RED]) do
		rNewScore = rNewScore + v.Rank
	end
	
	for i,v in pairs(self.Humans[self.FACTION_BLUE]) do
		bNewScore = bNewScore + v.Rank
	end
	
	self.CampScores[self.CAMP_INDEX_RED] = rNewScore
	self.CampScores[self.CAMP_INDEX_BLUE] = bNewScore
	
	self.CampScores[self.CAMP_INDEX_RED] = math.min(self.CampScores[self.CAMP_INDEX_RED],self.MAXSCORE)
	self.CampScores[self.CAMP_INDEX_BLUE] = math.min(self.CampScores[self.CAMP_INDEX_BLUE],self.MAXSCORE)

    self:OnNotifyScoreChanged(self.FACTION_RED,rOldScore,rNewScore)
    self:OnNotifyScoreChanged(self.FACTION_BLUE,bOldScore,bNewScore)
    
    -- �㲥����
    self:OnResourceChanged()
	
	-- self:BroadcastRanksEx(nil, nil, nil)
    
    if (self.CampScores[self.CAMP_INDEX_RED] >= self.MAXSCORE or self.CampScores[self.CAMP_INDEX_BLUE] >= self.MAXSCORE) then
        self:Settlement()
    end
    
end

function NJTZ:OnNotifyScoreChanged(camp,oldScore,newScore)
    if camp == self.FACTION_RED then
        if oldScore < 4000 and newScore >= 4000 then
            self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.OUR_SCORE_1000,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
            self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.ENEMY_SCORE_1000,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
        elseif oldScore < 4800 and newScore >= 4800 then
            self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.OUR_SCORE_1800,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
            self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.ENEMY_SCORE_1800,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
        end
    elseif camp == self.FACTION_BLUE then
        if oldScore < 4000 and newScore >= 4000 then
            self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.OUR_SCORE_1000,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
            self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.ENEMY_SCORE_1000,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
        elseif oldScore < 4800 and newScore >= 4800 then
            self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.OUR_SCORE_1800,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
            self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.ENEMY_SCORE_1800,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
        end
    end
end

function NJTZ:BroadcastRanks(timer,_finished,_winnerid)
    -- ������˻���
    local msg = { ranks = {} }
    
    msg.finished = _finished or false
    if msg.finished then
        msg.winnerid = _winnerid
    end

    local ranklist = self:GetRanklist()

    for i,v in ipairs(ranklist) do
        local tuserinfo = self.TencentUserInfos[tostring(v.ID)]

        msg.ranks[i] = 
        {
            id = v.ID,
            name = v.Name,
            rank = v.Rank,
            kill_count = v.KillCount,
            occupation_num = v.OccupationNum,
        }

        if tuserinfo ~= nil then
            msg.ranks[i].tencent_user_info = tuserinfo
        end
    end
    
    self.SModObjs:Broadcast(msgids.SCJTZNRoundResult,msg) 
    
    return ranklist
end

function NJTZ:BroadcastRanksEx(timer,_finished,_winnerid)
    -- ������˻���
    local msg = { info = {} }
    
    local ranklist = self:GetRanklist()

    for i,v in ipairs(ranklist) do
        local tuserinfo = self.TencentUserInfos[tostring(v.ID)]

        msg.info[i] = 
        {
            id = v.ID,
            name = v.Name,
            score = v.Rank,
            killnum = v.KillCount,
            killednum = 1,
			itemcount = 1,
			seconds = 1,
			maxbattercount = v.MaxBatterCount,
			guildid = v.GuildId,
        }

        if tuserinfo ~= nil then
            msg.info[i].tencent_user_info = tuserinfo
        end
    end
    
    self.SModObjs:Broadcast(msgids.SCDTSRankUpdate,msg) 
    
    return ranklist
end

function NJTZ:Settlement()
    pwdist.log('NJTZ:Settlement')
    self.Finished = true
	
	-- ͬ�����˷���
	self:BroadcastRanksEx(nil, nil, nil)
	
	-- ͬ���Ŷӷ���
	self:OnResourceChanged()
    
    if self.updateScoreTimer then
        self.SModCommon:CancelTimer(self.updateScoreTimer)
        self.updateScoreTimer = nil
    end
    
    if self.updateResTimer then
        self.SModCommon:CancelTimer(self.updateResTimer)
        self.updateResTimer = nil
    end
    
    if self.broadcastTimer then
        self.SModCommon:CancelTimer(self.broadcastTimer)
        self.broadcastTimer = nil
    end

    if self.beforeEndTimer then
        self.SModCommon:CancelTimer(self.beforeEndTimer)
        self.beforeEndTimer = nil
    end

    local firstIfRedWin = self:GetFirstMemberIfCampWin(self.FACTION_RED)
    local firstIfBlueWin = self:GetFirstMemberIfCampWin(self.FACTION_BLUE)
    
    -- ����ʤ��
    local rteaminfo = { self.Round, self.CampScores[self.CAMP_INDEX_RED], self.CampResources[self.CAMP_INDEX_RED], firstIfRedWin }
    local bteaminfo = { self.Round, self.CampScores[self.CAMP_INDEX_BLUE], self.CampResources[self.CAMP_INDEX_BLUE], firstIfBlueWin }
    self:Call('_rpc_SettlementResult',self.TeamPairIndex,rteaminfo,bteaminfo)
	NjtzHumanlist = {}
-- pwdist.log('NjtzHumanlist=========='..table.getn(NjtzHumanlist))
end

function NJTZ:Timer_start()
    pwdist.log('NJTZ:OnStarted')

    self.startTimer = nil
    
	-- ��������ʱ
	local msg = { targetlist = {} }
	msg.timesec = self.total_time - self.Timer_njtzstart - self.Timer_Correct - 20 --20������ʱ�� ���ʵ�Ŀ���ʱ��ȹ㲥������ʱ����20��
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList,msg)
	
   	self.Stage:GetModDetour():EnableMotionBlock(0, true)
	self.Stage:GetModDetour():EnableMotionBlock(1, true)
    self.Stage:GetModDetour():EnableMotionBlock(2, true)
	self.Stage:GetModDetour():EnableMotionBlock(3, true)   
    self:DisableAllBlockEffects()

	
    self.SModCommon:LaunchPolt(DUNGEON_START,0,"")
    
    -- 5�����һ�����˵÷�
    self.updateScoreTimer = self.SModCommon:CreatePeriodTimer(10, 10, -1,"UpdatePer5Sec")
    
    -- 1�����һ�γ����е���Դ����
    self.updateResTimer = self.SModCommon:CreatePeriodTimer(1, 1, -1,"UpdatePer1Sec")
    
    -- 1��㲥һ�θ��˵÷�����
    self.broadcastTimer = self.SModCommon:CreatePeriodTimer(1, 1, -1,"BroadcastRanksEx")
    
    --����5���ѭ�����Ź㲥
    self.broadcastBeforeIndex = 1
	self.SModCommon:CreatePeriodTimer(5, 10, #self.BROADCAST_BEFOR,"BroadCast_beforstart")
    
    -- ��ʼһ��ʱ���ˢ��Buff��
    math.randomseed(os.time())
	math.random(30, 60)
	local rand = math.random(30, 60)
	self.SModCommon:CreateTimer(rand, "_OnTimeAddBufObj")
end

function NJTZ:_OnTimeAddBufObj()
	pwdist.log('NJTZ:_OnTimeAddBufObj')
	
	for k,v in ipairs(self.BUFFOBJ.BuffId) do
		self.Stage:CreateStaticObject(self.BUFFOBJ.BuffPos[k], self.BUFFOBJ.BuffDir[k], v, 3,"_OnAddBuff")	
	end
end

function NJTZ:_OnAddBuff(obj, human)
	pwdist.log('NJTZ:_OnAddBuff')
	
	obj:LeaveWorld(0)
	
	math.randomseed(os.time())
	math.random(1, 3)
	local rand = math.random(1, 3)
	
	if rand == 1 then
		human:GetModAura():Create(self.BUFF.BUFF_ATTACK)
	elseif rand == 2 then
		human:GetModAura():Create(self.BUFF.BUFF_DEF)
	elseif rand == 3 then
		human:GetModAura():Create(self.BUFF.BUFF_SPEED)
	end
end

function NJTZ:OnResourceChanged()
    local rteaminfo = 
    { 
        teamid = self.TeamPairTable[self.TEAMPAIR_INDEX_RED].id, 
        resources = self.CampResources[self.CAMP_INDEX_RED] ,
        score = self.CampScores[self.CAMP_INDEX_RED]
    }
     local bteaminfo = 
    { 
        teamid = self.TeamPairTable[self.TEAMPAIR_INDEX_BLUE].id, 
        resources = self.CampResources[self.CAMP_INDEX_BLUE] ,
        score = self.CampScores[self.CAMP_INDEX_BLUE]
    }
    local msg = 
    {
        red = rteaminfo,
        blue = bteaminfo,
    }
	
    self.SModObjs:Broadcast(msgids.SCJTZNUpdate,msg)
end

function NJTZ:_rpc_MemberLeaved(guild,memberId)
    pwdist.log('NJTZ:_rpc_MemberLeaved',tostring(guild),tostring(memberId))
    
    local human = self.SModObjs:GetHuman(memberId)
    if human == nil then
        return
    end
    
    -- local strid = tostring(human:GetID())
    -- local guildid = human:GetGuildId()
    -- local campindex = self:GetCampIndex(guildid)
    -- local camp = self.CAMPS[campindex]
    
    -- self.Humans[camp][strid].Dismissed = true

    -- �뿪����ʱ���������ǿ�ƴ�������
    human:LeaveDungeon()
end

function NJTZ:_rpc_call_SetTencentUserInfo(longid,userinfo)
    local strid = tostring(longid)

    if userinfo ~= nil then
        self.TencentUserInfos[strid] = userinfo
    end
end

-- ����
function NJTZ:_rpc_Settlement()
    self:Settlement()
end


function NJTZ:_rpc_Start(total_time)
    pwdist.log('NJTZ:_rpc_Start'..total_time)
	
	self.total_time = total_time;
    
    self.startTimer = self.SModCommon:CreateTimer(self.Timer_njtzstart,"Timer_start")
	self.Game_start_clock = os.time() + self.Timer_njtzstart
    
    self.SModCommon:BroadcastClientOperation(UI_TIMER,tostring(self.Timer_njtzstart))

    -- ��ս�����������ʾ����ս��������
    self.beforeEndTimer = self.SModCommon:CreateTimer(20 * 60,"BroadCast_beforend")
end

function NJTZ:BroadCast_beforend()
    pwdist.log('NJTZ:BroadCast_beforend')

    self.beforeEndTimer = nil
    self.SModObjs:BroadcastNotifyWithFaction(self.BROADCAST_BEFOREND,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
    self.SModObjs:BroadcastNotifyWithFaction(self.BROADCAST_BEFOREND,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
end

function NJTZ:_rpc_Clean(bRedWin)
    if bRedWin then
        pwdist.log('NJTZ:_rpc_Clean red win')
    else
        pwdist.log('NJTZ:_rpc_Clean blue win')
    end

    local rteam = self.TeamPairTable[self.TEAMPAIR_INDEX_RED]
    local bteam = self.TeamPairTable[self.TEAMPAIR_INDEX_BLUE]

    local winnerCamp = self.FACTION_RED
    local winnerId = rteam.id
    if not bRedWin then
        winnerCamp = self.FACTION_BLUE
        winnerId = bteam.id
    end

    -- ��ʤ��ÿ�˶����50����
    for _,v in pairs(self.Humans[winnerCamp]) do
        v.Rank = v.Rank + self.RANKADD_WIN
    end
	
	local msg = {};
	msg.match_info = 
	{
		red_guild_id = rteam.id, 
		blue_guild_id = bteam.id, 
		win_guild_id = winnerId,
	}
	self.SModObjs:Broadcast(msgids.SCGBFinish,msg)
	
    pwdist.log('NJTZ:Settlement BroadcastMessage OK')
	
    -- local ranklist = self:BroadcastRanks(nil,true,winnerId)
	local ranklist = self:GetRanklist()

    local topFiveIds = {}
    local joinIds = {}  -- ���ֲ�Ϊ0�����
    for i,v in ipairs(ranklist) do
        if i <= 3 then
            table.insert(topFiveIds, v.ID)
        end
        if v.Rank > 0 then
            table.insert(joinIds, v.ID)
        end
    end
    
    local rmembers = self:GetMembers(self.FACTION_RED)
    local bmembers = self:GetMembers(self.FACTION_BLUE)
    self.Stage:GetModActivityPlay():NJTZ_AwardPrizes(self.Round, bRedWin, rteam.id, bteam.id, rteam.level, bteam.level, rmembers, bmembers, topFiveIds, joinIds)
    
    -- 30��󣬴���������
    self.SModCommon:BroadcastClientOperation(UI_TIMER,tostring(30))
    self.SModCommon:CreateTimer(30,"HumanLeave")
end

function NJTZ:HumanLeave()
    -- SCLeaveActivity
    local msg = { activityid = self.ConfId }
    self.SModObjs:Broadcast(msgids.SCLeaveActivity,msg) 
    
    -- �������뿪����
    local humans = self.SModObjs:GetHumans()
    for k,v in pairs(humans) do

        v:LeaveDungeon()
    end
end

function NJTZ:Call(func, ...)
    pwdist.log('NJTZ:Call func=',func )
	
    local buf,len = seripack(...)
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity,0)
    pwdist.call(nil, pwngs_rpcnames.ctrlsrv.SImplActivity.CallScript, self.ConfId, func, buf)
end

--����ǰ�㲥��ʾ
function NJTZ:BroadCast_beforstart()
	self.SModObjs:BroadcastNotifyWithFaction(self.BROADCAST_BEFOR[self.broadcastBeforeIndex],ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
	self.SModObjs:BroadcastNotifyWithFaction(self.BROADCAST_BEFOR[self.broadcastBeforeIndex],ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
    self.broadcastBeforeIndex = self.broadcastBeforeIndex + 1
    if self.broadcastBeforeIndex > #self.BROADCAST_BEFOR then
        self.broadcastBeforeIndex = 1
    end
end

