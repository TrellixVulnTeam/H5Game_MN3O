-----------------------------------------------------------------
-- 活动:龙王归来 
-- 控制服务器端
-----------------------------------------------------------------


local LWGL = {}

-----------------------------------------------------------------

--SImplActivitiesClasses[1] = LWGL

-----------------------------------------------------------------

LWGL.STATUS_AUCTION = 0
LWGL.STATUS_CREATE_STAGE = 1
LWGL.STATUS_TELEPORT = 2
LWGL.STATUS_PREPARE = 3
LWGL.STATUS_RUNNING = 4
LWGL.STATUS_ENDED = 5
LWGL.STATUS_CLOSED = 6

-----------------------------------------------------------------

LWGL.SIDE_HUMANS = 0
LWGL.SIDE_DRAGON = 1


LWGL.CASH_SPEND_TYPE_ACTIVITY_AURA = 11
LWGL.CASH_SPEND_TYPE_ACTIVITY_AUCTION = 12


-----------------------------------------------------------------

function LWGL:New(conf)
    local r = conf or {}
    setmetatable(r,self)
    self.__index = self
    
    -----------------------------------------------------------------
    -- 地图信息
    -----------------------------------------------------------------

    r.BaseMapId = 1007
    r.GameMapId = nil
    r.StageNode = nil
    r.StagePort = nil
    
    r.DragonType  = 1
    r.StepTimerId = nil
    r.Status = nil
    r.DragonHumanId = nil
    r.HumanContexts = {} -- key = id,value = table
    r.WinSide = nil
    r.Id = nil
    r.AllowAuras = { 4002, 4003, 4004 }

    return r
end

function LWGL:Start(ref,id)
    self.Id = id
    self.ScriptRef = ref
    self.Thread = GetServiceThread()
    self.Status = self.STATUS_AUCTION
    self.StepTimerId = self.Thread:CreateTimer(15,"OnAuctionEnded")
    
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_READY)
end

function LWGL:IsValidAura(auraid)
    for _,v in ipairs(self.AllowAuras) do
        if v == auraid then
            return true
        end
    end
    return false
end

function LWGL:Signup(id, activityId, gameMapId)

    pwdist.log('LWGL:Signup ' .. tostring(id))

    if self.HumanContexts[id] ~= nil then
        pwdist.return_values(-1)
        do return end
    end
    
    local ctx = 
    {
        AuctionGold = -1,
        OwnedAuras = {  }
    }
    
    self.HumanContexts[id] = ctx
    
    pwdist.return_values(0)
    
    pwdist.log('LWGL:Signup ' .. tostring(id) .. ' OK!')
end

function LWGL:CancelSignup(id, activityId, gameMapId)
    pwdist.log('LWGL:CancelSignup ' .. tostring(id) .. ' OK!')
    self.HumanContexts[id] = nil
end

function LWGL:Enter(id, activityId, gameMapId)
    pwdist.log('LWGL:Enter ' .. tostring(id))

    if self.Status ~= self.STATUS_TELEPORT and self.Status ~= self.STATUS_PREPARE then
        return
    end
    
    local ctx = self.HumanContexts[id]
    
    if ctx == nil then
        return
    end
    
    self.Thread:TeleportHuman(id,self.BaseMapId,self.GameMapId,0)
end

--------------------------------------------------------------------------

function LWGL:Call(func,...)
    pwdist.log('LWGL:Call ',...)
    local buf,_ = seripack(...)
    pwdist.prepare(self.StageNode,self.StagePort,self.GameMapId)
    pwdist.call(nil,pwngs_rpcnames.worldsrv.Stage.CallScript,func,buf)
end

--------------------------------------------------------------------------

