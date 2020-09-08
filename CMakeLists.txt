cmake_minimum_required (VERSION 3.8)

project ("RenderLib" VERSION 0.0.1)

message("Starting setup")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RENDERLIB_HEADERS
	"src/ogl4/OpenGL4Api.hpp"
 	#"src/ogl4/OpenGL4Mesh.hpp"
	"src/glad.h"
	"src/khrplatform.h"
	"src/IGPUApi.hpp"
	"src/utils/MeshData.h"
	"src/utils/Utils.h"
)

set(RENDERLIB_INCLUDES

 	"include/Renderlib/OpenGL4Mesh.hpp"
)


set(RENDERLIB_SOURCE
	
	${RENDERLIB_HEADERS_HEADERS}
	"src/ogl4/OpenGL4Api.cpp"
 	"src/ogl4/OpenGL4Mesh.cpp"
	"src/glad.c"
	"src/utils/MeshData.cpp"
	"src/utils/Utils.cpp"
)

	

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

add_executable(RenderLibMainTest "tests/main.cpp")
add_library(RenderLib STATIC ${RENDERLIB_SOURCE})

add_subdirectory(dependencies)
add_dependencies(RenderLibMainTest RenderLib)

message(WARNING ${CMAKE_SOURCE_DIR})

target_include_directories(RenderLib PUBLIC ${glm_SOURCE_DIR} glfw PUBLIC "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>")
target_link_libraries(RenderLib PUBLIC glfw assimp)

target_link_libraries(RenderLibMainTest PRIVATE RenderLib)
target_include_directories(RenderLibMainTest PRIVATE RenderLib)