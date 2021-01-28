#include <iostream>
#include <RenderLib/GPUApiFactory.hpp>
#include <RenderLib/IModel.hpp>
#include <RenderLib/IMesh.hpp>
#include <RenderLib/utils/Utils.hpp>
#include <RenderLib/ITexture.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <RenderLib/utils/Transform.hpp>
#include "../src/ogl4/glad.h"

int main()
{
	// AAA Almost Always Auto
	// Dangling pointers
	auto gpu = RenderLib::CreateOGL4GPUApi(1024, 1024, "Hello World");

	auto vertexShaderPath = std::filesystem::path("shaders/VertexShader.glsl");
	auto pixelShader2DPath = std::filesystem::path("shaders/FragmentShader2D.glsl");
	auto pixelShaderPath = std::filesystem::path("shaders/FragmentShader.glsl");

	auto vertexShaderCode = RenderLib::Utils::ReadFileContent(vertexShaderPath);
	auto pixelShaderCode = RenderLib::Utils::ReadFileContent(pixelShaderPath);
	auto pixelShader2DCode = RenderLib::Utils::ReadFileContent(pixelShader2DPath);

	auto pipeline = gpu->CreatePipeline(
		std::string(reinterpret_cast<char*>(vertexShaderCode->data()), vertexShaderCode->size()),
		std::string(reinterpret_cast<char*>(pixelShaderCode->data()), pixelShaderCode->size()));

	auto pipeline2D = gpu->CreatePipeline(
		std::string(reinterpret_cast<char*>(vertexShaderCode->data()), vertexShaderCode->size()),
		std::string(reinterpret_cast<char*>(pixelShader2DCode->data()), pixelShader2DCode->size()));

	auto eyeballModel = gpu->CreateModel();
	auto backpackModel = gpu->CreateModel();
	//std::vector<glm::vec3> vegetationVerteces;
	{
		auto eyeballModelDescriptor = RenderLib::Utils::GetModelDescriptor("assets/eyeball.obj");
		auto backpackModelDescriptor = RenderLib::Utils::GetModelDescriptor("assets/backpack.obj");

		backpackModelDescriptor->imageLoadingVerticalFlipFlag = true;

		eyeballModel->LoadModel(*eyeballModelDescriptor, *gpu);
		backpackModel->LoadModel(*backpackModelDescriptor, *gpu);

	}


	glm::vec3 camera = { 0, 1.5f, 6 };
	glm::vec3 lightDirection = { 0, 0, -1 };

	RenderLib::Utils::Transform transformEyeballModel;
	RenderLib::Utils::Transform transformBackpackModel;
	transformEyeballModel.position = { 0, 2.0f, 0 };
	transformBackpackModel.position = { 0, 0, 0 };

	//setting up custom 3Dobject for grass

	std::vector<float> floatVegetationVerterces = {
		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f,  0.5f,  0.0f,
		0.0f, -0.5f,  0.0f,
		1.0f, -0.5f,  0.0f,

		0.0f,  0.5f,  0.0f,
		1.0f, -0.5f,  0.0f,
		1.0f,  0.5f,  0.0f

	};

	std::vector<float> floatVegetetionsUV = {
		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f,  0.0f,
		0.0f,  1.0f,
		1.0f,  1.0f,

		0.0f,  0.0f,
		1.0f,  1.0f,
		1.0f,  0.0f
	};

	std::vector<float> floatVegetetionsNormal = {
		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
		1.0f, 1.0f,1.0f,
		1.0f, 1.0f,1.0f,
		1.0f, 1.0f,1.0f,

		1.0f, 1.0f,1.0f,
		1.0f, 1.0f,1.0f,
		1.0f, 1.0f,1.0f
	};

	RenderLib::Utils::MaterialDescriptor grassMat;
	RenderLib::Utils::TextureDescriptor grassText;
	RenderLib::Utils::ModelDescriptor grassDescriptor;
	RenderLib::Utils::MeshDescriptor grassMesh;

	grassMesh.materialIndex = 0;
	grassMesh.normals = floatVegetetionsNormal;
	grassMesh.vertices = floatVegetationVerterces;
	grassMesh.uvs = floatVegetetionsUV;

	grassText.type = RenderLib::Utils::TextureType::DIFFUSE;
	grassText.path = "blending_window.png";

	grassMat.materialTextures.push_back(grassText);

	grassDescriptor.directory = "assets";
	grassDescriptor.imageLoadingVerticalFlipFlag = false;
	grassDescriptor.materials[1] = grassMat;
	grassDescriptor.meshes.push_back(grassMesh);
	grassDescriptor.meshesCount = 1;
	grassDescriptor.texturesToLoad.push_back(grassText);

	auto grassModel = gpu->CreateModel();
	grassModel->LoadModel(grassDescriptor, *gpu);

	while (gpu->DequeueEvents())
	{
		auto projection = glm::perspective(
			glm::degrees(60.0f), static_cast<float>(gpu->GetWidth()) / static_cast<float>(gpu->GetHeight()),
			0.01f, 1000.0f);

		transformEyeballModel.rotation.y += 0.001f;
		transformBackpackModel.rotation.y += 0.0002f;
		//transformBackpackModel.scale = glm::vec3(5.0f);

		auto model = transformBackpackModel.getTransformModel();
		//model = glm::scale(model, glm::vec3(0.5f));
		auto model2 = transformEyeballModel.getTransformModel();

		auto view = glm::translate(glm::mat4(1), -camera);

		gpu->Clear({ 0, 1, 0, 1 });
		gpu->SetAlphaBlending(false);
		
		gpu->Draw(pipeline, backpackModel, glm::scale(model, glm::vec3(0.3f)), view, projection, lightDirection);
		gpu->Draw(pipeline, eyeballModel, glm::scale(model2, glm::vec3(0.3f)), view, projection, lightDirection);
		
		gpu->SetAlphaBlending(true);

		gpu->Draw(pipeline2D, grassModel, model, view, projection, lightDirection);

		gpu->Present();
	}

	return 0;
}