#ifndef RENDERLIB_IMAGEDATA
#define RENDERLIB_IMAGEDATA
#pragma once 

#include <memory>

namespace RenderLib
{
    struct ImageData
    {
        int width = -1;
        int height = -1;
        int nrComponents = -1;

        std::unique_ptr<unsigned char*> data;
    };
}

#endif // !RENDERLIB_IMAGEDATA