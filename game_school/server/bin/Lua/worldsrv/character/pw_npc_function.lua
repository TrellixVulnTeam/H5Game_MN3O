----------------------------------------------------------
-- 功能Npc功能脚本
-- 对应NPCFunctionConfig.xls表中"选项脚本号"
----------------------------------------------------------

-- 打开Npc商店
function NpcFunc_OpenShop(human,shopId)
	luaE_openShop(human, shopId)
end

-- NPC对话任务2
function NpcFunc_DiologQuest2(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end

-- NPC对话任务3
function NpcFunc_DiologQuest3(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end

-- NPC对话任务4
function NpcFunc_DiologQuest4(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end

-- NPC对话任务5
function NpcFunc_DiologQuest5(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end


-- NPC对话任务6
function NpcFunc_DiologQuest6(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end

-- NPC对话任务7
function NpcFunc_DiologQuest7(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end


-- NPC对话任务8
function NpcFunc_DiologQuest8(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end
-- NPC对话任务9
function NpcFunc_DiologQuest9(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end

-- NPC对话任务10
function NpcFunc_DiologQuest10(human,QuestID)
	NpcFunc_DiologQuest1(human,QuestID)
end

-- NPC对话任务1
function NpcFunc_DiologQuest1(human,QuestID)
	local pHuman = human:cast('Human')
	if(pHuman == nil)then
		return
	end
	if(pHuman ~= nil)then
		local QuestStatus = pHuman:GetModWantedQuest():GetExQuestStatus(2,QuestID)----2环任务，1帮派任务用这个借口，主支线任务用原有借口	
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

-- 打开护送界面
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

-- 打开篝火界面
function NpcFunc_OpenGouHuoUI(human,funcId)
	local HuMan= human:cast('Human')
	if HuMan == nil then
		return
	end
	luaE_openFunctionUI(HuMan, funcId)

end

