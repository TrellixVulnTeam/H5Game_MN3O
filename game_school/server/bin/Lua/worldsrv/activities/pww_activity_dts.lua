-----------------------------------------------------------------
-- 活动:大逃杀
-- 世界服务器端
CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* 
-----------------------------------------------------------------

local DTS = {}

-----------------------------------------------------------------

SImplActivitiesClasses[1] = DTS

-----------------------------------------------------------------

DTS.BASEMAPID = {BASEMAPID_1 = 37501,
				 BASEMAPID_2 = 37502,
				}
				
DTS.ITEMCOUNT = {100, 100}

DTS.LEVELLIMIT = 40	
DTS.ITEMID = 400024
DTS.BUFF = {
	BUFF_HP = 60200,
	BUFF_ATTACK = 60201,
	BUFF_DEF = 60202,
	BUFF_SPEED = 60203,
	BUFF_INVINCIBLE = 60205,
    --[[去掉经验奖励
	BUFF_EXP = 60204,
	BUFF_EXP1 = 60207,
	BUFF_EXP2 = 60208,
	BUFF_EXP3 = 60209,--]]
	
}
DTS.PK_FACTION = 6
DTS.SAFE_FACTION = 1
DTS.RED_FACTION = 3
DTS.BLUE_FACTION = 4

DTS.PK_POSTION = {{187.41,60.27,232.13},
{201.60,57.56,138.27},
{203.22,57.59,37.83},
{171.38,55.18,60.16},
{113.18,50.52,67.65},
{89.63,60.27,107.91},
{29.72,58.78,76.26},
{115.43,56.08,161.67},
{52.20,56.47,215.47}
					}
DTS.SAFE_POSTION = {{187.41,60.27,232.13}}

DTS.DOOROBJ = {DoorId = 1003003,
			Dir = {	
					{1,0,0},					
					{0,0,-1},
					{1,0,0},
					{0,0,-1},
					{0,0,-1}
					},
			DoorPos= {				
						{209.75,58.97,242.22},						
						{232.08,61.97,81.44},							
						{87.19,60.38,133.86},		
						{149.46,58.88,218},		
						{52.43,55.40,162.33}	
					 },
			}
DTS.BLOODOBJ = {BloodId = 1003001,
			 Dir = {{0,0,-1},
					{0,0,-1},
					{0,0,-1},
					{0,0,1},
					{0,0,1}
			},
			 BloodPos= {{219.17,55.09,198.69},
						{239.25,62.00,127.22},
						{183.69,57.61,124},
						{106.56,58.47,39.84},
						{148.47,50.45,81.44}
					 },
			}

DTS.BUFFOBJ = {BuffId = 1003002,
			   Dir = {{0,0,1},
						{0,0,1},
						{0,0,-1},
						{0,0,1},
						{-1,0,0}			   
			   },
			   BuffPos= {{148.11,54.61,137.69},
						{119.44,55.02,162.53},
						{79.63,54.99,74.93},
						{59.11,60.26,119.95},
						{94.55,58.56,214.80}
					 },
			}

DTS.UPDATE_TYPE = { init = 1, item = 2, kill = 3, killed = 4, }

DTS.TOP3PrizeItem = { 670001,670002,670003 }	

DTS.GAMETIME = 1200 --20分钟
DTS.PREP_UPDATE_FACTION_TIME = 30 --30秒

function DTS:New(conf)
    local r = conf or {}
    setmetatable(r,self)
    self.__index = self
    return r
end

function DTS:Start(stage, ref, id)
    --pwdist.log('DTS:Start ' .. tostring(id) .. tostring(stage)..tostring(ref))

    self.ScriptRef = ref
    self.Stage = stage
    self.Id = tostring(id)
	self.BaseMap = 0
	self.Sublime = 0
	self.NormalLeaveHumans = {}
    self.PendingRandomPositionHumans = {}
	self.Humans = {}
	self.SModCommon = self.Stage:GetModCommon()
    self.WillTransportHumans = {}
    self.Finished = false
	self.GameStartTime = os.time()
    self.FadeScreenHumans = {}
    
    self.SModObjs = self.Stage:GetModObjs()
end


function DTS:Clean()
    --pwdist.log('DTS:Clean')
end

--------------------------------------------------------------------------

function DTS:OnHumanEnter(unit)
    --pwdist.log('DTS:OnHumanEnter' .. tostring(unit:GetID()) .. ' sublime=' .. tostring(self.Sublime))
 -- pwdist.log('玩家进入了')	
	local human = unit:cast('Human')
	local strid = tostring(human:GetID())

	-- 发送分线id信息
	self.Stage:GetModCommon():ClientOperation(human,UI_DTS_SUBLIME,tostring(self.Sublime),"")
    
    --human:GetModAura():Create(self.BUFF.BUFF_EXP)
    
    -- 进入时给无敌
    -- human:GetModMisc():SetBitEx(UnitBits.IMMUNIZING,5000)
    
    self.WillTransportHumans[strid] = nil
	--print('baseMap', self.BaseMap, type(self.BaseMap))
	local count  =  human:GetModItem():GetQuestBag():CollectNum(self.ITEMID)
	
	local humanInfo = { id = human:GetID(),
						name = human:GetName(),
						killnum = 0,
						killednum = 0,
						constkill = 0,
						score = 0,
						itemCount = count,
						basemap = self.BaseMap,
						guildid = unit:GetID(),
					 }
					 
	self.Humans[strid] = humanInfo
	self:Call('_rpc_Update_HumanInfo', self.BaseMap, strid, humanInfo, self.UPDATE_TYPE.init,self.Sublime)
	
	--print('humanInfo-------id---------&&&&&&&&&&------------', humanInfo.id)
	--print('humanInfo-------guildid---------&&&&&&&&&&------------', strid)
	
	--self:_HumanSendMsg(human, strid, 1)
	
	self:Call('_rpc_UpdateFactionLeave', strid, false)
	
	-- 增加活跃度
	human:GetModDailyBonus():InjectActivityComplete(7,1)
	
	--都进PK区
	self:DTSEnterArea(human, 1)

	local timerid = self.Stage:GetModCommon():CreateTimer(2,"OnHumanEnterTimer")
	self.Stage:GetModCommon():SetTimerContext(timerid,{ strid })
	
	self.Stage:ReportHumanEnterToActivityManager(1,toll(strid))

