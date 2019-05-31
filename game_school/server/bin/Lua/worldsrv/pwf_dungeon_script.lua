
---------------------------------------------------------------------------

DungeonScriptNode = {}
DungeonScriptNode.Childs = {}

---------------------------------------------------------------------------

function DungeonScriptNode:Enter(script)
end

function DungeonScriptNode:Update(script)
    return true
end

function DungeonScriptNode:Leave(script)

end

function DungeonScriptNode:New(o)
    local v = o or {}
    setmetatable(v,self)
    self.__index = self
    return v
end

---------------------------------------------------------------------------

function DungeonScriptStartup(script)
    if script == nil then
        print("DungeonScriptStartup error script=nil")
        return 
    end
    
    local len = #script.RunningNodes
   
    for i = len, 1 , -1 do

        local node = script.RunningNodes[i]
        
        node:Enter(script)
    end
end

function DungeonScriptUpdate(script)

    if script == nil then
        print("DungeonScriptUpdate error script=nil")
        return 
    end
    
    local len = #script.RunningNodes
   
    for i = len, 1 , -1 do
    
        local node = script.RunningNodes[i]
        
        local result = node:Update(script)
        
        if result == true then
            
            node:Leave(script)
            
            table.remove(script.RunningNodes,i)
            
            local childs = node.Childs
            
            for j = 1, #childs do
                table.insert(script.RunningNodes,childs[j])
                childs[j]:Enter(script)
            end  
        end
    end
end


function DungeonScriptCleanup(script)
    if script == nil then
        print("DungeonScriptCleanup error script=nil")
        return 
    end
    
    local len = #script.RunningNodes
   
    for i = len, 1 , -1 do

        local node = script.RunningNodes[i]
        
        node:Leave(script)
    end
end