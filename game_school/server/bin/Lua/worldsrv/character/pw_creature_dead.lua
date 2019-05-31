----------------------------------------------------------
-- Npc的死亡脚本
-- 对应NpcSpawnMethodConfig.xls表中"死亡脚本"
----------------------------------------------------------

function OnCreatureDie1(mapID,casterID)
	luaE_finishDungeon(mapID,casterID)
end
