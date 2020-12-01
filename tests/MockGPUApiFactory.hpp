#ifndef MOCK_RENDERLIB_GPUFACTORY
#define MOCK_RENDERLIB_GPUFACTORY
#pragma once

#include <RenderLib/IGPUApi.hpp>
#include "MockOGL4GPUApi.hpp"

//factory to hide gpu apis
namespace MockRenderLib
{
	std::shared_ptr<RenderLib::IGPUApi> CreateOGL4GPUApi(const uint32_t width, const uint32_t height, const std::string title)
	{
		return std::make_shared<MockOGL4GPUApi>(width, height, title);
	}
	//create dx11 api
	//IGPUApi CreateOGL4GPUApi();
	//create dx12 api
	//IGPUApi CreateOGL4GPUApi();
}

#endif // !RENDERLIB_GPUFACTORY
