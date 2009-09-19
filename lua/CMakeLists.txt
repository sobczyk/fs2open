SET(lua_libname lua)

SET(lua_SRCS
	lapi.c
	lauxlib.c
	lbaselib.c
	lcode.c
	ldblib.c
	ldebug.c
	ldo.c
	ldump.c
	lfunc.c
	lgc.c
	linit.c
	liolib.c
	llex.c
	lmathlib.c
	lmem.c
	loadlib.c
	lobject.c
	lopcodes.c
	loslib.c
	lparser.c
	lstate.c
	lstring.c
	lstrlib.c
	ltable.c
	ltablib.c
	ltests.c
	ltm.c
	lua.c
	lundump.c
	lvm.c
	lzio.c
	print.c
)

INCLUDE(
	${CMAKE_CURRENT_BINARY_DIR}
)

ADD_LIBRARY(${lua_libname} STATIC ${lua_SRCS})
#set for external use
SET(LUA_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE)
SET(LUA_LIBRARY ${lua_libname} PARENT_SCOPE)
