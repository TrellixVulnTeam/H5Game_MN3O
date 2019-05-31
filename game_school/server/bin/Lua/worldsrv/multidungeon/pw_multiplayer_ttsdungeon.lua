--淘汰赛副本

CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .
CurrentDungeonScript.finish = false -- finish

CurrentDungeonScript.CAMP_INDEX_RED = 1
CurrentDungeonScript.CAMP_INDEX_BLUE = 2
CurrentDungeonScript.CAMPPOS = { {126.071,54.599,125.28}, {31.83,54.653,32.22} }
CurrentDungeonScript.nRedGuildId = 0;
CurrentDungeonScript.nBlueGuildId = 0;

CurrentDungeonScript.RESSCORE = {1,2,3,4,5}
CurrentDungeonScript.BigResScore = 1	--大点额外得分
CurrentDungeonScript.MAXSCORE = 5000

CurrentDungeonScript.FACTION_NEUTRAL = 7
CurrentDungeonScript.FACTION_MONSTER = 2
CurrentDungeonScript.FACTION_RED = 3
CurrentDungeonScript.FACTION_BLUE = 4
CurrentDungeonScript.CAMPS = { CurrentDungeonScript.FACTION_RED, CurrentDungeonScript.FACTION_BLUE }

CurrentDungeonScript.AURA_CONFIG = {[CurrentDungeonScript.FACTION_RED] = 60307,[CurrentDungeonScript.FACTION_BLUE] = 60306}	--玩家脚底光环

CurrentDungeonScript.BROADCAST_BEFOR = {51354,51355,51356}	--赛前广播提示
CurrentDungeonScript.BROADCAST_BEFOREND = 51374 -- 会战2分钟后结束，届时资源多的一方获胜
CurrentDungeonScript.BROADCAST_TYPE = 2

CurrentDungeonScript.RESSCORE_ADDBASE = 0 -- 资源分每次增加基础值，实际增加值为人数差+2，最高不能超过10
CurrentDungeonScript.RESSCORE_ADDMAX = 10 -- 资源分每次增加最大值
CurrentDungeonScript.RESSCOREMAX = 100 -- 资源分达到-100分，资源被红方抢占，资源分达到100分，资源被蓝方抢占

CurrentDungeonScript.RANKADD_KILL = 10    -- 杀人得2积分
CurrentDungeonScript.RANKADD_OCCUPY = 10 -- 抢占资源得10积分

-- 总时间后销毁场景
CurrentDungeonScript.TOTAL_TIME = 30 * 60
-- 开启前等待时间--第2分钟
CurrentDungeonScript.START_WAIT_TIME = 2 * 60
-- 战斗结束前提示--第20分钟
CurrentDungeonScript.BEFORE_FINISH_TIME = 20 * 60
-- 战斗结束时间--第30分钟
CurrentDungeonScript.FINISH_TIME = 22 * 60

