//#include <iostream>
//#include <RenderLib/GPUApiFactory.hpp>
//#include <RenderLib/IModel.hpp>
//#include <RenderLib/IMesh.hpp>
//#include <RenderLib/utils/Utils.hpp>
//#include <RenderLib/ITexture.hpp>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <RenderLib/utils/Transform.hpp>
//
//int main()
//{
//	// AAA Almost Always Auto
//	// Dangling pointers
//	auto gpu = RenderLib::CreateOGL4GPUApi(1024, 1024, "Hello World");
//
//	auto vertexShaderPath = std::filesystem::path("shaders/sprite_vertex.glsl");
//	auto pixelShaderPath = std::filesystem::path("shaders/grass.glsl");
//
//	auto vertexShaderCode = RenderLib::Utils::ReadFileContent(vertexShaderPath);
//	auto pixelShaderCode = RenderLib::Utils::ReadFileContent(pixelShaderPath);
//
//	auto pipeline = gpu->CreatePipeline(
//		std::string(reinterpret_cast<char*>(vertexShaderCode->data()), vertexShaderCode->size()),
//		std::string(reinterpret_cast<char*>(pixelShaderCode->data()), pixelShaderCode->size()));
//
//	auto eyeballModel = gpu->CreateModel();
//	auto backpackModel = gpu->CreateModel();
//	//std::vector<glm::vec3> vegetationVerteces;
//	{
//		auto eyeballModelDescriptor = RenderLib::Utils::GetModelDescriptor("assets/eyeball.obj");
//		auto backpackModelDescriptor = RenderLib::Utils::GetModelDescriptor("assets/backpack.obj");
//
//		backpackModelDescriptor->imageLoadingVerticalFlipFlag = true;
//
//		eyeballModel->LoadModel(*eyeballModelDescriptor, *gpu);
//		backpackModel->LoadModel(*backpackModelDescriptor, *gpu);
//
//		/*	vegetationVerteces.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
//			vegetationVerteces.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
//			vegetationVerteces.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
//			vegetationVerteces.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
//			vegetationVerteces.push_back(glm::vec3(0.5f, 0.0f, -0.6f));*/
//
//	}
//
//
//
//
//	glm::vec3 camera = { 0, 1.5f, 6 };
//	glm::vec3 lightDirection = { 0, 0, -1 };
//
//
//	RenderLib::Utils::Transform transformEyeballModel;
//	RenderLib::Utils::Transform transformBackpackModel;
//	transformEyeballModel.position = { 0, 2.0f, 0 };
//	transformBackpackModel.position = { 0, 0, 0 };
//
//
//	std::vector<float> floatVegetationVerterces = {
//		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
//		  5.0f, -0.5f,  5.0f,
//		-5.0f, -0.5f,  5.0f,
//		-5.0f, -0.5f, -5.0f,
//
//		 5.0f, -0.5f,  5.0f,
//		-5.0f, -0.5f, -5.0f,
//		 5.0f, -0.5f, -5.0f
//	};
//
//
//
//	auto grassMesh = gpu->CreateMesh();
//	grassMesh->AddElements(floatVegetationVerterces, 3);
//	auto grassTexture = gpu->CreateTexture();
//	grassTexture->LoadImage("grass.png", "assets", false);
//
//
//	while (gpu->DequeueEvents())
//	{
//		auto projection = glm::perspective(
//			glm::degrees(60.0f), static_cast<float>(gpu->GetWidth()) / static_cast<float>(gpu->GetHeight()),
//			0.01f, 1000.0f);
//
//
//		transformEyeballModel.rotation.y += 0.001f;
//		transformBackpackModel.rotation.y += 0.001f;
//
//		auto model = transformBackpackModel.getTransformModel();
//		//model = glm::scale(model, glm::vec3(0.5f));
//		auto model2 = transformEyeballModel.getTransformModel();
//
//		auto view = glm::translate(glm::mat4(1), -camera);
//
//		gpu->Clear({ 0, 1, 0, 1 });
//
//		//gpu->Draw(pipeline, backpackModel, model, view, projection, lightDirection);
//		//gpu->Draw(pipeline, eyeballModel, model2, view, projection, lightDirection);
//
//		grassTexture->setActiveTexture(std::string("texture1"));
//		gpu->Draw(pipeline, grassMesh, model, view, projection, lightDirection);
//
//		gpu->Present();
//	}
//
//	return 0;
//}