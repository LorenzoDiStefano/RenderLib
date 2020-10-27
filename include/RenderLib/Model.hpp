#ifndef RENDERLIB_MODEL
#define RENDERLIB_MODEL
#include <iostream>
#include <vector>
#include "MeshData.hpp"


namespace RenderLib
{
    class Model
    {
    public:
        Model() = default;
        ~Model() = default;
        // model data
        std::vector<MeshData> meshes;
        std::string directory;
        std::vector<Texture> textures_loaded;
        int meshCount = 0;

        void setActiveTexture();
    };
}
#endif