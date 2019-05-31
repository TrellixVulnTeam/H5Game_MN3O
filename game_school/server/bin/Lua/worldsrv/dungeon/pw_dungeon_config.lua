--通用副本配置

DUNGEON_ID = {--所有应用到通用逻辑的需要先将副本ID填入该table
				5001,5002,5003,5004,5005,5006,5007,5008,5009,5010,
				5011,5012,5013,5014,5015,5016,5017,5018,5019,5020,
				5021,5022,5023,5024,5025,5026,5027,5028,5029,5030,
				5031,5032,5033,5034,5035,5036,5037,5038,5039,5040,
				5041,5042,5043,5044,5045,5046,5047,5048,5049,5050,
				5051,5052,5053,5054,5055,5056,5057,5058,5059,5060,		
				5061,5062,5063,5064,5065,5066,5067,5068,5069,5070,	
                5071,5072,5073,5074,5075,5076,5077,5078,5079,5080,
                5081,5082,5083,5084,5085,5086,5087,5088,5089,5090,	
				5091,5092,5093,5094,5095,5096,5097,5098,5099,5100,	
				5101,5102,5103,5104,5105,5106,5107,5108,5109,5110,	
				5111,5112,5113,5114,5115,5116,5117,5118,5119,5120,	
				5121,5122,5123,5124,5125,5126,5127,5128,5129,5130,					
								}
DUNGEON_CONFIG = {}


---------------------------------------
--示例，注意：不需要的模块就直接删掉不填*****
--[[
DUNGEON_CONFIG[1101] = {
	HumanEnter_DoneQuest = {1,2,3},	--角色进场，完成XX任务：参数是任务ID
	HumanEnter_PlotStart = {1,2},		--角色进场，播放XX剧情。参数：剧情ID，任务ID(XX剧情需要前提任务的时候就填任务ID)
	HumanEnter_StartHint = {1},		--角色进场，播放弱提示，只能填一个
	HumanEnter_OpenEffectWalls = {1,2,3},		--角色进场，打开特效墙。可以填多个
	HumanEnter_CreateFinger = {{pos},{angle}},		--角色进场，创建一个指路特效
	NpcKilled_CrossDungeon = {{10001,2},{10002,2},{10003,2}--击杀某ID的怪物/个数——通关：参数是怪物ID+个数
								},	
	NpcKilled_CrossDungeonRandom = {{10001,10002},50,questid = 40 --击杀某ID的怪物/总个数——通关，填写questid的话代表顺便完成任务：参数是怪物ID表+个数
								},
	CreateTrigger_SpawnMonster = {
							[1] = {{43,119,55},5,42,"scn1101_01_xiejiao",Timer = 2},
							[2] = {{43,119,55},5,42,"scn1101_01_xiejiao",Timer = 2}
									},
	CreateTrigger_DoneQuest = {
							[1] = {{43,119,55},5,42,questid,Timer = 2},
							[2] = {{43,119,55},5,42,questid,Timer = 2}
							},
	CreateTrigger_LaunchPolt = {
							[1] = {{43,119,55},5,42,plotid,Timer = 2,questid = 2},	--需要前置任务判断的时候才写questid
							[2] = {{43,119,55},5,42,plotid,Timer = 2,questid = 2}
							},
	PlotEnd_DoneQuest = {{plotid,questid,Timer = 2},{plotid,questid,Timer = 2}},
	PlotEnd_SpawnMonster = {{plotid,monster_index,Timer = 2},{plotid,monster_index,Timer = 2}},	--剧情结束刷怪
	PlotEnd_LaunchPolt = {{plotid,plotid,Timer = 2},{plotid,plotid,Timer = 2}},
	NpcKilled_KillPet = {bossid,bossid},	--怪物死亡杀死召唤的小弟
	NpcKilled_PlotStart = {
							[1] = {{{10001,2},{10002,2},{10003,2}},plotid,Timer = 2},
							[2] = {{{10001,2},{10002,2},{10003,2}},plotid,Timer = 2},
							},
	HumanEnterEnableMotionBlock = {{1,true},{2,true}}--刚刚入场时候设置XX区域可走不可走
	
	--单独为剧情副本添加新规则(注意，str填0代表不提醒，填数字可提醒播报)
	--下面这几个必须在一起填写，怪物ID这个，如果是一波波刷怪的话，目标统计总数的话，就只填写小怪，BOSS也填在小怪里当做普通计数；如果目标是击杀两个或者三个BOSS的话，就把BOSS填写在后面BOSS的表里
	JQ_CrossDungeonNpcid = {monsterid = {},bossid = {},},
	JQ_DungeonObj = {monsterstr = {},bossstr = {},}, --有几个BOSS目标就填几个str，击杀小怪总数的那种不填
	JQ_DungeonMaxTime = 100,
	NpcKilled_CrossDungeonWava = {
					[1] = {method = {"scn5170_1_xiaoguai","scn5170_1_toumu"},count = 5,str = 0},	
					[2] = {method = {"scn5170_1_xiaoguai","scn5170_1_toumu"},count = 5,str = 123},	
					[3] = {method = {"scn5170_1_boss"},count = 1,str = 123},	
						}，
	}
]]--
--注意：不需要的模块就直接删掉不填*****
--[[DUNGEON_CONFIG[5122] = {	JQ_CrossDungeonNpcid = {monsterid = {32101,32103} , bossid = {32102,32104} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {50125,50126},} ,
							JQ_DungeonMaxTime = 200 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5122_1_xiaoguai"} , count = 3,str = 0},	
										[2] = {method = {"scn5122_2_xiaoguai"},count = 3,str = 0},	
										[3] = {method = {"scn5122_boss1"},count = 1,str = 50126},	
										[4] = {method = {"scn5122_3_xiaoguai"},count = 3,str = 0},	
										[5] = {method = {"scn5122_4_xiaoguai"},count = 3,str = 0},	
										[6] = {method = {"scn5122_boss2"},count = 1,str = 0},	
													},
						}--]]





DUNGEON_CONFIG[5001] = {	
							HumanEnter_PlotStart = {6,},
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,true}},  ---false代表打开
							HumanEnter_OpenEffectWalls = {104,},
							JQ_CrossDungeonNpcid = {monsterid = {22001} , bossid = {22003} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52003,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5001_xiaoguai1"} , count = 4,str = 52001},	
										[2] = {method = {"scn5001_xiaoguai2"},count = 4,str = 52001},	
										[3] = {method = {"scn5001_xiaoguai3"},count = 4,str = 52002},											
										[4] = {method = {"scn5001_boss1"},count = 1,str = 0},	
														 },
						}

DUNGEON_CONFIG[5002] = {	
							HumanEnter_PlotStart = {7,},
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {144,},
							JQ_CrossDungeonNpcid = {monsterid = {22051} , bossid = {22053} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52006,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5002_xiaoguai1"} , count = 4,str = 52004},	
										[2] = {method = {"scn5002_xiaoguai2"},count = 4,str = 52004},	
										[3] = {method = {"scn5002_xiaoguai3"},count = 4,str = 52005},											
										[4] = {method = {"scn5002_boss1"},count = 1,str = 0},	
														 },
						}
DUNGEON_CONFIG[5003] = {	
							HumanEnter_PlotStart = {8,},
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {157,156,},
							JQ_CrossDungeonNpcid = {monsterid = {22101} , bossid = {22103} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52009,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5003_xiaoguai1"} , count = 4,str = 52007},	
										[2] = {method = {"scn5003_xiaoguai2"},count = 4,str = 52007},	
										[3] = {method = {"scn5003_xiaoguai3"},count = 4,str = 52008},											
										[4] = {method = {"scn5003_boss1"},count = 1,str = 0},	
														 },
						}
DUNGEON_CONFIG[5004] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,false}},
							JQ_CrossDungeonNpcid = {monsterid = {22151} , bossid = {22153} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52012,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5004_xiaoguai1"} , count = 5,str = 52010},	
										[2] = {method = {"scn5004_xiaoguai2"},count = 5,str = 52010},	
										[3] = {method = {"scn5004_xiaoguai3"},count = 5,str = 52011},											
										[4] = {method = {"scn5004_boss1"},count = 1,str = 0},	
														 },
						}	

DUNGEON_CONFIG[5005] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,true},{4,true},{0,false}},
							JQ_CrossDungeonNpcid = {monsterid = {22201} , bossid = {22203} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52015,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5005_xiaoguai1"} , count = 5,str = 52013},	
										[2] = {method = {"scn5005_xiaoguai2"},count = 5,str = 52013},	
										[3] = {method = {"scn5005_xiaoguai3"},count = 5,str = 52014},											
										[4] = {method = {"scn5005_boss1"},count = 1,str = 0},	
														 },
						}
DUNGEON_CONFIG[5006] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,false}},
							JQ_CrossDungeonNpcid = {monsterid = {22251} , bossid = {22253,22254} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52019,52020,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5006_xiaoguai1"} , count = 5,str = 52016},	
										[2] = {method = {"scn5006_xiaoguai2"},count = 5,str = 52016},	
										[3] = {method = {"scn5006_xiaoguai3"},count = 5,str = 52017},											
										[4] = {method = {"scn5006_boss1"},count = 1,str = 52016},
										[5] = {method = {"scn5006_xiaoguai4"},count = 5,str = 52016},
										[6] = {method = {"scn5006_xiaoguai5"},count = 5,str = 52016},	
										[7] = {method = {"scn5006_xiaoguai6"},count = 5,str = 52018},	
										[8] = {method = {"scn5006_boss2"},count = 1,str = 0},
														 },
						}	

DUNGEON_CONFIG[5007] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {120,121,124,125,},
							JQ_CrossDungeonNpcid = {monsterid = {22301} , bossid = {22303,22304} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52024,52025,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5007_xiaoguai1"} , count = 6,str = 52021},	
										[2] = {method = {"scn5007_xiaoguai2"},count = 6,str = 52021},	
										[3] = {method = {"scn5007_xiaoguai3"},count = 6,str = 52022},											
										[4] = {method = {"scn5007_boss1"},count = 1,str = 52021},
										[5] = {method = {"scn5007_xiaoguai4"},count = 6,str = 52021},
										[6] = {method = {"scn5007_xiaoguai5"},count = 6,str = 52021},	
										[7] = {method = {"scn5007_xiaoguai6"},count = 6,str = 52023},	
										[8] = {method = {"scn5007_boss2"},count = 1,str = 0},
														 },
						}

DUNGEON_CONFIG[5008] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {141,142,},
							JQ_CrossDungeonNpcid = {monsterid = {22351} , bossid = {22353,22354} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52029,52030,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5008_xiaoguai1"} , count = 6,str = 52026},	
										[2] = {method = {"scn5008_xiaoguai2"},count = 6,str = 52026},	
										[3] = {method = {"scn5008_xiaoguai3"},count = 6,str = 52027},											
										[4] = {method = {"scn5008_boss1"},count = 1,str = 52026},
										[5] = {method = {"scn5008_xiaoguai4"},count = 6,str = 52026},
										[6] = {method = {"scn5008_xiaoguai5"},count = 6,str = 52026},	
										[7] = {method = {"scn5008_xiaoguai6"},count = 6,str = 52028},	
										[8] = {method = {"scn5008_boss2"},count = 1,str = 0},
														 },
						}		
