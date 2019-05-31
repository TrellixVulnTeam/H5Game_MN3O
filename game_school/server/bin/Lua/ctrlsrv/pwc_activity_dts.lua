-----------------------------------------------------------------
-- 活动:大逃杀
-- 控制服务器端
-----------------------------------------------------------------

local DTS = {}

-----------------------------------------------------------------

SImplActivitiesClasses[1] = DTS

-----------------------------------------------------------------

DTS.STATUS_AUCTION = 0
DTS.STATUS_CREATE_STAGE = 1
DTS.STATUS_TELEPORT = 2
DTS.STATUS_PREPARE = 3
DTS.STATUS_RUNNING = 4
DTS.STATUS_ENDED = 5
DTS.STATUS_CLOSED = 6

DTS.BASEMAPID = {BASEMAPID_1 = 37501,
				 BASEMAPID_2 = 37502,
				}

DTS.STAGE_LIMIT = {}
DTS.STAGE_LIMIT[DTS.BASEMAPID.BASEMAPID_1] = 80
DTS.STAGE_LIMIT[DTS.BASEMAPID.BASEMAPID_2] = 80

DTS.STAGE_CREATE_CONF = {}
DTS.STAGE_CREATE_CONF[DTS.BASEMAPID.BASEMAPID_1] = 5
DTS.STAGE_CREATE_CONF[DTS.BASEMAPID.BASEMAPID_2] = 3

DTS.UPDATE_TYPE = { init = 1, item = 2, kill = 3, killed = 4, }	

DTS.GAMETIME = 1200 --20分钟			

DTS.TIMER_HINT = {
				[1] = { ["time"] = 600,["strid"] = 51605,},
				[2] = { ["time"] = 60, ["strid"] = 51606,},
				[3] = { ["time"] = 30, ["strid"] = 51614,},
				[4] = { ["time"] = 10, ["strid"] = 51615,}, --迷宫探险活动将在10秒内结束。
			}

DTS.RED_FACTION = 3
DTS.BLUE_FACTION = 4
DTS.FactionHumans = {}	
-----------------------------------------------------------------

function DTS:New(conf)
	local r = conf or {}
    setmetatable(r,self)
    self.__index = self

	-----------------------------------------------------------------
    -- 地图信息
    -----------------------------------------------------------------
	r.Id = nil --活动ID
	r.Status = nil
	r.Maps = {
	}

	r.Rank = {}
	return r
end

--------------------------------------------------------------------------

function DTS:Start(ref,id)
    self.Id = id
    self.ScriptRef = ref
    self.Thread = GetServiceThread()
    self.Status = self.STATUS_AUCTION
    self.StepTimerId = self.Thread:CreateTimer(1,"OnAuctionEnded")
	self.Thread:CreateTimer(30, "UpdateActivityDTS")
	self.Thread:CreateTimerEx(1,1, "UpdateStageHumanNum") -- 更新每个地图的玩家数量给worldsrv的stage对象
    self.Finished = false

    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_READY)
	
end


--------------------------------------------------------------------------
function DTS:UpdateStageHumanNum()

	for _,m in pairs(self.Maps) do
		-- 先取得同层所有地图的玩家信息
		local humaninfo = {}
		for k,v in pairs(m) do
			humaninfo[k] = #v.Humans
		end
		-- 广播给所有同层地图
		for k,v in pairs(m) do
			self:Call('_rpc_UpdateHumanNums', v.StageNode, v.StagePort, v.GameMapId, humaninfo)
		end
	end
end

--副本更新数据函数
function DTS:UpdateActivityDTS()
	pwdist.log('DTS:UpdateActivityDTS')
		
	self.Thread:CreateTimer(300, "UpdateActivityDTS")
	
end

function DTS:OnAuctionEnded()
    pwdist.log('DTS:OnAuctionEnded')
    self.Status = self.STATUS_CREATE_STAGE
    self.StepTimerId = self.Thread:CreateTimer(1, "DoCreateStage")

end

function DTS:GetCreateNum(basemapid)
	local result = self.STAGE_CREATE_CONF[basemapid]
	if result == nil or result <= 0 then
		result = 2
	end
	return result
end