end

function DTS:OnHumanEnterTimer(timerid)
	local strid = pwdist.unpack(self.Stage:GetModCommon():GetTimerContext(timerid))

	local humanobj = self.Stage:GetModObjs():GetHuman(toll(strid))
	
	if humanobj ~= nil then
		self:OnHumanItemUpdate(humanobj,self.ITEMID)
		--pwdist.log('DTS::OnHumanEnterTimer processed:',strid)
	end
end

function DTS:_rpc_Update_HumanInit(humanInfo, showType)
	local strid = tostring(humanInfo.id)
	
	local stage = GetCurrentStage()
	local human = stage:GetModObjs():GetHuman(toll(strid))
	
	self.Humans[strid] = humanInfo
	self:_HumanSendMsg(human, strid, showType)	
end

function DTS:OnHumanLeave(human)
  --pwdist.log('DTS:OnHumanLeave '..tostring(self.BaseMap))
	
	local strid = tostring(human:GetID())
    
	if self.Finished then
		self.WillTransportHumans[strid] = false
		return
	end
	
	--self:Call('CancelSignup',  tostring(human:GetID()), toll(self.Id), tostring(self.Stage:GetID()))
	self:Call('CancelSignup',  tostring(human:GetID()), toll(self.Id), self.BaseMap,self.Sublime)
	
	local ret = (self.NormalLeaveHumans[strid] == nil)
    self.NormalLeaveHumans[strid] = nil
    self.WillTransportHumans[strid] = nil
    
	
    --pwdist.log('OnHumanLeave 扣牌子=' .. tostring(ret) .. ' id=' .. strid)
    
	if self.BaseMap == self.BASEMAPID.BASEMAPID_2 then

		local sanbox = MultiItemSandbox.new(human)
		local count  =  human:GetModItem():GetQuestBag():CollectNum(self.ITEMID)
		local num = 0
		if count > 200 then
			num = count - 200
		end
		
    --pwdist.log('OnHumanLeave 扣牌子 itemnum=' .. tostring(count) .. ' num=' .. tostring(num))
        
		if num ~= 0 then
			sanbox:Del(4, self.ITEMID, num)
			sanbox:Commit()
			--pwdist.log('OnHumanLeave,name='..human:GetName()..',id='..strid..',count='..count..',drop num ='..num)
		end
	end
	
	self:_HumanSendMsg(human, strid, 3)
	self.Humans[strid].itemCount = human:GetModItem():GetQuestBag():CollectNum(self.ITEMID)
	self:Call('_rpc_Update_HumanInfo', self.BaseMap, strid, self.Humans[strid], self.UPDATE_TYPE.item,self.Sublime)
	
	self:Call('_rpc_UpdateFactionLeave', strid, true)
end

function DTS:Call(func, ...)
    --pwdist.log('DTS:Call func=' .. func )
	
    local buf,len = seripack(...)
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity,0)
    pwdist.call(nil, pwngs_rpcnames.ctrlsrv.SImplActivity.CallScript, toll(self.Id), func, buf)
end

function DTS:_rpc_Initial(id, basemap,subline,stageLimits)
    --pwdist.log('DTS:_rpc_Initial' .. tostring(id), basemap,"subline=",subline)
-- pwdist.log("初始化华林射鬼")	
	self.BaseMap = basemap
	self.Sublime = subline
	self.StageLimits = stageLimits
	
	SetEventHandler_for_ActivityPlay(StageEvents.HumanKilled, "OnHumanKilled")
	SetEventHandler_for_ActivityPlay(StageEvents.HumanResurrect, "OnHumanResurrect")
	SetEventHandler_for_ActivityPlay(StageEvents.HumanItemUpdate, "OnHumanItemUpdate", {itemType = self.ITEMID})
	SetEventHandler_for_ActivityPlay(StageEvents.HumanLevelup, "OnHumanLevelup")
	
	--SetEventHandler_for_ActivityPlay(StageEvents.HumanDropped, "OnHumanDropped")

	local i = 1
	for i = 1, 5, 1 do
		self.Stage:CreateStaticObject(self.DOOROBJ.DoorPos[i], self.DOOROBJ.Dir[i], self.DOOROBJ.DoorId, 4, "_OnDoor")	
	end
	
	math.randomseed(os.time())
	math.random(30, 60)
	local rand = math.random(30, 60)
	self.SModCommon:CreateTimer(rand, "_OnTimeAddHpObj")
	self.SModCommon:CreateTimer(rand, "_OnTimeAddBufObj")
	--每10秒向活动管理线程报告人数
	self.SModCommon:CreatePeriodTimer(10,10,0,"_OnTimeUpdateHumanCount")
	--10分钟后玩家重新分配阵营
	if self.BaseMap ~= self.BASEMAPID.BASEMAPID_1 then
		self.SModCommon:CreateTimer(600-DTS.PREP_UPDATE_FACTION_TIME, "_OnTimePrepareUpdateFaction")
	end

	self.timer_upklist = self.SModCommon:CreatePeriodTimer(0,EXPTIME,120,"OnTimer_upklist")	------循环给予玩家经验值奖励----总时长变的时候，循环次数也需变

