cmake_minimum_required(VERSION 3.12)
project(OpenGLApp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLFW minimal build
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/glad)
add_subdirectory(external/glfw)

# ----------------- ImGui Target -----------------
add_library(imgui STATIC
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

# ImGui needs glad & glfw headers to compile its backends
target_include_directories(imgui PUBLIC
    external/imgui
    external/imgui/backends
)
target_link_libraries(imgui PUBLIC glad glfw)
# ------------------------------------------------

add_executable(app 
    src/main.cpp
    src/stb_image.cpp
)

target_link_libraries(app PRIVATE 
    glad 
    glfw 
    imgui
)

target_include_directories(app PRIVATE 
    external/glm
    external/stb
)
