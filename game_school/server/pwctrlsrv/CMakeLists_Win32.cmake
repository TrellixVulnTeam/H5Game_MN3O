# windows cmake

FILE(GLOB_RECURSE CMAKE_LIST . "*.cmake")

# header files
FILE(GLOB_RECURSE HEARDER_LIST . "*.h")

# source files
AUX_SOURCE_DIRECTORY(./ SRC)
AUX_SOURCE_DIRECTORY(../pwworldsrv/msg/process_proto SRC_MSG_PROTO)
AUX_SOURCE_DIRECTORY(./dist_impl SRC_DIST_IMPL)
AUX_SOURCE_DIRECTORY(./srv_log SRC_LOG)


SET(SRC_SHARED_MSG "../../shared/pwmsg/options.pb.cc" "../pwaccsrv/msg/accsrv.pb.cc")
# SET(SRC_WORLDSRV 
	# "../pwworldsrv/common/pw_upgrader.h"
	# "../pwworldsrv/common/pw_upgrader.cpp"
	# "../pwworldsrv/dataset/pw_shop_dataset.h"
    # "../pwworldsrv/dataset/pw_shop_dataset.cpp" 
	# "../pwworldsrv/dataset/pw_arena_match_dataset.h"
    # "../pwworldsrv/dataset/pw_arena_match_dataset.cpp"
	# "../pwworldsrv/dataset/pw_guild_dataset.h"
    # "../pwworldsrv/dataset/pw_guild_dataset.cpp"
	# "../pwworldsrv/dataset/pw_guild_fruiter_dataset.h" 
    # "../pwworldsrv/dataset/pw_guild_fruiter_dataset.cpp"
	# "../pwworldsrv/dataset/pw_notify_ball_dataset.h"
	# "../pwworldsrv/dataset/pw_notify_ball_dataset.cpp"
	# "../pwworldsrv/item/pw_item_build_struct.h"
	# "../pwworldsrv/item/pw_item_build_struct.cpp"
	# "../pwworldsrv/common_activity/pw_common_activity_dataset.h"
	# "../pwworldsrv/common_activity/pw_common_activity_dataset.cpp"
	# "../pwworldsrv/dataset/pw_warlord_dataset.h"
	# "../pwworldsrv/dataset/pw_warlord_dataset.cpp"
	# "../pwworldsrv/dataset/pw_mall_dataset.h"
	# "../pwworldsrv/dataset/pw_mall_dataset.cpp"
	# "../pwworldsrv/dataset/pw_gameseller_dataset.h"
	# "../pwworldsrv/dataset/pw_gameseller_dataset.cpp"
	# "../pwworldsrv/dataset/pw_playentry_dataset.h"
	# "../pwworldsrv/dataset/pw_playentry_dataset.cpp"
	# "../pwworldsrv/activities/pw_activity_dataset.h"
	# "../pwworldsrv/activities/pw_activity_dataset.cpp"
	# "../pwworldsrv/dataset/pw_njtz_dataset.h"
	# "../pwworldsrv/dataset/pw_njtz_dataset.cpp"
	# "../pwworldsrv/dataset/pw_open_auction_dataset.h"
	# "../pwworldsrv/dataset/pw_open_auction_dataset.cpp"
	# "../pwworldsrv/dataset/pw_guild_trial_land_dataset.h"
	# "../pwworldsrv/dataset/pw_guild_trial_land_dataset.cpp"
	# "../pwworldsrv/dataset/pw_grouppurchase_dataset.h"
	# "../pwworldsrv/dataset/pw_grouppurchase_dataset.cpp"
	# "../pwworldsrv/dataset/pw_public_dataset.h"
	# "../pwworldsrv/dataset/pw_public_dataset.cpp"
	# "../pwworldsrv/dataset/pw_activity_kfmz_dataset.h"
	# "../pwworldsrv/dataset/pw_activity_kfmz_dataset.cpp"
	# "../pwworldsrv/dataset/pw_runcar_dataset.h"
	# "../pwworldsrv/dataset/pw_runcar_dataset.cpp"
	# "./hmodules/pw_hmodules.h"
	# "./hmodules/pw_hmodules.cpp"
	# )
	
