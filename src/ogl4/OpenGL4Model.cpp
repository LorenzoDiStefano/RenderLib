#pragma once

#include "OpenGL4Api.hpp"
#include <string>
#include "glad.h"
#include "OpenGL4Model.hpp"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../dependencies/stb_image.h"
#endif
#include <string>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../ogl4/glad.h"
#include <RenderLib/Texture.hpp>
#include <RenderLib/IModel.hpp>
#include <RenderLib/MeshData.hpp>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <unordered_map>
#include <functional>

namespace RenderLib
{


	void IModel::setActiveTexture() {
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int y = 0; y < textures_loaded.size(); y++)
		{
			glActiveTexture(GL_TEXTURE0 + y); // activate proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures_loaded[y].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			glUniform1i(glGetUniformLocation(1, (name + number).c_str()), y);

			glBindTexture(GL_TEXTURE_2D, textures_loaded[y].id);
		}
		glActiveTexture(GL_TEXTURE0);
	}

	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma, const MeshData& loadedInformations)
	{
		std::string filename = std::string(path);
		filename = directory + '/' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format = GL_RED;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}

		return textureID;
	}


	//Loading vertex, normals and uvs informations from memory to the gpu
	void OpenGL4Model::LoadMeshes(MeshData& meshInformations, const IGPUApi& gpu)
	{
		meshesCount = meshInformations.meshesCount;
		for (size_t i = 0; i < meshInformations.meshesCount; i++)
		{
			auto triangle = gpu.CreateMesh();
			triangle->AddElements(meshInformations.meshes[i].vertices, 3);
			triangle->AddElements(meshInformations.meshes[i].normals, 3);
			triangle->AddElements(meshInformations.meshes[i].uvs, 2);
			modelMeshes.push_back(triangle);
		}

		for (unsigned int i = 0; i < meshInformations.texturesToLoad.size(); i++)
		{
			meshInformations.texturesToLoad[i].id = 
				TextureFromFile((meshInformations.texturesToLoad[i].path).c_str(), 
				meshInformations.directory, false, meshInformations);

			textures_loaded.push_back(meshInformations.texturesToLoad[i]);
		}
	}

}