function IfStun(target)

	if target:GetModAura():Exists(10010500) or target:GetModAura():Exists(10011000) or target:GetModAura():Exists(10011500) then		--目标有这些眩晕时返回true
		return true
	elseif target:GetModAura():Exists(10012000) or target:GetModAura():Exists(10012500) or target:GetModAura():Exists(10013000) then    --目标有这些眩晕时返回true
		return true
	end

	return false
end

-----------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------以下为通用技能判断函数-------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------

--蓄力检测，自身有<蓄力>时生效
function CombatTriggerCondition10000100(caster, target)
	if caster:GetModAura():Exists(10000100) then		--自身有<蓄力>时生效
		
		pwdist.log("CombatTriggerCondition10000100_true")
		
		return true
	end
	
	pwdist.log("CombatTriggerCondition10000100_false")
	
	return false 
end

--集气检测，自身有<集气>时生效
function CombatTriggerCondition10000200(caster, target)
	if caster:GetModAura():Exists(10000200) then		--自身有<集气>时生效
		return true
	end

	return false 
end

--虚弱检测，目标有<虚弱>时生效
function CombatTriggerCondition10000300(caster, target)
	if target:GetModAura():Exists(10000300) then		--目标有<虚弱>时生效
		return true
	end
	
	return false 
end

--破甲检测，目标有<破甲>时生效
function CombatTriggerCondition10000400(caster, target)
	if target:GetModAura():Exists(10000400) then		--目标有<破甲>时生效
		return true
	end
	
	return false 
end

--自身蓄力检测，自身有<蓄力>时生效
function CombatTriggerCondition10010100(owner)
	if owner:GetModAura():Exists(10000100) then		--自身有<蓄力>时生效
		return true
	end
	
	return false 
end

--自身集气检测，自身有<集气>时生效
function CombatTriggerCondition10010200(owner)
	if owner:GetModAura():Exists(10000200) then		--自身有<集气>时生效
		return true
	end
	
	return false 
end

--克制蓄力检测，自身有<蓄力>时生效
function CombatTriggerCondition10020100(caster, target)
	if target:GetModAura():Exists(10000100) then		--目标有<蓄力>时生效
		return true
	end
	
	return false 
end

--克制集气检测，自身有<集气>时生效
function CombatTriggerCondition10020200(caster, target)
	if target:GetModAura():Exists(10000200) then		--目标有<集气>时生效
		return true
	end
	
	return false 
end

--克制虚弱检测，目标有<虚弱>时生效
function CombatTriggerCondition10020300(caster, target)
	if caster:GetModAura():Exists(10000300) then		--自身有<虚弱>时生效
		return true
	end
	
	return false 
end

--克制破甲检测，目标有<破甲>时生效
function CombatTriggerCondition10020400(caster, target)
	if caster:GetModAura():Exists(10000400) then		--自身有<破甲>时生效
		return true
	end
	
	return false 
end

-----------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------以下为专用技能判断函数-------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------


--伏魔禅杖，目标有<破甲>或<虚弱>时生效
function CombatTriggerCondition20002200(caster, target)
	if target:GetModAura():Exists(10000400) or target:GetModAura():Exists(10000300) then		--目标有<破甲>或<虚弱>时生效
		return true
	end
	
	return false 
end

--以柔克刚，自身有<蓄力>或目标有破甲时额外伤害
function CombatTriggerCondition20008100(caster, target)
	if caster:GetModAura():Exists(10000100) then		--自身有<蓄力>时生效
		return true
	end
	if target:GetModAura():Exists(10000400) then		--目标有<破甲>时生效
		return true
	end
	
	return false 
end

--乱舞梨花，对有<破甲>的目标额外伤害
function CombatTriggerCondition20008300(caster, target)
	if target:GetModAura():Exists(10000400) then		--目标有<破甲>时生效
		return true
	end
	
	return false 
end

--摧心魔掌，有破甲回血
function CombatTriggerCondition20010301(caster, target)
	if caster:GetModAura():Exists(10000400) then		--自身有<破甲>时生效
		return true
	end
	
	return false 
end

