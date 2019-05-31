AdventureScripts = {}

pwdist.dofile("./Lua/ctrlsrv/simpl_adventure_common.lua")

function CreateAdventureScript(class,conf)
    if AdventureScripts[class] == nil then
        return CommonAdventure:New(conf)
    end
    return AdventureScripts[class]:New(conf)
end
