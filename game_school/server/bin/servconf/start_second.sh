#!/bin/bash 
ulimit -c unlimited
ulimit -n 204800

pwd=`pwd`

echo "********************************************************"
ulimit -c
echo "********************************************************"

nohup $pwd/pwconnsrv $pwd/pwconnsrv_2.xml >$pwd/pwconnsrv2.out&
nohup $pwd/pwworldsrv $pwd/server_1.xml  >$pwd/pwworldsrv1.out&

#nohup $pwd/pwclientlog 8015 >pwclientlog.out&