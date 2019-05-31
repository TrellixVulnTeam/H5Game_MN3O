PROJECT(pwclientlog)

AUX_SOURCE_DIRECTORY(./ SRC)

ADD_DEFINITIONS("-g --std=c++0x -O3 -msse2 -mmmx -mfpmath=sse")
ADD_DEFINITIONS("-DTBB_PREVIEW_CONCURRENT_PRIORITY_QUEUE")

INCLUDE_DIRECTORIES("./")

INCLUDE_DIRECTORIES("../libutil")
INCLUDE_DIRECTORIES("../libdefs")
INCLUDE_DIRECTORIES("../libcore/inc")
INCLUDE_DIRECTORIES("../libcore/cache")
INCLUDE_DIRECTORIES("../libg3dlite/include")

LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libutil/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libcore/Release")

ADD_EXECUTABLE(pwclientlog ${SRC})

ADD_DEPENDENCIES(pwclientlog util core)
TARGET_LINK_LIBRARIES(pwclientlog core util)
TARGET_LINK_LIBRARIES(pwclientlog mysqlclient ACE log4cplus protobuf g3dlite tbb log4cplus lua5.1)
TARGET_LINK_LIBRARIES(pwclientlog tcmalloc_minimal)




