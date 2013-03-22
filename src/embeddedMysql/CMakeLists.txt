#EMBEDDED_MYSQL
cmake_minimum_required(VERSION 2.8)
project(karakaxa)


FIND_PACKAGE( Qt4 REQUIRED )


SET( QT_USE_PHONON TRUE ) 
SET( QT_USE_SQL TRUE ) 
SET( QT_USE_XML TRUE)

SET( USE_LAST_FM TRUE )

SET( DATA_DIR /usr/share/kde4/apps)
INCLUDE_DIRECTORIES(${QT_QTSQL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${MYSQL_INCLUDEl})
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(/usr/include/Qt)

set ( LIB_CPP main.cpp qsql_mysql.cpp)
set (LIB_HDRS qsql_mysql.h  qsql_mysql_private.h  embeddedMysqlCreator.h)


QT4_WRAP_CPP( LIB_MOC_SRCS ${LIB_HDRS} )

add_library ( embeddedMysql STATIC ${LIB_CPP} ${LIB_MOC_SRCS} )
TARGET_LINK_LIBRARIES( embeddedMysql ${MYSQL_LIB} )
