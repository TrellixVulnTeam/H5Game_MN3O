--�����������ָ���ű�


--�����������Ҫ��
PlayerAdvance_Skilldata = {
	--ְҵ��ʾ��1սʿ��2���֣�3��ʦ
	[1] = {
			--��ҵȼ�����������{{����ID������Ҫ��ȼ�}}
			--������ҵȼ����ȼ����������������б����ܰ�˳��������ȼ�,���ܵȼ�Ϊ0ʱ��Ϊ���ȼ�
			--[1] = {level = {1} ,skilldata = {{1050,0}}},
			[2] = {level = {5} ,skilldata = {{1090,0.8},{1050,0.8}}},
			[3] = {level = {6,7,8,9} ,skilldata = {{1090,0.8},{1050,0.8},{1070,0.8}}},
			[4] = {level = {10,11,12,13,14,15,16,17,18,19} ,skilldata = {{1090,0.8},{1050,0.8},{1070,0.8},{1080,0.8}}},
			[5] = {level = {20,21,22} ,skilldata = {{1090,0.8},{1050,0.8},{1070,0.8},{1100,0.8},{1080,0.8}}},
			[6] = {level = {23,24,25} ,skilldata = {{1090,0.8},{1050,0.8},{1070,0.8},{1100,0.8},{1080,0.8},{1130,0.8}}},
			[7] = {level = {26,27,28} ,skilldata = {{1090,0.8},{1050,0.8},{1020,0.8},{1100,0.8},{1080,0.8},{1130,0.8}}},
			[8] = {level = {29,30,31} ,skilldata = {{1090,0.8},{1050,0.8},{1020,0.8},{1100,0.8},{1080,0.8},{1130,0.8},{1110,0.8}}},
			[9] = {level = {32,33,34} ,skilldata = {{1090,0.8},{1050,0.8},{1020,0.8},{1100,0.8},{1080,0.8},{1130,0.8},{1110,0.8}}},
			[10] = {level = {35,36,37} ,skilldata = {{1090,0.8},{1050,0.8},{1020,0.8},{1100,0.8},{1080,0.8},{1130,0.8},{1110,0.8}}},
			[11] = {level = {38,39,40} ,skilldata = {{1090,0.8},{1050,0.8},{1020,0.8},{1100,0.8},{1080,0.8},{1130,0.8},{1110,0.8}}},
			[12] = {level = {41,42,43,44,45,46,47,48,49,50} ,skilldata = {{1090,0.8},{1050,0.8},{1020,0.8},{1100,0.8},{1080,0.8},{1130,0.8},{1110,0.8}}},

	},
	[2] = {
			--������ҵȼ����ȼ����������������б����ܰ�˳��������ȼ�,���ܵȼ�Ϊ0ʱ��Ϊ���ȼ�
			--[1] = {level = {1} ,skilldata = {{2040,0}}},
			[2] = {level = {5} ,skilldata = {{2070,0.8},{2040,0.8}}},
			[3] = {level = {6,7,8,9} ,skilldata = {{2070,0.8},{2040,0.8},{2090,0.8}}},
			[4] = {level = {10,11,12,13,14,15,16,17,18,19} ,skilldata = {{2070,0.8},{2040,0.8},{2090,0.8},{2060,0.8}}},
			[5] = {level = {20,21,22} ,skilldata = {{2070,0.8},{2040,0.8},{2090,0.8},{2110,0.8},{2060,0.8}}},
			[6] = {level = {23,24,25,26,27,28} ,skilldata = {{2070,0.8},{2040,0.8},{2090,0.8},{2110,0.8},{2060,0.8},{2120,0.8}}},
			[7] = {level = {29,30,31,32,33,34,35,36,37,38,39,40} ,skilldata = {{2070,0.8},{2040,0.8},{2090,0.8},{2110,0.8},{2060,0.8},{2120,0.8},{2020,0.8}}},
			[8] = {level = {41,42,43,44,45,46,47,48,49,50} ,skilldata = {{2070,0.8},{2040,0.8},{2090,0.8},{2110,0.8},{2060,0.8},{2120,0.8},{2020,0.8}}},

	},
	[3] = {
		--������ҵȼ����ȼ����������������б����ܰ�˳��������ȼ�,���ܵȼ�Ϊ0ʱ��Ϊ���ȼ�
		--[1] = {level = {1} ,skilldata = {{3160,0}}},
		[2] = {level = {5} ,skilldata = {{3110,0.8},{3160,0.8}}},
		[3] = {level = {6,7,8,9} ,skilldata = {{3110,0.8},{3160,0.8},{3060,0.8}}},
		[4] = {level = {10,11,12,13,14,15,16,17,18,19} ,skilldata = {{3110,0.8},{3160,0.8},{3060,0.8},{3100,0.8}}},
		[5] = {level = {20,21,22} ,skilldata = {{3110,0.8},{3160,0.8},{3060,0.8},{3120,0.8},{3100,0.8}}},
		[6] = {level = {23,24,25,26,27,28} ,skilldata = {{3110,0.8},{3160,0.8},{3060,0.8},{3120,0.8},{3100,0.8},{3000,0.8}}},
		[7] = {level = {29,30,31,32,33,34,35,36,37} ,skilldata = {{3110,0.8},{3160,0.8},{3060,0.8},{3120,0.8},{3100,0.8},{3000,0.8},{3170,0.8}}},
		[8] = {level = {38,39,40,41,42,43,44,45,46,47,48,49,50} ,skilldata = {{3110,0.8},{3160,0.8},{3060,0.8},{3120,0.8},{3100,0.8},{3000,0.8},{3170,0.8}}},
	
	},
}
for adv = 51,100 do
	table.insert(PlayerAdvance_Skilldata[1][12].level,adv)
	table.insert(PlayerAdvance_Skilldata[2][7].level,adv)
	table.insert(PlayerAdvance_Skilldata[3][8].level,adv)
