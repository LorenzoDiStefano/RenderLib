#ifndef RENDERLIB_MESH_DATA
#define RENDERLIB_MESH_DATA
#include <iostream>
#include <string>
#include <vector>
#include "Vertex.hpp"
#include "Texture.hpp"

namespace RenderLib
{
	struct MeshInfo
	{
		std::vector<float> vertices;
		std::vector<float> normals;
		std::vector<float> uvs;
		std::vector<Texture> textures;
	};

	struct MeshData
	{
		// mesh data
		std::vector<Texture> texturesToLoad;
		std::string directory;
		uint16_t meshesCount;
		std::vector<MeshInfo> meshes;
	};
}

#endif