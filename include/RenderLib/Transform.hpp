#ifndef RENDERLIB_TRANSFORM
#define RENDERLIB_TRANSFORM

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace RenderLib {

	struct  Transform
	{
		glm::vec3 position;
		glm::vec3 rotation = glm::vec3(0.0f);
		glm::vec3 scale = glm::vec3(1.0f);

		glm::mat4x4 getTransformModel();
	};
}
#endif