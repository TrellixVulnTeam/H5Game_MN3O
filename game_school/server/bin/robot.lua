--[[
命令
	q 退出
	c 创建机器人 参数:-N 前缀,-s 开始id,-e 结束id
	gm text 发gm命令,参数: -s 影响的账号开始id, -e 影响的账号结束id
	moveto x y z 移动到x,y,z点(需要服务器寻路,比较卡)
	movetorandom x y z dist 在x,y,z点的dist距离内随机移动
	caster start 开始随机施法
	caster stop  停止随机施法
	ladder_start 所有账号开始登录天梯
	ladder_clean 所有账号关闭天新梯
	server -i ip -p port 将连接的服务器设为ip,port
	close 关闭所有机器人
	
	GM指令：
	1.随机装备   /random_equip (无视角色等级限制)
	2.开始龙跟随 /start_follow (随机选龙)
	停止龙跟随 /stop_follow
	3.开始骑乘   /robot_startride (随机选坐骑)
	停止骑乘   /robot_stopride
	4.开始龙召唤 /start_summon (随机选龙)
	停止龙召唤 /stop_summon
函数
	cmd 执行命令
	sleep 等待时间(毫秒)
]]--

cmd("server -i 127.0.0.1 -p 8000")

local count = 1
local numperonloop = 10

for i = 0, count do
    local str = "c -N robot -s " .. tostring(i*numperonloop + 1) .. " -e " .. tostring((i+1)*numperonloop)
    cmd(str)

    sleep(5000)
    local str = "gm /gofb 1105 -s " .. tostring(i*numperonloop + 1) .. " -e " .. tostring((i+1)*numperonloop)
    cmd(str)
	sleep(5000)
end

sleep(3000)
cmd("gm /wudi 1")
cmd("caster start")