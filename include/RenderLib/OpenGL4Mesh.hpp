#ifndef RENDERLIB_OPENGL4_MESH
#define RENDERLIB_OPENGL4_MESH
#include "../IMesh.hpp"
#include "OpenGL4Api.hpp"
#include <GLFW/glfw3.h>
#include <string>

namespace RenderLib
{
	class OpenGL4Mesh : public IMesh
	{
	public:
		OpenGL4Mesh();
		~OpenGL4Mesh();
		void AddElements(const std::vector<float>& data, const uint32_t size) override;
		void Bind() override;
		uint32_t GetNumberOfVertices() override {
			return number_of_vertices;
		};
	private:
		GLuint vao;
		std::vector<GLuint> vbos;
		uint32_t number_of_vertices;
	};

}
#endif