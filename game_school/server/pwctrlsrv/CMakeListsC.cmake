PROJECT(pwctrlsrv)

AUX_SOURCE_DIRECTORY(./ SRC)
AUX_SOURCE_DIRECTORY(../pwworldsrv/msg/process_proto SRC_MSG_PROTO)
AUX_SOURCE_DIRECTORY(./dist_impl SRC_DIST_IMPL)
AUX_SOURCE_DIRECTORY(./srv_log SRC_LOG)

#AUX_SOURCE_DIRECTORY(../pwworldsrv/conf SRC_CONF)

SET(SRC_SHARED_MSG "../../shared/pwmsg/options.pb.cc" "../pwaccsrv/msg/accsrv.pb.cc")
# SET(SRC_WORLDSRV "../pwworldsrv/common/pw_upgrader.cpp" 
    # "../pwworldsrv/dataset/pw_shop_dataset.cpp" 
    # "../pwworldsrv/dataset/pw_arena_match_dataset.cpp" 
    # "../pwworldsrv/dataset/pw_guild_dataset.cpp" 
    # "../pwworldsrv/dataset/pw_guild_fruiter_dataset.cpp" 
	# "../pwworldsrv/dataset/pw_notify_ball_dataset.cpp"
	# "../pwworldsrv/item/pw_item_build_struct.cpp"
	# "../pwworldsrv/common_activity/pw_common_activity_dataset.cpp"
	# "../pwworldsrv/dataset/pw_warlord_dataset.cpp"
	# "../pwworldsrv/dataset/pw_mall_dataset.cpp"
	# "../pwworldsrv/dataset/pw_gameseller_dataset"
	# "../pwworldsrv/dataset/pw_playentry_dataset.cpp"
	# "../pwworldsrv/activities/pw_activity_dataset.cpp"
	# "../pwworldsrv/dataset/pw_njtz_dataset.cpp"
	# "../pwworldsrv/dataset/pw_open_auction_dataset.cpp"
	# "../pwworldsrv/dataset/pw_guild_trial_land_dataset.cpp"
	# "../pwworldsrv/dataset/pw_grouppurchase_dataset.cpp"
	# "../pwworldsrv/dataset/pw_public_dataset.cpp"
	# "../pwworldsrv/dataset/pw_activity_kfmz_dataset.cpp"
	# "../pwworldsrv/dataset/pw_runcar_dataset.cpp"
	# "./hmodules/pw_hmodules.cpp")

ADD_DEFINITIONS("-g --std=c++0x -O3 -msse2 -mmmx -mfpmath=sse")
#ADD_DEFINITIONS("-g --std=c++0x -msse2 -mmmx -mfpmath=sse")
ADD_DEFINITIONS("-DTBB_PREVIEW_CONCURRENT_PRIORITY_QUEUE")

INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/include.cmake)

LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libutil/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libcore/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libg3dlite/Release")
LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/../build/libdefs/Release")

ADD_EXECUTABLE(pwctrlsrv 
	${SRC} ${SRC_MSG_PROTO} ${SRC_DIST_IMPL} 
	#${SRC_CONF} 
	${SRC_SHARED_MSG} 
	#${SRC_WORLDSRV}
    ${SRC_LOG}
    )

ADD_DEPENDENCIES(pwctrlsrv core util g3dlite defs)
TARGET_LINK_LIBRARIES(pwctrlsrv core defs util g3dlite)
TARGET_LINK_LIBRARIES(pwctrlsrv expat zmq ACE tbb log4cplus pthread mysqlclient protobuf lua5.1 curl ssl iconv)
TARGET_LINK_LIBRARIES(pwctrlsrv tcmalloc_minimal)