end
-----给予玩家经验值奖励
function DTS:OnTimer_upklist()
-- pwdist.log("给玩家经验函数，根据玩家等级来给")
	local humans = GetCurrentStage():GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		local HumLevel = v:GetLevel()		
		if(HumLevel ~= nil and HumLevel >= DTS.LEVELLIMIT)then
			local EXPlayer = 1
			local ExpNum = 1	
			if(self.BaseMap == self.BASEMAPID.BASEMAPID_1)then
				EXPlayer = MULTIPLE1
			elseif(self.BaseMap == self.BASEMAPID.BASEMAPID_2)then
				EXPlayer = MULTIPLE2
			end
			
			if(HumLevel <= 70) then
				ExpNum = 1
			elseif(HumLevel> 70 and HumLevel <= 80) then
				ExpNum = 1.5
			elseif(HumLevel > 80 and HumLevel <= 85) then
				ExpNum = HumLevel*0.1-6.5
			elseif(HumLevel > 85 and HumLevel <= 100) then
				ExpNum = HumLevel*0.2-15
			else
				ExpNum = HumLevel*0.5-45
			end
			
			local IndexExp = ExpNum*EXPlayer*EXPTIME
			local EXP = math.floor(IndexExp)					------------向下取整
			v:GetModExp():Add(EXP,4,0)							---------给玩家加经验值
-- pwdist.log("加了经验====="..EXP)
		end
	end
-- pwdist.log("-----------------------------------------")
end

function DTS:_OnTimeUpdateHumanCount()
	self.Stage:ReportHumanCountToActivityManager(1)
end

function DTS:_rpc_AwardPrize(rank, isReward)
    --pwdist.log('DTS:_rpc_AwardPrize')
   
    local params = {}
    local index = 1
    for _, v in pairs(rank) do
		params[index] = toll(_)
		params[index + 1] = v
		index = index + 2
    end
   
    local buf, len = seripack(params)
   
    self.Stage:GetModActivityPlay():DTS_AwardPrizes(buf,DTS.ITEMID,DTS.TOP3PrizeItem,isReward)

    --pwdist.log('**DTS** map=' .. tostring(self.BaseMap) .. ' humanum=' .. tostring(self.Stage:GetModObjs():GetHumanNum()))
end

function DTS:_rpc_UpdateHumanNums(humaninfo)
	--pwdist.log('_rpc_UpdateHumanNums')
	self.StageHumanInfos = humaninfo
	
	local basemap32 = toint32(self.Stage:GetBaseMapID())
--[[	
	for k,v in pairs(self.StageHumanInfos) do
		--pwdist.log(tostring(basemap32) .. ' human sub=' .. tostring(k) .. ' count=' .. tostring(v))
	end
--]]
end

function DTS:_rpc_HumanLeaveHint(ids)
    self.Finished = true
	--pwdist.log('DTS:_rpc_HumanLeaveHint')	
	local stage = GetCurrentStage()	
    
    stage:GetModActivityPlay():SetFinished(true)
	stage:SetCanPickup(false) --活动结束不可以捡牌子
    
	for i = 1, #ids do
		if ids[i] ~= nil then
			local strid = ids[i]
			local human = stage:GetModObjs():GetHuman(toll(strid))
			if human ~= nil then				
				human:SendNotifyMsg( 51604, CHAT_MODE_AWARD, CHAT_TEXT_SYSTEM)
				human:GetModMisc():SetBitEx(UnitBits.IMMUNIZING,18000)	--活动结束到离开，15秒时间
				human:GetModAura():Create(self.BUFF.BUFF_INVINCIBLE)
			end
		end	
	end
    
    for k,v in pairs(self.WillTransportHumans) do
        local strid = tostring(k)
        local human = stage:GetModObjs():GetHuman(toll(strid))
        if human ~= nil then
            --pwdist.log('_rpc_HumanLeaveHint rest human darkarea: ' .. strid)
            self:_SwitchAnim(human, strid, 2)
        end
    end
    self.WillTransportHumans = {}
end

function DTS:_rpc_HumanLeave(ids)
	--pwdist.log('DTS:_rpc_HumanLeave')
	
	local stage = GetCurrentStage()
	
	for i = 1, #ids do
		-- print('human:', ids[i])
		if ids[i] ~= nil then
			local strid = ids[i]
			local human = stage:GetModObjs():GetHuman(toll(strid))
			if human ~= nil then				
				local msg = { activityid = toll(self.Id)}
				human:SendMsg(msgids.SCLeaveActivity,msg)
				self.Humans[strid] = nil
				self.NormalLeaveHumans[strid] = 'ok'
				human:LeaveDungeon()
			end
		end	
	end
end

