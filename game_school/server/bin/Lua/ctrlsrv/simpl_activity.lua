SImplActivitiesConst = {}

SImplActivitiesConst.ACTIVITY_STATUS_NONE = 1
SImplActivitiesConst.ACTIVITY_STATUS_READY = 2
SImplActivitiesConst.ACTIVITY_STATUS_START = 3
SImplActivitiesConst.ACTIVITY_STATUS_END = 4
SImplActivitiesConst.ACTIVITY_STATUS_ENTER = 5
SImplActivitiesConst.ACTIVITY_STATUS_QUIT = 6


---------------------------------------------------------------
---------------------------------------------------------------
---------------------------------------------------------------

SImplActivitiesClasses = {}

---------------------------------------------------------------
---------------------------------------------------------------
---------------------------------------------------------------

-- pwdist.dofile("./Lua/ctrlsrv/pwc_activity_lwgl.lua")
pwdist.dofile("./Lua/ctrlsrv/pwc_activity_dts.lua")
-- pwdist.dofile("./Lua/ctrlsrv/pwc_activity_jtz.lua")
pwdist.dofile("./Lua/ctrlsrv/pwc_activity_njtz.lua")
-- pwdist.dofile("./Lua/ctrlsrv/pwc_activity_lgkj.lua")
pwdist.dofile("./Lua/ctrlsrv/pwc_activity_boss.lua")
pwdist.dofile("./Lua/ctrlsrv/pwc_activity_runcar.lua")

pwdist.dofile("./Lua/ctrlsrv/pwc_activity_kfmz.lua")
pwdist.dofile("./Lua/ctrlsrv/pwc_activity_kfmz_ladder.lua")
---------------------------------------------------------------
---------------------------------------------------------------
---------------------------------------------------------------

--g_Activity = {}--»î¶¯ÊµÀý

function CreateActivity(id,conf)
    local cls = SImplActivitiesClasses[id]
    if cls == nil then
        pwdist.log('CreateActivity nil',id)
        return nil
    end
    
	return cls:New(conf)
	
	--local obj = cls:New(conf)
	
	--if g_Activity[id] then
	--	g_Activity[id].append(obj)
	--else
	--	g_Activity[id] = {obj}
	--end
	
    --return obj
end