function DTS:GetTransportTargetSublime(basemapid)
	local stages = self.Maps[basemapid]
	local stage_limit = self.STAGE_LIMIT[basemapid]

	--for k, v in ipairs(stages) do
		--pwdist.log('GetTransportTargetSublime',k,v)
	--end


	if stages == nil then
		return
	end

	for k, v in ipairs(stages) do
	    if k == nil then
             return
         end
		 if v == nil then
             return
         end
		local num = #v.Humans
		if num < stage_limit then
			return k,v.StageNode,v.StagePort,v.GameMapId
		end
	end
	-- 都满了,随机找一个分线
	local r = math.random(1, #stages)	
	local info = stages[r]
	return r,info.StageNode,info.StagePort,info.GameMapId
end

function DTS:DoCreateStage()
    pwdist.log('DTS:DoCreateStage')

	for _, v in pairs(self.BASEMAPID) do
		pwdist.log('DTS:DoCreateStage',tostring(v))

		local num = self:GetCreateNum(v)
		for i=1, num do
			pwdist.prepare(pwngs_rpcnodes.ctrlsrv, pwngs_rpcports.ctrlsrv.stagemgr, 0)
			pwdist.call(nil, pwngs_rpcnames.ctrlsrv.SImplStageMgr.CreateStage, STAGE_FLAG_ACTIVITY, v, 0, nil)
			pwdist.listen_result_ref("OnCreateStageResult", self.ScriptRef, {v,i})
		end
	end
	
	self.Status = self.STATUS_PREPARE
    self.StepTimerId = self.Thread:CreateTimer(10,"DoRunning")
	self.UpdateTimerId = self.Thread:CreateTimerEx(1,2,"DoUpdateRank")
end

--生成一个默认副本，当玩家查询时发现已满再创建新副本

function DTS:OnCreateStageResult(params, code, node, port, gamemap)

    pwdist.log('DTS:OnCreateStageResult code=',tostring(code),tostring(gamemap), tostring(type(gamemap)))

    if code == nil then
        return
    end
	
    if code ~= 0 then
        self:Clean()
        return
    end
	
	local basemap,subline = pwdist.unpack(params)
	
	if basemap == nil then
		return
	end

	if self.Maps[basemap] == nil then
		self.Maps[basemap] = {}
	end

	self.Maps[basemap][subline] = {
			BaseMapId = tostring(basemap),
			GameMapId = tostring(gamemap),
			StageNode = node,
			StagePort = port,
			Humans = {} --玩家ID
	}
		

    -- 启动worldsrv端脚本
    pwdist.prepare(node , port, gamemap)
    pwdist.call(nil, pwngs_rpcnames.worldsrv.Stage.ActivityStartup, self.Id)

    -- 初始化
    self:Call('_rpc_Initial', node, port, gamemap, self.Id, basemap,subline,self.STAGE_LIMIT)

end


function DTS:DoRunning()
    pwdist.log('DTS:DoRunning')

    self.Status = self.STATUS_RUNNING
    self.StepTimerId = self.Thread:CreateTimer(DTS.GAMETIME,"DoExpired")
	--self.StepTimerId = self.Thread:CreateTimer(20,"DoExpired")
	
	self:TimeHint()
	
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_START)
    self.Thread:BroadcastActivityStart(self.Id)
end

function DTS:TimeHint()
	for i = 1, #DTS.TIMER_HINT, 1 do
		local timerid = self.Thread:CreateTimer(DTS.GAMETIME-DTS.TIMER_HINT[i]["time"],"DoTimeHint")
		self.Thread:SetTimerContext(timerid,{ DTS.TIMER_HINT[i]["strid"] })
	end
end

function DTS:DoTimeHint(timerid)

    pwdist.log('DTS:DoTimeHint')
	local hintid = pwdist.unpack(self.Thread:GetTimerContext(timerid))
    
	for _, m in pairs(self.Maps) do
		for _, v in ipairs(m) do
			if v.GameMapId ~= nil then
				self:Call('_rpc_HumanTimeHint', v.StageNode, v.StagePort, toll(v.GameMapId), v.Humans, hintid)
			end
		end
	end

end

