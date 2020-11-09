#include "OpenGL4Texture.hpp"
#include "glad.h"

#include <iostream>
#include <RenderLib/Utils.hpp>

namespace RenderLib
{
	void OpenGl4Texture::setActiveTexture()
	{
		glActiveTexture(GL_TEXTURE0 + textureNumber); // activate proper texture unit before binding
		glUniform1i(glGetUniformLocation(1, (cachedUniformName).c_str()), textureNumber);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void OpenGl4Texture::LoadImage(const char* path, const std::string& directory, bool gamma)
	{
		glGenTextures(1, &textureId);

		//get information of image loaded from disk
		auto imageInformations = Utils::TextureFromFile(path, directory);
		//get pointer to texture data loaded from disk
		auto imageInformationsDataPtr = *(imageInformations->data.get());

		if (imageInformationsDataPtr)
		{
			GLenum format = GL_RED;
			if (imageInformations->nrComponents == 1)
				format = GL_RED;
			else if (imageInformations->nrComponents == 3)
				format = GL_RGB;
			else if (imageInformations->nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, format, imageInformations->width,
				imageInformations->height, 0, format, GL_UNSIGNED_BYTE,
				imageInformationsDataPtr);

			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
		}
	}
}