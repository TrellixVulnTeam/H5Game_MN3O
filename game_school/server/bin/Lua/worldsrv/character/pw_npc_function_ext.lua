----------------------------------------------------------
-- 功能Npc功能脚本
-- 对应NPCFunctionConfig.xls表中"扩展选项脚本"
----------------------------------------------------------

--test--test--test--test--test--test--test--test--test--test--
NpcFunctionScript1 = {}

NpcFunctionScript1.config = 
{
    {names={90001,90002},func="OnSelect_1"},
    {names={90010,18501},func="OnSelect_2"},
}

function NpcFunctionScript1.OnOpenDialog(human)
    pwdist.log("OnOpenDialog")
    
    if human:GetLevel() > 20 then
        return NpcFunctionScript1.config[1].names, NpcFunctionScript1.config[1].func
    end
    
    return {},""
end

function NpcFunctionScript1.OnSelect_1(human,index)
    pwdist.log("OnSelect_1,index:" .. tostring(index))
end

function NpcFunctionScript1.OnSelect_2(human,index)
    pwdist.log("OnSelect_2,index:" .. tostring(index))
end





