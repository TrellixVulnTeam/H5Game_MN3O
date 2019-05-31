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
						if itemdata != nil then
							db:WriteNil()
						else
							db:WriteB(itemdata)
						end
                end
				return true
        end
        local humanitems=db:Hall('humanitems.' .. hid,fn)
end