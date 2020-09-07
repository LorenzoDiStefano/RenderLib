cmake_minimum_required (VERSION 3.8)

include(FetchContent)

set(FETCHCONTENT_QUIET ON)

#Including for glm
#Downloading glm from git
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG			0.9.9.8
)

FetchContent_GetProperties(glm)

if(NOT glm_POPULATED)
	FetchContent_Populate(glm)
	add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()

#Required from glfw
find_package(OpenGL REQUIRED)

#Including for glfw
#Downloading glfw from git
FetchContent_Declare(
	glfw
	GIT_REPOSITORY	https://github.com/glfw/glfw.git
	GIT_TAG			3.3.2
)

FetchContent_GetProperties(glfw)

if(NOT glfw_POPULATED)
	FetchContent_Populate(glfw)
	add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()


#Including assimp
#Downloading assimp from git
FetchContent_Declare(
	assimp
	GIT_REPOSITORY	https://github.com/assimp/assimp.git
	GIT_TAG			v5.0.1
)

FetchContent_GetProperties(assimp)

if(NOT assimp_POPULATED)
	FetchContent_Populate(assimp)
	set(ASSIMP_BUILD_STATIC_LIB ON)
	add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
endif()