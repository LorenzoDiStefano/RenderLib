#ifndef RENDERLIB_UTILS
#define RENDERLIB_UTILS

#include <filesystem>
#include <vector>
#include "../dependencies/stb_image.h"

namespace RenderLib
{

	class IModel;
	struct MeshData;

	class Utils
	{
		
	public:
		static std::unique_ptr<std::vector<std::byte>> ReadFileContent(const std::filesystem::path path);
		//set flip image
		static inline void SetImageLoadingVerticalFlip(bool flag) 
		{
			stbi_set_flip_vertically_on_load(flag);
		}
	};
	
	MeshData ImportModelAsset(std::string path);
}



#endif