----------------------------------------------------------
-- AI条件技能的脚本条件
-- 对应NpcConditionSkillConfig.xls表中"脚本条件"
----------------------------------------------------------

-- 检查自身是否存在指定buff : npc:GetModAura():Exists(buffid)
-- 		参数：buffid:buffID
-- 		返回：true/false

-- 获取自身当前召唤物数量 : npc:GetModSummoner():GetSummonedNum()
-- 		参数：无
-- 		返回：召唤物数量

-- 判断当前目标是否在指定范围 : npc:IsTargetInCircle(angle,dist,radius)
-- 		参数：angle:相对当前朝向的偏角，dist:相对自身的距离，radius:范围半径
-- 		返回：true/false

-- 获取目标 : npc:GetTarget()

----------------------------------------------------------
-- demo1 : 判断当前目标是否存在指定buff
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
		npc:Talk(41706)--41706虚幻的世界把真实的自我掩盖其中……
		return true
	end
	
	return false
end

function AICheckScriptCondition40100(npc)
	--魔王本的邪龙用的，别的不能用这个，搜索场景中所有的玩家目标
    local humanTab = GetCurrentStage():GetModObjs():GetHumans()
    for _,v in ipairs(humanTab) do
        if (v ~= nil) and (not v:IsNil()) then                          -- 校验目标非空
			if (npc:IsUnitInCircle(v, 0, 4, 5)) then   --前方4米，半径5米
				return true  -- 校验位置是否满足条件
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
-- 在与npc同组的怪中选择一个血量百分比低于percent的怪，作为当前目标
-- npc: 当前npc
-- percent: 百分比
-- 返回:true表示成功选择到目标,false表示没选到
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
		npc:Talk(41677)--41677	龙族的勇士啊，快来保护女王！
		return true
	end
	return false
end

-- -----------------------------------------------------------------------------------
-- 选择一个玩家作为当前目标。该玩家满足1)不是当前目标 2)职业是profession 3)血量百分比在hpPercentMin~hpPercentMax之间 4)距离在distance内 5)身上存在buffid的buff
-- profession: 指定职业
-- hpPercentMin: 百分比下限
-- hpPercentMax: 百分比上限
-- distance: 距离上限
-- buffid: 指定buff id
-- 返回:true表示成功选择到目标,false表示没选到
-- -----------------------------------以下为模板，每次使用需要拷贝一套出来，改ID填到NpcConditionSkillConfig.xls------------------------------------------------
function _AISelectTargetHuman1(npc,profession,hpPercentMin,hpPercentMax,distance,buffid)
    local humanTab = GetCurrentStage():GetModObjs():GetHumans()
    for _,v in ipairs(humanTab) do
        if (v ~= nil) and (not v:IsNil())                           -- 校验目标非空
        and (not _AIIsCurrentTarget(npc,v))                         -- 不是当前目标
        and (v:GetProfession() == profession)                       -- 校验目标职业
        and (v:GetModStatistic():GetHPPercent() >= hpPercentMin)    -- 校验目标血量
        and (v:GetModStatistic():GetHPPercent() < hpPercentMax)
        and (_AIIsDistanceLess(npc,v,distance))                     -- 校验目标距离
        and (v:GetModAura():Exists(buffid)) then                    -- 校验目标身上的buff
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
-- 例子1: 选择一个玩家作为当前目标。该玩家满足
-- 1)不是当前目标 
-- 2)职业是1[战士] 
-- 3)血量百分比在20~50之间 
-- 4)距离在10内 
-- 5)身上存在2021的buff
-- -----------------------------------------------------------------------------------
function AICheckScriptConditionTest1(npc)
    return _AISelectTargetHuman1(npc,1,20,50,10,2021)
end

-- -----------------------------------------------------------------------------------
-- 例子2: 判断指定圆中是否存在一名玩家
-- 注: 仅用于类似魔王本这种玩家数较少的场景，玩家数较多的场景需策划另外提接口需求
-- -----------------------------------------------------------------------------------
function AICheckScriptConditionTest2(npc)
    local humanTab = GetCurrentStage():GetModObjs():GetHumans()
    for _,v in ipairs(humanTab) do
        if (v ~= nil) and (not v:IsNil())                           -- 校验目标非空
        and (npc:IsUnitInCircle(v, 0, 20.0, 8.0)) then              -- 校验位置是否满足条件
            return true
        end
    end
    
    return false
end

-- -----------------------------------------------------------------------------------
-- 例子3: 判断npc的仇恨列表中是否存在一个目标，该目标在指定圆中
-- -----------------------------------------------------------------------------------
function AICheckScriptConditionTest3(npc)
    local unitTab = npc:GetModThreat():CollectThreats()
    for _,v in ipairs(unitTab) do
        if (v ~= nil) and (not v:IsNil())                           -- 校验目标非空
        and (npc:IsUnitInCircle(v, 0, 20.0, 8.0)) then              -- 校验位置是否满足条件
            return true
        end
    end
    
    return false
end

------------------------------------------------例子结束------------------------------------------------
function _AISelectTargetHuman2(npc,distance)
    local unitTab = npc:GetModThreat():CollectThreats()
    for _,v in ipairs(unitTab) do
        if (v ~= nil) and (not v:IsNil())                           -- 校验目标非空
        and (not _AIIsCurrentTarget(npc,v))                         -- 不是当前目标
        and (_AIIsDistanceLess(npc,v,distance)) then            -- 校验目标距离
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
-- 描述：选择仇恨列表中血量百分比最小的目标且在指定距离范围内，释放指定技能
-- 参数1：npc
-- 参数2：最小距离范围
-- 参数3：最大距离范围
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
-- 描述：选择仇恨列表中血量百分比最大的目标且在指定距离范围内，释放指定技能
-- 参数1：npc
-- 参数2：最小距离范围
-- 参数3：最大距离范围
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
-- 描述：选择仇恨列表中距离最远的目标且在指定距离范围内，释放指定技能
-- 参数1：npc
-- 参数2：最小距离范围
-- 参数3：最大距离范围
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
	--雪怪boss用的，别的不能用这个，搜索场景中所有的玩家目标
    local humanTab = GetCurrentStage():GetModObjs():GetHumans()
    for _,v in ipairs(humanTab) do
        if (v ~= nil) and (not v:IsNil())                           -- 校验目标非空
        and (npc:IsUnitInCircle(v, 0, 15.0, 4.0)) then                       --校验玩家位置是否满足条件
            return true
        end
		
		if (v ~= nil) and (not v:IsNil())                           -- 校验目标非空
        and (npc:IsUnitInCircle(v, 0, 5.0, 4.0)) then              --校验玩家位置是否满足条件
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