function DTS:DoExpired()

    pwdist.log('DTS:DoExpired')
	
	--GM指令重复敲的情况
	if self.Finished then
		return
	end

    self.Finished = true
	
	--这个奖励处理包括销毁副本，不知道为啥这么做	
	local info = {}	
	for k,v in pairs(self.Rank) do
        info[k] = v.itemCount
    end
			
	local isReward = false
	for _, m in pairs(self.Maps) do
		for _, v in ipairs(m) do
			if v.GameMapId ~= nil then
				self:Call('_rpc_AwardPrize', v.StageNode, v.StagePort, toll(v.GameMapId), info, isReward)
				isReward = true
			end	
		end
	end
	
	local vtName = self:GetTop3Names()
    local nranks = {}
    for k,v in pairs(self.Rank) do
        nranks[k] = v.itemCount
    end
    self.Thread:GetDTS():DoFinished(nranks,vtName)
	
	for _, m in pairs(self.Maps) do
		for _, v in ipairs(m) do
			if v.GameMapId ~= nil then
				self:Call('_rpc_HumanLeaveHint', v.StageNode, v.StagePort, toll(v.GameMapId), v.Humans)
			end
		end
	end

    self.StepTimerId = self.Thread:CreateTimer(15, "DoFinished")
end

function DTS:DoFinished()

    pwdist.log('DTS:DoFinished')

	--玩家离开副本
	for _, m in pairs(self.Maps) do
		for _, v in ipairs(m) do
			if v.GameMapId ~= nil then
				self:Call('_rpc_HumanLeave', v.StageNode, v.StagePort, toll(v.GameMapId), v.Humans)
			end
		end
	end

	--C统一流程里调用了
    --self.StepTimerId = self.Thread:CreateTimer(20,"Clean")
	
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_END)
	
    self.StepTimerId = self.Thread:CreateTimer(5, "DoClose")
end

function DTS:DoClose()
	self:CleanFaction()
    self.Thread:CloseMe()
end

function DTS:Clean()
    -- close stage
    pwdist.log('DTS:Clean')

    -- 关闭worldsrv端脚本
	if self.Maps ~= nil then
		for _, m in pairs(self.Maps) do
			for _, v in ipairs(m) do
				if v.GameMapId ~= nil then
					pwdist.prepare(v.StageNode, v.StagePort, toll(v.GameMapId))
					pwdist.call(nil,pwngs_rpcnames.worldsrv.Stage.ActivityCleanup)
				end
			end
		end
	end
	
	--self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_QUIT)
	
	self.MapNum = 0
	self.Id = nil --活动ID
	self.Status = nil
	self.Maps = {}
	self.Rank = nil	
end

--------------------------------------------------------------------------

function DTS:Call(func, stageNode, stagePort, gameMapId, ...)
    --pwdist.log('DTS:Call ' .. tostring(func))
    local buf,_ = seripack(...)
    pwdist.prepare(stageNode, stagePort, gameMapId)
    pwdist.call(nil,pwngs_rpcnames.worldsrv.Stage.CallScript,func,buf)
end

--------------------------------------------------------------------------

function DTS:_rpc_DTSSelectTransportCompleted(strid,basemap,dstsublime,sublime)
    local basemap32 = toint32(basemap)

    pwdist.log('_rpc_DTSSelectTransportCompleted',basemap32,basemap,dstSublime,sublime)
    local info = self.Maps[basemap32][dstsublime]
	if info == nil then
		pwdist.log('_rpc_DTSTransportCompleted failed')
        return
	end
    
    self:Call('_rpc_TransportCompleted',info.StageNode,info.StagePort,info.GameMapId,strid,basemap,nil)
end

function DTS:_rpc_DTSTransportCompleted(strid,basemap,oldbasemap,sublime)
    local basemap32 = toint32(basemap)

    local info = self.Maps[basemap32][sublime]
	if info == nil then
		pwdist.log('_rpc_DTSTransportCompleted failed')
        return
	end
    
    self:Call('_rpc_TransportCompleted',info.StageNode,info.StagePort,info.GameMapId,strid,basemap,oldbasemap)
end

--[[
-- CBH　2014-06-06　不再使用
function DTS:_rpc_DTSActivitySignUpInfo(activityId) --得发副本信息

	 pwdist.log('DTS:_rpc_DTSActivitySignUpInfo ' .. tostring(activityId))

	local info = {}
	local index = 1
	for _, m in pairs(self.Maps) do
		for _, v in ipairs(m) do
			if v ~= nil then
	            local strmapid = tostring(v.BaseMapId)
				info[index] = toll(v.GameMapId)
				info[index+1] = v.BaseMapId
				info[index+2] = #self.Maps[strmapid].Humans
				index = index + 3
			end
		end
	end

	local buf,_ = seripack(info)
	
	return pwdist.return_values(buf)
end
--]]

