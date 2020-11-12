#include "OpenGL4Texture.hpp"
#include "OpenGL4Model.hpp"
#include "OpenGL4Mesh.hpp"
#include "OpenGL4Api.hpp"
#include "glad.h"
#include <iostream>

namespace RenderLib
{
	class GPUPipeline
	{
	public:
		GLuint program_id;
		GLint model_location;
		GLint view_location;
		GLint projection_location;
		GLint light_location;
		//friend class OpenGL4Api;
	};

	OpenGL4Api::OpenGL4Api(const uint32_t width, const uint32_t height, const std::string title) :
		width(width),
		height(height),
		close(false)
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(window);
		gladLoadGL();

		glViewport(0, 0, width, height);

		glEnable(GL_DEPTH_TEST);

		// assign this to the user data of GLFWWindow
		glfwSetWindowUserPointer(window, this);

		glfwSetWindowCloseCallback(window, [](GLFWwindow* _window)
			{
				auto myself = reinterpret_cast<OpenGL4Api*>(glfwGetWindowUserPointer(_window));
				myself->close = true;
			});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* _window, int width, int height)
			{
				auto myself = reinterpret_cast<OpenGL4Api*>(glfwGetWindowUserPointer(_window));
				myself->width = width;
				myself->height = height;
				glViewport(0, 0, myself->GetWidth(), myself->GetHeight());
			});
	}

	const bool OpenGL4Api::DequeueEvents()
	{
		glfwPollEvents();
		return !close;
	}

	void OpenGL4Api::Present()
	{
		glfwSwapBuffers(window);
	}

	void OpenGL4Api::Clear(const glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	std::shared_ptr<IMesh> OpenGL4Api::CreateMesh() const
	{
		return std::make_shared<OpenGL4Mesh>();
	}

	std::shared_ptr<IMesh> OpenGL4Api::CreateMesh()
	{
		return std::make_shared<OpenGL4Mesh>();
	}

	std::shared_ptr<IModel> OpenGL4Api::CreateModel() const
	{
		return std::make_shared<OpenGL4Model>();
	}

	std::shared_ptr<IModel> OpenGL4Api::CreateModel()
	{
		return std::make_shared<OpenGL4Model>();
	}

	std::shared_ptr<ITexture> OpenGL4Api::CreateTexture() const
	{
		return std::make_shared<OpenGl4Texture>();
	}

	std::shared_ptr<ITexture> OpenGL4Api::CreateTexture()
	{
		return std::make_shared<OpenGl4Texture>();
	}

	void OpenGL4Api::Draw(std::shared_ptr<GPUPipeline> pipeline, std::shared_ptr<IMesh> mesh, glm::mat4& model, glm::mat4& view, glm::mat4& projection, glm::vec3& light)
	{
		glUseProgram(pipeline->program_id);
		mesh->Bind();
		glUniformMatrix4fv(pipeline->model_location, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(pipeline->view_location, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(pipeline->projection_location, 1, GL_FALSE, &projection[0][0]);
		glUniform3f(pipeline->light_location, light.x, light.y, light.z);
		glDrawArrays(GL_TRIANGLES, 0, mesh->GetNumberOfVertices());
	}

	void OpenGL4Api::Draw(std::shared_ptr<GPUPipeline> pipeline, std::shared_ptr<IModel> meshModel, glm::mat4& model, glm::mat4& view, glm::mat4& projection, glm::vec3& light)
	{
		auto castedModel = reinterpret_cast<OpenGL4Model*> (meshModel.get());

		for (size_t i = 0; i < castedModel->meshesCount; i++)
		{
			auto mesh = castedModel->modelMeshes[i];
			auto meshMat = castedModel->meshesMaterials[mesh->materialIndex];
			castedModel->ActivateMaterial(meshMat);

			Draw(pipeline, mesh, model, view, projection, light);
		}

		//only usefull when rendering models without textures
		//it should not be needed since a bind "overwrites" the state of what textures are active
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	std::shared_ptr<RenderLib::GPUPipeline> OpenGL4Api::CreatePipeline(const std::string vertex_shader_code, const std::string pixel_shader_code)
	{
		auto pipeline = std::make_shared<RenderLib::GPUPipeline>();
		pipeline->program_id = glCreateProgram();

		auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		auto vertex_shader_c_source = vertex_shader_code.c_str();
		const GLint vertex_shader_c_source_size = static_cast<GLint>(vertex_shader_code.size());
		glShaderSource(vertex_shader, 1, &vertex_shader_c_source, &vertex_shader_c_source_size);
		glCompileShader(vertex_shader);

		// check if the compilation failed
		GLint compile_status;
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
		if (!compile_status)
		{
			char info_log[512];
			glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
			/* retrieve the size of the info log before reading it
			GLsizei log_size;
			glGetShaderInfoLog(vertex_shader, 0, &log_size, nullptr);
			*/
			std::cerr << info_log << std::endl;
			throw std::exception(info_log);
		}

		auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		auto fragment_shader_c_source = pixel_shader_code.c_str();
		const GLint fragment_shader_c_source_size = static_cast<GLint>(pixel_shader_code.size());
		glShaderSource(fragment_shader, 1, &fragment_shader_c_source, &fragment_shader_c_source_size);
		glCompileShader(fragment_shader);
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
		if (!compile_status)
		{
			char info_log[512];
			glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
			std::cerr << info_log << std::endl;
			throw std::exception(info_log);
		}

		glAttachShader(pipeline->program_id, vertex_shader);
		glAttachShader(pipeline->program_id, fragment_shader);

		glLinkProgram(pipeline->program_id);

		glDetachShader(pipeline->program_id, vertex_shader);
		glDetachShader(pipeline->program_id, fragment_shader);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		pipeline->model_location = glGetUniformLocation(pipeline->program_id, "model");
		pipeline->view_location = glGetUniformLocation(pipeline->program_id, "view");
		pipeline->projection_location = glGetUniformLocation(pipeline->program_id, "projection");
		pipeline->light_location = glGetUniformLocation(pipeline->program_id, "light_direction");

		return pipeline;
	}
}