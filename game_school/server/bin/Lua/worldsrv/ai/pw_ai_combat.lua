----------------------------------------------------------
-- AIʵ�֣�ͨ��ս��AI
----------------------------------------------------------

require "./Lua/worldsrv/ai/pw_ai_def"

g_ai_class_combat = {}
g_ai_class_combat_evt = {}
g_ai_class_combat_fsm = {}

-- ******************************************************
g_ai_class_combat.event = g_ai_class_combat_evt
g_ai_class_combat.state = g_ai_class_combat_fsm

-- ******************************************************
-- ai�¼�
-- ******************************************************
-- ��ɱ��
-- �л�������״̬
function g_ai_class_combat_evt:OnDead(context)
	context:AISwitchTo("killed")
	context:AIJumpToMainEvt()
end

-- ����б��һ������
-- �����ſ����������״̬��������빥��״̬
function g_ai_class_combat_evt:OnThreatFirstAdd(context,firstID)
	-- ���ſ����������״̬��������빥��״̬
	if context:AIHasThreaten() == true then
		context:AISwitchTo("threaten")
	else
		context:AISwitchTo("attack")
	end
	context:AIJumpToMainEvt()
end

-- ׷����ʱ
-- �л����������״̬
function g_ai_class_combat_evt:OnChaseTimeout(context)
	context:AISwitchTo("back")
	context:AIJumpToMainEvt()
end

-- ������ط�Χ
-- �л����������״̬
function g_ai_class_combat_evt:OnExceedTerritory(context)
	context:AISwitchTo("back")
	context:AIJumpToMainEvt()
end

-- Ŀ��ı�
function g_ai_class_combat_evt:OnTargetChanged(context,oldTargetID,newTargetID)
	--[[if oldTargetID ~= toll(0) and newTargetID ~= toll(0) then
	    context:AIJumpToMainEvt()
    end--]]
end

-- ʩ�ż��ܳ�ʱ
-- ����ѡ����
function g_ai_class_combat_evt:OnActionTimeout(context)
	-- �ж��ǽ����ŵл��ǽ��뼼��ѡ��CD
	local needDisrupt = context:AIRandomDisrupt()
	if needDisrupt == true then
		context:AISwitchTo("disrupt")
	else
		context:AISwitchTo("attackcd")
	end
	context:AIJumpToMainEvt()
end

-- �ж������ʱ
-- �л�������״̬
function g_ai_class_combat_evt:OnActionInterTimeout(context)
	context:AISwitchTo("attack")
	context:AIJumpToMainEvt()
end

-- �����б��
-- �л����������״̬
function g_ai_class_combat_evt:OnThreatEmpty(context,lastID)
    if context.aiState == "back" then
        return
    end

    -- �����Ĺ�������������������ʬ״̬��������뷵�����״̬
    local lastHuman = GetCurrentStage():GetModObjs():GetHuman(lastID)
    if context:AIIsAllowPayRealive() and lastHuman ~= nil and lastHuman:IsDead() then
        context.guardCorpse = lastID
        context:AISwitchTo("guarding_corpse")
    else
        context:AISwitchTo("back")
    end

	context:AIJumpToMainEvt()
end

-- �ܵ�����
-- ��Ͽ���
function g_ai_class_combat_evt:OnMagicHit(context,enemyID,magicID)
    if context.aiState == "back" then
        return
    end

	if context.aiState == "threaten" then
		context:AISwitchTo("attack")
		context:AIJumpToMainEvt()
	end
end

-- �����ʬ
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

-- ״̬�ı�
function g_ai_class_combat_evt:OnStateChanged(context,oldState,newState)
    -- �뿪��ʬ״̬�������ʬĿ��
    if oldState == "guarding_corpse" then
        context:AIGuardingCorpseEnd(context.guardCorpse)
        context.guardCorpse = 0
    end
end

-- ******************************************************
-- �ڲ�����
-- ******************************************************
-- ׷������ʹ�ü���
function g_ai_class_combat:chaseAndUseSkill(context,skillID)
	local code,data = context:AIChase(g_ai_const.AI_CONST_CHASE_TYPE_ATTACK,skillID)
	if context:AITestJump() == true then
		return code,data
	end
	
	-- ׷��ʧ�ܻ��߱���ϣ�����
	if code ~= g_ai_code.Successful then
		return code,data
	end
    
    local fOverlapOffest = context:AIGetMagicMaxCastDist(skillID)
    if fOverlapOffest <= 0 then
        fOverlapOffest = 1.5
    else
        fOverlapOffest = math.min(fOverlapOffest,1.5)
    end
	
	-- ׷������󣬼���Ƿ��ص�
	local nCount = 2
	while nCount > 0 do
		if context:AIIsOverlap(0.5) == true then
			code,data = context:AIMoveToTarget(fOverlapOffest)
			if context:AITestJump() == true then
				return code,data
			end
			
			-- �ƶ�ʧ�ܣ����ص����������������ʼ�ͷż���
			if code ~= g_ai_code.Successful then
				break
			end
		else
			break
		end
		nCount = nCount - 1
	end
	
	-- ʩ�ż���
	return context:AIUseSkill(skillID)
end

-- ******************************************************
-- ai״̬��
-- ******************************************************
-- ����״̬
function g_ai_class_combat_fsm:idle(context)
	context:AISleep(3000)
end

-- ����״̬
function g_ai_class_combat_fsm:killed(context)
	context:AIExit()
end

