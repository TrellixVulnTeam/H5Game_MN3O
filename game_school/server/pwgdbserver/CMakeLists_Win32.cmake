# windows cmake

FILE(GLOB_RECURSE CMAKE_LIST . "*.cmake")

# header files
FILE(GLOB_RECURSE HEARDER_LIST . "*.h")

# source files
SET(SRC
	"./main.cpp"
	"./pw_gdb_client_script.cpp"
	"./pw_gdb_client_script_lua.cpp"
	"./pw_gdb_database.cpp"
	"./pw_gdb_database_backup.cpp"
	"./pw_gdb_database_dumpthread.cpp"
	"./pw_gdb_database_script_helper.cpp"
	"./pw_gdb_environment.cpp"
	"./pw_gdb_master.cpp"
	"./pw_gdb_master_connection.cpp"
	"./pw_gdb_operation.cpp"
	"./pw_gdb_operation_common.cpp"
	"./pw_gdb_operation_hashtable.cpp"
	"./pw_gdb_operation_kv.cpp"
	"./pw_gdb_operation_zset.cpp"
	"./pw_gdb_oplog.cpp"
	"./pw_gdb_query.cpp"
	"./pw_gdb_server.cpp"
	"./pw_gdb_server_connection.cpp"
	"./pw_gdb_server_connection_h.cpp"
	"./pw_gdb_server_connection_m.cpp"
	"./pw_gdb_server_connection_s.cpp"
	"./pw_gdb_server_connection_z.cpp"
	"./pw_gdb_slave.cpp"
	"./pw_gdb_slave_connection.cpp"
	"./pw_gdb_update.cpp"
	"./pw_orm_user.cpp"
	)

SET(SRC_MODS
	"./mods/dbmod_convert_passport.cpp"
	"./mods/dbmod_fix_names.cpp"
	"./mods/dbmod_fix_names2.cpp"
	"./mods/dbmod_fix_passportitems.cpp"
	"./mods/dbmod_merge.cpp"
	"./mods/dbmod_remove_futile.cpp"
	)

SET(SRC_LEVEL_DB_SNAPPY
	"../../deps/leveldb_1_15/snappy/snappy-c.cc"
	"../../deps/leveldb_1_15/snappy/snappy-sinksource.cc"
	"../../deps/leveldb_1_15/snappy/snappy-stubs-internal.cc"
	"../../deps/leveldb_1_15/snappy/snappy.cc"
	)
	
SET(SRC_LEVEL_DB_PORT
	"../../deps/leveldb_1_15/port/port_win.cc"
	)
	
SET(SRC_LEVEL_DB_DB
	"../../deps/leveldb_1_15/db/builder.cc"
	"../../deps/leveldb_1_15/db/db_impl.cc"
	"../../deps/leveldb_1_15/db/db_iter.cc"
	"../../deps/leveldb_1_15/db/dbformat.cc"
	"../../deps/leveldb_1_15/db/filename.cc"
	"../../deps/leveldb_1_15/db/log_reader.cc"
	"../../deps/leveldb_1_15/db/log_writer.cc"
	"../../deps/leveldb_1_15/db/c.cc"
	"../../deps/leveldb_1_15/db/memtable.cc"
	"../../deps/leveldb_1_15/db/repair.cc"
	"../../deps/leveldb_1_15/db/table_cache.cc"
	"../../deps/leveldb_1_15/db/version_edit.cc"
	"../../deps/leveldb_1_15/db/version_set.cc"
	"../../deps/leveldb_1_15/db/write_batch.cc"
	)
	
SET(SRC_LEVEL_DB_TABLE
	"../../deps/leveldb_1_15/table/block.cc"
	"../../deps/leveldb_1_15/table/block_builder.cc"
	"../../deps/leveldb_1_15/table/filter_block.cc"
	"../../deps/leveldb_1_15/table/format.cc"
	"../../deps/leveldb_1_15/table/iterator.cc"
	"../../deps/leveldb_1_15/table/merger.cc"
	"../../deps/leveldb_1_15/table/table.cc"
	"../../deps/leveldb_1_15/table/table_builder.cc"
	"../../deps/leveldb_1_15/table/two_level_iterator.cc"
	)
	