--听声辨位，有蓄力加伤
function CombatTriggerCondition20011200(caster, target)
	if caster:GetModAura():Exists(10000100) then		--自身有<蓄力>时生效
		return true
	end
	
	return false 
end

--飞天蝙蝠，有蓄力加伤
function CombatTriggerCondition20011300(caster, target)
	if caster:GetModAura():Exists(10000100) then		--自身有<蓄力>时生效
		return true
	end
	
	return false 
end

--飞天蝙蝠，对虚弱加伤
function CombatTriggerCondition20011301(caster, target)
	if target:GetModAura():Exists(10000300) then		--目标有<虚弱>时生效
		return true
	end
	
	return false 
end

--袖里乾坤-对破甲加伤
function CombatTriggerCondition20013100(caster, target)
	if target:GetModAura():Exists(10000400) then		--目标有<破甲>时生效
		return true
	end
	
	return false 
end


-----------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------以下为法宝强化判断函数-------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------


--混沌葫芦-减CD
function CombatTriggerCondition26001001(owner)
	if owner:GetModMagicWeapon():Exists(26001001) then
		return true
	end
	
	return false 
end

--混沌葫芦-增加伤害
function CombatTriggerCondition26001002(caster, target)
	if caster:GetModMagicWeapon():Exists(26001002) then
		return true
	end
	
	return false 
end

--混沌葫芦-附带减命中
function CombatTriggerCondition26001003(caster, target)
	if caster:GetModMagicWeapon():Exists(26001003) then
		return true
	end
	
	return false 
end

--乾坤笔-增加暴击
function CombatTriggerCondition26002001(caster, target)
	if caster:GetModMagicWeapon():Exists(26002001) then
		return true
	end
	
	return false 
end

--乾坤笔-增加持续时间
function CombatTriggerCondition26002002(caster, target)
	if caster:GetModMagicWeapon():Exists(26002002) then
		return true
	end
	
	return false 
end

--乾坤笔-增加移动速度
function CombatTriggerCondition26002003(caster, target)
	if caster:GetModMagicWeapon():Exists(26002003) then
		return true
	end
	
	return false 
end

--天命手环-附带水抗
function CombatTriggerCondition26003001(caster, target)
	if caster:GetModMagicWeapon():Exists(26003001) then
		return true
	end
	
	return false 
end

--天命手环-附带火抗
function CombatTriggerCondition26003002(caster, target)
	if caster:GetModMagicWeapon():Exists(26003002) then
		return true
	end
	
	return false 
end

--天命手环-附带土抗
function CombatTriggerCondition26003003(caster, target)
	if caster:GetModMagicWeapon():Exists(26003003) then
		return true
	end
	
	return false 
end

--神机盒-减CD
function CombatTriggerCondition26004001(owner)
	if owner:GetModMagicWeapon():Exists(26004001) then
		return true
	end
	
	return false 
end

--神机盒-增加伤害
function CombatTriggerCondition26004002(caster, target)
	if caster:GetModMagicWeapon():Exists(26004002) then
		return true
	end
	
	return false 
end

--神机盒-附带dot
function CombatTriggerCondition26004003(caster, target)
	if caster:GetModMagicWeapon():Exists(26004003) then
		return true
	end
	
	return false 
end

--混元拂尘-减CD
function CombatTriggerCondition26005001(owner)
	if owner:GetModMagicWeapon():Exists(26005001) then
		return true
	end
	
	return false 
end

--混元拂尘-附带dot
function CombatTriggerCondition26005002(caster, target)
	if caster:GetModMagicWeapon():Exists(26005002) then
		return true
	end
	
	return false 
end

--混元拂尘-减速更多
function CombatTriggerCondition26005003(caster, target)
	if caster:GetModMagicWeapon():Exists(26005003) then
		return true
	end
	
	return false 
end

--风火轮-增加伤害
function CombatTriggerCondition26006001(caster, target)
	if caster:GetModMagicWeapon():Exists(26006001) then
		return true
	end
	
	return false 
end

--风火轮-附带眩晕
function CombatTriggerCondition26006002(caster, target)
	if caster:GetModMagicWeapon():Exists(26006002) then
		return true
	end
	
	return false 
end

