----------------------------------------------------------
-- ����Npc���ܽű�
-- ��ӦNPCFunctionConfig.xls����"ѡ��ű���"
----------------------------------------------------------

-- ��Npc�̵�
function NpcFunc_OpenShop(human,shopId)
	luaE_openShop(human, shopId)
end

-- NPC�Ի�����2
function NpcFunc_DiologQuest2(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end

-- NPC�Ի�����3
function NpcFunc_DiologQuest3(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end

-- NPC�Ի�����4
function NpcFunc_DiologQuest4(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end

-- NPC�Ի�����5
function NpcFunc_DiologQuest5(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end


-- NPC�Ի�����6
function NpcFunc_DiologQuest6(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end

-- NPC�Ի�����7
function NpcFunc_DiologQuest7(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end


-- NPC�Ի�����8
function NpcFunc_DiologQuest8(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end
-- NPC�Ի�����9
function NpcFunc_DiologQuest9(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end

-- NPC�Ի�����10
function NpcFunc_DiologQuest10(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end

-- NPC�Ի�����1
function NpcFunc_DiologQuest1(human,QuestID)
	local pHuman = human:cast('Human')
	if(pHuman == nil)then
		return
	end
	if(pHuman ~= nil)then
		local QuestStatus = pHuman:GetModWantedQuest():GetExQuestStatus(2,QuestID)----2������1���������������ڣ���֧��������ԭ�н��	
		-- pwdist.log("QuestID "..tostring(QuestID))
		-- pwdist.log("QuestStatus "..tostring(QuestStatus))		
		if(QuestStatus == nil)then
			return
		end
		if(QuestStatus == 2 or QuestStatus == 3)then
			pHuman:GetModWantedQuest():SetExQuestDone(2,QuestID)
		end
	end
end
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- �򿪻��ͽ���
function NpcFunc_OpenFunctionUI(human,funcId)
	local HuMan= human:cast('Human')
	if HuMan == nil then
		return
	end
	local HLevel = HuMan:GetLevel()
	if(HLevel == nil)then
		return
	end
	if(HLevel < 70) then
		HuMan:SendNotifyMsg(134109, CHAT_MODE_SCREEN, CHAT_TEXT_SYSTEM)
	else
		luaE_openFunctionUI(HuMan, funcId)
	end
end

-- ���������
function NpcFunc_OpenGouHuoUI(human,funcId)
	local HuMan= human:cast('Human')
	if HuMan == nil then
		return
	end
	luaE_openFunctionUI(HuMan, funcId)

end

