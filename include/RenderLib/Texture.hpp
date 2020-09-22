#ifndef RENDERLIB_TEXTURE
#define RENDERLIB_TEXTURE
namespace RenderLib {
    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

}
#endif