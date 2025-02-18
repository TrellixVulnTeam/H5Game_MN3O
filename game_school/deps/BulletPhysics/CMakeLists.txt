cmake_minimum_required(VERSION 2.4.3)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

#this line has to appear before 'PROJECT' in order to be able to disable incremental linking
SET(MSVC_INCREMENTAL_DEFAULT ON)

PROJECT(BULLET_PHYSICS)
SET(BULLET_VERSION 2.81)

IF(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)


IF (NOT CMAKE_BUILD_TYPE)
# SET(CMAKE_BUILD_TYPE "Debug")
 SET(CMAKE_BUILD_TYPE "Release")
ENDIF (NOT CMAKE_BUILD_TYPE) 

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
#MESSAGE("CMAKE_CXX_FLAGS_DEBUG="+${CMAKE_CXX_FLAGS_DEBUG})

OPTION(USE_DOUBLE_PRECISION "Use double precision"	OFF)
OPTION(USE_GRAPHICAL_BENCHMARK "Use Graphical Benchmark" ON)
OPTION(USE_MULTITHREADED_BENCHMARK "Use Multithreaded Benchmark" OFF)

IF (USE_MULTITHREADED_BENCHMARK)
	ADD_DEFINITIONS(-DUSE_PARALLEL_SOLVER_BENCHMARK -DUSE_PARALLEL_DISPATCHER_BENCHMARK)
ENDIF()

OPTION(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC Runtime Library DLL (/MD or /MDd)" OFF)
OPTION(USE_MSVC_INCREMENTAL_LINKING "Use MSVC Incremental Linking" OFF)

OPTION(USE_CUSTOM_VECTOR_MATH "Use custom vectormath library" OFF)

IF (USE_CUSTOM_VECTOR_MATH)
	ADD_DEFINITIONS(-DUSE_SYSTEM_VECTORMATH)
	IF(WIN32)
	SET (VECTOR_MATH_INCLUDE ${BULLET_PHYSICS_SOURCE_DIR}/src/vectormath/sse CACHE PATH "Vector Math library include path.")
	ELSE(WIN32)
	SET (VECTOR_MATH_INCLUDE ${BULLET_PHYSICS_SOURCE_DIR}/src/vectormath/scalar CACHE PATH "Vector Math library include path.")
	ENDIF(WIN32)
ENDIF(USE_CUSTOM_VECTOR_MATH)

IF (MSVC)
	FIND_PATH(DIRECTX_SDK_BASE_DIR Include/D3D11.h PATH  $ENV{DXSDK_DIR} )
	IF(DIRECTX_SDK_BASE_DIR)
		OPTION(USE_DX11 "Use DirectX 11"	ON)
	ELSE()
		OPTION(USE_DX11 "Use DirectX 11"	OFF)
	ENDIF()
ENDIF(MSVC)


#SET(CMAKE_EXE_LINKER_FLAGS_INIT    "/STACK:10000000 /INCREMENTAL:NO")	
#SET(CMAKE_EXE_LINKER_FLAGS    "/STACK:10000000 /INCREMENTAL:NO")	

#MESSAGE("MSVC_INCREMENTAL_YES_FLAG"+${MSVC_INCREMENTAL_YES_FLAG})


IF(MSVC)
	IF (NOT USE_MSVC_INCREMENTAL_LINKING)
		#MESSAGE("MSVC_INCREMENTAL_DEFAULT"+${MSVC_INCREMENTAL_DEFAULT})
		SET( MSVC_INCREMENTAL_YES_FLAG "/INCREMENTAL:NO")
		 
		STRING(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replacementFlags ${CMAKE_EXE_LINKER_FLAGS_DEBUG}) 
		SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "/INCREMENTAL:NO ${replacementFlags}" )
		MESSAGE("CMAKE_EXE_LINKER_FLAGS_DEBUG=${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
	
#		STRING(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replacementFlags2 ${CMAKE_EXE_LINKER_FLAGS}) 
#		SET(CMAKE_EXE_LINKER_FLAGS ${replacementFlag2}) 
#		STRING(REPLACE "INCREMENTAL:YES" "" replacementFlags3 ${CMAKE_EXTRA_LINK_FLAGS}) 
#		SET(CMAKE_EXTRA_LINK_FLAGS ${replacementFlag3}) 
		
		
		STRING(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replacementFlags3 ${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO})
		SET(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO ${replacementFlags3}) 
		SET(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/INCREMENTAL:NO ${replacementFlags3}" )
	
	ENDIF (NOT USE_MSVC_INCREMENTAL_LINKING)

	IF (NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
		#We statically link to reduce dependancies
		FOREACH(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
			IF(${flag_var} MATCHES "/MD")
				STRING(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
			ENDIF(${flag_var} MATCHES "/MD")
			IF(${flag_var} MATCHES "/MDd")
				STRING(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
			ENDIF(${flag_var} MATCHES "/MDd")
		ENDFOREACH(flag_var)
	ENDIF (NOT USE_MSVC_RUNTIME_LIBRARY_DLL)

	OPTION(USE_MSVC_SSE "Use MSVC /arch:sse option"	ON)
	IF (USE_MSVC_SSE)
		ADD_DEFINITIONS(/arch:SSE)
	ENDIF()
	OPTION(USE_MSVC_FAST_FLOATINGPOINT "Use MSVC /fp:fast option"	ON)
	IF (USE_MSVC_FAST_FLOATINGPOINT)
		ADD_DEFINITIONS(/fp:fast)
  ENDIF()
ENDIF(MSVC)



IF (WIN32)
OPTION(INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES "Create MSVC projectfiles that can be distributed" OFF)

IF (INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
	SET (LIBRARY_OUTPUT_PATH ${BULLET_PHYSICS_SOURCE_DIR}/lib CACHE PATH "Single output directory for building all libraries.")
	SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BULLET_PHYSICS_SOURCE_DIR})
	SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BULLET_PHYSICS_SOURCE_DIR})
	SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BULLET_PHYSICS_SOURCE_DIR})
	SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${BULLET_PHYSICS_SOURCE_DIR})
	SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${BULLET_PHYSICS_SOURCE_DIR})
