function on_test_query_subline(timeout,chunk)
	pwdist.log('on_test_query_subline')
	local c = pwdist.bson_decode(chunk)
	for k,v in pairs(c) do
		pwdist.log('k=' .. tostring(k) .. ' v1=' .. tostring(v['v1']) .. ' v2=' .. tostring(v['v2']) .. ' v3=' .. tostring(v['v3']))
	end
end

function test_query_subline(strid)
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.stagemgr,0)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.SImplStageMgr.QueryStageSubline,toll(strid))
    pwdist.listen_result("on_test_query_subline")
end

function test_crash()
    local human = GetCurrentHuman()
    human:GetModQuest():DoneQuest(nil)
end

function testquest()
    local human = GetCurrentHuman()
    human:GetModQuest():GetMonsterKilled(27,10256)
    
end

function test_trigger22()
    local stage = GetCurrentStage()
    local trigger = stage:CreateTriggerSphere({1.9,1.1,1.5},5,"","")
    trigger:SetContext({1,"dafdsaf",3453.345345,22342343242})
    local tb = trigger:GetContext()
    for k,v in ipairs(tb) do
        print('k = ' .. tostring(k) .. '  v = ' .. tostring(v))
    end
    trigger:LeaveWorld(0)
end

function done_quest(strid)
    local human = GetCurrentHuman()
    human:GetModQuest():DoneQuest(tonumber(strid))
end

function open_hint(strid,strtime)
    local human = GetCurrentHuman()
    human:Hint(tonumber(strid),tonumber(strtime))
end

function close_hint(strid)
    local human = GetCurrentHuman()
    if strid == nil then
        human:CloseHint(0)
    else
        human:CloseHint(tonumber(strid))
    end
end

function open_adventure(strid,selfid)
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.adventure,0)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.SImplAdventure.CreateAdventure,tonumber(strid),tonumber(selfid),nil)
end

function cancel_adventure(selfid)
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.adventure,0)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.SImplAdventure.Leave,tonumber(selfid),0)
end

function open_activity(strid)
    if strid == nil then
        do return end
    end
	--pw_human_tester.cpp中实现
    --pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity,0)
    --pwdist.call(nil,pwngs_rpcnames.ctrlsrv.SImplActivity.GMStart,tonumber(strid))
end

function stop_activity(strid)
    if strid == nil then
        do return end
    end
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity,0)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.SImplActivity.GMClean,tonumber(strid))
end

function exec_activity(id,func,...)
    local buf,_ = seripack(...)
    print('exec_activity id = ' .. id .. ' func=' .. func)
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity,0)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.SImplActivity.CallScript,tonumber(id),func,buf)
end

function JTZChoiceGuildWarList(id)
	pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity, 2)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.ActivityNJTZ.JTZChoiceGuildWarList, tonumber(id))
end

function test_seri(buf,len)
    local humanid,str,num,int = seriunpack(buf,len)
    pwdist.log(humanid,str,num,int)
    print('test_seri ' .. tostring(humanid) ..  ' ' .. tostring(str) .. ' ' .. tostring(num) .. ' ' .. tostring(int))
end

function killtest()
    local human = GetCurrentHuman()
    human:GetModCombat():KillSelf(1050,1050)
end

function njtzinit(r)
	local round = r or 1
	pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity, 2)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.ActivityNJTZ.Init,tonumber(round))
end

function njtzinit2(id1,id2)
    if (id1 == nil) or (id2 == nil) then
        return
    end
	pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity, 2)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.ActivityNJTZ.InitWithGuilds,toll(id1),toll(id2))
end

function njtzfinish()
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity, 2)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.ActivityNJTZ.Finish)
end

function njtzclear(r)
	pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity, 2)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.ActivityNJTZ.GMClear)
end

function njtzrefresh(r)
	pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity, 2)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.ActivityNJTZ.GMRefresh)
end

function lgkjfinish(aid)
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity, tonumber(aid))
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.ActivityLGKJ.Finish)
end

function create_peroid_timer_at(str1,str2)
    if str1 == nil or str2 == nil then
        return
    end
    local stage = GetCurrentStage()
    stage:GetModCommon():CreatePeriodTimerAt(str1,str2,false) 
end

function exitserver(str1)
    if str1 == nil then
        pwdist.log('str == nil')
        do return end
    end
    pwdist.log('exit server ' .. str1)
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.stagemgr, 0)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.SImplStageMgr.ExitAfter,tonumber(str1))
end

function unsrv_check(name1)
    if name1 == nil then
        pwdist.log('name1 == nil')
        do return end
    end
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.common, 5)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.NameMgr.Check,tostring(name1))
 
end

function unsrv_take(name1)
    if name1 == nil then
        pwdist.log('name1 == nil')
        do return end
    end
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.common, 5)
    pwdist.call(nil,pwngs_rpcnames.ctrlsrv.NameMgr.TakeUp,tostring(name1),tostring(name1))
 
end

function dofile(str1)
	luaE_dofile("./Lua/worldsrv/" .. str1)
	print("dofile" .. str1)		
end