function StaticObjTrigger1(obj, human)
	pwdist.log('StaticObjTrigger1')
	
	obj:LeaveWorld(0)
	human:GetModAura():Create(60200)
end

function StaticObjTrigger2(obj, human)
	pwdist.log('StaticObjTrigger2')
	
	obj:LeaveWorld(0)
	
	math.randomseed(os.time())
	math.random(1, 3)
	local rand = math.random(1, 3)
	
	if rand == 1 then
		human:GetModAura():Create(60201)
	elseif rand == 2 then
		human:GetModAura():Create(60202)
	elseif rand == 3 then
		human:GetModAura():Create(60203)
	end
end

function StaticObjTrigger3(obj, human)
	pwdist.log('StaticObjTrigger3')
	
	obj:LeaveWorld(0)
	human:GetModAura():Create(60240)
end

function StaticObjTrigger4(obj, human)
	pwdist.log('StaticObjTrigger4')
	
	obj:LeaveWorld(0)
	human:GetModAura():Create(60241)
end

function StaticObjTrigger5(obj, human)
	pwdist.log('StaticObjTrigger5')
	
	obj:LeaveWorld(0)
	human:GetModAura():Create(60242)
end

function StaticObjTrigger6(obj, human)
	pwdist.log('StaticObjTrigger6')
	
	obj:LeaveWorld(0)
	human:GetModAura():Create(60243)
end
--[[
60240	水晶矿井：焰之利剑
60241	水晶矿井：风之祝福
60242	水晶矿井：血量回复
60243	水晶矿井：法力回复

	]]

function StaticObjTrigger9(obj, human)
	pwdist.log('StaticObjTrigger9')
	
	obj:LeaveWorld(0)
	--obj:GetModCombat():KillSelf(1050,1050)
	math.randomseed(os.time())
	math.random(1, 3)
	local rand = math.random(1, 3)
	local sanbox = MultiItemSandbox.new(human)	
	if rand == 1 then
		if(human ~=nil) then
			sanbox:Add(1,129210,1,0)			
			sanbox:Commit()	
		end
	elseif rand == 2 then
		if(human ~=nil) then
			sanbox:Add(1,129220,1,0)			
			sanbox:Commit()	
		end
	elseif rand == 3 then
		if(human ~=nil) then
			sanbox:Add(1,129230,1,0)			
			sanbox:Commit()	
		end
	end
end







	
	
