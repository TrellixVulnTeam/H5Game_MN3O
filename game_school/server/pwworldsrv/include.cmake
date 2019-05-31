ADD_DEFINITIONS("-g --std=c++0x -O3 -msse2 -mmmx -mfpmath=sse -Wno-deprecated")
#ADD_DEFINITIONS("-g --std=c++0x -msse2 -mmmx -mfpmath=sse -Wno-deprecated")
ADD_DEFINITIONS("-DTBB_PREVIEW_CONCURRENT_PRIORITY_QUEUE -DBT_NO_PROFILE")
ADD_DEFINITIONS("-fPIC")

INCLUDE_DIRECTORIES("./")
INCLUDE_DIRECTORIES("./dist_impl")
INCLUDE_DIRECTORIES("./msg")
INCLUDE_DIRECTORIES("./msg/process_proto")
INCLUDE_DIRECTORIES("./human")

INCLUDE_DIRECTORIES("../libutil")
INCLUDE_DIRECTORIES("../libdefs")
INCLUDE_DIRECTORIES("../libcore/inc")
INCLUDE_DIRECTORIES("../libcore/cache")
INCLUDE_DIRECTORIES("../libg3dlite/include")

INCLUDE_DIRECTORIES("../../shared/pwmsg")

