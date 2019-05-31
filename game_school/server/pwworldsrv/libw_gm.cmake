PROJECT(w_gm)

INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/include.cmake)

INCLUDE_DIRECTORIES(./hmodules)

ADD_LIBRARY(w_gm SHARED "./hmodules/pw_hmodule_wgm.cpp")