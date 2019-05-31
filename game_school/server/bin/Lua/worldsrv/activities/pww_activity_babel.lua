----------------------------------------------------------------------
--GetModBabel():GetCurrLv()			获取当前层数
--GetModBabel():OnWaveStart(level)	开始战斗时调用
--GetModBabel():OnWaveEnd(level)	结束战斗时调用
-- local msg = { section = 1或2}    1:通过当前层数到达传送门后发送 2:延迟1s并瞬移主角后发送
-- self.MainHuman:SendMsg(msgids.SCBabelSwitchAnim,msg)
----------------------------------------------------------------------
CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
pwngs_require("./Lua/worldsrv/activities/pww_activity_babel_data.lua")
-----------------------------------------------------------


-----------------------------------------------------------
--副本变量
-----------------------------------------------------------
CurrentDungeonScript.CurrLv = 1			--层数
CurrentDungeonScript.CurrWave = 1		--当前层刷小怪的波数
CurrentDungeonScript.CurrMagicCnt = 0	--当前出招次数
CurrentDungeonScript.DungenEnd = 0		--副本通关与否
CurrentDungeonScript.GuideNpc = nil		--指引NPC
CurrentDungeonScript.R1L5Boss = nil		--5层boss特殊处理
CurrentDungeonScript.CurrLevelFightActive = false --用于防止网络卡时多次刷怪


-----------------------------------------------------------
--副本开启与关闭
-----------------------------------------------------------
function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()
	self.SModCommon = self.Stage:GetModCommon()
	
	SetEventHandler(StageEvents.HumanEnter,			"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,			"HumanLeaveEvent")
    SetEventHandler(StageEvents.CreatureKilled,		"CreatureKilled")
    SetEventHandler(StageEvents.HumanKilled,		"HumanKilled")
	SetEventHandler(StageEvents.CreatureMagicHit,	"CreatureMagicHit")
end

function CurrentDungeonScript:Cleanup()
end


-----------------------------------------------------------
--玩家进入与离开,死亡与复活
-----------------------------------------------------------
function CurrentDungeonScript:HumanEnterEvent(human)
	human:GetModMotionMaster():ChangePosition(BabelConfig.PlayerEnterPos)
	human:GetModMotionMaster():ChangeOrientation(BabelConfig.PlayerEnterOra)
	self.CurrLv = self.MainHuman:GetModBabel():GetCurrLv()
	self:SpawnGuideNpc()
	self.MainHuman:GetModBabel():UpdateBabel(self.CurrLv)	--通知服务器刷新场景
	self.Stage:GetModDetour():EnableMotionBlock(1,true)
	self.Stage:GetModDetour():EnableMotionBlock(0,true)

	local Sceneid = toint32(self.Stage:GetBaseMapID())
	self.MonsterInfo = BabelConfig.MonsterTable[Sceneid]
	self.PrizeInfo	 = BabelConfig.PrizeTable[Sceneid]
end

function CurrentDungeonScript:HumanLeaveEvent(human)
    human:GetModBabel():SetGuideNpcStatu(BabelConfig.GUIDE_NPC_WAIT)
	self.Stage:GetModDungeonScript():Cleanup()	--*玩家离开场景清空所有剧情相关逻辑，以免出问题
end

function CurrentDungeonScript:HumanKilled(human,killer)
	human:GetModRealive():HideRealiveButton(true)
	self.SModDungeonScript:CreateTimer(6,"Timer_Realive")
	self.MainHuman:GetModBabel():SetGuideNpcStatu(BabelConfig.GUIDE_NPC_WAIT)
	self.MainHuman:SendNotifyMsg( 50301, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM)
	self.MainHuman:GetModBabel():SendBabelResult(0)
end

function CurrentDungeonScript:Timer_Realive()
	self.MainHuman:GetModRealive():Realive(self.MainHuman:GetPosition(), 0)
	self.MainHuman:LeaveDungeon()
end

-----------------------------------------------------------
--初始化场景
-----------------------------------------------------------
function CurrentDungeonScript:SpawnGuideNpc()                                             --去除npc显示，进入2s后直接开始
	--self.GuideNpc = self.SModCommon:SpawnMonsterAt(BabelConfig.GuideNpcPos, BabelConfig.GuideNpcOra, BabelConfig.GuideNpcType)
	--if self.MainHuman:GetModBabel():GetGuideNpcStatu() == BabelConfig.GUIDE_NPC_WAIT then
	--	self.MainHuman:SendNotifyMsg( 50312, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM)
	--	return
	--end
	self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(3))
	self.SModCommon:CreateTimer(3, "OnFightBegin")
