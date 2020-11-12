#ifndef RENDERLIB_MATERIAL
#define RENDERLIB_MATERIAL

#include <RenderLib/ITexture.hpp>
#include <vector>
#include <memory>

namespace RenderLib
{
	class Material
	{
	public:
		std::vector<std::pair<std::string,std::shared_ptr<ITexture>>> textures;
	};
}

#endif // !RENDERLIB_MATERIAL
