
ADD_DEFINITIONS("-g --std=c++0x -O3 -msse2 -mmmx -mfpmath=sse")
ADD_DEFINITIONS("-fPIC")
#ADD_DEFINITIONS("-g --std=c++0x -msse2 -mmmx -mfpmath=sse")
ADD_DEFINITIONS("-DTBB_PREVIEW_CONCURRENT_PRIORITY_QUEUE")

INCLUDE_DIRECTORIES("./")

INCLUDE_DIRECTORIES("./srv_log")

INCLUDE_DIRECTORIES("./dist_impl")
#INCLUDE_DIRECTORIES("../pwworldsrv/conf")
INCLUDE_DIRECTORIES("../pwworldsrv/msg")
INCLUDE_DIRECTORIES("../pwworldsrv/msg/process_proto")
INCLUDE_DIRECTORIES("../pwaccsrv/msg")

INCLUDE_DIRECTORIES("../libutil")
INCLUDE_DIRECTORIES("../libutil/algorithm")
INCLUDE_DIRECTORIES("../libdefs")
INCLUDE_DIRECTORIES("../libcore/inc")
INCLUDE_DIRECTORIES("../libcore/cache")
INCLUDE_DIRECTORIES("../libg3dlite/include")

INCLUDE_DIRECTORIES("../../shared/pwmsg")