function DTS:_rpc_Update_Rank(rank)
	 --pwdist.log('DTS:_rpc_Update_Rank')
	 
	  local msg = { info = {} }
	  local i = 0
	  for k, v in pairs(rank) do
        i = i + 1
        msg.info[i] = 
        {
			id = toll(k),
			name = v.name,
			score = v.score,
			killnum = v.killnum,
			killednum = v.killednum,
			itemcount = v.itemCount,
			seconds = self:GetRestSecondes(), 
			guildid = v.guildid,
		}
        if v.tencent_user_info ~= nil then
        	msg.info[i].tencent_user_info = v.tencent_user_info
        end
		--print('humanrankinfo:', msg.info[i].id, msg.info[i].name, msg.info[i].guildid)
	 end
	 
    self.Stage:GetModObjs():Broadcast(msgids.SCDTSRankUpdate, msg) 
end
--[[去掉经验奖励
function DTS:GetBuffExp()
    local mapid = toint32(self.Stage:GetBaseMapID())
    
    if mapid == self.BASEMAPID.BASEMAPID_1 then
        do return self.BUFF.BUFF_EXP1 end
    elseif mapid == self.BASEMAPID.BASEMAPID_2 then
        do return self.BUFF.BUFF_EXP2 end
    else
        do return self.BUFF.BUFF_EXP3 end
    end
end
--]]
function DTS:DTSEnterArea(human, areaType)--进入战斗区或者安全区 //1:安全区 2：PVP
	--pwdist.log('DTS:DTSEnterArea' .. tostring(areaType))
	
    math.randomseed(os.time())
	math.random(1, 9)
	local rand = math.random(1, 9)
	local num = human:GetModItem():GetQuestBag():CollectNum(self.ITEMID)
	--[[去掉经验奖励
    human:GetModAura():Delete(self.BUFF.BUFF_EXP1)
    human:GetModAura():Delete(self.BUFF.BUFF_EXP2)
    human:GetModAura():Delete(self.BUFF.BUFF_EXP3)
	
	human:GetModAura():Create(self:GetBuffExp())
    --]]
	if areaType == 1 then
        -- 直接进场
        human:GetModMotionMaster():ChangePosition(self.PK_POSTION[rand])
		self:ChangeFaction(human) 
		human:GetModLansquenet():ChangeLansFaction()	
	elseif areaType == 2 then
        --同步ctrl
        local strid = tostring(human:GetID())
        self:_SwitchAnim(human, strid, 1)
        self.PendingRandomPositionHumans[strid] = 'ok'
        local timerid = self.SModCommon:CreateTimer(2, "_OnSwitchAnimHandle")
        --local expbuffid = self:GetBuffExp()
        --pwdist.log('expbuffid=',expbuffid)
        self.SModCommon:SetTimerContext(timerid,{ 0, strid, self.PK_POSTION[rand], 0, self.BUFF.BUFF_INVINCIBLE })--删除了expbuffid项
        
        -- print('strid:', strid, self.Humans[strid])
        self.Humans[strid].itemCount = num
        self:Call('_rpc_Update_HumanInfo', self.BaseMap, strid, self.Humans[strid], self.UPDATE_TYPE.item,self.Sublime)
        
        self:_HumanSendMsg(human, strid, 2)
        --改阵营
        self:ChangeFaction(human)
		human:GetModLansquenet():ChangeLansFaction()
	end
	
	return 0
end

function DTS:ChangeFaction(human)
	local strid = tostring(human:GetID())
	self:Call('_rpc_GetFaction', self.BaseMap, strid, self.Sublime)
end

function DTS:_rpc_Update_faction(strid,faction)
    --pwdist.log('_rpc_Update_faction',strid)
    local stage = GetCurrentStage()
    local human = stage:GetModObjs():GetHuman(toll(strid))
	
	local mapid = toint32(self.Stage:GetBaseMapID())
	if mapid == self.BASEMAPID.BASEMAPID_1 then
		return
	end
	
	if faction == DTS.RED_FACTION or faction == DTS.BLUE_FACTION then
		human:ChangeFaction(faction)
		human:GetModLansquenet():ChangeLansFaction()
	end

	--pwdist.log('strid:', strid, 'faction:', faction)	
end

function DTS:_OnTimePrepareUpdateFaction()
	self.SModCommon:BroadcastClientOperationEx(UI_TIMER,tostring(DTS.PREP_UPDATE_FACTION_TIME),tostring(51701))
	self.SModCommon:CreateTimer(DTS.PREP_UPDATE_FACTION_TIME,"_OnTimeUpdateFaction")
end

function DTS:_OnTimeUpdateFaction()
	local faction = 0
	local humans = self.Stage:GetModActivityPlay():GetHumansByFightPoint()
	local rfactions = {}
	local bfactions = {}
	for i = 1, #humans do
		if i % 2 == 0 then
			faction = DTS.RED_FACTION
			table.insert(rfactions,tostring(humans[i]))
		else
			faction = DTS.BLUE_FACTION
			table.insert(bfactions,tostring(humans[i]))
		end
		local human = self.Stage:GetModObjs():GetHuman(toll(humans[i]))
		if human ~= nil then
			human:ChangeFaction(faction)
			human:GetModLansquenet():ChangeLansFaction()
		end
	end
	
	self:Call('_rpc_UpdateFaction', rfactions, bfactions)
end

function DTS:ConstKillNotify(human, count)

	if count >= 5 and count <= 10 then
	
		local strID = 134101 + (count - 5)
		
		self.SModObjs:BroadcastNotifyToWorld(strID, human:GetName(), human:GetID(), human:GetSex())
	end
	
end

