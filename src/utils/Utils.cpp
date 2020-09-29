#include <RenderLib/Utils.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../dependencies/stb_image.h"
#endif



std::unique_ptr<std::vector<std::byte>> RenderLib::Utils::ReadFileContent(const std::filesystem::path path)
{
	auto file_size_in_bytes = std::filesystem::file_size(path);
	auto vector_of_bytes = std::make_unique<std::vector<std::byte>>(file_size_in_bytes);

	std::ifstream file_to_read(path);


	
	file_to_read.read(reinterpret_cast<char*>(vector_of_bytes->data()), file_size_in_bytes);

	file_to_read.close();


	return vector_of_bytes;
}

namespace RenderLib
{

    unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma)
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


    
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, Model& model)
    {
        std::vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            bool skip = false;
            for (unsigned int j = 0; j < model.textures_loaded.size(); j++)
            {
                if (std::strcmp(model.textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(model.textures_loaded[j]);
                    skip = true;
                    break;
                }
            }
            if (!skip)
            {   // if texture hasn't been loaded already, load it
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(), model.directory,false);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                model.textures_loaded.push_back(texture); // add to loaded textures
            }
        }
        return textures;
    }



    MeshData processMesh(aiMesh* mesh, const aiScene* scene, Model& model)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
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

        MeshData result;


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
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
                aiTextureType_DIFFUSE, "texture_diffuse", model);
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<Texture> specularMaps = loadMaterialTextures(material,
                aiTextureType_SPECULAR, "texture_specular", model);
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            
            result.textures = textures;
        }

        return result;
    }


    void processNode(aiNode* node, const aiScene* scene, Model& model)
    {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            model.meshes.push_back(processMesh(mesh, scene, model));
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene, model);
        }
    }



    void loadModel(std::string path, Model& model)
    {
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        model.directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene, model);
    }

}