end

--function CurrentDungeonScript:OnSelectStart()
	--self.MainHuman:GetModBabel():SetGuideNpcStatu(BabelConfig.GUIDE_NPC_VISIT)
	--self:OnFightBegin()
--end

function CurrentDungeonScript:OnFightBegin()	--进场XX时间后开始刷怪

	--防止网络卡的情况多次刷怪
	if self.CurrLevelFightActive then
		pwdist.log(self.MainHuman:GetName() .. ',Fight already begin')
		return
	end
	self.CurrLevelFightActive = true
	
	self.SModDungeonScript:PlotStart()	
	if self.CurrLv <= #self.MonsterInfo then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(41597))			--文字提示：开始挑战
		self.Stage:GetModObjs():SuspendCreaturesAI()
		self:SpawnMonster()
		self.Stage:GetModObjs():ResumeCreaturesAI()
		self:SendClientHint()
	end	
	self.SModDungeonScript:PlotClean()
	self.MainHuman:GetModBabel():OnWaveStart(self.CurrLv)	--通知服务器战斗开始
	
end
		
function CurrentDungeonScript:SendClientHint()
	if #self.MonsterInfo[self.CurrLv]["time_nodes"] > 0 then
		local param = ''
		for i = 2, #self.MonsterInfo[self.CurrLv]["time_nodes"], 1 do
			param = param..self.MonsterInfo[self.CurrLv]["time_nodes"][i]
			if i ~= #self.MonsterInfo[self.CurrLv]["time_nodes"] then
				param = param..','
			end
		end
		self.MainHuman:GetModBabel():SendLevelPeriod(param)

		for i = 1, 3, 1 do
			local time_node = self.MonsterInfo[self.CurrLv]["time_nodes"][i]
			local timerid = self.SModCommon:CreateTimer(time_node, "TimerSendNodes")
			self.SModCommon:SetTimerContext(timerid,{ time_node} )
		end

		self.MainHuman:GetModBabel():SendWaveAim(self.MonsterInfo[self.CurrLv]["aim"])
		self.MainHuman:GetModBabel():SendBabelPrizeTips(BabelConfig.PrizeHints)
	end

	self.MainHuman:SendNotifyMsg( 50303, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM, self.MainHuman:GetName(), self.MainHuman:GetID(), 0, self.MonsterInfo[self.CurrLv]["npc_name"] )
	self.SModDungeonScript:CreateTimer(4,"TimerHintAim")	
end
	
function CurrentDungeonScript:TimerSendNodes(timerid)
	local time_node = pwdist.unpack(self.SModCommon:GetTimerContext(timerid))
	self.MainHuman:GetModBabel():SendUsedTime(time_node)
end

function CurrentDungeonScript:TimerHintAim()
	self.MainHuman:Hint(self.MonsterInfo[self.CurrLv]["aim"],1000)
end


