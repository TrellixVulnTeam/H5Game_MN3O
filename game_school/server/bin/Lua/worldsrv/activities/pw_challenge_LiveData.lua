

ChallengeLive = {}

ChallengeLive.WIN_TYPE_KILLALL 		= 1		--全部杀死通关
ChallengeLive.WIN_TYPE_KILLBYWAVE		= 2		--塔防N波怪通关
-------修改任何一点的通关时间，记得修改逻辑脚本中的提示内容@杨磊
----刷怪点
ChallengeLive.MonsterPosition = {
	
	[1] = {[1]={60.619,41.25,54.099},		[2]={0.0,0.0,1.0},},	 ---玩家入场点
	
	[2] = {[1]={48.189,41.25,69.599},		[2]={0.0,0.0,-1.0},},	--远程怪点
	[3] = {[1]={73.389,41.25,70.099},		[2]={0.0,0.0,-1.0},},	--远程怪点
	[4] = {[1]={63.49,41.25,69.599},		[2]={0.0,0.0,-1.0},},	--远程怪点
	[5] = {[1]={60.689,41.25,69.8},		[2]={0.0,0.0,-1.0},},	--远程怪点
	[6] = {[1]={57.59,41.25,69.9},	    	[2]={0.0,0.0,-1.0},},	--远程怪点
	
	[7] = {[1]={67.089,41.25,61.959},		[2]={0.0,0.0,-1.0},},	--近战怪点
	[8] = {[1]={63.689,41.25,61.959},		[2]={0.0,0.0,-1.0},},	--近战怪点
	[9] = {[1]={60.689,41.25,61.959},		[2]={0.0,0.0,-1.0},},	--近战怪点
	[10] = {[1]={57.689,41.25,61.959},		[2]={0.0,0.0,-1.0},},	--近战怪点	
	[11] = {[1]={54.689,41.25,61.959},		[2]={0.0,0.0,-1.0},},	--近战怪点

----只用了上面这部分
	
	[12] = {[1]={40.387,28,41.24},		[2]={-0.4,0.0,-0.9},},	--外圈1点 
	[13] = {[1]={41.51,28,36.74},		[2]={-0.7,0.0,-0.7},},	--外圈1点30
	[14] = {[1]={45.61,28,34.1},		[2]={-0.9,0.0,-0.4},},	--外圈2点 
	[15] = {[1]={47.11,28,30.73},		[2]={-1.0,0.0,0.0},},	--外圈3点
	[16] = {[1]={45.61,28,24.51},		[2]={-0.9,0.0,0.4},},	--外圈4点 
	[17] = {[1]={41.51,28,26.26},		[2]={-0.7,0.0,0.7},},	--外圈4点30
	[18] = {[1]={40.187,28,21.66},		[2]={-0.4,0.0,0.9},},	--外圈5点 
	[19] = {[1]={32.587,28,19.72},		[2]={0.0,0.0,1.0},},	--外圈6点
	[20] = {[1]={24.487,28,21.66},		[2]={0.4,0.0,0.9},},	--外圈7点 
	[21] = {[1]={23.9,28,26.26},		[2]={0.7,0.0,0.7},},	--外圈7点30
	[22] = {[1]={19.6,28,24.61},   	[2]={0.9,0.0,0.4},},	--外圈8点 
	[23] = {[1]={17.9,28,30.73},		[2]={1.0,0.0,0.0},},	--外圈9点
	[24] = {[1]={19.6,28,34},	    	[2]={0.9,0.0,-0.4},},	--外圈10点 
	[25] = {[1]={23.9,28,36.74},		[2]={0.7,0.0,-0.7},},	--外圈10点30
	[26] = {[1]={24.487,28,41.24},		[2]={0.4,0.0,-0.9},},	--外圈11点

	[27] = {[1]={36.56,28,45.68},		[2]={0.0,0.0,-1.0},},	--12点佛像下
	[28] = {[1]={44.81,28,39.9},		[2]={-0.7,0.0,-0.7},},	--1点30佛像下 
	[29] = {[1]={44.36,28,30.73},		[2]={-1.0,0.0,0.0},},	--3点楼梯口
	[30] = {[1]={43.96,28,22.71},  	[2]={-0.7,0.0,0.7},},	--4点30佛像下
	[31] = {[1]={32.62,28,24.39},		[2]={0.0,0.0,1.0},},	--6点门口
	[32] = {[1]={21.2,28,22.67},		[2]={0.7,0.0,0.7},},	--7点30佛像下
	[33] = {[1]={20.7,28,30.76},		[2]={1.0,0.0,0.0},},	--9点楼梯口
	[34] = {[1]={20.8,28,40.02},		[2]={0.7,0.0,-0.7},},	--10点30佛像下

	[36] = {[1]={28.587,28,41.56},		[2]={0.0,0.0,-1.0},},      --12点位置3行1
	[37] = {[1]={30.587,28,41.56},		[2]={0.0,0.0,-1.0},},      --12点位置3行2
	[38] = {[1]={32.587,28,41.56},		[2]={0.0,0.0,-1.0},},      --12点位置3行3
	[39] = {[1]={34.587,28,41.56},		[2]={0.0,0.0,-1.0},},      --12点位置3行4
	[40] = {[1]={36.587,28,41.56},		[2]={0.0,0.0,-1.0},},      --12点位置3行5
	[41] = {[1]={28.587,28,39.56},		[2]={0.0,0.0,-1.0},},      --12点位置2行1
	[42] = {[1]={30.587,28,39.56},		[2]={0.0,0.0,-1.0},},      --12点位置2行2
	[43] = {[1]={32.587,28,39.56},		[2]={0.0,0.0,-1.0},},      --12点位置2行3
	[44] = {[1]={34.587,28,39.56},		[2]={0.0,0.0,-1.0},},      --12点位置2行4
	[45] = {[1]={36.587,28,39.56},		[2]={0.0,0.0,-1.0},},      --12点位置2行5
	[46] = {[1]={28.587,28,37.56},		[2]={0.0,0.0,-1.0},},      --12点位置1行1
	[47] = {[1]={30.587,28,37.56},		[2]={0.0,0.0,-1.0},},      --12点位置1行2
	[48] = {[1]={32.587,28,37.56},		[2]={0.0,0.0,-1.0},},      --12点位置1行3
	[49] = {[1]={34.587,28,37.56},		[2]={0.0,0.0,-1.0},},      --12点位置1行4
	[50] = {[1]={36.587,28,37.56},		[2]={0.0,0.0,-1.0},},      --12点位置1行5

	[136] = {[1]={28.587,28,33.56},		[2]={0.0,0.0,-1.0},},      --12点位置3行1
	[137] = {[1]={30.587,28,33.56},		[2]={0.0,0.0,-1.0},},      --12点位置3行2
	[138] = {[1]={32.587,28,33.56},		[2]={0.0,0.0,-1.0},},      --12点位置3行3
	[139] = {[1]={34.587,28,33.56},		[2]={0.0,0.0,-1.0},},      --12点位置3行4
	[140] = {[1]={36.587,28,33.56},		[2]={0.0,0.0,-1.0},},      --12点位置3行5
	[141] = {[1]={28.587,28,31.56},		[2]={0.0,0.0,-1.0},},      --12点位置2行1
	[142] = {[1]={30.587,28,31.56},		[2]={0.0,0.0,-1.0},},      --12点位置2行2
	[143] = {[1]={32.587,28,31.56},		[2]={0.0,0.0,-1.0},},      --12点位置2行3
	[144] = {[1]={34.587,28,31.56},		[2]={0.0,0.0,-1.0},},      --12点位置2行4
	[145] = {[1]={36.587,28,31.56},		[2]={0.0,0.0,-1.0},},      --12点位置2行5
	[146] = {[1]={28.587,28,29.56},		[2]={0.0,0.0,-1.0},},      --12点位置1行1
	[147] = {[1]={30.587,28,29.56},		[2]={0.0,0.0,-1.0},},      --12点位置1行2
	[148] = {[1]={32.587,28,29.56},		[2]={0.0,0.0,-1.0},},      --12点位置1行3
	[149] = {[1]={34.587,28,29.56},		[2]={0.0,0.0,-1.0},},      --12点位置1行4
	[150] = {[1]={36.587,28,29.56},		[2]={0.0,0.0,-1.0},},      --12点位置1行5


	[101] = {[1]={63.75,0.1,56.54},		[2]={0.0,0.0,1.0},},	--中央点位
	[102] = {[1]={63.75,0.1,56.54},		[2]={1.0,0.0,0.0},},	--中央点位
	[103] = {[1]={63.75,0.1,56.54},		[2]={0.0,0.0,-1.0},},	--中央点位
	[104] = {[1]={63.75,0.1,56.54},		[2]={-1.0,0.0,0.0},},	--中央点位
}

