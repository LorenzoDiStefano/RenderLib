#include <gtest/gtest.h>
#include <RenderLib/OpenGL4Api.hpp>

TEST(gtest_test, test)
{
    auto gpu = std::make_shared<RenderLib::OpenGL4Api>(512, 512, "Hello World");

    EXPECT_TRUE
    (
        true == true
    );
}