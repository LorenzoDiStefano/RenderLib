#include <iostream>
#include <RenderLib/GPUApiFactory.hpp>
#include <RenderLib/IModel.hpp>
#include <RenderLib/IMesh.hpp>
#include <RenderLib/Utils.hpp>
#include <RenderLib/MeshData.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
	// AAA Almost Always Auto
	// Dangling pointers
	auto gpu = RenderLib::CreateOGL4GPUApi(1024, 1024, "Hello World");

	auto vertex_shader_path = std::filesystem::path("shaders/sprite_vertex.glsl");
	auto pixel_shader_path = std::filesystem::path("shaders/sprite_pixel.glsl");

	auto vertex_shader_code = RenderLib::Utils::ReadFileContent(vertex_shader_path);
	auto pixel_shader_code = RenderLib::Utils::ReadFileContent(pixel_shader_path);

	auto pipeline = gpu->CreatePipeline(
		std::string(reinterpret_cast<char*>(vertex_shader_code->data()), vertex_shader_code->size()),
		std::string(reinterpret_cast<char*>(pixel_shader_code->data()), pixel_shader_code->size())
	);

	// set flip image
	RenderLib::Utils::SetImageLoadingVerticalFlip(true);

	auto stormtropper_model = gpu->CreateModel();

	RenderLib::MeshData assetLoadedData = RenderLib::Utils::ImportModelAsset("assets/backpack.obj");

	stormtropper_model->LoadMeshes(assetLoadedData, *gpu);

	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 camera = { 0 ,1.5f, 6 };
	glm::vec3 light_direction = { 0, 0, -1 };

	float roty = 0;

	while (gpu->DequeueEvents())
	{
		auto projection = glm::perspective(
			glm::degrees(60.0f), static_cast<float>(gpu->GetWidth()) / static_cast<float>(gpu->GetHeight()), 
			0.01f, 1000.0f);


		roty += 0.00001f;

		auto model = glm::translate(glm::mat4(1), position) *
			glm::rotate(glm::mat4(1), glm::degrees(roty), { 0, 1, 0 });
		model = glm::scale(model, glm::vec3(0.5f));
		//model = glm::scale(model, glm::vec3(0.5f));

		auto view = glm::translate(glm::mat4(1), -camera);

		gpu->Clear({ 0, 1, 0, 1 });

		// active texture 
		stormtropper_model->setActiveTexture();

		for (size_t i = 0; i < stormtropper_model->meshesCount; i++)
		{
			gpu->Draw(pipeline, stormtropper_model->modelMeshes[i], model, view, projection, light_direction);
		}

		gpu->Present();
	}

	return 0;
}