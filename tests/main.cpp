#include <iostream>
#include <RenderLib/OpenGL4Api.hpp>
#include <RenderLib/OpenGL4Mesh.hpp>
#include <RenderLib/Utils.hpp>

int main()
{
	// AAA Almost Always Auto
	// Dangling pointers
	auto gpu = std::make_shared<RenderLib::OpenGL4Api>(1024, 1024, "Hello World");

	auto vertex_shader_path = std::filesystem::path("shaders/sprite_vertex.glsl");
	auto pixel_shader_path = std::filesystem::path("shaders/sprite_pixel.glsl");

	auto vertex_shader_code = RenderLib::Utils::ReadFileContent(vertex_shader_path);
	auto pixel_shader_code = RenderLib::Utils::ReadFileContent(pixel_shader_path);

	auto pipeline = gpu->CreatePipeline(
		std::string(reinterpret_cast<char*>(vertex_shader_code->data()), vertex_shader_code->size()),
		std::string(reinterpret_cast<char*>(pixel_shader_code->data()), pixel_shader_code->size())
	);

	auto triangle = gpu->CreateMesh();

	
	
	RenderLib::Model stormtropper_model;
	RenderLib::loadModel("assets/peasant_man.fbx", stormtropper_model);
	

	triangle->AddElements(stormtropper_model.meshes[0].vertices, 3);
	triangle->AddElements(stormtropper_model.meshes[0].normals, 3);
	triangle->AddElements(stormtropper_model.meshes[0].uvs, 2);

	glm::vec3 position = { 0, 0, 0 };

	glm::vec3 camera = { 0 , 150.5f, 350 };

	glm::vec3 light_direction = { 0, 0, -1 };

	float roty = 0;



	while (gpu->DequeueEvents())
	{
		auto projection = glm::perspective(glm::degrees(60.0f), static_cast<float>(gpu->GetWidth()) / static_cast<float>(gpu->GetHeight()), 0.01f, 1000.0f);


		roty += 0.001f;

		auto model = glm::translate(glm::mat4(1), position) *
			glm::rotate(glm::mat4(1), glm::degrees(roty), { 0, 1, 0 });

		//model = glm::scale(model, glm::vec3(0.5f));

		auto view = glm::translate(glm::mat4(1), -camera);

		gpu->Clear({ 0, 1, 0, 1 });

		gpu->Draw(pipeline, triangle, model, view, projection, light_direction);

		gpu->Present();
	}

	return 0;
}