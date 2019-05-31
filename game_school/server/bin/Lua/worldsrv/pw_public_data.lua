--------------------------
--服务器脚本公用数据
--------------------------

--背包类型定义
BAG_TYPE = 1 				--背包
EQUIP_TYPE = 2				--装备
STORAGE_TYPE = 3 			--仓库
ASTROLOGY_TYPE = 4 			--占星
RUNE_TYPE = 5  				--星运符文栏
SOULSTONE_TYPE = 6			--灵石栏
BLESSING_TYPE = 7 			--祝福栏

--副本常用剧情编号
DUNGEON_START = 9000		--关卡开始
DUNGEON_END = 9001			--关卡结束

--召唤师死亡后召唤的小弟被脚本杀死，技能ID
PET_KILLSELF_SKILLID = 1050
PET_KILLSELF_EFFECT = 1050

--关卡开始、结束的触发时间
DUNGEON_START_TIME = 4
DUNGEON_END_TIME = 2

--塔防关卡的波数特效
PLOT_WAVE1 = 9002
PLOT_WAVE2 = 9003
PLOT_WAVE3 = 9004
PLOT_WAVE4 = 9005
PLOT_WAVE5 = 9006

--公用的creatureid
CREATURE_FINGER = 80009	--场景指路的NPCid

--魔王本公用的提示str
STR_MULTI_SUCCEED = 41733
STR_MULTI_FAILD = 41732
STR_MULTI_SUCCEED_ALL = 41734

--频道类型定义
--[[
ChannelType.Screen			--屏幕中间提示
ChannelType.System			--系统提示
ChannelType.Guide			--引导提示
ChannelType.Prompt			--提示框
ChannelType.PromptAutoHide	--自动关闭提示框
ChannelType.Award			--获得奖励提示
ChannelType.Announcement	--系统公告
ChannelType.General			--综合频道
ChannelType.World			--世界频道
ChannelType.Guild			--工会频道
ChannelType.Horn			--喇叭频道
ChannelType.Gm				--GM频道
--]]

--服务器调UI界面约定ID
UI_WARN = 1			--屏幕中间警告提醒
UI_TIMER = 2		--倒计时
UI_BLACK_WHITE = 3	--屏幕变黑白，梦境模式
UI_TIMECOUNTDOWN = 4	--副本三种宝箱倒计时
UI_DTS_SUBLIME = 5 --大逃杀分线id[1-N]
UI_DARKARENA_CRAZY= 6 --暗黑竞技场怪狂暴倒计时
UI_LONGYU= 7 --龙域
UI_TRIAL_LAND = 8 --试炼之地
UI_CHALLENGE_TIMER = 9 --挑战副本倒计时
UI_COMBAT_BEGIN = 13	--战斗开始
UI_COMBAT_END = 14		--战斗结束
UI_COLOR = 15					--颜色变化
UI_GRAY = 16			--全屏置灰

--服务器调UI界面约定参数(挑战副本倒计时)
UI_CHALLENGE_TIMER_BEGIN = 1 -- 开始
UI_CHALLENGE_TIMER_NEXT = 2 -- 本关结束，开始下一关
UI_CHALLENGE_TIMER_END = 3 -- 通关全部关卡

-- 提示消息定义
CHAT_MODE_SCREEN			= 0x0001    --屏幕中间提示
CHAT_MODE_SYSTEM			= 0x0002    --系统提示
CHAT_MODE_GUIDE				= 0x0004    --引导提示
CHAT_MODE_PROMPT_NORMAL		= 0x0008    --提示框
CHAT_MODE_PROMPT_AUTO_HIDE	= 0x0010    --自动关闭提示框
CHAT_MODE_AWARD				= 0x0020    --获得奖励提示
CHAT_MODE_ANNOUNCEMENT		= 0x0040    --系统公告
-- 聊天频道定义
CHAT_MODE_GENERAL			= 0x0100    --综合频道
CHAT_MODE_WORLD				= 0x0200    --世界频道
CHAT_MODE_GUILD				= 0x0400    --公会频道
CHAT_MODE_HORN				= 0x0800    --喇叭频道
CHAT_MODE_GM				= 0x1000    --GM频道
CHAT_MODE_STAGE				= 0x2000    --场景频道
CHAT_MODE_TEAM				= 0x4000    --队伍频道
CHAT_MODE_WHISPER			= 0x8000    --私聊频道


-- 消息类型分类
CHAT_TEXT_UNKNOWN 			= 0		-- 无效消息
CHAT_TEXT_SYSTEM			= 1		-- 系统消息
CHAT_TEXT_PUBLIC_NOTIFY		= 2		-- 公告消息
CHAT_TEXT_ACTIVITY_NOTIFY	= 3		-- 通告消息
CHAT_TEXT_MAIL_NOTIFY		= 4		-- 邮件消息
CHAT_TEXT_WORLD				= 5		-- 世界消息
CHAT_TEXT_GUILD				= 6		-- 公会消息
CHAT_TEXT_LOG				= 7		-- 日志消息
CHAT_TEXT_WHISPER			= 8		-- 私聊消息


----------------------------------战神系统加分-----------------------------------------------------------------------------------------
----用到的函数是AddMilitaryScore类型1表示1V1，2表示3V3，3表示15V15，4表示野外，5表示帮派战和跨服帮派战
BattleGod = {YW = {},BBZ = {},}
BattleGod.YW[1] = 20----野外杀人者获得的战神积分数

BattleGod.BBZ[1] = 100 -----本服帮派战进入加的战神的积分数

-----------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------华林射鬼（迷宫）加经验公式倍数-------------------------------------------------------------------------------------
MULTIPLE1 = 750	------1层的每秒基础经验，经验倍数为等级的分段函数
MULTIPLE2 = 1250 ------2层的每秒基础经验，经验倍数为等级的分段函数
EXPTIME = 10	-------每隔多久给予玩家一次经验,区域分段写在了活动脚本中@杨磊
-----------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------
