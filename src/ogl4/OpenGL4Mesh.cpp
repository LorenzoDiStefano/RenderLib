#include <RenderLib/OpenGL4Mesh.hpp>
#include <iostream>

namespace RenderLib {

	RenderLib::OpenGL4Mesh::OpenGL4Mesh() : number_of_vertices(0)
	{
		glGenVertexArrays(1, &vao);
	}

	RenderLib::OpenGL4Mesh::~OpenGL4Mesh()
	{
		glDeleteVertexArrays(1, &vao);
	}

	void RenderLib::OpenGL4Mesh::AddElements(const std::vector<float>& data, const uint32_t size)
	{
		glBindVertexArray(vao);
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(static_cast<GLuint>(vbos.size()));
		// set how buffer data are passed to the shader: example {1,2,3,4} can be passed as a couple of floats -> T0={1,2} T1={3,4}
		glVertexAttribPointer(static_cast<GLuint>(vbos.size()), size, GL_FLOAT, GL_FALSE, 0, nullptr);

		if (vbos.size() == 0)
		{
			number_of_vertices = static_cast<uint32_t>(data.size()) / size;
		}

		vbos.push_back(vbo);
	}

	void RenderLib::OpenGL4Mesh::Bind()
	{
		glBindVertexArray(vao);
	}


}
