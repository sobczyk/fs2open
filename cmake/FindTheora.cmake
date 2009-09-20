# - Try to find Theora
# Once done this will define
#  
#  THEORA_FOUND        - system has Theora
#  THEORA_INCLUDE_DIR  - the include directory
#  THEORA_LIBRARY  - Link these to use Theora

FIND_PATH(THEORA_INCLUDE_DIR theora.h
	PATH_SUFFIXES include/theora include
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

FIND_LIBRARY(THEORA_LIBRARY theora
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

SET(THEORA_FOUND NO)
IF(THEORA_LIBRARY AND THEORA_INCLUDE_DIR)
  SET(THEORA_FOUND YES)
ENDIF(THEORA_LIBRARY AND THEORA_INCLUDE_DIR)

MARK_AS_ADVANCED(THEORA_INCLUDE_DIR THEORA_LIBRARY)
