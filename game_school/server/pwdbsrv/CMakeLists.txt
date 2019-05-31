if(WIN32)

	# header files
	FILE(GLOB_RECURSE HEARDER_LIST . "*.h")

else()

	PROJECT(pwdbsrv)

	ADD_DEFINITIONS("-g --std=c++0x -O3 -msse2 -mmmx -mfpmath=sse")
	ADD_DEFINITIONS("-DTBB_PREVIEW_CONCURRENT_PRIORITY_QUEUE")

endif()

# source files
AUX_SOURCE_DIRECTORY(./ SRC)

SET(SRC_DIST_IMPL
	"./dist_impl/pw_rpcs_impl_simplkvdb.cpp"
	"./dist_impl/pw_rpcs_impl_simplkvdbloader.cpp"
	)


if(WIN32)

	# source_group
	SOURCE_GROUP("dist_impl" REGULAR_EXPRESSION dist_impl)
	SOURCE_GROUP("kvsrv" REGULAR_EXPRESSION dbsrv_kv)

endif()

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
	${DEPS_LIBICONV}
	${DEPS_ACE}
	${DEPS_PROTOBUF}
	${DEPS_MYSQL}
	${DEPS_VLD}
	${DEPS_UNITTEST}
	)

INCLUDE_DIRECTORIES(
	"./"
	"./dist_impl"
	"../libutil"
	"../libdefs"
	"../libcore/inc"
	"../libcore/cache"
	"../libg3dlite/include"
	"../../shared/pwmsg"
	)

LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libutil/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libcore/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libg3dlite/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libdefs/Release")

ADD_EXECUTABLE(pwdbsrv 
		${HEARDER_LIST}
		${SRC}
		${SRC_DIST_IMPL}
		)

ADD_DEPENDENCIES(pwdbsrv core util g3dlite defs)

if(WIN32)

	TARGET_LINK_LIBRARIES(pwdbsrv libexpat libzmq ACEd tbb log4cplus libmysql.lib pthreadVC2 libprotobuf lua51 libcurl_imp ssleay32 libeay32 UnitTest++.vsnet2005 libiconv)
	TARGET_LINK_LIBRARIES(pwdbsrv core util g3dlite defs)

	SET_TARGET_PROPERTIES(pwdbsrv
			PROPERTIES
			COMPILE_FLAGS "/wd4996"
	)

else()

	TARGET_LINK_LIBRARIES(pwdbsrv core defs g3dlite util)
	TARGET_LINK_LIBRARIES(pwdbsrv expat zmq ACE tbb log4cplus pthread mysqlclient protobuf lua5.1)
	TARGET_LINK_LIBRARIES(pwdbsrv tcmalloc_minimal)

endif()