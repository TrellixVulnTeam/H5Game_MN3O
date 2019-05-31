SImplActivitiesClasses = {}

---------------------------------------------------------------
---------------------------------------------------------------
---------------------------------------------------------------

-- pwdist.dofile("./Lua/worldsrv/activities/pww_activity_lwgl.lua")
pwdist.dofile("./Lua/worldsrv/activities/pww_activity_dts.lua")
-- pwdist.dofile("./Lua/worldsrv/activities/pww_activity_jtz.lua")
pwdist.dofile("./Lua/worldsrv/activities/pww_activity_njtz.lua")
pwdist.dofile("./Lua/worldsrv/activities/pww_activity_boss.lua")
pwdist.dofile("./Lua/worldsrv/activities/pww_activity_kfmz.lua")
pwdist.dofile("./Lua/worldsrv/activities/pww_activity_kfmz_ladder.lua")


---------------------------------------------------------------
---------------------------------------------------------------
---------------------------------------------------------------

function CreateActivity(id,conf)
    local cls = SImplActivitiesClasses[id]
    if cls == nil then
        return nil
    end
    
    return cls:New(conf)
end