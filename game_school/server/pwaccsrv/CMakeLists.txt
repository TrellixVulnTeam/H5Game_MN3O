if(WIN32)

# header files
FILE(GLOB_RECURSE HEARDER_LIST . "*.h")

# source_group
SOURCE_GROUP("dist_impl" REGULAR_EXPRESSION dist_impl)
SOURCE_GROUP("msg" REGULAR_EXPRESSION msg)
SOURCE_GROUP("auth" REGULAR_EXPRESSION auth)

else()
	
PROJECT(pwaccsrv)
ADD_DEFINITIONS("-g --std=c++0x -O3 -msse2 -mmmx -mfpmath=sse")
#ADD_DEFINITIONS("-g --std=c++0x -msse2 -mmmx -mfpmath=sse")
ADD_DEFINITIONS("-DTBB_PREVIEW_CONCURRENT_PRIORITY_QUEUE")

endif()

AUX_SOURCE_DIRECTORY(./ SRC)
AUX_SOURCE_DIRECTORY(./dist_impl SRC_DIST_IMPL)
AUX_SOURCE_DIRECTORY(./msg SRC_MSG)

SET(SRC_DIST_IMPL
	"./dist_impl/pw_rpcs_impl_simplacc.cpp"
	"./dist_impl/pw_rpcs_impl_simplwallow.cpp"
)
SET(SRC_COMMON "../libutil/pw_utils.cpp")
SET(SRC_SHARED_MSG "../../shared/pwmsg/options.pb.cc")

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

INCLUDE_DIRECTORIES("./")
INCLUDE_DIRECTORIES("./dist_impl")
INCLUDE_DIRECTORIES("./msg")

INCLUDE_DIRECTORIES("../libutil")
INCLUDE_DIRECTORIES("../libdefs")
INCLUDE_DIRECTORIES("../libcore/inc")
INCLUDE_DIRECTORIES("../libcore/cache")
INCLUDE_DIRECTORIES("../libg3dlite/include")
INCLUDE_DIRECTORIES("../../shared/pwmsg")

LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libutil/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libcore/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libg3dlite/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libdefs/Release")

ADD_EXECUTABLE(pwaccsrv 
	${SRC} ${SRC_MSG}
	${SRC_DIST_IMPL}
	${SRC_COMMON}
	${SRC_SHARED_MSG}
	${HEARDER_LIST}
	)

	
ADD_DEPENDENCIES(pwaccsrv core util defs)
	
if(WIN32)

TARGET_LINK_LIBRARIES(pwaccsrv libexpat libzmq ACEd tbb log4cplus libmysql.lib pthreadVC2 libprotobuf lua51 libcurl_imp ssleay32 libeay32 UnitTest++.vsnet2005 libiconv)
TARGET_LINK_LIBRARIES(pwaccsrv core util g3dlite defs)

SET_TARGET_PROPERTIES(pwaccsrv
		PROPERTIES
		COMPILE_FLAGS "/wd4996"
	)

else()
	
TARGET_LINK_LIBRARIES(pwaccsrv core defs util)
TARGET_LINK_LIBRARIES(pwaccsrv expat zmq ACE tbb log4cplus pthread mysqlclient protobuf g3dlite lua5.1 ssl)
TARGET_LINK_LIBRARIES(pwaccsrv tcmalloc_minimal)

endif()