function DTS:_rpc_transport(id, srcBaseMap, srcSublime, dstBaseMap,dstSublime)
    if self.Finished then 
        do return end
    end

    local srcbasemap32 = toint32(srcBaseMap)
    local dstbasemap32 = toint32(dstBaseMap)
    local dstsublime = dstSublime or self:GetTransportTargetSublime(dstbasemap32)
	
	pwdist.log('_rpc_transport:' .. tostring(dstsublime))
    	
    local old_humans = self.Maps[srcbasemap32][srcSublime].Humans
    local new_humans = self.Maps[dstbasemap32][dstsublime].Humans
    
	local strid = tostring(id)
	
    for k, v in ipairs(old_humans) do
		if v == strid then
			table.remove(old_humans,k)
			break
		end
	end
    
    table.insert(new_humans,strid)
	
	self:Enter(id, dstbasemap32,dstsublime)
end

--DTS.UPDATE_TYPE = { init = 1, item = 2, kill = 3, killed = 4, }		
--同步world上的令牌数
function DTS:_rpc_Update_HumanInfo(basemap, id, humanInfo, updateType,sublime)

	
	local basemap32 = toint32(basemap)

	pwdist.log('_rpc_Update_HumanInfo' .. tostring(id),tostring(updateType),tostring(sublime),tostring(basemap),tostring(basemap32) )
	
	if humanInfo == nil then
		return
	end
	
	local strid = tostring(id)
	
	if updateType == self.UPDATE_TYPE.init then
		local showType = 1
		if self.Rank[strid] == nil then
			self.Rank[strid] = humanInfo
			self.Rank[strid].basemap = humanInfo.basemap
			showType = 1
		else
			self.Rank[strid].guildid = humanInfo.guildid
			self.Rank[strid].itemCount = humanInfo.itemCount
			self.Rank[strid].basemap = humanInfo.basemap
			showType = 2
		end

		local stageinfo = self.Maps[basemap32][sublime]

		self:Call('_rpc_Update_HumanInit', stageinfo.StageNode, stageinfo.StagePort, toll(stageinfo.GameMapId), self.Rank[strid], showType)		
	elseif updateType == self.UPDATE_TYPE.item then
		self.Rank[strid].itemCount = humanInfo.itemCount
	elseif updateType == self.UPDATE_TYPE.kill then
		self.Rank[strid].killnum = humanInfo.killnum
	elseif updateType == self.UPDATE_TYPE.killed then
		self.Rank[strid].killednum = humanInfo.killednum
	end	
end

function DTS:DoUpdateRank()
	
	-- pwdist.log('DTS:DoUpdateRank')
	
	local tmpRank = {}
	local i = 0
	
	if self.Rank == nil then
		pwdist.log('Rank is nil')
		return
	end
	
	for k, v in pairs(self.Rank) do
		i = i + 1
		tmpRank[i] = v
        tmpRank[i].hid = toll(k)
	end
	
	local _sortRank = function(h1, h2)
        if h1.itemCount == h2.itemCount then
            return h1.hid < h2.hid
        end
		return h1.itemCount > h2.itemCount
	end

	table.sort(tmpRank, _sortRank)

	for _, v in pairs(tmpRank) do
		v.tencent_user_info = GetTencentUserInfo()
	end
		
	for _, m in pairs(self.Maps) do
		for _, v in ipairs(m) do
			self:Call('_rpc_Update_Rank', v.StageNode, v.StagePort, toll(v.GameMapId), tmpRank)
		end
	end
end
--------------------------------------------------------------------------

function DTS:Signup(id, activityId, basemap) -- 登陆到副本中
	if self.Finished then
		pwdist.log('DTS::Signup finished',tostring(id))
		return
	end

    pwdist.log('DTS:Signup ' .. tostring(id) .. 'activity:' .. tostring(activityId) .. 'basemap:' .. tostring(basemap) .. tostring(type(basemap)))

	local strid = tostring(id)
	local basemap32 = toint32(basemap)
	local sublime = self:GetTransportTargetSublime(basemap32)	
			
    pwdist.return_values(0)
			
	--进入副本
	self:Enter(id, basemap32,sublime)

    pwdist.log('DTS:Signup ' .. tostring(id) ..  'activity' .. tostring(activityId) .. 'gameMapId:' ..  tostring(basemap) .. ' OK!')
end

--------------------------------------------------------------------------

function DTS:CancelSignup(id, activityId, basemap,sublime) -- 退出副本
    pwdist.log('DTS:CancelSignup ' .. tostring(id) .. 'activityId' .. tostring(activityId) .. 'basemap:' .. tostring(basemap)..' OK!')
	

	local strid = tostring(id)
	local basemap32 = toint32(basemap)
		
	local humans = self.Maps[basemap32][sublime].Humans	
    
	for k, v in ipairs(humans) do
		if v == strid then
            table.remove(humans,k)
            break
		end
	end
	
