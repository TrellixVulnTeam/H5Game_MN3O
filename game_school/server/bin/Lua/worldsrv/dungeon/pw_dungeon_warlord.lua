CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------

-----------------------------------------------------------
--副本变量
-----------------------------------------------------------

CurrentDungeonScript.EnemyPlayer = nil	--当前被挑战者(角色)
CurrentDungeonScript.EnemyMonster = nil	--当前被挑战者(怪物)
CurrentDungeonScript.Player = nil		--挑战者
CurrentDungeonScript.ChallengeStart = false							--挑战开始标识
CurrentDungeonScript.Prepare_time = 3								--PK准备时间
CurrentDungeonScript.PK_time = 90									--PK时间
CurrentDungeonScript.Hold_buff = 102								--定身buff
CurrentDungeonScript.Challenge_timer = nil							--超时定时器
CurrentDungeonScript.timer_1sec = nil								--每秒定时器(检测血量)
CurrentDungeonScript.timer_hpcd = nil								--30秒定时器(血瓶CD)
-- CurrentDungeonScript.Enemy_buff = 50020								--被挑战者buffID
CurrentDungeonScript.HP_percent = 30								--使用血瓶生命比例
CurrentDungeonScript.HP_cd = 30										--使用血瓶cd

--角色复活坐标
CurrentDungeonScript.Relive_pos = 
								{
									["loc"] = {49.9,61.99,49.9},
									["dir"] = {-0.3,0.0,-0.9},
								}
--PK挑战者坐标
CurrentDungeonScript.Player_pos = 
								{
									["loc"] = {49.9,61.99,49.9},
									["dir"] = {-0.3,0.0,-0.9},
								}
--PK被挑战者坐标
CurrentDungeonScript.Enemy_pos = 
								{
									["loc"] = {45.1,61.99,45.7},
									["dir"] = {0.3,0.0,0.9},
								}



local QuestID = {1403}--------------主线进场景完成的任务ID		
local ZhiXianQuestID = {10094,10001}	-----任务ID，和任务怪ID						
-----------------------------------------------------------
--副本开启与关闭
-----------------------------------------------------------
function CurrentDungeonScript:Startup()
	self.SModDungeonScript = self.Stage:GetModDungeonScript()
	self.SModCommon = self.Stage:GetModCommon()
	
	SetEventHandler(StageEvents.HumanEnter, "HumanEnter")
	SetEventHandler(StageEvents.HumanLeave, "HumanLeave")
	SetEventHandler(StageEvents.HumanKilled, "HumanKilled")
	SetEventHandler(StageEvents.CreatureKilled, "CreatureKilled")
	
	pwdist.log('init..........')
end

function CurrentDungeonScript:Cleanup()
	pwdist.log('CurrentDungeonScript : Cleanup')
end

-----------------------------------------------------------
-- 事件：玩家进入与离开、死亡
-----------------------------------------------------------
function CurrentDungeonScript:HumanEnter(human)
	if(human ~= nil)then
		local LHuMan= human:cast('Human')
		for t = 1, #QuestID,1 do
			if LHuMan:GetModQuest():GetQuestStatus(QuestID[t]) == 2 then
				LHuMan:GetModQuest():DoneQuest(QuestID[t])
			end		
		end
	end		
	local HuMan= human:cast('Human')
		-----新手流程用到的内容，脚本写个实现任务想要实现的内容
	if HuMan:GetModQuest():GetQuestStatus(ZhiXianQuestID[1]) == 2 then
		HuMan:GetModQuest():InjectCreatureKilled(ZhiXianQuestID[2])	
-- pwdist.log('更新次数')
	end	
	if self.Player == nil then
		self.Player = human
		
		-- 挑战者处理
		self.Player:GetModWarlord():OnCombatStart(0)
		-- 传送
		self.Player:GetModMotionMaster():ChangePosition(self.Player_pos["loc"])
		self.Player:GetModMotionMaster():ChangeOrientation(self.Player_pos["dir"])
		-- 满血魔
		self.Player:GetModStatistic():SetPercentHP(1)
		self.Player:GetModStatistic():SetPercentMP(1)
		-- 定身
		self.Player:GetModAura():Create(self.Hold_buff)
		
		return
	end

	pwdist.log('HumanEnter end')
