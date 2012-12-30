#last CMAKE file
cmake_minimum_required(VERSION 2.8)
project(karakaxa)

include_directories( ${LAST_FM_INCL})

file(GLOB_RECURSE  LFM_CPP "./*.cpp")
file(GLOB_RECURSE  LFM_HDRS "./*.h")
QT4_WRAP_CPP( LFM_MOC_SRCS ${LFM_HDRS} )

ADD_LIBRARY (karakaxa_lfm STATIC ${LFM_CPP} ${LFM_MOC_SRCS} )
TARGET_LINK_LIBRARIES( karakaxa_lfm lastfm )