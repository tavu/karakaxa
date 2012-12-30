#library CMAKE file
cmake_minimum_required(VERSION 2.8)
project(karakaxa)


# SET( SAMPLE_SRCS
#   ./src/w.cpp
# ./src/main.cpp
# )
# 
# SET( SAMPLE_HDRS
#   ./src/w.h
# )

set( LAST_FM_FILES ../lastFm)

file(GLOB_RECURSE  LIB_CPP "./*.cpp")
file(GLOB_RECURSE  LIB_HDRS "./*.h")


# if ( ${LAST_FM_FOUND}  )
# # 	file(GLOB_RECURSE  LAST_FM_CPP  "../lastFm/*.cpp")
# # 	file(GLOB_RECURSE  LAST_FM_HDRS "../lastFm/*.h")
# # 	QT4_WRAP_CPP( LAST_FM_MOC_SRCS ${LAST_FM_HDRS} )
# # 	TARGET_LINK_LIBRARIES( karakaxa lastfm )
# #  	TARGET_LINK_LIBRARIES( karakaxa_lfm lastfm )
# 	subdirs(../lastFm)
# endif()

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


QT4_WRAP_CPP( LIB_MOC_SRCS ${LIB_HDRS} )

add_library ( karakaxa SHARED ${LIB_CPP} ${LIB_MOC_SRCS}    ${LAST_FM_CPP}  ${LAST_FM_MOC_SRCS}  )
#TARGET_LINK_LIBRARIES( karakaxa ${QT_LIBRARIES} )
#TARGET_LINK_LIBRARIES( karakaxa ${QT_QTSQL_LIBRARIES} )
#TARGET_LINK_LIBRARIES( karakaxa ${QT_QTXM_LIBRARIES} )

#TARGET_LINK_LIBRARIES( karakaxa kdecore )
#TARGET_LINK_LIBRARIES( karakaxa kdeui )
#TARGET_LINK_LIBRARIES( karakaxa kfile )
#TARGET_LINK_LIBRARIES( karakaxa kio )
#TARGET_LINK_LIBRARIES( karakaxa tag )
#TARGET_LINK_LIBRARIES( karakaxa tag-extras )

# TARGET_LINK_LIBRARIES( karakaxa karakaxa_lfm )

# if ( USE_LAST_FM  )
#   	TARGET_LINK_LIBRARIES( karakaxa karakaxa_lfm )
# endif()


INSTALL(TARGETS karakaxa LIBRARY DESTINATION lib)