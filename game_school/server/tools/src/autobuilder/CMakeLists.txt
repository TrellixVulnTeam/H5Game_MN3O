PROJECT(autobuilder)

AUX_SOURCE_DIRECTORY(./ SRC)

ADD_DEFINITIONS("-g --std=c++0x -O3 -msse2 -mmmx -mfpmath=sse")

INCLUDE_DIRECTORIES("./")

ADD_EXECUTABLE(autobuilder ${SRC})
