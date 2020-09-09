#include "ObjParser.hpp"
namespace RenderLib
{

	ObjParser::ObjParser(const std::filesystem::path filename)
	{
		std::ifstream objfile(filename);
		auto lines = get_lines(objfile);
		objfile.close();

		std::unordered_map<std::string, std::function<void(const std::string&)>> pattern_matching
		{
			{ "v", [&](auto line) { raw_vertices.push_back(split<float, 3>(line)); }},
			{ "vn", [&](auto line) {raw_normals.push_back(split<float, 3>(line)); }},
			{ "vt", [&](auto line) {raw_uvs.push_back(split<float, 2>(line)); }},
			{"f", [&](auto line)
				{
					auto line_to_indices = split<std::string, 3>(line);
					indices.push_back(
					{
						split_by_delimiter<size_t, 3>(line_to_indices[0], '/'),
						split_by_delimiter<size_t, 3>(line_to_indices[1], '/'),
						split_by_delimiter<size_t, 3>(line_to_indices[2], '/')
					});
				}
			}
		};

		for (auto line : lines)
		{
			auto it = pattern_matching.find(get_first_word(line));
			if (it != pattern_matching.end())
			{
				// pattern_matching["v"](line)
				it->second(line);
			}
		}

		for (auto& face : indices)
		{
			for (auto i = 0; i < 3; i++)
			{
				auto vindex = face[i][0]; vindex--;
				vertices.push_back(raw_vertices[vindex][0]);
				vertices.push_back(raw_vertices[vindex][1]);
				vertices.push_back(raw_vertices[vindex][2]);

				auto vtindex = face[i][1]; vtindex--;
				uvs.push_back(raw_uvs[vtindex][0]);
				uvs.push_back(raw_uvs[vtindex][1]);

				auto vnindex = face[i][2]; vnindex--;
				normals.push_back(raw_normals[vnindex][0]);
				normals.push_back(raw_normals[vnindex][1]);
				normals.push_back(raw_normals[vnindex][2]);
			}
		}

	}



	const std::vector<std::string> ObjParser::get_lines(std::ifstream& stream)
	{
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(stream, line))
		{
			lines.push_back(line);
		}
		return lines;
	}



	const std::string ObjParser::get_first_word(const std::string line)
	{
		std::string first_word;
		std::stringstream sstream(line);

		sstream >> first_word;

		return first_word;
	}

}