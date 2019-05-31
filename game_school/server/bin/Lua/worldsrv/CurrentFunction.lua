--------------------------------
--服务器脚本公用函数
--------------------------------

--关卡开始通用逻辑(启动副本计时器)
function CurrentDungeonScript:G_DungeonStart()
    self.DungeonStartClock = os.time()
end

--关卡结束给奖励逻辑
function CurrentDungeonScript:G_DungeonEnd(timer)
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k , v in pairs(CreatureTab) do
		v:GetModCombat():KillSelf(PET_KILLSELF_SKILLID,PET_KILLSELF_EFFECT)
	end	
	self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"")
	self.MainHuman:CloseHint(0)
	-- self.Stage:GetModDragonTame():DragonTamePrepared(self.MainHuman)	暂时屏蔽
	local clearTime = os.time() - self.DungeonStartClock
	self.SModDungeonScript:CalcScore(clearTime)
end

--关卡结束给奖励逻辑，需要玩家自己点击离开按钮
function CurrentDungeonScript:G_DungeonEnd2(timer)
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k , v in pairs(CreatureTab) do
		v:GetModCombat():KillSelf(PET_KILLSELF_SKILLID,PET_KILLSELF_EFFECT)
	end	
	
	self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"")
	self.MainHuman:CloseHint(0)
	self.Stage:GetModDragonTame():DragonTamePrepared(self.MainHuman)
	local clearTime = os.time() - self.DungeonStartClock
	self.SModDungeonScript:CalcScoreEx(clearTime,false)
end

--boss挑战结算专用函数
function CurrentDungeonScript:G_SingleBossDungeonEnd(timer)
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k , v in pairs(CreatureTab) do
		v:GetModCombat():KillSelf(PET_KILLSELF_SKILLID,PET_KILLSELF_EFFECT)
	end	
	self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"")
	self.MainHuman:CloseHint(0)
	local clearTime = os.time() - self.DungeonStartClock
	self.SModDungeonScript:CalcScoreSingleBossEx(clearTime,true)
end
-- 玩家死亡处理
local DealPoltID = 38
local AutoRealiveDelay = 300
function CurrentDungeonScript:G_InterHumanKilledEvent(human,killer)
	human:CloseHint(0)	--关闭弱提示
	
	self.Stage:GetModObjs():RespawnCreaturesWhenHumanKilled()	--重新刷血球
	
	--[[ 判断是否需要自动复活
	if human:GetLevel() < 10 then
		-- 自动复活阶段1:触发死亡剧本，剧本结束后，自动原地复活
		human:GetModRealive():HideRealiveButton(true)
		self.SModDungeonScript:LaunchPoltEx(DealPoltID,"G_DeadPoltCompleted",false)
	end]]
end
function CurrentDungeonScript:G_DeadPoltCompleted()
	-- 自动复活阶段2:通知客户端做复活表现
	local msg = {}
	self.MainHuman:SendMsg(msgids.SCRealiveEffect,msg)
	
	-- 复活表现结束后自动复活
	self.MainHuman:GetModRealive():Realive(self.MainHuman:GetPosition(), AutoRealiveDelay)
end

--BOSS进战斗出发特效墙，阻挡/////脱战清除
function CurrentDungeonScript:G_BossFightingEvent_EffectW(bossid,effectwall,motionblock)
	self.G_EffectWall = effectwall
	self.G_MotionBlock = motionblock
	SetEventHandler(StageEvents.EnterCombat,"G_BossEnterCombat",{type = bossid})
	SetEventHandler(StageEvents.LeaveCombat,"G_BossLeaveCombat",{type = bossid})
end
function CurrentDungeonScript:G_BossEnterCombat()
	self.Stage:GetModDetour():EnableMotionBlock(self.G_MotionBlock,false)
	self.Stage:GetModDetour():EnableBlockEffects(self.G_EffectWall,true)	--打开特效墙
end
function CurrentDungeonScript:G_BossLeaveCombat()
	self.Stage:GetModDetour():EnableMotionBlock(self.G_MotionBlock,true)
	self.Stage:GetModDetour():EnableBlockEffects(self.G_EffectWall,false)	--打开特效墙
end



