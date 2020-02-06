#include "Texture.h"

namespace TEngine
{
	Texture::Texture()
		: width_(0), height_(0), format_(TexFormat::RGBA), type_(TexType::diffuse), data_(nullptr), Resource(0, "")
	{
	}

	Texture::Texture(U32 width, U32 height, TexFormat format, TexType type, unsigned char* data, U32 rId, std::string path)
		: width_(width), height_(height), format_(format), type_(type), data_(data), Resource(rId, path)
	{
	}

	TexType Texture::GetType() const
	{
		return type_;
	}

	TexFormat Texture::GetFormat() const
	{
		return format_;
	}

	U32 Texture::GetWidth() const
	{
		return width_;
	}

	U32 Texture::GetHeight() const
	{
		return height_;
	}

	unsigned char* Texture::GetDataPtr() const
	{
		return data_;
	}

	void Texture::SetType(TexType type)
	{
		this->type_ = type;
	}
}
