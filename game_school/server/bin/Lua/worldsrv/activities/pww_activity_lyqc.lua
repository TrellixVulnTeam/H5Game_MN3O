--单人玩法，炼狱千层

CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------

--策划配置项，预设BOSS坐标，小怪坐标，BOSS在前，小怪在后
--怪物刷新，根据关卡层数，设定每层小怪ID组，个数，BOSSid组，个数
local MonsterPos = {
			["Boss"] = {{87,21,91},{86,21,91},{88,21,91},},
			["Monst"] = {{87,21,86},{88,21,86},{86,21,86},},
		}
		
CurrentDungeonScript.monstertable = {47301,47302,47303,47311,47312,47313,47321,47322,47323,47331,47332,47333,47341,47342,47343,47351,47352,47353,47361,47362,47363,47371,47372,47373,47381,47382,47383,47391,47392,47393,}
CurrentDungeonScript.bosstable = {47304,47305,47314,47315,47324,47325,47334,47335,47344,47345,47354,47355,47364,47365,47374,47375,47384,47385,47394,47395}

CurrentDungeonScript.MonstTable = {
	[1] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 20,
			},
	[2] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 21,
			},
	[3] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 22,
			},
	[4] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 23,
			},
	[5] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 0,
			["bossid"] = {47304},
			["bosscnt"] = 1,
			["timer"] = 24,
			},
	[6] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 25,
			},
	[7] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 26,
			},
	[8] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 27,
			},		
	[9] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 28,
			},		
	[10] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 0,
			["bossid"] = {47305},
			["bosscnt"] = 1,
			["timer"] = 29,
			},		
	[11] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 31,
			},	
	[12] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 32,
			},	
	[13] = {
				["monsterid"] = {47301,47302,47303,47311,47312,47313},
				["monstercnt"] = 3,
				["bossid"] = {},
				["bosscnt"] = 0,
				["timer"] = 33,
				},	
	[14] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 34,
			},	
	[15] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 0,
			["bossid"] = {47314},
			["bosscnt"] = 1,
			["timer"] = 35,
			},	
	[16] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 36,
			},	
	[17] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 37,
			},	
	[18] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 38,
			},	
	[19] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 39,
			},	
	[20] = {
			["monsterid"] = {47301,47302,47303,47311,47312,47313},
			["monstercnt"] = 0,
			["bossid"] = {47315},
			["bosscnt"] = 1,
			["timer"] = 40,
			},	
	[21] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 20,
			},
	[22] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 21,
			},
	[23] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 22,
			},
	[24] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 23,
			},
	[25] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 0,
			["bossid"] = {47324},
			["bosscnt"] = 1,
			["timer"] = 24,
			},
	[26] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 25,
			},
	[27] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 26,
			},
	[28] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 27,
			},		
	[29] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 28,
			},		
	[30] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 0,
			["bossid"] = {47325},
			["bosscnt"] = 1,
			["timer"] = 29,
			},		
	[31] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 31,
			},	
	[32] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 32,
			},	
	[33] = {
				["monsterid"] = {47321,47322,47323,47331,47332,47333},
				["monstercnt"] = 3,
				["bossid"] = {},
				["bosscnt"] = 0,
				["timer"] = 33,
				},	
	[34] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 34,
			},	
	[35] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 0,
			["bossid"] = {47334},
			["bosscnt"] = 1,
			["timer"] = 35,
			},	
	[36] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 36,
			},	
	[37] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 37,
			},	
	[38] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 38,
			},	
	[39] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 39,
			},	
	[40] = {
			["monsterid"] = {47321,47322,47323,47331,47332,47333},
			["monstercnt"] = 0,
			["bossid"] = {47335},
			["bosscnt"] = 1,
			["timer"] = 40,
			},	
	[41] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 20,
			},
	[42] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 21,
			},
	[43] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 22,
			},
	[44] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 23,
			},
	[45] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 0,
			["bossid"] = {47344},
			["bosscnt"] = 1,
			["timer"] = 24,
			},
	[46] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 25,
			},
	[47] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 26,
			},
	[48] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 27,
			},		
	[49] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 28,
			},		
	[50] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 0,
			["bossid"] = {47345},
			["bosscnt"] = 1,
			["timer"] = 29,
			},		
	[51] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 31,
			},	
	[52] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 32,
			},	
	[53] = {
				["monsterid"] = {47341,47342,47342,47351,47352,47353},
				["monstercnt"] = 3,
				["bossid"] = {},
				["bosscnt"] = 0,
				["timer"] = 33,
				},	
	[54] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 34,
			},	
	[55] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 0,
			["bossid"] = {47354},
			["bosscnt"] = 1,
			["timer"] = 35,
			},	
	[56] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 36,
			},	
	[57] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 37,
			},	
	[58] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 38,
			},	
	[59] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 39,
			},	
	[60] = {
			["monsterid"] = {47341,47342,47342,47351,47352,47353},
			["monstercnt"] = 0,
			["bossid"] = {47355},
			["bosscnt"] = 1,
			["timer"] = 40,
			},
	[61] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 20,
			},
	[62] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 21,
			},
	[63] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 22,
			},
	[64] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 23,
			},
	[65] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 0,
			["bossid"] = {47364},
			["bosscnt"] = 1,
			["timer"] = 24,
			},
	[66] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 25,
			},
	[67] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 26,
			},
	[68] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 27,
			},		
	[69] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 28,
			},		
	[70] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 0,
			["bossid"] = {47365},
			["bosscnt"] = 1,
			["timer"] = 29,
			},		
	[71] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 31,
			},	
	[72] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 32,
			},	
	[73] = {
				["monsterid"] = {47361,47362,47363,47371,47372,47373},
				["monstercnt"] = 3,
				["bossid"] = {},
				["bosscnt"] = 0,
				["timer"] = 33,
				},	
	[74] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 34,
			},	
	[75] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 0,
			["bossid"] = {47374},
			["bosscnt"] = 1,
			["timer"] = 35,
			},	
	[76] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 36,
			},	
	[77] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 37,
			},	
	[78] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 38,
			},	
	[79] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 39,
			},	
	[80] = {
			["monsterid"] = {47361,47362,47363,47371,47372,47373},
			["monstercnt"] = 0,
			["bossid"] = {47375},
			["bosscnt"] = 1,
			["timer"] = 40,
			},	
    [81] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 20,
			},
	[82] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 21,
			},
	[83] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 22,
			},
	[84] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 23,
			},
	[85] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 0,
			["bossid"] = {47384},
			["bosscnt"] = 1,
			["timer"] = 24,
			},
	[86] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 25,
			},
	[87] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 26,
			},
	[88] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 27,
			},		
	[89] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 28,
			},		
	[90] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 0,
			["bossid"] = {47385},
			["bosscnt"] = 1,
			["timer"] = 29,
			},		
	[91] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 31,
			},	
	[92] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 32,
			},	
	[93] = {
				["monsterid"] = {47381,47382,47383,47391,47392,47393},
				["monstercnt"] = 3,
				["bossid"] = {},
				["bosscnt"] = 0,
				["timer"] = 33,
				},	
	[94] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 34,
			},	
	[95] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 0,
			["bossid"] = {47394},
			["bosscnt"] = 1,
			["timer"] = 35,
			},	
	[96] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 36,
			},	
	[97] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 37,
			},	
	[98] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 38,
			},	
	[99] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 3,
			["bossid"] = {},
			["bosscnt"] = 0,
			["timer"] = 39,
			},	
	[100] = {
			["monsterid"] = {47381,47382,47383,47391,47392,47393},
			["monstercnt"] = 0,
			["bossid"] = {47395},
			["bosscnt"] = 1,
			["timer"] = 40,
			},		
}


