-- Ctrlsrv ��½����ͼ,�������Զ��������� ����Ϊ  ��ͼ�������� => ��worldsrv�ϴ������ߵ�ͼ => ��½���µ�ͼ, ����û�� =>��½��ָ����ͼ
function LoginToStageAndAutoCreateSubline(exports,targetDungeonNode,targetDungeonPort,targetDungeon,humanid,recordbuf)
    
    local IsDungeonFull = exports["LuaE_IsDungeonFull"] or nil;
    assert(IsDungeonFull)
    
    -- �첽����ֵ��׼��
	local prepareid = __pwdist_prepare_async_return()

    if not IsDungeonFull(targetDungeon) then
        -- ��ͼ����û����,ֱ�ӵ�½
        __pwdist_prepare(targetDungeonNode,targetDungeonPort,targetDungeon,0)
        local errorcode = __pwdist_callwithresult(nil,��Login��,humanid,recordbuf)
        -- ���ص�½���
        __pwdist_async_return(prepareid,errorcode,targetDungeonNode,targetDungeonPort,targetDungeon)
    else
        -- node,port�����ⲿ�����exports�л�ȡ
        local node = "worldsrv0"
        local port = "1"
        
        -- ����һ����ͼ�����ߣ�
		__pwdist_prepare(node,port,0); 
		local errorcode,mapid = __pwdist_callwithresult(nil,��CreateDungeon��,...)
        
        -- �ɹ���������
		if errorcode == 0 then 
            
            -- ��½
            __pwdist_prepare(port,node,mapid,0)
            
            local errorcode = __pwdist_callwithresult(nil,��Login��,humanid,recordbuf)
            
            -- ���ص�½���
            __pwdist_async_return(prepareid,errorcode,node,port,mapid)
        else
            -- ���ش������߷ְ�
            __pwdist_async_return(prepareid,-100)
        end
    end
end