-----------------------------------------------------------
--怪物生成
-----------------------------------------------------------
function CurrentDungeonScript:SpawnMonster()
	self.CurrLv = self.MainHuman:GetModBabel():GetCurrLv()
	self.CurrWave = 1
	--1.boss
	self:SpawnCommonCreature(self.MonsterInfo[self.CurrLv]["boss_type"])	
	--需要特殊生成的boss	
	self:SpawnR1L5Boss()

	--2.monster
	self:SpawnCommonCreature(self.MonsterInfo[self.CurrLv]["monster_table"][1])

	--3.copy monster
	self:SpawnCopyMonster()
end

function CurrentDungeonScript:CreatureAddBuffs(creature, buffs, overlap)
	if buffs == nil then
		return;
	end

	if #buffs < 1 then
		return;
	end

	for i = 1, #buffs, 1 do
		if not creature:GetModAura():Exists(buffs[i]) then
			creature:GetModAura():Create(buffs[i])
		elseif overlap then
			creature:GetModAura():Create(buffs[i])
		end
	end
end

--[22741] = { ["cnt"] = 2, ["buffs"] = {}, ["pos"]={12,13}, ["r"]=1,},
--[22742] = { ["cnt"] = 16, ["buffs"] = {}, ["pos"]={9,8,18,19}, ["r"]=1,},
function CurrentDungeonScript:SpawnCommonCreature( param )

	if param == nil then
		return
	end

	for k, v in pairs(param) do
		local j = 1
		creature_type		= k
		creature_cnt		= v["cnt"]
		creature_buffs		= v["buffs"]
		creature_poslist	= v["pos"]
		creature_pos_r		= v["r"]
		for i = 1, creature_cnt, 1 do
			pos_info = BabelConfig.MonsterPosition[creature_poslist[j]]
			if pos_info ~= nil then
				pos = pos_info[1]
				ora = pos_info[2]
				self.SModDungeonScript:SpawnMonsterOriRandom(pos, ora, creature_pos_r, creature_type, 1)
				if creature_buffs ~= nil then
					local creature_tab = self.Stage:GetModAOI():CollectCreatureInStage(creature_type)
					for k2,v2 in pairs(creature_tab) do
						self:CreatureAddBuffs(v2, creature_buffs, false)
					end
				end
			end

			if j < #creature_poslist then
				j = j + 1
			else
				j = 1
			end
		end
	end	--end param loop
	
end

function CurrentDungeonScript:SpawnCopyMonster()
	local copy_num = self.MonsterInfo[self.CurrLv]["copy_num"]
	local copy_cd  = self.MonsterInfo[self.CurrLv]["copy_cd"]
	if copy_num == nil then
		return
	end
	
	if copy_num >=2 then
		self.SpawnCopyMonsterFinish = false	
	end
	
	for i = 2,copy_num, 1 do 
		local timerid = self.SModCommon:CreateTimer(copy_cd * i, "TimerSpawnCopyMonster")
		self.SModCommon:SetTimerContext(timerid,{ self.CurrLv, self.CurrWave, i, copy_num } )
	end	
end

function CurrentDungeonScript:TimerSpawnCopyMonster(timerid)
	local lv,wave,copy_index,copy_num = pwdist.unpack(self.SModCommon:GetTimerContext(timerid))
	self:SpawnCommonCreature(self.MonsterInfo[self.CurrLv]["monster_table"][copy_index])
	if copy_index == copy_num then
		self.SpawnCopyMonsterFinish = true
	end
end

function CurrentDungeonScript:SpawnWaveMonster()
	self.CurrLv = self.MainHuman:GetModBabel():GetCurrLv()
	if self.MonsterInfo[self.CurrLv]["win_param"] - self.CurrWave-1 > 0 then
		self.MainHuman:SendNotifyMsg( 50307, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM, self.CurrWave+1, self.MonsterInfo[self.CurrLv]["win_param"] - self.CurrWave-1 )
	else
		self.MainHuman:SendNotifyMsg( 50313, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM)
	end
	self.CurrWave = self.CurrWave + 1
	if self.CurrWave <= self.MonsterInfo[self.CurrLv]["win_param"] then
		self:SpawnCommonCreature(self.MonsterInfo[self.CurrLv]["monster_table"][self.CurrWave])
	end