-- ����״̬
function g_ai_class_combat_fsm:threaten(context)
	local code, data = context:AIChase(g_ai_const.AI_CONST_CHASE_TYPE_THREATEN)
	if context:AITestJump() == true then
		return
	end
	
	-- ׷�������ŷ�Χ����ʼ����
	if code == g_ai_code.Successful or code == g_ai_code.MotionCleanup then
		context:AIThreaten()
		if context:AITestJump() == true then
			return
		end
		
		-- ������ɣ��л�������״̬
		context:AISwitchTo("attack")
	else
		-- ׷��ʧ�ܣ��������
		context:AISwitchTo("back")
	end
end

-- ����״̬
function g_ai_class_combat_fsm:attack(context)
	-- �����ж���ʱ��ʱ��
	context:AIStartAction()
	
	-- ���ڳ�Ĭ״̬ʱ��ֹͣ����ѡ��
    if context:AIIsInSilent() then
        context:AIStopAction()
        context:AISleep(300)
        return
    end
    
	local code, data
	local bNeedUseDefault = true
	
	if context:AISelectConditionSkill() then
        -- ʩ����������ʱ����Ŀ�꣬ʩ�Ž���ʱ�����Ŀ��
        context:AILockTarget()
		local cndSkillID = context:AIGetConditionSkill()
		-- ��һ����������ѡ��ɹ�
		if cndSkillID > 0 then
            context:AITalkWhenUseConditionSkill()
			code,data = g_ai_class_combat:chaseAndUseSkill(context,cndSkillID)
			if context:AITestJump() == true then
				context:AIStopAction()
                context:AIUnlockTarget()
				return
			end
			
			-- ׷������ϣ���ȴһ��ʱ�䣬����ѡ����
			if code == g_ai_code.MotionCleanup then
				context:AIStopAction()
				context:AISleep(g_ai_const.AI_CONST_CHASE_COOLDOWN)
                context:AIUnlockTarget()
				return
			end
			
			-- ׷��ʧ�ܣ������룺Ŀ�Ĳ��ɴ�������
			if code == g_ai_code.MotionUnreachable or code == g_ai_code.TargetInvalid then
				-- print(tostring(context.ownerId) .. ":chase fail,code:" .. tostring(code) .. ", data:" .. tostring(data))
				context:AIStopAction()
				context:AISwitchTo("back")
                context:AIUnlockTarget()
				return
			end
			
			-- ��һ�����������ͷųɹ�������ʩ�ź������������
			if code == g_ai_code.Successful then
				bNeedUseDefault = false		--	Ĭ�ϼ��ܲ���ʩ��
				cndSkillID = context:AIGetConditionSkill()
				while cndSkillID > 0 do
					code,data = g_ai_class_combat:chaseAndUseSkill(context,cndSkillID)
					if context:AITestJump() == true then
						context:AIStopAction()
                        context:AIUnlockTarget()
						return
					end
					
					-- ׷��ʧ�ܣ������룺Ŀ�Ĳ��ɴ�������
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
	
	-- ��Ҫʩ��Ĭ�ϼ���
	if bNeedUseDefault == true then
		local defSkillID = context:AISelectDefaultSkill()
		
		code,data = g_ai_class_combat:chaseAndUseSkill(context,defSkillID)
		if context:AITestJump() == true then
			context:AIStopAction()
			return
		end
		
		-- ׷������ϣ���ȴһ��ʱ�䣬����ѡ����
		if code == g_ai_code.MotionCleanup then
			context:AIStopAction()
			context:AISleep(g_ai_const.AI_CONST_CHASE_COOLDOWN)
			return
		end
		
		-- ׷��ʧ�ܣ������룺Ŀ�Ĳ��ɴ�������
		if code == g_ai_code.MotionUnreachable or code == g_ai_code.TargetInvalid then
			-- print(tostring(context.ownerId) .. ":chase fail,code:" .. tostring(code) .. ", data:" .. tostring(data))
			context:AIStopAction()
			context:AISwitchTo("back")
			return
		end
		
		-- Ĭ�ϼ����ͷ�ʧ�ܣ�ֱ�ӽ��뼼��ѡ��CD
		if code ~= g_ai_code.Successful then
			context:AIStopAction()
			context:AISwitchTo("attackcd")
			return
		end
	end
	
	context:AIStopAction()
	-- �ж��ǽ����ŵл��ǽ��뼼��ѡ��CD
	local needDisrupt = context:AIRandomDisrupt()
	if needDisrupt == true then
		context:AISwitchTo("disrupt")
	else
		context:AISwitchTo("attackcd")
	end
end

-- ����CD
function g_ai_class_combat_fsm:attackcd(context)
	-- ��ʼ����CD��ʱ��
	context:AIStartActionInter(g_ai_const.AI_CONST_TIMER_TYPE_ATTACK_CD)
	
	-- ׷��������ָ������
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

-- �ŵ�״̬
function g_ai_class_combat_fsm:disrupt(context)
	--	��ʼ�ŵм�ʱ��
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

-- �������״̬
function g_ai_class_combat_fsm:back(context)
	context:AIBack()
	
	if context:AITestJump() == true then
		return
	end
	
	context:AISwitchTo("idle")
end

-- ��ʬ״̬
function g_ai_class_combat_fsm:guarding_corpse(context)
    local code,data = context:AIGuardingCorpse(context.guardCorpse)
    
    if context:AITestJump() == true then
        return
    end
    
    context:AISwitchTo("back")
end
