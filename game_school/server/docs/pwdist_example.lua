-- Ctrlsrv 登陆到地图,人满则自动创建分线 流程为  地图人数满了 => 在worldsrv上创建分线地图 => 登陆到新地图, 人数没满 =>登陆到指定地图
function LoginToStageAndAutoCreateSubline(exports,targetDungeonNode,targetDungeonPort,targetDungeon,humanid,recordbuf)
    
    local IsDungeonFull = exports["LuaE_IsDungeonFull"] or nil;
    assert(IsDungeonFull)
    
    -- 异步返回值的准备
	local prepareid = __pwdist_prepare_async_return()

    if not IsDungeonFull(targetDungeon) then
        -- 地图人数没有满,直接登陆
        __pwdist_prepare(targetDungeonNode,targetDungeonPort,targetDungeon,0)
        local errorcode = __pwdist_callwithresult(nil,”Login”,humanid,recordbuf)
        -- 返回登陆结果
        __pwdist_async_return(prepareid,errorcode,targetDungeonNode,targetDungeonPort,targetDungeon)
    else
        -- node,port可由外部传入或exports中获取
        local node = "worldsrv0"
        local port = "1"
        
        -- 创建一个地图（分线）
		__pwdist_prepare(node,port,0); 
		local errorcode,mapid = __pwdist_callwithresult(nil,”CreateDungeon”,...)
        
        -- 成功创建分线
		if errorcode == 0 then 
            
            -- 登陆
            __pwdist_prepare(port,node,mapid,0)
            
            local errorcode = __pwdist_callwithresult(nil,”Login”,humanid,recordbuf)
            
            -- 返回登陆结果
            __pwdist_async_return(prepareid,errorcode,node,port,mapid)
        else
            -- 返回创建分线分败
            __pwdist_async_return(prepareid,-100)
        end
    end
end
