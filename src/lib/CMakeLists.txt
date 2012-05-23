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

file(GLOB_RECURSE  LIB_CPP "./*.cpp")
file(GLOB_RECURSE  LIB_HDRS "./*.h")


SET( HDRS
     ./database 
     ./core 
     ./files 
     ./views    
)


FIND_PACKAGE( Qt4 REQUIRED )
SET( QT_USE_PHONON TRUE )
SET( QT_USE_SQL TRUE )
SET( QT_USE_XML TRUE)
# 
# 
# include_directories(./database)
# include_directories(./core )
# include_directories(./files )
# include_directories(./views )
# 
# include_directories( ${HDRS})
# include_directories( /usr/include/KDE/)
# include_directories( /usr/include/taglib)
# 
# INCLUDE_DIRECTORIES(${QT_QTSQL_INCLUDE_DIR})
# INCLUDE_DIRECTORIES(${QT_QTXML_INCLUDE_DIR})
# 
# ADD_DEFINITIONS( -Wall -Wno-reorder )
# INCLUDE(${QT_USE_FILE})


QT4_WRAP_CPP( LIB_MOC_SRCS ${LIB_HDRS} )

# LIBS += -lkdecore -lkdeui -lkfile -lkio -ltag -ltag-extras 
# ADD_EXECUTABLE( karakaxa ${LIB_CPP} )
add_library ( karakaxa SHARED ${LIB_CPP} ${LIB_MOC_SRCS}  )
TARGET_LINK_LIBRARIES( karakaxa ${QT_LIBRARIES} )
TARGET_LINK_LIBRARIES( karakaxa ${QT_QTSQL_LIBRARIES} )
TARGET_LINK_LIBRARIES( karakaxa ${QT_QTXM_LIBRARIES} )

TARGET_LINK_LIBRARIES( karakaxa kdecore )
TARGET_LINK_LIBRARIES( karakaxa kdeui )
TARGET_LINK_LIBRARIES( karakaxa kfile )
TARGET_LINK_LIBRARIES( karakaxa kio )
TARGET_LINK_LIBRARIES( karakaxa tag )
TARGET_LINK_LIBRARIES( karakaxa tag-extras )

INSTALL(TARGETS karakaxa LIBRARY DESTINATION lib)