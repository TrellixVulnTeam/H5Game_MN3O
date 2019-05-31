PROJECT(hmtest1_c)

#ADD_DEFINITIONS("-fPIC")

INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/include.cmake)

INCLUDE_DIRECTORIES(./hmodules)

ADD_LIBRARY(hmtest1_c SHARED "./hmodules/pw_hmodule_test1.cpp")