#ifndef RENDERLIB_OPENGL4TEXTURE
#define RENDERLIB_OPENGL4TEXTURE

#include <RenderLib/ITexture.hpp>

namespace RenderLib
{
	class OpenGl4Texture : public ITexture
	{
	public:
		void setActiveTexture(std::string& uniform) override;
		void LoadImage(const char* path, const std::string& directory, bool gamma) override;
	};
}

#endif // !RENDERLIB_OPENGL4TEXTURE
