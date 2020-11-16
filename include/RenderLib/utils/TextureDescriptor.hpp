#ifndef RENDERLIB_TEXTUREDESCRIPTOR
#define RENDERLIB_TEXTUREDESCRIPTOR
#pragma once 

#include <string>

namespace RenderLib::Utils
{
    enum class TextureType
    {
        DIFFUSE,    //texture_diffuse
        SPECULAR    //texture_specular
    };

    //TextureDescriptor holds all the informations about a texture for easy loading
    struct TextureDescriptor 
    {
        TextureType type;
        std::string path;
    };
}

#endif // !RENDERLIB_TEXTUREDESCRIPTOR