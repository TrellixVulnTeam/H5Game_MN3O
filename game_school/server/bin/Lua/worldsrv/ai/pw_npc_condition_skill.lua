----------------------------------------------------------
-- AI�������ܵĽű�����
-- ��ӦNpcConditionSkillConfig.xls����"�ű�����"
----------------------------------------------------------

-- ��������Ƿ����ָ��buff : npc:GetModAura():Exists(buffid)
-- 		������buffid:buffID
-- 		���أ�true/false

-- ��ȡ����ǰ�ٻ������� : npc:GetModSummoner():GetSummonedNum()
-- 		��������
-- 		���أ��ٻ�������

-- �жϵ�ǰĿ���Ƿ���ָ����Χ : npc:IsTargetInCircle(angle,dist,radius)
-- 		������angle:��Ե�ǰ�����ƫ�ǣ�dist:�������ľ��룬radius:��Χ�뾶
-- 		���أ�true/false

-- ��ȡĿ�� : npc:GetTarget()

----------------------------------------------------------
-- demo1 : �жϵ�ǰĿ���Ƿ����ָ��buff
--    function AICheckScriptCondition1(npc)
--        local target = npc:GetTarget()
--        if target ~= nil and target:GetModAura():Exists(100) then
--            return true
--        end
--        
--        return false
--    end

function AICheckScriptCondition1(npc)
	if npc:GetModAura():Exists(100) then
		return true
	end
	
	return false
end

function AICheckScriptCondition2(npc)
	if npc:GetModSummoner():GetSummonedNum() < 1 then
		return true
	end
	
	return false
end

function AICheckScriptCondition10116(npc)
	if npc:GetModSummoner():GetSummonedNum() < 1 then
		return true
	end
	
	return false
end

function AICheckScriptCondition10100(npc)
	if npc:GetModAura():Exists(10160) then
		return true
	end
	
	return false
end

function AICheckScriptCondition10101(npc)
	if npc:GetModAura():Exists(10160) then
		return false
	end
	
	return true
end

function AICheckScriptCondition10213(npc)
	local target = npc:GetTarget()
		if target ~= nil and target:GetModAura():Exists(10230) then
			return true
		end
		
	return false
end

function AICheckScriptCondition12000(npc)
	if npc:GetModAura():Exists(12030) then
		return true
	end
	
	return false
end

function AICheckScriptCondition12012(npc)
	if npc:GetModAura():Exists(12030) and not npc:GetModAura():Exists(4) then
		return true
	end
	
	return false
end

function AICheckScriptCondition12013(npc)
	if npc:GetModAura():Exists(12030) and npc:GetModAura():Exists(4) then
		return true
	end
	
	return false
end

function AICheckScriptCondition12301(npc)
	if npc:GetModSummoner():GetSummonedNum() > 3 then
		return true
	end
	
	return false
end

function AICheckScriptCondition12302(npc)
	if npc:GetModSummoner():GetSummonedNum() < 6 then
		return true
	end
	
	return false
end

function AICheckScriptCondition12601(npc)
	if npc:GetModAura():Exists(12630) then
		return false
	end
	
	return true
end

function AICheckScriptCondition12602(npc)
	if npc:GetModAura():Exists(12630) then
		return true
	end
	
	return false
end

function AICheckScriptCondition12714(npc)
	if npc:GetModSummoner():GetSummonedNum() < 1 then
		return true
	end
	
	return false
end

function AICheckScriptCondition14405(npc)
	if npc:GetModSummoner():GetSummonedNum() < 1 then
		npc:Talk(41706)--41706��õ��������ʵ�������ڸ����С���
		return true
	end
	
	return false
end

function AICheckScriptCondition40100(npc)
	--ħ������а���õģ���Ĳ�����������������������е����Ŀ��
    local humanTab = GetCurrentStage():GetModObjs():GetHumans()
    for _,v in ipairs(humanTab) do
        if (v ~= nil) and (not v:IsNil()) then                          -- У��Ŀ��ǿ�
			if (npc:IsUnitInCircle(v, 0, 4, 5)) then   --ǰ��4�ף��뾶5��
				return true  -- У��λ���Ƿ���������
			end
			
			if (npc:IsUnitInCircle(v, 0, 12, 5)) then
				return true
			end
			
			if (npc:IsUnitInCircle(v, 0, 20, 5)) then
				return true
			end
        end
    end
    
    return false
