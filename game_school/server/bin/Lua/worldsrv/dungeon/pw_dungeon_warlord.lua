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

CurrentDungeonScript.EnemyPlayer = nil	--��ǰ����ս��(��ɫ)
CurrentDungeonScript.EnemyMonster = nil	--��ǰ����ս��(����)
CurrentDungeonScript.Player = nil		--��ս��
CurrentDungeonScript.ChallengeStart = false							--��ս��ʼ��ʶ
CurrentDungeonScript.Prepare_time = 3								--PK׼��ʱ��
CurrentDungeonScript.PK_time = 90									--PKʱ��
CurrentDungeonScript.Hold_buff = 102								--����buff
CurrentDungeonScript.Challenge_timer = nil							--��ʱ��ʱ��
CurrentDungeonScript.timer_1sec = nil								--ÿ�붨ʱ��(���Ѫ��)
CurrentDungeonScript.timer_hpcd = nil								--30�붨ʱ��(ѪƿCD)
-- CurrentDungeonScript.Enemy_buff = 50020								--����ս��buffID
CurrentDungeonScript.HP_percent = 30								--ʹ��Ѫƿ��������
CurrentDungeonScript.HP_cd = 30										--ʹ��Ѫƿcd

--��ɫ��������
CurrentDungeonScript.Relive_pos = 
								{
									["loc"] = {49.9,61.99,49.9},
									["dir"] = {-0.3,0.0,-0.9},
								}
--PK��ս������
CurrentDungeonScript.Player_pos = 
								{
									["loc"] = {49.9,61.99,49.9},
									["dir"] = {-0.3,0.0,-0.9},
								}
--PK����ս������
CurrentDungeonScript.Enemy_pos = 
								{
									["loc"] = {45.1,61.99,45.7},
									["dir"] = {0.3,0.0,0.9},
								}



local QuestID = {1403}--------------���߽�������ɵ�����ID		
local ZhiXianQuestID = {10094,10001}	-----����ID���������ID						
-----------------------------------------------------------
--����������ر�
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
-- �¼�����ҽ������뿪������
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
		-----���������õ������ݣ��ű�д��ʵ��������Ҫʵ�ֵ�����
	if HuMan:GetModQuest():GetQuestStatus(ZhiXianQuestID[1]) == 2 then
		HuMan:GetModQuest():InjectCreatureKilled(ZhiXianQuestID[2])	
-- pwdist.log('���´���')
	end	
	if self.Player == nil then
		self.Player = human
		
		-- ��ս�ߴ���
		self.Player:GetModWarlord():OnCombatStart(0)
		-- ����
		self.Player:GetModMotionMaster():ChangePosition(self.Player_pos["loc"])
		self.Player:GetModMotionMaster():ChangeOrientation(self.Player_pos["dir"])
		-- ��Ѫħ
		self.Player:GetModStatistic():SetPercentHP(1)
		self.Player:GetModStatistic():SetPercentMP(1)
		-- ����
		self.Player:GetModAura():Create(self.Hold_buff)
		
		return
	end

	pwdist.log('HumanEnter end')
end

function CurrentDungeonScript:HumanLeave(human)
	pwdist.log('HumanLeave:')
	
	if self.Player ~= nil then
		-- self:OnChallengeFail()
	
		-- ����
		self.Player:GetModWarlord():OnCombatEnd()
		self.Player = nil
		
	end
	
end

function CurrentDungeonScript:HumanKilled(human,killer)
	if self.Player == nil then
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
	
		self:OnChallengeFail()
	elseif self.EnemyPlayer ~= nil and human:GetID() == self.EnemyPlayer:GetID() then
		-- ��ս�ɹ�
		self.ChallengeStart = false
		if self.Challenge_timer ~= nil then
			self.SModDungeonScript:CancelTimer(self.Challenge_timer)
			self.Challenge_timer = nil
		end

		self:OnChallengeSucc()
	end
	
	-- �Լ�����
	if self.Player:GetModAura():Exists(self.Hold_buff) == false then
		self.Player:GetModAura():Create(self.Hold_buff)
	end
	
	-- ���ֶ���
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
	
	-- ս���ѽ��� ������
	if self.ChallengeStart == false then
		return
	end
	
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

	self:OnChallengeSucc();
end

