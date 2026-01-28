cmake_minimum_required(VERSION 3.12)

project(glad LANGUAGES C)

add_library(glad STATIC
    src/glad.c
)

# Expose headers to consumers
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# OpenGL dependency
find_package(OpenGL REQUIRED)
target_link_libraries(glad PUBLIC OpenGL::GL)