end

--Ѫ���������Ҫ��
PlayerAdvance_Blooddata = {
	--Ѫ�����÷�ְҵ ^_^
	--������ҵȼ����䡣��Ӧ��Ѫ��Ҫ�������Ѫ��֮���ܺ�
	[1] = {level = {1,14} ,blooddata = {2,2500}},
	[2] = {level = {15,19} ,blooddata = {2,5000}},
	[3] = {level = {20,29} ,blooddata = {2,3,10000}},
	[4] = {level = {30,39} ,blooddata = {2,3,"zise"}},
	[5] = {level = {40,49} ,blooddata = {2,3,4,"jinse"}},
	[6] = {level = {50,59} ,blooddata = {2,3,4,"chengse"}},
	[7] = {level = {60,79} ,blooddata = {2,3,4,"chengse"}},

}

--���������Ҫ��
PlayerAdvance_Dragondata = {
	--��ϵͳ����Ҫ��ְҵ ^_^
	--������ҵȼ����ȼ������䣬��Ӧ��������������ֵ��ר�����������Եȼ�
	--�ж����ͱ�־λ���壺1����������԰ٷֱȣ�2����ר���жϣ�3��������
	--ר����־λ���壺0,1,2,3,4 �ֱ��������Ͻ��������ɫר��
	[1] = {level = {1,29} ,dragondata = {{1,0.5},{1,0.6}}},
	[2] = {level = {30,34} ,dragondata = {{1,0.5},{2,1,1},{1,0.6},{2,2,1},{1,0.7}}},
	[3] = {level = {35,39} ,dragondata = {{1,0.5},{2,1,2},{1,0.6},{2,2,1},{1,0.7},{2,2,2}}},
	[4] = {level = {40,49} ,dragondata = {{1,0.5},{2,1,3},{1,0.6},{2,2,2},{1,0.7},{3,1},{2,2,3},{1,0.8},{3,2}}},
	[5] = {level = {50,59} ,dragondata = {{1,0.5},{2,1,4},{1,0.6},{2,2,3},{1,0.7},{3,1},{2,2,4},{1,0.8},{3,2},{2,3,1},{3,3}}},
	[6] = {level = {60,100} ,dragondata = {{1,0.5},{2,1,5},{1,0.6},{2,2,4},{1,0.7},{3,1},{2,2,5},{1,0.8},{3,2},{2,3,1},{3,3}}},
}