--风火轮-附带吸血
function CombatTriggerCondition26006003(caster, target)
	if caster:GetModMagicWeapon():Exists(26006003) then
		return true
	end
	
	return false 
end

--炎霄剑-减CD
function CombatTriggerCondition26007001(owner)
	if owner:GetModMagicWeapon():Exists(26007001) then
		return true
	end
	
	return false 
end

--炎霄剑-增加伤害
function CombatTriggerCondition26007002(caster, target)
	if caster:GetModMagicWeapon():Exists(26007002) then
		return true
	end
	
	return false 
end

--炎霄剑-附带吸血
function CombatTriggerCondition26007003(caster, target)
	if caster:GetModMagicWeapon():Exists(26007003) then
		return true
	end
	
	return false 
end

--天罡五雷盾-反弹效果增加
function CombatTriggerCondition26008001(caster, target)
	if caster:GetModMagicWeapon():Exists(26008001) then
		return true
	end
	
	return false 
end

--天罡五雷盾-减CD
function CombatTriggerCondition26008002(owner)
	if owner:GetModMagicWeapon():Exists(26008002) then
		return true
	end
	
	return false 
end

--天罡五雷盾-附带回血
function CombatTriggerCondition26008003(caster, target)
	if caster:GetModMagicWeapon():Exists(26008003) then
		return true
	end
	
	return false 
end

--天清玉瓶-减CD
function CombatTriggerCondition26009001(owner)
	if owner:GetModMagicWeapon():Exists(26009001) then
		return true
	end
	
	return false 
end

--天清玉瓶-增加恢复量
function CombatTriggerCondition26009002(caster, target)
	if caster:GetModMagicWeapon():Exists(26009002) then
		return true
	end
	
	return false 
end

--天清玉瓶-增加防御
function CombatTriggerCondition26009003(caster, target)
	if caster:GetModMagicWeapon():Exists(26009003) then
		return true
	end
	
	return false 
end

--无影刺-减CD
function CombatTriggerCondition26010001(owner)
	if owner:GetModMagicWeapon():Exists(26010001) then
		return true
	end
	
	return false 
end

--无影刺-增加伤害
function CombatTriggerCondition26010002(caster, target)
	if caster:GetModMagicWeapon():Exists(26010002) then
		return true
	end
	
	return false 
end

--无影刺-附带减速
function CombatTriggerCondition26010003(caster, target)
	if caster:GetModMagicWeapon():Exists(26010003) then
		return true
	end
	
	return false 
end

--遮天钟-减CD
function CombatTriggerCondition26011001(owner)
	if owner:GetModMagicWeapon():Exists(26011001) then
		return true
	end
	
	return false 
end

--遮天钟-恢复生命
function CombatTriggerCondition26011002(caster, target)
	if caster:GetModMagicWeapon():Exists(26011002) then
		return true
	end
	
	return false 
end

--遮天钟-免疫眩晕
function CombatTriggerCondition26011003(caster, target)
	if caster:GetModMagicWeapon():Exists(26011003) then
		return true
	end
	
	return false 
end

--山河图-增加闪避
function CombatTriggerCondition26012001(owner)
	if owner:GetModMagicWeapon():Exists(26012001) then
		return true
	end
	
	return false 
end

--山河图-加持续时间
function CombatTriggerCondition26012002(caster, target)
	if caster:GetModMagicWeapon():Exists(26012002) then
		return true
	end
	
	return false 
end

--山河图-增加命中
function CombatTriggerCondition26012003(caster, target)
	if caster:GetModMagicWeapon():Exists(26012003) then
		return true
	end
	
	return false 
end

--封魔之刃-手里剑-减少cd
function CombatTriggerCondition26013001(owner)
	if owner:GetModMagicWeapon():Exists(26013001) then
		return true
	end
	
	return false 
end

--封魔之刃-手里剑-增加dot25%伤害
function CombatTriggerCondition26013002(caster, target)
	if caster:GetModMagicWeapon():Exists(26013002) then
		return true
	end
	
	return false 
end

--封魔之刃-手里剑-目标10%减速
function CombatTriggerCondition26013003(caster, target)
	if caster:GetModMagicWeapon():Exists(26013003) then
		return true
	end
	
	return false 
