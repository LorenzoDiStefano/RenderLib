#include "Utils.h"
#include <assimp/Importer.hpp>

std::unique_ptr<std::vector<std::byte>> enGino::Utils::ReadFileContent(const std::filesystem::path path)
{
	auto file_size_in_bytes = std::filesystem::file_size(path);
	auto vector_of_bytes = std::make_unique<std::vector<std::byte>>(file_size_in_bytes);

	std::ifstream file_to_read(path);


	// NOTE: unfortunately .read() still expects a char*
	/*file_to_read.read(reinterpret_cast<char*>(vector_of_bytes->data()), file_size_in_bytes);

	file_to_read.close();*/

	Assimp::Importer::ReadFile(path);

	return vector_of_bytes;
}