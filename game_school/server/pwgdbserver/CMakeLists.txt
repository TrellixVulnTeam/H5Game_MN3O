cmake_minimum_required(VERSION 2.8)

if(WIN32)

	INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists_Win32.cmake)
	
else()

	PROJECT(pwgdbserver_all)

	INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CMakeListsS.cmake)
	INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists_FixPassportItems.cmake)
	INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists_ConvertPassport.cmake)
	INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists_RemoveFutile.cmake)
	INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists_Merge.cmake)
	INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists_FixNames.cmake)
	INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists_FixNames2.cmake)
	
endif()


