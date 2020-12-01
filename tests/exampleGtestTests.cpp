#include <gtest/gtest.h>
#include <RenderLib/utils/Transform.hpp>
#include "MockGPUApiFactory.hpp"

TEST(test_prova, subtest)
{
    //auto gpu = std::make_shared<RenderLib::OpenGL4Api>(512, 512, "Hello World");

    RenderLib::Utils::Transform testTransoform;

    auto api = MockRenderLib::CreateOGL4GPUApi(20, 20, "test");

    EXPECT_TRUE
    (
        //testTransoform.position.x == 0.0f
        api->GetWidth() == 20
    );
}