CurrentDungeonScript.BUFFOBJ = {
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

CurrentDungeonScript.BUFF = {
	--BUFF_HP = 60200,
	BUFF_ATTACK = 60201,
	BUFF_DEF = 60202,
	BUFF_SPEED = 60203,
	--BUFF_EXP = 60204,
	BUFF_INVINCIBLE = 60800,
    
	--BUFF_EXP1 = 60207,
	--BUFF_EXP2 = 60208,
	--BUFF_EXP3 = 60209
}

CurrentDungeonScript.ResurrectPos = { 
										{
											{126.071,54.599,125.28},
											{126.071,54.599,125.28},
										},
										{ 
											{31.83,54.653,32.22},
											{31.83,54.653,32.22},					
										} 
									}

-- 中立资源					
CurrentDungeonScript.RESOBJ = {
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

-- 保护塔			
CurrentDungeonScript.TOWEROBJ = {
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
        CurrentDungeonScript.FACTION_RED,
        CurrentDungeonScript.FACTION_RED,
        CurrentDungeonScript.FACTION_BLUE,
        CurrentDungeonScript.FACTION_BLUE,
    },
}

CurrentDungeonScript.SERVER_STR = {
    ENEMY_OCCUPY_RES = 51358,   -- 敌方占领资源
    OUR_OCCUPY_RES = 51359,     -- 我方占领资源
    ENEMY_LOSE_RES = 51360,     -- 敌方丢失资源
    OUR_LOSE_RES = 51361,       -- 我方丢失资源
    
    BATTER_5 = 51362,          -- 5连杀
    BATTER_6 = 51363,          -- 6连杀
    BATTER_7 = 51364,          -- 7连杀
    BATTER_8 = 51365,          -- 8连杀
	BATTER_9 = 51366,          -- 9连杀
	BATTER_10 = 51367,			--10连杀
    
    BATTER_END = 51369,     -- >=5连杀被终结了
    
    ENEMY_SCORE_1000 = 51370,   -- 敌方已经积累了4000积分了
    ENEMY_SCORE_1800 = 51371,   -- 敌方已经积累了4800积分了，接近胜利了
    OUR_SCORE_1000 = 51372,     -- 我方已经积累了4000积分了
    OUR_SCORE_1800 = 51373,     -- 我方已经积累了1800资源了，马上接近胜利了
}


-- 开始初始化
function CurrentDungeonScript:Startup()
	pwdist.log("tts:startup");
	
	self.SModDungeonScript = self.Stage:GetModDungeonScript()
	self.SModCommon = self.Stage:GetModCommon()
	self.SModAOI = self.Stage:GetModAOI()
    self.SModObjs = self.Stage:GetModObjs()
	
	local SModLogic = self.Stage:GetModLogic()
	self.SModLogicTTS = SModLogic:cast("SModLogicTTS")

    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanKilled,"OnHumanKilled")
    SetEventHandler(StageEvents.HumanResurrect,"OnHumanResurrect")
	
    self.CampHumans = {}
    self.CampHumans[self.FACTION_RED] = {}
    self.CampHumans[self.FACTION_BLUE] = {}

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
	
	-- 初始化红队和蓝队的GuildId
	self.nRedGuildId = self.SModLogicTTS:GetRedGuildId();
	self.nBlueGuildId = self.SModLogicTTS:GetBlueGuildId();
	
	pwdist.log('[hz]red[' .. tostring(self.nRedGuildId) .. "]blue[" .. tostring(self.nBlueGuildId) .. "]")
	
	-- 设置场景阻挡
	self.Stage:GetModDetour():EnableMotionBlock(0, false)
	self.Stage:GetModDetour():EnableMotionBlock(1, false)
	self.Stage:GetModDetour():EnableMotionBlock(2, false)
	self.Stage:GetModDetour():EnableMotionBlock(3, false)
	
	-- 刷出第一次的中立资源
    for k,v in ipairs(self.RESOBJ.ResId) do
        local res = self.SModCommon:SpawnMonsterAt(self.RESOBJ.ResPos[k],self.RESOBJ.ResDir[k],v)
        res:ChangeFaction(self.FACTION_NEUTRAL)
        
        local staticObject = res:cast("StaticObject")
        staticObject:Enable(false)

        local resTab = {
            ResObj = res,   -- 资源对象
            Score = 0,      -- 资源当前分数
            Radius = self.RESOBJ.ResRad[k], -- 资源争夺半径
            ResNo = k,      -- 资源序号
            RedNum = 0,     -- 占领人数：红方
            BlueNum = 0,    -- 占领人数：蓝方
        }
        table.insert(self.CampResources.Resources,resTab)
    end
    
    -- 刷出保护塔
    for k,v in ipairs(self.TOWEROBJ.TowerId) do
        local tow = self.SModCommon:SpawnMonsterAt(self.TOWEROBJ.TowerPos[k],self.TOWEROBJ.TowerDir[k],v)
        tow:ChangeFaction(self.TOWEROBJ.TowerFaction[k])
        tow:SetBit(UnitBits.IMMUNIZING,true)
        
        pwdist.log('_rpc_Initial tower:',tostring(v))
    end
	
	-- 会战START_WAIT_TIME秒后开始
	self.startTimer = self.SModCommon:CreateTimer(self.START_WAIT_TIME, "Timer_start")
	
	-- 会战最后两分钟提示，会战即将结束
    self.beforeEndTimer = self.SModCommon:CreateTimer(self.BEFORE_FINISH_TIME, "BroadCast_beforend")
	
	-- 会战到达最长结束时间
	self.finishTimer = self.SModCommon:CreateTimer(self.FINISH_TIME, "OnFinishTTS")
	
	-- 进入倒计时
	self.Game_start_clock = os.time() + self.START_WAIT_TIME
	
	pwdist.log("tts:startup end")