-----------------------------------------------------------
--��ս��� ��ʼ��ս
-----------------------------------------------------------
-- ��ս��ɫ
function CurrentDungeonScript:StartChallengeHuman(human)
	if self.Player == nil then
		return
	end
	
	if self.ChallengeStart == true then
		return
	end
	
	if human ~= nil then
		self.EnemyPlayer = human
		
		-- ����ս�ߴ���
		self.EnemyPlayer:GetModWarlord():OnCombatStart(self.Player:GetModCombatPoint():GetCombatPoint())
		-- ����
		self.EnemyPlayer:GetModMotionMaster():ChangePosition(self.Enemy_pos["loc"])
		self.EnemyPlayer:GetModMotionMaster():ChangeOrientation(self.Enemy_pos["dir"])
		-- ����ս����Ѫħ
		self.EnemyPlayer:GetModStatistic():SetPercentHP(1)
		self.EnemyPlayer:GetModStatistic():SetPercentMP(1)
		-- ����
		self.EnemyPlayer:GetModAura():Create(self.Hold_buff)
		
		-- ֪ͨ�ͻ���
		local msg = { result = 0, wid = self.EnemyPlayer:GetID(), prepare_second = self.Prepare_time, pk_second = self.PK_time}
		self.Player:SendMsg(msgids.SCWarlordStart,msg)
		-- PKǰ׼��
		self.ChallengeStart = true
		self.SModCommon:CreateTimer(self.Prepare_time, "OnChallengeStart")
	end
end

-- ��ս����
function CurrentDungeonScript:StartChallengeMonster(creature)

	if self.ChallengeStart == true then
		return
	end
	
	if creature ~= nil then
		self.EnemyMonster = creature
		-- ����
		self.EnemyMonster:GetModMotionMaster():ChangePosition(self.Enemy_pos["loc"])
		self.EnemyMonster:GetModMotionMaster():ChangeOrientation(self.Enemy_pos["dir"])
		
		-- ����
		self.EnemyMonster:GetModAura():Create(self.Hold_buff)
		
		self.SModCommon:CreateTimer(1, "OnStartChallengeMonster")
	end
	
	pwdist.log('StartChallengeMonster')
end

function CurrentDungeonScript:OnStartChallengeMonster()

	if (self.Player == nil) or (self.EnemyMonster == nil) then
		return
	end
	
	-- ֪ͨ�ͻ���
	local msg = { result = 0, wid = self.EnemyMonster:GetID(), prepare_second = self.Prepare_time, pk_second = self.PK_time}
	self.Player:SendMsg(msgids.SCWarlordStart,msg)
	
	pwdist.log('SCWarlordStart')
	
	-- PKǰ׼��
	self.ChallengeStart = true
	self.SModCommon:CreateTimer(self.Prepare_time, "OnChallengeStart")
	
end

function CurrentDungeonScript:OnChallengeStart()
	if self.Player == nil then
		return
	end
	
	-- �������
	if self.Player:GetModAura():Exists(self.Hold_buff) then
		self.Player:GetModAura():DeleteSync(self.Hold_buff)
	end
	
	if self.EnemyPlayer ~= nil then
		-- �������
		if self.EnemyPlayer:GetModAura():Exists(self.Hold_buff) then
			self.EnemyPlayer:GetModAura():DeleteSync(self.Hold_buff)
		end
		-- ����ս�߿�ʼAI
		self.EnemyPlayer:ChangeFaction(2)
		self.EnemyPlayer:StartAI()
		self.EnemyPlayer:AddThreat(self.Player)
		-- PK��ʱ
		self.Challenge_timer = self.SModDungeonScript:CreateTimer(self.PK_time,"OnChallengeTimeout")
	elseif self.EnemyMonster ~= nil then
	
		-- �������
		if self.EnemyMonster:GetModAura():Exists(self.Hold_buff) then
			self.EnemyMonster:GetModAura():DeleteSync(self.Hold_buff)
		end
		
		-- ����ս�߿�ʼAI
		self.EnemyMonster:ChangeFaction(2)

		-- PK��ʱ
		self.Challenge_timer = self.SModDungeonScript:CreateTimer(self.PK_time,"OnChallengeTimeout")
	end
	
	--��������ʱ
	local msg = { targetlist = {} }
	msg.timesec = self.PK_time
	self.Player:SendMsg(msgids.SCDungeonTargetList, msg)
end

-----------------------------------------------------------
--��ս��� ��ս������ʱ
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
	
	-- ����
	if self.Player:GetModAura():Exists(self.Hold_buff) == false then
		self.Player:GetModAura():Create(self.Hold_buff)
	end
	
	self:OnChallengeFail()
end

function CurrentDungeonScript:OnChallengeSucc()
	if self.Player == nil then
		return
	end
	
	-- ����
	self.Player:GetModWarlord():OnCombatSucc(0)
end

function CurrentDungeonScript:OnChallengeFail()
	if self.Player == nil then
		return
	end
	
	-- ����
	self.Player:GetModWarlord():OnCombatFail(0)
end

-- ����
function CurrentDungeonScript:GiveUp()
	if self.ChallengeStart == false then
		return
	end
	
	self.ChallengeStart = false;
	
	if self.Player == nil then
		return
	end
	
	-- ����
	if self.Player:GetModAura():Exists(self.Hold_buff) == false then
		self.Player:GetModAura():Create(self.Hold_buff)
	end
	
	self:OnChallengeFail()
end


