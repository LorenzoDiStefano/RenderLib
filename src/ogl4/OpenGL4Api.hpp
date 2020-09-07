#ifndef RENDERLIB_OPENGL4_API
#define RENDERLIB_OPENGL4_API

#include "../IGPUApi.hpp"
#include "../glad.h"
#include <GLFW/glfw3.h>
#include <string>

namespace RenderLib
{
	class OpenGL4Api : public IGPUApi
	{
	public:
		OpenGL4Api(const uint32_t width, const uint32_t height, const std::string title);
		const uint32_t GetWidth() const override { return width; }
		const uint32_t GetHeight() const override { return height; }

		const bool DequeueEvents() override;
		void Present() override;

		void Clear(const glm::vec4 color) override;


	private:
		GLFWwindow* window;
		const uint32_t width;
		const uint32_t height;
		bool close;
	};
}

#endif