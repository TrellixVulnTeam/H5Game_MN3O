g=require('./gdbclient')
t=require('./util.js')
c=new g.Client()
c.connect('10.68.43.14',8016)
c.authentication('test','test')
c.select('characters')

var babel = c.hvals('humanbabel')
for(var i = 0; i < babel.length; i++)
{
	var hid = babel[i].hid;
	var orank = babel[i].babel_rank
	console.log('old rank : ' + orank)
	var human = c.hget('human',hid)[0]
	if(typeof(human) != 'object' )
	{
		console.log('null hid : ' + hid)
		continue
	}
	
	var level = human.level
	if(level >= 28 && level <= 30)
	{
		console.log('chg level : ' + level)
		babel[i].babel_rank = orank+1
		babel[i].babel_curlv = 1
		c.hset('humanbabel',hid,babel[i])
	}
	else if(level > 30)
	{
		console.log('chg level : ' + level)
		babel[i].babel_rank = orank+2
		babel[i].babel_curlv = 1
		c.hset('humanbabel',hid,babel[i])
	}
	
	console.log('new rank : ' + babel[i].babel_rank)
	console.log('')
}

console.log('initial finished!')
