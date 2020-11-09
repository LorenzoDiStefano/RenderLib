#ifndef RENDERLIB_MODEL
#define RENDERLIB_MODEL
#pragma once 

#include <RenderLib/IModel.hpp>
#include "OpenGL4Texture.hpp"

namespace RenderLib
{
    class OpenGL4Api;

    class OpenGL4Model : public IModel
    {
    public:
        void ActivateTextures() override;
        void LoadModel(ModelDescriptor&, const IGPUApi&) override;

        std::vector<std::shared_ptr<IMesh>> modelMeshes;
        std::vector<std::shared_ptr<ITexture>> loadedTextures;
        uint16_t meshesCount = 0;
    };
}

#endif