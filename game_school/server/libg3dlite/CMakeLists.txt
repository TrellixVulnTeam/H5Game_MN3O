# g3dlite library

if(WIN32)
	# header files
	FILE(GLOB_RECURSE HEARDER_LIST . "*.h")
else()
	PROJECT(g3dlite)

	ADD_DEFINITIONS("-g --std=c++0x")
	ADD_DEFINITIONS("-DTBB_PREVIEW_CONCURRENT_PRIORITY_QUEUE")
endif()

# include directories
INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(./include)
INCLUDE_DIRECTORIES(${DEPS_ZLIB})

# source files
AUX_SOURCE_DIRECTORY(./src SRC_LIST)

if(WIN32)
	# ignore files
	SET(IGNORE_LIST 
		"./src/GImage.cpp"
		"./src/GImage_png.cpp"
		"./src/GImage_jpeg.cpp"
		)
	list(REMOVE_ITEM SRC_LIST ${IGNORE_LIST})
endif()
	
# build library
ADD_LIBRARY(g3dlite STATIC
	${HEARDER_LIST}
	${SRC_LIST}
	)
	
if(WIN32)
	# vs propertites
	SET_TARGET_PROPERTIES(g3dlite
		PROPERTIES
		COMPILE_FLAGS "/wd4996"
		FOLDER "libs"
	)
else()
	# makefile propertites
endif()

