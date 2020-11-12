#ifndef RENDERLIB_MATERIALDESCRIPTOR
#define RENDERLIB_MATERIALDESCRIPTOR

#include <RenderLib/TextureDescriptor.hpp>
#include <vector>

namespace RenderLib
{
	struct MaterialDescriptor
	{
		std::vector<TextureDescriptor> materialTextures;
	};
}

#endif // !RENDERLIB_MATERIALDESCRIPTOR