end

function AICheckScriptCondition40104(npc)
	if npc:GetModSummoner():GetSummonedNum() < 3 then
		return true
	end
	
	return false
end
function AICheckScriptCondition13002(npc)
	if npc:GetModSummoner():GetSummonedNum() < 1 then
		return true
	end
	
	return false
end

function AICheckScriptCondition13003(npc)
	if npc:GetModSummoner():GetSummonedNum() < 1 then
		return true
	end
	
	return false
end

-- -----------------------------------------------------------------------------------
-- ����npcͬ��Ĺ���ѡ��һ��Ѫ���ٷֱȵ���percent�Ĺ֣���Ϊ��ǰĿ��
-- npc: ��ǰnpc
-- percent: �ٷֱ�
-- ����:true��ʾ�ɹ�ѡ��Ŀ��,false��ʾûѡ��
-- -----------------------------------------------------------------------------------
function _AISelectTargetNpc1(npc,percent)
    local monsterTab = GetCurrentStage():GetModObjs():CollectCreatureBySpawnMethod(npc:GetNpcSpawnMethodName())
    for _,v in ipairs(monsterTab) do
        if v:GetID() ~= npc:GetID() and v:GetModStatistic():GetHPPercent() < percent then
            local aiContext = g_ai_tables[npc:GetAIUniqueID()]
            if aiContext == nil then
                return false
            end
            
            aiContext:AIChangeTarget(v:GetID())
            return true
        end
    end
    
    return false
end

function AICheckScriptCondition88888(npc)
    return _AISelectTargetNpc1(npc,50)
end

-- -----------------------------------------------------------------------------------

function _AIIsDistanceLess(npc,human,dist)
    local pos1 = npc:GetPosition()
    local pos2 = human:GetPosition()
    
    local dx = math.abs(pos1[1] - pos2[1])
    local dy = math.abs(pos1[2] - pos2[2])
    local dz = math.abs(pos1[3] - pos2[3])
    
    return (dx*dx + dy*dy + dz*dz) < dist*dist
end

function _AIIsDistanceGreat(npc,human,dist)
    local pos1 = npc:GetPosition()
    local pos2 = human:GetPosition()
    
    local dx = math.abs(pos1[1] - pos2[1])
    local dy = math.abs(pos1[2] - pos2[2])
    local dz = math.abs(pos1[3] - pos2[3])
    
    return (dx*dx + dy*dy + dz*dz) >= dist*dist
end

function _AICalcDistance(pos1,pos2)
    local dx = math.abs(pos1[1] - pos2[1])
    local dy = math.abs(pos1[2] - pos2[2])
    local dz = math.abs(pos1[3] - pos2[3])
    
    return math.sqrt(dx*dx + dy*dy + dz*dz)
end

function _AIIsCurrentTarget(npc,human)
    local target = npc:GetTarget()
    if target == nil or target:IsNil() then
        return false
    end
    
    return target:GetID() == human:GetID()
end

function AICheckScriptCondition13502(npc)
	if npc:GetModSummoner():GetSummonedNum() < 1 then
		npc:Talk(41677)--41677	�������ʿ������������Ů����
		return true
	end
	return false
end

