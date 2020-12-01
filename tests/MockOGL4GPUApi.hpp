#include <RenderLib/IGPUApi.hpp>

namespace MockRenderLib
{
	class MockOGL4GPUApi : public RenderLib::IGPUApi
	{
	public:

		MockOGL4GPUApi(const uint32_t myWidth, const uint32_t myHeight, const std::string myTitle)
		{
			width = myWidth;
			height = myHeight;
		}

		const uint32_t GetWidth() const override { return width; }
		const uint32_t GetHeight() const override { return height; }

		const bool DequeueEvents() override { return false; }
		void Present() override {}

		void Clear(const glm::vec4 color) override{}

		std::shared_ptr<RenderLib::GPUPipeline> CreatePipeline(const std::string vertex_shader_code, const std::string pixel_shader_code) override
		{
			return nullptr;
		}

		std::shared_ptr<RenderLib::IMesh> CreateMesh() const override { return nullptr; }
		std::shared_ptr<RenderLib::IMesh> CreateMesh() override { return nullptr; }

		std::shared_ptr<RenderLib::IModel> CreateModel() const override { return nullptr; }
		std::shared_ptr<RenderLib::IModel> CreateModel() override { return nullptr; }

		std::shared_ptr<RenderLib::ITexture> CreateTexture() const override { return nullptr; }
		std::shared_ptr<RenderLib::ITexture> CreateTexture() override { return nullptr; }

		void Draw(std::shared_ptr<RenderLib::GPUPipeline> pipeline, std::shared_ptr<RenderLib::IMesh> mesh, glm::mat4& model, glm::mat4& view, glm::mat4& projection, glm::vec3& light) override {}
		void Draw(std::shared_ptr<RenderLib::GPUPipeline> pipeline, std::shared_ptr<RenderLib::IModel> meshModel, glm::mat4& model, glm::mat4& view, glm::mat4& projection, glm::vec3& light) override {}

	private:
		void* window;

		uint32_t width;
		uint32_t height;
		bool close;

	};

}