--װ���������Ҫ��
PlayerAdvance_Equipdata = {

	--������ҵȼ�����Ӧ��װ��λ��װ���ȼ��������ȼ���˳���Ⱥ���
	--װ��λ��0=������1=ͷ��2=�磬3=�ؼף�4=���ӣ�5=������6=��ָ,7=����
	--ְҵ��ʾ��1սʿ��2���֣�3��ʦ

	--[[
	[1] = {level = {1} , equiplv = 9, equiporder = {1,2,3,6,7,10,4,9,5,8}},
	[2] = {level = {2} , equiplv = 10, equiporder = {1,2,3,6,7,10,4,9,5,8}},
	[3] = {level = {3} , equiplv = 11, equiporder = {1,2,3,6,7,10,4,9,5,8}},
	[4] = {level = {4} , equiplv = 12, equiporder = {1,2,3,6,7,10,4,9,5,8}},
	[5] = {level = {5} , equiplv = 13, equiporder = {1,2,3,6,7,10,4,9,5,8}},
	[6] = {level = {6} , equiplv = 14, equiporder = {1,2,3,6,7,10,4,9,5,8}},
	[7] = {level = {7} , equiplv = 15, equiporder = {1,2,3,6,7,10,4,9,5,8}},
	[8] = {level = {8} , equiplv = 16, equiporder = {1,2,3,6,7,10,4,9,5,8}},
	[9] = {level = {9} , equiplv = 17, equiporder = {1,2,3,6,7,10,4,9,5,8}},
	[10] = {level = {10} , equiplv = 18, equiporder = {1,2,3,6,7,10,4,9,5,8}},
	[11] = {level = {11} , equiplv = 19, equiporder = {1,2,3,6,7,10,4,9,5,8}},
	]]
	[12] = {level = {12} , equiplv = 14, equiporder = {0,3,4,7,1,6,2,5}},
	[13] = {level = {13} , equiplv = 15, equiporder = {0,3,4,7,1,6,2,5}},
	[14] = {level = {14} , equiplv = 15, equiporder = {0,3,4,7,1,6,2,5}},
	[15] = {level = {15} , equiplv = 16, equiporder = {0,3,4,7,1,6,2,5}},
	[16] = {level = {16} , equiplv = 17, equiporder = {0,3,4,7,1,6,2,5}},
	[17] = {level = {17} , equiplv = 18, equiporder = {0,3,4,7,1,6,2,5}},
	[18] = {level = {18} , equiplv = 18, equiporder = {0,3,4,7,1,6,2,5}},
	[19] = {level = {19} , equiplv = 19, equiporder = {0,3,4,7,1,6,2,5}},
	[20] = {level = {20} , equiplv = 20, equiporder = {0,3,4,7,1,6,2,5}},
	[21] = {level = {21} , equiplv = 22, equiporder = {0,3,4,7,1,6,2,5}},
	[22] = {level = {22} , equiplv = 23, equiporder = {0,3,4,7,1,6,2,5}},
	[23] = {level = {23} , equiplv = 25, equiporder = {0,3,4,7,1,6,2,5}},
	[24] = {level = {24} , equiplv = 27, equiporder = {0,3,4,7,1,6,2,5}},
	[25] = {level = {25} , equiplv = 28, equiporder = {0,3,4,7,1,6,2,5}},
	[26] = {level = {26} , equiplv = 30, equiporder = {0,3,4,7,1,6,2,5}},
	[27] = {level = {27} , equiplv = 32, equiporder = {0,3,4,7,1,6,2,5}},
	[28] = {level = {28} , equiplv = 34, equiporder = {0,3,4,7,1,6,2,5}},
	[29] = {level = {29} , equiplv = 35, equiporder = {0,3,4,7,1,6,2,5}},
	[30] = {level = {30} , equiplv = 37, equiporder = {0,3,4,7,1,6,2,5}},
	[31] = {level = {31} , equiplv = 41, equiporder = {0,3,4,7,1,6,2,5}},
	[32] = {level = {32} , equiplv = 43, equiporder = {0,3,4,7,1,6,2,5}},
	[33] = {level = {33} , equiplv = 45, equiporder = {0,3,4,7,1,6,2,5}},
	[34] = {level = {34} , equiplv = 47, equiporder = {0,3,4,7,1,6,2,5}},
	[35] = {level = {35} , equiplv = 48, equiporder = {0,3,4,7,1,6,2,5}},
	[36] = {level = {36} , equiplv = 50, equiporder = {0,3,4,7,1,6,2,5}},
	[37] = {level = {37} , equiplv = 52, equiporder = {0,3,4,7,1,6,2,5}},
	[38] = {level = {38} , equiplv = 54, equiporder = {0,3,4,7,1,6,2,5}},
	[39] = {level = {39} , equiplv = 55, equiporder = {0,3,4,7,1,6,2,5}},
	[40] = {level = {40} , equiplv = 67, equiporder = {0,3,4,7,1,6,2,5}},
	[41] = {level = {41} , equiplv = 69, equiporder = {0,3,4,7,1,6,2,5}},
	[42] = {level = {42} , equiplv = 72, equiporder = {0,3,4,7,1,6,2,5}},
	[43] = {level = {43} , equiplv = 75, equiporder = {0,3,4,7,1,6,2,5}},
	[44] = {level = {44} , equiplv = 78, equiporder = {0,3,4,7,1,6,2,5}},
	[45] = {level = {45} , equiplv = 82, equiporder = {0,3,4,7,1,6,2,5}},
	[46] = {level = {46} , equiplv = 86, equiporder = {0,3,4,7,1,6,2,5}},
	[47] = {level = {47} , equiplv = 90, equiporder = {0,3,4,7,1,6,2,5}},
	[48] = {level = {48} , equiplv = 94, equiporder = {0,3,4,7,1,6,2,5}},
	[49] = {level = {49} , equiplv = 97, equiporder = {0,3,4,7,1,6,2,5}},
	[50] = {level = {50} , equiplv = 102, equiporder = {0,3,4,7,1,6,2,5}},
	[51] = {level = {51} , equiplv = 119, equiporder = {0,3,4,7,1,6,2,5}},
	[52] = {level = {52} , equiplv = 123, equiporder = {0,3,4,7,1,6,2,5}},
	[53] = {level = {53} , equiplv = 127, equiporder = {0,3,4,7,1,6,2,5}},
	[54] = {level = {54} , equiplv = 131, equiporder = {0,3,4,7,1,6,2,5}},
	[55] = {level = {55} , equiplv = 134, equiporder = {0,3,4,7,1,6,2,5}},
	[56] = {level = {56} , equiplv = 139, equiporder = {0,3,4,7,1,6,2,5}},
	[57] = {level = {57} , equiplv = 142, equiporder = {0,3,4,7,1,6,2,5}},
	[58] = {level = {58} , equiplv = 146, equiporder = {0,3,4,7,1,6,2,5}},
	[59] = {level = {59} , equiplv = 150, equiporder = {0,3,4,7,1,6,2,5}},
	[60] = {level = {60} , equiplv = 179, equiporder = {0,3,4,7,1,6,2,5}},
	[61] = {level = {61} , equiplv = 186, equiporder = {0,3,4,7,1,6,2,5}},
	[62] = {level = {62} , equiplv = 193, equiporder = {0,3,4,7,1,6,2,5}},
	[63] = {level = {63} , equiplv = 200, equiporder = {0,3,4,7,1,6,2,5}},
	[64] = {level = {64} , equiplv = 207, equiporder = {0,3,4,7,1,6,2,5}},
	[65] = {level = {65} , equiplv = 214, equiporder = {0,3,4,7,1,6,2,5}},
	[66] = {level = {66} , equiplv = 221, equiporder = {0,3,4,7,1,6,2,5}},
	[67] = {level = {67} , equiplv = 228, equiporder = {0,3,4,7,1,6,2,5}},
	[68] = {level = {68} , equiplv = 235, equiporder = {0,3,4,7,1,6,2,5}},
	[69] = {level = {69} , equiplv = 242, equiporder = {0,3,4,7,1,6,2,5}},
	[70] = {level = {70} , equiplv = 249, equiporder = {0,3,4,7,1,6,2,5}},


}

