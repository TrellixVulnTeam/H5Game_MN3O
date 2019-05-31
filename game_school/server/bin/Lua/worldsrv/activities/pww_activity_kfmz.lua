-----------------------------------------------------------------
-- 活动:跨服盟战
-----------------------------------------------------------------
local KFMZ = {}
SImplActivitiesClasses[24] = KFMZ

function KFMZ:New(conf)
    local r = conf or {}
    setmetatable(r,self)
    self.__index = self
	
    return r
end

function KFMZ:Start(stage, ref, id)
	pwdist.log("KFMZ:Start")
end

function KFMZ:Clean()
    pwdist.log('KFMZ:Clean')
end