#ifndef RENDERLIB_GPUFACTORY
#define RENDERLIB_GPUFACTORY
#pragma once

#include <RenderLib/IGPUApi.hpp>

//factory to hide gpu apis
namespace RenderLib
{
	std::shared_ptr<IGPUApi> CreateOGL4GPUApi(const uint32_t width, const uint32_t height, const std::string title);
	//create dx11 api
	//IGPUApi CreateOGL4GPUApi();
	//create dx12 api
	//IGPUApi CreateOGL4GPUApi();
}

#endif // !RENDERLIB_GPUFACTORY
