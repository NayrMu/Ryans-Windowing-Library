# Create an executable target and specify the source files
add_executable(WinWrap
    "main.c"
)

add_subdirectory("WWinds")
add_subdirectory("Fbuff")
target_link_libraries(WinWrap wwinds)
target_link_libraries(WinWrap fbuff)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WinWrap PROPERTY CXX_STANDARD 20)
  target_compile_options(WinWrap PRIVATE -O0)
endif()