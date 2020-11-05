#ifndef RENDERLIB_VERTEX
#define RENDERLIB_VERTEX
#pragma once

#include <glm/glm.hpp>

namespace RenderLib
{
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

}

#endif