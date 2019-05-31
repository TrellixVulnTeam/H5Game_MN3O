

for(var i = 0; i < charges.length; ++i) {
	var v = { _T: "commonactivitychargesum", uid: '(longlong)' + charges[i].roleid,charge_sum: String(charges[i].rmb_fen / 10) }
	c.hset("commonactivitychargesum",charges[i].roleid,v)
//	console.log(v)
}