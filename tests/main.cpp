#include <iostream>
#include <RenderLib/OpenGL4Api.hpp>

int main()
{
    auto gpu = std::make_shared<RenderLib::OpenGL4Api>(512, 512, "Hello World");

	while (gpu->DequeueEvents())
	{
		gpu->Clear({ 0, 1, 0, 1 });

		gpu->Present();
	}

    return 0;

}