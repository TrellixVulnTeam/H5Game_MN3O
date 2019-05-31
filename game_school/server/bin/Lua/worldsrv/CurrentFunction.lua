--------------------------------
--�������ű����ú���
--------------------------------

--�ؿ���ʼͨ���߼�(����������ʱ��)
function CurrentDungeonScript:G_DungeonStart()
    self.DungeonStartClock = os.time()
end

--�ؿ������������߼�
function CurrentDungeonScript:G_DungeonEnd(timer)
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k , v in pairs(CreatureTab) do
		v:GetModCombat():KillSelf(PET_KILLSELF_SKILLID,PET_KILLSELF_EFFECT)
	end	
	self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"")
	self.MainHuman:CloseHint(0)
	-- self.Stage:GetModDragonTame():DragonTamePrepared(self.MainHuman)	��ʱ����
	local clearTime = os.time() - self.DungeonStartClock
	self.SModDungeonScript:CalcScore(clearTime)
end

--�ؿ������������߼�����Ҫ����Լ�����뿪��ť
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

--boss��ս����ר�ú���
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
-- �����������
local DealPoltID = 38
local AutoRealiveDelay = 300
function CurrentDungeonScript:G_InterHumanKilledEvent(human,killer)
	human:CloseHint(0)	--�ر�����ʾ
	
	self.Stage:GetModObjs():RespawnCreaturesWhenHumanKilled()	--����ˢѪ��
	
	--[[ �ж��Ƿ���Ҫ�Զ�����
	if human:GetLevel() < 10 then
		-- �Զ�����׶�1:���������籾���籾�������Զ�ԭ�ظ���
		human:GetModRealive():HideRealiveButton(true)
		self.SModDungeonScript:LaunchPoltEx(DealPoltID,"G_DeadPoltCompleted",false)
	end]]
end
function CurrentDungeonScript:G_DeadPoltCompleted()
	-- �Զ�����׶�2:֪ͨ�ͻ������������
	local msg = {}
	self.MainHuman:SendMsg(msgids.SCRealiveEffect,msg)
	
	-- ������ֽ������Զ�����
	self.MainHuman:GetModRealive():Realive(self.MainHuman:GetPosition(), AutoRealiveDelay)
end

--BOSS��ս��������Чǽ���赲/////��ս���
function CurrentDungeonScript:G_BossFightingEvent_EffectW(bossid,effectwall,motionblock)
	self.G_EffectWall = effectwall
	self.G_MotionBlock = motionblock
	SetEventHandler(StageEvents.EnterCombat,"G_BossEnterCombat",{type = bossid})
	SetEventHandler(StageEvents.LeaveCombat,"G_BossLeaveCombat",{type = bossid})
end
function CurrentDungeonScript:G_BossEnterCombat()
	self.Stage:GetModDetour():EnableMotionBlock(self.G_MotionBlock,false)
	self.Stage:GetModDetour():EnableBlockEffects(self.G_EffectWall,true)	--����Чǽ
end
function CurrentDungeonScript:G_BossLeaveCombat()
	self.Stage:GetModDetour():EnableMotionBlock(self.G_MotionBlock,true)
	self.Stage:GetModDetour():EnableBlockEffects(self.G_EffectWall,false)	--����Чǽ
end



