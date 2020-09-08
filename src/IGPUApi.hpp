#ifndef RENDERLIB_IGPU_API
#define RENDERLIB_IGPU_API

#include <cstdint>
#include <memory>
#include <string>
#include <functional>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

/*
Interface for GPU api abstraction

*/
namespace RenderLib
{

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

	protected:
		// "abstract" class (in the C#/Java sense)
		IGPUApi() = default;
	};
}

#endif