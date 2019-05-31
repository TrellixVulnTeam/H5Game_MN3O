# header files
FILE(GLOB_RECURSE HEARDER_LIST . "*.h")

SOURCE_GROUP("dist_impl" REGULAR_EXPRESSION dist_impl)

# source files
AUX_SOURCE_DIRECTORY(./ SRC)
AUX_SOURCE_DIRECTORY(./dist_impl SRC_DIST_IMPL)

SET(IGNORE_DIST_IMPL 
	"./dist_impl/pw_rpcs_impl_base.cpp"
	)

list(REMOVE_ITEM SRC_DIST_IMPL ${IGNORE_DIST_IMPL})
	
INCLUDE_DIRECTORIES(
	"./"
	"./dist_impl"
	"../libutil"
	"../libdefs"
	"../libcore/inc"
	"../libcore/cache"
	)

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


ADD_EXECUTABLE(pwglobalsrv
	${HEARDER_LIST}
	${SRC}
	${SRC_DIST_IMPL}
	)
	
ADD_DEPENDENCIES(pwglobalsrv core util g3dlite defs)

	TARGET_LINK_LIBRARIES(pwglobalsrv libexpat libzmq ACEd tbb log4cplus libmysql.lib pthreadVC2 libprotobuf lua51 libcurl_imp ssleay32 libeay32 UnitTest++.vsnet2005 libiconv)
	TARGET_LINK_LIBRARIES(pwglobalsrv core util g3dlite defs)

	SET_TARGET_PROPERTIES(pwglobalsrv
			PROPERTIES
			COMPILE_FLAGS "/wd4996"
	)
	