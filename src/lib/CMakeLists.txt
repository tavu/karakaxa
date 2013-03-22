#LIBRARY
cmake_minimum_required(VERSION 2.8)
project(karakaxa)

# set( LAST_FM_FILES ../lastFm)

file(GLOB_RECURSE  LIB_CPP "./*.cpp")
file(GLOB_RECURSE  LIB_HDRS "./*.h")

# FIND_PACKAGE( lastfm REQUIRED )

# if ( ${USE_LAST_FM}  )
# #  	file(GLOB_RECURSE  LAST_FM_CPP  "../lastFm/*.cpp")
# #   	file(GLOB_RECURSE  LAST_FM_HDRS "../lastFm/*.h")
# #   	QT4_WRAP_CPP( LAST_FM_MOC_SRCS ${LAST_FM_HDRS} )
# #   	subdirs(../lastFm)
# #   	include_directories(../lastFm)
# #   	TARGET_LINK_LIBRARIES( karakaxa lastfm )
# #    	TARGET_LINK_LIBRARIES( karakaxa_lfm lastfm ) 	
# endif()


SET( HDRS
     ./database 
     ./core 
     ./files 
     ./views
)


# FIND_PACKAGE( Qt4 REQUIRED )
# FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtSql REQUIRED)
# 
# SET( QT_USE_PHONON TRUE )
# SET( QT_USE_QTSQL TRUE )
# SET( QT_USE_XML TRUE)
# SET( QT_USE_NETWORK TRUE )
# INCLUDE_DIRECTORIES(${QT_QTSQL_INCLUDE_DIR})

QT4_WRAP_CPP( LIB_MOC_SRCS ${LIB_HDRS}  )

ADD_LIBRARY ( karakaxa SHARED ${LIB_CPP} ${LIB_MOC_SRCS} )
#TARGET_LINK_LIBRARIES( karakaxa ${QT_QTSQL_LIBRARIES} )


INSTALL(TARGETS karakaxa LIBRARY DESTINATION lib)