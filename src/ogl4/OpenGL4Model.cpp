#include "OpenGL4Model.hpp"
#include "OpenGL4Api.hpp"

#include <RenderLib/IMesh.hpp>
#include <RenderLib/Utils.hpp>

#include <iostream>
#include <string>


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

	unsigned int OpenGL4Model::LoadImage(const char* path, const std::string& directory, bool gamma)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);

		//call texture from file
		auto imageInformations = RenderLib::Utils::TextureFromFile(path, directory);

		if (*(imageInformations->data.get()))
		{
			GLenum format = GL_RED;
			if (imageInformations->nrComponents == 1)
				format = GL_RED;
			else if (imageInformations->nrComponents == 3)
				format = GL_RGB;
			else if (imageInformations->nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, imageInformations->width, 
				imageInformations->height, 0, format, GL_UNSIGNED_BYTE, 
				*(imageInformations->data.get()));

			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
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
				LoadImage((meshInformations.texturesToLoad[i].path).c_str(),
				meshInformations.directory, false);

			textures_loaded.push_back(meshInformations.texturesToLoad[i]);
		}
	}

}