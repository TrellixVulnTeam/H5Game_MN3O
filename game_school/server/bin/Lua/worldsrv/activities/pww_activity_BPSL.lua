CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------

local XYBuff = 10019999       -----ѣ������BUFF
local JSBuff = 10029999       -----��������BUFF


function CurrentDungeonScript:Startup()
	SetEventHandler(StageEvents.CreatureSpawn,"CreatureSpawn")
--pwdist.log('���ӹ������')
end

function CurrentDungeonScript:CreatureSpawn(creature)
--pwdist.log('��ʼ��BUFF')
	creature:GetModAura():Create(XYBuff)
	creature:GetModAura():Create(JSBuff)
--pwdist.log('BUFF���')
end
