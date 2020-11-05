#include <RenderLib/ModelDescriptor.hpp>
#include <RenderLib/IModel.hpp>
#include <RenderLib/IMesh.hpp>
#include <iostream>
#include <string>

#include "OpenGL4Model.hpp"
#include "OpenGL4Api.hpp"
#include "glad.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../dependencies/stb_image.h"
#endif

namespace RenderLib
{
	//This should be in Ogl4Texture
	void IModel::setActiveTexture()
	{
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

	//This should not be here, dont load image data from disk in the ogl4 model class
	//a part of this sould be in utils and the rest in Ogl4Texture
	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma, const ModelDescriptor& loadedInformations)
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
	void OpenGL4Model::LoadModel(ModelDescriptor& meshInformations, const IGPUApi& gpu)
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