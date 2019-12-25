#include "Font.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace TEngine
{
	Font::Font(std::string name, std::string file)
		: file(file), name(name)
	{
	}

	Character Font::GetCharacter(char c) const
	{
		return characterMap.at(c);
	}

	void Font::Load()
	{
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			throw std::exception("FONT::Load: Could not init FreeType Library");

		FT_Face face;
		if (FT_New_Face(ft, file.c_str(), 0, &face))
			throw std::exception("Font::Load: Failed to load font");

		FT_Set_Pixel_Sizes(face, 0, 12);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Textures stored just as one byte

		// Load in the ASCII set
		for (uint8 c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				throw std::exception("ERROR::Load: Failed to load Glyph" + c);
				continue;
			}

			uint32 texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			Character character = {
				texture,
				face->glyph->advance.x,
				Vector2Int(face->glyph->bitmap_left, face->glyph->bitmap_top),
				Vector2Int(face->glyph->bitmap.width, face->glyph->bitmap.rows)
			};

			characterMap[c] = character;
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Reset

		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		isLoaded = true;
	}

	std::string Font::GetFilePath() const
	{
		return file;
	}

	std::string Font::GetName() const
	{
		return name;
	}

	Font* Font::GetDefaultFont()
	{
		static Font f("Lucida Consoles", "D:\\TEngine\\TEngine\\Resources\\Fonts\\lucon.ttf");
		if (!f.isLoaded) f.Load();

		return &f;
	}
}
