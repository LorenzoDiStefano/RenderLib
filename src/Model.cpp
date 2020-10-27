#include <RenderLib/Model.hpp>
#include "../src/glad.h"
#include <string>
namespace RenderLib
{
	void Model::setActiveTexture() {
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int y = 0; y < textures_loaded.size(); y++)
		{
			glActiveTexture(GL_TEXTURE0 + y); // activate proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures_loaded[y].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			glUniform1i(glGetUniformLocation(1, (name + number).c_str()), y);

			glBindTexture(GL_TEXTURE_2D, textures_loaded[y].id);
		}
		glActiveTexture(GL_TEXTURE0);
	}

}