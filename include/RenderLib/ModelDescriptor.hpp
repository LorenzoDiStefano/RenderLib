#ifndef RENDERLIB_MODELDESCRIPTOR
#define RENDERLIB_MODELDESCRIPTOR
#pragma once

#include <RenderLib/MeshDescriptor.hpp>

namespace RenderLib
{
	//ModelDescriptor holds all the informations about a model for easy loading by IModel
	struct ModelDescriptor
	{
		unsigned int meshesCount = 0;
		std::vector<TextureDescriptor> texturesToLoad;
		std::vector<MeshDescriptor> meshes;
		std::string directory;
	};
}

#endif