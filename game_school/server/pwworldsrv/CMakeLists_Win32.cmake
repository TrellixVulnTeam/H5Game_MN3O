# windows cmake

FILE(GLOB_RECURSE CMAKE_LIST . "*.cmake")

# header files
FILE(GLOB_RECURSE HEARDER_LIST . "*.h")

# source files
AUX_SOURCE_DIRECTORY(./ SRC)
AUX_SOURCE_DIRECTORY(./dist_impl SRC_DIST_IMPL)
AUX_SOURCE_DIRECTORY(./msg SRC_MSG)
AUX_SOURCE_DIRECTORY(./msg/process_proto SRC_MSG_PROTO)
AUX_SOURCE_DIRECTORY(./human SRC_HUMAN)


SET(SRC_SHARED_MSG "../../shared/pwmsg/options.pb.cc" "../pwaccsrv/msg/accsrv.pb.cc")
	
# 过滤文件

SET(IGNORE_DIST_IMPL 
	"./dist_impl/pw_rpcs_impl_base.cpp"
	"./dist_impl/pw_rpcs_impl_simplsupport.cpp"
	)
list(REMOVE_ITEM SRC_DIST_IMPL ${IGNORE_DIST_IMPL})

# SET(IGNORE_SRC_CONF
	# )
# list(REMOVE_ITEM SRC_CONF ${IGNORE_SRC_CONF})

# ignore files
# SET(IGNORE_LIST 
	# "./pw_msg_export_pwaccsrv.cpp"
	# )
	
# list(REMOVE_ITEM SRC_LIST ${IGNORE_LIST})

# source_group
SOURCE_GROUP("dist_impl" REGULAR_EXPRESSION /dist_impl)
SOURCE_GROUP("hmodules" REGULAR_EXPRESSION /hmodules)
SOURCE_GROUP("msg" REGULAR_EXPRESSION /msg)
SOURCE_GROUP("human" REGULAR_EXPRESSION /human)


SOURCE_GROUP("characters" REGULAR_EXPRESSION /characters)


# include directories
INCLUDE_DIRECTORIES(
	${DEPS_PTHREAD}
	${DEPS_TBB}
	${DEPS_EXPAT}
	${DEPS_CURL}
	${DEPS_LOG4CPLUS}
	${DEPS_OPENSSL}
	${DEPS_ZEROMQ}
	${DEPS_LUA51}
	${DEPS_LUA51Ex}
	${DEPS_LIBICONV}
	${DEPS_ACE}
	${DEPS_PROTOBUF}
	${DEPS_MYSQL}
	${DEPS_VLD}
	${DEPS_UNITTEST}
	${DEPS_BULLETPHYSICS}
	)

INCLUDE_DIRECTORIES(
	"./"
	"./dist_impl"
	"./msg"
	"./msg/process_proto"
	"./human"
	)
	
INCLUDE_DIRECTORIES(
	"../libutil"
	"../libdefs"
	"../libcore/inc"
	"../libcore/cache"
	"../libg3dlite/include"
	"../../shared/pwmsg"
	)


# build exe
ADD_EXECUTABLE(pwworldsrv
	${CMAKE_LIST}
	${HEARDER_LIST}
	${SRC}
    ${SRC_MSG}
    ${SRC_MSG_PROTO}
    ${SRC_DIST_IMPL}
	${SRC_SHARED_MSG}
	${SRC_HUMAN}
	)

ADD_DEPENDENCIES(pwworldsrv core util g3dlite defs)
	
TARGET_LINK_LIBRARIES(pwworldsrv libexpat libzmq ACEd tbb log4cplus libmysql.lib pthreadVC2)
TARGET_LINK_LIBRARIES(pwworldsrv libprotobuf lua51 libcurl_imp ssleay32 libeay32 UnitTest++.vsnet2005 libiconv)
TARGET_LINK_LIBRARIES(pwworldsrv BulletCollision_vs2008_debug BulletDynamics_vs2008_debug LinearMath_vs2008_debug libtcmalloc_minimal)
TARGET_LINK_LIBRARIES(pwworldsrv core util g3dlite defs)

SET_TARGET_PROPERTIES(pwworldsrv
		PROPERTIES
		COMPILE_FLAGS "/wd4996"
	)




	