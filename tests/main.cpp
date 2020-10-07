#include <iostream>
#include <RenderLib/OpenGL4Api.hpp>
#include <RenderLib/OpenGL4Mesh.hpp>
#include <RenderLib/Utils.hpp>
#include "../dependencies/stb_image.h"


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
	
	stbi_set_flip_vertically_on_load(true);

	RenderLib::Model stormtropper_model;
	RenderLib::loadModel("assets/backpack.obj", stormtropper_model);
	
	std::vector<std::shared_ptr<RenderLib::IMesh>> modelMeshes;
	for (size_t i = 0; i < stormtropper_model.meshCount; i++)
	{
		auto triangle = gpu->CreateMesh();
		triangle->AddElements(stormtropper_model.meshes[i].vertices, 3);
		triangle->AddElements(stormtropper_model.meshes[i].normals, 3);
		triangle->AddElements(stormtropper_model.meshes[i].uvs, 2);
		modelMeshes.push_back(triangle);
	}

	glm::vec3 position = { 0, 0, 0 };

	glm::vec3 camera = { 0 ,1.5f, 6 };

	glm::vec3 light_direction = { 0, 0, -1 };

	float roty = 0;

	while (gpu->DequeueEvents())
	{
		auto projection = glm::perspective(glm::degrees(60.0f), static_cast<float>(gpu->GetWidth()) / static_cast<float>(gpu->GetHeight()), 0.01f, 1000.0f);


		roty += 0.00001f;

		auto model = glm::translate(glm::mat4(1), position) *
			glm::rotate(glm::mat4(1), glm::degrees(roty), { 0, 1, 0 });
		model = glm::scale(model, glm::vec3(0.5f));
		//model = glm::scale(model, glm::vec3(0.5f));

		auto view = glm::translate(glm::mat4(1), -camera);

		gpu->Clear({ 0, 1, 0, 1 });

		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int y = 0; y < stormtropper_model.textures_loaded.size(); y++)
		{
			glActiveTexture(GL_TEXTURE0 + y); // activate proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = stormtropper_model.textures_loaded[y].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			glUniform1i(glGetUniformLocation(1, (name + number).c_str()), y);

			//shader.setFloat(("material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, stormtropper_model.textures_loaded[y].id);
		}
		glActiveTexture(GL_TEXTURE0);

		for (size_t i = 0; i < stormtropper_model.meshCount; i++)
		{
			gpu->Draw(pipeline, modelMeshes[i], model, view, projection, light_direction);
		}

		gpu->Present();
	}

	return 0;
}