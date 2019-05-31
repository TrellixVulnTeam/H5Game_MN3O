
if(process.argv.length != 5) {
        console.log('need args: ip port dbname')
}

g=require('./gdbclient')
c=new g.Client()

if(!c.connect(process.argv[2],process.argv[3])) {
        throw new Error('connect to server failed')
        return
}

if(!c.authentication('test','test')) {
        throw new Error('authentication to server failed')
}

if(!c.select(process.argv[4])) {
        throw new Error('select database failed')
}

var sid = c.hget('systemconfigure','0')
var zid = c.hget('systemconfigure','1')

if(typeof sid == 'object' && sid.length == 1) {
	sid = sid[0]
        if(!sid.ivar1) { sid.ivar1 = 0; }
        console.log('localid\t' + sid.ivar1)
}

if(typeof zid == 'object' && zid.length == 1) {
        zid = zid[0]
        if(!zid.ivar1) { zid.ivar1 = 0; }
        console.log('zoneid\t' + zid.ivar1)
}