ELSE()
	SET (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE PATH "Single output directory for building all libraries.")
ENDIF()



OPTION(INTERNAL_CREATE_MSVC_RELATIVE_PATH_PROJECTFILES "Create MSVC projectfiles with relative paths" OFF)
OPTION(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES "Add MSVC postfix for executable names (_Debug)" OFF)

SET(CMAKE_DEBUG_POSTFIX "_Debug" CACHE STRING "Adds a postfix for debug-built libraries.")
SET(CMAKE_MINSIZEREL_POSTFIX "_MinsizeRel" CACHE STRING "Adds a postfix for MinsizeRelease-built libraries.")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo" CACHE STRING "Adds a postfix for ReleaseWithDebug-built libraries.")



IF(MSVC)
	FIND_PATH(AMD_OPENCL_BASE_DIR include/CL/cl.h PATH  $ENV{ATISTREAMSDKROOT} $ENV{AMDAPPSDKROOT} )
	IF(AMD_OPENCL_BASE_DIR)
		#AMD adds an extras slash at the end of the ATISTREAMSDKROOT variable
		SET(AMD_OPENCL_INCLUDES ${AMD_OPENCL_BASE_DIR}/include )
		MESSAGE("AMD OPENCL SDK FOUND")
		IF (CMAKE_CL_64)
			SET(CMAKE_ATISTREAMSDK_LIBPATH 		${AMD_OPENCL_BASE_DIR}/lib/x86_64 )
		ELSE(CMAKE_CL_64)
			SET(CMAKE_ATISTREAMSDK_LIBPATH		${AMD_OPENCL_BASE_DIR}/lib/x86 )
		ENDIF(CMAKE_CL_64)
		SET(CMAKE_ATISTREAMSDK_LIBRARY		${CMAKE_ATISTREAMSDK_LIBPATH}/OpenCL.lib )
		OPTION(BUILD_AMD_OPENCL_DEMOS "Build OpenCL demos for AMD (GPU or CPU)"	ON)
		IF (CMAKE_CL_64)
			SET(CMAK_GLEW_LIBRARY
				${BULLET_PHYSICS_SOURCE_DIR}/Glut/glew64s.lib		)
		ELSE(CMAKE_CL_64)
			SET(CMAK_GLEW_LIBRARY		${BULLET_PHYSICS_SOURCE_DIR}/Glut/glew32s.lib		)
		ENDIF(CMAKE_CL_64)
	ELSE()
		OPTION(BUILD_AMD_OPENCL_DEMOS "Build OpenCL demos for AMD (GPU or CPU)"	OFF)
	ENDIF()
	
	FIND_PATH(INTEL_OPENCL_BASE_DIR include/CL/cl.h PATH  $ENV{INTELOCLSDKROOT} )
	IF(INTEL_OPENCL_BASE_DIR)
		SET(INTEL_OPENCL_INCLUDES ${INTEL_OPENCL_BASE_DIR}/include )
		MESSAGE("INTEL OPENCL SDK FOUND")
		MESSAGE(${INTEL_OPENCL_INCLUDES})
		IF (CMAKE_CL_64)
			SET(CMAKE_INTELOCLSDK_LIBPATH 		${INTEL_OPENCL_BASE_DIR}/lib/x64 )
		ELSE(CMAKE_CL_64)
			SET(CMAKE_INTELOCLSDK_LIBPATH		${INTEL_OPENCL_BASE_DIR}/lib/x86 )
		ENDIF(CMAKE_CL_64)
		SET(INTEL_OPENCL_LIBRARIES ${CMAKE_INTELOCLSDK_LIBPATH}/OpenCL.lib)
		OPTION(BUILD_INTEL_OPENCL_DEMOS "Build OpenCL demos for Intel (CPU)"	ON)
	ELSE()
		OPTION(BUILD_INTEL_OPENCL_DEMOS "Build OpenCL demos for Intel (CPU)"	OFF)
	ENDIF()
	
	FIND_PATH(NVIDIA_OPENCL_BASE_DIR include/CL/cl.h PATH  $ENV{CUDA_PATH} )
	IF(NVIDIA_OPENCL_BASE_DIR)
		SET(NVIDIA_OPENCL_INCLUDES ${NVIDIA_OPENCL_BASE_DIR}/include )
		MESSAGE("NVIDIA OPENCL SDK FOUND")
		MESSAGE(${NVIDIA_OPENCL_INCLUDES})
		IF (CMAKE_CL_64)
			SET(CMAKE_NVSDKCOMPUTE_LIBPATH		${NVIDIA_OPENCL_BASE_DIR}/lib/x64 )
		ELSE(CMAKE_CL_64)
			SET(CMAKE_NVSDKCOMPUTE_LIBPATH		${NVIDIA_OPENCL_BASE_DIR}/lib/Win32	)
		ENDIF(CMAKE_CL_64)
	SET(NVIDIA_OPENCL_LIBRARIES		${CMAKE_NVSDKCOMPUTE_LIBPATH}/OpenCL.lib)
	
		OPTION(BUILD_NVIDIA_OPENCL_DEMOS "Build OpenCL demos for NVidia (GPU)"	ON)
	ELSE()
		OPTION(BUILD_NVIDIA_OPENCL_DEMOS "Build OpenCL demos for NVidia (GPU)"	OFF)
	ENDIF()
