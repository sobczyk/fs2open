
OPTION(GPROF "Enable profiling" OFF)
OPTION(DEBUG "Turn on debugging" OFF)

IF(DEBUG)
	SET( CMAKE_BUILD_TYPE "Release" )
	ADD_DEFINITIONS(-DNDEBUG)
ELSE(DEBUG)
	SET( CMAKE_BUILD_TYPE "Debug" )
	ADD_DEFINITIONS(-D_DEBUG)
ENDIF(DEBUG)

IF(GPROF)
	SET(flags ${flags} -pg)
ENDIF(GPROF)

SET(CMAKE_C_FLAGS
	${CMAKE_C_FLAGS}
	-Wno-write-strings
	-g
	${flags}
)
SET(CMAKE_CXX_FLAGS
	${CMAKE_CXX_FLAGS}
	-Wno-invalid-offsetof
	-Wno-write-strings
	-g
	${flags}
)

SET(CMAKE_C_FLAGS_DEBUG
	${CMAKE_C_FLAGS}
	-O0
	-Wall 
	-Wextra
	-Wno-usused-parameter
	-Wno-write-strings
	-Wshadow
	-funroll-loops
	${flags}
)
SET(CMAKE_CXX_FLAGS_DEBUG
	${CMAKE_CXX_FLAGS}
	-O0
	-Wall 
	-Wextra
	-Wno-usused-parameter
	-Wno-write-strings
	-Wshadow
	-funroll-loops
	${flags}
)

SET(CMAKE_C_FLAGS_RELEASE
	${CMAKE_C_FLAGS}
	-Os
	-Wall
	-funroll-loops
	${flags}
)
SET(CMAKE_CXX_FLAGS_RELEASE
	${CMAKE_CXX_FLAGS}
	-Os
	-Wall
	-funroll-loops
	${flags}
)
