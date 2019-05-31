-----------------------------------------------------------------
-- 活动:世界boss
-- 控制服务器端
-----------------------------------------------------------------

local WorldBoss = {}

-----------------------------------------------------------------

SImplActivitiesClasses[4] = WorldBoss
SImplActivitiesClasses[5] = WorldBoss
SImplActivitiesClasses[6] = WorldBoss

WorldBoss.STATUS_BEGAN = 1
WorldBoss.STATUS_CREATE_STAGE = 2
WorldBoss.STATUS_RUNNING = 3
WorldBoss.STATUS_ENDED = 4
WorldBoss.STATUS_CLOSED = 5
WorldBoss.BASEMAP = 9002
WorldBoss.GAMETIME = 20*60
--WorldBoss.GAMETIME = 60

function WorldBoss:New(conf)
	local r = conf or {}
    setmetatable(r,self)
    self.__index = self
	
	-----------------------------------------------------------------
    -- 地图信息
    -----------------------------------------------------------------
	r.Id = nil --活动ID
	r.Status = nil
    r.StageId = 0
    r.StageNode = ''
    r.StagePort = ''
    r.KillerId = 0
    r.Ranks = {}
	return r
end


function WorldBoss:Start(ref,id)
    self.Id = id
    self.ScriptRef = ref
    self.Thread = GetServiceThread()
    self.Status = self.STATUS_BEGAN
    self.StepTimerId = self.Thread:CreateTimer(1,"DoCreateStage")
	--self.Thread:CreateTimerEx(1,1, "UpdateStageHumanNum") -- 更新每个地图的玩家数量给worldsrv的stage对象
    self.Finished = false
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_READY)
	self.StartTime = os.time()
    self.FinishTime = 0
end

function WorldBoss:DoCreateStage()
    pwdist.log('WorldBoss:DoCreateStage')

	pwdist.prepare(pwngs_rpcnodes.ctrlsrv, pwngs_rpcports.ctrlsrv.stagemgr, 0)
	pwdist.call(nil, pwngs_rpcnames.ctrlsrv.SImplStageMgr.CreateStage, STAGE_FLAG_ACTIVITY, self.BASEMAP, 0, nil)
	pwdist.listen_result_ref("OnCreateStageResult", self.ScriptRef, {v,i})
	
	self.Status = self.STATUS_CREATE_STAGE
end

--生成一个默认副本，当玩家查询时发现已满再创建新副本

function WorldBoss:OnCreateStageResult(params, code, node, port, gamemap)

    pwdist.log('WorldBoss:OnCreateStageResult code=',tostring(code),tostring(gamemap), tostring(type(gamemap)))

    if code == nil then
        return
    end
	
    if code ~= 0 then
        self:Clean()
        return
    end
    
    self.StageId = gamemap
    self.StageNode = node
    self.StagePort = port
	
    -- 启动worldsrv端脚本
    pwdist.prepare(node , port, gamemap)
    pwdist.call(nil, pwngs_rpcnames.worldsrv.Stage.ActivityStartup, self.Id)

    local aobj = self.Thread:GetBoss(self.Id)

    -- 初始化
    self:Call('_rpc_Initial', self.Id,aobj:GetMonsterLevel(),aobj:GetSubstitutes())

    self.StepTimerId = self.Thread:CreateTimer(1,"DoRunning")
end


function WorldBoss:DoRunning()
    pwdist.log('WorldBoss:DoRunning')

    self.Status = self.STATUS_RUNNING
    self.StepTimerId = self.Thread:CreateTimer(WorldBoss.GAMETIME,"DoExpired")
	
	--self:TimeHint()
	
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_START)
    self.Thread:BroadcastActivityStart(self.Id)
    self.StartTime = os.time()
end

-- 时间到了,结束
function WorldBoss:DoExpired()
    if not self.Finished then
        self.Finished = true
        self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_END)
        self.StepTimerId = self.Thread:CreateTimer(180, "DoClose")
        self:Call('_rpc_Expired')
    end
end

-- 击杀完成,结束
function WorldBoss:DoFinished()
	--C统一流程里调用了
    --self.StepTimerId = self.Thread:CreateTimer(20,"Clean")
	
    self.FinishTime = os.time()

    if not self.Finished then
        self.Finished = true
        self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_END)
	    self.StepTimerId = self.Thread:CreateTimer(180, "DoClose")
    end

    local aobj = self.Thread:GetBoss(self.Id)
    aobj:DoFinished(self.KillerId,self.Ranks,self.FinishTime - self.StartTime)

    self:Call("_rpc_Settlement",self.FinishTime - self.StartTime,aobj:GetMonsterLevel())
end

function WorldBoss:DoClose()
    pwdist.log('WorldBoss:DoClose')
    self:Call('_rpc_KickAll')
    self.StepTimerId = self.Thread:CreateTimer(30, "DoClean")
end

function WorldBoss:DoClean()
	self.Thread:CloseMe()
end

function WorldBoss:Clean()
    -- close stage
    pwdist.log('WorldBoss:Clean')

    -- 关闭worldsrv端脚本
	pwdist.prepare(self.StageNode, self.StagePort, toll(self.StageId))
	pwdist.call(nil,pwngs_rpcnames.worldsrv.Stage.ActivityCleanup)
	
	self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_QUIT)
	
	self.Id = nil --活动ID
	self.Status = nil
end

--------------------------------------------------------------------------

function WorldBoss:Call(func, ...)
    --pwdist.log('WorldBoss:Call ' .. tostring(func))
    local buf,_ = seripack(...)
    pwdist.prepare(self.StageNode, self.StagePort, toll(self.StageId))
    pwdist.call(nil,pwngs_rpcnames.worldsrv.Stage.CallScript,func,buf)
end

function WorldBoss:Signup(id, activityId, basemap) -- 登陆到副本中
	if self.Finished then
		--pwdist.log('DTS::Signup finished',tostring(id))
        pwdist.return_values(51151)
		return
	end

    pwdist.log('DTS:Signup ' .. tostring(id) .. 'activity:' .. tostring(activityId) .. 'basemap:' .. tostring(basemap) .. tostring(type(basemap)))
			
    pwdist.return_values(0)
			
	--进入副本
	self.Thread:TeleportHuman(id, toll(self.BASEMAP), toll(self.StageId), 0 )
end

function WorldBoss:_rpc_CtrlsrvBossKilled(killerid,ranks)
    self.KillerId = killerid
    self.Ranks = ranks

    self:DoFinished(self.KillerId,self.Ranks)
end

function WorldBoss:_rpc_CtrlsrvExpired(ranks)
    self.KillerId = 0
    self.Ranks = ranks

    self:DoFinished(self.KillerId,self.Ranks)
end