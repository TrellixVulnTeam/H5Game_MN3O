#!/bin/bash 
ulimit -c unlimited
ulimit -n 204800

pwd=`pwd`

echo "********************************************************"
ulimit -c
echo "********************************************************"

nohup $pwd/pwconnsrv $pwd/pwconnsrv_1.xml >$pwd/pwconnsrv1.out&
nohup $pwd/pwaccsrv >$pwd/pwaccsrv.out&
nohup $pwd/pwdbsrv  >$pwd/pwdbsrv.out&
nohup valgrind --tool=memcheck $pwd/pwctrlsrv  >$pwd/pwctrlsrv.out&
nohup valgrind --tool=memcheck $pwd/pwworldsrv $pwd/server_0.xml  >$pwd/pwworldsrv0.out&

#nohup $pwd/pwclientlog 8015 >pwclientlog.out&
