if(WIN32)

INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists_Win32.cmake)

else()

PROJECT(pwglobalsrv)

AUX_SOURCE_DIRECTORY(./ SRC)
AUX_SOURCE_DIRECTORY(./dist_impl SRC_DIST_IMPL)

SET(SRC_COMMON "../common/pw_utils.cpp")

ADD_DEFINITIONS("-g --std=c++0x -O3 -msse2 -mmmx -mfpmath=sse")
ADD_DEFINITIONS("-DTBB_PREVIEW_CONCURRENT_PRIORITY_QUEUE")

INCLUDE_DIRECTORIES("./")
INCLUDE_DIRECTORIES("./dist_impl")

INCLUDE_DIRECTORIES("../libutil")
INCLUDE_DIRECTORIES("../libdefs")
INCLUDE_DIRECTORIES("../libcore/inc")
INCLUDE_DIRECTORIES("../libcore/cache")
INCLUDE_DIRECTORIES("../libg3dlite/include")

LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libutil/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libcore/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libdefs/Release")

ADD_EXECUTABLE(pwglobalsrv ${SRC} ${SRC_DIST_IMPL})

ADD_DEPENDENCIES(pwglobalsrv core util defs)
TARGET_LINK_LIBRARIES(pwglobalsrv core defs util)
TARGET_LINK_LIBRARIES(pwglobalsrv expat zmq ACE tbb log4cplus pthread mysqlclient protobuf lua5.1 ssl)
TARGET_LINK_LIBRARIES(pwglobalsrv tcmalloc_minimal)

endif()