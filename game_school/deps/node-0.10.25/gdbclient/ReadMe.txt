���Բ������ݿ����ݵ������й���
ʹ�÷�����ִ��node.exe
����
gdb = require('./gdbclient')
c = new gdb.Client()
c.help()���Կ�c֧�ֵĺ���

�������ݿ������

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
tmp.name = '����������'
c.hset('human',-1,tmp)

ע�⣺�����������ᵼ�������ƻ�����Ҫô��ģ�Ҫôͬʱά������

��������ǻ���node.js������ִ��javascript���к�����֧�������������ݿ��¼

tmp = c.hcrossvals('humanitems')
tmp2 = []
for(var i = 0; i < tmp.length; i++)
{
	console.log(tmp[i].item_uuids[0])
}