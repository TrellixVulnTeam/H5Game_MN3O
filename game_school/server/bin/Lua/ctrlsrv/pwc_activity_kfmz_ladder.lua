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
	
	self.Thread = GetServiceThread()
	
	self.TimerClosed = self.Thread:CreateTimer(25 * 60, "OnClosed")
end

function KFMZ_LADDER:Signup(id, activityId, basemap)
	pwdist.log("KFMZ_LADDER:Signup")
end

function KFMZ_LADDER:OnClosed()
	self.Thread:CloseMe()
	
	pwdist.log('KFMZ_LADDER:OnClosed()')
end

function KFMZ_LADDER:Clean()

	pwdist.log('KFMZ_LADDER:Clean()')
end