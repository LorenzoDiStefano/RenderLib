#include <iostream>
#include <RenderLib/GPUApiFactory.hpp>
#include <RenderLib/IModel.hpp>
#include <RenderLib/IMesh.hpp>
#include <RenderLib/Utils.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <RenderLib/Transform.hpp>

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

	glm::vec3 camera = { 0, 1.5f, 6 };
	glm::vec3 lightDirection = { 0, 0, -1 };


	RenderLib::Transform transformEyeballModel;
	RenderLib::Transform transformBackpackModel;
	transformEyeballModel.position = { 0, 2.0f, 0 };
	transformBackpackModel.position = { 0, 0, 0 };


	while (gpu->DequeueEvents())
	{
		auto projection = glm::perspective(
			glm::degrees(60.0f), static_cast<float>(gpu->GetWidth()) / static_cast<float>(gpu->GetHeight()),
			0.01f, 1000.0f);


		transformEyeballModel.rotation.y += 0.001f;
		transformBackpackModel.rotation.y += 0.001f;

		auto model = transformBackpackModel.getTransformModel();
		//model = glm::scale(model, glm::vec3(0.5f));
		auto model2 = transformEyeballModel.getTransformModel();

		auto view = glm::translate(glm::mat4(1), -camera);

		gpu->Clear({ 0, 1, 0, 1 });

		gpu->Draw(pipeline, backpackModel, model, view, projection, lightDirection);
		gpu->Draw(pipeline, eyeballModel, model2, view, projection, lightDirection);

		gpu->Present();
	}

	return 0;
}