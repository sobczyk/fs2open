
OPTION(GPROF "Enable profiling" OFF)
MESSAGE( STATUS "Enable profiling GPROF= ${GPROF}" )
OPTION(DEBUG "Turn on debugging" OFF)
MESSAGE( STATUS "Turn on debugging DEBUG= ${DEBUG}" )

IF(DEBUG)
	SET( CMAKE_BUILD_TYPE "Debug" )
	ADD_DEFINITIONS(-D_DEBUG)
ELSE(DEBUG)
	SET( CMAKE_BUILD_TYPE "Release" )
	ADD_DEFINITIONS(-DNDEBUG)
ENDIF(DEBUG)

IF(GPROF)
	SET(flags "-pg")
ENDIF(GPROF)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-write-strings -g ${flags}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -Wno-write-strings -g ${flags}")

SET(debug_flags "-O0 -Wall -Wextra -Wno-usused-parameter -Wno-write-strings -Wshadow -funroll-loops")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${debug_flags}")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${debug_flags}")

SET(release_flags "-Os -Wall -funroll-loops")
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${release_flags}")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${release_flags}")

IF( MSVC )
# check 64 bit
	IF( CMAKE_SIZEOF_VOID_P EQUALS 4 )
	  SET( HAVE_64_BIT FALSE )
	ELSE( CMAKE_SIZEOF_VOID_P EQUALS 4 )
	  SET( HAVE_64_BIT TRUE )
	ENDIF( CMAKE_SIZEOF_VOID_P EQUALS 4 )
ENDIF( MSVC )
