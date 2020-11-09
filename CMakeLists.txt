cmake_minimum_required (VERSION 3.8)

project ("RenderLib" VERSION 0.0.1)

message("Starting setup")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "/Od" )

set(RENDERLIB_HEADERS
	"dependencies/stb_image.h"
	"src/ogl4/glad.h"
	"src/ogl4/khrplatform.h"
	"src/ogl4/OpenGL4Api.hpp"
 	"src/ogl4/OpenGL4Mesh.hpp"
	"src/ogl4/OpenGL4Model.hpp"
	"src/ogl4/OpenGL4Texture.hpp"
	"src/utils/ImageData.hpp"
)

set(RENDERLIB_SOURCE
	${RENDERLIB_HEADERS_HEADERS}
	"src/ogl4/glad.c"
	"src/ogl4/OpenGL4Api.cpp"
 	"src/ogl4/OpenGL4Mesh.cpp"
	"src/ogl4/OpenGL4Model.cpp"
	"src/ogl4/OpenGL4Texture.cpp"
	"src/utils/Utils.cpp"
	"src/GPUApiFactory.cpp"
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

add_custom_command(TARGET RenderLibMainTest PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/assets #<--- copy files in this folder
		${PROJECT_BINARY_DIR}/assets/) #<--- into this path

add_custom_command(TARGET RenderLibMainTest PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/src/shaders #<--- copy files in this folder
		${PROJECT_BINARY_DIR}/shaders/) #<--- into this path