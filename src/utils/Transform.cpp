#include <RenderLib/utils/Transform.hpp>

namespace RenderLib::Utils
{
	glm::mat4x4 Transform::getTransformModel()
	{
		auto modelTransform = glm::translate(glm::mat4(1), position)*
			glm::rotate(glm::mat4(1), glm::degrees(rotation.y), { 0, 1, 0 });
		modelTransform = glm::scale(modelTransform, glm::vec3(0.3f));
		
		return modelTransform;
	}

}