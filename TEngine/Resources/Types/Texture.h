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
			U32 width,
			U32 height,
			TexFormat format,
			TexType type,
			unsigned char* data,
			U32 r_id,
			std::string path
		);

		TexType GetType() const;
		TexFormat GetFormat() const;
		U32 GetWidth() const;
		U32 GetHeight() const;
		unsigned char* GetDataPtr() const;

		void SetType(TexType type);

	protected:
		TexType type_;
		TexFormat format_;
		U32 width_;
		U32 height_;
		unsigned char* data_;
	};
}
