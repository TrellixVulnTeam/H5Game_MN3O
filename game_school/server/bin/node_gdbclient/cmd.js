g=require('./gdbclient')
c=new g.Client()
c.connect('127.0.0.1',8600)
c.authentication('test','test')
c.select('testdb')

// 目标数据库
v_dst_dbname = 'origin_4300'
v_dst_zoneid = 4300

// 源数据库
v_src_dbname = 'origin_4301'
v_src_zoneid = 4301
v_src_localid = 1

// 修复名字前缀
//c.modload('dbmod_fix_names','./libdbmod_fix_names.so')
//c.modexec('dbmod_fix_names',{db: 'characters',prefix: 'S1.'})
// 修复名字前缀2(*漏了namedhuman的key)
//c.modload('dbmod_fix_names2','./libdbmod_fix_names2.so')
//c.modexec('dbmod_fix_names2',{db: 'characters',prefix: 'S1.'})

// 删除两个数据库里无用的玩家数据
c.modload('dbmod_remove_futile','./libdbmod_remove_futile.so')
c.modexec('dbmod_remove_futile',{db: v_dst_dbname,related: __human_slaves,related_slave: __human_slave_tables, related_global_slave: [ {'guildmember': 'uid'}]})
c.modexec('dbmod_remove_futile',{db: v_src_dbname,related: __human_slaves,related_slave: __human_slave_tables, related_global_slave: [ {'guildmember': 'uid'}]})

// 合服
c.modload('dbmod_merge','./libdbmod_merge.so')
c.modexec('dbmod_merge',{
db1: {name: v_dst_dbname, zoneid: v_dst_zoneid },
db2: {name: v_src_dbname, zoneid: v_src_zoneid },
merge_tables: __human_slaves.concat(__passport_slaves).concat(__global_tables),
merge_slave_tables: __human_slave_tables.concat(__passport_slave_tables).concat(__global_salve_tables),
merge_zset: __ranklist_names,
remove_table_fields: [ {"guild": "applist"} ]
})


// 合服后清除部份数据
c.select(v_dst_dbname)
c.hclear('legionwar')
c.hclear('warlordcombatresult')
c.hclear('legionwarsupport')
c.hclear('globalwelfare')
c.hclear('arenaseasonuser')
c.hclear('legionwarhistory')

c.hclear('ctrlhotactivity')
c.hclear('humanhotactivity')

c.hclear('humancommonactivity')
c.hclear('commonactivityreward')

// 重置玩家身上的全局发奖id

c.hupdate('human',{},{ $set: {'award_server_taken_id': 0} } )

// 合服信息
c.hset('systemmergeinfo',v_src_localid,{ sid:v_src_localid, zoneid: v_src_zoneid,date:'2014-08-19 14:44:00'})
// 最后合服时间(合服活动)
c.hset('systemconfigure','6',{ id:6,ivar1: 20140819})