-- -----------------------------------------------------------------------------------
-- ѡ��һ�������Ϊ��ǰĿ�ꡣ���������1)���ǵ�ǰĿ�� 2)ְҵ��profession 3)Ѫ���ٷֱ���hpPercentMin~hpPercentMax֮�� 4)������distance�� 5)���ϴ���buffid��buff
-- profession: ָ��ְҵ
-- hpPercentMin: �ٷֱ�����
-- hpPercentMax: �ٷֱ�����
-- distance: ��������
-- buffid: ָ��buff id
-- ����:true��ʾ�ɹ�ѡ��Ŀ��,false��ʾûѡ��
-- -----------------------------------����Ϊģ�壬ÿ��ʹ����Ҫ����һ�׳�������ID�NpcConditionSkillConfig.xls------------------------------------------------
function _AISelectTargetHuman1(npc,profession,hpPercentMin,hpPercentMax,distance,buffid)
    local humanTab = GetCurrentStage():GetModObjs():GetHumans()
    for _,v in ipairs(humanTab) do
        if (v ~= nil) and (not v:IsNil())                           -- У��Ŀ��ǿ�
        and (not _AIIsCurrentTarget(npc,v))                         -- ���ǵ�ǰĿ��
        and (v:GetProfession() == profession)                       -- У��Ŀ��ְҵ
        and (v:GetModStatistic():GetHPPercent() >= hpPercentMin)    -- У��Ŀ��Ѫ��
        and (v:GetModStatistic():GetHPPercent() < hpPercentMax)
        and (_AIIsDistanceLess(npc,v,distance))                     -- У��Ŀ�����
        and (v:GetModAura():Exists(buffid)) then                    -- У��Ŀ�����ϵ�buff
            local aiContext = g_ai_tables[npc:GetAIUniqueID()]
            if aiContext == nil then
                return false
            end
            
            aiContext:AIChangeTarget(v:GetID())
            return true
        end
    end
    
    return false
end

-- -----------------------------------------------------------------------------------
-- ����1: ѡ��һ�������Ϊ��ǰĿ�ꡣ���������
-- 1)���ǵ�ǰĿ�� 
-- 2)ְҵ��1[սʿ] 
-- 3)Ѫ���ٷֱ���20~50֮�� 
-- 4)������10�� 
-- 5)���ϴ���2021��buff
-- -----------------------------------------------------------------------------------
function AICheckScriptConditionTest1(npc)
    return _AISelectTargetHuman1(npc,1,20,50,10,2021)
end

-- -----------------------------------------------------------------------------------
-- ����2: �ж�ָ��Բ���Ƿ����һ�����
-- ע: ����������ħ����������������ٵĳ�����������϶�ĳ�����߻�������ӿ�����
-- -----------------------------------------------------------------------------------
function AICheckScriptConditionTest2(npc)
    local humanTab = GetCurrentStage():GetModObjs():GetHumans()
    for _,v in ipairs(humanTab) do
        if (v ~= nil) and (not v:IsNil())                           -- У��Ŀ��ǿ�
        and (npc:IsUnitInCircle(v, 0, 20.0, 8.0)) then              -- У��λ���Ƿ���������
            return true
        end
    end
    
    return false
end

-- -----------------------------------------------------------------------------------
-- ����3: �ж�npc�ĳ���б����Ƿ����һ��Ŀ�꣬��Ŀ����ָ��Բ��
-- -----------------------------------------------------------------------------------
function AICheckScriptConditionTest3(npc)
    local unitTab = npc:GetModThreat():CollectThreats()
    for _,v in ipairs(unitTab) do
        if (v ~= nil) and (not v:IsNil())                           -- У��Ŀ��ǿ�
        and (npc:IsUnitInCircle(v, 0, 20.0, 8.0)) then              -- У��λ���Ƿ���������
            return true
        end
    end
    
    return false
end

------------------------------------------------���ӽ���------------------------------------------------
function _AISelectTargetHuman2(npc,distance)
    local unitTab = npc:GetModThreat():CollectThreats()
    for _,v in ipairs(unitTab) do
        if (v ~= nil) and (not v:IsNil())                           -- У��Ŀ��ǿ�
        and (not _AIIsCurrentTarget(npc,v))                         -- ���ǵ�ǰĿ��
        and (_AIIsDistanceLess(npc,v,distance)) then            -- У��Ŀ�����
            local aiContext = g_ai_tables[npc:GetAIUniqueID()]
            if aiContext == nil then
                return false
            end
            
            aiContext:AIChangeTarget(v:GetID())
            return true
        end
    end
    
    return false
end

function AICheckScriptCondition15105(npc)
    return _AISelectTargetHuman2(npc,20)
end