PlayerAdvance_StrTable = {
	Skill = {130110},
	Blood = {slot = 130111, slotexp = 130112},
	Dragon = {basdata = 130113,
				specsta = 130114,
				savey = 130115},
	--װ��λ��0=������1=ͷ��2=�磬3=�ؼף�4=���ӣ�5=������6=��ָ,7=����
	Equip = {[1] = 130116,[2] = 130117,[3] = 130118,[4] = 130119,[5] = 130120,
			[6] = 130121,[7] = 130122,[0] = 130123},

}


--��ҵ�½����ʼ��������ʾ
function PlayerAdvance_OnHumanEnterWorld(human)
	PlayerAdvance_OnSkillUp(human)
	--if not human:GetModFunctionDeblocking():IsBlocked(Functions.FUNCTION_BLOOD) then
	--	PlayerAdvance_OnBloodUp(human)
	--end
	--if not human:GetModFunctionDeblocking():IsBlocked(Functions.FUNCTION_DRAGON) and human:GetModDragon():HasEquipDragon() then
	--	PlayerAdvance_OnDragonUp(human)
	--end
	PlayerAdvance_OnEquipUp(human)
end

--��������¼���ˢ�¸�����ʾ
function PlayerAdvance_OnLevelUp(human)
	PlayerAdvance_OnSkillUp(human)
	--if not human:GetModFunctionDeblocking():IsBlocked(Functions.FUNCTION_BLOOD) then
	--	PlayerAdvance_OnBloodUp(human)
	--end
	--if not human:GetModFunctionDeblocking():IsBlocked(Functions.FUNCTION_DRAGON) and human:GetModDragon():HasEquipDragon() then
	--	PlayerAdvance_OnDragonUp(human)
	--end
	PlayerAdvance_OnEquipUp(human)
