-----------------------------------------------------------------
-- 活动:跨服盟战_Ladder
-----------------------------------------------------------------
local KFMZ_LADDER = {}
SImplActivitiesClasses[25] = KFMZ_LADDER

function KFMZ_LADDER:New(conf)
    local r = conf or {}
    setmetatable(r,self)
    self.__index = self
	
    return r
end

function KFMZ_LADDER:Start(stage, ref, id)
	pwdist.log("KFMZ_LADDER:Start")
end

function KFMZ_LADDER:Clean()
    pwdist.log('KFMZ_LADDER:Clean')
end

function KFMZ_LADDER:OnHumanEnter(unit)

end

function KFMZ_LADDER:OnHumanLeave(unit)

end