end

function CurrentDungeonScript:IsR1L5()
	if self.MainHuman:GetModBabel():GetRankID() == 3 and self.CurrLv == 5 then
		return true
	end	
	return false
end

function CurrentDungeonScript:IsR1L5_new()
	if self.MainHuman:GetModBabel():GetRankID() == 1 and self.CurrLv == 5 then
		return true
	end	
	return false
end

function CurrentDungeonScript:SpawnR1L5Boss() 
	if self:IsR1L5() == true then 
		self.R1L5Boss = self.SModCommon:SpawnMonsterAt(BabelConfig.R1L5Boss["pos"], BabelConfig.R1L5Boss["ora"], BabelConfig.R1L5Boss["type"])	
		self.R1L5Boss:Talk(50365)
		self.SModCommon:CreateTimer(3, "R1L5WaveHint")
	end
end


-----------------------------------------------------------
--战斗处理
-----------------------------------------------------------
function CurrentDungeonScript:CreatureKilled(creature,killer, hurttype)	--场景怪物被杀事件
	local monster_type = creature:GetCreatureType()
	local win_type = self.MonsterInfo[self.CurrLv]["win_type"]
	local finish = false

	if self.MonsterInfo[self.CurrLv]["copy_num"] ~= nil and self.SpawnCopyMonsterFinish == false then
		return
	end
	
	if win_type == BabelConfig.WIN_TYPE_KILLALL  or win_type == BabelConfig.WIN_TYPE_KILLCNT  or win_type == BabelConfig.WIN_TYPE_KILLNOINJURE then
		if self:IsAllDead() then
			finish = true
		end

	elseif win_type == BabelConfig.WIN_TYPE_KILLBOSS then
		if monster_type == self:GetKeys(self.MonsterInfo[self.CurrLv]["boss_type"])[1] then
			self:KillLeftMonster()
			finish = true
		end

	elseif win_type == BabelConfig.WIN_TYPE_KILLBYSKILL then
		if hurttype ~= self.MonsterInfo[self.CurrLv]["win_param"] then
			self.MainHuman:GetModStatistic():SetHP(0.0)
		elseif self:IsAllDead() then
			finish = true
		end

	elseif win_type == BabelConfig.WIN_TYPE_KILLBYWAVE then
		local dead = self:IsAllConfigTypeDead(self:GetKeys(self.MonsterInfo[self.CurrLv]["monster_table"][self.CurrWave]))
		if dead then
			if self.CurrWave < self.MonsterInfo[self.CurrLv]["win_param"] then
				self:SpawnWaveMonster()
				self:R1L5WaveHint()
			else
				finish = true
				if self:IsR1L5() then
					self:R1L5BossRun()
					self.SModDungeonScript:CreateTimer(3,"KillLeftMonster")
				else
					self:KillLeftMonster()
				end
			end
		end
	
	elseif win_type == BabelConfig.WIN_TYPE_KILLBYWAVE_LIVE then
		--local cnt = self:GetAliveMonsterCnt(self:GetKeys(self.MonsterInfo[self.CurrLv]["monster_table"][self.CurrWave]))
		local cnt = self:GetAliveMonsterCntInStage()
		if cnt == 0 and self.CurrWave == self.MonsterInfo[self.CurrLv]["win_param"] then
			finish = true
			self:KillLeftMonster()
		elseif cnt <= self.MonsterInfo[self.CurrLv]["live_num"][self.CurrWave] then
			self:SpawnWaveMonster()
		end
	end

	if finish then
		self.CurrLevelFightActive = false
		self.MainHuman:GetModBabel():OnWaveEnd(self.CurrLv)
		self.SModDungeonScript:CreateTimer(DUNGEON_END_TIME,"TimerFightEnd")
		self.MainHuman:GetModBabel():SendBabelResult(1)
		if self.CurrLv == #self.MonsterInfo then
			self:TriggerRankUpdate()
		end
	end
