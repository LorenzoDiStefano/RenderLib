cmake_minimum_required (VERSION 3.8)

project ("RenderLib" VERSION 0.0.1)

message("Starting setup")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RENDERLIB_HEADERS
	"src/ogl4/OpenGL4Api.hpp"
	"src/glad.h"
	"src/khrplatform.h"
	"src/IGPUApi.hpp"
	"src/utils/MeshData.h"
	"src/utils/Utils.h"
)

set(RENDERLIB_SOURCE
	
	${RENDERLIB_HEADERS_HEADERS}
	"src/ogl4/OpenGL4Api.cpp"
	"src/glad.c"
	"src/main.cpp"
	"src/utils/MeshData.cpp"
	"src/utils/Utils.cpp"
)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

add_executable(RenderLibMainTest ${RENDERLIB_SOURCE})
add_subdirectory(dependencies)

target_include_directories(RenderLibMainTest PRIVATE ${glm_SOURCE_DIR})

target_link_libraries(RenderLibMainTest PRIVATE glfw assimp)
target_include_directories(RenderLibMainTest PRIVATE glfw)
