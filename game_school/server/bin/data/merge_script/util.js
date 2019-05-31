
exports.filter = function (array,fn) {
			for(var i in array) {
				if(fn(array[i])) {
					console.log(array[i])
				}
			}
		}
exports.runfile = function(filename) {
	var fs = require('fs')
	var vm = require('vm')
	fs.readFile(filename,'utf-8',function(err,data) {
		if(err) {
			console.error(err)
		} else {
			vm.runInThisContext(data)
		}
	})
}

exports.finditemowner = function(c) {
	itemids = [ 3062617,3062715,3048552,3062695,3062729,3045520,3062653,3060919,3062683,3062707,3062697,3062721,3062705,3062706,3052079,3062646,3062616,3062723,3062693,3062692,3062690,3062689,3050208,3062719,3062649,3062699,3062493,3062536,3062696,3062624,3062703,3040599,3060879,3062670,3062671,3049436,3062687,3062662,3062664,3062698,3062727,3062714,3062665,3062644,3062685,3062659,3062648,3062619,3062521,3062682,3062667,3062675,3062638,3062701,3062702,3062635,3062713,3062603,3062657,3062711,3060693,3062633,3060872,3062704,3062663,3062691,3062718 ]
	humans = c.hvals('human')

	for(var i in humans) {
		var h = humans[i]
		var humanitems = c.hvals('humanitems.' + h.id)
		for(var j in humanitems) {
			var hitems = humanitems[j]
			for(var k in hitems.item_uuids) {
				var id = hitems.item_uuids[k]
				for(var o in itemids) {
					var itemid = itemids[o]
					if(itemid == id) {
						console.log('human:' + h.id + ' itemid:' + itemid)
						break
					}
				}
			}
		}
	}
}