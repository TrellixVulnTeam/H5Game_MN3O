
g=require('./gdbclient')
c=new g.Client()
c.connect('10.68.43.14',8016)
c.authentication('test','test')

// 修复账号子表key
c.modload('dbmod_fixpassportitems','./libdbmod_fixpassportitems.so')
c.modexec('dbmod_fixpassportitems',{db: 'characters'})

// 转化账号为新的账号隔离体系
c.modload('dbmod_convert_passport','./libdbmod_convert_passport.so')
c.modexec('dbmod_convert_passport',{srcdb: 'characters',dstdb: 'characters',zoneid: 4300,agent: '173'})




// 修复账号子表key
c.modload('dbmod_fixpassportitems','./libdbmod_fixpassportitems.so')
c.modexec('dbmod_fixpassportitems',{db: v_dst_dbname})
c.modexec('dbmod_fixpassportitems',{db: v_src_dbname})

// 转化账号为新的账号隔离体系
c.modload('dbmod_convert_passport','./libdbmod_convert_passport.so')
c.modexec('dbmod_convert_passport',{srcdb: v_dst_dbname,dstdb: v_dst_dbname,zoneid: v_dst_zoneid,agent: v_default_agent})
c.modexec('dbmod_convert_passport',{srcdb: v_src_dbname,dstdb: v_src_dbname,zoneid: v_src_zoneid,agent: v_default_agent})