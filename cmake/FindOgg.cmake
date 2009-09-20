# - Try to find ogg
# Once done this will define
#  
#  OGG_FOUND        - system has Ogg
#  OGG_INCLUDE_DIR  - the include directory
#  OGG_LIBRARY  - Link these to use Ogg

FIND_PATH(OGG_INCLUDE_DIR ogg.h config_types.h os_types.h
	PATH_SUFFIXES include/ogg include
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

FIND_LIBRARY(OGG_LIBRARY ogg
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

SET(OGG_FOUND NO)
IF(OGG_LIBRARY AND OGG_INCLUDE_DIR)
  SET(OGG_FOUND YES)
ENDIF(OGG_LIBRARY AND OGG_INCLUDE_DIR)

MARK_AS_ADVANCED(OGG_INCLUDE_DIR OGG_LIBRARY)
