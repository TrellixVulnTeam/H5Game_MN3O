----------------------------------------------------------
-- AI实现：通用战斗AI
----------------------------------------------------------

require "./Lua/worldsrv/ai/pw_ai_def"

g_ai_class_combat = {}
g_ai_class_combat_evt = {}
g_ai_class_combat_fsm = {}

-- ******************************************************
g_ai_class_combat.event = g_ai_class_combat_evt
g_ai_class_combat.state = g_ai_class_combat_fsm

-- ******************************************************
-- ai事件
-- ******************************************************
-- 被杀死
-- 切换到死亡状态
function g_ai_class_combat_evt:OnDead(context)
	context:AISwitchTo("killed")
	context:AIJumpToMainEvt()
end

-- 仇恨列表第一次增加
-- 若恐吓开启进入恐吓状态，否则进入攻击状态
function g_ai_class_combat_evt:OnThreatFirstAdd(context,firstID)
	-- 恐吓开，进入恐吓状态，否则进入攻击状态
	if context:AIHasThreaten() == true then
		context:AISwitchTo("threaten")
	else
		context:AISwitchTo("attack")
	end
	context:AIJumpToMainEvt()
end

-- 追击超时
-- 切换到返回领地状态
function g_ai_class_combat_evt:OnChaseTimeout(context)
	context:AISwitchTo("back")
	context:AIJumpToMainEvt()
end

-- 超出领地范围
-- 切换到返回领地状态
function g_ai_class_combat_evt:OnExceedTerritory(context)
	context:AISwitchTo("back")
	context:AIJumpToMainEvt()
end

-- 目标改变
function g_ai_class_combat_evt:OnTargetChanged(context,oldTargetID,newTargetID)
	--[[if oldTargetID ~= toll(0) and newTargetID ~= toll(0) then
	    context:AIJumpToMainEvt()
    end--]]
end

-- 施放技能超时
-- 重新选技能
function g_ai_class_combat_evt:OnActionTimeout(context)
	-- 判断是进入扰敌还是进入技能选择CD
	local needDisrupt = context:AIRandomDisrupt()
	if needDisrupt == true then
		context:AISwitchTo("disrupt")
	else
		context:AISwitchTo("attackcd")
	end
	context:AIJumpToMainEvt()
end

-- 行动间隔超时
-- 切换到攻击状态
function g_ai_class_combat_evt:OnActionInterTimeout(context)
	context:AISwitchTo("attack")
	context:AIJumpToMainEvt()
end

-- 敌人列表空
-- 切换到返回领地状态
function g_ai_class_combat_evt:OnThreatEmpty(context,lastID)
    if context.aiState == "back" then
        return
    end

    -- 如最后的攻击玩家死亡，则进入守尸状态，否则进入返回领地状态
    local lastHuman = GetCurrentStage():GetModObjs():GetHuman(lastID)
    if context:AIIsAllowPayRealive() and lastHuman ~= nil and lastHuman:IsDead() then
        context.guardCorpse = lastID
        context:AISwitchTo("guarding_corpse")
    else
        context:AISwitchTo("back")
    end

	context:AIJumpToMainEvt()
end

-- 受到攻击
-- 打断恐吓
function g_ai_class_combat_evt:OnMagicHit(context,enemyID,magicID)
    if context.aiState == "back" then
        return
    end

	if context.aiState == "threaten" then
		context:AISwitchTo("attack")
		context:AIJumpToMainEvt()
	end
end

-- 打断守尸
function g_ai_class_combat_evt:OnBreakCorpseGuarding(context,back)
    if context.aiState ~= "guarding_corpse" then
        return
    end
    
    if back then
        context:AISwitchTo("back")
    else
        context:AISwitchTo("idle")
    end
    
    context:AIJumpToMainEvt()
end

-- 状态改变
function g_ai_class_combat_evt:OnStateChanged(context,oldState,newState)
    -- 离开守尸状态，清除守尸目标
    if oldState == "guarding_corpse" then
        context:AIGuardingCorpseEnd(context.guardCorpse)
        context.guardCorpse = 0
    end
