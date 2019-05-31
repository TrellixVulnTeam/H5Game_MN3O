CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .


----------------------------------------------------------------------


function CurrentDungeonScript:Startup()
SetEventHandler(StageEvents.DungeonCreated, "EventCreateProcess")
end


function CurrentDungeonScript:EventCreateProcess()
  self.SModDungeonScript:CreateTimer(10, Timer1)
end


function CurrentDungeonScript:Timer1()
if SetEventHandler()>1 then
end


if SetEventHandler()>1 then
end


