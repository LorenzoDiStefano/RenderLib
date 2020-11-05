#ifndef RENDERLIB_MESHDESCRIPTOR
#define RENDERLIB_MESHDESCRIPTOR
#pragma once 

#include <RenderLib/TextureDescriptor.hpp>
#include <vector>

namespace RenderLib
{
	//MeshDescriptor holds all the informations about a mesh
	struct MeshDescriptor
	{
		std::vector<float> vertices;
		std::vector<float> normals;
		std::vector<float> uvs;
		std::vector<TextureDescriptor> textures;
	};
}

#endif