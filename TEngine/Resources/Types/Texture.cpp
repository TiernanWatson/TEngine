#include "Texture.h"

namespace TEngine
{
	Texture::Texture()
		: width(0), height(0), format(TexFormat::RGBA), type(TexType::diffuse), data(nullptr), Resource(0, "")
	{
	}

	Texture::Texture(uint32 width, uint32 height, TexFormat format, TexType type, unsigned char* data, uint32 rId, std::string path)
		: width(width), height(height), format(format), type(type), data(data), Resource(rId, path)
	{
	}

	TexType Texture::GetType() const
	{
		return type;
	}

	TexFormat Texture::GetFormat() const
	{
		return format;
	}

	uint32 Texture::GetWidth() const
	{
		return width;
	}

	uint32 Texture::GetHeight() const
	{
		return height;
	}

	unsigned char* Texture::GetDataPtr() const
	{
		return data;
	}

	void Texture::SetType(TexType type)
	{
		this->type = type;
	}
}
