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
	"src/utils/MeshData.hpp"
	"src/utils/Utils.hpp"
	"src/utils/ObjParser.hpp"
	"src/utils/Model.hpp"
	"src/utils/Vertex.hpp"
)

set(RENDERLIB_SOURCE
	
	${RENDERLIB_HEADERS_HEADERS}
	"src/ogl4/OpenGL4Api.cpp"
 	"src/ogl4/OpenGL4Mesh.cpp"
	"src/glad.c"
	"src/utils/MeshData.cpp"
	"src/utils/Utils.cpp"
	"src/utils/ObjParser.cpp"
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

add_executable(RenderLibMainTest "tests/main.cpp")
add_library(RenderLib STATIC ${RENDERLIB_SOURCE})

add_subdirectory(dependencies)
add_subdirectory(tests)
add_dependencies(RenderLibMainTest RenderLib)

target_include_directories(RenderLib PUBLIC ${glm_SOURCE_DIR} glfw PUBLIC "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>")
target_link_libraries(RenderLib PUBLIC glfw assimp)

target_link_libraries(RenderLibMainTest PRIVATE RenderLib)
target_include_directories(RenderLibMainTest PRIVATE RenderLib)