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

CurrentDungeonScript.CurrEnemy = nil								--当前被挑战者
CurrentDungeonScript.Player = nil									--挑战者
CurrentDungeonScript.ChallengeStart = false							--挑战开始标识
CurrentDungeonScript.Prepare_time = 5								--PK准备时间
CurrentDungeonScript.PK_time = 60									--PK时间
CurrentDungeonScript.Hold_buff = 102								--定身buff
CurrentDungeonScript.Challenge_timer = nil							--超时定时器
CurrentDungeonScript.timer_1sec = nil								--每秒定时器(检测血量)
CurrentDungeonScript.timer_hpcd = nil								--30秒定时器(血瓶CD)
CurrentDungeonScript.Enemy_buff = 50020								--被挑战者buffID
CurrentDungeonScript.HP_percent = 30								--使用血瓶生命比例
CurrentDungeonScript.HP_cd = 30										--使用血瓶cd
--角色复活坐标
CurrentDungeonScript.Relive_pos = 
								{
									["loc"] = {85.13676,34.89838,24.61471},
									["dir"] = {0.0,0.0,1.0},
								}			
--PK挑战者坐标
CurrentDungeonScript.Player_pos = 
								{
									["loc"] = {48.70262,23.05725,44.43245},
									["dir"] = {0.0,0.0,1.0},
								}
--PK被挑战者坐标
CurrentDungeonScript.Enemy_pos = 
								{
									["loc"] = {48.70262,23.05727,73.70867},
									["dir"] = {0.0,0.0,-1.0},
								}
--站立被挑战者坐标
local warlord_pos = {
					[0] = { ["loc"] = {85.2093,37.88528,95.94314},["dir"] = {0.0,0.0,-1.0},},	-- 第一名
					[1] = { ["loc"] = {79.65524,37.7131,88.44532},["dir"] = {1.0,0.0,0.0},},	-- 第二名
					[2] = { ["loc"] = {90.56718,37.7131,88.44532},["dir"] = {-1.0,0.0,0.0},},	-- 第三名
					[3] = { ["loc"] = {81.57909,36.10419,77.17209},["dir"] = {1.0,0.0,0.0},},		-- 高六名
					[4] = { ["loc"] = {81.57909,36.10419,68.95769},["dir"] = {1.0,0.0,0.0},},		-- 高五名
					[5] = { ["loc"] = {81.57909,36.10419,60.81318},["dir"] = {1.0,0.0,0.0},},		-- 高四名
					[6] = { ["loc"] = {81.57909,36.10419,52.67556},["dir"] = {1.0,0.0,0.0},},		-- 高三名
					[7] = { ["loc"] = {81.57909,36.10419,44.48568},["dir"] = {1.0,0.0,0.0},},		-- 高二名
					[8] = { ["loc"] = {81.57909,36.10419,36.37383},["dir"] = {1.0,0.0,0.0},},		-- 高一名
					}
-----------------------------------------------------------
--副本开启与关闭
-----------------------------------------------------------
function CurrentDungeonScript:Startup()
	self.SModDungeonScript = self.Stage:GetModDungeonScript()
	self.SModCommon = self.Stage:GetModCommon()
	
	SetEventHandler(StageEvents.HumanEnter,"HumanEnter")
	SetEventHandler(StageEvents.HumanLeave,"HumanLeave")
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
end

function CurrentDungeonScript:Cleanup()
end

-----------------------------------------------------------
--玩家进入与离开
-----------------------------------------------------------
function CurrentDungeonScript:HumanEnter(human)
	--pwdist.log(tostring(human:GetID()))
	--武神争霸，进场完成任务
	self.ModQuest = human:GetModQuest()
	if self.ModQuest:GetQuestStatus(10106) == 2 then
		self.ModQuest:DoneQuest(10106)
	end
	if self.Player == nil then
		self.Player = human
		return
	end
	
	if human:GetID() ~= self.Player:GetID() then
		human:GetModMotionMaster():ChangePosition(warlord_pos[human:GetModWarlord():GetPosID()]["loc"])
		human:GetModMotionMaster():ChangeOrientation(warlord_pos[human:GetModWarlord():GetPosID()]["dir"])
	end
end

function CurrentDungeonScript:HumanLeave(human)
	-- 玩家离开
	if human:GetID() == self.Player:GetID() then
		-- 战斗未结束 挑战失败
		--if self.ChallengeStart == true then
		--	slef:OnChallengeFail()
		--end
		self.SModDungeonScript:Cleanup()	--*玩家离开场景清空所有剧情相关逻辑，以免出问题
	end
