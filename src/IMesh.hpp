#ifndef RENDERLIB_IMESH
#define RENDERLIB_IMESH

#include <vector>
#include <cstdint>

namespace RenderLib
{
	class IMesh
	{
	public:
		virtual void AddElements(const std::vector<float>& data, const uint32_t size) = 0;
		virtual void Bind() = 0;
		virtual uint32_t GetNumberOfVertices() = 0;
	};
}

#endif