function DTS:OnHumanKilled(human, killer)

    if self.Finished then
		self:_HumanRealive(human)
        do return end
    end
    --pwdist.log('DTS:OnHumanKilled')
	
	if killer:IsKindOf(CLSID.Human) then
		local strkillerid = tostring(killer:GetID())
    local humankiller = killer:cast('Human')
		self.Humans[strkillerid].killnum = self.Humans[strkillerid].killnum + 1
		-- 连杀数
		self.Humans[strkillerid].constkill = self.Humans[strkillerid].constkill + 1
		self:ConstKillNotify(humankiller, self.Humans[strkillerid].constkill)
		
		--pwdist.log('OnHumanKilled,name='..human:GetName()..' ,constkill='..tostring(self.Humans[strkillerid].constkill))
		
		self:Call('_rpc_Update_HumanInfo', tostring(self.Stage:GetID()), strkillerid, self.Humans[strkillerid], self.UPDATE_TYPE.kill,self.Sublime)
		self:_HumanSendMsg(humankiller, strkillerid, 2)
	end
	
	if not human:IsKindOf(CLSID.Human) then 
		return
	end
	
	local strid = tostring(human:GetID())
	
	-- 连杀数清零
	if killer:IsKindOf(CLSID.Human) then
		
		if self.Humans[strid].constkill >= 5 then
			local humankiller = killer:cast('Human')
			human:SendNotifyMsg(134107, CHAT_MODE_SYSTEM, CHAT_TEXT_SYSTEM, humankiller:GetName(), humankiller:GetID(),humankiller:GetSex(), human:GetName(), human:GetID(), human:GetSex())
		end
		
		self.Humans[strid].constkill = 0
	end
		
	if self.BaseMap == self.BASEMAPID.BASEMAPID_2 then
		--删除令牌
		local sanbox = MultiItemSandbox.new(human)
		local count  =  human:GetModItem():GetQuestBag():CollectNum(self.ITEMID)
		local num = math.floor(count / 2)
		
		if num ~= 0 then
			sanbox:Del(4, self.ITEMID, num)
			sanbox:Commit()
			--pwdist.log('OnHumanKilled,name='..human:GetName()..',id='..strid..',count='..count..',drop num ='..num)
			--掉落物品
			-- for i = 1, num, 1 do
				-- luaE_drop(human, killer, 1, {self.ITEMID}, {1}, 10000)
			-- end
		
			luaE_drop(human, killer, 1, {self.ITEMID}, {num}, 10000)
		end
		
		local itemCount = count - num
		if self.BaseMap == self.BASEMAPID.BASEMAPID_2 then
--pwdist.log("如果当前地图等于地图2")	
			if itemCount < self.ITEMCOUNT[2] then
--pwdist.log("传送回1")	
				self:DoTransportDownDelay(human, self.BaseMap, self.BASEMAPID.BASEMAPID_1)
--pwdist.log("传送完成")	
			end
		end
	end

	self.Humans[strid].killednum = self.Humans[strid].killednum + 1		
	
    self:_HumanRealive(human)    
	
	--同步ctrl
	self:Call('_rpc_Update_HumanInfo', tostring(self.Stage:GetID()), strid, self.Humans[strid], self.UPDATE_TYPE.killed,self.Sublime)
	self:_HumanSendMsg(human, strid, 2)
end

function DTS:RealiveHuman(timerid)
    local id = pwdist.unpack(self.SModCommon:GetTimerContext(timerid))
    local stage = GetCurrentStage()
	local pHuman = stage:GetModObjs():GetHuman(id)
    if pHuman ~= nil then
        self:_HumanRealive(pHuman)
    end
end

function DTS:OnHumanResurrect(human)
    local strid = tostring(human:GetID())

	--pwdist.log('DTS:OnHumanResurrect',strid,self.WillTransportHumans[strid])

    if self.WillTransportHumans[strid] == nil then
		human:GetModAura():Create(112)
		--human:GetModMisc():SetBitEx(UnitBits.IMMUNIZING,3000)
        self:DTSEnterArea(human, 2)
        human:GetModMisc():SetBitEx(UnitBits.IMMUNIZING,3000)
    end
end

function DTS:OnHumanItemUpdate(human, itemId)
	--pwdist.log('DTS:OnHumanItemUpdate', itemId)
	
    if self.Finished then
        do return end
    end

	local strid = tostring(human:GetID())
    
    if self.WillTransportHumans[strid] ~= nil then
		local itemCount  =  human:GetModItem():GetQuestBag():CollectNum(self.ITEMID)		
		self.Humans[strid].itemCount = itemCount
		self:Call('_rpc_Update_HumanInfo', self.BaseMap, strid, self.Humans[strid], self.UPDATE_TYPE.item,self.Sublime)
		self:_HumanSendMsg(human, strid, 2)
        do return end
    end
	
	if itemId == self.ITEMID then
		local itemCount  =  human:GetModItem():GetQuestBag():CollectNum(self.ITEMID)
		self.Humans[strid].itemCount = itemCount
		self:Call('_rpc_Update_HumanInfo', self.BaseMap, strid, self.Humans[strid], self.UPDATE_TYPE.item,self.Sublime)
		self:_HumanSendMsg(human, strid, 2)
			
		if self.BaseMap == self.BASEMAPID.BASEMAPID_2 then
		
			if itemCount < self.ITEMCOUNT[2] then
				-- self.Humans[strid] = nil
				self:DoTransportDownDelay(human,self.BaseMap,self.BASEMAPID.BASEMAPID_1)
			end
					
		elseif self.BaseMap == self.BASEMAPID.BASEMAPID_1 then
			
			if itemCount >= 200 then
				human:SendNotifyMsg(103224, CHAT_MODE_SYSTEM, CHAT_TEXT_SYSTEM)
				human:SetCanPickup(false)
			end
			
		end
	end
	