-------------------------------------------------------------------------------------
-- ������ѡ�����б���Ѫ���ٷֱ���С��Ŀ������ָ�����뷶Χ�ڣ��ͷ�ָ������
-- ����1��npc
-- ����2����С���뷶Χ
-- ����3�������뷶Χ
-------------------------------------------------------------------------------------
function _AISelectTargetLowestHPPercent(npc,distMin,distMax)
	local unitTab = npc:GetModThreat():CollectThreats()
	local hppercent = 100
	local targetid = 0
    for _,v in ipairs(unitTab) do
		if (v ~= nil) and (not v:IsNil()) then
			local dist = _AICalcDistance(npc:GetPosition(),v:GetPosition())
			if dist > distMin and dist < distMax  and v:GetModStatistic():GetHPPercent() < hppercent then
				hppercent = v:GetModStatistic():GetHPPercent()
				targetid = v:GetID()
			end
		end
    end
	
	if targetid ~= 0 then
		local aiContext = g_ai_tables[npc:GetAIUniqueID()]
		if aiContext == nil then
			return false
		end
		
		aiContext:AIChangeTarget(targetid)
		return true
	end
    
    return false
end

-------------------------------------------------------------------------------------
-- ������ѡ�����б���Ѫ���ٷֱ�����Ŀ������ָ�����뷶Χ�ڣ��ͷ�ָ������
-- ����1��npc
-- ����2����С���뷶Χ
-- ����3�������뷶Χ
-------------------------------------------------------------------------------------
function _AISelectTargetHighestHPPercent(npc,distMin,distMax)
	local unitTab = npc:GetModThreat():CollectThreats()
	local hppercent = 100
	local targetid = 0
    for _,v in ipairs(unitTab) do
		if (v ~= nil) and (not v:IsNil()) then
			local dist = _AICalcDistance(npc:GetPosition(),v:GetPosition())
			if dist > distMin and dist < distMax  and v:GetModStatistic():GetHPPercent() > hppercent then
				hppercent = v:GetModStatistic():GetHPPercent()
				targetid = v:GetID()
			end
		end
    end
	
	if targetid ~= 0 then
		local aiContext = g_ai_tables[npc:GetAIUniqueID()]
		if aiContext == nil then
			return false
		end
		
		aiContext:AIChangeTarget(targetid)
		return true
	end
    
    return false
end

-------------------------------------------------------------------------------------
-- ������ѡ�����б��о�����Զ��Ŀ������ָ�����뷶Χ�ڣ��ͷ�ָ������
-- ����1��npc
-- ����2����С���뷶Χ
-- ����3�������뷶Χ
-------------------------------------------------------------------------------------
function _AISelectTargetFarestHPPercent(npc,distMin,distMax)
	local unitTab = npc:GetModThreat():CollectThreats()
	local distCur = 0
	local targetid = 0
    for _,v in ipairs(unitTab) do
		if (v ~= nil) and (not v:IsNil()) then
			local dist = _AICalcDistance(npc:GetPosition(),v:GetPosition())
			if dist > distMin and dist < distMax  and dist > distCur then
				distCur = dist
				targetid = v:GetID()
			end
		end
    end
	
	if targetid ~= 0 then
		local aiContext = g_ai_tables[npc:GetAIUniqueID()]
		if aiContext == nil then
			return false
		end
		
		aiContext:AIChangeTarget(targetid)
		return true
	end
    
    return false
end

function AISelectTargetFarestHPPercent11811(npc)
	return _AISelectTargetFarestHPPercent(npc,5,18)
end

function AISelectTargetLowestHPPercent11812(npc)
	return _AISelectTargetLowestHPPercent(npc,0,9)
end

function AISelectTargetLowestHPPercent12320(npc)
	return _AISelectTargetLowestHPPercent(npc,0,14)
end

function AISelectTargetFarestHPPercent12321(npc)
	return _AISelectTargetFarestHPPercent(npc,0,11)
end

function AISelectTargetLowestHPPercent12323(npc)
	return _AISelectTargetLowestHPPercent(npc,0,14)
end

function AISelectTargetLowestHPPercent16570(npc)
	return _AISelectTargetLowestHPPercent(npc,0,19)
end

function AISelectTargetFarestHPPercent14204(npc)
	return _AISelectTargetFarestHPPercent(npc,0,19)
end

function AISelectTargetLowestHPPercent10001(npc)
	return _AISelectTargetLowestHPPercent(npc,0,19)
end

