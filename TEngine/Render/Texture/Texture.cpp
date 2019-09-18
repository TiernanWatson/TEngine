#include "Texture.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <stdexcept>
#include "../../External/stb_image.h"
#include <iostream>

namespace TEngine
{
	Texture::Texture(const std::string& filePath, TexType type)
		: path(filePath), type(type)
	{
	}

	void Texture::Load()
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		uint8* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

		//std::cout << "trying path: " << path << std::endl;

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			this->width = width;
			this->height = height;
			this->nrChannels = nrChannels;
		}
		else
		{
			throw std::exception("Texture::Load: Could not load texture!");
		}

		stbi_image_free(data);
	}

	void Texture::Unload()
	{
		glDeleteTextures(1, &id);
		id = 0;
	}

	void Texture::Use()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}
}
