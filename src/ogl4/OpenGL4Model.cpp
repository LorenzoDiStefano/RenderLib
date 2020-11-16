#include "OpenGL4Model.hpp"
#include "OpenGL4Api.hpp"
#include <RenderLib/IMesh.hpp>
#include <RenderLib/utils/Utils.hpp>
#include <iostream>
#include <string>

namespace RenderLib
{
	void OpenGL4Model::ActivateMaterial(Material& mat)
	{
		for each (auto tex in mat.textures)
		{
			tex.second->setActiveTexture(tex.first);
		}
	}

	//Loading vertex, normals and uvs informations from memory to the gpu
	void OpenGL4Model::LoadModel(Utils::ModelDescriptor& meshInformations, IGPUApi& gpu)
	{
		//lading vertices, normals and uvs
		meshesCount = meshInformations.meshesCount;
		for (size_t i = 0; i < meshesCount; i++)
		{
			auto triangle = gpu.CreateMesh();

			triangle->AddElements(meshInformations.meshes[i].vertices, 3);
			triangle->AddElements(meshInformations.meshes[i].normals, 3);
			triangle->AddElements(meshInformations.meshes[i].uvs, 2);
			triangle->materialIndex = meshInformations.meshes[i].materialIndex;

			modelMeshes.push_back(triangle);
		}

		auto ogl4Gpu = reinterpret_cast<OpenGL4Api*> (&gpu);

		//loading materials
		for (unsigned int y = 0; y < meshInformations.materials.size(); y++)
		{
			Material mat;

			Utils::MaterialDescriptor& matDesc = meshInformations.materials[y+1];

			//loading textures
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			unsigned int normalNr = 1;
			unsigned int heightNr = 1;

			for (unsigned int i = 0; i < matDesc.materialTextures.size(); i++)
			{
				//getting cache uniform name
				std::string cachedUniformName;

				switch (matDesc.materialTextures[i].type)
				{
				case Utils::TextureType::SPECULAR:
					cachedUniformName = "texture_specular" + std::to_string(specularNr++);
					break;
				case Utils::TextureType::DIFFUSE:
					cachedUniformName = "texture_diffuse" + std::to_string(diffuseNr++);
					break;
				default:
					break;
				}

				std::shared_ptr<ITexture> texPtr;
				auto search = ogl4Gpu->textureLoaded.find(matDesc.materialTextures[i].path);

				//if texture has not been loaded
				if (search == ogl4Gpu->textureLoaded.end())
				{
					// set flip image
					Utils::SetImageLoadingVerticalFlip(meshInformations.imageLoadingVerticalFlipFlag);

					texPtr = gpu.CreateTexture();
					texPtr->LoadImage((matDesc.materialTextures[i].path).c_str(),
						meshInformations.directory, false);

					texPtr->textureNumber = i;

					ogl4Gpu->textureLoaded[matDesc.materialTextures[i].path] = texPtr;
				}
				else
				{
					texPtr = search->second;
				}

				mat.textures.push_back(std::pair(cachedUniformName, texPtr));
				
			}

			this->meshesMaterials.push_back(mat);
		}
	}

}