function AISelectTargetFarestHPPercent10210(npc)
	return _AISelectTargetFarestHPPercent(npc,5,19)
end

function AISelectTargetLowestHPPercent10211(npc)
	return _AISelectTargetLowestHPPercent(npc,5,19)
end

function AISelectTargetLowestHPPercent40102(npc)
	return _AISelectTargetLowestHPPercent(npc,0,59)
end

function AISelectTargetFarestHPPercent14402(npc)
	return _AISelectTargetFarestHPPercent(npc,0,19)
end

function AISelectTargetLowestHPPercent14404(npc)
	return _AISelectTargetLowestHPPercent(npc,0,19)
end

function AISelectTargetFarestHPPercent13001(npc)
	return _AISelectTargetFarestHPPercent(npc,3,19)
end

function AISelectTargetLowestHPPercent13000(npc)
	return _AISelectTargetLowestHPPercent(npc,0,19)
end

function AISelectTargetFarestHPPercent16930(npc)
	return _AISelectTargetFarestHPPercent(npc,5,14)
end

function AISelectTargetLowestHPPercent10116(npc)
	return _AISelectTargetLowestHPPercent(npc,0,4)
end

function AISelectTargetFarestHPPercent10117(npc)
	return _AISelectTargetFarestHPPercent(npc,7,20)
end

function AISelectTargetFarestHPPercent15102(npc)
	return _AISelectTargetFarestHPPercent(npc,5,20)
end

function AISelectTargetLowestHPPercent17501(npc)
	return _AISelectTargetLowestHPPercent(npc,0,15)
end

function AISelectTargetFarestHPPercent40007(npc)
	return _AISelectTargetFarestHPPercent(npc,4,14)
end

function AISelectTargetFarestHPPercent90130(npc)
	return _AISelectTargetFarestHPPercent(npc,0,20)
end

function AISelectTargetLowestHPPercent90040(npc)
	return _AISelectTargetLowestHPPercent(npc,0,20)
end

function AISelectTargetLowestHPPercent90210(npc)
	return _AISelectTargetLowestHPPercent(npc,0,15)
end

function AISelectTargetFarestHPPercent90320(npc)
	return _AISelectTargetFarestHPPercent(npc,0,25)
end

function AISelectTargetLowestHPPercent90340(npc)
	return _AISelectTargetLowestHPPercent(npc,0,25)
end

function AISelectTargetFarestHPPercent90410(npc)
	return _AISelectTargetFarestHPPercent(npc,0,15)
end

function AISelectTargetLowestHPPercent100230(npc)
	return _AISelectTargetLowestHPPercent(npc,0,30)
end

function AISelectTargetFarestHPPercent100220(npc)
	return _AISelectTargetFarestHPPercent(npc,0,30)
end

function AISelectTargetLowestHPPercent100020(npc)
	return _AISelectTargetLowestHPPercent(npc,0,5)
end

function AISelectTargetFarestHPPercent100030(npc)
	return _AISelectTargetFarestHPPercent(npc,0,18)
end

function AISelectTargetLowestHPPercent100140(npc)
	return _AISelectTargetLowestHPPercent(npc,0,25)
end

function AISelectTargetFarestHPPercent100130(npc)
	return _AISelectTargetFarestHPPercent(npc,0,20)
end

function AICheckScriptCondition17702(npc)
	--ѩ��boss�õģ���Ĳ�����������������������е����Ŀ��
    local humanTab = GetCurrentStage():GetModObjs():GetHumans()
    for _,v in ipairs(humanTab) do
        if (v ~= nil) and (not v:IsNil())                           -- У��Ŀ��ǿ�
        and (npc:IsUnitInCircle(v, 0, 15.0, 4.0)) then                       --У�����λ���Ƿ���������
            return true
        end
		
		if (v ~= nil) and (not v:IsNil())                           -- У��Ŀ��ǿ�
        and (npc:IsUnitInCircle(v, 0, 5.0, 4.0)) then              --У�����λ���Ƿ���������
            return true
		end
		return false
    end
end

function AICheckScriptCondition17701(npc)
	if npc:GetModSummoner():GetSummonedNum() < 1 then
		return true
	end
	return false
end