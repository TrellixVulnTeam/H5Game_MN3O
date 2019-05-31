

----------------------------------------------------------------------
W_LevelRegin	=	{0,			24,		39,		49,		99,		119,		139,		149,		179,		219,		300}-----玩家等级段区间
W_BoxID			=	{48181,		48182,	48183,	48184,	48185,	48186,		48187,		48188,		48189,		48190,	}		----宝箱ID个数与上面等级段对应		----5分钟寿命
W_BoxItemID		=	{100207,	100207,	100207,	100207,	100207,	100207,		100207,		100207,		100207,		100207,	}		----宝箱ID对应的奖励物品ID
W_OneMonterID 	= 	{48202,		48212,	48222,	48232,	48242,	48252,		48262,		48272,		48282,		48292,	}		-----单只怪物的ID与上面等级段对应		----10分钟寿命
W_ManyMonterID 	= 	{48201,		48211,	48221,	48231,	48241,	48251,		48261,		48271,		48281,		48291,	}		-----多只怪物的ID与上面等级段对应		----10分钟寿命
W_ManyMonterNum	=	{3,			3,		4,		4,		4,		5,			5,			5,			5,			5,}				-----随机多只怪事件的怪物数量
W_BuffID 		= 	{61000,	61000,	61010,	61010,	61010,	61020,		61020,		61020,		61020,		61020,}	-------buffID与上面等级段对应
W_DungeonID 	= 	2099		-----副本ID
W_StrInfo 		= 	{41701,41702,41703,41704,}-----若提示信息

-------纯野外非PK区域随机挖宝事件函数，包括所有挖宝事件-----------随机百分比跟数值商定后修改把
function CurrentDungeonScript:W_OpenRand(human)
	math.randomseed(os.time())	--随机种子
	local rand = math.random(1,5)
	if(rand<= 1)then
		self:W_Box(human)
	elseif(rand>1 and rand <=2)then
		self:W_OneMonter(human)
	elseif(rand>2 and rand <=3)then
		self:W_ManyMonter(human)
	elseif(rand>3 and rand <=4)then
		self:W_Buff(human)
	elseif(rand>4 and rand <=5)then
		self:W_Dungeon(human)
	end
end

------PK场景挖宝随机事件函数-----------原因因为PK模式跟静物的阵营之间有冲突不能采集---随机百分比跟数值商定后修改把
function CurrentDungeonScript:W_PKRand(human)
	math.randomseed(os.time())	--随机种子
	local rand = math.random(1,4)
	if(rand<= 1)then
		self:W_OneMonter(human)
	elseif(rand>1 and rand <=2)then
		self:W_ManyMonter(human)
	elseif(rand>2 and rand <=3)then
		self:W_Buff(human)
	elseif(rand>3 and rand <=4)then
		self:W_Dungeon(human)		
	end	
end

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

----刷新静态物体宝箱事件
function CurrentDungeonScript:W_Box(human)
	local Stage = 1
	local HuMan= human:cast('Human')
	local HumLevel = HuMan:GetLevel()
	local HumPos = HuMan:GetPosition()
	local HumOrg = HuMan:GetOrientation()
	for i = 1,#W_LevelRegin-1, 1 do
		if(HumLevel >= W_LevelRegin[i] and HumLevel<= W_LevelRegin[i+1])then
			Stage = i
		end
	end
	self.Stage:CreateStaticObject(HumPos,HumOrg,W_BoxID[Stage],3,"W_Refresh")
	HuMan:Hint(W_StrInfo[1],1000)
end

----刷新一只怪事件
function CurrentDungeonScript:W_OneMonter(human)
	local Stage = 1
	local HuMan= human:cast('Human')
	local HumLevel = HuMan:GetLevel()
	local HumPos = HuMan:GetPosition()
	local HumOrg = HuMan:GetOrientation()
	for i = 1,#W_LevelRegin-1, 1 do
		if(HumLevel >= W_LevelRegin[i] and HumLevel<= W_LevelRegin[i+1])then
			Stage = i
		end
	end
	self.SModCommon:SpawnMonsterAt(HumPos,HumOrg,W_OneMonterID[Stage])
	HuMan:Hint(W_StrInfo[2],1000)
end

----以某点为圆心刷新多只怪事件
function CurrentDungeonScript:W_ManyMonter(human)
	local Stage = 1
	local HuMan= human:cast('Human')
	local HumLevel = HuMan:GetLevel()
	local HumPos = HuMan:GetPosition()
	local HumOrg = HuMan:GetOrientation()
	for i = 1,#W_LevelRegin-1, 1 do
		if(HumLevel >= W_LevelRegin[i] and HumLevel<= W_LevelRegin[i+1])then
			Stage = i
		end
	end
	self.SModCommon:SpawnMonsterRandom(HumPos,2,W_ManyMonterID[Stage],W_ManyMonterNum[Stage])
	HuMan:Hint(W_StrInfo[3],1000)
end

----刷新buff事件
function CurrentDungeonScript:W_Buff(human)
	local Stage = 1
	local HuMan= human:cast('Human')
	local HumLevel = HuMan:GetLevel()
	local HumPos = HuMan:GetPosition()
	local HumOrg = HuMan:GetOrientation()
	for i = 1,#W_LevelRegin-1, 1 do
		if(HumLevel >= W_LevelRegin[i] and HumLevel <= W_LevelRegin[i+1])then
			Stage = i
		end
	end
	HuMan:GetModAura():Create(W_BuffID[Stage])
	HuMan:Hint(W_StrInfo[4],1000)
end

-----进入副本事件
function CurrentDungeonScript:W_Dungeon(human)
	local HuMan= human:cast('Human')
	HuMan:EnterDungeon(W_DungeonID)
end

-----静态物体的箱子被采集,销毁创建的静态物体，给采集的人增加奖励
function CurrentDungeonScript:W_Refresh(staticobj,target)
	if not staticobj:IsInWorld() then 
		return 
	end
	if not target:IsKindOf(CLSID.Human) then
		return
	end
	local HuMan= target:cast('Human')
	local HumLevel = HuMan:GetLevel()
	local Stage = 1
	for i = 1,#W_LevelRegin-1, 1 do
		if(HumLevel > W_LevelRegin[i] and HumLevel<= W_LevelRegin[i+1])then
			Stage = i
		end
	end
	staticobj:LeaveWorld(0)----销毁宝箱	
	local sanbox = MultiItemSandbox.new(HuMan)				
	sanbox:Add(BAG_TYPE,W_BoxItemID[Stage],1,0)
	sanbox:Commit()
end

