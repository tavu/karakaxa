cmake_minimum_required(VERSION 2.8)
project(karakaxa)

option (USE_LAST_FM "Use last-fm library" ON) 

option (DEBUG "built on debug mode" ON)

# mysql
option (EMBEDDED_MYSQL "use embedded mysql" ON)
set( MYSQL_INCLUDE "/usr/include/mysql")
set (MYSQL_LIB "/usr/lib64/libmysqld.so.18")
set(KDE_INCLUDE "/usr/include/KDE")

set(TAGLIB_INCLUDE "/usr/include/taglib")

set( DATA_DIR "/usr/share/kde4/apps")