end

-- ******************************************************
-- 内部函数
-- ******************************************************
-- 追击到后使用技能
function g_ai_class_combat:chaseAndUseSkill(context,skillID)
	local code,data = context:AIChase(g_ai_const.AI_CONST_CHASE_TYPE_ATTACK,skillID)
	if context:AITestJump() == true then
		return code,data
	end
	
	-- 追击失败或者被打断，返回
	if code ~= g_ai_code.Successful then
		return code,data
	end
    
    local fOverlapOffest = context:AIGetMagicMaxCastDist(skillID)
    if fOverlapOffest <= 0 then
        fOverlapOffest = 1.5
    else
        fOverlapOffest = math.min(fOverlapOffest,1.5)
    end
	
	-- 追击到达后，检测是否重叠
	local nCount = 2
	while nCount > 0 do
		if context:AIIsOverlap(0.5) == true then
			code,data = context:AIMoveToTarget(fOverlapOffest)
			if context:AITestJump() == true then
				return code,data
			end
			
			-- 移动失败，防重叠检查立即结束，开始释放技能
			if code ~= g_ai_code.Successful then
				break
			end
		else
			break
		end
		nCount = nCount - 1
	end
	
	-- 施放技能
	return context:AIUseSkill(skillID)
end

-- ******************************************************
-- ai状态机
-- ******************************************************
-- 空闲状态
function g_ai_class_combat_fsm:idle(context)
	context:AISleep(3000)
end

-- 死亡状态
function g_ai_class_combat_fsm:killed(context)
	context:AIExit()
end

-- 恐吓状态
function g_ai_class_combat_fsm:threaten(context)
	local code, data = context:AIChase(g_ai_const.AI_CONST_CHASE_TYPE_THREATEN)
	if context:AITestJump() == true then
		return
	end
	
	-- 追击到恐吓范围，开始恐吓
	if code == g_ai_code.Successful or code == g_ai_code.MotionCleanup then
		context:AIThreaten()
		if context:AITestJump() == true then
			return
		end
		
		-- 恐吓完成，切换到攻击状态
		context:AISwitchTo("attack")
	else
		-- 追击失败，返回领地
		context:AISwitchTo("back")
	end
end

