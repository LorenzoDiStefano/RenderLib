#ifndef RENDERLIB_TEXTUREDESCRIPTOR
#define RENDERLIB_TEXTUREDESCRIPTOR
#pragma once 

#include <string>

namespace RenderLib 
{
    //TextureDescriptor holds all the informations about a texture for easy loading
    struct TextureDescriptor 
    {
        unsigned int id;
        std::string type;
        std::string path;
    };
}

#endif