#include <Windows.h>
#include <RenderLib/Utils.hpp>
#include <RenderLib/OpenGL4Api.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace RenderLib
{

	class ObjParser
	{
		/*
			v -0.544744 2.718269 -0.216881  vertici
			vt 1.170400 0.832200     UV
			vn -0.737600 0.301100 -0.604400   normali
			f 275/387/275 280/392/280 273/385/273  facce



		*/
	public:
		ObjParser(const std::filesystem::path filename);

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

		// get lines .obj files
		const std::vector<std::string> get_lines(std::ifstream& stream);

		// get first line word (v or vt or vn or f)
		const std::string get_first_word(const std::string line);

		std::vector<std::array<float, 3>> raw_vertices;
		std::vector<std::array<float, 3>> raw_normals;
		std::vector<std::array<float, 2>> raw_uvs;

		std::vector<std::array<std::array<size_t, 3>, 3>> indices;

		std::vector<float> vertices;
		std::vector<float> normals;
		std::vector<float> uvs;
	};
}