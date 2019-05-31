CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------

-----------------------------------------------------------
--��������
-----------------------------------------------------------

CurrentDungeonScript.CurrEnemy = nil								--��ǰ����ս��
CurrentDungeonScript.Player = nil									--��ս��
CurrentDungeonScript.ChallengeStart = false							--��ս��ʼ��ʶ
CurrentDungeonScript.Prepare_time = 5								--PK׼��ʱ��
CurrentDungeonScript.PK_time = 60									--PKʱ��
CurrentDungeonScript.Hold_buff = 102								--����buff
CurrentDungeonScript.Challenge_timer = nil							--��ʱ��ʱ��
CurrentDungeonScript.timer_1sec = nil								--ÿ�붨ʱ��(���Ѫ��)
CurrentDungeonScript.timer_hpcd = nil								--30�붨ʱ��(ѪƿCD)
CurrentDungeonScript.Enemy_buff = 50020								--����ս��buffID
CurrentDungeonScript.HP_percent = 30								--ʹ��Ѫƿ��������
CurrentDungeonScript.HP_cd = 30										--ʹ��Ѫƿcd
--��ɫ��������
CurrentDungeonScript.Relive_pos = 
								{
									["loc"] = {85.13676,34.89838,24.61471},
									["dir"] = {0.0,0.0,1.0},
								}			
--PK��ս������
CurrentDungeonScript.Player_pos = 
								{
									["loc"] = {48.70262,23.05725,44.43245},
									["dir"] = {0.0,0.0,1.0},
								}
--PK����ս������
CurrentDungeonScript.Enemy_pos = 
								{
									["loc"] = {48.70262,23.05727,73.70867},
									["dir"] = {0.0,0.0,-1.0},
								}
--վ������ս������
local warlord_pos = {
					[0] = { ["loc"] = {85.2093,37.88528,95.94314},["dir"] = {0.0,0.0,-1.0},},	-- ��һ��
					[1] = { ["loc"] = {79.65524,37.7131,88.44532},["dir"] = {1.0,0.0,0.0},},	-- �ڶ���
					[2] = { ["loc"] = {90.56718,37.7131,88.44532},["dir"] = {-1.0,0.0,0.0},},	-- ������
					[3] = { ["loc"] = {81.57909,36.10419,77.17209},["dir"] = {1.0,0.0,0.0},},		-- ������
					[4] = { ["loc"] = {81.57909,36.10419,68.95769},["dir"] = {1.0,0.0,0.0},},		-- ������
					[5] = { ["loc"] = {81.57909,36.10419,60.81318},["dir"] = {1.0,0.0,0.0},},		-- ������
					[6] = { ["loc"] = {81.57909,36.10419,52.67556},["dir"] = {1.0,0.0,0.0},},		-- ������
					[7] = { ["loc"] = {81.57909,36.10419,44.48568},["dir"] = {1.0,0.0,0.0},},		-- �߶���
					[8] = { ["loc"] = {81.57909,36.10419,36.37383},["dir"] = {1.0,0.0,0.0},},		-- ��һ��
					}
-----------------------------------------------------------
--����������ر�
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
--��ҽ������뿪
-----------------------------------------------------------
function CurrentDungeonScript:HumanEnter(human)
	--pwdist.log(tostring(human:GetID()))
	--�������ԣ������������
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
	-- ����뿪
	if human:GetID() == self.Player:GetID() then
		-- ս��δ���� ��սʧ��
		--if self.ChallengeStart == true then
		--	slef:OnChallengeFail()
		--end
		self.SModDungeonScript:Cleanup()	--*����뿪����������о�������߼������������
	end
end

-----------------------------------------------------------
--��ս��� ��ʼ��ս
-----------------------------------------------------------
function CurrentDungeonScript:StartChallenge(human)
	if self.ChallengeStart == true then
		return
	end
	
	if human ~= nil then
		self.CurrEnemy = human
		-- ��ɫ��ʼս��ǰ����
		self.Player:GetModWarlord():OnCombatStart(0)
		self.CurrEnemy:GetModWarlord():OnCombatStart(self.Player:GetModCombatPoint():GetCombatPoint())
		-- ����
		self.Player:GetModMotionMaster():ChangePosition(self.Player_pos["loc"])
		self.Player:GetModMotionMaster():ChangeOrientation(self.Player_pos["dir"])
		self.CurrEnemy:GetModMotionMaster():ChangePosition(self.Enemy_pos["loc"])
		self.CurrEnemy:GetModMotionMaster():ChangeOrientation(self.Enemy_pos["dir"])
		-- ��Ѫħ
		self.Player:GetModStatistic():SetPercentHP(1)
		self.Player:GetModStatistic():SetPercentMP(1)
		--self.CurrEnemy:GetModStatistic():SetPercentHP(1)
		--self.CurrEnemy:GetModStatistic():SetPercentMP(1)
		-- ����
		self.Player:GetModAura():Create(self.Hold_buff)
		self.CurrEnemy:GetModAura():Create(self.Hold_buff)
		-- ֪ͨ�ͻ���
		local msg = { result = 0, wid = self.CurrEnemy:GetID(), prepare_second = self.Prepare_time, pk_second = self.PK_time}
		self.Player:SendMsg(msgids.SCWarlordStart,msg)
		-- PKǰ׼��
		self.ChallengeStart = true
		self.SModCommon:CreateTimer(self.Prepare_time, "OnChallengeStart")
	end
