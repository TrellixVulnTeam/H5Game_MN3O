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

a=$(ps -ef |grep $pwd|grep -v grep |wc -l)
if [[ $a -ge 1 ]]
then
    ps aux | grep `pwd` | grep -v "grep" | awk '{print $2}' | xargs -i kill -2 {}
    echo "killall -2 finish"
else
    echo "OK"
fi

sleep 3

a=$(ps -ef |grep $pwd|grep -v grep |wc -l)
if [[ $a -ge 1 ]]
then
    ps aux | grep `pwd` | grep -v "grep" | awk '{print $2}' | xargs -i kill -9 {}
    echo "killall -9 finish"
else
    echo "OK"
fi
rm -rf $pwd/stop.sig
