#include <RenderLib/GPUApiFactory.hpp>
#include "ogl4/OpenGL4Api.hpp"

namespace RenderLib
{
	std::shared_ptr<IGPUApi> CreateOGL4GPUApi(const uint32_t width, const uint32_t height, const std::string title)
	{
		return std::make_shared<RenderLib::OpenGL4Api>(width, height, title);
	}
}