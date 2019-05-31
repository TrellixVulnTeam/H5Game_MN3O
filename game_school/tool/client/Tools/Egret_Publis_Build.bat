@ECHO OFF

cd scripts && node createResourceVersionCopy.js

rem egret publish build 
cd ../py

python Egret_PublishBuild.py

pause