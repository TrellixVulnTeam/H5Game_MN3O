--[[
bson_encode(table,[sort]) : BsonObject*
bson_decode(BsonObject*) : table

BsonObject* - val :
	isbson : bool
	toll : int64
	obj(f) : err,BsonObject*
	int(f) : err,int64
	str(f) : err,string
	dec(f) : err,double
	
DatabaseScriptHelper* - db:
	WriteI(int64)
	WriteS(string)
	WriteB(BsonObject*)
	WriteNil()
	
	Hall(name,function(db,name,key,val)) **c++exception
	Hcrossall(name,,function(db,name,key,val)) **c++exception
	Hdrop(name)
	Hsize(name) : int32
	Hget(name,key) : nil | BsonObject*
	Hset(name,key,BsonObject*) : true | false
	Hdel(name,key) : true | false
--]]

function G_split_str(str)
	local result = {}
	while true do
		local pos,len = string.find(str,'`')
		if pos == nil then
			if string.len(str) > 0 then
				table.insert(result,str)
			end
			break
		end
		
		local param = string.sub(str,0,len - 1)
		table.insert(result,param)
		str = string.sub(str,len+1)
	end
	return result
end

function filter(name,key,val)
	local err,_ = val:str('last_login')
	if err ~= nil then
		print(key .. ': no found last_login intval=' .. tostring(val:toll()))		
	end
	return false
end

function execute(db,strparam)
	db:WriteI(0)
	db:WriteS('ok')
	
	local bson1 = db:Hget('human','-1')
	if bson1 ~= nil then
		print(tostring(bson1))
		local table1 = bson_decode(bson1)
		
		local bson2 = bson_encode(table1,true)		
		db:WriteB(bson1)
		db:WriteB(bson2)		
	end
end

function query_human_items(db,hid)
        db:WriteI(0)
        db:WriteS('ok')
        local fn = function(db,name,key,val)
                local t = bson_decode(val)
                local itemids = t.item_uuids
				
				if itemids == nil then
					return true
				end

                for k,v in pairs(itemids) do
                        local itemdata = db:Hget('item',tostring(v))
						if itemdata ~= nil then
							db:WriteNil()
						else
							db:WriteB(itemdata)
						end
                end
				return true
        end
        local humanitems=db:Hall('humanitems.' .. hid,fn)
end

function clear_heros(db)
	db:WriteI(0)
	db:WriteS('ok')
	
	local count = 0
	local heros = {}
	local fn = function(db,name,key,val)
		local t = bson_decode(val)
		if t.flags ~= nil and t.flags == 8 then
			count = count + 1
			table.insert(heros,tostring(t.id))
		end
		return true
	end
	
	db:Hall('human',fn)
	
	for _,v in ipairs(heros) do
		db:Hdel('human',v)
	end
	db:WriteI(toll(count))
end

function count_heros(db)
	db:WriteI(0)
	db:WriteS('ok')
	
	local count = 0
	local heros = {}
	local fn = function(db,name,key,val)
		local t = bson_decode(val)
		if t.flags ~= nil and t.flags == 8 then
			count = count + 1
		end
		return true
	end
	
	db:Hall('human',fn)
	db:WriteI(toll(count))
end

function find_byname(db)
	db:WriteI(0)
	db:WriteS('ok')
	
	local count = 0
	local heros = {}
	local fn = function(db,name,key,val)
		local t = bson_decode(val)
		if t.name ~= nil and string.find(t.name,name) ~= nil then
			db:WriteI(toll(t.hid))
			db:WriteS(t.name)
		end
		return true
	end
	
	db:Hall('namedhuman',fn)
end

function connect_human_to_passport(db,strparams)
	db:WriteI(0)
	db:WriteS('ok')
	
	local tparams = G_split_str(strparams)
	local hidstr,passport = unpack(tparams)
	
	print(hidstr)
	print(passport)
	
	local humanobj = db:Hget('human',hidstr)
	local passportobj = db:Hget('passporthuman',passport)
	if humanobj ~= nil and passportobj ~= nil then

		local humant = bson_decode(humanobj)
		local passportt = bson_decode(passportobj)
		
		if passportt.hid == nil then
			passportt.hid = {}
		end
		
		for _,v in pairs(passportt.hid) do
			if tostring(v) == tostring(humant.id) then
				db:WriteS('failed,human allready in passport')
				return 
			end
		end
		
		humant.passport = passport
		table.insert(passportt.hid,toll(humant.id))
		
		local humanbson = bson_encode(humant,false)
		local passportbson = bson_encode(passportt,false)
		
		db:Hset('human',hidstr,humanbson)
		db:Hset('passporthuman',passport,passportbson)
		db:WriteS('successful')
	else
		db:WriteS('failed,human or passport no exists')
	end
end

function test_split(db,strparam)
	db:WriteI(0)
	db:WriteS('ok')
	
	local params = G_split_str(strparam)
	for k,v in ipairs(params) do
		db:WriteS(v)
	end
end