function LWGL:OnAuctionEnded()

    pwdist.log('LWGL:OnAuctionEnded')
    
    local maxid = 0
    local maxgold = -10000
    
    local k,v = nil,nil
    repeat
        k,v = next(self.HumanContexts,k)
        
        if k ~= nil and v ~= nil then
            
            pwdist.log('OnAuctionEnded id=' .. tostring(k) .. ' gold = ' .. tostring(v.AuctionGold))
            
            if v.AuctionGold > maxgold then
                maxgold = v.AuctionGold
                maxid = k
            end
        end
    until k == nil
    
    pwdist.log('LWGL:OnAuctionEnded id=' .. tostring(maxid) .. ' gold=' .. tostring(maxgold))
    
    self.DragonHumanId = maxid
    self.DragonHumanName = self.Thread:GetHumanName(self.DragonHumanId)
    self.Status = self.STATUS_CREATE_STAGE
    self.StepTimerId = self.Thread:CreateTimer(10,"DoCreateStage")
    
    local bossmsg = 
    {
        id = self.DragonHumanId ,
        name = self.DragonHumanName
    }
    self.Thread:BroadcastMsg(msgids.SCActivityBoss,bossmsg)
end

function LWGL:DoCreateStage()
    pwdist.log('LWGL:DoCreateStage')
    
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.stagemgr,0)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.SImplStageMgr.CreateStage,STAGE_FLAG_ACTIVITY,self.BaseMapId,0,nil)
    pwdist.listen_result_ref("OnCreateStageResult",self.ScriptRef)
end

function LWGL:OnCreateStageResult(params,code,node,port,gamemap)
    
    pwdist.log('LWGL:OnCreateStageResult code=',tostring(code),gamemap)
    
    if code == nil then
        return
    end
    
    if code ~= 0 then
        self:Clean()
        return 
    end
    
    self.GameMapId = gamemap
    self.StageNode = node
    self.StagePort = port
   
    self.Status = self.STATUS_TELEPORT
    self.StepTimerId = self.Thread:CreateTimer(10,"DoTeleport") 
    
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_ENTER)
    
    -- 启动worldsrv端脚本
    pwdist.prepare(self.StageNode,self.StagePort,self.GameMapId)
    pwdist.call(nil,pwngs_rpcnames.worldsrv.Stage.ActivityStartup,self.Id)
    
    -- 初始化
    self:Call('_rpc_Initial',self.DragonHumanId,self.DragonHumanName,self.DragonType)
end

function LWGL:DoTeleport()
    pwdist.log('LWGL:DoTeleport')
    
    local k,v = nil,nil
    repeat
        k,v = next(self.HumanContexts,k)
        
        if k ~= nil and v ~= nil then
            self.Thread:TeleportHuman(k,self.BaseMapId,self.GameMapId,0)
        end
    until k == nil
    
    self.Status = self.STATUS_PREPARE
    self.StepTimerId = self.Thread:CreateTimer(10,"DoRunning") 
end

function LWGL:DoRunning()
    pwdist.log('LWGL:DoRunning')
    
    self.Status = self.STATUS_RUNNING
    self.StepTimerId = self.Thread:CreateTimer(15 * 60,"DoExpired") 
    
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_START)
end

function LWGL:DoExpired()

    pwdist.log('LWGL:DoExpired')
    
    if self.WinSide == nil then
        self.WinSide = self.SIDE_DRAGON
        self.StepTimerId = self.Thread:CreateTimer(10,"DoFinished") 
    end   
end

function LWGL:DoFinished()

    pwdist.log('LWGL:DoFinished')
    
	--C统一流程里已经调用
    --self.StepTimerId = self.Thread:CreateTimer(20,"Clean")  
    
    if self.WinSide ~= nil then
        self:Call('_rpc_AwardPrize',self.WinSide)
    end
   
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_END)
   
end

function LWGL:Clean()
    -- close stage
    pwdist.log('LWGL:Clean')
    
    -- 关闭worldsrv端脚本
    if self.GameMapId ~= nil then
        pwdist.prepare(self.StageNode,self.StagePort,self.GameMapId)
        pwdist.call(nil,pwngs_rpcnames.worldsrv.Stage.ActivityCleanup)
    end

    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_QUIT)
    
    self.Thread:CloseMe()
end

----------------------------------------------------------------------------
-- 与worldsrv的交互,rpc函数
----------------------------------------------------------------------------

function LWGL:_rpc_QueryHumanDragonId(id)
    local msg = 
    {
        id = self.DragonHumanId,
        name = self.DragonHumanName
    }
    
    self.Thread:SendMsg(id,msgids.SCActivityBoss,msg)
