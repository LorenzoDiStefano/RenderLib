#ifndef RENDERLIB_ITEXTURE
#define RENDERLIB_ITEXTURE

#include <string>

namespace RenderLib
{
	class ITexture
	{
	public:
		virtual void setActiveTexture() = 0;
		virtual void LoadImage(const char* path, const std::string& directory, bool gamma) = 0;

		unsigned int textureNumber = -1;
		std::string cachedUniformName;

	protected:
		unsigned int textureId = -1;
	};
}

#endif // !RENDERLIB_ITEXTURE