end

-----------------------------------------------------------
--挑战相关 开始挑战
-----------------------------------------------------------
function CurrentDungeonScript:StartChallenge(human)
	if self.ChallengeStart == true then
		return
	end
	
	if human ~= nil then
		self.CurrEnemy = human
		-- 角色开始战斗前操作
		self.Player:GetModWarlord():OnCombatStart(0)
		self.CurrEnemy:GetModWarlord():OnCombatStart(self.Player:GetModCombatPoint():GetCombatPoint())
		-- 传送
		self.Player:GetModMotionMaster():ChangePosition(self.Player_pos["loc"])
		self.Player:GetModMotionMaster():ChangeOrientation(self.Player_pos["dir"])
		self.CurrEnemy:GetModMotionMaster():ChangePosition(self.Enemy_pos["loc"])
		self.CurrEnemy:GetModMotionMaster():ChangeOrientation(self.Enemy_pos["dir"])
		-- 满血魔
		self.Player:GetModStatistic():SetPercentHP(1)
		self.Player:GetModStatistic():SetPercentMP(1)
		--self.CurrEnemy:GetModStatistic():SetPercentHP(1)
		--self.CurrEnemy:GetModStatistic():SetPercentMP(1)
		-- 定身
		self.Player:GetModAura():Create(self.Hold_buff)
		self.CurrEnemy:GetModAura():Create(self.Hold_buff)
		-- 通知客户端
		local msg = { result = 0, wid = self.CurrEnemy:GetID(), prepare_second = self.Prepare_time, pk_second = self.PK_time}
		self.Player:SendMsg(msgids.SCWarlordStart,msg)
		-- PK前准备
		self.ChallengeStart = true
		self.SModCommon:CreateTimer(self.Prepare_time, "OnChallengeStart")
	end
end

function CurrentDungeonScript:OnChallengeStart()
	if self.CurrEnemy ~= nil then
		-- 解除定身
		if self.Player:GetModAura():Exists(self.Hold_buff) then
			self.Player:GetModAura():DeleteSync(self.Hold_buff)
		end
		if self.CurrEnemy:GetModAura():Exists(self.Hold_buff) then
			self.CurrEnemy:GetModAura():DeleteSync(self.Hold_buff)
		end
		-- 被挑战者增加buff
		--self.CurrEnemy:GetModAura():Create(self.Enemy_buff)
		-- 被挑战者血量监控
		self:CreateHPTime()
		-- 被挑战者满血魔
		self.CurrEnemy:GetModStatistic():SetPercentHP(1)
		self.CurrEnemy:GetModStatistic():SetPercentMP(1)
		-- 被挑战者开始AI
		self.CurrEnemy:ChangeFaction(2)
		self.CurrEnemy:StartAI()
		self.CurrEnemy:AddThreat(self.Player)
		-- PK计时
		self.Challenge_timer = self.SModDungeonScript:CreateTimer(self.PK_time,"OnChallengeTimeout")
	end
end

-----------------------------------------------------------
--挑战相关 挑战结束或超时
-----------------------------------------------------------
function CurrentDungeonScript:HumanKilled(human,killer)
	if (self.CurrEnemy == nil) or (self.Player == nil) then
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
		-- 定身
		if self.Player:GetModAura():Exists(self.Hold_buff) == false then
			self.Player:GetModAura():Create(self.Hold_buff)
		end
		self.SModCommon:CreateTimer(3, "OnChallengeFail")
	elseif human:GetID() == self.CurrEnemy:GetID() then
		-- 挑战成功
		self.ChallengeStart = false
		if self.Challenge_timer ~= nil then
			self.SModDungeonScript:CancelTimer(self.Challenge_timer)
			self.Challenge_timer = nil
		end
		-- 定身
		if self.Player:GetModAura():Exists(self.Hold_buff) == false then
			self.Player:GetModAura():Create(self.Hold_buff)
		end
		self.SModCommon:CreateTimer(3, "OnChallengeSucc")
	end
end

function CurrentDungeonScript:OnChallengeTimeout()
	if self.Challenge_timer == nil then
		return
	end
	
	if self.CurrEnemy ~= nil then
		-- 挑战失败
		self.ChallengeStart = false
		self.Challenge_timer = nil
		-- 定身
		if self.Player:GetModAura():Exists(self.Hold_buff) == false then
			self.Player:GetModAura():Create(self.Hold_buff)
		end
		self.SModCommon:CreateTimer(3, "OnChallengeFail")
	end
