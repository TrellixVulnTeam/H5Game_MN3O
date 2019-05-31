PROJECT(pwgdbserver)
AUX_SOURCE_DIRECTORY(. SRC_LIST)

ADD_DEFINITIONS("-D_TCMALLOC_USED")
ADD_DEFINITIONS("-g --std=c++0x  -O3 -msse2 -mmmx -mfpmath=sse")
#ADD_DEFINITIONS("-g --std=c++0x")

INCLUDE_DIRECTORIES("./")
INCLUDE_DIRECTORIES("../libutil")
INCLUDE_DIRECTORIES("../libutil/kvdb")
INCLUDE_DIRECTORIES("../libutil/gdb")

LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libutil/Release")

ADD_EXECUTABLE(pwgdbserver ${SRC_LIST})
ADD_DEPENDENCIES(pwgdbserver util)
TARGET_LINK_LIBRARIES(pwgdbserver util leveldb log4cplus tbb lua5.1 log4cplus)
TARGET_LINK_LIBRARIES(pwgdbserver tcmalloc_minimal)