end

function CurrentDungeonScript:OnChallengeStart()
	if self.CurrEnemy ~= nil then
		-- �������
		if self.Player:GetModAura():Exists(self.Hold_buff) then
			self.Player:GetModAura():DeleteSync(self.Hold_buff)
		end
		if self.CurrEnemy:GetModAura():Exists(self.Hold_buff) then
			self.CurrEnemy:GetModAura():DeleteSync(self.Hold_buff)
		end
		-- ����ս������buff
		--self.CurrEnemy:GetModAura():Create(self.Enemy_buff)
		-- ����ս��Ѫ�����
		self:CreateHPTime()
		-- ����ս����Ѫħ
		self.CurrEnemy:GetModStatistic():SetPercentHP(1)
		self.CurrEnemy:GetModStatistic():SetPercentMP(1)
		-- ����ս�߿�ʼAI
		self.CurrEnemy:ChangeFaction(2)
		self.CurrEnemy:StartAI()
		self.CurrEnemy:AddThreat(self.Player)
		-- PK��ʱ
		self.Challenge_timer = self.SModDungeonScript:CreateTimer(self.PK_time,"OnChallengeTimeout")
	end
end

-----------------------------------------------------------
--��ս��� ��ս������ʱ
-----------------------------------------------------------
function CurrentDungeonScript:HumanKilled(human,killer)
	if (self.CurrEnemy == nil) or (self.Player == nil) then
		return
	end
	-- ս���������������
	if human:GetID() == self.Player:GetID() then
		self.Player:GetModRealive():HideRealiveButton(true)
	end
	-- ս���ѽ��� ������
	if self.ChallengeStart == false then
		return
	end
	
	if human:GetID() == self.Player:GetID() then
		-- ��սʧ��
		self.ChallengeStart = false
		if self.Challenge_timer ~= nil then
			self.SModDungeonScript:CancelTimer(self.Challenge_timer)
			self.Challenge_timer = nil
		end
		-- ����
		if self.Player:GetModAura():Exists(self.Hold_buff) == false then
			self.Player:GetModAura():Create(self.Hold_buff)
		end
		self.SModCommon:CreateTimer(3, "OnChallengeFail")
	elseif human:GetID() == self.CurrEnemy:GetID() then
		-- ��ս�ɹ�
		self.ChallengeStart = false
		if self.Challenge_timer ~= nil then
			self.SModDungeonScript:CancelTimer(self.Challenge_timer)
			self.Challenge_timer = nil
		end
		-- ����
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
		-- ��սʧ��
		self.ChallengeStart = false
		self.Challenge_timer = nil
		-- ����
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
	-- ����ս�߸���
	self.CurrEnemy:GetModRealive():Realive(warlord_pos[self.CurrEnemy:GetModWarlord():GetPosID()]["loc"], 0)
	-- ����
	self.Player:GetModWarlord():OnCombatSucc(self.CurrEnemy:GetID())
	-- ����
	self:OnChallengeEnd()
end

function CurrentDungeonScript:OnChallengeFail()
	if (self.CurrEnemy == nil) or (self.Player == nil) then
		return
	end
	-- ����ս�߹�λ
	self.CurrEnemy:GetModMotionMaster():ChangePosition(warlord_pos[self.CurrEnemy:GetModWarlord():GetPosID()]["loc"])
	self.CurrEnemy:GetModMotionMaster():ChangeOrientation(warlord_pos[self.CurrEnemy:GetModWarlord():GetPosID()]["dir"])
	-- ����
	self.Player:GetModWarlord():OnCombatFail(self.CurrEnemy:GetID())
	-- ����
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
	-- ����ս��ɾ��buff
	if self.CurrEnemy:GetModAura():Exists(self.Enemy_buff) then
		self.CurrEnemy:GetModAura():DeleteSync(self.Enemy_buff)
	end
	self.CurrEnemy:ChangeFaction(1)
	self.CurrEnemy:CleanAI()
	self.CurrEnemy = nil
end

function CurrentDungeonScript:LeaveChallenge()
	if self.ChallengeStart == false then
		-- ��Ҹ���
		if self.Player:IsDead() == true then
			self.Player:GetModRealive():Realive(self.Relive_pos["loc"], 0)
			self.Player:GetModMotionMaster():ChangeOrientation(self.Relive_pos["dir"])
		-- ��ҹ�λ
		else
			self.Player:GetModMotionMaster():StopMotion()
			self.Player:GetModMotionMaster():ChangePosition(self.Relive_pos["loc"])
			self.Player:GetModMotionMaster():ChangeOrientation(self.Relive_pos["dir"])
		end
		-- �������
 		if self.Player:GetModAura():Exists(self.Hold_buff) then
			self.Player:GetModAura():DeleteSync(self.Hold_buff)
		end
		
		-- ��ɫ����ս������
		self.Player:GetModWarlord():OnCombatEnd()
	end
end

function CurrentDungeonScript:CreateHPTime()
	self.timer_1sec = self.SModDungeonScript:CreatePeriodTimer(1,1,-1,"CheckUseBloodBottle")	--Ѫ�����
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