ENDIF()



IF (INTERNAL_CREATE_MSVC_RELATIVE_PATH_PROJECTFILES)
SET(CMAKE_SUPPRESS_REGENERATION  1)
SET(CMAKE_USE_RELATIVE_PATHS 1)
ENDIF(INTERNAL_CREATE_MSVC_RELATIVE_PATH_PROJECTFILES)

ENDIF (WIN32)

IF (MSVC OR APPLE)
	OPTION(BUILD_MINICL_OPENCL_DEMOS "Build OpenCL demos for MiniCL (Generic CPU)"  ON)
ELSE()
	OPTION(BUILD_MINICL_OPENCL_DEMOS "Build OpenCL demos for MiniCL (Generic CPU)" OFF)
	
	FIND_PATH(AMD_OPENCL_BASE_DIR include/CL/cl.h PATH  $ENV{ATISTREAMSDKROOT} $ENV{AMDAPPSDKROOT} )
	IF(AMD_OPENCL_BASE_DIR)
		#AMD adds an extras slash at the end of the ATISTREAMSDKROOT variable
		SET(AMD_OPENCL_INCLUDES ${AMD_OPENCL_BASE_DIR}/include )
		MESSAGE("AMD OPENCL SDK FOUND")
		MESSAGE(${AMD_OPENCL_INCLUDES})
		IF (CMAKE_CL_64)
			SET(CMAKE_ATISTREAMSDK_LIBPATH 		${AMD_OPENCL_BASE_DIR}/lib/x86_64 )
		ELSE(CMAKE_CL_64)
			SET(CMAKE_ATISTREAMSDK_LIBPATH		${AMD_OPENCL_BASE_DIR}/lib/x86 )
		ENDIF(CMAKE_CL_64)
		OPTION(BUILD_AMD_OPENCL_DEMOS "Build OpenCL demos for AMD (GPU or CPU)"	ON)
		SET(CMAKE_ATISTREAMSDK_LIBRARY		OpenCL )
	ELSE()
		OPTION(BUILD_AMD_OPENCL_DEMOS "Build OpenCL demos for AMD (GPU or CPU)"	OFF)
	ENDIF()
		
        FIND_PATH(INTEL_OPENCL_INCLUDES CL/cl.h)
        FIND_PATH(INTEL_OPENCL_ICD_CFG intelocl64.icd /etc/OpenCL/vendors)
        FIND_LIBRARY(INTEL_OPENCL_LIBRARIES OpenCL PATH /usr/lib64)
        IF (INTEL_OPENCL_INCLUDES AND INTEL_OPENCL_LIBRARIES AND INTEL_OPENCL_ICD_CFG)
                MESSAGE("INTEL OPENCL SDK FOUND")
                MESSAGE(${INTEL_OPENCL_LIBRARIES})
                OPTION(BUILD_INTEL_OPENCL_DEMOS "Build OpenCL demos for Intel (CPU)"        ON)
        ELSE ()
                MESSAGE("INTEL OPENCL NOT FOUND")
                OPTION(BUILD_INTEL_OPENCL_DEMOS "Build OpenCL demos for Intel (CPU)"        OFF)
        ENDIF ()

	FIND_PATH(NVIDIA_OPENCL_INCLUDES CL/cl.h)
        FIND_PATH(NVIDIA_OPENCL_ICD_CFG nvidia.icd /etc/OpenCL/vendors)
        FIND_LIBRARY(NVIDIA_OPENCL_LIBRARIES OpenCL PATH /usr/lib64 /usr/local/lib)
        IF (NVIDIA_OPENCL_INCLUDES AND NVIDIA_OPENCL_LIBRARIES AND NVIDIA_OPENCL_ICD_CFG)
                MESSAGE("NVidia OPENCL FOUND")
		MESSAGE(${NVIDIA_OPENCL_LIBRARIES})
		OPTION(BUILD_NVIDIA_OPENCL_DEMOS "Build OpenCL demos for NVidia (GPU)"	ON)
	ELSE ()
                MESSAGE("NVidia OPENCL NOT FOUND")
		OPTION(BUILD_NVIDIA_OPENCL_DEMOS "Build OpenCL demos for NVidia (GPU)"	OFF)
	ENDIF ()