end

function CurrentDungeonScript:R1L5WaveHint()
	if self:IsR1L5() == true and self.R1L5Boss ~= nil then
		if self.CurrWave == 1 then
			self.R1L5Boss:Talk(50366)
		elseif self.CurrWave == 2 then
			self.R1L5Boss:Talk(50367)
		elseif self.CurrWave == 3 then
			self.R1L5Boss:Talk(50368)
		elseif self.CurrWave == 4 then
			self.R1L5Boss:Talk(50369)
		elseif self.CurrWave == 5 then
			self.R1L5Boss:Talk(50370)
		end		
	end
end

function CurrentDungeonScript:R1L5BossRun()
	self.R1L5Boss:Talk(50371)
	self.R1L5Boss:GetModMotionMaster():NavigatePosition(BabelConfig.R1L5Boss["target"],"OnR1L5BossRun")
end

function CurrentDungeonScript:OnR1L5BossRun()
	self.R1L5Boss:LeaveWorld(0)
end

function CurrentDungeonScript:IsAllDead( )
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k,v in pairs(CreatureTab) do
		if v:IsDead() == false then
			return false
		end
	end
	return true
end

function CurrentDungeonScript:IsAllConfigTypeDead( param )
	for i = 1, #param, 1 do
		local creatureTab = self.Stage:GetModAOI():CollectCreatureInStage(param[i])
		for k , v in pairs(creatureTab) do
			if v:IsDead() == false then
				return false
			end
		end
	end
	return true
end

function CurrentDungeonScript:GetAliveMonsterCnt( param )
	local cnt = 0
	for i = 1, #param, 1 do
		local creatureTab = self.Stage:GetModAOI():CollectCreatureInStage(param[i])
		for k , v in pairs(creatureTab) do
			if not v:IsDead() then
				cnt = cnt + 1
			end
		end
	end
	return cnt
end

function CurrentDungeonScript:GetAliveMonsterCntInStage()
    local cnt = 0
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	
	if CreatureTab == nil then
		return cnt
	end
	
	for k , v in pairs(CreatureTab) do
			if not v:IsDead() then
				cnt = cnt + 1
			end
		end
	return cnt
end

function CurrentDungeonScript:KillLeftMonster()
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k , v in pairs(CreatureTab) do
		v:LeaveWorld(0)
	end
end

function CurrentDungeonScript:GetKeys(t)
	local keys = {}
	for k,v in pairs(t) do
		table.insert(keys, k)
	end
	return keys
end

function CurrentDungeonScript:CreatureMagicHit(sourcer,target)	--场景怪物打击触发
	if sourcer:IsKindOf(CLSID.Human) and self.MonsterInfo[self.CurrLv]["win_type"] == BabelConfig.WIN_TYPE_KILLCNT then
		self.CurrMagicCnt = self.CurrMagicCnt + 1
		if self.CurrMagicCnt >= self.MonsterInfo[self.CurrLv]["win_param"] then
			self.SModDungeonScript:CreateTimer(1,"OnMagicHitCntFull")
		end
	end

	if target:IsKindOf(CLSID.Human) and self.MonsterInfo[self.CurrLv]["win_type"] == BabelConfig.WIN_TYPE_KILLNOINJURE then
		self.MainHuman:GetModStatistic():SetHP(0.0)
	end
	
	if self:IsR1L10() and target:IsKindOf(CLSID.Monster) then
		local creature = target:cast('Creature')
		if creature ~= nil and creature:GetCreatureType() == BabelConfig.R1L10BossType then
			self:R1L10BossAddBuff()
		end
	end
end

function CurrentDungeonScript:OnMagicHitCntFull()
	if not self:IsAllDead() then
		self.MainHuman:GetModStatistic():SetHP(0.0)
	end
