# Create an executable target and specify the source files
add_executable(WinWrap
    "main.c"
)

# target_include_directories(WinWrap PRIVATE "GMath" "Voxel" "Shader")

# Link against GLFW
# target_link_libraries(WinWrap PRIVATE glfw3)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WinWrap PROPERTY CXX_STANDARD 20)
  target_compile_options(WinWrap PRIVATE -O0)
endif()