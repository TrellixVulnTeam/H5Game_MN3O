if(WIN32)

INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists_Win32.cmake)

else()

PROJECT(pwworldsrv_all)

INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CMakeListsW.cmake)
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CMakeListsH.cmake)

endif()