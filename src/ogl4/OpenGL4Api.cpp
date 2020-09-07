#include "OpenGL4Api.hpp"
#include <iostream>

RenderLib::OpenGL4Api::OpenGL4Api(const uint32_t width, const uint32_t height, const std::string title) :
	width(width),
	height(height),
	close(false)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, width, height);

	// assign this to the user data of GLFWWindow
	glfwSetWindowUserPointer(window, this);

	glfwSetWindowCloseCallback(window, [](GLFWwindow* _window)
		{
			auto myself = reinterpret_cast<RenderLib::OpenGL4Api*>(glfwGetWindowUserPointer(_window));
			myself->close = true;
		});
}

const bool RenderLib::OpenGL4Api::DequeueEvents()
{
	glfwPollEvents();
	return !close;
}

void RenderLib::OpenGL4Api::Present()
{
	glfwSwapBuffers(window);
}

void RenderLib::OpenGL4Api::Clear(const glm::vec4 color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

namespace RenderLib
{
	class GPUPipeline
	{
	public:
		GLuint program_id;
		GLint mvp_location;
		friend class OpenGL4Api;
	};
}