end

function CurrentDungeonScript:IsR1L10()                                            --判断是否为1阶10层
	if self.MainHuman:GetModBabel():GetRankID() == 1 and self.CurrLv == 10 then
		return true
	end	
	return false
end

function CurrentDungeonScript:IsR2L10()                                            --判断是否为2阶10层，为20664号任务进行特殊处理
	if self.MainHuman:GetModBabel():GetRankID() == 2 and self.CurrLv == 10 then
		return true
	end	
	return false
end

function CurrentDungeonScript:IsQuest20664()                                        --判断玩家是否处于20664号任务下
	if self.MainHuman:GetModQuest():GetQuestStatus(20664) == 3 then
		return true
	end	
	return false
end

function CurrentDungeonScript:R1L10BossAddBuff()
	local creature_tab = self.Stage:GetModAOI():CollectCreatureInStage(BabelConfig.R1L10MonsterType)
	for k,v in pairs(creature_tab) do
		self:CreatureAddBuffs(v, BabelConfig.R1L10BossBuff, true)
	end
end

function CurrentDungeonScript:IsR1L15()
	if self.MainHuman:GetModBabel():GetRankID() == 1 and self.CurrLv == 15 then
		return true
	end	
	return false
end

-----------------------------------------------------------
--战斗结束处理
-----------------------------------------------------------
function CurrentDungeonScript:TimerFightEnd()
	self:GivePrize()
	flag =false
	if self:IsR2L10() and self:IsQuest20664() then
	     flag = true
	end
	if self.CurrLv ~= #self.MonsterInfo  and not self:IsR1L5_new() and not flag then
	    self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(5))
		self.SModDungeonScript:CreateTimer(6,"DungeonHandle")
	end
end

function CurrentDungeonScript:GivePrize()
	local second = self.MainHuman:GetModBabel():GetLevelTimeConsume()
	local level = 3
	if #self.MonsterInfo[self.CurrLv]["time_nodes"] >= 3 then
		if second <= toll(self.MonsterInfo[self.CurrLv]["time_nodes"][2]) then
			self.MainHuman:SendNotifyMsg( 50306, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM, self.MainHuman:GetName(), self.MainHuman:GetID(), 0 )
			level = 1
		elseif second <= toll(self.MonsterInfo[self.CurrLv]["time_nodes"][3]) then
			self.MainHuman:SendNotifyMsg( 50305, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM, self.MainHuman:GetName(), self.MainHuman:GetID(), 0 )
			level = 2
		else
			self.MainHuman:SendNotifyMsg( 50304, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM, self.MainHuman:GetName(), self.MainHuman:GetID(), 0 )
			level = 3
		end
	else
		self.MainHuman:SendNotifyMsg( 50302, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM)
	end
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(41596))
	for i = 1, #self.PrizeInfo[self.CurrLv], 1 do
		if level <= i then
			self.MainHuman:GetModBabel():DropPrize(self.PrizeInfo[self.CurrLv][i], self.MainHuman:GetPosition(), BabelConfig.PrizeR)
		end
	end	
end

--function CurrentDungeonScript:ShowTransport()                                                                     --不再显示传送点
		--self.GuideNpc:Talk(50307)
		--self.staticobj = self.Stage:CreateStaticObject(BabelConfig.TransportPos,BabelConfig.TransportOra,BabelConfig.TransportType, BabelConfig.TransportDistance,"OnTriggerTransport")
--end

function CurrentDungeonScript:DungeonHandle()	--触发器
	self.MainHuman:GetModMotionMaster():StopMotion()
	--self.GuideNpc:LeaveWorld(0)
	--self.staticobj:LeaveWorld(0)
	self.Stage:GetModObjs():ClearItemCharacter()		--清除场景内掉落
	self.Stage:GetModObjs():ClearBreakableObject()		--清除场景内可破坏物（箱子）
	self.Stage:GetModObjs():ClearTrap()
	self.Stage:GetModObjs():ClearPuppet()
	self.MainHuman:CloseHint(0)
	local msg = { section = 1, clear_objs = true}
	self.MainHuman:SendMsg(msgids.SCBabelSwitchAnim,msg)	--发消息，播放第一个客户端UI
	self.SModDungeonScript:CreateTimer(1,"TimerPlotNextDungeon")	--1秒后播放第二个表现
