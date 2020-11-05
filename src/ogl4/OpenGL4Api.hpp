#ifndef RENDERLIB_OPENGL4_API
#define RENDERLIB_OPENGL4_API
#pragma once

#include <RenderLib/IGPUApi.hpp>
//glad.h must ALWAYS be included before GLFW
#include "glad.h"
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

		std::shared_ptr<GPUPipeline> CreatePipeline(const std::string vertex_shader_code, const std::string pixel_shader_code) override;

		std::shared_ptr<IMesh> CreateMesh() const override;
		std::shared_ptr<IModel> CreateModel() override;

		void Draw(std::shared_ptr<GPUPipeline> pipeline, std::shared_ptr<IMesh> mesh, glm::mat4& model, glm::mat4& view, glm::mat4& projection, glm::vec3& light) override;

	private:
		GLFWwindow* window;
		uint32_t width;
		uint32_t height;
		bool close;
	};
}

#endif