DUNGEON_CONFIG[5009] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {155,156,},
							JQ_CrossDungeonNpcid = {monsterid = {22401} , bossid = {22403,22404} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52034,52035,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5009_xiaoguai1"} , count = 6,str = 52031},	
										[2] = {method = {"scn5009_xiaoguai2"},count = 6,str = 52031},	
										[3] = {method = {"scn5009_xiaoguai3"},count = 6,str = 52032},											
										[4] = {method = {"scn5009_boss1"},count = 1,str = 52031},
										[5] = {method = {"scn5009_xiaoguai4"},count = 6,str = 52031},
										[6] = {method = {"scn5009_xiaoguai5"},count = 6,str = 52031},	
										[7] = {method = {"scn5009_xiaoguai6"},count = 6,str = 52033},	
										[8] = {method = {"scn5009_boss2"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5010] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {101,107,},
							JQ_CrossDungeonNpcid = {monsterid = {22451} , bossid = {22453,22454} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52039,52040,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5010_xiaoguai1"} , count = 7,str = 52036},	
										[2] = {method = {"scn5010_xiaoguai2"},count = 7,str = 52036},	
										[3] = {method = {"scn5010_xiaoguai3"},count = 7,str = 52037},											
										[4] = {method = {"scn5010_boss1"},count = 1,str = 52036},
										[5] = {method = {"scn5010_xiaoguai4"},count = 7,str = 52036},
										[6] = {method = {"scn5010_xiaoguai5"},count = 7,str = 52036},	
										[7] = {method = {"scn5010_xiaoguai6"},count = 7,str = 52038},	
										[8] = {method = {"scn5010_boss2"},count = 1,str = 0},
														 },
						}						
					
DUNGEON_CONFIG[5011] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {144,},
							JQ_CrossDungeonNpcid = {monsterid = {22501} , bossid = {22503} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52043,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5011_xiaoguai1"} , count = 4,str = 52041},	
										[2] = {method = {"scn5011_xiaoguai2"},count = 4,str = 52041},	
										[3] = {method = {"scn5011_xiaoguai3"},count = 4,str = 52042},											
										[4] = {method = {"scn5011_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5012] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {120,124,125,129,},
							JQ_CrossDungeonNpcid = {monsterid = {22551} , bossid = {22553} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52046,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5012_xiaoguai1"} , count = 4,str = 52044},	
										[2] = {method = {"scn5012_xiaoguai2"},count = 4,str = 52044},	
										[3] = {method = {"scn5012_xiaoguai3"},count = 4,str = 52045},											
										[4] = {method = {"scn5012_boss1"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5013] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {110,111,},
							JQ_CrossDungeonNpcid = {monsterid = {22601} , bossid = {22603} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52049,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5013_xiaoguai1"} , count = 4,str = 52047},	
										[2] = {method = {"scn5013_xiaoguai2"},count = 4,str = 52047},	
										[3] = {method = {"scn5013_xiaoguai3"},count = 4,str = 52048},											
										[4] = {method = {"scn5013_boss1"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5014] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {157,158,},
							JQ_CrossDungeonNpcid = {monsterid = {22651} , bossid = {22653} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52052,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5014_xiaoguai1"} , count = 5,str = 52050},	
										[2] = {method = {"scn5014_xiaoguai2"},count = 5,str = 52050},	
										[3] = {method = {"scn5014_xiaoguai3"},count = 5,str = 52051},											
										[4] = {method = {"scn5014_boss1"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5015] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {109,110,},
							JQ_CrossDungeonNpcid = {monsterid = {22701} , bossid = {22703} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52055,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5015_xiaoguai1"} , count = 5,str = 52053},	
										[2] = {method = {"scn5015_xiaoguai2"},count = 5,str = 52053},	
										[3] = {method = {"scn5015_xiaoguai3"},count = 5,str = 52054},											
										[4] = {method = {"scn5015_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5016] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,false}},
							JQ_CrossDungeonNpcid = {monsterid = {22751} , bossid = {22753} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52058,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5016_xiaoguai1"} , count = 5,str = 52056},	
										[2] = {method = {"scn5016_xiaoguai2"},count = 5,str = 52056},	
										[3] = {method = {"scn5016_xiaoguai3"},count = 5,str = 52056},											
										[4] = {method = {"scn5016_xiaoguai4"} , count = 5,str = 52056},	
										[5] = {method = {"scn5016_xiaoguai5"},count = 5,str = 52056},	
										[6] = {method = {"scn5016_xiaoguai6"},count = 5,str = 52057},											
										[7] = {method = {"scn5016_boss1"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5017] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,false}},
							JQ_CrossDungeonNpcid = {monsterid = {22801} , bossid = {22803} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52061,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5017_xiaoguai1"} , count = 6,str = 52059},	
										[2] = {method = {"scn5017_xiaoguai2"},count = 6,str = 52059},	
										[3] = {method = {"scn5017_xiaoguai3"},count = 6,str = 52059},											
										[4] = {method = {"scn5017_xiaoguai4"} , count = 6,str = 52059},	
										[5] = {method = {"scn5017_xiaoguai5"},count = 6,str = 52059},	
										[6] = {method = {"scn5017_xiaoguai6"},count = 6,str = 52060},											
										[7] = {method = {"scn5017_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5018] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,false}},
							JQ_CrossDungeonNpcid = {monsterid = {22851} , bossid = {22853} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52064,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5018_xiaoguai1"} , count = 6,str = 52062},	
										[2] = {method = {"scn5018_xiaoguai2"},count = 6,str = 52062},	
										[3] = {method = {"scn5018_xiaoguai3"},count = 6,str = 52062},											
										[4] = {method = {"scn5018_xiaoguai4"} , count = 6,str = 52062},	
										[5] = {method = {"scn5018_xiaoguai5"},count = 6,str = 52062},	
										[6] = {method = {"scn5018_xiaoguai6"},count = 6,str = 52063},											
										[7] = {method = {"scn5018_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5019] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {164,},
							JQ_CrossDungeonNpcid = {monsterid = {22901} , bossid = {22903} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52067,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5019_xiaoguai1"} , count = 6,str = 52065},	
										[2] = {method = {"scn5019_xiaoguai2"},count = 6,str = 52065},	
										[3] = {method = {"scn5019_xiaoguai3"},count = 6,str = 52065},											
										[4] = {method = {"scn5019_xiaoguai4"} , count = 6,str = 52065},	
										[5] = {method = {"scn5019_xiaoguai5"},count = 6,str = 52065},	
										[6] = {method = {"scn5019_xiaoguai6"},count = 6,str = 52066},											
										[7] = {method = {"scn5019_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5020] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {143,144,},
							JQ_CrossDungeonNpcid = {monsterid = {22951} , bossid = {22953} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52070,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5020_xiaoguai1"} , count = 7,str = 52068},	
										[2] = {method = {"scn5020_xiaoguai2"},count = 7,str = 52068},	
										[3] = {method = {"scn5020_xiaoguai3"},count = 7,str = 52068},											
										[4] = {method = {"scn5020_xiaoguai4"} , count = 7,str = 52068},	
										[5] = {method = {"scn5020_xiaoguai5"},count = 7,str = 52068},	
										[6] = {method = {"scn5020_xiaoguai6"},count = 7,str = 52069},											
										[7] = {method = {"scn5020_boss1"},count = 1,str = 0},
														 },
						}	

DUNGEON_CONFIG[5021] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {140,141,},
							JQ_CrossDungeonNpcid = {monsterid = {23001} , bossid = {23003} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52073,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5021_xiaoguai1"} , count = 4,str = 52071},	
										[2] = {method = {"scn5021_xiaoguai2"},count = 4,str = 52071},	
										[3] = {method = {"scn5021_xiaoguai3"},count = 4,str = 52072},											
										[4] = {method = {"scn5021_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5022] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {140,},
							JQ_CrossDungeonNpcid = {monsterid = {23051} , bossid = {23053} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52076,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5022_xiaoguai1"} , count = 4,str = 52074},	
										[2] = {method = {"scn5022_xiaoguai2"},count = 4,str = 52074},	
										[3] = {method = {"scn5022_xiaoguai3"},count = 4,str = 52075},											
										[4] = {method = {"scn5022_boss1"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5023] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {140,141,},
							JQ_CrossDungeonNpcid = {monsterid = {23101} , bossid = {23103} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52079,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5023_xiaoguai1"} , count = 4,str = 52077},	
										[2] = {method = {"scn5023_xiaoguai2"},count = 4,str = 52077},	
										[3] = {method = {"scn5023_xiaoguai3"},count = 4,str = 52078},											
										[4] = {method = {"scn5023_boss1"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5024] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {142,141,},
							JQ_CrossDungeonNpcid = {monsterid = {23151} , bossid = {23153} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52082,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5024_xiaoguai1"} , count = 5,str = 52080},	
										[2] = {method = {"scn5024_xiaoguai2"},count = 5,str = 52080},	
										[3] = {method = {"scn5024_xiaoguai3"},count = 5,str = 52081},											
										[4] = {method = {"scn5024_boss1"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5025] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {142,141,},
							JQ_CrossDungeonNpcid = {monsterid = {23201} , bossid = {23203} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52085,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5025_xiaoguai1"} , count = 5,str = 52083},	
										[2] = {method = {"scn5025_xiaoguai2"},count = 5,str = 52083},	
										[3] = {method = {"scn5025_xiaoguai3"},count = 5,str = 52084},											
										[4] = {method = {"scn5025_boss1"},count = 1,str = 0},
														 },
						}

DUNGEON_CONFIG[5026] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {141,},
							JQ_CrossDungeonNpcid = {monsterid = {23251} , bossid = {23253,23254,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52089,52090,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5026_xiaoguai1"} , count = 5,str = 52086},	
										[2] = {method = {"scn5026_xiaoguai2"},count = 5,str = 52086},	
										[3] = {method = {"scn5026_xiaoguai3"},count = 5,str = 52087},											
										[4] = {method = {"scn5026_boss1"},count = 1,str = 52086},
										[5] = {method = {"scn5026_xiaoguai4"},count = 5,str = 52086},
										[6] = {method = {"scn5026_xiaoguai5"},count = 5,str = 52086},
										[7] = {method = {"scn5026_xiaoguai6"},count = 5,str = 52088},
										[8] = {method = {"scn5026_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5027] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {140,141,},
							JQ_CrossDungeonNpcid = {monsterid = {23301} , bossid = {23303,23304,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52094,52095,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5027_xiaoguai1"} , count = 6,str = 52091},	
										[2] = {method = {"scn5027_xiaoguai2"},count = 6,str = 52091},	
										[3] = {method = {"scn5027_xiaoguai3"},count = 6,str = 52092},											
										[4] = {method = {"scn5027_boss1"},count = 1,str = 52091},
										[5] = {method = {"scn5027_xiaoguai4"},count = 6,str = 52091},
										[6] = {method = {"scn5027_xiaoguai5"},count = 6,str = 52091},
										[7] = {method = {"scn5027_xiaoguai6"},count = 6,str = 52093},
										[8] = {method = {"scn5027_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5028] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {142,141,},
							JQ_CrossDungeonNpcid = {monsterid = {23351} , bossid = {23353,23354,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52099,52100,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5028_xiaoguai1"} , count = 6,str = 52096},	
										[2] = {method = {"scn5028_xiaoguai2"},count = 6,str = 52096},	
										[3] = {method = {"scn5028_xiaoguai3"},count = 6,str = 52097},											
										[4] = {method = {"scn5028_boss1"},count = 1,str = 52096},
										[5] = {method = {"scn5028_xiaoguai4"},count = 6,str = 52096},
										[6] = {method = {"scn5028_xiaoguai5"},count = 6,str = 52096},
										[7] = {method = {"scn5028_xiaoguai6"},count = 6,str = 52098},
										[8] = {method = {"scn5028_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5029] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {142,141,},
							JQ_CrossDungeonNpcid = {monsterid = {23401} , bossid = {23403,23404,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52104,52105,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5029_xiaoguai1"} , count = 6,str = 52101},	
										[2] = {method = {"scn5029_xiaoguai2"},count = 6,str = 52101},	
										[3] = {method = {"scn5029_xiaoguai3"},count = 6,str = 52102},											
										[4] = {method = {"scn5029_boss1"},count = 1,str = 52101},
										[5] = {method = {"scn5029_xiaoguai4"},count = 6,str = 52101},
										[6] = {method = {"scn5029_xiaoguai5"},count = 6,str = 52101},
										[7] = {method = {"scn5029_xiaoguai6"},count = 6,str = 52103},
										[8] = {method = {"scn5029_boss2"},count = 1,str = 0},
														 },
						}
						
DUNGEON_CONFIG[5030] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {142,},
							JQ_CrossDungeonNpcid = {monsterid = {23451} , bossid = {23453,23454,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52109,52110,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5030_xiaoguai1"} , count = 7,str = 52106},	
										[2] = {method = {"scn5030_xiaoguai2"},count = 7,str = 52106},	
										[3] = {method = {"scn5030_xiaoguai3"},count = 7,str = 52107},											
										[4] = {method = {"scn5030_boss1"},count = 1,str = 52106},
										[5] = {method = {"scn5030_xiaoguai4"},count = 7,str = 52106},
										[6] = {method = {"scn5030_xiaoguai5"},count = 7,str = 52106},
										[7] = {method = {"scn5030_xiaoguai6"},count = 7,str = 52108},
										[8] = {method = {"scn5030_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5031] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {151,},
							JQ_CrossDungeonNpcid = {monsterid = {23501} , bossid = {23503} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52113,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5031_xiaoguai1"} , count = 4,str = 52111},	
										[2] = {method = {"scn5031_xiaoguai2"},count = 4,str = 52111},	
										[3] = {method = {"scn5031_xiaoguai3"},count = 4,str = 52112},											
										[4] = {method = {"scn5031_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5032] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {153,},
							JQ_CrossDungeonNpcid = {monsterid = {23551} , bossid = {23553} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52116,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5032_xiaoguai1"} , count = 4,str = 52114},	
										[2] = {method = {"scn5032_xiaoguai2"},count = 4,str = 52114},	
										[3] = {method = {"scn5032_xiaoguai3"},count = 4,str = 52115},											
										[4] = {method = {"scn5032_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5033] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {156,157,},
							JQ_CrossDungeonNpcid = {monsterid = {23601} , bossid = {23603} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52119,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5033_xiaoguai1"} , count = 4,str = 52117},	
										[2] = {method = {"scn5033_xiaoguai2"},count = 4,str = 52117},	
										[3] = {method = {"scn5033_xiaoguai3"},count = 4,str = 52118},											
										[4] = {method = {"scn5033_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5034] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {158,},
							JQ_CrossDungeonNpcid = {monsterid = {23651} , bossid = {23653} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52122,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5034_xiaoguai1"} , count = 5,str = 52120},	
										[2] = {method = {"scn5034_xiaoguai2"},count = 5,str = 52120},	
										[3] = {method = {"scn5034_xiaoguai3"},count = 5,str = 52121},											
										[4] = {method = {"scn5034_boss1"},count = 1,str = 0},
														 },
						}						
						
DUNGEON_CONFIG[5035] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {155,156,},
							JQ_CrossDungeonNpcid = {monsterid = {23701} , bossid = {23703} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52125,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5035_xiaoguai1"} , count = 5,str = 52123},	
										[2] = {method = {"scn5035_xiaoguai2"},count = 5,str = 52123},	
										[3] = {method = {"scn5035_xiaoguai3"},count = 5,str = 52124},											
										[4] = {method = {"scn5035_boss1"},count = 1,str = 0},
														 },
						}
						
DUNGEON_CONFIG[5036] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {150,},
							JQ_CrossDungeonNpcid = {monsterid = {23751} , bossid = {23753,23754,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52129,52130,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5036_xiaoguai1"} , count = 5,str = 52126},	
										[2] = {method = {"scn5036_xiaoguai2"},count = 5,str = 52126},	
										[3] = {method = {"scn5036_xiaoguai3"},count = 5,str = 52127},											
										[4] = {method = {"scn5036_boss1"},count = 1,str = 52126},
										[5] = {method = {"scn5036_xiaoguai4"},count = 5,str = 52126},
										[6] = {method = {"scn5036_xiaoguai5"},count = 5,str = 52126},
										[7] = {method = {"scn5036_xiaoguai6"},count = 5,str = 52128},
										[8] = {method = {"scn5036_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5037] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {152,},
							JQ_CrossDungeonNpcid = {monsterid = {23801} , bossid = {23803,23804,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52134,52135,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5037_xiaoguai1"} , count = 6,str = 52131},	
										[2] = {method = {"scn5037_xiaoguai2"},count = 6,str = 52131},	
										[3] = {method = {"scn5037_xiaoguai3"},count = 6,str = 52132},											
										[4] = {method = {"scn5037_boss1"},count = 1,str = 52131},
										[5] = {method = {"scn5037_xiaoguai4"},count = 6,str = 52131},
										[6] = {method = {"scn5037_xiaoguai5"},count = 6,str = 52131},
										[7] = {method = {"scn5037_xiaoguai6"},count = 6,str = 52133},
										[8] = {method = {"scn5037_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5038] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {156,157,},
							JQ_CrossDungeonNpcid = {monsterid = {23851} , bossid = {23853,23854,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52139,52140,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5038_xiaoguai1"} , count = 6,str = 52136},	
										[2] = {method = {"scn5038_xiaoguai2"},count = 6,str = 52136},	
										[3] = {method = {"scn5038_xiaoguai3"},count = 6,str = 52137},											
										[4] = {method = {"scn5038_boss1"},count = 1,str = 52136},
										[5] = {method = {"scn5038_xiaoguai4"},count = 6,str = 52136},
										[6] = {method = {"scn5038_xiaoguai5"},count = 6,str = 52136},
										[7] = {method = {"scn5038_xiaoguai6"},count = 6,str = 52138},
										[8] = {method = {"scn5038_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5039] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {156,155,},
							JQ_CrossDungeonNpcid = {monsterid = {23901} , bossid = {23903,23904,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52144,52145,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5039_xiaoguai1"} , count = 6,str = 52141},	
										[2] = {method = {"scn5039_xiaoguai2"},count = 6,str = 52141},	
										[3] = {method = {"scn5039_xiaoguai3"},count = 6,str = 52142},											
										[4] = {method = {"scn5039_boss1"},count = 1,str = 52141},
										[5] = {method = {"scn5039_xiaoguai4"},count = 6,str = 52141},
										[6] = {method = {"scn5039_xiaoguai5"},count = 6,str = 52141},
										[7] = {method = {"scn5039_xiaoguai6"},count = 6,str = 52143},
										[8] = {method = {"scn5039_boss2"},count = 1,str = 0},
														 },
						}
						
DUNGEON_CONFIG[5040] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {158,},
							JQ_CrossDungeonNpcid = {monsterid = {23951} , bossid = {23953,23954,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52149,52150,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5040_xiaoguai1"} , count = 7,str = 52146},	
										[2] = {method = {"scn5040_xiaoguai2"},count = 7,str = 52146},	
										[3] = {method = {"scn5040_xiaoguai3"},count = 7,str = 52147},											
										[4] = {method = {"scn5040_boss1"},count = 1,str = 52146},
										[5] = {method = {"scn5040_xiaoguai4"},count = 7,str = 52146},
										[6] = {method = {"scn5040_xiaoguai5"},count = 7,str = 52146},
										[7] = {method = {"scn5040_xiaoguai6"},count = 7,str = 52148},
										[8] = {method = {"scn5040_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5041] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {159,},
							JQ_CrossDungeonNpcid = {monsterid = {24001} , bossid = {24003} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52153,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5041_xiaoguai1"} , count = 4,str = 52151},	
										[2] = {method = {"scn5041_xiaoguai2"},count = 4,str = 52151},	
										[3] = {method = {"scn5041_xiaoguai3"},count = 4,str = 52152},											
										[4] = {method = {"scn5041_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5042] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {160,161,},
							JQ_CrossDungeonNpcid = {monsterid = {24051} , bossid = {24053} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52156,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5042_xiaoguai1"} , count = 4,str = 52154},	
										[2] = {method = {"scn5042_xiaoguai2"},count = 4,str = 52154},	
										[3] = {method = {"scn5042_xiaoguai3"},count = 4,str = 52155},											
										[4] = {method = {"scn5042_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5043] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {162,163,},
							JQ_CrossDungeonNpcid = {monsterid = {24101} , bossid = {24103} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52159,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5043_xiaoguai1"} , count = 4,str = 52157},	
										[2] = {method = {"scn5043_xiaoguai2"},count = 4,str = 52157},	
										[3] = {method = {"scn5043_xiaoguai3"},count = 4,str = 52158},											
										[4] = {method = {"scn5043_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5044] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {164,},
							JQ_CrossDungeonNpcid = {monsterid = {24151} , bossid = {24153} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52162,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5044_xiaoguai1"} , count = 5,str = 52160},	
										[2] = {method = {"scn5044_xiaoguai2"},count = 5,str = 52160},	
										[3] = {method = {"scn5044_xiaoguai3"},count = 5,str = 52161},											
										[4] = {method = {"scn5044_boss1"},count = 1,str = 0},
														 },
						}						
						
DUNGEON_CONFIG[5045] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {156,157,},
							JQ_CrossDungeonNpcid = {monsterid = {24201} , bossid = {24203} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52165,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5045_xiaoguai1"} , count = 5,str = 52163},	
										[2] = {method = {"scn5045_xiaoguai2"},count = 5,str = 52163},	
										[3] = {method = {"scn5045_xiaoguai3"},count = 5,str = 52164},											
										[4] = {method = {"scn5045_boss1"},count = 1,str = 0},
														 },
						}
						
DUNGEON_CONFIG[5046] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {158,157,},
							JQ_CrossDungeonNpcid = {monsterid = {24251} , bossid = {24253,24254,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52169,52170,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5046_xiaoguai1"} , count = 5,str = 52166},	
										[2] = {method = {"scn5046_xiaoguai2"},count = 5,str = 52166},	
										[3] = {method = {"scn5046_xiaoguai3"},count = 5,str = 52167},											
										[4] = {method = {"scn5046_boss1"},count = 1,str = 52166},
										[5] = {method = {"scn5046_xiaoguai4"},count = 5,str = 52166},
										[6] = {method = {"scn5046_xiaoguai5"},count = 5,str = 52166},
										[7] = {method = {"scn5046_xiaoguai6"},count = 5,str = 52168},
										[8] = {method = {"scn5046_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5047] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {155,156,},
							JQ_CrossDungeonNpcid = {monsterid = {24301} , bossid = {24303,24304,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52174,52175,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5047_xiaoguai1"} , count = 6,str = 52171},	
										[2] = {method = {"scn5047_xiaoguai2"},count = 6,str = 52171},	
										[3] = {method = {"scn5047_xiaoguai3"},count = 6,str = 52172},											
										[4] = {method = {"scn5047_boss1"},count = 1,str = 52171},
										[5] = {method = {"scn5047_xiaoguai4"},count = 6,str = 52171},
										[6] = {method = {"scn5047_xiaoguai5"},count = 6,str = 52171},
										[7] = {method = {"scn5047_xiaoguai6"},count = 6,str = 52173},
										[8] = {method = {"scn5047_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5048] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {162,163,},
							JQ_CrossDungeonNpcid = {monsterid = {24351} , bossid = {24353,24354,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52179,52180,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5048_xiaoguai1"} , count = 6,str = 52176},	
										[2] = {method = {"scn5048_xiaoguai2"},count = 6,str = 52176},	
										[3] = {method = {"scn5048_xiaoguai3"},count = 6,str = 52177},											
										[4] = {method = {"scn5048_boss1"},count = 1,str = 52176},
										[5] = {method = {"scn5048_xiaoguai4"},count = 6,str = 52176},
										[6] = {method = {"scn5048_xiaoguai5"},count = 6,str = 52176},
										[7] = {method = {"scn5048_xiaoguai6"},count = 6,str = 52178},
										[8] = {method = {"scn5048_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5049] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {164,},
							JQ_CrossDungeonNpcid = {monsterid = {24401} , bossid = {24403,24404,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52184,52185,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5049_xiaoguai1"} , count = 6,str = 52181},	
										[2] = {method = {"scn5049_xiaoguai2"},count = 6,str = 52181},	
										[3] = {method = {"scn5049_xiaoguai3"},count = 6,str = 52182},											
										[4] = {method = {"scn5049_boss1"},count = 1,str = 52181},
										[5] = {method = {"scn5049_xiaoguai4"},count = 6,str = 52181},
										[6] = {method = {"scn5049_xiaoguai5"},count = 6,str = 52181},
										[7] = {method = {"scn5049_xiaoguai6"},count = 6,str = 52183},
										[8] = {method = {"scn5049_boss2"},count = 1,str = 0},
														 },
						}
						
DUNGEON_CONFIG[5050] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {156,157,},
							JQ_CrossDungeonNpcid = {monsterid = {24451} , bossid = {24453,24454,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52189,52190,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5050_xiaoguai1"} , count = 7,str = 52186},	
										[2] = {method = {"scn5050_xiaoguai2"},count = 7,str = 52186},	
										[3] = {method = {"scn5050_xiaoguai3"},count = 7,str = 52187},											
										[4] = {method = {"scn5050_boss1"},count = 1,str = 52186},
										[5] = {method = {"scn5050_xiaoguai4"},count = 7,str = 52186},
										[6] = {method = {"scn5050_xiaoguai5"},count = 7,str = 52186},
										[7] = {method = {"scn5050_xiaoguai6"},count = 7,str = 52188},
										[8] = {method = {"scn5050_boss2"},count = 1,str = 0},
														 },
						}						


-- 关于空气墙  false是开启空气墙不允许通过 true是指关掉空气墙允许通过


DUNGEON_CONFIG[5051] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {150,151,},
							JQ_CrossDungeonNpcid = {monsterid = {24501} , bossid = {24503} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52193,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5051_xiaoguai1"} , count = 4,str = 52191},	
										[2] = {method = {"scn5051_xiaoguai2"},count = 4,str = 52191},	
										[3] = {method = {"scn5051_xiaoguai3"},count = 4,str = 52192},											
										[4] = {method = {"scn5051_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5052] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {152,153,},
							JQ_CrossDungeonNpcid = {monsterid = {24551} , bossid = {24553} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52196,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5052_xiaoguai1"} , count = 4,str = 52194},	
										[2] = {method = {"scn5052_xiaoguai2"},count = 4,str = 52194},	
										[3] = {method = {"scn5052_xiaoguai3"},count = 4,str = 52195},											
										[4] = {method = {"scn5052_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5053] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {157,158,},
							JQ_CrossDungeonNpcid = {monsterid = {24601} , bossid = {24603} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52199,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5053_xiaoguai1"} , count = 4,str = 52197},	
										[2] = {method = {"scn5053_xiaoguai2"},count = 4,str = 52197},	
										[3] = {method = {"scn5053_xiaoguai3"},count = 4,str = 52198},											
										[4] = {method = {"scn5053_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5054] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {159,},
							JQ_CrossDungeonNpcid = {monsterid = {24651} , bossid = {24653} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52202,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5054_xiaoguai1"} , count = 5,str = 52200},	
										[2] = {method = {"scn5054_xiaoguai2"},count = 5,str = 52200},	
										[3] = {method = {"scn5054_xiaoguai3"},count = 5,str = 52201},											
										[4] = {method = {"scn5054_boss1"},count = 1,str = 0},
														 },
						}						
						
DUNGEON_CONFIG[5055] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {160,161,},
							JQ_CrossDungeonNpcid = {monsterid = {24701} , bossid = {24703} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52205,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5055_xiaoguai1"} , count = 5,str = 52203},	
										[2] = {method = {"scn5055_xiaoguai2"},count = 5,str = 52203},	
										[3] = {method = {"scn5055_xiaoguai3"},count = 5,str = 52204},											
										[4] = {method = {"scn5055_boss1"},count = 1,str = 0},
														 },
						}
						
DUNGEON_CONFIG[5056] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {150,152,154,},
							JQ_CrossDungeonNpcid = {monsterid = {24751} , bossid = {24753,24754,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52209,52210,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5056_xiaoguai1"} , count = 5,str = 52206},	
										[2] = {method = {"scn5056_xiaoguai2"},count = 5,str = 52206},	
										[3] = {method = {"scn5056_xiaoguai3"},count = 5,str = 52207},											
										[4] = {method = {"scn5056_boss1"},count = 1,str = 52206},
										[5] = {method = {"scn5056_xiaoguai4"},count = 5,str = 52206},
										[6] = {method = {"scn5056_xiaoguai5"},count = 5,str = 52206},
										[7] = {method = {"scn5056_xiaoguai6"},count = 5,str = 52208},
										[8] = {method = {"scn5056_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5057] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {155,156,},
							JQ_CrossDungeonNpcid = {monsterid = {24801} , bossid = {24803,24804,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52214,52215,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5057_xiaoguai1"} , count = 6,str = 52211},	
										[2] = {method = {"scn5057_xiaoguai2"},count = 6,str = 52211},	
										[3] = {method = {"scn5057_xiaoguai3"},count = 6,str = 52212},											
										[4] = {method = {"scn5057_boss1"},count = 1,str = 52211},
										[5] = {method = {"scn5057_xiaoguai4"},count = 6,str = 52211},
										[6] = {method = {"scn5057_xiaoguai5"},count = 6,str = 52211},
										[7] = {method = {"scn5057_xiaoguai6"},count = 6,str = 52213},
										[8] = {method = {"scn5057_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5058] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {162,163,},
							JQ_CrossDungeonNpcid = {monsterid = {24851} , bossid = {24853,24854,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52219,52220,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5058_xiaoguai1"} , count = 6,str = 52216},	
										[2] = {method = {"scn5058_xiaoguai2"},count = 6,str = 52216},	
										[3] = {method = {"scn5058_xiaoguai3"},count = 6,str = 52217},											
										[4] = {method = {"scn5058_boss1"},count = 1,str = 52216},
										[5] = {method = {"scn5058_xiaoguai4"},count = 6,str = 52216},
										[6] = {method = {"scn5058_xiaoguai5"},count = 6,str = 52216},
										[7] = {method = {"scn5058_xiaoguai6"},count = 6,str = 52218},
										[8] = {method = {"scn5058_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5059] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {160,161,},
							JQ_CrossDungeonNpcid = {monsterid = {24901} , bossid = {24903,24904,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52224,52225,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5059_xiaoguai1"} , count = 6,str = 52221},	
										[2] = {method = {"scn5059_xiaoguai2"},count = 6,str = 52221},	
										[3] = {method = {"scn5059_xiaoguai3"},count = 6,str = 52222},											
										[4] = {method = {"scn5059_boss1"},count = 1,str = 52221},
										[5] = {method = {"scn5059_xiaoguai4"},count = 6,str = 52221},
										[6] = {method = {"scn5059_xiaoguai5"},count = 6,str = 52221},
										[7] = {method = {"scn5059_xiaoguai6"},count = 6,str = 52223},
										[8] = {method = {"scn5059_boss2"},count = 1,str = 0},
														 },
						}
						
DUNGEON_CONFIG[5060] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {},
							JQ_CrossDungeonNpcid = {monsterid = {24951} , bossid = {24953,24954,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52229,52230,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5060_xiaoguai1"} , count = 7,str = 52226},	
										[2] = {method = {"scn5060_xiaoguai2"},count = 7,str = 52226},	
										[3] = {method = {"scn5060_xiaoguai3"},count = 7,str = 52227},											
										[4] = {method = {"scn5060_boss1"},count = 1,str = 52226},
										[5] = {method = {"scn5060_xiaoguai4"},count = 7,str = 52226},
										[6] = {method = {"scn5060_xiaoguai5"},count = 7,str = 52226},
										[7] = {method = {"scn5060_xiaoguai6"},count = 7,str = 52228},
										[8] = {method = {"scn5060_boss2"},count = 1,str = 0},
														 },
						}						





DUNGEON_CONFIG[5061] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {104,115,},
							JQ_CrossDungeonNpcid = {monsterid = {25001} , bossid = {25003} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52233,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5061_xiaoguai1"} , count = 4,str = 52231},	
										[2] = {method = {"scn5061_xiaoguai2"},count = 4,str = 52231},	
										[3] = {method = {"scn5061_xiaoguai3"},count = 4,str = 52232},											
										[4] = {method = {"scn5061_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5062] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,false},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {103,104,105,},
							JQ_CrossDungeonNpcid = {monsterid = {25051} , bossid = {25053} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52236,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5062_xiaoguai1"} , count = 4,str = 52234},	
										[2] = {method = {"scn5062_xiaoguai2"},count = 4,str = 52234},	
										[3] = {method = {"scn5062_xiaoguai3"},count = 4,str = 52235},											
										[4] = {method = {"scn5062_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5063] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {103,113,},
							JQ_CrossDungeonNpcid = {monsterid = {25101} , bossid = {25103} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52239,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5063_xiaoguai1"} , count = 4,str = 52237},	
										[2] = {method = {"scn5063_xiaoguai2"},count = 4,str = 52237},	
										[3] = {method = {"scn5063_xiaoguai3"},count = 4,str = 52238},											
										[4] = {method = {"scn5063_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5064] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {102,109,},
							JQ_CrossDungeonNpcid = {monsterid = {25151} , bossid = {25153} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52242,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5064_xiaoguai1"} , count = 5,str = 52240},	
										[2] = {method = {"scn5064_xiaoguai2"},count = 5,str = 52240},	
										[3] = {method = {"scn5064_xiaoguai3"},count = 5,str = 52241},											
										[4] = {method = {"scn5064_boss1"},count = 1,str = 0},
														 },
						}						
						
DUNGEON_CONFIG[5065] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {107,},
							JQ_CrossDungeonNpcid = {monsterid = {25201} , bossid = {25203} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52245,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5065_xiaoguai1"} , count = 5,str = 52243},	
										[2] = {method = {"scn5065_xiaoguai2"},count = 5,str = 52243},	
										[3] = {method = {"scn5065_xiaoguai3"},count = 5,str = 52244},											
										[4] = {method = {"scn5065_boss1"},count = 1,str = 0},
														 },
						}
						
DUNGEON_CONFIG[5066] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {101,102,105,},
							JQ_CrossDungeonNpcid = {monsterid = {25251} , bossid = {25253,25254,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52249,52250,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5066_xiaoguai1"} , count = 5,str = 52246},	
										[2] = {method = {"scn5066_xiaoguai2"},count = 5,str = 52246},	
										[3] = {method = {"scn5066_xiaoguai3"},count = 5,str = 52247},											
										[4] = {method = {"scn5066_boss1"},count = 1,str = 52246},
										[5] = {method = {"scn5066_xiaoguai4"},count = 5,str = 52246},
										[6] = {method = {"scn5066_xiaoguai5"},count = 5,str = 52246},
										[7] = {method = {"scn5066_xiaoguai6"},count = 5,str = 52248},
										[8] = {method = {"scn5066_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5067] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {110,},
							JQ_CrossDungeonNpcid = {monsterid = {25301} , bossid = {25303,25304,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52254,52255,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5067_xiaoguai1"} , count = 6,str = 52251},	
										[2] = {method = {"scn5067_xiaoguai2"},count = 6,str = 52251},	
										[3] = {method = {"scn5067_xiaoguai3"},count = 6,str = 52252},											
										[4] = {method = {"scn5067_boss1"},count = 1,str = 52251},
										[5] = {method = {"scn5067_xiaoguai4"},count = 6,str = 52251},
										[6] = {method = {"scn5067_xiaoguai5"},count = 6,str = 52251},
										[7] = {method = {"scn5067_xiaoguai6"},count = 6,str = 52253},
										[8] = {method = {"scn5067_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5068] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {101,107,},
							JQ_CrossDungeonNpcid = {monsterid = {25351} , bossid = {25353,25354,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52259,52260,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5068_xiaoguai1"} , count = 6,str = 52256},	
										[2] = {method = {"scn5068_xiaoguai2"},count = 6,str = 52256},	
										[3] = {method = {"scn5068_xiaoguai3"},count = 6,str = 52257},											
										[4] = {method = {"scn5068_boss1"},count = 1,str = 52256},
										[5] = {method = {"scn5068_xiaoguai4"},count = 6,str = 52256},
										[6] = {method = {"scn5068_xiaoguai5"},count = 6,str = 52256},
										[7] = {method = {"scn5068_xiaoguai6"},count = 6,str = 52258},
										[8] = {method = {"scn5068_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5069] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {103,},
							JQ_CrossDungeonNpcid = {monsterid = {25401} , bossid = {25403,25404,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52264,52265,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5069_xiaoguai1"} , count = 6,str = 52261},	
										[2] = {method = {"scn5069_xiaoguai2"},count = 6,str = 52261},	
										[3] = {method = {"scn5069_xiaoguai3"},count = 6,str = 52262},											
										[4] = {method = {"scn5069_boss1"},count = 1,str = 52261},
										[5] = {method = {"scn5069_xiaoguai4"},count = 6,str = 52261},
										[6] = {method = {"scn5069_xiaoguai5"},count = 6,str = 52261},
										[7] = {method = {"scn5069_xiaoguai6"},count = 6,str = 52263},
										[8] = {method = {"scn5069_boss2"},count = 1,str = 0},
														 },
						}
						
DUNGEON_CONFIG[5070] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {141,142,},
							JQ_CrossDungeonNpcid = {monsterid = {25451} , bossid = {25453,25454,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52269,52270,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5070_xiaoguai1"} , count = 7,str = 52266},	
										[2] = {method = {"scn5070_xiaoguai2"},count = 7,str = 52266},	
										[3] = {method = {"scn5070_xiaoguai3"},count = 7,str = 52267},											
										[4] = {method = {"scn5070_boss1"},count = 1,str = 52266},
										[5] = {method = {"scn5070_xiaoguai4"},count = 7,str = 52266},
										[6] = {method = {"scn5070_xiaoguai5"},count = 7,str = 52266},
										[7] = {method = {"scn5070_xiaoguai6"},count = 7,str = 52268},
										[8] = {method = {"scn5070_boss2"},count = 1,str = 0},
														 },
						}		
DUNGEON_CONFIG[5071] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {104,115,},
							JQ_CrossDungeonNpcid = {monsterid = {25501} , bossid = {25503} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52353,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5071_xiaoguai1"} , count = 4,str = 52351},	
										[2] = {method = {"scn5071_xiaoguai2"},count = 4,str = 52351},	
										[3] = {method = {"scn5071_xiaoguai3"},count = 4,str = 52352},											
										[4] = {method = {"scn5071_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5072] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,false},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {103,104,105,},
							JQ_CrossDungeonNpcid = {monsterid = {25551} , bossid = {25553} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52356,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5072_xiaoguai1"} , count = 4,str = 52354},	
										[2] = {method = {"scn5072_xiaoguai2"},count = 4,str = 52354},	
										[3] = {method = {"scn5072_xiaoguai3"},count = 4,str = 52355},											
										[4] = {method = {"scn5072_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5073] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {103,113,},
							JQ_CrossDungeonNpcid = {monsterid = {25601} , bossid = {25603} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52359,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5073_xiaoguai1"} , count = 4,str = 52357},	
										[2] = {method = {"scn5073_xiaoguai2"},count = 4,str = 52357},	
										[3] = {method = {"scn5073_xiaoguai3"},count = 4,str = 52358},											
										[4] = {method = {"scn5073_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5074] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {102,109,},
							JQ_CrossDungeonNpcid = {monsterid = {25651} , bossid = {25653} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52362,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5074_xiaoguai1"} , count = 5,str = 52360},	
										[2] = {method = {"scn5074_xiaoguai2"},count = 5,str = 52360},	
										[3] = {method = {"scn5074_xiaoguai3"},count = 5,str = 52361},											
										[4] = {method = {"scn5074_boss1"},count = 1,str = 0},
														 },
						}						
						
DUNGEON_CONFIG[5075] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {107,},
							JQ_CrossDungeonNpcid = {monsterid = {25701} , bossid = {25703} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52365,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5075_xiaoguai1"} , count = 5,str = 52363},	
										[2] = {method = {"scn5075_xiaoguai2"},count = 5,str = 52363},	
										[3] = {method = {"scn5075_xiaoguai3"},count = 5,str = 52364},											
										[4] = {method = {"scn5075_boss1"},count = 1,str = 0},
														 },
						}
						
DUNGEON_CONFIG[5076] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {101,102,105,},
							JQ_CrossDungeonNpcid = {monsterid = {25751} , bossid = {25753,25754,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52369,52370,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5076_xiaoguai1"} , count = 5,str = 52366},	
										[2] = {method = {"scn5076_xiaoguai2"},count = 5,str = 52366},	
										[3] = {method = {"scn5076_xiaoguai3"},count = 5,str = 52367},											
										[4] = {method = {"scn5076_boss1"},count = 1,str = 52366},
										[5] = {method = {"scn5076_xiaoguai4"},count = 5,str = 52366},
										[6] = {method = {"scn5076_xiaoguai5"},count = 5,str = 52366},
										[7] = {method = {"scn5076_xiaoguai6"},count = 5,str = 52368},
										[8] = {method = {"scn5076_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5077] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {110,},
							JQ_CrossDungeonNpcid = {monsterid = {25801} , bossid = {25803,25804,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52374,52375,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5077_xiaoguai1"} , count = 6,str = 52371},	
										[2] = {method = {"scn5077_xiaoguai2"},count = 6,str = 52371},	
										[3] = {method = {"scn5077_xiaoguai3"},count = 6,str = 52372},											
										[4] = {method = {"scn5077_boss1"},count = 1,str = 52371},
										[5] = {method = {"scn5077_xiaoguai4"},count = 6,str = 52371},
										[6] = {method = {"scn5077_xiaoguai5"},count = 6,str = 52371},
										[7] = {method = {"scn5077_xiaoguai6"},count = 6,str = 52373},
										[8] = {method = {"scn5077_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5078] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {101,107,},
							JQ_CrossDungeonNpcid = {monsterid = {25851} , bossid = {25853,25854,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52379,52380,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5078_xiaoguai1"} , count = 6,str = 52376},	
										[2] = {method = {"scn5078_xiaoguai2"},count = 6,str = 52376},	
										[3] = {method = {"scn5078_xiaoguai3"},count = 6,str = 52377},											
										[4] = {method = {"scn5078_boss1"},count = 1,str = 52376},
										[5] = {method = {"scn5078_xiaoguai4"},count = 6,str = 52376},
										[6] = {method = {"scn5078_xiaoguai5"},count = 6,str = 52376},
										[7] = {method = {"scn5078_xiaoguai6"},count = 6,str = 52378},
										[8] = {method = {"scn5078_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5079] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {103,},
							JQ_CrossDungeonNpcid = {monsterid = {25901} , bossid = {25903,25904,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52384,52385,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5079_xiaoguai1"} , count = 6,str = 52381},	
										[2] = {method = {"scn5079_xiaoguai2"},count = 6,str = 52381},	
										[3] = {method = {"scn5079_xiaoguai3"},count = 6,str = 52382},											
										[4] = {method = {"scn5079_boss1"},count = 1,str = 52381},
										[5] = {method = {"scn5079_xiaoguai4"},count = 6,str = 52381},
										[6] = {method = {"scn5079_xiaoguai5"},count = 6,str = 52381},
										[7] = {method = {"scn5079_xiaoguai6"},count = 6,str = 52383},
										[8] = {method = {"scn5079_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5080] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,false},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {141,142,},
							JQ_CrossDungeonNpcid = {monsterid = {25951} , bossid = {25953,25954,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52389,52390,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5080_xiaoguai1"} , count = 7,str = 52386},	
										[2] = {method = {"scn5080_xiaoguai2"},count = 7,str = 52386},	
										[3] = {method = {"scn5080_xiaoguai3"},count = 7,str = 52387},											
										[4] = {method = {"scn5080_boss1"},count = 1,str = 52386},
										[5] = {method = {"scn5080_xiaoguai4"},count = 7,str = 52386},
										[6] = {method = {"scn5080_xiaoguai5"},count = 7,str = 52386},
										[7] = {method = {"scn5080_xiaoguai6"},count = 7,str = 52388},
										[8] = {method = {"scn5080_boss2"},count = 1,str = 0},
														 },
						}								
DUNGEON_CONFIG[5081] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {153,},
							JQ_CrossDungeonNpcid = {monsterid = {26001} , bossid = {26003} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52393,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5081_xiaoguai1"} , count = 4,str = 52391},	
										[2] = {method = {"scn5081_xiaoguai2"},count = 4,str = 52391},	
										[3] = {method = {"scn5081_xiaoguai3"},count = 4,str = 52392},											
										[4] = {method = {"scn5081_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5082] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {158,},
							JQ_CrossDungeonNpcid = {monsterid = {26051} , bossid = {26053} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52396,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5082_xiaoguai1"} , count = 5,str = 52394},	
										[2] = {method = {"scn5082_xiaoguai2"},count = 5,str = 52394},	
										[3] = {method = {"scn5082_xiaoguai3"},count = 5,str = 52395},											
										[4] = {method = {"scn5082_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5083] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {159,},
							JQ_CrossDungeonNpcid = {monsterid = {26101} , bossid = {26103} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52399,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5083_xiaoguai1"} , count = 4,str = 52397},	
										[2] = {method = {"scn5083_xiaoguai2"},count = 4,str = 52397},	
										[3] = {method = {"scn5083_xiaoguai3"},count = 4,str = 52398},											
										[4] = {method = {"scn5083_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5084] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {164,},
							JQ_CrossDungeonNpcid = {monsterid = {26151} , bossid = {26153} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52402,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5084_xiaoguai1"} , count = 5,str = 52400},	
										[2] = {method = {"scn5084_xiaoguai2"},count = 5,str = 52400},	
										[3] = {method = {"scn5084_xiaoguai3"},count = 5,str = 52401},											
										[4] = {method = {"scn5084_boss1"},count = 1,str = 0},
														 },
						}		
DUNGEON_CONFIG[5085] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {152,153,},
							JQ_CrossDungeonNpcid = {monsterid = {26201} , bossid = {26203} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52405,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5085_xiaoguai1"} , count = 4,str = 52403},	
										[2] = {method = {"scn5085_xiaoguai2"},count = 4,str = 52403},	
										[3] = {method = {"scn5085_xiaoguai3"},count = 4,str = 52404},											
										[4] = {method = {"scn5085_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5086] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {150,},
							JQ_CrossDungeonNpcid = {monsterid = {26251} , bossid = {26253,26254,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52409,52410,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5086_xiaoguai1"} , count = 5,str = 52406},	
										[2] = {method = {"scn5086_xiaoguai2"},count = 5,str = 52406},	
										[3] = {method = {"scn5086_xiaoguai3"},count = 5,str = 52407},											
										[4] = {method = {"scn5086_boss1"},count = 1,str = 52406},
										[5] = {method = {"scn5086_xiaoguai4"},count = 5,str = 52406},
										[6] = {method = {"scn5086_xiaoguai5"},count = 5,str = 52406},
										[7] = {method = {"scn5086_xiaoguai6"},count = 5,str = 52408},
										[8] = {method = {"scn5086_boss2"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5087] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {156,155,},
							JQ_CrossDungeonNpcid = {monsterid = {26301} , bossid = {26303,26304,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52414,52415,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5087_xiaoguai1"} , count = 6,str = 52411},	
										[2] = {method = {"scn5087_xiaoguai2"},count = 6,str = 52411},	
										[3] = {method = {"scn5087_xiaoguai3"},count = 6,str = 52412},											
										[4] = {method = {"scn5087_boss1"},count = 1,str = 52411},
										[5] = {method = {"scn5087_xiaoguai4"},count = 6,str = 52411},
										[6] = {method = {"scn5087_xiaoguai5"},count = 6,str = 52411},
										[7] = {method = {"scn5087_xiaoguai6"},count = 6,str = 52413},
										[8] = {method = {"scn5087_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5088] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {155,156,},
							JQ_CrossDungeonNpcid = {monsterid = {26351} , bossid = {26353,26354,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52419,52420,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5088_xiaoguai1"} , count = 6,str = 52416},	
										[2] = {method = {"scn5088_xiaoguai2"},count = 6,str = 52416},	
										[3] = {method = {"scn5088_xiaoguai3"},count = 6,str = 52417},											
										[4] = {method = {"scn5088_boss1"},count = 1,str = 52416},
										[5] = {method = {"scn5088_xiaoguai4"},count = 6,str = 52416},
										[6] = {method = {"scn5088_xiaoguai5"},count = 6,str = 52416},
										[7] = {method = {"scn5088_xiaoguai6"},count = 6,str = 52418},
										[8] = {method = {"scn5088_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5089] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {164,},
							JQ_CrossDungeonNpcid = {monsterid = {26401} , bossid = {26403,26404,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52424,52425,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5089_xiaoguai1"} , count = 6,str = 52421},	
										[2] = {method = {"scn5089_xiaoguai2"},count = 6,str = 52421},	
										[3] = {method = {"scn5089_xiaoguai3"},count = 6,str = 52422},											
										[4] = {method = {"scn5089_boss1"},count = 1,str = 52421},
										[5] = {method = {"scn5089_xiaoguai4"},count = 6,str = 52421},
										[6] = {method = {"scn5089_xiaoguai5"},count = 6,str = 52421},
										[7] = {method = {"scn5089_xiaoguai6"},count = 6,str = 52423},
										[8] = {method = {"scn5089_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5090] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {162,163,},
							JQ_CrossDungeonNpcid = {monsterid = {26451} , bossid = {26453,26454,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52429,52430,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5090_xiaoguai1"} , count = 6,str = 52426},	
										[2] = {method = {"scn5090_xiaoguai2"},count = 6,str = 52426},	
										[3] = {method = {"scn5090_xiaoguai3"},count = 6,str = 52427},											
										[4] = {method = {"scn5090_boss1"},count = 1,str = 52426},
										[5] = {method = {"scn5090_xiaoguai4"},count = 6,str = 52426},
										[6] = {method = {"scn5090_xiaoguai5"},count = 6,str = 52426},
										[7] = {method = {"scn5090_xiaoguai6"},count = 6,str = 52428},
										[8] = {method = {"scn5090_boss2"},count = 1,str = 0},
														 },
						}	


DUNGEON_CONFIG[5091] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {170,171,172,},
							JQ_CrossDungeonNpcid = {monsterid = {26501} , bossid = {26503} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52273,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5091_xiaoguai1"} , count = 4,str = 52271},	
										[2] = {method = {"scn5091_xiaoguai2"},count = 4,str = 52271},	
										[3] = {method = {"scn5091_xiaoguai3"},count = 4,str = 52272},											
										[4] = {method = {"scn5091_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5092] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {172,173,174,},
							JQ_CrossDungeonNpcid = {monsterid = {26551} , bossid = {26553} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52276,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5092_xiaoguai1"} , count = 5,str = 52274},	
										[2] = {method = {"scn5092_xiaoguai2"},count = 5,str = 52274},	
										[3] = {method = {"scn5092_xiaoguai3"},count = 5,str = 52275},											
										[4] = {method = {"scn5092_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5093] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {174,175,176,},
							JQ_CrossDungeonNpcid = {monsterid = {26601} , bossid = {26603} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52279,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5093_xiaoguai1"} , count = 4,str = 52277},	
										[2] = {method = {"scn5093_xiaoguai2"},count = 4,str = 52277},	
										[3] = {method = {"scn5093_xiaoguai3"},count = 4,str = 52278},											
										[4] = {method = {"scn5093_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5094] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {170,177,178,},
							JQ_CrossDungeonNpcid = {monsterid = {26651} , bossid = {26653} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52282,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5094_xiaoguai1"} , count = 5,str = 52280},	
										[2] = {method = {"scn5094_xiaoguai2"},count = 5,str = 52280},	
										[3] = {method = {"scn5094_xiaoguai3"},count = 5,str = 52281},											
										[4] = {method = {"scn5094_boss1"},count = 1,str = 0},
														 },
						}		
DUNGEON_CONFIG[5095] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {171,173,175,178,179,180,181,182,},
							JQ_CrossDungeonNpcid = {monsterid = {26701} , bossid = {26703} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52285,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5095_xiaoguai1"} , count = 4,str = 52283},	
										[2] = {method = {"scn5095_xiaoguai2"},count = 4,str = 52283},	
										[3] = {method = {"scn5095_xiaoguai3"},count = 4,str = 52284},											
										[4] = {method = {"scn5095_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5096] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {170,177,178,},
							JQ_CrossDungeonNpcid = {monsterid = {26751} , bossid = {26753,26754,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52289,52290,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5096_xiaoguai1"} , count = 5,str = 52286},	
										[2] = {method = {"scn5096_xiaoguai2"},count = 5,str = 52286},	
										[3] = {method = {"scn5096_xiaoguai3"},count = 5,str = 52287},											
										[4] = {method = {"scn5096_boss1"},count = 1,str = 52286},
										[5] = {method = {"scn5096_xiaoguai4"},count = 5,str = 52286},
										[6] = {method = {"scn5096_xiaoguai5"},count = 5,str = 52286},
										[7] = {method = {"scn5096_xiaoguai6"},count = 5,str = 52288},
										[8] = {method = {"scn5096_boss2"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5097] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {174,175,176,},
							JQ_CrossDungeonNpcid = {monsterid = {26801} , bossid = {26803,26804,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52294,52295,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5097_xiaoguai1"} , count = 6,str = 52291},	
										[2] = {method = {"scn5097_xiaoguai2"},count = 6,str = 52291},	
										[3] = {method = {"scn5097_xiaoguai3"},count = 6,str = 52292},											
										[4] = {method = {"scn5097_boss1"},count = 1,str = 52291},
										[5] = {method = {"scn5097_xiaoguai4"},count = 6,str = 52291},
										[6] = {method = {"scn5097_xiaoguai5"},count = 6,str = 52291},
										[7] = {method = {"scn5097_xiaoguai6"},count = 6,str = 52293},
										[8] = {method = {"scn5097_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5098] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {172,173,175,176,},
							JQ_CrossDungeonNpcid = {monsterid = {26851} , bossid = {26853,26854,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52299,52300,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5098_xiaoguai1"} , count = 6,str = 52296},	
										[2] = {method = {"scn5098_xiaoguai2"},count = 6,str = 52296},	
										[3] = {method = {"scn5098_xiaoguai3"},count = 6,str = 52297},											
										[4] = {method = {"scn5098_boss1"},count = 1,str = 52296},
										[5] = {method = {"scn5098_xiaoguai4"},count = 6,str = 52296},
										[6] = {method = {"scn5098_xiaoguai5"},count = 6,str = 52296},
										[7] = {method = {"scn5098_xiaoguai6"},count = 6,str = 52298},
										[8] = {method = {"scn5098_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5099] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {170,177,178,},
							JQ_CrossDungeonNpcid = {monsterid = {26901} , bossid = {26903,26904,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52304,52305,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5099_xiaoguai1"} , count = 6,str = 52301},	
										[2] = {method = {"scn5099_xiaoguai2"},count = 6,str = 52301},	
										[3] = {method = {"scn5099_xiaoguai3"},count = 6,str = 52302},											
										[4] = {method = {"scn5099_boss1"},count = 1,str = 52301},
										[5] = {method = {"scn5099_xiaoguai4"},count = 6,str = 52301},
										[6] = {method = {"scn5099_xiaoguai5"},count = 6,str = 52301},
										[7] = {method = {"scn5099_xiaoguai6"},count = 6,str = 52303},
										[8] = {method = {"scn5099_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5100] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {162,163,},
							JQ_CrossDungeonNpcid = {monsterid = {26951} , bossid = {26953,26954,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52309,52310,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5100_xiaoguai1"} , count = 6,str = 52306},	
										[2] = {method = {"scn5100_xiaoguai2"},count = 6,str = 52306},	
										[3] = {method = {"scn5100_xiaoguai3"},count = 6,str = 52307},											
										[4] = {method = {"scn5100_boss1"},count = 1,str = 52306},
										[5] = {method = {"scn5100_xiaoguai4"},count = 6,str = 52306},
										[6] = {method = {"scn5100_xiaoguai5"},count = 6,str = 52306},
										[7] = {method = {"scn5100_xiaoguai6"},count = 6,str = 52308},
										[8] = {method = {"scn5100_boss2"},count = 1,str = 0},
														 },
						}	
						




DUNGEON_CONFIG[5101] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {176,182,183,},
							JQ_CrossDungeonNpcid = {monsterid = {27001} , bossid = {27003} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52313,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5101_xiaoguai1"} , count = 4,str = 52311},	
										[2] = {method = {"scn5101_xiaoguai2"},count = 4,str = 52311},	
										[3] = {method = {"scn5101_xiaoguai3"},count = 4,str = 52312},											
										[4] = {method = {"scn5101_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5102] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {177,179,184,},
							JQ_CrossDungeonNpcid = {monsterid = {27051} , bossid = {27053} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52316,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5102_xiaoguai1"} , count = 5,str = 52314},	
										[2] = {method = {"scn5102_xiaoguai2"},count = 5,str = 52314},	
										[3] = {method = {"scn5102_xiaoguai3"},count = 5,str = 52315},											
										[4] = {method = {"scn5102_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5103] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {180,184,185,},
							JQ_CrossDungeonNpcid = {monsterid = {27101} , bossid = {27103} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52319,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5103_xiaoguai1"} , count = 4,str = 52317},	
										[2] = {method = {"scn5103_xiaoguai2"},count = 4,str = 52317},	
										[3] = {method = {"scn5103_xiaoguai3"},count = 4,str = 52318},											
										[4] = {method = {"scn5103_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5104] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {181,183,185,},
							JQ_CrossDungeonNpcid = {monsterid = {27151} , bossid = {27153} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52322,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5104_xiaoguai1"} , count = 5,str = 52320},	
										[2] = {method = {"scn5104_xiaoguai2"},count = 5,str = 52320},	
										[3] = {method = {"scn5104_xiaoguai3"},count = 5,str = 52321},											
										[4] = {method = {"scn5104_boss1"},count = 1,str = 0},
														 },
						}		
DUNGEON_CONFIG[5105] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {171,173,175,178,179,180,181,182,},
							JQ_CrossDungeonNpcid = {monsterid = {27201} , bossid = {27203} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52325,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5105_xiaoguai1"} , count = 4,str = 52323},	
										[2] = {method = {"scn5105_xiaoguai2"},count = 4,str = 52323},	
										[3] = {method = {"scn5105_xiaoguai3"},count = 4,str = 52324},											
										[4] = {method = {"scn5105_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5106] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {},
							JQ_CrossDungeonNpcid = {monsterid = {27251} , bossid = {27253,27254,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52329,52330,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5106_xiaoguai1"} , count = 5,str = 52326},	
										[2] = {method = {"scn5106_xiaoguai2"},count = 5,str = 52326},	
										[3] = {method = {"scn5106_xiaoguai3"},count = 5,str = 52327},											
										[4] = {method = {"scn5106_boss1"},count = 1,str = 52326},
										[5] = {method = {"scn5106_xiaoguai4"},count = 5,str = 52326},
										[6] = {method = {"scn5106_xiaoguai5"},count = 5,str = 52326},
										[7] = {method = {"scn5106_xiaoguai6"},count = 5,str = 52328},
										[8] = {method = {"scn5106_boss2"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5107] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {},
							JQ_CrossDungeonNpcid = {monsterid = {27301} , bossid = {27303,27304,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52334,52335,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5107_xiaoguai1"} , count = 6,str = 52331},	
										[2] = {method = {"scn5107_xiaoguai2"},count = 6,str = 52331},	
										[3] = {method = {"scn5107_xiaoguai3"},count = 6,str = 52332},											
										[4] = {method = {"scn5107_boss1"},count = 1,str = 52331},
										[5] = {method = {"scn5107_xiaoguai4"},count = 6,str = 52331},
										[6] = {method = {"scn5107_xiaoguai5"},count = 6,str = 52331},
										[7] = {method = {"scn5107_xiaoguai6"},count = 6,str = 52333},
										[8] = {method = {"scn5107_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5108] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {},
							JQ_CrossDungeonNpcid = {monsterid = {27351} , bossid = {27353,27354,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52339,52340,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5108_xiaoguai1"} , count = 6,str = 52336},	
										[2] = {method = {"scn5108_xiaoguai2"},count = 6,str = 52336},	
										[3] = {method = {"scn5108_xiaoguai3"},count = 6,str = 52337},											
										[4] = {method = {"scn5108_boss1"},count = 1,str = 52336},
										[5] = {method = {"scn5108_xiaoguai4"},count = 6,str = 52336},
										[6] = {method = {"scn5108_xiaoguai5"},count = 6,str = 52336},
										[7] = {method = {"scn5108_xiaoguai6"},count = 6,str = 52338},
										[8] = {method = {"scn5108_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5109] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {},
							JQ_CrossDungeonNpcid = {monsterid = {27401} , bossid = {27403,27404,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52344,52345,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5109_xiaoguai1"} , count = 6,str = 52341},	
										[2] = {method = {"scn5109_xiaoguai2"},count = 6,str = 52341},	
										[3] = {method = {"scn5109_xiaoguai3"},count = 6,str = 52342},											
										[4] = {method = {"scn5109_boss1"},count = 1,str = 52341},
										[5] = {method = {"scn5109_xiaoguai4"},count = 6,str = 52341},
										[6] = {method = {"scn5109_xiaoguai5"},count = 6,str = 52341},
										[7] = {method = {"scn5109_xiaoguai6"},count = 6,str = 52343},
										[8] = {method = {"scn5109_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5110] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {},
							JQ_CrossDungeonNpcid = {monsterid = {27451} , bossid = {27453,27454,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52349,52350,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5110_xiaoguai1"} , count = 6,str = 52346},	
										[2] = {method = {"scn5110_xiaoguai2"},count = 6,str = 52346},	
										[3] = {method = {"scn5110_xiaoguai3"},count = 6,str = 52347},											
										[4] = {method = {"scn5110_boss1"},count = 1,str = 52346},
										[5] = {method = {"scn5110_xiaoguai4"},count = 6,str = 52346},
										[6] = {method = {"scn5110_xiaoguai5"},count = 6,str = 52346},
										[7] = {method = {"scn5110_xiaoguai6"},count = 6,str = 52348},
										[8] = {method = {"scn5110_boss2"},count = 1,str = 0},
														 },
						}	












DUNGEON_CONFIG[5111] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {159,},
							JQ_CrossDungeonNpcid = {monsterid = {27501} , bossid = {27504} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52433,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5111_xiaoguai1"} , count = 4,str = 52431},	
										[2] = {method = {"scn5111_xiaoguai2"},count = 4,str = 52431},	
										[3] = {method = {"scn5111_xiaoguai3"},count = 4,str = 52432},											
										[4] = {method = {"scn5111_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5112] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {160,161,},
							JQ_CrossDungeonNpcid = {monsterid = {27551} , bossid = {27554} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52436,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5112_xiaoguai1"} , count = 4,str = 52434},	
										[2] = {method = {"scn5112_xiaoguai2"},count = 4,str = 52434},	
										[3] = {method = {"scn5112_xiaoguai3"},count = 4,str = 52435},											
										[4] = {method = {"scn5112_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5113] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {162,163,},
							JQ_CrossDungeonNpcid = {monsterid = {27601} , bossid = {27604} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52439,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5113_xiaoguai1"} , count = 4,str = 52437},	
										[2] = {method = {"scn5113_xiaoguai2"},count = 4,str = 52437},	
										[3] = {method = {"scn5113_xiaoguai3"},count = 4,str = 52438},											
										[4] = {method = {"scn5113_boss1"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5114] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {164,},
							JQ_CrossDungeonNpcid = {monsterid = {27651} , bossid = {27654} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52442,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5114_xiaoguai1"} , count = 5,str = 52440},	
										[2] = {method = {"scn5114_xiaoguai2"},count = 5,str = 52440},	
										[3] = {method = {"scn5114_xiaoguai3"},count = 5,str = 52441},											
										[4] = {method = {"scn5114_boss1"},count = 1,str = 0},
														 },
						}						
						
DUNGEON_CONFIG[5115] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {156,157,},
							JQ_CrossDungeonNpcid = {monsterid = {27701} , bossid = {27704} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52445,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5115_xiaoguai1"} , count = 5,str = 52443},	
										[2] = {method = {"scn5115_xiaoguai2"},count = 5,str = 52443},	
										[3] = {method = {"scn5115_xiaoguai3"},count = 5,str = 52444},											
										[4] = {method = {"scn5115_boss1"},count = 1,str = 0},
														 },
						}
						
DUNGEON_CONFIG[5116] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {158,157,},
							JQ_CrossDungeonNpcid = {monsterid = {27751} , bossid = {27753,27754,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52449,52450,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5116_xiaoguai1"} , count = 5,str = 52446},	
										[2] = {method = {"scn5116_xiaoguai2"},count = 5,str = 52446},	
										[3] = {method = {"scn5116_xiaoguai3"},count = 5,str = 52447},											
										[4] = {method = {"scn5116_boss1"},count = 1,str = 52446},
										[5] = {method = {"scn5116_xiaoguai4"},count = 5,str = 52446},
										[6] = {method = {"scn5116_xiaoguai5"},count = 5,str = 52446},
										[7] = {method = {"scn5116_xiaoguai6"},count = 5,str = 52448},
										[8] = {method = {"scn5116_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5117] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {155,156,},
							JQ_CrossDungeonNpcid = {monsterid = {27801} , bossid = {27803,27804,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52454,52455,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5117_xiaoguai1"} , count = 6,str = 52451},	
										[2] = {method = {"scn5117_xiaoguai2"},count = 6,str = 52451},	
										[3] = {method = {"scn5117_xiaoguai3"},count = 6,str = 52452},											
										[4] = {method = {"scn5117_boss1"},count = 1,str = 52451},
										[5] = {method = {"scn5117_xiaoguai4"},count = 6,str = 52451},
										[6] = {method = {"scn5117_xiaoguai5"},count = 6,str = 52451},
										[7] = {method = {"scn5117_xiaoguai6"},count = 6,str = 52453},
										[8] = {method = {"scn5117_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5118] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {162,163,},
							JQ_CrossDungeonNpcid = {monsterid = {27851} , bossid = {27853,27854,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52459,52460,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5118_xiaoguai1"} , count = 6,str = 52456},	
										[2] = {method = {"scn5118_xiaoguai2"},count = 6,str = 52456},	
										[3] = {method = {"scn5118_xiaoguai3"},count = 6,str = 52457},											
										[4] = {method = {"scn5118_boss1"},count = 1,str = 52456},
										[5] = {method = {"scn5118_xiaoguai4"},count = 6,str = 52456},
										[6] = {method = {"scn5118_xiaoguai5"},count = 6,str = 52456},
										[7] = {method = {"scn5118_xiaoguai6"},count = 6,str = 52458},
										[8] = {method = {"scn5118_boss2"},count = 1,str = 0},
														 },
						}	
						
DUNGEON_CONFIG[5119] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {164,},
							JQ_CrossDungeonNpcid = {monsterid = {27901} , bossid = {27903,27904,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52464,52465,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5119_xiaoguai1"} , count = 6,str = 52461},	
										[2] = {method = {"scn5119_xiaoguai2"},count = 6,str = 52461},	
										[3] = {method = {"scn5119_xiaoguai3"},count = 6,str = 52462},											
										[4] = {method = {"scn5119_boss1"},count = 1,str = 52461},
										[5] = {method = {"scn5119_xiaoguai4"},count = 6,str = 52461},
										[6] = {method = {"scn5119_xiaoguai5"},count = 6,str = 52461},
										[7] = {method = {"scn5119_xiaoguai6"},count = 6,str = 52463},
										[8] = {method = {"scn5119_boss2"},count = 1,str = 0},
														 },
						}
						
DUNGEON_CONFIG[5120] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {156,157,},
							JQ_CrossDungeonNpcid = {monsterid = {27951} , bossid = {27953,27954,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52469,52470,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5120_xiaoguai1"} , count = 7,str = 52466},	
										[2] = {method = {"scn5120_xiaoguai2"},count = 7,str = 52466},	
										[3] = {method = {"scn5120_xiaoguai3"},count = 7,str = 52467},											
										[4] = {method = {"scn5120_boss1"},count = 1,str = 52466},
										[5] = {method = {"scn5120_xiaoguai4"},count = 7,str = 52466},
										[6] = {method = {"scn5120_xiaoguai5"},count = 7,str = 52466},
										[7] = {method = {"scn5120_xiaoguai6"},count = 7,str = 52468},
										[8] = {method = {"scn5120_boss2"},count = 1,str = 0},
														 },
						}						





















DUNGEON_CONFIG[5121] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {176,182,183,},
							JQ_CrossDungeonNpcid = {monsterid = {28001} , bossid = {28004} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52473,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5121_xiaoguai1"} , count = 4,str = 52471},	
										[2] = {method = {"scn5121_xiaoguai2"},count = 4,str = 52471},	
										[3] = {method = {"scn5121_xiaoguai3"},count = 4,str = 52472},											
										[4] = {method = {"scn5121_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5122] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {177,179,184,},
							JQ_CrossDungeonNpcid = {monsterid = {28051} , bossid = {28054} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52476,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5122_xiaoguai1"} , count = 5,str = 52474},	
										[2] = {method = {"scn5122_xiaoguai2"},count = 5,str = 52474},	
										[3] = {method = {"scn5122_xiaoguai3"},count = 5,str = 52475},											
										[4] = {method = {"scn5122_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5123] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {180,184,185,},
							JQ_CrossDungeonNpcid = {monsterid = {28101} , bossid = {28104} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52479,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5123_xiaoguai1"} , count = 4,str = 52477},	
										[2] = {method = {"scn5123_xiaoguai2"},count = 4,str = 52477},	
										[3] = {method = {"scn5123_xiaoguai3"},count = 4,str = 52478},											
										[4] = {method = {"scn5123_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5124] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {181,183,185,},
							JQ_CrossDungeonNpcid = {monsterid = {28151} , bossid = {28154} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52482,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5124_xiaoguai1"} , count = 5,str = 52480},	
										[2] = {method = {"scn5124_xiaoguai2"},count = 5,str = 52480},	
										[3] = {method = {"scn5124_xiaoguai3"},count = 5,str = 52481},											
										[4] = {method = {"scn5124_boss1"},count = 1,str = 0},
														 },
						}		
DUNGEON_CONFIG[5125] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,false},{4,false},{0,false}},
							HumanEnter_OpenEffectWalls = {171,173,175,178,179,180,181,182,},
							JQ_CrossDungeonNpcid = {monsterid = {28201} , bossid = {28204} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52485,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5125_xiaoguai1"} , count = 4,str = 52483},	
										[2] = {method = {"scn5125_xiaoguai2"},count = 4,str = 52483},	
										[3] = {method = {"scn5125_xiaoguai3"},count = 4,str = 52484},											
										[4] = {method = {"scn5125_boss1"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5126] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,true},{4,true},{0,false}},
							HumanEnter_OpenEffectWalls = {},
							JQ_CrossDungeonNpcid = {monsterid = {28251} , bossid = {28253,28254,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52489,52490,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5126_xiaoguai1"} , count = 5,str = 52486},	
										[2] = {method = {"scn5126_xiaoguai2"},count = 5,str = 52486},	
										[3] = {method = {"scn5126_xiaoguai3"},count = 5,str = 52487},											
										[4] = {method = {"scn5126_boss1"},count = 1,str = 52486},
										[5] = {method = {"scn5126_xiaoguai4"},count = 5,str = 52486},
										[6] = {method = {"scn5126_xiaoguai5"},count = 5,str = 52486},
										[7] = {method = {"scn5126_xiaoguai6"},count = 5,str = 52488},
										[8] = {method = {"scn5126_boss2"},count = 1,str = 0},
														 },
						}	
DUNGEON_CONFIG[5127] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,true},{4,false},{0,true}},
							HumanEnter_OpenEffectWalls = {},
							JQ_CrossDungeonNpcid = {monsterid = {28301} , bossid = {28303,28304,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52494,52495,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5127_xiaoguai1"} , count = 6,str = 52491},	
										[2] = {method = {"scn5127_xiaoguai2"},count = 6,str = 52491},	
										[3] = {method = {"scn5127_xiaoguai3"},count = 6,str = 52492},											
										[4] = {method = {"scn5127_boss1"},count = 1,str = 52491},
										[5] = {method = {"scn5127_xiaoguai4"},count = 6,str = 52491},
										[6] = {method = {"scn5127_xiaoguai5"},count = 6,str = 52491},
										[7] = {method = {"scn5127_xiaoguai6"},count = 6,str = 52493},
										[8] = {method = {"scn5127_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5128] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {},
							JQ_CrossDungeonNpcid = {monsterid = {28351} , bossid = {28353,28354,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52499,52500,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5128_xiaoguai1"} , count = 6,str = 52496},	
										[2] = {method = {"scn5128_xiaoguai2"},count = 6,str = 52496},	
										[3] = {method = {"scn5128_xiaoguai3"},count = 6,str = 52497},											
										[4] = {method = {"scn5128_boss1"},count = 1,str = 52496},
										[5] = {method = {"scn5128_xiaoguai4"},count = 6,str = 52496},
										[6] = {method = {"scn5128_xiaoguai5"},count = 6,str = 52496},
										[7] = {method = {"scn5128_xiaoguai6"},count = 6,str = 52498},
										[8] = {method = {"scn5128_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5129] = {	
							HumanEnterEnableMotionBlock = {{1,true},{2,true},{3,false},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {},
							JQ_CrossDungeonNpcid = {monsterid = {28401} , bossid = {28403,28404,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52504,52505,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5129_xiaoguai1"} , count = 6,str = 52501},	
										[2] = {method = {"scn5129_xiaoguai2"},count = 6,str = 52501},	
										[3] = {method = {"scn5129_xiaoguai3"},count = 6,str = 52502},											
										[4] = {method = {"scn5129_boss1"},count = 1,str = 52501},
										[5] = {method = {"scn5129_xiaoguai4"},count = 6,str = 52501},
										[6] = {method = {"scn5129_xiaoguai5"},count = 6,str = 52501},
										[7] = {method = {"scn5129_xiaoguai6"},count = 6,str = 52503},
										[8] = {method = {"scn5129_boss2"},count = 1,str = 0},
														 },
						}
DUNGEON_CONFIG[5130] = {	
							HumanEnterEnableMotionBlock = {{1,false},{2,false},{3,true},{4,true},{0,true}},
							HumanEnter_OpenEffectWalls = {},
							JQ_CrossDungeonNpcid = {monsterid = {28451} , bossid = {28453,28454,} , },
							JQ_DungeonObj = {monsterstr = {} , bossstr = {52509,52510,},},
							JQ_DungeonMaxTime = 240 ,
							NpcKilled_CrossDungeonWava = {
										[1] = {method = {"scn5130_xiaoguai1"} , count = 6,str = 52506},	
										[2] = {method = {"scn5130_xiaoguai2"},count = 6,str = 52506},	
										[3] = {method = {"scn5130_xiaoguai3"},count = 6,str = 52507},											
										[4] = {method = {"scn5130_boss1"},count = 1,str = 52506},
										[5] = {method = {"scn5130_xiaoguai4"},count = 6,str = 52506},
										[6] = {method = {"scn5130_xiaoguai5"},count = 6,str = 52506},
										[7] = {method = {"scn5130_xiaoguai6"},count = 6,str = 52508},
										[8] = {method = {"scn5130_boss2"},count = 1,str = 0},
														 },
						}	


	