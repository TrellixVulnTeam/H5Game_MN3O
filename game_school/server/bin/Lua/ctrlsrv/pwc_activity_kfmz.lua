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
	
	self.Thread = GetServiceThread()
	
	self.TimerClosed = self.Thread:CreateTimer(1 * 60, "OnClosed")
end

function KFMZ:Signup(id, activityId, basemap)
	pwdist.log("KFMZ:Signup")
end

function KFMZ:OnClosed()
	self.Thread:CloseMe()
	
	pwdist.log('KFMZ:CloseMe()');
end

function KFMZ:Clean()
	pwdist.log('KFMZ:Clean()');
end

