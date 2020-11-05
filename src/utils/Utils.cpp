#include <RenderLib/ImageData.hpp>
#include <RenderLib/IModel.hpp>
#include <RenderLib/Vertex.hpp>
#include <RenderLib/Utils.hpp>

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <iostream>
#include <fstream>
#include <memory>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../dependencies/stb_image.h"
#endif

namespace RenderLib::Utils
{
    std::unique_ptr<std::vector<std::byte>> ReadFileContent(const std::filesystem::path path)
    {
	    auto file_size_in_bytes = std::filesystem::file_size(path);
	    auto vector_of_bytes = std::make_unique<std::vector<std::byte>>(file_size_in_bytes);

	    std::ifstream file_to_read(path);
	    file_to_read.read(reinterpret_cast<char*>(vector_of_bytes->data()), file_size_in_bytes);
	    file_to_read.close();

	    return vector_of_bytes;
    }

    std::unique_ptr<ImageData> TextureFromFile(const char* path, const std::string& directory)
    {
        auto imageInformations = std::make_unique<ImageData>();
        std::string filename = std::string(path);
        filename = directory + '/' + filename;

        auto dataPtr = stbi_load(
            filename.c_str(), &imageInformations->width,
            &imageInformations->height, &imageInformations->nrComponents, 0);

        imageInformations->data = std::make_unique<unsigned char*>(dataPtr);

        return imageInformations;
    }

    std::vector<TextureDescriptor> loadMaterialTextures(
        aiMaterial* mat, aiTextureType type, std::string typeName, 
        ModelDescriptor& modelInformations)
    {
        std::vector<TextureDescriptor> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);

            bool skip = false;
            for (unsigned int j = 0; j < modelInformations.texturesToLoad.size(); j++)
            {
                if (std::strcmp(modelInformations.texturesToLoad[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(modelInformations.texturesToLoad[j]);
                    skip = true;
                    break;
                }
            }
            if (!skip)
            {   
                // if texture hasn't been loaded already, load it
                TextureDescriptor texture;
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                // add texture informations for easy loding when necessary
                modelInformations.texturesToLoad.push_back(texture); 
            }
        }
        return textures;
    }

    MeshDescriptor processMesh(aiMesh* mesh, const aiScene* scene, ModelDescriptor& modelInformations)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<TextureDescriptor> textures;
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;

            //process vertex
            glm::vec3 vector;
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;

            //process Normal
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;

            //process texture
            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;

                //// tangent
                //vector.x = mesh->mTangents[i].x;
                //vector.y = mesh->mTangents[i].y;
                //vector.z = mesh->mTangents[i].z;
                //vertex.Tangent = vector;
                //// bitangent
                //vector.x = mesh->mBitangents[i].x;
                //vector.y = mesh->mBitangents[i].y;
                //vector.z = mesh->mBitangents[i].z;
                //vertex.Bitangent = vector;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        // process indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        MeshDescriptor result;

        // copy vertices in float array 
        for (auto index : indices)
        {
            result.vertices.push_back(vertices[index].Position.x);
            result.vertices.push_back(vertices[index].Position.y);
            result.vertices.push_back(vertices[index].Position.z);

            result.uvs.push_back(vertices[index].TexCoords.x);
            result.uvs.push_back(vertices[index].TexCoords.y);

            result.normals.push_back(vertices[index].Normal.x);
            result.normals.push_back(vertices[index].Normal.y);
            result.normals.push_back(vertices[index].Normal.z);
        }

        // process material
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<TextureDescriptor> diffuseMaps = loadMaterialTextures(material,
                aiTextureType_DIFFUSE, "texture_diffuse", modelInformations);
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<TextureDescriptor> specularMaps = loadMaterialTextures(material,
                aiTextureType_SPECULAR, "texture_specular", modelInformations);
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            
            result.textures = textures;
        }

        return result;
    }

    void processNode(aiNode* node, const aiScene* scene, ModelDescriptor& modelInformations)
    {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            modelInformations.meshes.push_back(processMesh(mesh, scene, modelInformations));
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene, modelInformations);
        }
    }

    ModelDescriptor GetModelDescriptor(std::string modelPath)
    {
        ModelDescriptor modelInformations;
        
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return modelInformations;
        }

        modelInformations.directory = modelPath.substr(0, modelPath.find_last_of('/'));
        modelInformations.meshesCount = scene->mNumMeshes;

        processNode(scene->mRootNode, scene, modelInformations);

        return modelInformations;
    }
}
