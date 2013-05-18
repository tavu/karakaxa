#APPLICATION
cmake_minimum_required(VERSION 2.8)
project(karakaxa)


file(GLOB_RECURSE  APP_CPP "./*.cpp")
file(GLOB_RECURSE  APP_HDRS "./*.h")
file(GLOB_RECURSE  APP_UI  "./*.ui")

QT4_WRAP_UI( APP_UI_HDRS ${APP_UI} )
QT4_WRAP_CPP( APP_MOC_SRCS ${APP_HDRS} )
ADD_EXECUTABLE( karakaxa_exec ${APP_CPP} ${APP_MOC_SRCS} ${APP_UI_HDRS} )

TARGET_LINK_LIBRARIES( karakaxa_exec karakaxa )
TARGET_LINK_LIBRARIES( karakaxa_exec ${QT_LIBRARIES} )
TARGET_LINK_LIBRARIES( karakaxa_exec ${QT_QTXM_LIBRARIES} )
TARGET_LINK_LIBRARIES( karakaxa_exec kdecore )
TARGET_LINK_LIBRARIES( karakaxa_exec kdeui )
TARGET_LINK_LIBRARIES( karakaxa_exec kfile )
TARGET_LINK_LIBRARIES( karakaxa_exec kio )
TARGET_LINK_LIBRARIES( karakaxa_exec tag )
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
if(EMBEDDED_MYSQL)
    TARGET_LINK_LIBRARIES( karakaxa_exec embeddedMysql )
endif()


if ( USE_LAST_FM )
  	TARGET_LINK_LIBRARIES( karakaxa_exec karakaxa_lfm )
endif()


set_target_properties(karakaxa_exec PROPERTIES OUTPUT_NAME "karakaxa")
INSTALL(TARGETS karakaxa_exec RUNTIME DESTINATION bin)
