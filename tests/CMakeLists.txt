cmake_minimum_required (VERSION 3.8)

set(gtest_force_shared_crt ON CACHE BOOL [FORCE])

set(SOURCE_TESTS

	"gtest_test.cpp"
)

add_executable(RenderLib_Tests ${SOURCE_TESTS})
add_dependencies(RenderLib_Tests RenderLib)

target_link_libraries(RenderLib_Tests PUBLIC gtest_main RenderLib)
target_include_directories(RenderLib_Tests PUBLIC RenderLib)

add_test(
	NAME RenderLib_Tests
	COMMAND RenderLib_Tests
)