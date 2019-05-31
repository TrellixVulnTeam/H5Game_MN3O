if(WIN32)

# header files
FILE(GLOB_RECURSE HEARDER_LIST . "*.h")

# source_group
SOURCE_GROUP("dist_impl" REGULAR_EXPRESSION dist_impl)

else()
	
PROJECT(pwconnsrv)
ADD_DEFINITIONS("-g --std=c++0x -O3 -msse2 -mmmx -mfpmath=sse")
ADD_DEFINITIONS("-DTBB_PREVIEW_CONCURRENT_PRIORITY_QUEUE")

endif()

# source files
AUX_SOURCE_DIRECTORY(./ SRC)
SET(SRC_DIST_IMPL
	"./dist_impl/pw_rpcs_impl_connection.cpp"
	"./dist_impl/pw_rpcs_impl_simpllistener.cpp"
	"./dist_impl/pw_rpcs_impl_simplsend.cpp"
)

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
INCLUDE_DIRECTORIES("../libutil")
INCLUDE_DIRECTORIES("../libdefs")
INCLUDE_DIRECTORIES("../libcore/inc")
INCLUDE_DIRECTORIES("../libcore/cache")
INCLUDE_DIRECTORIES("../libg3dlite/include")
INCLUDE_DIRECTORIES("../../shared/pwmsg")

LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libutil/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libcore/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libg3dlite/Release")

ADD_EXECUTABLE(pwconnsrv 
	${SRC} 
	${SRC_DIST_IMPL}
	${HEARDER_LIST}
	)

ADD_DEPENDENCIES(pwconnsrv core util defs)

if(WIN32)

TARGET_LINK_LIBRARIES(pwconnsrv libexpat libzmq ACEd tbb log4cplus libmysql.lib pthreadVC2 libprotobuf lua51 libcurl_imp ssleay32 libeay32 UnitTest++.vsnet2005 libiconv)
TARGET_LINK_LIBRARIES(pwconnsrv core util g3dlite defs)

SET_TARGET_PROPERTIES(pwconnsrv
		PROPERTIES
		COMPILE_FLAGS "/wd4996"
	)

else()
	
TARGET_LINK_LIBRARIES(pwconnsrv core defs util)
TARGET_LINK_LIBRARIES(pwconnsrv expat zmq ACE tbb log4cplus pthread mysqlclient protobuf g3dlite lua5.1 iconv)
TARGET_LINK_LIBRARIES(pwconnsrv tcmalloc_minimal)

endif()







