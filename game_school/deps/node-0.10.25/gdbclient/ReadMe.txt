可以操作数据库数据的命令行工具
使用方法，执行node.exe
输入
gdb = require('./gdbclient')
c = new gdb.Client()
c.help()可以看c支持的函数

操作数据库的例子

gdb = require('./gdbclient')
c = new gdb.Client()
c.connect('172.22.111.31',8018)
c.authentication('test','test')
c.select('characters')


gdb = require('./gdbclient')
c = new gdb.Client()
c.connect('10.68.43.10',8016)
c.authentication('test','test')
c.select('characters')

gdb = require('./gdbclient')
c = new gdb.Client()
c.connect('127.0.0.1',8600)
c.authentication('test','test')
c.select('account')
c.hscan('passport','cbh10.','cbh',100)
c.select('characters')

tmp = c.hget('human',-1)[0]
tmp.name = '哈哈改名了'
c.hset('human',-1,tmp)

注意：：更改主键会导致索引破坏！！要么别改，要么同时维护索引

这个工具是基于node.js，可以执行javascript所有函数，支持批量处理数据库记录

tmp = c.hcrossvals('humanitems')
tmp2 = []
for(var i = 0; i < tmp.length; i++)
{
	console.log(tmp[i].item_uuids[0])
}