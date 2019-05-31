g_async_scripts = {}

function async_script_make(ptr,context,func,funcInit,funcExit)
	local routine = coroutine.create(async_script_wrapper)
	coroutine.resume(routine,ptr,context,routine,func,funcInit,funcExit)
end

function async_script_wrapper(ptr,context,routine,func,funcInit,funcExit)
	g_async_scripts[routine] = routine
    
	funcInit(ptr,routine)
    
	local callable = _G[func]
    
	if callable ~= nil then
		callable(context)
	else
		__pwdist_log("async_context_wrapper " .. func .. " not exists!!")
	end
    
	funcExit(ptr)
	g_async_scripts[routine] = nil
end