end

--��Ҹ���XX�¼�,�����������ǣ��������ͣ�1Ϊ���ܣ�2ΪѪ����3Ϊ����4Ϊװ��
function PlayerAdvance_OnPlayerUpdata(human,uptype)
	if uptype == 1 then
		PlayerAdvance_OnSkillUp(human)
	--elseif uptype == 2 then
	--	PlayerAdvance_OnBloodUp(human)
	--elseif uptype == 3 and human:GetModDragon():HasEquipDragon() then
	--	PlayerAdvance_OnDragonUp(human)
	elseif uptype == 4 then
		PlayerAdvance_OnEquipUp(human)
	end
end

--��ǰ�˷���Ϣ�����½���

function PlayerAdvance_SendMsg(human,c_oper,c_type,c_subtype,c_strid,c_nparam1,c_nparam2)
	local msg = {
					oper = c_oper,
					type = c_type,
					subtype = c_subtype,
					strid = c_strid,
					nparam1 = c_nparam1,
					nparam2 = c_nparam2,
					}
				
				human:SendMsg(msgids.SCAdvanceOper, msg) 
end



--���������¼���ˢ�¼��������ʾ
function PlayerAdvance_OnSkillUp(human)
	local PlayerSkilldata = PlayerAdvance_Skilldata[human:GetProfession()]
	for k , v in pairs(PlayerSkilldata) do
		local PlayerLv = human:GetLevel()
		for i , j in pairs(v.level) do
			if PlayerLv == j then
				for m , n in pairs(v.skilldata) do
					if n[2] == 0 then
						if human:GetModAdvance():GetMagicLevel(n[1]) <  PlayerLv then	--�ӿڣ���ȡ���ָ��ID���ܵȼ�
							--�ӿڣ�������Ϣ
							PlayerAdvance_SendMsg(human,0,1,1,PlayerAdvance_StrTable.Skill[1],n[1])
							return
						end
					elseif n[2] > 0 and n[2] < 1 then
						if human:GetModAdvance():GetMagicLevel(n[1]) <  math.ceil(PlayerLv * n[2] ) then	--�ӿڣ���ȡ���ָ��ID���ܵȼ�
							--�ӿڣ�������Ϣ
							PlayerAdvance_SendMsg(human,0,1,1,PlayerAdvance_StrTable.Skill[1],n[1])
							return
						end						
					else
						if human:GetModAdvance():GetMagicLevel(n[1]) <  n[2] then	--�ӿڣ���ȡ���ָ��ID���ܵȼ�
							--�ӿڣ�������Ϣ
							PlayerAdvance_SendMsg(human,0,1,1,PlayerAdvance_StrTable.Skill[1],n[1])
							return
						end
					end
					
					if m == #v.skilldata then	--�����Ҫȷ���ǲ��Ǽ��ܶ�����Ҫ�رգ�������ʾһ������������������Ϣ
						--�ӿڣ��ر���Ϣ
						PlayerAdvance_SendMsg(human,1,1,1,PlayerAdvance_StrTable.Skill[1])
					end
				end
			end
		end
	end
end

