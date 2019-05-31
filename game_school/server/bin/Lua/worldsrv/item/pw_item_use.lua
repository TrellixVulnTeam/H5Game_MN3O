
function OnItemUse_AddHP(user,item,context)
	local ret = luaE_addHP(user,item,context)
	return ret or -1
end

function OnItemUse_AddHPMP(user,item,context)
	local ret = luaE_addHPMP(user,item,context)
	return ret or -1
end

function OnItemUse_UseFormula(user,item,context)
	local ret = luaE_useFormula(user,item,context)
	return ret or -1
end

function OnItemUse_UseDragonEgg(user,item,context)
	local ret = luaE_useDragonEgg(user,item,context)
	return ret or -1
end

function OnItemUse_AddSoul(user,item,context)
	local ret = luaE_addSoul(user,item,context)
	return ret or -1
end

function OnItemUse_UseTreasureBox(user,item,context)
	local ret = luaE_useTreasureBox(user,item,context)
	return ret or -1
end

function OnItemUse_UseMagicBook(user,item,context)
	local ret = luaE_useMagicBook(user,item,context)
	return ret or -1
end

function OnItemUse_AddSilver(user,item,context)
	local ret = luaE_addSilver(user,item,context)
	return ret or -1
end

function OnItemUse_UseTreasureMap(user,item,context)
	local ret = luaE_useTreasureMap(user,item,context)
	return ret or -1
end

function OnItemUse_UseRide(user,item,context)
	local ret = luaE_useRide(user,item,context)
	return ret or -1
end

function OnItemUse_UsePet(user,item,context)
	local ret = luaE_usePet(user,item,context)
	return ret or -1
end

function OnItemUse_UseGiftBag(user,item,context)
	local ret = luaE_useGiftBag(user,item,context)
	return ret or -1
end

function OnItemUse_UseDropGiftBag(user,item,context)
	local ret = luaE_useDropGiftBag(user,item,context)
	return ret or -1
end

function OnItemUse_AddMisc(user,item,context)
	local ret = luaE_addMiscItem(user,item,context)
	return ret or -1
end

function OnItemUse_UseBloodBottle(user,item,context)
	local ret = luaE_useBloodBottle(user,item,context)
	return ret or -1
end

function OnItemUse_UseMagicBottle(user,item,context)
	local ret = luaE_useMagicBottle(user,item,context)
	return ret or -1
end

function OnItemUse_AddExp(user,item,context)
	local ret = luaE_addExp(user,item,context)
	return ret or -1
end

function OnItemUse_DragonHorn(user,item,context)
	local ret = luaE_useDragonHorn(user,item,context)
	return ret or -1
end

function OnItemUse_Transport(user,item,context)
	local ret = luaE_transport(user,item,context)
	return ret or -1
end

function OnItemUse_UseBloodHalidom(user,item,context)
	local ret = luaE_useBloodHalidom(user,item,context)
	return ret or -1
end

function OnItemUse_UseExpDan(user,item,context)
	local ret = luaE_useExpDan(user,item,context)
	return ret or -1
end

function OnItemUse_Combine(user,item,context)
	local ret = luaE_combineItem(user,item,context)
	return ret or -1
end

function OnItemUse_AddTempVipLevel(user,item,context)
	local ret = luaE_addTempVipLevel(user,item,context)
	return ret or -1
end

function OnItemUse_AddVipExp(user,item,context)
	local ret = luaE_addVipExp(user,item,context)
	return ret or -1
end

function OnItemUse_Levelup(user,item,context)
	local ret = luaE_levelup(user,item,context)
	return ret or -1
end

function OnItemUse_AddHPMPAndRestoreDragonEne(user,item,context)
	local ret = luaE_addHPMP(user,item,context)
	if user:IsKindOf(CLSID.Human) and user:GetModDragon():HasEquipDragon() then
		user:GetModDragon():AddEquipDragonEne(1024)
	end
	return ret or -1
end

function OnItemUse_UseVigorDan(user,item,context)
	local ret = luaE_useVigorDan(user,item,context)
	return ret or -1
end

function OnItemUse_UseGjfbDan(user,item,context)
	local ret = luaE_useGjfbDan(user,item,context)
	return ret or -1
end

function OnItemUse_UseVipCard(user,item,context)
	local ret = luaE_useVipCard(user,item,context)
	return ret or -1
end

function OnItemUse_AddExpPoint(user,item,context)
	local ret = luaE_addExpPoint(user,item,context)
	return ret or -1
end

function OnItemUse_GiveTitle(user,item,context)
	local ret = luaE_giveTitle(user,item,context)
	return ret or -1
end

function OnItemUse_OpenHeroCardEquipLoc(user,item,context)
	local ret = luaE_openHeroCardEquipLoc(user,item,context)
	return ret or -1
end

function OnItemUse_UseFlag(user,item,context)
	local ret = luaE_useFlag(user,item,context)
	return ret or -1
end
function OnItemUse_UseMagicCircle(user,item,context)
	local ret = luaE_useMagicCircle(user,item,context)
	return ret or -1
end