end

--夺魄-镰刀-减少cd
function CombatTriggerCondition26014001(owner)
	if owner:GetModMagicWeapon():Exists(26014001) then
		return true
	end
	
	return false 
end

--夺魄-镰刀-2倍伤害
function CombatTriggerCondition26014002(caster, target)
	if caster:GetModMagicWeapon():Exists(26014002) then
		return true
	end
	
	return false 
end

--夺魄-镰刀-1.5秒眩晕
function CombatTriggerCondition26014003(caster, target)
	if caster:GetModMagicWeapon():Exists(26014003) then
		return true
	end
	
	return false 
end

--传国玉玺-玉玺-80%减防
function CombatTriggerCondition26015001(caster, target)
	if caster:GetModMagicWeapon():Exists(26015001) then
		return true
	end
	
	return false 
end

--传国玉玺-玉玺-2倍伤害
function CombatTriggerCondition26015002(caster, target)
	if caster:GetModMagicWeapon():Exists(26015002) then
		return true
	end
	
	return false 
end

--传国玉玺-玉玺-3秒50%减速
function CombatTriggerCondition26015003(caster, target)
	if caster:GetModMagicWeapon():Exists(26015003) then
		return true
	end
	
	return false 
end




-----------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------以下为职业强化判断函数-------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------


--一阶buff判断
function CombatTriggerCondition19010010(caster, target)
	if caster:GetModAura():Exists(19011010) then
		return true
	end
	if caster:GetModAura():Exists(19012010) then
		return true
	end
	if caster:GetModAura():Exists(19013010) then
		return true
	end
	
	return false 
end

--二阶buff判断
function CombatTriggerCondition19010020(caster, target)
	if caster:GetModAura():Exists(19011020) then
		return true
	end
	if caster:GetModAura():Exists(19012020) then
		return true
	end
	if caster:GetModAura():Exists(19013020) then
		return true
	end
	
	return false 
end

--三阶buff判断
function CombatTriggerCondition19010030(caster, target)
	if caster:GetModAura():Exists(19011030) then
		return true
	end
	if caster:GetModAura():Exists(19012030) then
		return true
	end
	if caster:GetModAura():Exists(19013030) then
		return true
	end
	
	return false 
end

--四阶buff判断
function CombatTriggerCondition19010040(caster, target)
	if caster:GetModAura():Exists(19011040) then
		return true
	end
	if caster:GetModAura():Exists(19012040) then
		return true
	end
	if caster:GetModAura():Exists(19013040) then
		return true
	end
	
	return false 
end

--五阶buff判断
function CombatTriggerCondition19010050(caster, target)
	if caster:GetModAura():Exists(19011050) then
		return true
	end
	if caster:GetModAura():Exists(19012050) then
		return true
	end
	if caster:GetModAura():Exists(19013050) then
		return true
	end
	
	return false 
end

--六阶buff判断
function CombatTriggerCondition19010060(caster, target)
	if caster:GetModAura():Exists(19011060) then
		return true
	end
	if caster:GetModAura():Exists(19012060) then
		return true
	end
	if caster:GetModAura():Exists(19013060) then
		return true
	end
	
	return false 
end

--七阶buff判断
function CombatTriggerCondition19010070(caster, target)
	if caster:GetModAura():Exists(19011070) then
		return true
	end
	if caster:GetModAura():Exists(19012070) then
		return true
	end
	if caster:GetModAura():Exists(19013070) then
		return true
	end
	
	return false 
end

--八阶buff判断
function CombatTriggerCondition19010080(caster, target)
	if caster:GetModAura():Exists(19011080) then
		return true
	end
	if caster:GetModAura():Exists(19012080) then
		return true
	end
	if caster:GetModAura():Exists(19013080) then
		return true
	end
	
	return false 
end

--九阶buff判断
function CombatTriggerCondition19010090(caster, target)
	if caster:GetModAura():Exists(19011090) then
		return true
	end
	if caster:GetModAura():Exists(19012090) then
		return true
	end
	if caster:GetModAura():Exists(19013090) then
		return true
	end
	
	return false 
end