end

function CurrentDungeonScript:HumanLeave(human)
	pwdist.log('HumanLeave:')
	
	if self.Player ~= nil then
		-- self:OnChallengeFail()
	
		-- 结束
		self.Player:GetModWarlord():OnCombatEnd()
		self.Player = nil
		
	end
	
end

function CurrentDungeonScript:HumanKilled(human,killer)
	if self.Player == nil then
		return
	end
	
	-- 战斗结束后玩家死亡
	if human:GetID() == self.Player:GetID() then
		self.Player:GetModRealive():HideRealiveButton(true)
	end
	-- 战斗已结束 不处理
	if self.ChallengeStart == false then
		return
	end
	
	if human:GetID() == self.Player:GetID() then
		-- 挑战失败
		self.ChallengeStart = false
		if self.Challenge_timer ~= nil then
			self.SModDungeonScript:CancelTimer(self.Challenge_timer)
			self.Challenge_timer = nil
		end
	
		self:OnChallengeFail()
	elseif self.EnemyPlayer ~= nil and human:GetID() == self.EnemyPlayer:GetID() then
		-- 挑战成功
		self.ChallengeStart = false
		if self.Challenge_timer ~= nil then
			self.SModDungeonScript:CancelTimer(self.Challenge_timer)
			self.Challenge_timer = nil
		end

		self:OnChallengeSucc()
	end
	
	-- 自己定身
	if self.Player:GetModAura():Exists(self.Hold_buff) == false then
		self.Player:GetModAura():Create(self.Hold_buff)
	end
	
	-- 对手定身
	if self.EnemyMonster ~= nil and self.EnemyMonster:GetModAura():Exists(self.Hold_buff) == false then
		self.EnemyMonster:GetModAura():Create(self.Hold_buff)
	end
	
	if self.EnemyPlayer ~= nil and self.EnemyPlayer:GetModAura():Exists(self.Hold_buff) == false then
		self.EnemyPlayer:GetModAura():Create(self.Hold_buff)
	end
end

function CurrentDungeonScript:CreatureKilled(creature,killer,hurtType)
	if self.Player == nil then
		return
	end
	
	-- 战斗已结束 不处理
	if self.ChallengeStart == false then
		return
	end
	
	-- 挑战失败
	self.ChallengeStart = false
	if self.Challenge_timer ~= nil then
		self.SModDungeonScript:CancelTimer(self.Challenge_timer)
		self.Challenge_timer = nil
	end
	-- 定身
	if self.Player:GetModAura():Exists(self.Hold_buff) == false then
		self.Player:GetModAura():Create(self.Hold_buff)
	end

	self:OnChallengeSucc();
end

-----------------------------------------------------------
--挑战相关 开始挑战
-----------------------------------------------------------
-- 挑战角色
function CurrentDungeonScript:StartChallengeHuman(human)
	if self.Player == nil then
		return
	end
	
	if self.ChallengeStart == true then
		return
	end
	
	if human ~= nil then
		self.EnemyPlayer = human
		
		-- 被挑战者处理
		self.EnemyPlayer:GetModWarlord():OnCombatStart(self.Player:GetModCombatPoint():GetCombatPoint())
		-- 传送
		self.EnemyPlayer:GetModMotionMaster():ChangePosition(self.Enemy_pos["loc"])
		self.EnemyPlayer:GetModMotionMaster():ChangeOrientation(self.Enemy_pos["dir"])
		-- 被挑战者满血魔
		self.EnemyPlayer:GetModStatistic():SetPercentHP(1)
		self.EnemyPlayer:GetModStatistic():SetPercentMP(1)
		-- 定身
		self.EnemyPlayer:GetModAura():Create(self.Hold_buff)
		
		-- 通知客户端
		local msg = { result = 0, wid = self.EnemyPlayer:GetID(), prepare_second = self.Prepare_time, pk_second = self.PK_time}
		self.Player:SendMsg(msgids.SCWarlordStart,msg)
		-- PK前准备
		self.ChallengeStart = true
		self.SModCommon:CreateTimer(self.Prepare_time, "OnChallengeStart")
	end
end

