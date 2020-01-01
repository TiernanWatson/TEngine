#pragma once
#include "../Resource.h"

namespace TEngine
{
	enum class TexType
	{
		diffuse,
		specular,
		normal,
		height
	};

	enum class TexFormat
	{
		R,
		RGB,
		RGBA
	};

	class Texture : public Resource
	{
	public:
		Texture();
		Texture(
			uint32 width,
			uint32 height,
			TexFormat format,
			TexType type,
			unsigned char* data,
			uint32 rId,
			std::string path
		);

		TexType GetType() const;
		TexFormat GetFormat() const;
		uint32 GetWidth() const;
		uint32 GetHeight() const;
		unsigned char* GetDataPtr() const;

		void SetType(TexType type);

	protected:
		TexType type;
		TexFormat format;
		uint32 width;
		uint32 height;
		unsigned char* data;
	};
}
