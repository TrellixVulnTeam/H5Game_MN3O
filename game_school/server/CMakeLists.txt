CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# set include directory variable
SET(DEPS_ACE		${CMAKE_SOURCE_DIR}/../deps/ACE_wrappers)
SET(DEPS_BULLETPHYSICS	${CMAKE_SOURCE_DIR}/../deps/BulletPhysics/src)
SET(DEPS_CURL		${CMAKE_SOURCE_DIR}/../deps/curl-7.36.0/include)
SET(DEPS_EXPAT		${CMAKE_SOURCE_DIR}/../deps/expat-2.0.1/lib)
SET(DEPS_LEVEL_DB	${CMAKE_SOURCE_DIR}/../deps/leveldb_1_15)
SET(DEPS_LIBICONV	${CMAKE_SOURCE_DIR}/../deps/libiconv-1.9.2/include)
SET(DEPS_LOG4CPLUS	${CMAKE_SOURCE_DIR}/../deps/log4cplus-1.1.1/include)
SET(DEPS_LUA51		${CMAKE_SOURCE_DIR}/../deps/lua-5.2.0/lua5.1)
SET(DEPS_LUA51Ex	${CMAKE_SOURCE_DIR}/../deps/lua-5.2.0)
SET(DEPS_MYSQL		${CMAKE_SOURCE_DIR}/../deps/mysql)
SET(DEPS_OPENSSL	${CMAKE_SOURCE_DIR}/../deps/openssl-0.98zb/include)
SET(DEPS_PROTOBUF	${CMAKE_SOURCE_DIR}/../deps/protobuf-2.4.1/src)
SET(DEPS_PTHREAD	${CMAKE_SOURCE_DIR}/../deps/pthread_win32/include)
SET(DEPS_TBB		${CMAKE_SOURCE_DIR}/../deps/tbb40_233oss/include)
SET(DEPS_UNITTEST	${CMAKE_SOURCE_DIR}/../deps/UnitTest++2013)
SET(DEPS_VLD		${CMAKE_SOURCE_DIR}/../deps/vld_2.3/include)
SET(DEPS_ZEROMQ		${CMAKE_SOURCE_DIR}/../deps/zeromq-4.0.1/include)
SET(DEPS_ZLIB		${CMAKE_SOURCE_DIR}/../deps/zlib)

if(WIN32)

# windows platform
project(pwngs)

#可以添加解决方案项目文件夹
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

add_definitions(-D_WIN32_WINNT=0x0501)

set(LIBRARY_OUTPUT_PATH 	${CMAKE_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH	${CMAKE_SOURCE_DIR}/bin)

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/win32/lib)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/expat-2.0.1/win32/bin)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/zeromq-4.0.1/lib)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/ACE_wrappers/lib)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/tbb40_233oss/lib/ia32/vc9)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/log4cplus-1.1.1/msvc12)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/pthread_win32/lib)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/mysql/lib)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/protobuf-2.4.1/vsprojects2013)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/lua-5.2.0/lib)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/curl-7.36.0/build/lib)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/openssl-0.98zb/lib)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/vld_2.3/lib/Win32)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/zlib/lib)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/UnitTest++2013)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/libiconv-1.9.2/lib)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/BulletPhysics/lib)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../deps/gperftools-2.1/Release)

ADD_SUBDIRECTORY(pwglobalsrv pwglobalsrv/Release)

else()

# linux platform
ADD_SUBDIRECTORY(pwnrobot pwnrobot/Release)
ADD_SUBDIRECTORY(pwaccmgr pwaccmgr/Release)
ADD_SUBDIRECTORY(pwclientlog pwclientlog/Release)

ADD_SUBDIRECTORY(pwgdbclient pwgdbclient/Release)
ADD_SUBDIRECTORY(pwglobalsrv pwglobalsrv/Release)

endif()

ADD_SUBDIRECTORY(libcore libcore/Release)
ADD_SUBDIRECTORY(libutil libutil/Release)
ADD_SUBDIRECTORY(libg3dlite libg3dlite/Release)
ADD_SUBDIRECTORY(libdefs libdefs/Release)


ADD_SUBDIRECTORY(pwctrlsrv pwctrlsrv/Release)
ADD_SUBDIRECTORY(pwdbsrv pwdbsrv/Release)
ADD_SUBDIRECTORY(pwworldsrv pwworldsrv/Release)
ADD_SUBDIRECTORY(pwconnsrv pwconnsrv/Release)


if(NOT WIN32)
	message("linux project .0.")
	
	ADD_SUBDIRECTORY(pwgdbserver pwgdbserver/Release)
	ADD_SUBDIRECTORY(pwaccsrv pwaccsrv/Release)
	ADD_SUBDIRECTORY(pwconnsrv pwconnsrv/Release)
	
endif()
