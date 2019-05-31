function main_worldsrv()
    luaE_dofile("./Lua/worldsrv/pw_const.lua")
	luaE_dofile("./Lua/worldsrv/pw_function.lua")
    luaE_dofile("./Lua/worldsrv/pw_activity.lua")
	luaE_dofile("./Lua/worldsrv/pw_public_data.lua")
	luaE_dofile("./Lua/worldsrv/pw_tester.lua")
	luaE_dofile("./Lua/worldsrv/pwf_async_context.lua")
    luaE_dofile("./Lua/worldsrv/pwf_dungeon_script.lua")
	
	luaE_dofile("./Lua/worldsrv/character/pw_region_trigger.lua")
	luaE_dofile("./Lua/worldsrv/character/pw_static_object_trigger.lua")
	luaE_dofile("./Lua/worldsrv/character/pw_npc_function.lua")
    luaE_dofile("./Lua/worldsrv/character/pw_npc_function_ext.lua")
	luaE_dofile("./Lua/worldsrv/character/pw_creature_dead.lua")
	luaE_dofile("./Lua/worldsrv/character/pw_creature_spawn.lua")
	luaE_dofile("./Lua/worldsrv/character/pw_creature_drop.lua")
	
	luaE_dofile("./Lua/worldsrv/dungeon/pw_dungeon_select.lua")
	luaE_dofile("./Lua/worldsrv/activities/pww_activities.lua")
	
	luaE_dofile("./Lua/worldsrv/ai/pw_ai_def.lua")
	luaE_dofile("./Lua/worldsrv/ai/pw_scripted_ai.lua")
	luaE_dofile("./Lua/worldsrv/ai/pw_ai_combat.lua")
	luaE_dofile("./Lua/worldsrv/ai/pw_ai_init.lua")
	luaE_dofile("./Lua/worldsrv/ai/pw_npc_condition_skill.lua")
	
	luaE_dofile("./Lua/worldsrv/item/pw_item_use.lua")
  
	luaE_dofile("./Lua/worldsrv/quest/pw_quest_done.lua")
	luaE_dofile("./Lua/worldsrv/quest/pw_player_advance_hint.lua")
	
	luaE_dofile("./Lua/worldsrv/skill/pw_combat_trigger.lua")
end

------------------------------------------------------------------------------------------------------------------

main_worldsrv()
