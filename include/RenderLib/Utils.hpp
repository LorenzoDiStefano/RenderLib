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

namespace RenderLib
{
	class Utils
	{
	public:
		static std::unique_ptr<std::vector<std::byte>> ReadFileContent(const std::filesystem::path path);
	};
}

#endif