end

function LWGL:_rpc_DragonKilled()
    pwdist.log('LWGL:_rpc_DragonKilled')
    
    self.WinSide = self.SIDE_HUMANS
    self:DoFinished()
end

function LWGL:_rpc_Auction(id,gold)

    local ctx = self.HumanContexts[id]
    
    pwdist.log('LWGL:_rpc_Auction',id,gold)

    if ctx == nil then
        pwdist.log('LWGL:_rpc_Auction ' .. ' ctx = nil')
        return
    end
    
--[[
    if self.Status ~= self.STATUS_AUCTION then
        return
    end
--]]

    if ctx.AuctionGold ~= -1 then
        pwdist.log('LWGL:_rpc_Auction ' .. ' AuctionGold != -1',ctx.AuctionGold)
        return
    end
    
    ctx.AuctionGold = 0
    
    local node,port,stageid = self.Thread:GetHumanEndpoint(id)
    if node == nil or port == nil or stageid == nil then
        pwdist.log('LWGL:_rpc_Auction ',node,port,stageid)
        return
    end
    
    pwdist.prepare(node,port,stageid,id)
    pwdist.call(nil,pwngs_rpcnames.worldsrv.Human.Spend,gold,0,self.CASH_SPEND_TYPE_ACTIVITY_AUCTION,'LWGL:_rpc_Auction')
    pwdist.listen_result_ref('OnAuctionSpendResult',self.ScriptRef, { id,gold })
end

function LWGL:OnAuctionSpendResult(params,code)
    local id,gold = pwdist.unpack(params)
    
    pwdist.log('LWGL:OnAuctionSpendResult',id,gold,code)
    
    local ctx = self.HumanContexts[id]
    
    if ctx == nil then
        return
    end
    
    ctx.AuctionGold = -1
    
    if code ~= 0 then
        return
    end
    
    ctx.AuctionGold = gold
end


function LWGL:_rpc_BuyAura(id,buffid)
    
    pwdist.log('LWGL:_rpc_BuyAura',id,buffid)
    
    local ctx = self.HumanContexts[id]
    
    if ctx == nil then
        pwdist.log('LWGL:_rpc_BuyAura valid ctx=nil')
        return
    end
    
    if not self:IsValidAura(buffid) then
        pwdist.log('LWGL:_rpc_BuyAura valid = false')
        return
    end
    
    if ctx.OwnedAuras[buffid] == true then
        pwdist.log('LWGL:_rpc_BuyAura owned = true')
        return
    end
    
    local node,port,stageid = self.Thread:GetHumanEndpoint(id)
    if node == nil or port == nil or stageid == nil then
        pwdist.log('LWGL:_rpc_BuyAura ',node,port,stageid)
        return
    end
    
    pwdist.prepare(node,port,stageid,id)
    pwdist.call(nil,pwngs_rpcnames.worldsrv.Human.Spend,1,0,self.CASH_SPEND_TYPE_ACTIVITY_AURA,'LWGL:_rpc_BuyAura ' .. tostring(buffid))
    pwdist.listen_result_ref('OnAuraSpendResult',self.ScriptRef, { id,buffid })
end

function LWGL:OnAuraSpendResult(params,code)
    
    pwdist.log('LWGL:OnAuraSpendResult')
    
    local id,buffid = pwdist.unpack(params)
    
    if code == nil then
        return 
    end
    
    if code ~= 0 then
        return 
    end
    
    local ctx = self.HumanContexts[id]
    
    if ctx == nil then
        return
    end
    
    ctx.OwnedAuras[buffid] = true
    
    self:Call('_rpc_AwardAura',id,buffid)
end

--------------------------------------------------------------------------
-- 测试函数
--------------------------------------------------------------------------

function LWGL:TestSignup(id)
    self:Signup(tonumber(id))
end

function LWGL:TestAuction(strid,strgold)
    self:_rpc_Auction(tonumber(strid),tonumber(strgold))
end

function LWGL:TestAura(strid,strbuffid)
    pwdist.log('LWGL:TestAura')
    self:_rpc_BuyAura(tonumber(strid),tonumber(strbuffid))
end