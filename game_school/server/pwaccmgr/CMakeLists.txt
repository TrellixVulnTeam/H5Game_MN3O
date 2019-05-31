PROJECT(pwaccmgr)

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
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libg3dlite/Release")

ADD_EXECUTABLE(pwaccmgr ${SRC})

ADD_DEPENDENCIES(pwaccmgr util core defs)
TARGET_LINK_LIBRARIES(pwaccmgr core defs util)
TARGET_LINK_LIBRARIES(pwaccmgr mysqlclient rt log4cplus)
TARGET_LINK_LIBRARIES(pwaccmgr tcmalloc_minimal)




