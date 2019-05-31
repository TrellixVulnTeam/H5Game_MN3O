-----------------------------------------------------------------
-- 活动:跨服盟战
-----------------------------------------------------------------
local RUNCAR = {}
SImplActivitiesClasses[7] = RUNCAR

function RUNCAR:New(conf)
	local r = conf or {}
	setmetatable(r,self)
	self.__index = self
	
	return r
end

function RUNCAR:Start(stage, ref, id)
	pwdist.log("RUNCAR:Start")
	
	self.Thread = GetServiceThread()
	
	self.TimerClosed = self.Thread:CreateTimer(1 * 60, "OnClosed")
end

function RUNCAR:Signup(id, activityId, basemap)
	pwdist.log("RUNCAR:Signup")
end

function RUNCAR:OnClosed()
	self.Thread:CloseMe()
	
	pwdist.log('RUNCAR:CloseMe()');
end

function RUNCAR:Clean()
	pwdist.log('RUNCAR:Clean()');
end

