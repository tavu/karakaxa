#LIBRARY
cmake_minimum_required(VERSION 2.8)
project(karakaxa)

# set( LAST_FM_FILES ../lastFm)

file(GLOB_RECURSE  LIB_CPP "./*.cpp")
file(GLOB_RECURSE  LIB_HDRS "./*.h")



SET( HDRS
     ./database 
     ./core 
     ./files 
     ./views
     .
)

QT4_WRAP_CPP( LIB_MOC_SRCS ${LIB_HDRS}  )

ADD_LIBRARY ( karakaxa SHARED ${LIB_CPP} ${LIB_MOC_SRCS} )
#TARGET_LINK_LIBRARIES( karakaxa ${QT_QTSQL_LIBRARIES} )


INSTALL(TARGETS karakaxa LIBRARY DESTINATION lib)