--Ѫ�������¼���ˢ��Ѫ�������ʾ
function PlayerAdvance_OnBloodUp(human)
	for k , v in pairs(PlayerAdvance_Blooddata) do
		local PlayerLv = human:GetLevel()
		--for i , j in pairs(v.level) do
			--if PlayerLv == j then
			if PlayerLv >= v.level[1] and PlayerLv <= v.level[2] then
				for m , n in pairs(v.blooddata) do
					if type(n) == "number" then
						if n <= 10 then
							if  human:GetModAdvance():GetBloodSlotActiveCnt() < n then	--��������
								PlayerAdvance_SendMsg(human,0,2,2,PlayerAdvance_StrTable.Blood.slot)
								return
							end
						else
							if human:GetModAdvance():GetBloodSlotExp() < n then
								PlayerAdvance_SendMsg(human,0,2,3,PlayerAdvance_StrTable.Blood.slotexp)
								return
							end
						end
					elseif type(n) == "string" then
						if n == "zise" then
							PlayerAdvance_SendMsg(human,0,2,3,130128)
							return
						elseif n == "jinse" then
							PlayerAdvance_SendMsg(human,0,2,3,130129)
							return
						elseif n == "chengse" then
							PlayerAdvance_SendMsg(human,0,2,3,130130)
							return
						end
					end
					if m == #v.blooddata then
						--�ӿڣ��ر���Ϣ
						PlayerAdvance_SendMsg(human,1,2,3)
					end
				end
			end
		--end
	end
end

--�������¼���ˢ���������ʾ��ֻ��Ե�ǰʹ�õ���
function PlayerAdvance_OnDragonUp(human)
	for k , v in pairs(PlayerAdvance_Dragondata) do
		local PlayerLv = human:GetLevel()
		--for i , j in pairs(v.level) do
		if PlayerLv >= v.level[1] and PlayerLv <= v.level[2] then
			--if PlayerLv == j then
				for m , n in pairs(v.dragondata) do
					if n[1] == 1 then --��������
						local currentdata = human:GetModAdvance():GetDragonBaseStatValue() / human:GetModAdvance():GetDragonBaseStatMaxValue()
						if currentdata < n[2] then	
							--�ӿڣ�����Ϣ�����ӻ�������
							PlayerAdvance_SendMsg(human,0,3,4,PlayerAdvance_StrTable.Dragon.basdata)
							return
						end
					elseif n[1] == 2 then --ר��
						if not human:GetModFunctionDeblocking():IsBlocked(Functions.FUNCTION_DRAGON_DELVE) then
							local SpecStatCnt = 0
							for num = n[2] , 4 do
								SpecStatCnt = SpecStatCnt + human:GetModAdvance():GetDragonSpecStatCnt(num)
							end
							if SpecStatCnt < n[3] then
								--�ӿڣ�����Ϣ������XX��ɫר��
								PlayerAdvance_SendMsg(human,0,3,5,PlayerAdvance_StrTable.Dragon.specsta,n[3],n[2])
								return
							end
						end
					elseif n[1] == 3 then --����
						if not human:GetModFunctionDeblocking():IsBlocked(Functions.FUNCTION_DRAGON_SAVEY) then
							if human:GetModAdvance():GetDragonSaveyLevel() < n[2] then
								--�ӿڣ�����Ϣ���������Եȼ�
								PlayerAdvance_SendMsg(human,0,3,6,PlayerAdvance_StrTable.Dragon.savey)
								return
							end
						end
					end
					if m == #v.dragondata then
						--�ӿڣ��ر���Ϣ
						PlayerAdvance_SendMsg(human,1,3,6)
					end
				end							
			--end
		end
	end

end

--װ�������¼���ˢ��װ�������ʾ
function PlayerAdvance_OnEquipUp(human)
	for k , v in pairs(PlayerAdvance_Equipdata) do
		local PlayerLv = human:GetLevel()
		for i , j in pairs(v.level) do
			if PlayerLv == j then
				for m , n in pairs(v.equiporder) do
					if human:GetModAdvance():GetEquipLevel(n) and human:GetModAdvance():GetEquipLevel(n) < v.equiplv then	--�ӿڣ���ȡָ��װ��λ��װ��lv��ûװ������false
						--�ӿڣ�������Ϣ
						--PlayerAdvance_SendMsg(human,0,4,7,PlayerAdvance_StrTable.Equip[n])
						if PlayerLv >= 20 and PlayerLv < 31 then
							PlayerAdvance_SendMsg(human,0,4,7,130124)
						elseif PlayerLv >= 31 and PlayerLv < 45 then
							PlayerAdvance_SendMsg(human,0,4,7,130125)
						elseif PlayerLv >= 45 and PlayerLv < 55 then
							PlayerAdvance_SendMsg(human,0,4,7,130126)
						elseif PlayerLv >= 55 then
							PlayerAdvance_SendMsg(human,0,4,7,130127)
						end
						return
					end
					if m == #v.equiporder then
						--�ӿڣ��ر���Ϣ
						PlayerAdvance_SendMsg(human,1,4,7)
					end
				end
			end
		end
	end
end