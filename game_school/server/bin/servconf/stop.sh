#!/bin/bash
#pkill -2 -x pwconnsrv 
#pkill -2 -x pwaccsrv
#pkill -2 -x pwdbsrv
#pkill -2 -x pwctrlsrv
#pkill -2 -x pwworldsrv

#pkill -2 -x pwclientlog

pwd=`pwd`

echo 20 > $pwd/stop.sig
sleep 30

aa=$(ps -ef | grep $pwd|grep -v grep |wc -l)
if [[ $ab -ge 1 ]]
then
	killall -2 $pwd/pw*
	sleep 30
	ab=$(ps -ef | grep $pwd|grep -v grep | wc -l)
	if [[ $ab -ge 1 ]]
	then
        killall -9 $pwd/pw*
		echo "Kill -9 Performed"
	else
        echo "Kill -2 OK"
	fi
else
	echo "Close OK"
fi

#if [ -f "$pwd/stop.sig"] then
#	rm -rf $pwd/stop.sig
#	echo "stop.sig exists,removed"
#fi
rm -rf $pwd/stop.sig