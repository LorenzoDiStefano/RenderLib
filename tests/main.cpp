#include <iostream>
#include <RenderLib/GPUApiFactory.hpp>
#include <RenderLib/IModel.hpp>
#include <RenderLib/IMesh.hpp>
#include <RenderLib/Utils.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
	// AAA Almost Always Auto
	// Dangling pointers
	auto gpu = RenderLib::CreateOGL4GPUApi(1024, 1024, "Hello World");

	auto vertexShaderPath = std::filesystem::path("shaders/sprite_vertex.glsl");
	auto pixelShaderPath = std::filesystem::path("shaders/sprite_pixel.glsl");

	auto vertexShaderCode = RenderLib::Utils::ReadFileContent(vertexShaderPath);
	auto pixelShaderCode = RenderLib::Utils::ReadFileContent(pixelShaderPath);

	auto pipeline = gpu->CreatePipeline(
		std::string(reinterpret_cast<char*>(vertexShaderCode->data()), vertexShaderCode->size()),
		std::string(reinterpret_cast<char*>(pixelShaderCode->data()), pixelShaderCode->size()));

	auto eyeballModel = gpu->CreateModel();
	auto backpackModel = gpu->CreateModel();

	{
		auto eyeballModelDescriptor = RenderLib::Utils::GetModelDescriptor("assets/eyeball.obj");
		auto backpackModelDescriptor = RenderLib::Utils::GetModelDescriptor("assets/backpack.obj");

		backpackModelDescriptor->imageLoadingVerticalFlipFlag = true;

		eyeballModel->LoadModel(*eyeballModelDescriptor, *gpu);
		backpackModel->LoadModel(*backpackModelDescriptor, *gpu);
	}

	glm::vec3 backpackPosition = { 0, 0, 0 };
	glm::vec3 eyeballPosition = { 0, 2.0f, 0 };
	glm::vec3 camera = { 0, 1.5f, 6 };
	glm::vec3 lightDirection = { 0, 0, -1 };

	float roty = 0;

	while (gpu->DequeueEvents())
	{
		auto projection = glm::perspective(
			glm::degrees(60.0f), static_cast<float>(gpu->GetWidth()) / static_cast<float>(gpu->GetHeight()),
			0.01f, 1000.0f);

		roty += 0.001f;

		auto model = glm::translate(glm::mat4(1), backpackPosition) *
			glm::rotate(glm::mat4(1), glm::degrees(roty), { 0, 1, 0 });
		model = glm::scale(model, glm::vec3(0.3f));
		//model = glm::scale(model, glm::vec3(0.5f));

		auto model2 = glm::translate(glm::mat4(1), eyeballPosition) *
			glm::rotate(glm::mat4(1), glm::degrees(roty), { 0, 1, 0 });
		model2 = glm::scale(model2, glm::vec3(0.3f));

		auto view = glm::translate(glm::mat4(1), -camera);

		gpu->Clear({ 0, 1, 0, 1 });

		gpu->Draw(pipeline, backpackModel, model, view, projection, lightDirection);
		gpu->Draw(pipeline, eyeballModel, model2, view, projection, lightDirection);

		gpu->Present();
	}

	return 0;
}