end

function DTS:Enter(id, dstbasemap32,dstsublime)
    pwdist.log('DTS:Enter ' .. tostring(id),tostring(dstbasemap32),tostring(dstsublime))

  local info = self.Maps[dstbasemap32][dstsublime]
  if info == nil then
  	return
  end
  
	local humans = info.Humans
	local strid = tostring(id)
	
	local isExist = false
	for k, v in pairs(humans) do
		if v == strid then
			isExist = true
            break
		end
	end
	
	if not isExist then
        table.insert(humans,strid)
	end
	
	--print('TeleportHuman', id, basemap, self.Maps[strbasemap].GameMapId)
    self.Thread:TeleportHuman(id, toll(dstbasemap32), toll(info.GameMapId), 0 )
end

function DTS:GetTop3Names()
	local tmpRank = {}
	local i = 0
	for k, v in pairs(self.Rank) do
		i = i + 1
		tmpRank[i] = v
        tmpRank[i].hid = toll(k)
	end
	
	local _sortRank = function(h1, h2)
        if h1.itemCount == h2.itemCount then
            return h1.hid < h2.hid
        end
		return h1.itemCount > h2.itemCount
	end

	table.sort(tmpRank, _sortRank)
	
	local names = {}
	local size = #tmpRank
	
	if size >= 3 then
		names = { tmpRank[1].name, tmpRank[2].name, tmpRank[3].name, }
	elseif size == 2 then
		names = { tmpRank[1].name, tmpRank[2].name,}
	elseif size == 1 then
		names = { tmpRank[1].name, }
	end
	
	return names
end

function DTS:PrintMaps()
	for _, v in pairs(self.Maps) do
		if v.GameMapId ~= nil then
			for id, strid in pairs(v.Humans) do
				print('--------------_='.._..',GameMapId='..v.GameMapId..',id='..id..',strid='..strid)
			end
		end
	end
end

function DTS:_rpc_GetFaction(basemap, id, sublime)
	local basemap32 = toint32(basemap)
	local strid = tostring(id)
	local red = 0
	local blue = 0
	local faction
	
	if DTS.FactionHumans[strid] ~=nil and DTS.FactionHumans[strid].faction ~= nil then
		faction = DTS.FactionHumans[strid].faction
	else
		for k,v in pairs(DTS.FactionHumans) do
			if v.leave == false then
				if v.faction == DTS.RED_FACTION then
					red = red + 1
				elseif v.faction == DTS.BLUE_FACTION then
					blue = blue + 1
				end
			end
		end
		
		pwdist.log('FACTION,red:', red, 'blue:', blue)
		if red <= blue then
			faction = DTS.RED_FACTION
		else
			faction = DTS.BLUE_FACTION
		end		
		DTS.FactionHumans[strid] = {}
		DTS.FactionHumans[strid].faction = faction
		DTS.FactionHumans[strid].leave = false
	end
	
	local stageinfo = self.Maps[basemap32][sublime]
	self:Call('_rpc_Update_faction', stageinfo.StageNode, stageinfo.StagePort, toll(stageinfo.GameMapId), strid, faction)
	pwdist.log('_rpc_GetFaction,strid='..strid..',faction='..faction)	
end

function DTS:_rpc_UpdateFaction(rfactions,bfactions)
	for i = 1, #rfactions do
		if rfactions[i] ~= nil then
			local strid = rfactions[i]
			if DTS.FactionHumans[strid] ~=nil then
				DTS.FactionHumans[strid].faction = DTS.RED_FACTION
			end
		end	
	end
	for i = 1, #bfactions do
		if bfactions[i] ~= nil then
			local strid = bfactions[i]
			if DTS.FactionHumans[strid] ~=nil then
				DTS.FactionHumans[strid].faction = DTS.BLUE_FACTION
			end
		end	
	end
end

function DTS:_rpc_UpdateFactionLeave(id,status)
	local strid = tostring(id)
	if DTS.FactionHumans[strid] ~=nil then
		DTS.FactionHumans[strid].leave = status
		pwdist.log('FACTION:update leave')
	end	
end

function DTS:CleanFaction()
	DTS.FactionHumans = {}
	pwdist.log('FACTION:CleanFaction')
end