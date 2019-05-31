

ChallengeOther = {}

ChallengeOther.WIN_TYPE_KILLALL 		= 1		--全部杀死通关
ChallengeOther.WIN_TYPE_KILLBYWAVE		= 2		--塔防N波怪通关
----刷怪点
ChallengeOther.MonsterPosition = {
	
	[1] = {[1]={60.659,41.23,71.309},		[2]={0.0,0.0,-1.0},},	--八卦12点 
	[2] = {[1]={67.16,41.23,64.01},		[2]={-0.7,0.0,-0.7},},	--八卦1点30
	[3] = {[1]={69.559,41.23,62.009},		[2]={-1.0,0.0,0.0},},	--八卦3点
	[4] = {[1]={67.16,41.23,57.209},		[2]={-0.7,0.0,0.7},},	--八卦4点30
	[5] = {[1]={60.659,41.23,52.909},		[2]={0.0,0.0,1.0},},	--八卦6点
	[6] = {[1]={54.159,41.23,57.409},		[2]={0.7,0.0,0.7},},	--八卦7点30
	[7] = {[1]={51.459,41.23,62.009},		[2]={1.0,0.0,0.0},},	--八卦9点
	[8] = {[1]={54.159,41.23,64.01},		[2]={0.7,0.0,-0.7},},	--八卦10点30
	[9] = {[1]={60.659,41.23,54.409},		[2]={0.0,0.0,1.0},},	--中央点位
	[10] = {[1]={60.659,41.23,48.81},		[2]={0.0,0.0,1.0},},	--大门口
	
	
	[11] = {[1]={56.659,41.23,77.11},		[2]={0.0,0.0,-1.0},},	--外圈12点 
	[12] = {[1]={68.459,41.23,72.51},		[2]={-0.4,0.0,-0.9},},	--外圈1点 
	[13] = {[1]={69.559,41.23,68.01},		[2]={-0.7,0.0,-0.7},},	--外圈1点30
	[14] = {[1]={73.66,41.23,65.41},		[2]={-0.9,0.0,-0.4},},	--外圈2点 
	[15] = {[1]={75.16,41.23,62.009},		[2]={-1.0,0.0,0.0},},	--外圈3点
	[16] = {[1]={73.66,41.23,55.81},		[2]={-0.9,0.0,0.4},},	--外圈4点 
	[17] = {[1]={69.559,41.23,57.509},		[2]={-0.7,0.0,0.7},},	--外圈4点30
	[18] = {[1]={68.26,41.23,52.909},		[2]={-0.4,0.0,0.9},},	--外圈5点 
	[19] = {[1]={60.659,41.23,51.009},		[2]={0.0,0.0,1.0},},	--外圈6点
	[20] = {[1]={52.56,41.23,52.909},		[2]={0.4,0.0,0.9},},	--外圈7点 
	[21] = {[1]={51.959,41.23,57.509},		[2]={0.7,0.0,0.7},},	--外圈7点30
	[22] = {[1]={47.659,41.23,55.909},   	[2]={0.9,0.0,0.4},},	--外圈8点 
	[23] = {[1]={45.959,41.23,62.009},		[2]={1.0,0.0,0.0},},	--外圈9点
	[24] = {[1]={47.659,41.23,65.309},	    	[2]={0.9,0.0,-0.4},},	--外圈10点 
	[25] = {[1]={51.959,41.23,68.01},		[2]={0.7,0.0,-0.7},},	--外圈10点30
	[26] = {[1]={52.56,41.23,72.51},		[2]={0.4,0.0,-0.9},},	--外圈11点

	[27] = {[1]={64.66,41.23,77.01},		[2]={0.0,0.0,-1.0},},	--12点佛像下
	[28] = {[1]={72.86,41.23,71.209},		[2]={-0.7,0.0,-0.7},},	--1点30佛像下 
	[29] = {[1]={72.459,41.23,62.009},		[2]={-1.0,0.0,0.0},},	--3点楼梯口
	[30] = {[1]={72.059,41.23,54.009},   	[2]={-0.7,0.0,0.7},},	--4点30佛像下
	[31] = {[1]={60.659,41.23,55.709},		[2]={0.0,0.0,1.0},},	--6点门口
	[32] = {[1]={49.259,41.23,54.009},		[2]={0.7,0.0,0.7},},	--7点30佛像下
	[33] = {[1]={48.759,41.23,62.009},		[2]={1.0,0.0,0.0},},	--9点楼梯口
	[34] = {[1]={48.86,41.23,71.309},		[2]={0.7,0.0,-0.7},},	--10点30佛像下

	[36] = {[1]={56.659,41.23,72.809},		[2]={0.0,0.0,-1.0},},      --12点位置3行1
	[37] = {[1]={58.659,41.23,72.809},		[2]={0.0,0.0,-1.0},},      --12点位置3行2
	[38] = {[1]={60.659,41.23,72.809},		[2]={0.0,0.0,-1.0},},      --12点位置3行3
	[39] = {[1]={62.659,41.23,72.809},		[2]={0.0,0.0,-1.0},},      --12点位置3行4
	[40] = {[1]={64.66,41.23,72.809},		[2]={0.0,0.0,-1.0},},      --12点位置3行5
	[41] = {[1]={56.659,41.23,70.809},		[2]={0.0,0.0,-1.0},},      --12点位置2行1
	[42] = {[1]={58.659,41.23,70.809},		[2]={0.0,0.0,-1.0},},      --12点位置2行2
	[43] = {[1]={60.659,41.23,70.809},		[2]={0.0,0.0,-1.0},},      --12点位置2行3
	[44] = {[1]={62.659,41.23,70.809},		[2]={0.0,0.0,-1.0},},      --12点位置2行4
	[45] = {[1]={64.66,41.23,70.809},		[2]={0.0,0.0,-1.0},},      --12点位置2行5
	[46] = {[1]={56.659,41.23,68.809},		[2]={0.0,0.0,-1.0},},      --12点位置1行1
	[47] = {[1]={58.659,41.23,68.809},		[2]={0.0,0.0,-1.0},},      --12点位置1行2
	[48] = {[1]={60.659,41.23,68.809},		[2]={0.0,0.0,-1.0},},      --12点位置1行3
	[49] = {[1]={62.659,41.23,68.809},		[2]={0.0,0.0,-1.0},},      --12点位置1行4
	[50] = {[1]={64.66,41.23,68.809},		[2]={0.0,0.0,-1.0},},      --12点位置1行5

	[136] = {[1]={56.659,41.23,64.809},		[2]={0.0,0.0,-1.0},},      --12点位置3行1
	[137] = {[1]={58.659,41.23,64.809},		[2]={0.0,0.0,-1.0},},      --12点位置3行2
	[138] = {[1]={60.659,41.23,64.809},		[2]={0.0,0.0,-1.0},},      --12点位置3行3
	[139] = {[1]={62.659,41.23,64.809},		[2]={0.0,0.0,-1.0},},      --12点位置3行4
	[140] = {[1]={64.66,41.23,64.809},		[2]={0.0,0.0,-1.0},},      --12点位置3行5
	[141] = {[1]={56.659,41.23,62.81},		[2]={0.0,0.0,-1.0},},      --12点位置2行1
	[142] = {[1]={58.659,41.23,62.81},		[2]={0.0,0.0,-1.0},},      --12点位置2行2
	[143] = {[1]={60.659,41.23,62.81},		[2]={0.0,0.0,-1.0},},      --12点位置2行3
	[144] = {[1]={62.659,41.23,62.81},		[2]={0.0,0.0,-1.0},},      --12点位置2行4
	[145] = {[1]={64.66,41.23,62.81},		[2]={0.0,0.0,-1.0},},      --12点位置2行5
	[146] = {[1]={56.659,41.23,60.81},		[2]={0.0,0.0,-1.0},},      --12点位置1行1
	[147] = {[1]={58.659,41.23,60.81},		[2]={0.0,0.0,-1.0},},      --12点位置1行2
	[148] = {[1]={60.659,41.23,60.81},		[2]={0.0,0.0,-1.0},},      --12点位置1行3
	[149] = {[1]={62.659,41.23,60.81},		[2]={0.0,0.0,-1.0},},      --12点位置1行4
	[150] = {[1]={64.66,41.23,60.81},		[2]={0.0,0.0,-1.0},},      --12点位置1行5


	[101] = {[1]={91.86,41.23,87.809},		[2]={0.0,0.0,1.0},},	--中央点位
	[102] = {[1]={91.86,41.23,87.809},		[2]={1.0,0.0,0.0},},	--中央点位
	[103] = {[1]={91.86,41.23,87.809},		[2]={0.0,0.0,-1.0},},	--中央点位
	[104] = {[1]={91.86,41.23,87.809},		[2]={-1.0,0.0,0.0},},	--中央点位
}

