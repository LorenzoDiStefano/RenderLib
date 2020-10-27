#ifndef RENDERLIB_UTILS
#define RENDERLIB_UTILS

#include <memory>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <unordered_map>
#include <functional>
#include "../src/utils/ObjParser.hpp"
#include "Model.hpp"
#include "../dependencies/stb_image.h"

namespace RenderLib
{
	class Utils
	{
		
	public:
		static std::unique_ptr<std::vector<std::byte>> ReadFileContent(const std::filesystem::path path);
		//set flip image
		static inline void setImageVerticalFlip(bool flag) {
			stbi_set_flip_vertically_on_load(flag);
		}
	};
	
	void loadModel(std::string path, Model& model);
}



#endif