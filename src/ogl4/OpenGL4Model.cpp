#include "OpenGL4Model.hpp"
#include "OpenGL4Api.hpp"
#include <RenderLib/IMesh.hpp>
#include <RenderLib/Utils.hpp>
#include <iostream>
#include <string>

namespace RenderLib
{
	void OpenGL4Model::ActivateTextures()
	{
		for each (auto tex in loadedTextures)
		{
			tex->setActiveTexture();
		}
	}

	//Loading vertex, normals and uvs informations from memory to the gpu
	void OpenGL4Model::LoadModel(ModelDescriptor& meshInformations, const IGPUApi& gpu)
	{
		//lading vertices, normals and uvs
		meshesCount = meshInformations.meshesCount;
		for (size_t i = 0; i < meshesCount; i++)
		{
			auto triangle = gpu.CreateMesh();
			triangle->AddElements(meshInformations.meshes[i].vertices, 3);
			triangle->AddElements(meshInformations.meshes[i].normals, 3);
			triangle->AddElements(meshInformations.meshes[i].uvs, 2);
			modelMeshes.push_back(triangle);
		}

		//loading textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;

		for (unsigned int i = 0; i < meshInformations.texturesToLoad.size(); i++)
		{
			//creating texture and asking for image loading
			auto tex = gpu.CreateTexture();
			tex->LoadImage((meshInformations.texturesToLoad[i].path).c_str(),
				meshInformations.directory, false);

			//getting information to cache
			std::string number;
			std::string name = meshInformations.texturesToLoad[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);

			//caching texture info
			tex->textureNumber = i;
			tex->cachedUniformName = (name + number).c_str();

			//saving loaded texture needed
			loadedTextures.push_back(tex);
		}
	}

}