end

function CurrentDungeonScript:OnChallengeSucc()
	if (self.CurrEnemy == nil) or (self.Player == nil) then
		return
	end
	-- 被挑战者复活
	self.CurrEnemy:GetModRealive():Realive(warlord_pos[self.CurrEnemy:GetModWarlord():GetPosID()]["loc"], 0)
	-- 结算
	self.Player:GetModWarlord():OnCombatSucc(self.CurrEnemy:GetID())
	-- 重置
	self:OnChallengeEnd()
end

function CurrentDungeonScript:OnChallengeFail()
	if (self.CurrEnemy == nil) or (self.Player == nil) then
		return
	end
	-- 被挑战者归位
	self.CurrEnemy:GetModMotionMaster():ChangePosition(warlord_pos[self.CurrEnemy:GetModWarlord():GetPosID()]["loc"])
	self.CurrEnemy:GetModMotionMaster():ChangeOrientation(warlord_pos[self.CurrEnemy:GetModWarlord():GetPosID()]["dir"])
	-- 结算
	self.Player:GetModWarlord():OnCombatFail(self.CurrEnemy:GetID())
	-- 重置
	self:OnChallengeEnd()
end

function CurrentDungeonScript:OnChallengeEnd()
	if self.timer_1sec ~= nil then
		self.SModDungeonScript:CancelTimer(self.timer_1sec)
		self.timer_1sec = nil
	end
	
	if self.timer_hpcd ~= nil then
		self.SModDungeonScript:CancelTimer(self.timer_hpcd)
		self.timer_hpcd = nil
	end
	
	if self.CurrEnemy == nil then
		return
	end
	-- 被挑战者删除buff
	if self.CurrEnemy:GetModAura():Exists(self.Enemy_buff) then
		self.CurrEnemy:GetModAura():DeleteSync(self.Enemy_buff)
	end
	self.CurrEnemy:ChangeFaction(1)
	self.CurrEnemy:CleanAI()
	self.CurrEnemy = nil
end

function CurrentDungeonScript:LeaveChallenge()
	if self.ChallengeStart == false then
		-- 玩家复活
		if self.Player:IsDead() == true then
			self.Player:GetModRealive():Realive(self.Relive_pos["loc"], 0)
			self.Player:GetModMotionMaster():ChangeOrientation(self.Relive_pos["dir"])
		-- 玩家归位
		else
			self.Player:GetModMotionMaster():StopMotion()
			self.Player:GetModMotionMaster():ChangePosition(self.Relive_pos["loc"])
			self.Player:GetModMotionMaster():ChangeOrientation(self.Relive_pos["dir"])
		end
		-- 解除定身
 		if self.Player:GetModAura():Exists(self.Hold_buff) then
			self.Player:GetModAura():DeleteSync(self.Hold_buff)
		end
		
		-- 角色结束战斗操作
		self.Player:GetModWarlord():OnCombatEnd()
	end
end

function CurrentDungeonScript:CreateHPTime()
	self.timer_1sec = self.SModDungeonScript:CreatePeriodTimer(1,1,-1,"CheckUseBloodBottle")	--血量检测
end

function CurrentDungeonScript:CheckUseBloodBottle()
	if self.CurrEnemy ~= nil then
		if self.CurrEnemy:IsDead() == true then
			return
		end
		
		local percent = self.CurrEnemy:GetModStatistic():GetHPPercent()
		if percent < self.HP_percent then
			local hp = 0
			local level = self.CurrEnemy:GetLevel()
			if level < 20 then
				hp = 3750
			elseif level < 30 then
				hp = 6250
			elseif level < 40 then
				hp = 12500
			elseif level < 50 then
				hp = 25000
			elseif level < 60 then
				hp = 52500
			elseif level < 70 then
				hp = 80000
			else
				hp = 130000
			end
			
			local curr = self.CurrEnemy:GetModStatistic():GetHP()
			self.CurrEnemy:GetModStatistic():SetHP(hp + curr)
			if self.timer_1sec ~= nil then
				self.SModDungeonScript:CancelTimer(self.timer_1sec)
				self.timer_1sec = nil
				self.timer_hpcd = self.SModCommon:CreateTimer(self.HP_cd,"CreateHPTime")
			end
		end
	end
end