ChallengeOther.MonsterTable = 
{
	[1] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42011,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={46,47,48,49,50,11,12,13,25,26,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLALL,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["time_nodes"]		= {},
		},
	[2] = 		--
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42021,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={11,12,13,25,26,34,27,28,42,44,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLALL,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["time_nodes"]		= {},
		},
	[3] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42031,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={11,12,13,14,25,26,24,1,47,49,},},
											},								
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLALL,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["time_nodes"]		= {},
		},
	[4] = 		--
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42041,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={1,2,3,7,8,11,12,26,46,50,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLALL,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["time_nodes"]		= {},
		},
	[5] = 		--单BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42051,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,47,49,},},
												{["MonterID"] = 42053,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={48,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLALL,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["time_nodes"]		= {},
		},
	[6] = 		--
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42061,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={11,12,13,25,26,1,2,8,41,45,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLALL,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["time_nodes"]		= {},
		},
	[7] = 		--
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
											    {["MonterID"] = 42071,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={11,12,13,25,26,34,27,28,47,49,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLALL,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["time_nodes"]		= {},
		},
	[8] = 		--
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
											    {["MonterID"] = 42081,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={11,12,13,14,25,26,24,42,43,44,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLALL,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["time_nodes"]		= {},
		},												
	[9] = 		--
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
											    {["MonterID"] = 42091,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={1,2,3,7,8,11,12,26,43,48,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLALL,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["time_nodes"]		= {},
		},
	[10] = 		--双BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42101,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,47,49,},},
												{["MonterID"] = 42103,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={42,},},
												{["MonterID"] = 42104,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={44,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLALL,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["time_nodes"]		= {},
		},
	[11] = 		--8+8
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42111,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42113,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42112,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={42,43,44,46,48,50,},},
												{["MonterID"] = 42113,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[12] = 		--
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42121,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42123,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42122,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={42,43,44,46,48,50,},},
												{["MonterID"] = 42123,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[13] = 		--
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42131,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42133,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42132,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={42,43,44,46,48,50,},},
												{["MonterID"] = 42133,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[14] = 		--
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42141,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42143,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42142,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={42,43,44,46,48,50,},},
												{["MonterID"] = 42143,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[15] = 		--单BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42151,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42152,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,},},
												{["MonterID"] = 42154,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[16] = 		--8+8
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42161,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42163,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42162,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={42,43,44,46,48,50,},},
												{["MonterID"] = 42163,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[17] = 		--
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42171,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42173,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42172,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={42,43,44,46,48,50,},},
												{["MonterID"] = 42173,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[18] = 		--
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42181,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42183,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42182,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={42,43,44,46,48,50,},},
												{["MonterID"] = 42183,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[19] = 		--
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42191,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42193,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42192,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={42,43,44,46,48,50,},},
												{["MonterID"] = 42193,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[20] = 		--双BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42201,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,},},
												{["MonterID"] = 42204,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},												
											},
										[2] = 
											{ 
												{["MonterID"] = 42202,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,},},
												{["MonterID"] = 42205,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[21] = 		--8+9
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42211,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42213,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42212,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42213,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[22] = 		--8+9
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42221,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42223,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42222,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42223,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[23] = 		--8+9
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42231,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42233,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42232,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42233,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[24] = 		--8+9
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42241,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42243,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42242,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42243,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[25] = 		--单BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42251,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,43,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42252,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,},},
												{["MonterID"] = 42254,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[26] = 		--8+9
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42261,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42263,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42262,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42263,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[27] = 		--8+9
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42271,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42273,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42272,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42273,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[28] = 		--8+9
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42281,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42283,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42282,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42283,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[29] = 		--8+9
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42291,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42293,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42292,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42293,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={37,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[30] = 		--双BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42301,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,},},
												{["MonterID"] = 42304,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},												
											},
										[2] = 
											{ 
												{["MonterID"] = 42302,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,48,},},
												{["MonterID"] = 42305,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[31] = 		--8+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42311,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42313,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42312,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42313,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[32] = 		--8+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42321,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42323,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42322,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42323,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[33] = 		--8+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42331,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42333,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42332,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42333,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[34] = 		--8+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42341,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42343,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42342,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42343,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[35] = 		--单BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42351,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,43,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42352,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,48,},},
												{["MonterID"] = 42354,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[36] = 		--8+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42361,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42363,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42362,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42363,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[37] = 		--8+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42371,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42373,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42372,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42373,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[38] = 		--8+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42381,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42383,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42382,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42383,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[39] = 		--8+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42391,  ["cnt"] = 6, ["buffs"] = {}, ["pos"]={142,143,144,146,148,150,},},
												{["MonterID"] = 42393,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42392,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42393,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[40] = 		--双BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42401,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,48,},},
												{["MonterID"] = 42404,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},												
											},
										[2] = 
											{ 
												{["MonterID"] = 42402,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,48,},},
												{["MonterID"] = 42405,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[41] = 		--9+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42411,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42413,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42412,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42413,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[42] = 		--9+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42421,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42423,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42422,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42423,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[43] = 		--9+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42431,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42433,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42432,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42433,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[44] = 		--9+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42441,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42443,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42442,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42443,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},	
	[45] = 		--单BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42451,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42452,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,48,},},
												{["MonterID"] = 42454,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[46] = 		--9+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42461,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42463,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42462,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42463,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[47] = 		--9+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42471,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42473,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42472,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42473,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[48] = 		--9+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42481,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42483,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42482,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42483,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[49] = 		--9+10
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42491,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42493,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42492,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={42,43,44,46,47,49,50,},},
												{["MonterID"] = 42493,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[50] = 		--双BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42501,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,},},
												{["MonterID"] = 42504,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},												
											},
										[2] = 
											{ 
												{["MonterID"] = 42502,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,48,},},
												{["MonterID"] = 42505,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[51] = 		--9+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42511,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42513,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42512,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42513,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[52] = 		--9+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42521,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42523,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42522,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42523,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[53] = 		--9+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42531,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42533,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42532,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42533,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[54] = 		--9+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42541,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42543,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42542,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42543,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[55] = 		--单BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42551,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42552,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,},},
												{["MonterID"] = 42554,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[56] = 		--9+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42561,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42563,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42562,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42563,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[57] = 		--9+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42571,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42573,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42572,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42573,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[58] = 		--9+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42581,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42583,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42582,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42583,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[59] = 		--9+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42591,  ["cnt"] = 7, ["buffs"] = {}, ["pos"]={142,143,144,146,147,149,150,},},
												{["MonterID"] = 42593,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42592,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42593,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[60] = 		--双BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42601,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,},},
												{["MonterID"] = 42604,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},												
											},
										[2] = 
											{ 
												{["MonterID"] = 42602,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,},},
												{["MonterID"] = 42605,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[61] = 		--10+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42611,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42613,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42612,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42613,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[62] = 		--10+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42621,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42623,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42622,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42623,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[63] = 		--10+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42631,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42633,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42632,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42633,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[64] = 		--10+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42641,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42643,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42642,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42643,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[65] = 		--单BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42651,  ["cnt"] = 11, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,43,44,},},
												},
										[2] = 
											{ 
												{["MonterID"] = 42652,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,},},
												{["MonterID"] = 42654,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[66] = 		--10+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42661,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42663,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42662,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42663,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[67] = 		--10+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42671,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42673,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42672,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42673,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[68] = 		--10+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42681,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42683,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42682,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42683,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[69] = 		--10+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42691,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42693,  ["cnt"] = 2, ["buffs"] = {}, ["pos"]={137,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42692,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42693,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[70] = 		--双BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42701,  ["cnt"] = 11, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,38,},},
												{["MonterID"] = 42704,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},												
											},
										[2] = 
											{ 
												{["MonterID"] = 42702,  ["cnt"] = 10, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,},},
												{["MonterID"] = 42705,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[71] = 		--11+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42711,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42713,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42712,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42713,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[72] = 		--11+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42721,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42723,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42722,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42723,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[73] = 		--11+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42731,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42733,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42732,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42733,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[74] = 		--11+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42741,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42743,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42742,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42743,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[75] = 		--单BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42751,  ["cnt"] = 11, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,43,44,},},
												},
										[2] = 
											{ 
												{["MonterID"] = 42752,  ["cnt"] = 11, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,43,44,},},
												{["MonterID"] = 42754,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={38,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[76] = 		--11+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42761,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42763,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42762,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42763,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[77] = 		--11+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42771,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42773,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42772,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42773,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[78] = 		--11+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42781,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42783,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42782,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42783,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[79] = 		--11+11
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42791,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42793,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42792,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,},},
												{["MonterID"] = 42793,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[80] = 		--双BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42801,  ["cnt"] = 11, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,38,},},
												{["MonterID"] = 42804,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},												
											},
										[2] = 
											{ 
												{["MonterID"] = 42802,  ["cnt"] = 11, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,38,},},
												{["MonterID"] = 42805,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[81] = 		--11+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42811,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42813,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42812,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42813,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[82] = 		--11+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42821,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42823,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42822,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42823,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[83] = 		--11+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42831,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42833,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42832,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42833,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[84] = 		--11+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42841,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42843,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42842,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42843,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},	
	[85] = 		--单BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42851,  ["cnt"] = 12, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,43,44,38,},},
												},
										[2] = 
											{ 
												{["MonterID"] = 42852,  ["cnt"] = 11, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,43,44,},},
												{["MonterID"] = 42854,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={38,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[86] = 		--11+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42861,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42863,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42862,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42863,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},	
	[87] = 		--11+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42871,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42873,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42872,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42873,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},	
	[88] = 		--11+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42881,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42883,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42882,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42883,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},	
	[89] = 		--11+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42891,  ["cnt"] = 8, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,},},
												{["MonterID"] = 42893,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42892,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42893,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},	
	[90] = 		--双BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42901,  ["cnt"] = 12, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,37,39,},},
												{["MonterID"] = 42904,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},												
											},
										[2] = 
											{ 
												{["MonterID"] = 42902,  ["cnt"] = 11, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,38,},},
												{["MonterID"] = 42905,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[91] = 		--12+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42911,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,1,},},
												{["MonterID"] = 42913,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42912,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42913,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},	
	[92] = 		--12+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42921,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,1,},},
												{["MonterID"] = 42923,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42922,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42923,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},	
	[93] = 		--12+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42931,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,1,},},
												{["MonterID"] = 42933,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42932,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42933,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},	
	[94] = 		--12+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42941,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,1,},},
												{["MonterID"] = 42943,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42942,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42943,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},		

	[95] = 		--单BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42951,  ["cnt"] = 12, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,43,44,38,},},
												},
										[2] = 
											{ 
												{["MonterID"] = 42952,  ["cnt"] = 12, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,43,44,48,},},
												{["MonterID"] = 42954,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={38,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},
	[96] = 		--12+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42961,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,1,},},
												{["MonterID"] = 42963,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42962,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42963,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},	
	[97] = 		--12+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42971,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,1,},},
												{["MonterID"] = 42973,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42972,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42973,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},	
	[98] = 		--12+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42981,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,1,},},
												{["MonterID"] = 42983,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42982,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42983,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},	
	[99] = 		--12+12
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42991,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={142,143,144,146,147,148,149,150,1,},},
												{["MonterID"] = 42993,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={137,138,139,},},
											},
										[2] = 
											{ 
												{["MonterID"] = 42992,  ["cnt"] = 9, ["buffs"] = {}, ["pos"]={42,43,44,46,47,48,49,50,11,},},
												{["MonterID"] = 42993,  ["cnt"] = 3, ["buffs"] = {}, ["pos"]={37,38,39,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 5,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},	
	[100] = 		--双BOSS
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 42001,  ["cnt"] = 12, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,37,39,},},
												{["MonterID"] = 42004,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},												
											},
										[2] = 
											{ 
												{["MonterID"] = 42002,  ["cnt"] = 12, ["buffs"] = {}, ["pos"]={1,2,3,4,5,6,7,8,42,44,37,39,},},
												{["MonterID"] = 42005,  ["cnt"] = 1, ["buffs"] = {}, ["pos"]={43,},},
											},
									},
				["win_type"]		= ChallengeOther.WIN_TYPE_KILLBYWAVE,
				["hum_pos"]			= 9,
				["winTime"]			= 60,
				["win_param"]		= 2,
				["time_nodes"]		= {10},
		},

}
	