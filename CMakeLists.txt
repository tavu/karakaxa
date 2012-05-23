cmake_minimum_required(VERSION 2.8)
project(test)


# SET( SAMPLE_SRCS
#   ./src/w.cpp
# ./src/main.cpp
# )
# 
# SET( SAMPLE_HDRS
#   ./src/w.h
# )


FIND_PACKAGE( Qt4 REQUIRED )


SET( QT_USE_PHONON TRUE ) 
SET( QT_USE_SQL TRUE ) 
SET( QT_USE_XML TRUE)

SET( DATA_DIR /usr/share/kde4/apps)

include_directories(./src/lib/database)
include_directories(./src/lib/core )
include_directories(./src/lib/files )
include_directories(./src/lib/views )

include_directories( /usr/include/KDE/)
include_directories( /usr/include/taglib)

INCLUDE_DIRECTORIES(${QT_QTSQL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${QT_QTXML_INCLUDE_DIR})

ADD_DEFINITIONS( -Wall -Wno-reorder )

INCLUDE(${QT_USE_FILE})

subdirs(src/lib)
subdirs(src/player)

# INSTALL(FILES ../data DESTINATION ${DATA_INSTALL_DIR})
INSTALL(DIRECTORY data/icons DESTINATION ${DATA_DIR}/karakaxa)
INSTALL(DIRECTORY data/sql DESTINATION ${DATA_DIR}/karakaxa)

# file(INSTALL data/ DESTINATION ${DATA_DIR})

# INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/src/player/karakaxa  DESTINATION bin)
# INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/src/lib/karakaxalib  DESTINATION lib)

# INSTALL(TARGETS karakaxa karakaxalib 
#   RUNTIME DESTINATION bin
#   LIBRARY DESTINATION lib
# )