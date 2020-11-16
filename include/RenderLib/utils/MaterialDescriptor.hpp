#ifndef RENDERLIB_MATERIALDESCRIPTOR
#define RENDERLIB_MATERIALDESCRIPTOR

#include <RenderLib/utils/TextureDescriptor.hpp>
#include <vector>

namespace RenderLib::Utils
{
	struct MaterialDescriptor
	{
		std::vector<TextureDescriptor> materialTextures;
	};
}

#endif // !RENDERLIB_MATERIALDESCRIPTOR
