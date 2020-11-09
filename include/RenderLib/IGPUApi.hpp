#ifndef RENDERLIB_IGPU_API
#define RENDERLIB_IGPU_API
#pragma once 

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include <memory>
#include <string>

/*
Interface for GPU api abstraction
*/
namespace RenderLib
{
	class GPUPipeline;
	class IModel;
	class IMesh;
	class ITexture;

	class IGPUApi
	{
	public:
		IGPUApi(const IGPUApi& other) = delete;
		IGPUApi(IGPUApi&& other) = delete;
		IGPUApi& operator=(const IGPUApi& other) = delete;
		IGPUApi& operator=(IGPUApi&& other) = delete;

		// return window/screen dimensions
		virtual const uint32_t GetWidth() const = 0;
		virtual const uint32_t GetHeight() const = 0;

		// dequeue all window/context events
		virtual const bool DequeueEvents() = 0;
		// submit rendered framebuffer/texture to the window/screen
		virtual void Present() = 0;

		// clear the current window/screen backbuffer
		virtual void Clear(const glm::vec4 color) = 0;

		// create a rasterizer pipeline (shaders, blending, root signatures, drawing modes...)
		virtual std::shared_ptr<GPUPipeline> CreatePipeline(const std::string vertex_shader_code, const std::string pixel_shader_code) = 0;

		// a mesh is a series of gpu buffers, with the 0 one containing the geometry vertices
		virtual std::shared_ptr<IMesh> CreateMesh() const = 0;
		virtual std::shared_ptr<IMesh> CreateMesh() = 0;

		//
		virtual std::shared_ptr<IModel> CreateModel() const = 0;
		virtual std::shared_ptr<IModel> CreateModel() = 0;

		//
		virtual std::shared_ptr<ITexture> CreateTexture() const = 0;
		virtual std::shared_ptr<ITexture> CreateTexture() = 0;

		// submit a draw call with the specified pipeline and data
		virtual void Draw(std::shared_ptr<GPUPipeline> pipeline, std::shared_ptr<IMesh> mesh, glm::mat4& model, glm::mat4& view, glm::mat4& projection, glm::vec3& light) = 0;
		virtual void Draw(std::shared_ptr<GPUPipeline> pipeline, std::shared_ptr<IModel> meshModel, glm::mat4& model, glm::mat4& view, glm::mat4& projection, glm::vec3& light) = 0;

	protected:
		// "abstract" class (in the C#/Java sense)
		IGPUApi() = default;
	};
}

#endif