CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------

local XYBuff = 10019999       -----眩晕免疫BUFF
local JSBuff = 10029999       -----减速免疫BUFF


function CurrentDungeonScript:Startup()
	SetEventHandler(StageEvents.CreatureSpawn,"CreatureSpawn")
--pwdist.log('监视怪物出生')
end

function CurrentDungeonScript:CreatureSpawn(creature)
--pwdist.log('开始加BUFF')
	creature:GetModAura():Create(XYBuff)
	creature:GetModAura():Create(JSBuff)
--pwdist.log('BUFF完成')
end
