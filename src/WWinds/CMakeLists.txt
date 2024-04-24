add_library(wwinds STATIC "WWinds.c" "draw.c")
target_include_directories(wwinds PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
