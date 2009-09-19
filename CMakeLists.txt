cmake_minimum_required(VERSION 2.6)

PROJECT( fsopen )

#build options
OPTION(JPEG_STATIC "Build statically with the included jpeg library" ON)
#not working atm.
OPTION(speech "Build speech recognition (Windows only)" ON)

#some options are forced on certain systems
IF(WIN32)
	SET(JPEG_STATIC ON)
ELSEIF(WIN32)
	SET(speech OFF)
	SET(directx OFF)
ENDIF(WIN32)

IF( NOT CMAKE_BUILD_TYPE )
	SET( CMAKE_BUILD_TYPE "Release" )
ENDIF()

IF( NOT CPACK_GENERATOR )
	SET( CPACK_GENERATOR "DEB")
ENDIF()

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-write-strings")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -Wno-write-strings")
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/build)

IF(UNIX)
	MESSAGE( "UNIX build" )
	ADD_DEFINITIONS(-DSCP_UNIX)
	ADD_DEFINITIONS(-DUSE_OPENAL)
ENDIF(UNIX)
IF(WIN32)
	MESSAGE( "WIN 32 build" )
	ADD_DEFINITIONS(-D_WIN32)
ENDIF(WIN32)

FIND_PACKAGE(SDL REQUIRED)
FIND_PACKAGE(OpenAL REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
IF(JPEG_STATIC)
	ADD_SUBDIRECTORY(libjpeg)
ELSE(JPEG_STATIC)
	FIND_PACKAGE(JPEG REQUIRED)
ENDIF(JPEG_STATIC)

ADD_SUBDIRECTORY(lua)
ADD_SUBDIRECTORY(code)

MESSAGE( STATUS )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}" )
MESSAGE( STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}" )
MESSAGE( STATUS "Change a value with: cmake -D<Variable>=<Value>" )
MESSAGE( STATUS "Package CPACK_GENERATOR=${CPACK_GENERATOR}" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS )
