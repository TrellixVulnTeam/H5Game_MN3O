
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

var humans = c.hvals('human')
for(var i = 0; i < humans.length; i++) {
	var hid = humans[i].id
	if(typeof hid == 'string' && hid.indexOf('longlong') > 0)
		hid = g.ll2str(hid)

	var humandailybonus = c.hget('humandailybonus',hid)
	if(!!humandailybonus && humandailybonus.length == 1) {
		if(!!humandailybonus[0].active_total) {
			humans[i].active_total=humandailybonus[0].active_total
		} else {
			humans[i].active_total = 0
		}
		
	}
}

function compare_func(a,b) {
	if(a.active_total > b.active_total) {
		return -1
	} else if(a.active_total < b.active_total) {
		return 1
	}
	return 0;
}

humans.sort(compare_func)

for(var i = 0; i < humans.length; i++) {
	var h = humans[i]
	var hid = humans[i].id
	if(typeof hid == 'string' && hid.indexOf('longlong') > 0)
		hid = g.ll2str(hid)

	if(h.active_total <= 0) {
		continue
	}
	console.log('hid=' + hid + ' name=' + h.name + ' active=' + h.active_total)
}