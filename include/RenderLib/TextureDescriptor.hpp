#ifndef RENDERLIB_TEXTUREDESCRIPTOR
#define RENDERLIB_TEXTUREDESCRIPTOR
#pragma once 

#include <string>
#include <memory>

namespace RenderLib 
{
    //TextureDescriptor holds all the informations about a texture for easy loading
    struct TextureDescriptor 
    {
        std::string type;
        std::string path;
    };
}

#endif