
if(process.argv.length != 5) {
    throw new Error('need args: addr port dbname')
}

g=require('./gdbclient')
c=new g.Client()

if(!c.connect(process.argv[2],process.argv[3])) {
    throw new Error('connect to server failed')
}

if(!c.authentication('test','test')) {
    throw new Error('authentication to server failed')
}

if(!c.select(process.argv[4])) {
	throw new Error('select database failed')
}

var mergeinfos = c.hvals('systemmergeinfo')
if(typeof mergeinfos == 'object') {
		if(mergeinfos.length == 0) {
			console.log('merged\t-1\t-1\t-1')
		}
        for(var i = 0; i < mergeinfos.length; i++) {
                console.log('merged\t' + mergeinfos[i].sid + '\t' + mergeinfos[i].zoneid + '\t' + mergeinfos[i].date)
        }
} else {
	console.log('merged\t-1\t-1\t-1')
}