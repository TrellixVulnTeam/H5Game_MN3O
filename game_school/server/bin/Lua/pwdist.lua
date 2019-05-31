
__pwdist_coroutines = {}

function __pwdist_began(co)
    __pwdist_coroutines[co] = co
end

function __pwdist_ended(co)
    __pwdist_coroutines[co] = nil
end

function __pwdist_invoke(func,exports,...)
    local routine = coroutine.create(__pwdist_wrap)
	coroutine.resume(routine,routine,func,exports,...)
end

function __pwdist_invoke_non_return(func,exports,...)
	local callable = _G[func]
	if callable ~= nil then
		callable(exports,...)
	else
		pwdist.log("__pwdist_call_non_wait " .. func .. " not exists!!")
	end
end

function __pwdist_unknown_call(func,...)
	local callable = _G[func]
	if callable ~= nil then
		callable(...)
	else
		pwdist.log("__pwdist_unknown_call " .. func .. " not exists!!")
	end
end

function __pwdist_wrap(routine,func,exports,...)
    __pwdist_began(routine)
	local callable = _G[func]
	if callable ~= nil then
		callable(exports,...)
	else
		pwdist.log("__pwdist_call " .. func .. " not exists!!")
	end
	__pwdist_ended(routine)
end

------------------------------------------------------------------------------------------------------------------

function main()
    pwdist.dofile("./Lua/pwdist_def.lua")     
    pwdist.dofile("./Lua/pwdist_rpcnames.lua")
end

------------------------------------------------------------------------------------------------------------------

main()