SET(SRC_LEVEL_DB_UTIL
	"../../deps/leveldb_1_15/util/arena.cc"
	"../../deps/leveldb_1_15/util/bloom.cc"
	"../../deps/leveldb_1_15/util/cache.cc"
	"../../deps/leveldb_1_15/util/coding.cc"
	"../../deps/leveldb_1_15/util/comparator.cc"
	"../../deps/leveldb_1_15/util/crc32c.cc"
	"../../deps/leveldb_1_15/util/env.cc"
	"../../deps/leveldb_1_15/util/env_win.cc"
	"../../deps/leveldb_1_15/util/filter_policy.cc"
	"../../deps/leveldb_1_15/util/hash.cc"
	"../../deps/leveldb_1_15/util/histogram.cc"
	"../../deps/leveldb_1_15/util/logging.cc"
	"../../deps/leveldb_1_15/util/options.cc"
	"../../deps/leveldb_1_15/util/status.cc"
	"../../deps/leveldb_1_15/util/testutil.cc"
	"../../deps/leveldb_1_15/util/win_logger.cc"
	)


# source_group
SOURCE_GROUP("mods" REGULAR_EXPRESSION mods)
SOURCE_GROUP("db" REGULAR_EXPRESSION leveldb)
SOURCE_GROUP("table" REGULAR_EXPRESSION table)
SOURCE_GROUP("snappy" REGULAR_EXPRESSION snappy)
SOURCE_GROUP("port" REGULAR_EXPRESSION port)
SOURCE_GROUP("port\\win" REGULAR_EXPRESSION port/win)


# include directories
INCLUDE_DIRECTORIES(
	${DEPS_ACE}
	${DEPS_EXPAT}
	${DEPS_LEVEL_DB}
	${DEPS_LEVEL_DB}/db
	${DEPS_LEVEL_DB}/include
	${DEPS_LEVEL_DB}/port
	${DEPS_LEVEL_DB}/table
	${DEPS_LEVEL_DB}/util
	${DEPS_LEVEL_DB}/port/win
	${DEPS_LIBICONV}
	${DEPS_LOG4CPLUS}
	${DEPS_LUA51}
	${DEPS_MYSQL}
	${DEPS_PROTOBUF}
	${DEPS_PTHREAD}
	${DEPS_TBB}
	${DEPS_UNITTEST}
	${DEPS_ZEROMQ}
	${DEPS_ZLIB}
	)

INCLUDE_DIRECTORIES(
	"./"
	"./mods"
	"../../shared/pwmsg"
	)

INCLUDE_DIRECTORIES(
	"../libcore/inc"
	"../libutil"
	"../libutil/gdb"
	"../libg3dlite/include"
	"../libdefs"
	)

# build exe
ADD_EXECUTABLE(pwgdbserver 
	${CMAKE_LIST}
	${HEARDER_LIST}
	${SRC} 
	${SRC_MODS}
	${SRC_LEVEL_DB_UTIL}
	${SRC_LEVEL_DB_DB}
	${SRC_LEVEL_DB_TABLE}
	${SRC_LEVEL_DB_SNAPPY}
	${SRC_LEVEL_DB_PORT}
	${SRC_LEVEL_DB_PORT_WIN}
    )

ADD_DEPENDENCIES(pwgdbserver util)
	
TARGET_LINK_LIBRARIES(pwgdbserver 
	ACEd 
	zlib
	libiconv
	libcharset
	libmysql
	UnitTest++.vsnet2005
	lua51
	libprotobuf
	libzmq
	libexpat
	pthreadVC2
	log4cplus
	WS2_32
	)
	
TARGET_LINK_LIBRARIES(pwgdbserver util core)

SET_TARGET_PROPERTIES(pwgdbserver
		PROPERTIES
		COMPILE_FLAGS "/wd4996"
	)




	