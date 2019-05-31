if(WIN32)

# header files
FILE(GLOB_RECURSE HEARDER_LIST . "*.h")

# source_group
SOURCE_GROUP("dist_impl" REGULAR_EXPRESSION dist_impl)

else()
	
PROJECT(pwnrobot)
ADD_DEFINITIONS("-g --std=c++0x -O3 -msse2 -mmmx -mfpmath=sse")
ADD_DEFINITIONS("-DTBB_PREVIEW_CONCURRENT_PRIORITY_QUEUE")

endif()


AUX_SOURCE_DIRECTORY(./ SRC)
AUX_SOURCE_DIRECTORY(../pwworldsrv/msg/process_proto SRC_MSG_PROTO)

SET(SRC_SHARED_MSG "../../shared/pwmsg/options.pb.cc" "../pwaccsrv/msg/accsrv.pb.cc")

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

INCLUDE_DIRECTORIES("../libutil")
INCLUDE_DIRECTORIES("../libdefs")
INCLUDE_DIRECTORIES("../libcore/inc")
INCLUDE_DIRECTORIES("../libg3dlite/include")
INCLUDE_DIRECTORIES("../pwworldsrv/msg")
INCLUDE_DIRECTORIES("../pwworldsrv/msg/process_proto")

INCLUDE_DIRECTORIES("../../shared/pwmsg")

LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libutil/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libcore/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libg3dlite/Release")

ADD_EXECUTABLE(pwnrobot 
	${SRC} ${SRC_SHARED_MSG} ${SRC_MSG_PROTO})

if(WIN32)

TARGET_LINK_LIBRARIES(pwnrobot ACEd tbb log4cplus lua51 libprotobuf pthreadVC2 UnitTest++.vsnet2005 libiconv)
TARGET_LINK_LIBRARIES(pwnrobot util g3dlite)

SET_TARGET_PROPERTIES(pwnrobot
		PROPERTIES
		COMPILE_FLAGS "/wd4996"
	)

else()

ADD_DEPENDENCIES(pwnrobot util)

TARGET_LINK_LIBRARIES(pwnrobot util)
TARGET_LINK_LIBRARIES(pwnrobot ACE log4cplus protobuf g3dlite tbb log4cplus lua5.1)
TARGET_LINK_LIBRARIES(pwnrobot tcmalloc_minimal)

endif()



