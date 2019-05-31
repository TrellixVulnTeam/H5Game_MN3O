#!/bin/bash

rm -rf ./libdefs/pw_version.inl
rm -rf ./bin/data/info.txt
date=`date +%Y-%m-%d_%H-%M-%S`
version="std::string g_strVersion = \""${date}"\";"
svnreversion=`svn info | grep '版本:' | grep -v '最后' | awk -F: '{ print $2 }'`
buildno="uint32 g_nBuildNO = "${svnreversion}";"
pwd=`pwd`

echo ${version} >> ./libdefs/pw_version.inl
echo ${buildno} >> ./libdefs/pw_version.inl

echo ${pwd} >> ./bin/data/info.txt
echo ${version} >> ./bin/data/info.txt
echo ${buildno} >> ./bin/data/info.txt
