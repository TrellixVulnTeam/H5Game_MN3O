--副本选择脚本
--每个关卡都可能执行两套逻辑，一套是针对任务剧情而做的，一套是趟图用的
--这个脚本就是根据当前任务状态，选择执行不同的脚本逻辑

function SelectDungeonScript_general(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon_general.lua" 
end

function SelectDungeonScript_4000(human,stageId)
   return stageId, "./Lua/worldsrv/activities/pw_challenge.lua" 
end
function SelectDungeonScript_4002(human,stageId)
   return stageId, "./Lua/worldsrv/activities/pw_challenge_other.lua" 
end

function SelectDungeonScript_2000(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon2000.lua" 
end

function SelectDungeonScript_2100(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon2100.lua" 
end

function SelectDungeonScript_2200(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon2200.lua" 
end

function SelectDungeonScript_2300(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon2300.lua" 
end

function SelectDungeonScript_2400(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon2400.lua" 
end

function SelectDungeonScript_2500(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon2500.lua" 
end

function SelectDungeonScript_2600(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon2600.lua" 
end

function SelectDungeonScript_2700(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon2700.lua" 
end

function SelectDungeonScript_2800(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon2800.lua" 
end

function SelectDungeonScript_3999(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon3999.lua" 
end
function SelectDungeonScript_7000(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon7000.lua" 
end
function SelectDungeonScript_1009(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon1009.lua" 
end

function SelectDungeonScript_2099(human,stageId)
   return stageId, "./Lua/worldsrv/dungeon/pw_dungeon2099.lua" 
end