end

function DTS:OnHumanLevelup(human)
	if self.Finished then
        do return end
    end
	
	if human:GetLevel() ~= DTS.LEVELLIMIT or self.BaseMap ~= self.BASEMAPID.BASEMAPID_1 then
		do return end
	end
	
	human:SetCanPickup(true)
	
	local itemCount = human:GetModItem():GetQuestBag():CollectNum(self.ITEMID)	

	if itemCount >= self.ITEMCOUNT[2] and itemCount < self.ITEMCOUNT[1] then
		-- self.Humans[strid] = nil
		self:DoTransportUpDelay(human,self.BaseMap,self.BASEMAPID.BASEMAPID_2)
	end	
	
end

function DTS:OnHumanDropped(human)
	--pwdist.log('DTS:OnHumanDropped')
	
	--删除令牌
	local sanbox = MultiItemSandbox.new(human)
	local count  =  human:GetModItem():GetQuestBag():CollectNum(self.ITEMID)
	local num = 0
	local strid = tostring(human:GetID())

	if count % 2 == 0 then
		num = count / 2
	elseif count % 2 == 1 then
		num = (count + 1) / 2
	end
	
	if num ~= 0 then
		sanbox:Del(4, self.ITEMID, num)
		sanbox:Commit()
		--pwdist.log('OnHumanDropped,name='..human:GetName()..',id='..strid..',count='..count..',drop num ='..num)
	end
	
	local count = human:GetModItem():GetQuestBag():CollectNum(self.ITEMID)
	self.Humans[strid].itemCount = count
	self:Call('_rpc_Update_HumanInfo', self.BaseMap, strid, self.Humans[strid], self.UPDATE_TYPE.item,self.Sublime)
	self:_HumanSendMsg(human, strid, 2)
	
	self:Call('_rpc_UpdateFactionLeave', strid, true)
end

function DTS:GetTargetSublime()
	local basemap32 = toint32(self.Stage:GetBaseMapID())
	local stage_limit = self.StageLimits[basemap32]

