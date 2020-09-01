cmake_minimum_required (VERSION 3.8)

project ("RenderLib" VERSION 0.0.1)

message("Starting setup")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RenderLibMainTest "src/main.cpp")
add_subdirectory(dependencies)

target_include_directories(RenderLibMainTest PRIVATE ${glm_SOURCE_DIR})
