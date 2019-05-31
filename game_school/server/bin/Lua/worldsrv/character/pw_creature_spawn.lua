----------------------------------------------------------
-- Npc的出生脚本
-- 对应NpcSpawnMethodConfig.xls表中"出生脚本"
----------------------------------------------------------

function OnCreatureSpawn1(npcID)
	-- luaE_startUseSkillByTime(npcID, {12000,40000}, {10020})
end

function OnCreatureSpawn2(npcID)
	luaE_leave_world(npcID, 4500)
end