--	return math.random(1,#self.StageHumanInfos)
	for k,v in pairs(self.StageHumanInfos) do
		if v < stage_limit then
			return k
		end
	end
	return self.Sublime
end

function DTS:_OnDoor(obj, human)

    if self.Finished then
        do return end
    end

    local dstsublime = self:GetTargetSublime()
	local pHuman = human:cast('Human')
	
	--pwdist.log('_OnDoor:' .. tostring(dstsublime))

  if dstsublime == self.Sublime then
		--pwdist.log('DTS:_OnDoor')
		math.randomseed(os.time())
		math.random(1, 9)
		local rand = math.random(1, 9)
		local strid = tostring(human:GetID())
	    
	    if self.WillTransportHumans[strid] ~= nil then
	        --pwdist.log('DTS:DoTransportDelay strid ~= nil')
	        do return end
	    end
		
	    if self.PendingRandomPositionHumans[strid] ~= nil then
	        --pwdist.log('door id=' .. strid .. ' in pending')
	        do return end
	    end
		
	    if pHuman ~= nil then
	        if self:_SwitchAnim(pHuman, strid, 1) then
	            local timerid = self.SModCommon:CreateTimer(2, "_OnSwitchAnimHandle")
	            self.PendingRandomPositionHumans[strid] = 'ok'
	            self.SModCommon:SetTimerContext(timerid,{ 1, strid, self.PK_POSTION[rand] } )
	        end
	    end    
	else
		--pwdist.log('DoTransportSelectSublimeDelay',tostring(self.BaseMap),tostring(dstsublime))
		self:DoTransportSelectSublimeDelay(pHuman,self.BaseMap,dstsublime)
	end
end

function DTS:_OnTimeAddHpObj()
	--pwdist.log('DTS:_OnTimeAddHpObj')

	local i = 1
	for i = 1, 5, 1 do
		self.Stage:CreateStaticObject(self.BLOODOBJ.BloodPos[i], self.BLOODOBJ.Dir[i], self.BLOODOBJ.BloodId, 3,"_OnAddHp")	
	end
	
end

function DTS:_OnTimeAddBufObj()
	--pwdist.log('DTS:_OnTimeAddBufObj')
	
	local i = 1
	for i = 1, 5, 1 do
		self.Stage:CreateStaticObject(self.BUFFOBJ.BuffPos[i], self.BUFFOBJ.Dir[i], self.BUFFOBJ.BuffId, 3,"_OnAddBuff")	
	end
	
end

function DTS:_OnAddHp(obj, human)
	--pwdist.log('DTS:_OnAddHp')
	
	obj:LeaveWorld(0)
	human:GetModAura():Create(self.BUFF.BUFF_HP)
end

function DTS:_OnAddBuff(obj, human)
	--pwdist.log('DTS:_OnAddBuff')
	
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

function DTS:GetRestSecondes()
	local past = os.time() - self.GameStartTime
	local rest = DTS.GAMETIME - past
	if rest > DTS.GAMETIME or rest < 0 then
		rest = DTS.GAMETIME
	end
	return rest
end

function DTS:_HumanSendMsg(human, strid, showType)

		if self.Humans[strid] == nil then
			print ('_HumanSendMsg',strid)
			return
		end
		
		-- print('killed:',strid, self.Humans[strid].name, self.Humans[strid].score, self.Humans[strid].killnum, self.Humans[strid].killednum, self.Humans[strid].itemCount)
		local msg = {
			type=showType, 
			 basemap = self.BaseMap, 
			 info = { id = toll(strid),
					  name = self.Humans[strid].name,
					  score = self.Humans[strid].score,
					  killnum = self.Humans[strid].killnum,
					  killednum = self.Humans[strid].killednum,
					  itemcount = self.Humans[strid].itemCount,
					  seconds = self:GetRestSecondes()
					}
			 }

		human:SendMsg(msgids.SCDTSHumanInfoUpdate, msg) 
end
function DTS:_HumanRealive(human)

	math.randomseed(os.time())
	math.random(1, 9)
	local rand = math.random(1, 9)
	human:GetModRealive():HideRealiveButton(true)
	human:GetModRealive():Realive(human:GetPosition() , 1000)
	
end

function DTS:_SwitchAnim(human, strid, open)
--pwdist.log("开始传送")	
    if open == 1 then
       if self.FadeScreenHumans[strid] ~= nil then
            --pwdist.log('_SwitchAnim errorstate ',tostring(open),strid)
            do return false end
        end
        self.FadeScreenHumans[strid] = 'IN'
    end   
    if open == 2 then
        if self.FadeScreenHumans[strid] == nil then 
            --pwdist.log('_SwitchAnim errorstate ',tostring(open),strid)
            do return false end
        end
        self.FadeScreenHumans[strid] = nil
    end
	--pwdist.log('_SwitchAnim', tostring(human), strid, open)
	local msg = {
		section = open,
        clear_objs = false
	}
	human:SendMsg(msgids.SCBabelSwitchAnim, msg)    
    return true
end

function DTS:_OnSwitchAnimHandle(timerid)
	local code,strid,pos,buff1,buff2 = pwdist.unpack(self.SModCommon:GetTimerContext(timerid))
	--pwdist.log('DTS:_OnSwitchAnimHandle',tostring(code),tostring(strid),tostring(pos),tostring(buff1),tostring(buff2))
	local stage = GetCurrentStage()
	local pHuman = stage:GetModObjs():GetHuman(toll(strid))
	
    self.PendingRandomPositionHumans[strid] = nil
    
	if pHuman == nil then
        do return end
	end
    
    if code == 0 then
        --pHuman:GetModAura():Create(buff1)
		pHuman:GetModAura():Create(buff2)

    end
    pHuman:GetModMotionMaster():ChangePosition(pos)
	self:_SwitchAnim(pHuman, strid, 2)
end

function DTS:DoTransportUpDelay(human,srcmap,destmap)
    if self.Finished then
        do return end
    end
    
    local id = human:GetID()
    local strid = tostring(id)
    
    if self.WillTransportHumans[strid] ~= nil then
        --pwdist.log('DTS:DoTransportDelay strid ~= nil')
        do return end
    end
    
	self.Stage:GetModCommon():ClientOperation(human,UI_TIMER,tostring(5),"")        
    human:GetModMisc():SetBitEx(UnitBits.IMMUNIZING,5000)
	human:GetModAura():Create(self.BUFF.BUFF_INVINCIBLE)
    self.WillTransportHumans[strid] = true
    
	local timerid = self.SModCommon:CreateTimer(5,'DoTransportUp')
    self.SModCommon:SetTimerContext(timerid,{ id,srcmap,destmap })
end


function DTS:DoTransportUp(timerid)
    local id,srcmap,destmap = pwdist.unpack(self.SModCommon:GetTimerContext(timerid))
    local strid = tostring(id)
	local human = self.Stage:GetModObjs():GetHuman(toll(strid))
    --pwdist.log(' DoTransport set id will leave:' .. strid)
	
	if self.Finished then
		self.WillTransportHumans[strid] = false
		return
	end
	
	if self.WillTransportHumans[strid] == nil or self.WillTransportHumans[strid] == false then
		return
	end	
	
	if human ~= nil then
		self:_SwitchAnim(human, strid, 1) 	
		self.NormalLeaveHumans[strid] = 'ok'
		self:Call('_rpc_transport', id,srcmap,self.Sublime,destmap)
		self:DoTransportAfter(tostring(id),destmap,self.Stage:GetBaseMapID())
	end
end

function DTS:DoTransportSelectSublimeDelay(human,srcmap,dstsublime)
	if self.Finished then
        do return end
    end
    
    local id = human:GetID()
    local strid = tostring(id)
    
    if self.WillTransportHumans[strid] ~= nil then
        --pwdist.log('DTS:DoTransportDelay strid ~= nil')
        do return end
    end
        
    local timerid = self.SModCommon:CreateTimer(2,'DoTransportSelectSublime')
    self.SModCommon:SetTimerContext(timerid,{ id,srcmap,dstsublime })
    human:GetModAura():Create(112)
    self.WillTransportHumans[strid] = true
    self:_SwitchAnim(human, strid, 1)	
end

function DTS:DoTransportDownDelay(human,srcmap,destmap)
    if self.Finished then
        do return end
    end
    
    local id = human:GetID()
    local strid = tostring(id)
    
    if self.WillTransportHumans[strid] ~= nil then
        --pwdist.log('DTS:DoTransportDelay strid ~= nil')
        do return end
    end
        
    local timerid = self.SModCommon:CreateTimer(2,'DoTransportDown')
    self.SModCommon:SetTimerContext(timerid,{ id,srcmap,destmap })
    human:GetModAura():Create(112)
    self.WillTransportHumans[strid] = true
    self:_SwitchAnim(human, strid, 1)	
end

function DTS:DoTransportSelectSublime(timerid)
    local id,srcmap,dstsublime = pwdist.unpack(self.SModCommon:GetTimerContext(timerid))
    local strid = tostring(id)
	
	if self.Finished then
		self.WillTransportHumans[strid] = false
		return
	end
	
	if self.WillTransportHumans[strid] == nil or self.WillTransportHumans[strid] == false then
		return
	end	
	
    --pwdist.log(' DoTransport set id will leave:' .. strid)
    self.NormalLeaveHumans[strid] = 'ok'
    self:Call('_rpc_transport', id,srcmap,self.Sublime,srcmap,dstsublime)
    
    local timerid = self.SModCommon:CreateTimer(2,'_OnSelectTransportCompleted')
    self.SModCommon:SetTimerContext(timerid,{ strid,srcmap,dstsublime })
end

function DTS:_OnSelectTransportCompleted(timerid)
	local strid,basemap,dstsublime = pwdist.unpack(self.SModCommon:GetTimerContext(timerid))
    self:Call('_rpc_DTSSelectTransportCompleted',strid,basemap,dstsublime,self.Sublime)
end

function DTS:DoTransportDown(timerid)
    local id,srcmap,destmap = pwdist.unpack(self.SModCommon:GetTimerContext(timerid))
    local strid = tostring(id)
	
	if self.Finished then
		self.WillTransportHumans[strid] = false
		return
	end
	
	if self.WillTransportHumans[strid] == nil or self.WillTransportHumans[strid] == false then
		return
	end	
	
    --pwdist.log(' DoTransport set id will leave:' .. strid)
    self.NormalLeaveHumans[strid] = 'ok'
    self:Call('_rpc_transport', id,srcmap,self.Sublime,destmap)
    self:DoTransportAfter(tostring(id),destmap,self.Stage:GetBaseMapID())
end

function DTS:DoTransportAfter(strid,basemap,oldbasemap)
    local timerid = self.SModCommon:CreateTimer(2,'_OnTransportCompleted')
    self.SModCommon:SetTimerContext(timerid,{ strid,basemap,oldbasemap })
end

function DTS:_OnTransportCompleted(timerid)
    local strid,basemap,oldbasemap = pwdist.unpack(self.SModCommon:GetTimerContext(timerid))
    --pwdist.log('_OnTransportCompleted',strid,basemap)
    self:Call('_rpc_DTSTransportCompleted',strid,basemap,oldbasemap,self.Sublime)
end

function DTS:GetNotifyStrId(basemap,oldbasemap)
    local newm = toint32(basemap)
    local oldm = toint32(oldbasemap)
    if oldm == self.BASEMAPID.BASEMAPID_1 and newm == self.BASEMAPID.BASEMAPID_2 then
        do return 51513 end
    elseif oldm == self.BASEMAPID.BASEMAPID_2 and newm == self.BASEMAPID.BASEMAPID_1 then
        do return 51515 end
    end	
    do return 51512 end
end

function DTS:GetMapLevel(basemap)
	local mapid = toint32(basemap)
	if mapid == self.BASEMAPID.BASEMAPID_1 then
		return 1
	elseif mapid == self.BASEMAPID.BASEMAPID_2 then
		return 2
	end
	return 0
end

function DTS:_rpc_TransportCompleted(strid,basemap,oldbasemap)
    --pwdist.log('_rpc_TransportCompleted',strid)
    local stage = GetCurrentStage()
    local pHuman = stage:GetModObjs():GetHuman(toll(strid))
    
    if pHuman ~= nil then
    	-- oldbasemap==nil表示同层传送
    	if oldbasemap ~= nil then
        	local notifystrid = self:GetNotifyStrId(basemap,oldbasemap)
        	--pwdist.log('notifystrid=',notifystrid,'basemap=',tostring(basemap),'oldbasemap=',tostring(oldbasemap))
        	pHuman:SendNotifyMsg( notifystrid, CHAT_MODE_AWARD, CHAT_TEXT_SYSTEM)
        	self:_SwitchAnim(pHuman, tostring(pHuman:GetID()), 2) 
					self.Stage:GetModActivityPlay():DTS_MapLevel(pHuman, self:GetMapLevel(basemap))	
					pHuman:GetModMisc():SetBitEx(UnitBits.IMMUNIZING,5000)
					pHuman:GetModAura():Create(self.BUFF.BUFF_INVINCIBLE)		
			else
        	self:_SwitchAnim(pHuman, tostring(pHuman:GetID()), 2)
			end
    else
        --pwdist.log('_rpc_TransportCompleted human = nil',strid)

        -- oldbasemap==nil表示同层传送
        if oldbasemap ~= nil then
        	local timerid = self.SModCommon:CreateTimer(1,'_OnTransportCompleted')
        	self.SModCommon:SetTimerContext(timerid,{ strid,basemap,oldbasemap })
        end
    end    
end

function DTS:_rpc_HumanTimeHint(ids,hintid)
	local stage = GetCurrentStage()	
      
	for i = 1, #ids do
		if ids[i] ~= nil then
			local strid = ids[i]
			local human = stage:GetModObjs():GetHuman(toll(strid))
			if human ~= nil then				
				human:SendNotifyMsg( hintid, CHAT_MODE_AWARD, CHAT_TEXT_SYSTEM)
				if hintid == 51605 then
					human:SendNotifyMsg( hintid, CHAT_MODE_ANNOUNCEMENT, CHAT_TEXT_SYSTEM)
				end
			end
		end	
	end
	
end

function DTS:DTSGmEndGame()
	self:Call('DoExpired')
end
