#ifndef RENDERLIB_MESH_DATA
#define RENDERLIB_MESH_DATA
#include <iostream>
#include <vector>
#include "Vertex.hpp"

namespace RenderLib
{
	struct MeshData
	{
		MeshData() = default;
		~MeshData() = default;
		
		
	public:
		// mesh data

		std::vector<float> vertices;
		std::vector<float> normals;
		std::vector<float> uvs;
		//std::vector<Texture> textures;
	};
}

#endif