end

function CurrentDungeonScript:TimerPlotNextDungeon()
	self:HumanEnterEvent(self.MainHuman)	--重新执行角色进场
	local msg = { section = 2, clear_objs = true}
	self.MainHuman:SendMsg(msgids.SCBabelSwitchAnim,msg)--发消息，播放第二个客户端UI
end


-----------------------------------------------------------
--升阶处理
-----------------------------------------------------------
function CurrentDungeonScript:TriggerRankUpdate()
	local result = self.MainHuman:GetModBabel():IsAllowUpgradeRank()
	if result == 0 then
		self.MainHuman:SendNotifyMsg( 50309, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM, self.MainHuman:GetModBabel():GetRankID() )
		--self.GuideNpc:Talk(50309)
		self.Stage:GetModCommon():ClientOperationDialog(self.MainHuman, 50309, "OnSelectUpdateRank")
	else
		self.MainHuman:SendNotifyMsg( 50308, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM, self.MainHuman:GetModBabel():GetRankID() )
		if self.MainHuman:GetModBabel():GetRankID() == 1 then
			self.MainHuman:SendNotifyMsg( 50315, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM )
			self.MainHuman:SendNotifyMsg( 50316, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM )
		end
		self.MainHuman:SendNotifyMsg( 50311, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM )
		self.SModDungeonScript:CreateTimer(3,"RankUpdateOperHint")
	end
end

function CurrentDungeonScript:RankUpdateOperHint()
	self.MainHuman:SendNotifyMsg( 50312, CHAT_MODE_GUIDE, CHAT_TEXT_SYSTEM )
end

function CurrentDungeonScript:OnSelectUpdateRank(human, option)
	if option == 0 then
		local result = self.MainHuman:GetModBabel():UpgradeRank()
		if result == 0 then
			self.SModDungeonScript:CreateTimer(3,"DungeonRankHandle")
		else
			self.MainHuman:SendNotifyMsg( result, CHAT_MODE_PROMPT_NORMAL, CHAT_TEXT_SYSTEM)
		end
	end
end

--function CurrentDungeonScript:ShowRankTransport()
		--self.GuideNpc:Talk(50307)
		--self.staticobj = self.Stage:CreateStaticObject(BabelConfig.TransportPos,BabelConfig.TransportOra,BabelConfig.TransportType, BabelConfig.TransportDistance,"OnTriggerRankTransport")
--end

function CurrentDungeonScript:DungeonRankHandle()	--下一阶触发器
	self.MainHuman:GetModMotionMaster():StopMotion()
	--self.GuideNpc:LeaveWorld(0)
	--self.staticobj:LeaveWorld(0)
	self.Stage:GetModObjs():ClearItemCharacter()		
	self.Stage:GetModObjs():ClearBreakableObject()	
	self.Stage:GetModObjs():ClearTrap()	
	self.Stage:GetModObjs():ClearPuppet()
	self.MainHuman:CloseHint(0)
	local msg = { section = 1, clear_objs = true}
	self.MainHuman:SendMsg(msgids.SCBabelSwitchAnim,msg)	
	self.SModDungeonScript:CreateTimer(1,"TimerPlotNextRank")	
end

function CurrentDungeonScript:TimerPlotNextRank()
	self.MainHuman:GetModBabel():Enter()	
	local msg = { section = 2, clear_objs = true}
	self.MainHuman:SendMsg(msgids.SCBabelSwitchAnim,msg)
end






