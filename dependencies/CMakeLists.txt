cmake_minimum_required (VERSION 3.8)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)

#Looking for glm
find_package(GLM)

if(GLM_FOUND)
	message("GLM included at ${GLM_INCLUDE_DIR}")
else()
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
endif()

#looking for glfw
find_package(OpenGL REQUIRED)
find_package(GLFW3)

if(GLFW3_FOUND)
	message("Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
else()
	#Downloading glm from git
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
endif()