end

-- 通过GuildId获取红蓝阵营索引
function CurrentDungeonScript:GetCampIndex(guildid)
    if self.nRedGuildId == guildid then
        return self.CAMP_INDEX_RED
	elseif self.nBlueGuildId == guildid then
		return self.CAMP_INDEX_BLUE
	else
		pwdist.log("[hz]guildid[" .. tostring(guildid) .. "]red[" .. tostring(self.nRedGuildId) .. "]blue[" .. tostring(self.nBlueGuildId) .. "]")
		return self.CAMP_INDEX_RED
    end
end

-- 通过阵营获取红蓝阵营索引
function CurrentDungeonScript:GetCampIndexByCamp(camp)
    if camp == self.FACTION_RED then
        return self.CAMP_INDEX_RED
	elseif camp == self.FACTION_BLUE then
		return self.CAMP_INDEX_BLUE
	else
		pwdist.log("[hz]camp[" .. tostring(camp) .. "]")
		return self.CAMP_INDEX_RED
    end
    
end

function CurrentDungeonScript:GetResScoreAddValue(diffnum)
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

function CurrentDungeonScript.MembersComparer(m1,m2)
    if m1.Rank ~= m2.Rank then
        return m1.Rank > m2.Rank
    else
        return m1.CombatPoint > m2.CombatPoint
    end
end

function CurrentDungeonScript:AddPersonScoreWhenOccupy(humanTab,camp)
    for _,human in ipairs(humanTab) do
        if human:GetFaction() == camp and (not human:IsDead()) then
            local strid = tostring(human:GetID())
            local humantable = self.CampHumans[camp][strid]
            if humantable ~= nil then
                humantable.Rank = humantable.Rank + self.RANKADD_OCCUPY
                humantable.OccupationNum = humantable.OccupationNum + 1
            else
                pwdist.log('OnHumanKilled humantable==nil',camp,strid)
            end
        end
    end
end

-- 禁用所有阻挡效果
function CurrentDungeonScript:DisableAllBlockEffects()
    for k,v in pairs(self.BlockEffects) do
        self.Stage:GetModDetour():EnableBlockEffects(k,false)
    end
    
    self.BlockEffects = {}
end

function CurrentDungeonScript:OnNotifyScoreChanged(camp,oldScore,newScore)
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

-- 资源变更
function CurrentDungeonScript:OnResourceChanged()
    local rteaminfo = 
    { 
        teamid = self.nRedGuildId, 
        resources = self.CampResources[self.CAMP_INDEX_RED] ,
        score = self.CampScores[self.CAMP_INDEX_RED],
		maxscore = self.MAXSCORE
    }
     local bteaminfo = 
    { 
        teamid = self.nBlueGuildId, 
        resources = self.CampResources[self.CAMP_INDEX_BLUE] ,
        score = self.CampScores[self.CAMP_INDEX_BLUE],
		maxscore = self.MAXSCORE
    }
    local msg = 
    {
        red = rteaminfo,
        blue = bteaminfo,
		kfmz = true
    }
    self.SModObjs:Broadcast(msgids.SCJTZNUpdate,msg)
end

-- 获取资源分数
function CurrentDungeonScript:GetResScoreAddValue(diffnum)
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

function CurrentDungeonScript:AddPersonScoreWhenOccupy(humanTab,camp)
    for _,human in ipairs(humanTab) do
        if human:GetFaction() == camp and (not human:IsDead()) then
            local strid = tostring(human:GetID())
            local humantable = self.CampHumans[camp][strid]
            if humantable ~= nil then
                humantable.Rank = humantable.Rank + self.RANKADD_OCCUPY
                humantable.OccupationNum = humantable.OccupationNum + 1
            else
                pwdist.log('OnHumanKilled humantable==nil',camp,strid)
            end
        end
    end
end

function CurrentDungeonScript.MembersComparer(m1,m2)
    if m1.Rank ~= m2.Rank then
        return m1.Rank > m2.Rank
    else
        return m1.CombatPoint > m2.CombatPoint
    end
end
-- 获取个人排行
function CurrentDungeonScript:GetRanklist()
    local members = {}
    for _,v in pairs(self.CampHumans[self.FACTION_RED]) do
        table.insert(members, v)
    end

    for _,v in pairs(self.CampHumans[self.FACTION_BLUE]) do
        table.insert(members, v)
    end

    table.sort(members, self.MembersComparer)
    return members