ChallengeLive.MonsterTable = 
{
	[1] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47001,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},

	[2] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47002,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[3] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47003,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[4] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47004,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[5] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47005,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47105,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[6] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47006,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},

	[7] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47007,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[8] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47008,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[9] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47009,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[10] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47010,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47110,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[11] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47011,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[12] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47012,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[13] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47013,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[14] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47014,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[15] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47015,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47115,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[16] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47016,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[17] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47017,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[18] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47018,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[19] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47019,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[20] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47020,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47120,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[21] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47021,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[22] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47022,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[23] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47023,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[24] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47024,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[25] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47025,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47125,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[26] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47026,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[27] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47027,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[28] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47028,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[29] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47029,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[30] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47030,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47130,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[31] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47031,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[32] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47032,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[33] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47033,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[34] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47034,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[35] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47035,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47135,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[36] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47036,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[37] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47037,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[38] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47038,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[39] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47039,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[40] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47040,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47140,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[41] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47041,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[42] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47042,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[43] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47043,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[44] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47044,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[45] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47045,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47145,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[46] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47046,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[47] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47047,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[48] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47048,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[49] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47049,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[50] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47050,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47150,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[51] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47051,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},
	[52] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47052,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[53] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47053,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[54] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47054,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[55] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47055,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47155,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[56] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47056,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[57] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47057,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[58] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47058,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[59] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47059,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[60] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47060,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47160,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[61] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47061,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[62] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47062,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[63] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47063,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[64] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47064,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[65] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47065,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47165,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[66] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47066,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[67] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47067,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[68] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47068,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[69] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47069,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[70] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47070,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47170,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[71] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47071,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[72] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47072,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[73] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47073,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[74] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47074,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[75] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47075,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47175,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[76] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47076,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[77] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47077,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[78] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47078,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[79] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47079,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[80] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47080,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47180,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[81] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47081,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[82] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47082,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[83] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47083,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[84] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47084,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[85] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47085,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47185,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[86] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47086,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[87] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47087,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[88] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47088,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	
	[89] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47089,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	

	[90] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47090,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47190,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	

	[91] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47091,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	

	[92] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47092,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	

	[93] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47093,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	

	[94] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47094,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	

	[95] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47095,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47195,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	

	[96] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47096,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	


	[97] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47097,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	

	[98] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47098,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	

	[99] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47099,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	

	[100] = 		--												
		{
				["monster_table"]	= 
									{
										[1] = 
											{ 
												{["MonterID"] = 47100,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={2,3,4,5,6,},},
												{["MonterID"] = 47200,  ["cnt"] = 5, ["buffs"] = {}, ["pos"]={7,8,9,10,11,},},
											},
									},
				["win_type"]		= ChallengeLive.WIN_TYPE_KILLALL,
				["hum_pos"]			= 1,
				["winTime"]			= 45,
				["time_nodes"]		= {},
		},	

}



		