
int SImplDungeon::LuaE_IsDungeonFull(lua_State* L)
{
    assert(lua_gettop(L) = =1)
    sint64 mapid = (sint64)lua_tonumber(L,1);
    
    SImplDungeon* simpl = (SImplDungeon*)pwdist::Port::self();
    
    SDungeon* info = simpl->GetDungeon(mapid);
    
    // 将返回值压栈
    lua_pushboolean(L,info->nHumanCount > 500);
    
    return 1; // 返回一个值
}

void SImplDungeon::_rpc_call_LoginToStageAndAUtoCreateSubline(sint64 mapid,sint64 humanid,pwdist::Chunk recordbuf)
{
    SLuaExportDef exports[] = 
    {
        { “LuaE_IsDungeonFull”, &LuaE_IsDungeonFull } ,
        { “LuaE_AddHumanToDungeon”, &LuaE_AddHumanToDungeon },
        { NULL, NULL },
    };
    
    SDungeon* dungeon = GetDungeonInfo(mapid);
    if(dungeon == NULL)
    {
        ReturnEx(-1);
        return ;
    }

    this->pwdistExec(“LoginToStageAndAutoCreateSubline”,exports,node,port,mapid,humanid,recordbuf);
}