end

function CurrentDungeonScript:OnNotifyResCampChanged(oldCamp,newCamp)
    -- 红方资源丢了
    if oldCamp == self.FACTION_RED then
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.OUR_LOSE_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.ENEMY_LOSE_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
    end

    -- 蓝方资源丢了
    if oldCamp == self.FACTION_BLUE then
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.OUR_LOSE_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.ENEMY_LOSE_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
    end

    -- 红方占领了资源
    if newCamp == self.FACTION_RED then
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.OUR_OCCUPY_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.ENEMY_OCCUPY_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
    end

    -- 蓝方占领了资源
    if newCamp == self.FACTION_BLUE then
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.OUR_OCCUPY_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
        self.SModObjs:BroadcastNotifyWithFaction(self.SERVER_STR.ENEMY_OCCUPY_RES,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
    end
end

-- 结算
function CurrentDungeonScript:Settlement()
    pwdist.log('tts:Settlement')
	
	if self.Finished then
        return
    end
	
    self.Finished = true
	
	-- 同步个人分数
	self:BroadcastRanksEx(nil, nil, nil)
	
	-- 同步团队分数
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

	local winGuildId = 0
    -- 结算胜负[ToDo]
	if self.CampScores[self.CAMP_INDEX_RED] > self.CampScores[self.CAMP_INDEX_BLUE] then
		winGuildId = self.nRedGuildId
	elseif self.CampScores[self.CAMP_INDEX_RED] < self.CampScores[self.CAMP_INDEX_BLUE] then
		winGuildId = self.nBlueGuildId
	else
		-- 相等时，红队胜利
		winGuildId = self.nRedGuildId
	end
	
	-- 通知结束倒计时
	local msg = 
	{
		flag = 2
	}
	self.SModObjs:Broadcast(msgids.SCTTSEnter, msg)
	
	-- 通知pwctrl淘汰赛结果
	self.SModLogicTTS:TTSGuildWin(winGuildId)
	
	-- 发送结果
	self:BroadcastRanks(nil,true,winGuildId)
	
	-- 场景60秒后销毁
	self.Stage:StartDestruct(60)
	
	pwdist.log('tts:Settlement end')
end

-- 到时间结束
function CurrentDungeonScript:OnFinishTTS()
	self:Settlement()
end

-- 每5秒更新一次联盟得分
function CurrentDungeonScript:UpdatePer5Sec()
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
		for i,v in pairs(self.CampHumans[self.FACTION_RED]) do
			if v.Dismissed == false then
				v.Rank = v.Rank + self.RESSCORE[rnum]
				if rbignum > 0 then
					v.Rank = v.Rank + self.BigResScore
				end
			end
		end
	end
	
	if bnum > 0 then
		for i,v in pairs(self.CampHumans[self.FACTION_BLUE]) do
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
	
	for i,v in pairs(self.CampHumans[self.FACTION_RED]) do
		rNewScore = rNewScore + v.Rank
	end
	
	for i,v in pairs(self.CampHumans[self.FACTION_BLUE]) do
		bNewScore = bNewScore + v.Rank
	end
	
	self.CampScores[self.CAMP_INDEX_RED] = rNewScore
	self.CampScores[self.CAMP_INDEX_BLUE] = bNewScore
	
	self.CampScores[self.CAMP_INDEX_RED] = math.min(self.CampScores[self.CAMP_INDEX_RED],self.MAXSCORE)
	self.CampScores[self.CAMP_INDEX_BLUE] = math.min(self.CampScores[self.CAMP_INDEX_BLUE],self.MAXSCORE)

    self:OnNotifyScoreChanged(self.FACTION_RED,rOldScore,rNewScore)
    self:OnNotifyScoreChanged(self.FACTION_BLUE,bOldScore,bNewScore)
    
    -- 广播数据
    self:OnResourceChanged()
    
    if (self.CampScores[self.CAMP_INDEX_RED] >= self.MAXSCORE or self.CampScores[self.CAMP_INDEX_BLUE] >= self.MAXSCORE) then
        self:Settlement()
    end
end

-- 每秒更新资源分数
function CurrentDungeonScript:UpdatePer1Sec()
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
        
        -- 更新资源分数
        local oldScore = resTab.Score
        resTab.Score = resTab.Score + self:GetResScoreAddValue(resTab.RedNum - resTab.BlueNum)
        resTab.Score = math.max(math.min(resTab.Score, self.RESSCOREMAX), -self.RESSCOREMAX)
        local newScore = resTab.Score
        
        -- 下发资源信息给客户端
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
		
        -- 占领后，给友方加血buff
        local resBuf = self.RESOBJ.ResBuf[resIdx]
        
        local oldResCamp = resObj:GetFaction()
        -- 变成中立资源
        if (oldScore > 0 and newScore <= 0) or (oldScore < 0 and newScore >= 0) then
            if oldResCamp ~= self.FACTION_NEUTRAL then
                resObj:ChangeFaction(self.FACTION_NEUTRAL)
                self:OnNotifyResCampChanged(oldResCamp,self.FACTION_NEUTRAL)

                resObj:GetModAura():Create(resBuf)
            end
        end
        
        -- 变成蓝方资源
        if oldScore > -self.RESSCOREMAX and newScore <= -self.RESSCOREMAX then
            if oldResCamp ~= self.FACTION_BLUE then
                resObj:ChangeFaction(self.FACTION_BLUE)
                self:AddPersonScoreWhenOccupy(humanTab,self.FACTION_BLUE)
                self:OnNotifyResCampChanged(oldResCamp,self.FACTION_BLUE)

                resObj:GetModAura():Delete(resBuf)
                resObj:GetModAura():Create(resBuf)
            end
        end
        
        -- 变成红方资源
        if oldScore < self.RESSCOREMAX and newScore >= self.RESSCOREMAX then
            if oldResCamp ~= self.FACTION_RED then
                resObj:ChangeFaction(self.FACTION_RED)
                self:AddPersonScoreWhenOccupy(humanTab,self.FACTION_RED)
                self:OnNotifyResCampChanged(oldResCamp,self.FACTION_RED)

                resObj:GetModAura():Delete(resBuf)
                resObj:GetModAura():Create(resBuf)
            end
        end
        
        -- 统计两方资源数
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

function CurrentDungeonScript:BroadcastRanks(timer,_finished,_winnerid)
    -- 计算个人积分
    local msg = { ranks = {}, kfmz_guild_info = 
			{
				red_guild_id = self.SModLogicTTS:GetRedGuildId(),
				blue_guild_id = self.SModLogicTTS:GetBlueGuildId(),
				red_guild_name = self.SModLogicTTS:GetRedGuildName(),
				blue_guild_name = self.SModLogicTTS:GetBlueGuildName(),
			}, }
    
    msg.finished = _finished or false
    if msg.finished then
        msg.winnerid = _winnerid
    end
	
	pwdist.log('guildred:' .. msg.kfmz_guild_info.red_guild_name);

    local ranklist = self:GetRanklist()

    for i,v in ipairs(ranklist) do
        local tuserinfo = self.TencentUserInfos[tostring(v.ID)]
		--occupation_num此处用作最大连杀数
        msg.ranks[i] = 
        {
            id = v.ID,
            name = v.Name,
            rank = v.Rank,
            kill_count = v.KillCount,
            occupation_num = v.MaxBatterCount,
			guild_id = v.GuildId,
        }
		
        if tuserinfo ~= nil then
            msg.ranks[i].tencent_user_info = tuserinfo
        end
    end
    
    self.SModObjs:Broadcast(msgids.SCJTZNRoundResult,msg) 
    
    return ranklist
end

function CurrentDungeonScript:BroadcastRanksEx(timer,_finished,_winnerid)
    -- 计算个人积分
    local msg = { info = {} }
    
    local ranklist = self:GetRanklist()

    for i,v in ipairs(ranklist) do
        local tuserinfo = self.TencentUserInfos[tostring(v.ID)]
		--itemcount此处用作抢夺资源数
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

function CurrentDungeonScript:Timer_start()
    pwdist.log('tts:OnStarted')

    self.startTimer = nil
    
	-- 关闭阻挡，允许通行
   	self.Stage:GetModDetour():EnableMotionBlock(0, true)
	self.Stage:GetModDetour():EnableMotionBlock(1, true)
    self.Stage:GetModDetour():EnableMotionBlock(2, true)
	self.Stage:GetModDetour():EnableMotionBlock(3, true)   
    -- 禁用所有阻挡效果
    self:DisableAllBlockEffects()
    
	-- 开始关卡
    self.SModCommon:LaunchPolt(DUNGEON_START, 0, "")
    
    -- 5秒更新一次联盟得分
    self.updateScoreTimer = self.SModCommon:CreatePeriodTimer(10, 10, -1, "UpdatePer5Sec")
    
    -- 1秒更新一次场景中的资源分数
    self.updateResTimer = self.SModCommon:CreatePeriodTimer(1, 1, -1,"UpdatePer1Sec")
    
    -- 1秒广播一次个人得分排行
    self.broadcastTimer = self.SModCommon:CreatePeriodTimer(1, 1, -1,"BroadcastRanksEx")
    
    --开场5秒后循环播放广播
    self.broadcastBeforeIndex = 1
	self.SModCommon:CreatePeriodTimer(5, 10, #self.BROADCAST_BEFOR,"BroadCast_beforstart")
    
    -- 开始一段时候后刷新Buff球
    math.randomseed(os.time())
	math.random(30, 60)
	local rand = math.random(30, 60)
	self.SModCommon:CreateTimer(rand, "_OnTimeAddBufObj")
	
	-- 副本倒计时
	local msg = { targetlist = {} }
	msg.timesec = self.FINISH_TIME - self.START_WAIT_TIME
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList,msg)
	
	pwdist.log('tts:OnStarted end')
end

function CurrentDungeonScript:_OnTimeAddBufObj()
	pwdist.log('tts:_OnTimeAddBufObj')
	
	for k,v in ipairs(self.BUFFOBJ.BuffId) do
		self.Stage:CreateStaticObject(self.BUFFOBJ.BuffPos[k], self.BUFFOBJ.BuffDir[k], v, 3,"_OnAddBuff")	
	end
	
	pwdist.log('tts:_OnTimeAddBufObj end')
end

function CurrentDungeonScript:_OnAddBuff(obj, human)
	pwdist.log('tts:_OnAddBuff')
	
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
	
	pwdist.log('tts:_OnAddBuff end')
end

--开赛前广播提示
function CurrentDungeonScript:BroadCast_beforstart()
	self.SModObjs:BroadcastNotifyWithFaction(self.BROADCAST_BEFOR[self.broadcastBeforeIndex],ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
	self.SModObjs:BroadcastNotifyWithFaction(self.BROADCAST_BEFOR[self.broadcastBeforeIndex],ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
    self.broadcastBeforeIndex = self.broadcastBeforeIndex + 1
    if self.broadcastBeforeIndex > #self.BROADCAST_BEFOR then
        self.broadcastBeforeIndex = 1
    end
end

function CurrentDungeonScript:BroadCast_beforend()
    pwdist.log('tts:BroadCast_beforend')

    self.beforeEndTimer = nil
    self.SModObjs:BroadcastNotifyWithFaction(self.BROADCAST_BEFOREND,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_RED)
    self.SModObjs:BroadcastNotifyWithFaction(self.BROADCAST_BEFOREND,ChannelType.Announcement,self.BROADCAST_TYPE,self.FACTION_BLUE)
	
	pwdist.log('tts:BroadCast_beforend end')
end

-- 广播阻挡效果状态
function CurrentDungeonScript:BroadcastBlockEffectsStatus()
    for k,v in pairs(self.BlockEffects) do
        self.Stage:GetModDetour():EnableBlockEffects(k,v)
    end
end

-- 广播资源状态
function CurrentDungeonScript:BroadcastResStatus()
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

---玩家进入副本函数
function CurrentDungeonScript:HumanEnterEvent(human)
	pwdist.log('tts:OnHumanEnter',tostring(human:GetID()))
    
	-- 通知进入淘汰赛
	local msg = 
	{
		flag = 1
	}
	human:SendMsg(msgids.SCTTSEnter, msg)
	
    self:BroadcastBlockEffectsStatus()
    
	-- 进入倒计时提示
    if self.startTimer ~= nil then
        if self.Game_start_clock - os.time() > 0 then
		    self.SModCommon:ClientOperation(human,UI_TIMER,tostring(self.Game_start_clock - os.time()),"")
        end
    end
	
	-- 副本倒计时
	if self.Game_start_clock ~= 0 then
		if os.time() - self.Game_start_clock > 0 then
			local leaft_time = self.FINISH_TIME - self.START_WAIT_TIME - (os.time() - self.Game_start_clock)
			if leaft_time > 0 then
				local msg = { targetlist = {} }
				msg.timesec = leaft_time
				human:SendMsg(msgids.SCDungeonTargetList,msg)
				
				pwdist.log('leaft_time:'..tostring(leaft_time))
			end
		end
	end
	
    local guildid = human:GetKfmzGuildId()
    local campindex = self:GetCampIndex(guildid)
    local camp = self.CAMPS[campindex]
	
    local strid = tostring(human:GetID())

    if not self.Finished and self.CampHumans[camp][strid] == nil then
        self.CampHumans[camp][strid] = {}
        local humantable = self.CampHumans[camp][strid]
        humantable.Name = human:GetName()
        humantable.ID = human:GetID()
		humantable.GuildId = guildid
        humantable.Camp = camp
        humantable.CampIndex = campindex        
        humantable.Rank = 0
        humantable.Dismissed = false
        humantable.KillCount = 0
        humantable.OccupationNum = 0
        humantable.BatterCount = 0 -- 连杀数，死亡清零
		humantable.MaxBatterCount = 0 -- 最大连杀
        humantable.CombatPoint = human:GetModCombatPoint():GetCombatPoint()
    end
	
	if self.CampHumans[camp][strid] then
		self.CampHumans[camp][strid].Dismissed = false
	end
	
	-- 改变角色进入点位置
	human:GetModMotionMaster():ChangePosition(self.CAMPPOS[campindex])
    human:ChangeFaction(self.CAMPS[campindex])
	--human:GetModLansquenet():ChangeLansFaction()--改变侍从阵营
	human:GetModAura():Create(self.AURA_CONFIG[self.CAMPS[campindex]]) --加光环
	
	pwdist.log('tts:OnHumanEnter end')
end

function CurrentDungeonScript:HumanLeaveEvent(human)
	pwdist.log("tts:leavehuman");
	
    if human ~= nil then
        if not self.Finished then
            local guildid = human:GetKfmzGuildId()
            local campindex = self:GetCampIndex(guildid)
            local camp = self.CAMPS[campindex]
            local strid = tostring(human:GetID())
            local humantable = self.CampHumans[camp][strid]
			if nil ~= humantable then
				humantable.Dismissed = true
			end
        end
    end
end

function CurrentDungeonScript:EventCreateProcess()
	pwdist.log("tts:create");
end

function CurrentDungeonScript:EventDestroyProcess()
	pwdist.log("tts:destroy");
end

function CurrentDungeonScript:OnNotifyKiller(killed,killer,killerbattercount)
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

function CurrentDungeonScript:OnNotifyKilled(killer,killed,killedbattercount)
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

function CurrentDungeonScript:OnHumanKilled(human,killer)
    pwdist.log('tts:OnHumanKilled')
    if self.Finished then
        return
    end
    
    if not killer:IsKindOf(CLSID.Human) then
        return
    end
    
    local killercamp = killer:GetFaction()
    local killerstrid = tostring(killer:GetID())    
   
    local killerhuman = killer:cast('Human')
    if killerhuman ~= nil then
        local humantable = self.CampHumans[killercamp][killerstrid]
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
    local killedstrid = tostring(human:GetID())
    if human ~= nil then
        local humantable = self.CampHumans[killedcamp][killedstrid]
        if humantable ~= nil then
            self:OnNotifyKilled(killerhuman,human,humantable.BatterCount)
            humantable.BatterCount = 0
        else
            pwdist.log('OnHumanKilled killedtable==nil',killedcamp,killedstrid)
        end
    end
end

function CurrentDungeonScript:OnHumanResurrect(human)
	pwdist.log('tts:OnHumanResurrect',tostring(human:GetID()))
    
    local camp = human:GetFaction()
    local campindex = self:GetCampIndexByCamp(camp)
	math.randomseed(os.time())
	math.random(1, 2)
	local rand = math.random(1, 2)
    human:GetModMotionMaster():ChangePosition(self.ResurrectPos[campindex][rand])
    
    -- 复活免疫5秒
    human:GetModAura():Create(self.BUFF.BUFF_INVINCIBLE)
end