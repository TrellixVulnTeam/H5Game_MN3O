----------------------------------------------------------
-- AI脚本框架
----------------------------------------------------------

require "./Lua/worldsrv/ai/pw_ai_def"

g_ai_tables = {}

-- *****************************************************************

g_ai_context = {}

function g_ai_context:new(o)
	o = o or {}
	setmetatable(o,self)
	self.__index = self
	return o
end

-- AI sleep一段时间
-- param(_time): sleep的时间（单位MS）
function g_ai_context:AISleep(_time)
	_AISleep(self.ownerPtr,_time)
end

function g_ai_context:AIBrainPaused()
	return _AIBrainPaused(self.ownerPtr)
end

-- 向附近频道说话
-- param(text): 说话的内容
function g_ai_context:AISay(text)
	_AISay(self.ownerPtr,text)
end

-- 测试当前状态的执行流程是否被打断
-- 被打断时，当前状态执行流程需立即结束
function g_ai_context:AITestJump()
	return self.aiJump
end

-- 切换状态
-- param(state): 切换到的状态
function g_ai_context:AISwitchTo(state)
    if self.aiState == state then
        return
    end
    
    local oldState = self.aiState
	self.aiState = state
    ai_exec_event(self.ownerId,"OnStateChanged",oldState,state)
end

-- 中断当前状态执行流程
function g_ai_context:AIJumpToMain()
	self.aiJump = true
end

-- 打断正在执行的异步操作，中断当前状态执行流程
function g_ai_context:AIJumpToMainEvt()
	self.aiJump = true
	_AICleanupAsyncOper(self.ownerPtr,g_ai_code.EventBreaked,0)
end

-- AI退出
function g_ai_context:AIExit()
	self.aiJump = true
	self.aiExit = true
end

-- 追击
-- param(chaseType): 追击类型，追击到后是恐吓还是攻击
-- param(skillID): 技能ID，追击该技能的施法范围
function g_ai_context:AIChase(chaseType,...)
	return _AIChase(self.ownerPtr,chaseType,...)
end

-- 是否是恐吓怪
function g_ai_context:AIHasThreaten()
	return _AIHasThreaten(self.ownerPtr)
end

-- 恐吓
function g_ai_context:AIThreaten()
	_AIThreaten(self.ownerPtr)
end

-- 开始行动超时计时器
function g_ai_context:AIStartAction()
	_AIStartAction(self.ownerPtr)
end

-- 结束行动超时计时器
function g_ai_context:AIStopAction()
	_AIStopAction(self.ownerPtr)
end

-- 开始行动间隔超时计时器
function g_ai_context:AIStartActionInter(timerType)
	_AIStartActionInter(self.ownerPtr,timerType)
end

-- 结束行动超时计时器
function g_ai_context:AIStopActionInter()
	_AIStopActionInter(self.ownerPtr)
end

-- 返回领地
function g_ai_context:AIBack()
	return _AIBack(self.ownerPtr)
end

-- 随机本次行动间隔中是否有扰敌
function g_ai_context:AIRandomDisrupt()
	return _AIRandomDisrupt(self.ownerPtr)
end

-- 获取当前扰敌的中心点
function g_ai_context:AIGetDisruptPoint()
	return _AIGetDisruptPoint(self.ownerPtr)
end

-- 获取当前扰敌的移动速度
function g_ai_context:AIGetDisruptSpeed()
	return _AIGetDisruptSpeed(self.ownerPtr)
end

-- 扰敌
function g_ai_context:AIDisrupt()
	return _AIDisrupt(self.ownerPtr)
end

-- 选择条件技能列表
function g_ai_context:AISelectConditionSkill()
	return _AISelectConditionSkill(self.ownerPtr)
end

-- 选择默认技能
function g_ai_context:AISelectDefaultSkill()
	return _AISelectDefaultSkill(self.ownerPtr)
end

-- 获取本次行动下一个条件技能
function g_ai_context:AIGetConditionSkill()
	return _AIGetConditionSkill(self.ownerPtr)
end

-- 使用技能
-- param(skillID): 技能ID
function g_ai_context:AIUseSkill(skillID)
	return _AIUseSkill(self.ownerPtr, skillID)
end

-- 移动到指定点
-- param(posx): 指定点x坐标
-- param(posy): 指定点y坐标
-- param(posz): 指定点z坐标
function g_ai_context:AIMoveToPoint(pos,speed)
	return _AIMoveToPoint(self.ownerPtr,pos,speed)
end

-- 销毁自身
function g_ai_context:AIDestroySelf()
	_AIDestroySelf(self.ownerPtr)
	self:AIExit()
end