CurrentDungeonScript.current_wave = 0 --记录当前挑战层数
CurrentDungeonScript.CurrentWaveStarttime = 0
CurrentDungeonScript.CurrentMonsCount = 0	--当前波数怪物数量
CurrentDungeonScript.MaxWave = 100 	--最大波数
CurrentDungeonScript.Timer_begain = 5		--开场倒计时
CurrentDungeonScript.isdungeonend = 0




function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
	self.SModLogicLYQC = self.Stage:GetModLogic():cast("SModLogicHellTrial")
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
	SetEventHandler(StageEvents.HumanLeave,"HumanLeave")
    SetEventHandler(StageEvents.HumanKilled,"OnHumanKilled")
	for k , v in pairs(self.monstertable) do
		SetEventHandler(StageEvents.CreatureKilled,"OnMonsterKilled",{type = v})	
	end
	for m , n in pairs(self.bosstable) do
		SetEventHandler(StageEvents.CreatureKilled,"OnMonsterKilled",{type = n})	
	end

	SetEventHandler(StageEvents.CreatureSpawn,"OnMonsterSpawn")  --怪物刷新
end

function CurrentDungeonScript:HumanEnterEvent(human)
	self.Stage:GetModDetour():EnableMotionBlock(0,true)
	self.SModDungeonScript:PlotStart()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(self.Timer_begain))
	self.SModDungeonScript:CreateTimer(self.Timer_begain,"OnTimer_DungeonStart")
	
	--[[
	self.current_wave = self.SModLogicLYQC:GetMyRound()
	if self.current_wave == 0 then
		self.SModLogicLYQC:EndedRound(self.current_wave,30)	--开场弹UI，提交波数、时间
	else
		self.SModLogicLYQC:EndedRound(self.current_wave - 1,30)	--开场弹UI，提交波数、时间
	end]]
end
function CurrentDungeonScript:OnTimer_DungeonStart()
	--开场
	
	self.SModDungeonScript:PlotClean()
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"")
	self:SpawnMonster()
	
