#ifndef RENDERLIB_MODELDESCRIPTOR
#define RENDERLIB_MODELDESCRIPTOR
#pragma once

#include <RenderLib/utils/MaterialDescriptor.hpp>
#include <RenderLib/utils/MeshDescriptor.hpp>
#include <unordered_map>

namespace RenderLib::Utils
{
	//ModelDescriptor holds all the informations about a model for easy loading by IModel
	struct ModelDescriptor
	{
		unsigned int meshesCount = 0;
		bool imageLoadingVerticalFlipFlag = false;

		std::unordered_map<unsigned int, MaterialDescriptor> materials;
		std::vector<TextureDescriptor> texturesToLoad;
		std::vector<MeshDescriptor> meshes;
		std::string directory;
	};
}

#endif // !RENDERLIB_MODELDESCRIPTOR