# 过滤文件
SET(IGNORE_SRC_DIST_IMPL
	"./dist_impl/pw_rpcs_impl_base.cpp"
	)
list(REMOVE_ITEM SRC_DIST_IMPL ${IGNORE_SRC_DIST_IMPL})

# SET(SRC_CONF
	# "../pwworldsrv/conf/pwconf_Activity.h"
	# "../pwworldsrv/conf/pwconf_Activity.cpp"
	# "../pwworldsrv/conf/pwconf_ActivityGuildWarReward.h"
	# "../pwworldsrv/conf/pwconf_ActivityGuildWarReward.cpp"
	# "../pwworldsrv/conf/pwconf_Adventure.h"
	# "../pwworldsrv/conf/pwconf_Adventure.cpp"
	# "../pwworldsrv/conf/pwconf_AdventureEvent.h"
	# "../pwworldsrv/conf/pwconf_AdventureEvent.cpp"
	# "../pwworldsrv/conf/pwconf_AdventureGenerate.h"
	# "../pwworldsrv/conf/pwconf_AdventureGenerate.cpp"
	# "../pwworldsrv/conf/pwconf_ArenaJoin.h"
	# )
	
# ignore files
# SET(IGNORE_LIST 
	# "./pw_msg_export_pwaccsrv.cpp"
	# )
	
# list(REMOVE_ITEM SRC_LIST ${IGNORE_LIST})

# source_group
SOURCE_GROUP("dist_impl" REGULAR_EXPRESSION dist_impl)
SOURCE_GROUP("srv_log" REGULAR_EXPRESSION srv_log)
SOURCE_GROUP("pwworldsrv" REGULAR_EXPRESSION pwworldsrv)
SOURCE_GROUP("conf" REGULAR_EXPRESSION pwworldsrv/conf)
SOURCE_GROUP("msg" REGULAR_EXPRESSION pwworldsrv/msg)



# include directories
INCLUDE_DIRECTORIES(
	${DEPS_PTHREAD}
	${DEPS_TBB}
	${DEPS_EXPAT}
	${DEPS_CURL}
	${DEPS_LOG4CPLUS}
	${DEPS_OPENSSL}
	${DEPS_ZEROMQ}
	${DEPS_LUA51}
	${DEPS_LIBICONV}
	${DEPS_ACE}
	${DEPS_PROTOBUF}
	${DEPS_MYSQL}
	${DEPS_VLD}
	${DEPS_UNITTEST}
	)

INCLUDE_DIRECTORIES(
	"./"
	"./srv_log"
	"./dist_impl"
	)

INCLUDE_DIRECTORIES(
	"../pwworldsrv/conf"
	"../pwworldsrv/msg"
	"../pwworldsrv/msg/process_proto"
	"../pwaccsrv/msg"
	"../common"
	"../common/algorithm"
	"../pwcommon"
	"../libcore/inc"
	"../libcore/cache"
	"../g3dlite/include"
	"../../shared/pwmsg"
	"../libdefs"
	"../libutil"
	"../libutil/algorithm"
	"../libg3dlite"
	"../libcore/inc"
	"../libcore/cache"
	"../libg3dlite/include"
	)

# build exe
ADD_EXECUTABLE(pwctrlsrv 
	${CMAKE_LIST}
	${HEARDER_LIST}
	${SRC} ${SRC_MSG_PROTO} ${SRC_DIST_IMPL}
	#${SRC_CONF}
	${SRC_SHARED_MSG} 
	#${SRC_WORLDSRV}
    ${SRC_LOG}
    )

ADD_DEPENDENCIES(pwctrlsrv core util g3dlite defs)
	
TARGET_LINK_LIBRARIES(pwctrlsrv libexpat libzmq ACEd tbb log4cplus pthreadVC2 mysqlclient libprotobuf lua51 libcurl_imp ssleay32 libeay32 UnitTest++.vsnet2005 libiconv)
TARGET_LINK_LIBRARIES(pwctrlsrv core util g3dlite defs)

SET_TARGET_PROPERTIES(pwctrlsrv
		PROPERTIES
		COMPILE_FLAGS "/wd4996"
	)




	