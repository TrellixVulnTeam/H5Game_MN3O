-----------------------------------------------------------------
-- 活动:大逃杀 阵营
-- 世界服务器端
-----------------------------------------------------------------

FACTION = {}

-----------------------------------------------------------------

FACTION.RED_FACTION = 3
FACTION.BLUE_FACTION = 4

FACTION.Humans = {}

function FACTION:GetFaction()
	local red = 0
	local blue = 0
	for k,v in pairs(FACTION.Humans) do
		if v.leave == false then
			if v.faction == FACTION.RED_FACTION then
				red = red + 1
			elseif v.faction == FACTION.BLUE_FACTION then
				blue = blue + 1
			end
		end
	end
	
	pwdist.log('FACTION,red:', red, 'blue:', blue)
	if red <= blue then
		return FACTION.RED_FACTION
	else
		return FACTION.BLUE_FACTION
	end
end

function FACTION:CleanFaction()
	FACTION.Humans = {}
	pwdist.log('FACTION:CleanFaction')
end