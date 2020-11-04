#ifndef RENDERLIB_MODEL
#define RENDERLIB_MODEL
#include <iostream>
#include <vector>
#include <RenderLib/IModel.hpp>
#include <RenderLib/IMesh.hpp>

namespace RenderLib
{
    class OpenGL4Api;

    class OpenGL4Model : public IModel
    {
    public:

        void LoadMeshes(MeshData&, const IGPUApi&) override;
    };
}
#endif