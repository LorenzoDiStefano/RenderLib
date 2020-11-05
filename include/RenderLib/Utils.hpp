#ifndef RENDERLIB_UTILS
#define RENDERLIB_UTILS
#pragma once

#include <filesystem>
#include <vector>

#include "../dependencies/stb_image.h"

struct RenderLib::ModelDescriptor;

namespace RenderLib::Utils
{
	std::unique_ptr<std::vector<std::byte>> ReadFileContent(const std::filesystem::path path);
	ModelDescriptor GetModelDescriptor(std::string path);

	//used to set stbi flag for vertical flip of images
	inline void SetImageLoadingVerticalFlip(bool flag) 
	{
		stbi_set_flip_vertically_on_load(flag);
	}
}

#endif