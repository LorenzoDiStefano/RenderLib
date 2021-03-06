#ifndef RENDERLIB_MESHDESCRIPTOR
#define RENDERLIB_MESHDESCRIPTOR
#pragma once 

#include <RenderLib/utils/TextureDescriptor.hpp>
#include <vector>

namespace RenderLib::Utils
{
	//MeshDescriptor holds all the informations about a mesh
	struct MeshDescriptor
	{
		std::vector<float> vertices;
		std::vector<float> normals;
		std::vector<float> uvs;

		unsigned int materialIndex;
	};
}

#endif // !RENDERLIB_MESHDESCRIPTOR