-- 挑战怪物
function CurrentDungeonScript:StartChallengeMonster(creature)

	if self.ChallengeStart == true then
		return
	end
	
	if creature ~= nil then
		self.EnemyMonster = creature
		-- 传送
		self.EnemyMonster:GetModMotionMaster():ChangePosition(self.Enemy_pos["loc"])
		self.EnemyMonster:GetModMotionMaster():ChangeOrientation(self.Enemy_pos["dir"])
		
		-- 定身
		self.EnemyMonster:GetModAura():Create(self.Hold_buff)
		
		self.SModCommon:CreateTimer(1, "OnStartChallengeMonster")
	end
	
	pwdist.log('StartChallengeMonster')
end

function CurrentDungeonScript:OnStartChallengeMonster()

	if (self.Player == nil) or (self.EnemyMonster == nil) then
		return
	end
	
	-- 通知客户端
	local msg = { result = 0, wid = self.EnemyMonster:GetID(), prepare_second = self.Prepare_time, pk_second = self.PK_time}
	self.Player:SendMsg(msgids.SCWarlordStart,msg)
	
	pwdist.log('SCWarlordStart')
	
	-- PK前准备
	self.ChallengeStart = true
	self.SModCommon:CreateTimer(self.Prepare_time, "OnChallengeStart")
	
end

function CurrentDungeonScript:OnChallengeStart()
	if self.Player == nil then
		return
	end
	
	-- 解除定身
	if self.Player:GetModAura():Exists(self.Hold_buff) then
		self.Player:GetModAura():DeleteSync(self.Hold_buff)
	end
	
	if self.EnemyPlayer ~= nil then
		-- 解除定身
		if self.EnemyPlayer:GetModAura():Exists(self.Hold_buff) then
			self.EnemyPlayer:GetModAura():DeleteSync(self.Hold_buff)
		end
		-- 被挑战者开始AI
		self.EnemyPlayer:ChangeFaction(2)
		self.EnemyPlayer:StartAI()
		self.EnemyPlayer:AddThreat(self.Player)
		-- PK计时
		self.Challenge_timer = self.SModDungeonScript:CreateTimer(self.PK_time,"OnChallengeTimeout")
	elseif self.EnemyMonster ~= nil then
	
		-- 解除定身
		if self.EnemyMonster:GetModAura():Exists(self.Hold_buff) then
			self.EnemyMonster:GetModAura():DeleteSync(self.Hold_buff)
		end
		
		-- 被挑战者开始AI
		self.EnemyMonster:ChangeFaction(2)

		-- PK计时
		self.Challenge_timer = self.SModDungeonScript:CreateTimer(self.PK_time,"OnChallengeTimeout")
	end
	
	--副本倒计时
	local msg = { targetlist = {} }
	msg.timesec = self.PK_time
	self.Player:SendMsg(msgids.SCDungeonTargetList, msg)
end

-----------------------------------------------------------
--挑战相关 挑战结束或超时
-----------------------------------------------------------
function CurrentDungeonScript:OnChallengeTimeout()
	if self.Player == nil then
		return
	end
	
	if self.Challenge_timer == nil then
		return
	end
	
	self.Challenge_timer = nil
	
	if self.ChallengeStart == false then
		return
	end
	
	self.ChallengeStart = false
	
	-- 定身
	if self.Player:GetModAura():Exists(self.Hold_buff) == false then
		self.Player:GetModAura():Create(self.Hold_buff)
	end
	
	self:OnChallengeFail()
end

function CurrentDungeonScript:OnChallengeSucc()
	if self.Player == nil then
		return
	end
	
	-- 结算
	self.Player:GetModWarlord():OnCombatSucc(0)
end

function CurrentDungeonScript:OnChallengeFail()
	if self.Player == nil then
		return
	end
	
	-- 结算
	self.Player:GetModWarlord():OnCombatFail(0)
end

-- 放弃
function CurrentDungeonScript:GiveUp()
	if self.ChallengeStart == false then
		return
	end
	
	self.ChallengeStart = false;
	
	if self.Player == nil then
		return
	end
	
	-- 定身
	if self.Player:GetModAura():Exists(self.Hold_buff) == false then
		self.Player:GetModAura():Create(self.Hold_buff)
	end
	
	self:OnChallengeFail()
end


