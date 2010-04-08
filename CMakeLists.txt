PROJECT (AmberHyperNet)

#SET(CMAKE_VERBOSE_MAKEFILE "ON")

SET(CMAKE_CXX_FLAGS "-Wno-deprecated" )
SET(CMAKE_CXX_FLAGS "-Os" )

ADD_DEFINITIONS( -fPIC)

SUBDIRS( src/main )
SUBDIRS( src/ahnServLog )
SUBDIRS( src/ahnMicrocore )
