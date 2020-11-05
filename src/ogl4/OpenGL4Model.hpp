#ifndef RENDERLIB_MODEL
#define RENDERLIB_MODEL
#pragma once 

#include <RenderLib/IModel.hpp>

namespace RenderLib
{
    class OpenGL4Api;

    class OpenGL4Model : public IModel
    {
    public:
        //void setActiveTexture() override;
        void LoadModel(ModelDescriptor&, const IGPUApi&) override;
    };
}

#endif