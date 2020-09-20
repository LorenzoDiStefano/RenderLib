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
		MeshData(std::vector<Vertex> vertices, std::vector<unsigned int> indices) :vertices{ vertices }, indices{indices}{}
		
	public:
		// mesh data
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		std::vector<float> _vertices;
		std::vector<float> _normals;
		std::vector<float> _uvs;
		//std::vector<Texture> textures;
	};
}

#endif