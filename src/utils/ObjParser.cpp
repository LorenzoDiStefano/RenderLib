#include <Windows.h>
#include <RenderLib/Utils.hpp>
#include <RenderLib/OpenGL4Api.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ObjParser
{
	/*
		v -0.544744 2.718269 -0.216881  vertici
		vt 1.170400 0.832200     UV
		vn -0.737600 0.301100 -0.604400   normali
		f 275/387/275 280/392/280 273/385/273  facce



	*/

public:
	ObjParser(const std::filesystem::path filename)
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

	~ObjParser() = default;

	ObjParser(const ObjParser& other) = delete;
	ObjParser& operator=(const ObjParser& other) = delete;

	ObjParser(ObjParser&& other) = delete;
	ObjParser& operator=(const ObjParser&& other) = delete;

	std::vector<float>& get_vertices() { return vertices; }
	std::vector<float>& get_normals() { return normals; }
	std::vector<float>& get_uvs() { return uvs; }

protected:

	template<typename T, size_t N>
	const std::array<T, N> split(const std::string& line)
	{
		std::string skip;
		std::stringstream sstream(line);
		std::array<T, N> result;
		sstream >> skip;

		for (auto i = 0; i < N; i++)
		{
			sstream >> result[i];
		}

		return result;
	}

	template<typename T, size_t N>
	const std::array<T, N> split_by_delimiter(const std::string& line, const char separator)
	{
		std::array<T, N> result;
		std::stringstream sstream(line);

		for (auto i = 0; i < N; i++)
		{
			std::string item;
			std::getline(sstream, item, separator);
			std::stringstream itemstream(item);
			itemstream >> result[i];
		}
		return result;

	}

	const std::vector<std::string> get_lines(std::ifstream& stream)
	{
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(stream, line))
		{
			lines.push_back(line);
		}
		return lines;
	}

	const std::string get_first_word(const std::string line)
	{
		std::string first_word;
		std::stringstream sstream(line);

		sstream >> first_word;

		return first_word;
	}

	std::vector<std::array<float, 3>> raw_vertices;
	std::vector<std::array<float, 3>> raw_normals;
	std::vector<std::array<float, 2>> raw_uvs;

	std::vector<std::array<std::array<size_t, 3>, 3>> indices;

	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> uvs;
};