end

--刷怪
function CurrentDungeonScript:SpawnMonster()
	if self.SModLogicLYQC:GetCostRound() > 0 then
		self.current_wave = self.SModLogicLYQC:GetCostRound()
	else
		self.current_wave = self.SModLogicLYQC:GetMyRound()
		self.current_wave = self.current_wave + 1
	end
	self.MainHuman:CloseHint(0)
	self.SModLogicLYQC:StartRound(self.current_wave,self.MonstTable[self.current_wave].timer)	--开启战斗，提交波数
	self.CurrentWaveStarttime = os.time()	--记录开启时间
	self.Timer_fight = self.SModDungeonScript:CreateTimer(self.MonstTable[self.current_wave].timer,"OnTimer_DungeonFaild")	--限定时间挑战
	
	self.CurrentMonsCount = self.MonstTable[self.current_wave].monstercnt + self.MonstTable[self.current_wave].bosscnt
	math.random(#self.MonstTable)
	for i = 1,self.MonstTable[self.current_wave].monstercnt do
		self.SModDungeonScript:SpawnMonsterRandom(MonsterPos.Monst[i],0,self.MonstTable[self.current_wave].monsterid[math.random(#self.MonstTable[self.current_wave].monsterid)],1)
	end
	for j = 1,self.MonstTable[self.current_wave].bosscnt do
		self.SModDungeonScript:SpawnMonsterRandom(MonsterPos.Boss[j],0,self.MonstTable[self.current_wave].bossid[math.random(#self.MonstTable[self.current_wave].bossid)],1)
	end
	
end
--时间到 了，挑战失败
function CurrentDungeonScript:OnTimer_DungeonFaild()
	self:DungeonFaild()
end
--怪物被击杀
function CurrentDungeonScript:OnMonsterKilled(creature)
	self.CurrentMonsCount = self.CurrentMonsCount -1
	if self.CurrentMonsCount == 0 then
		--该层挑战结束
		if self.Timer_fight ~= nil then self.SModDungeonScript:CancelTimer(self.Timer_fight) end	--关闭计时器
		local TimeUse = os.time() - self.CurrentWaveStarttime
		
		
		if self.SModLogicLYQC:GetCostRound() > 0 then
			self.isdungeonend = 1
			self.MainHuman:GetModAura():Create(304) --无敌无表现
			self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"")
			self.MainHuman:Hint(41883,30000)
			self.SModLogicLYQC:EndedRound(self.SModLogicLYQC:GetCostRound(),TimeUse)	--结束战斗，提交波数、时间
			self.SModLogicLYQC:Finish()
		else
			self.SModLogicLYQC:EndedRound(self.current_wave,TimeUse)	--结束战斗，提交波数、时间
			if self.current_wave < self.MaxWave then	--还没通关
				self.SModDungeonScript:CreateTimer(5,"OnTimer_OpenNext")
				self.MainHuman:Hint(41881,30000)
			else --全部通关
				self.isdungeonend = 1
				self.MainHuman:GetModAura():Create(304) --无敌无表现
				self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"")
				self.MainHuman:Hint(41883,30000)
				self.Stage:GetModObjs():BroadcastNotifyWithFaction(102010,ChannelType.Announcement,2,1,self.current_wave)
				self.SModLogicLYQC:Finish()
			end
		end
	end
end

--开启下一波
function CurrentDungeonScript:OnTimer_OpenNext()
	self:SpawnMonster()
end

--挑战失败
function CurrentDungeonScript:DungeonFaild()
	self.isdungeonend = 1
	self.SModLogicLYQC:Finish()
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k , v in pairs(CreatureTab) do
		v:LeaveWorld(0)
	end
	if self.MainHuman:IsDead() then
		self.MainHuman:GetModRealive():Realive(self.MainHuman:GetPosition(), 1)
		self.MainHuman:GetModAura():Create(304) --无敌无表现
	end
	self.MainHuman:Hint(41882,30000)

	local plmax_wave = self.SModLogicLYQC:GetMyRound()
	self.Stage:GetModObjs():BroadcastNotifyWithFaction(102009,ChannelType.Announcement,2,1,plmax_wave)
	self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"")
end



function CurrentDungeonScript:HumanLeave(human)  
	if human:GetModQuest():GetQuestStatus(10065) == 2 then
		human:GetModQuest():DoneQuest(10065)
	end
	self.Stage:GetModDungeonScript():Cleanup()
end
function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end

function CurrentDungeonScript:OnHumanKilled(human,killer)
	if self.isdungeonend == 1 then	
		human:GetModRealive():Realive(human:GetPosition(),1)
	else
		human:GetModRealive():SetRealiveDelay(5000)
	end
end

--怪物刷新 加属性
function CurrentDungeonScript:OnMonsterSpawn(creature)
	self.SModLogicLYQC:AdjustMonsterAttrs(creature,self.current_wave)	--修改怪物属性
end