ENDIF()

OPTION(BUILD_CPU_DEMOS "Build original Bullet CPU demos"        ON)



OPTION(INTERNAL_UPDATE_SERIALIZATION_STRUCTURES "Internal update serialization structures" OFF)
IF (INTERNAL_UPDATE_SERIALIZATION_STRUCTURES)
ADD_DEFINITIONS( -DBT_INTERNAL_UPDATE_SERIALIZATION_STRUCTURES)
ENDIF (INTERNAL_UPDATE_SERIALIZATION_STRUCTURES)

IF (USE_DOUBLE_PRECISION)
ADD_DEFINITIONS( -DBT_USE_DOUBLE_PRECISION)
SET( BULLET_DOUBLE_DEF "-DBT_USE_DOUBLE_PRECISION")
ENDIF (USE_DOUBLE_PRECISION)

IF(USE_GRAPHICAL_BENCHMARK)
ADD_DEFINITIONS( -DUSE_GRAPHICAL_BENCHMARK)
ENDIF (USE_GRAPHICAL_BENCHMARK)

IF (WIN32)
OPTION(USE_GLUT "Use Glut"	ON)
ADD_DEFINITIONS( -D_IRR_STATIC_LIB_ )
ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
ADD_DEFINITIONS( -D_CRT_SECURE_NO_DEPRECATE )
ADD_DEFINITIONS( -D_SCL_SECURE_NO_WARNINGS )