-- 重叠检测，判断是否和正在攻击相同目标其他怪重叠
function g_ai_context:AIIsOverlap(fAnticollDist)
	return _AIIsOverlap(self.ownerPtr,fAnticollDist)
end

-- 随机偏移，随机移动到目标周围的一个点
-- param(radius): 偏移半径
function g_ai_context:AIMoveToTarget(radius)
	return _AIMoveToTarget(self.ownerPtr, radius)
end

-- 跟随主人
-- param(fDistMin): 跟随的最小距离
-- param(fDistMax): 跟随的最大距离
function g_ai_context:AIFollow(fDistMin, fDistMax)
	return _AIFollow(self.ownerPtr, fDistMin, fDistMax)
end

-- 改变当前攻击目标
-- param(enemyID): 目标ID
function g_ai_context:AIChangeTarget(enemyID)
	_AIChangeTarget(self.ownerPtr, enemyID)
end

-- 检查自身血量
-- param(hpMin): 血量下限
-- param(hpMax): 血量上限
function g_ai_context:AICheckSelfHP(hpMin,hpMax)
	return _AICheckSelfHP(self.ownerPtr,hpMin,hpMax)
end

-- 检查是否处于沉默状态
function g_ai_context:AIIsInSilent()
    return _AIIsInSilent(self.ownerPtr)
end

-- 获取技能的最大施法距离
function g_ai_context:AIGetMagicMaxCastDist(magicId)
    return _AIGetMagicMaxCastDist(self.ownerPtr,magicId)
end

-- 释放条件技能前说话
function g_ai_context:AITalkWhenUseConditionSkill()
    return _AITalkWhenUseConditionSkill(self.ownerPtr)
end

-- 获取Owner(返回SmartUnit*)
function g_ai_context:AIGetOwner()
    return _AIGetOwner(self.ownerPtr)
end

-- 守尸
function g_ai_context:AIGuardingCorpse(targetId)
    return _AIGuardingCorpse(self.ownerPtr,targetId)
end

-- 离开守尸
function g_ai_context:AIGuardingCorpseEnd(targetId)
    return _AIGuardingCorpseEnd(self.ownerPtr,targetId)
end

-- 本场景是否可买活
function g_ai_context:AIIsAllowPayRealive()
    return _AIIsAllowPayRealive(self.ownerPtr)
end

-- 锁定当前目标(除非当前目标失效，否则不切换目标)
function g_ai_context:AILockTarget()
    return _AILockTarget(self.ownerPtr)
end

-- 解锁当前目标(默认机制，按距离选目标)
function g_ai_context:AIUnlockTarget()
    return _AIUnlockTarget(self.ownerPtr)
end

-- *****************************************************************

function ai_make_env(id,ptr,cls)
	local init = 
	{
			ownerId = id,
			ownerPtr = ptr,
			--aiClass = _G[cls],
			aiClass = g_ai[cls],
			aiThread = coroutine.create(ai_wrapper),
			aiJump = false,
			aiExit = false,
			aiState = "idle",
			aiExited = false,
            guardCorpse = 0,
	}
	
	local context = g_ai_context:new(init)
	
	-- print("cls:" .. tostring(cls) .. ",aiClass:" .. tostring(context.aiClass))
	if context.aiClass == nil then
		context.aiThread = nil
		return nil
	end
	
	g_ai_tables[id] = context
	
	return context.aiThread
end

function ai_startup(id)
	local context = g_ai_tables[id]
	if context ~= nil then
		coroutine.resume(context.aiThread,context)
	end
end

function ai_cleanup(id)
	local context = g_ai_tables[id]
	if context ~= nil then
		if not context.aiExited then
			context.aiExit = true
			context.aiJump = true
			coroutine.resume(context.aiThread,-1,-1)
		end
		g_ai_tables[id] = nil
	end
end

function ai_wrapper(context)
	-- print("ai_wrapper start")	
	while not context.aiExit do
		-- print("id:" .. tostring(context.ownerId) .. ",state:" ..  tostring(context.aiState))
		local aiOperations = context.aiClass.state[context.aiState]
		
		if context:AIBrainPaused() then
			context:AISleep(100)
		elseif aiOperations ~= nil then
			aiOperations(context.aiClass.state,context)
		else
			break
		end
		
		context.aiJump = false
	end
	-- print("ai_wrapper end")
	context.aiExited = true
end

function ai_exec_event(id,name,...)
	local context = g_ai_tables[id]
	if context == nil then
		return 
	end
	
	-- print("id:" .. tostring(context.ownerId) .. ",event:" .. tostring(name))
	local aiOperations = context.aiClass.event[name]
	if aiOperations ~= nil then
		aiOperations(context.aiClass.event,context,...)
	end
end