-- 攻击状态
function g_ai_class_combat_fsm:attack(context)
	-- 启动行动超时计时器
	context:AIStartAction()
	
	-- 处于沉默状态时，停止技能选择
    if context:AIIsInSilent() then
        context:AIStopAction()
        context:AISleep(300)
        return
    end
    
	local code, data
	local bNeedUseDefault = true
	
	if context:AISelectConditionSkill() then
        -- 施放条件技能时锁定目标，施放结束时需解锁目标
        context:AILockTarget()
		local cndSkillID = context:AIGetConditionSkill()
		-- 第一个条件技能选择成功
		if cndSkillID > 0 then
            context:AITalkWhenUseConditionSkill()
			code,data = g_ai_class_combat:chaseAndUseSkill(context,cndSkillID)
			if context:AITestJump() == true then
				context:AIStopAction()
                context:AIUnlockTarget()
				return
			end
			
			-- 追击被打断，冷却一段时间，重新选择技能
			if code == g_ai_code.MotionCleanup then
				context:AIStopAction()
				context:AISleep(g_ai_const.AI_CONST_CHASE_COOLDOWN)
                context:AIUnlockTarget()
				return
			end
			
			-- 追击失败，错误码：目的不可达，返回领地
			if code == g_ai_code.MotionUnreachable or code == g_ai_code.TargetInvalid then
				-- print(tostring(context.ownerId) .. ":chase fail,code:" .. tostring(code) .. ", data:" .. tostring(data))
				context:AIStopAction()
				context:AISwitchTo("back")
                context:AIUnlockTarget()
				return
			end
			
			-- 第一个条件技能释放成功，依次施放后面的条件技能
			if code == g_ai_code.Successful then
				bNeedUseDefault = false		--	默认技能不再施放
				cndSkillID = context:AIGetConditionSkill()
				while cndSkillID > 0 do
					code,data = g_ai_class_combat:chaseAndUseSkill(context,cndSkillID)
					if context:AITestJump() == true then
						context:AIStopAction()
                        context:AIUnlockTarget()
						return
					end
					
					-- 追击失败，错误码：目的不可达，返回领地
					if code == g_ai_code.MotionUnreachable or code == g_ai_code.TargetInvalid then
						-- print(tostring(context.ownerId) .. ":chase fail,code:" .. tostring(code) .. ", data:" .. tostring(data))
						context:AIStopAction()
						context:AISwitchTo("back")
                        context:AIUnlockTarget()
						return
					end
					
					if code ~= g_ai_code.Successful then
						break
					end
					
					cndSkillID = context:AIGetConditionSkill()
				end
			end
		end
        context:AIUnlockTarget()
	end
	
	-- 需要施放默认技能
	if bNeedUseDefault == true then
		local defSkillID = context:AISelectDefaultSkill()
		
		code,data = g_ai_class_combat:chaseAndUseSkill(context,defSkillID)
		if context:AITestJump() == true then
			context:AIStopAction()
			return
		end
		
		-- 追击被打断，冷却一段时间，重新选择技能
		if code == g_ai_code.MotionCleanup then
			context:AIStopAction()
			context:AISleep(g_ai_const.AI_CONST_CHASE_COOLDOWN)
			return
		end
		
		-- 追击失败，错误码：目的不可达，返回领地
		if code == g_ai_code.MotionUnreachable or code == g_ai_code.TargetInvalid then
			-- print(tostring(context.ownerId) .. ":chase fail,code:" .. tostring(code) .. ", data:" .. tostring(data))
			context:AIStopAction()
			context:AISwitchTo("back")
			return
		end
		
		-- 默认技能释放失败，直接进入技能选择CD
		if code ~= g_ai_code.Successful then
			context:AIStopAction()
			context:AISwitchTo("attackcd")
			return
		end
	end
	
	context:AIStopAction()
	-- 判断是进入扰敌还是进入技能选择CD
	local needDisrupt = context:AIRandomDisrupt()
	if needDisrupt == true then
		context:AISwitchTo("disrupt")
	else
		context:AISwitchTo("attackcd")
	end
end

-- 攻击CD
function g_ai_class_combat_fsm:attackcd(context)
	-- 开始攻击CD计时器
	context:AIStartActionInter(g_ai_const.AI_CONST_TIMER_TYPE_ATTACK_CD)
	
	-- 追击到表中指定距离
	while true do
		context:AIChase(g_ai_const.AI_CONST_CHASE_TYPE_ATTACK_CD)
		if context:AITestJump() == true then
			break
		end
		context:AISleep(g_ai_const.AI_CONST_CHASE_COOLDOWN)
		if context:AITestJump() == true then
			break
		end
	end
	
	context:AIStopActionInter()
end

-- 扰敌状态
function g_ai_class_combat_fsm:disrupt(context)
	--	开始扰敌计时器
	context:AIStartActionInter(g_ai_const.AI_CONST_TIMER_TYPE_DISRUPT)
	
	local point = context:AIGetDisruptPoint()
    local speed = context:AIGetDisruptSpeed()
	context:AIMoveToPoint(point,speed)
	if context:AITestJump() == true then
		context:AIStopActionInter()
		return
	end
	context:AIDisrupt()
	if context:AITestJump() == true then
		context:AIStopActionInter()
		return
	end
	
	context:AIStopActionInter()
	context:AISwitchTo("attack")
end

-- 返回领地状态
function g_ai_class_combat_fsm:back(context)
	context:AIBack()
	
	if context:AITestJump() == true then
		return
	end
	
	context:AISwitchTo("idle")
end

-- 守尸状态
function g_ai_class_combat_fsm:guarding_corpse(context)
    local code,data = context:AIGuardingCorpse(context.guardCorpse)
    
    if context:AITestJump() == true then
        return
    end
    
    context:AISwitchTo("back")
end
