/*
0)备份数据库,将数据库复制到合服目标数据进程
1)修改merge.json
2)修改合服日期

merge.json
{
	"host": "127.0.0.1",
	"port": 8600,
	"user": "test",
	"pswd": "test",
	"databases": [ '4300','4301','4302','4303','4304','4305','4306' ],
	"default_zoneids" : [ 4300,4301,4302,4303,4304,4305,4306 ],
	"default_localids": [ 0,1,2,3,4,5,6 ]
}

多次合服
merge.json
{
	"host": "10.64.72.77",
	"port": 8800,
	"user": "test",
	"pswd": "test",
	"databases": [ "4300","4303","4306","4307" ],
	"default_zoneids" : [ [4300,4301,4302],[4303,4304,4305],4306,4307 ],
	"default_localids": [ [0,1,2],[3,4,5],6,7 ]
}

*/
var fs = require('fs')

//////////////////////////////////////////////////////////
// 以下两个必须改
//////////////////////////////////////////////////////////
var merge_date = 20141112 // 合服日期
var current_date = '2014-11-12 16:00:00'
//////////////////////////////////////////////////////////

var configure_file = './merge.json'

if(process.argv.length > 2) {
	configure_file = process.argv[2]
	console.log('use configure ' + configure_file)
}

configure_data = fs.readFileSync(configure_file,'utf-8')
configure_object = JSON.parse(configure_data)

u=require('./util.js')
o=require('./orm.js')

g=require('./gdbclient')
c=new g.Client()
c.connect(configure_object.host,configure_object.port)
c.authentication(configure_object.user,configure_object.pswd)

db_list = configure_object.databases
zoneid_list = configure_object.default_zoneids
localid_list = configure_object.default_localids

if(db_list.length != zoneid_list.length || zoneid_list.length != localid_list.length)
	throw new Error('db_list & zoneid & localid length no match')

// 输出当前zoneid/localid
for (var i = 0; i < db_list.length; i++) {
	console.log('db=' + db_list[i] + ' zoneid=' + zoneid_list[i] + ' localid=' + localid_list[i])
    c.load(db_list[i])
}

if(!c.modload('dbmod_remove_futile','./libdbmod_remove_futile.so'))
	throw new Error('load dbmod_remove_futile.so failed')

if(!c.modload('dbmod_merge','./libdbmod_merge.so'))
	throw new Error('load libdbmod_merge.so failed')

//console.log(__human_slaves)

for (var i = 0; i < db_list.length; i++) {

	console.log('start dbmod_remove_futile at database:' + db_list[i])

	// 删除无用的玩家数据
	var result = c.modexec('dbmod_remove_futile',{db: db_list[i],related: __human_slaves,related_slave: __human_slave_tables, related_global_slave: [ {'guildmember': 'uid'}],
		zsets: __human_ranklist_names,
		remove_futile_passporthuman: false,
		zoneid: zoneid_list[i] })

	if (typeof(result) != 'object' || result.length != 0)
		throw new Error('dbmod_remove_futile failed:' + result)
}

for (var i = 1; i < db_list.length; i++) {

	console.log('start dbmod_merge at database:' + db_list[i])

	var result = c.modexec('dbmod_merge',{
		db1: {name: db_list[0] },
		db2: {name: db_list[i] },
		merge_tables: __human_slaves.concat(__passport_slaves).concat(__global_tables),
		merge_slave_tables: __human_slave_tables.concat(__passport_slave_tables).concat(__global_salve_tables),
		merge_zset: __ranklist_names,
		remove_table_fields: [ {"guild": "applist"} ]
		})

	if (typeof(result) != 'object' || result.length != [])
		throw new Error('dbmod_merge failed,' + db_list[i] + ' result=' + result)

}
// 合服后清除部份数据
c.select(db_list[0])

console.log('setup systemmergeinfo..')

// 合服信息
for (var i = 1; i < db_list.length; i++) {
	if(typeof(zoneid_list[i]) == 'object') {
		for(var j = 0; j < zoneid_list[i].length; ++j) {
			c.hset('systemmergeinfo',localid_list[i][j],{ sid:localid_list[i][j], zoneid: zoneid_list[i][j],date: current_date})	
		}
	} else {
		c.hset('systemmergeinfo',localid_list[i],{ sid:localid_list[i], zoneid: zoneid_list[i],date:current_date})
	}
}
// 最后合服时间(合服活动)

console.log('clean tables...')

c.hset('systemconfigure','6',{ id:6,ivar1:  merge_date})
c.hclear('legionwar')
c.hclear('warlordcombatresult')
c.hclear('legionwarsupport')
c.hclear('globalwelfare')
c.hclear('legionwarhistory')

c.hclear('ctrlhotactivity')
c.hclear('humanhotactivity')
c.hclear('openauctionitem')

c.hclear('humancommonactivity')
c.hclear('commonactivityreward')

c.hclear('guildtriallandrecord')
c.hclear('guildtriallandrecordnew')
c.hclear('lotterygloballog')
c.hclear('chestgloballog')

console.log('clean human award_server_taken_id...')
// 重置玩家身上的全局发奖id
c.hupdate('human',{},{ $set: {'award_server_taken_id': 0} } )

console.log('finished')

for (var i = 1; i < db_list.length; i++) {
	c.delete(db_list[i])
}