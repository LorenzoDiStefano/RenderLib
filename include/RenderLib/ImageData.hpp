#ifndef RENDERLIB_IMAGEDATA
#define RENDERLIB_IMAGEDATA
#pragma once 

#include <memory>

namespace RenderLib
{
    struct ImageData
    {
        int width;
        int height;
        int nrComponents;

        std::unique_ptr<unsigned char*> data;
    };
}

#endif // !RENDERLIB_IMAGEDATA