IF (USE_GLUT AND MSVC)
        string (REPLACE "/D_WINDOWS" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
        remove_definitions(-D_WINDOWS )
ENDIF()



ELSE(WIN32)
OPTION(USE_GLUT "Use Glut"	ON)
ENDIF(WIN32)

   
IF(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)
   

# This is the shortcut to finding GLU, GLUT and OpenGL if they are properly installed on your system
# This should be the case.

FIND_PACKAGE(OpenGL)
IF (OPENGL_FOUND)
	MESSAGE("OPENGL FOUND")
	MESSAGE(${OPENGL_LIBRARIES})
ELSE (OPENGL_FOUND)
	MESSAGE("OPENGL NOT FOUND")
	SET(OPENGL_gl_LIBRARY opengl32)
	SET(OPENGL_glu_LIBRARY glu32)
ENDIF (OPENGL_FOUND)

# ADD_DEFINITIONS(-DBT_USE_FREEGLUT)

FIND_PACKAGE(GLU)

IF (USE_GLUT)
	FIND_PACKAGE(GLUT)
	IF (GLUT_FOUND)
		MESSAGE("GLUT FOUND")
		MESSAGE(${GLUT_glut_LIBRARY})
	ELSE (GLUT_FOUND)
		IF (MINGW)
			MESSAGE ("GLUT NOT FOUND not found, trying to use MINGW glut32")
			SET(GLUT_glut_LIBRARY glut32)
			#TODO add better GLUT detection for MinGW
			SET(GLUT_FOUND TRUE)
		ENDIF (MINGW)
		IF (MSVC)
			SET(GLUT_FOUND TRUE)
			IF (CMAKE_CL_64)
				message("Win64 using Glut/glut64.lib")
				SET(GLUT_glut_LIBRARY ${BULLET_PHYSICS_SOURCE_DIR}/Glut/glut64.lib)
			ELSE(CMAKE_CL_64)
				message("Win32 using Glut/glut32.lib")
				SET(GLUT_glut_LIBRARY ${BULLET_PHYSICS_SOURCE_DIR}/Glut/glut32.lib)
			ENDIF (CMAKE_CL_64)
		 	INCLUDE_DIRECTORIES(${BULLET_PHYSICS_SOURCE_DIR}/Glut)
		ELSE()
			MESSAGE("GLUT NOT FOUND")	
		ENDIF (MSVC)
	ENDIF (GLUT_FOUND)

	IF(NOT WIN32)	
		# This is added for linux. This should always work if everything is installed and working fine.
		INCLUDE_DIRECTORIES(/usr/include /usr/local/include) 
	ENDIF()
ENDIF(USE_GLUT)


OPTION(BUILD_DEMOS "Set when you want to build the demos" ON)
IF(BUILD_DEMOS)
	IF(EXISTS ${BULLET_PHYSICS_SOURCE_DIR}/Demos AND IS_DIRECTORY ${BULLET_PHYSICS_SOURCE_DIR}/Demos)
		SUBDIRS(Demos)
	ENDIF()
ENDIF(BUILD_DEMOS)

#  "Demos_ps3")
IF (MSVC)
	IF (NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		IF(EXISTS ${BULLET_PHYSICS_SOURCE_DIR}/Demos_ps3 AND IS_DIRECTORY ${BULLET_PHYSICS_SOURCE_DIR}/Demos_ps3)
		MESSAGE("Demos_ps3 found")
			SUBDIRS(Demos_ps3)
		ENDIF()
	ENDIF()
ENDIF(MSVC)


OPTION(BUILD_EXTRAS "Set when you want to build the extras" ON)
IF(BUILD_EXTRAS)
  SUBDIRS(Extras)
ENDIF(BUILD_EXTRAS)

#Maya Dynamica plugin is moved to http://dynamica.googlecode.com

SUBDIRS(src)

IF("${CMAKE_GENERATOR}" MATCHES "Unix Makefiles")
	OPTION(INSTALL_LIBS "Set when you want to install libraries" ON)
ELSE()
	IF(APPLE AND FRAMEWORK)
		OPTION(INSTALL_LIBS "Set when you want to install libraries" ON)
	ELSE()
#by default, don't enable the 'INSTALL' option for Xcode and MSVC projectfiles
		OPTION(INSTALL_LIBS "Set when you want to install libraries" OFF)
	ENDIF()
ENDIF()

IF(INSTALL_LIBS)
	SET (LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
	SET (LIB_DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE STRING "Library directory name")
	## the following are directories where stuff will be installed to
	SET(INCLUDE_INSTALL_DIR      "${CMAKE_INSTALL_PREFIX}/include/bullet/" CACHE PATH "The subdirectory to the header prefix")
	SET(PKGCONFIG_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig/" CACHE STRING "Base directory for pkgconfig files")
	IF(NOT WIN32)
	  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/bullet.pc.cmake ${CMAKE_CURRENT_BINARY_DIR}/bullet.pc @ONLY)
  	INSTALL(
	    FILES
    	${CMAKE_CURRENT_BINARY_DIR}/bullet.pc
    	DESTINATION
    	${PKGCONFIG_INSTALL_PREFIX})
	ENDIF(NOT WIN32)
ENDIF(INSTALL_LIBS)

#INSTALL of other files requires CMake 2.6
IF (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.5)
	OPTION(INSTALL_EXTRA_LIBS "Set when you want extra libraries installed" OFF)
ENDIF (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.5)

OPTION(BUILD_UNIT_TESTS "Build Unit Tests"	OFF)

IF (BUILD_UNIT_TESTS)
	SUBDIRS(UnitTests)
ENDIF()
