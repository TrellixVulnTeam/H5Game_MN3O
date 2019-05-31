PROJECT(dbmod_merge)

ADD_DEFINITIONS("-g --std=c++0x  -O3 -msse2 -mmmx -mfpmath=sse")

INCLUDE_DIRECTORIES("./")
INCLUDE_DIRECTORIES("./mods")
INCLUDE_DIRECTORIES("../libutil")
INCLUDE_DIRECTORIES("../libutil/kvdb")
INCLUDE_DIRECTORIES("../libutil/gdb")

ADD_LIBRARY(dbmod_merge SHARED "./mods/dbmod_merge.cpp")