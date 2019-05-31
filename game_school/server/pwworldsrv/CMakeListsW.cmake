PROJECT(pwworldsrv)

#ADD_DEFINITIONS("-D_Gperf_HeapProfile_ -D_Gperf_HeapCheck_")
#ADD_DEFINITIONS("-D_Gperf_HeapCheck_")

AUX_SOURCE_DIRECTORY(./ SRC)
AUX_SOURCE_DIRECTORY(./dist_impl SRC_DIST_IMPL)
AUX_SOURCE_DIRECTORY(./msg SRC_MSG)
AUX_SOURCE_DIRECTORY(./msg/process_proto SRC_MSG_PROTO)
AUX_SOURCE_DIRECTORY(./human SRC_HUMAN)

SET(SRC_SHARED_MSG "../../shared/pwmsg/options.pb.cc" "../pwaccsrv/msg/accsrv.pb.cc")


INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/include.cmake)

INCLUDE_DIRECTORIES("/usr/local/include/bullet")

LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libutil/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libcore/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libg3dlite/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libdefs/Release")

ADD_EXECUTABLE(pwworldsrv 
	${SRC}
    ${SRC_MSG}
    ${SRC_MSG_PROTO}
    ${SRC_DIST_IMPL}
	${SRC_SHARED_MSG}
	${SRC_HUMAN}
	)

ADD_DEPENDENCIES(pwworldsrv core util g3dlite defs)
TARGET_LINK_LIBRARIES(pwworldsrv core defs util g3dlite)
TARGET_LINK_LIBRARIES(pwworldsrv expat zmq ACE tbb log4cplus pthread mysqlclient protobuf lua5.1 ssl curl)
#TARGET_LINK_LIBRARIES(pwworldsrv BulletSoftBody_gmake_x64_release BulletDynamics_gmake_x64_release BulletCollision_gmake_x64_release LinearMath_gmake_x64_release)
TARGET_LINK_LIBRARIES(pwworldsrv BulletCollision BulletDynamics BulletSoftBody LinearMath)
TARGET_LINK_LIBRARIES(pwworldsrv unittest++)
TARGET_LINK_LIBRARIES(pwworldsrv tcmalloc_minimal)
#TARGET_LINK_LIBRARIES(pwworldsrv tcmalloc_and_profiler)