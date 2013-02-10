#application
cmake_minimum_required(VERSION 2.8)
project(karakaxa)


file(GLOB_RECURSE  APP_CPP "./*.cpp")
file(GLOB_RECURSE  APP_HDRS "./*.h")


QT4_WRAP_CPP( APP_MOC_SRCS ${APP_HDRS} )
ADD_EXECUTABLE( karakaxa_exec ${APP_CPP} ${APP_MOC_SRCS} )

# add_library ( karakaxa_exec SHARED ${LIB_CPP}  )
TARGET_LINK_LIBRARIES( karakaxa_exec karakaxa )
TARGET_LINK_LIBRARIES( karakaxa_exec ${QT_LIBRARIES} )
TARGET_LINK_LIBRARIES( karakaxa_exec ${QT_QTSQL_LIBRARIES} )
TARGET_LINK_LIBRARIES( karakaxa_exec ${QT_QTXM_LIBRARIES} )
TARGET_LINK_LIBRARIES( karakaxa_exec kdecore )
TARGET_LINK_LIBRARIES( karakaxa_exec kdeui )
TARGET_LINK_LIBRARIES( karakaxa_exec kfile )
TARGET_LINK_LIBRARIES( karakaxa_exec kio )
TARGET_LINK_LIBRARIES( karakaxa_exec tag )
# TARGET_LINK_LIBRARIES( karakaxa_exec tag-extras )
# TARGET_LINK_LIBRARIES( karakaxa_exec lastfm )

if ( ${USE_LAST_FM}  )
  	TARGET_LINK_LIBRARIES( karakaxa_exec karakaxa_lfm )
endif()

set_target_properties(karakaxa_exec PROPERTIES OUTPUT_NAME "karakaxa")
INSTALL(TARGETS karakaxa_exec RUNTIME DESTINATION bin)
