#ifndef RENDERLIB_OPENGL4MODEL
#define RENDERLIB_OPENGL4MODEL
#pragma once 

#include <RenderLib/IModel.hpp>
#include <RenderLib/Material.hpp>
#include "OpenGL4Texture.hpp"
#include <array>

namespace RenderLib
{
    class OpenGL4Api;

    class OpenGL4Model : public IModel
    {
    public:
        void ActivateMaterial(Material&);
        void LoadModel(ModelDescriptor&, IGPUApi&) override;

        std::vector<std::shared_ptr<IMesh>> modelMeshes;
        std::vector<Material> meshesMaterials;
        uint16_t meshesCount = 0;
    };
}

#endif // !RENDERLIB_OPENGL4MODEL