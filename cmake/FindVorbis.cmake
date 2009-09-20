# - Try to find Vorbis
# Once done this will define
#  
#  VORBIS_FOUND        - system has Vorbis
#  VORBIS_INCLUDE_DIR  - the include directory
#  VORBIS_LIBRARY  - Link these to use Vorbis

FIND_PATH(VORBIS_INCLUDE_DIR codec.h vorbisenc.h vorbisfile.h
	PATH_SUFFIXES include/vorbis include
	PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw
	/opt/local
	/opt/csw
	/opt
)

#todo split to check each of the libraries
FIND_LIBRARY(VORBIS_LIB NAMES vorbis vorbisfile m
	PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
	PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw
	/opt/local
	/opt/csw
	/opt
)

FIND_LIBRARY(VORBISFILE_LIB NAMES vorbisfile
	PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
	PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw
	/opt/local
	/opt/csw
	/opt
)
FIND_LIBRARY(M_LIB NAMES m
	PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
	PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw
	/opt/local
	/opt/csw
	/opt
)

SET(VORBIS_FOUND NO)
IF(VORBIS_LIB AND VORBISFILE_LIB AND M_LIB AND VORBIS_INCLUDE_DIR)
  SET(VORBIS_FOUND YES)
  SET(VORBIS_LIBRARY ${VORBIS_LIB} ${VORBISFILE_LIB} ${M_LIB})
ENDIF(VORBIS_LIB AND VORBISFILE_LIB AND M_LIB AND VORBIS_INCLUDE_DIR)

MARK_AS_ADVANCED(VORBIS_INCLUDE_DIR VORBIS_LIBRARY)
