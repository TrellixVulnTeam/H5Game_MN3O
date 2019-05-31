#!/bin/bash 
ulimit -c unlimited
ulimit -n 204800

pwd=`pwd`

echo "********************************************************"
ulimit -c
echo "********************************************************"

nohup $pwd/pwglobalsrv >$pwd/pwglobalsrv.out&
