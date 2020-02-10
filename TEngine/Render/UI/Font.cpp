#include "Font.h"
#include "../../Engine.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <sstream>

namespace TEngine
{
	Font::Font(std::string name, std::string file)
		: file_(file), name_(name)
	{
	}

	Character Font::GetCharacter(char c) const
	{
		return character_map_.at(c);
	}

	void Font::Load()
	{
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			throw std::exception("FONT::Load: Could not init FreeType Library");

		FT_Face face;
		if (FT_New_Face(ft, file_.c_str(), 0, &face))
			throw std::exception("Font::Load: Failed to load font_");

		FT_Set_Pixel_Sizes(face, 0, 12);

		// Load in the ASCII set
		for (U8 c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				throw std::exception("ERROR::Load: Failed to load Glyph" + c);
				continue;
			}

			Texture* tex = new Texture(
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				TexFormat::R,
				TexType::diffuse,
				face->glyph->bitmap.buffer,
				0,
				""
			);

			/*Texture tex(
				face->glyph->bitmap.width_,
				face->glyph->bitmap.rows,
				TexFormat::R,
				TexType::diffuse_,
				face->glyph->bitmap.buffer,
				0,
				""
			);*/
			
			Character character = {
				new DXTexture(Engine::Get().GetRenderer(), tex),
				face->glyph->advance.x,
				Vector2Int(face->glyph->bitmap_left, face->glyph->bitmap_top),
				Vector2Int(face->glyph->bitmap.width, face->glyph->bitmap.rows)
			};

			character_map_[c] = character;
		}

		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		is_loaded_ = true;
	}

	std::string Font::GetFilePath() const
	{
		return file_;
	}

	std::string Font::GetName() const
	{
		return name_;
	}

	Font* Font::GetDefaultFont()
	{
		static Font f("Lucida Consoles", "D:\\TEngine\\TEngine\\Resources\\Fonts\\lucon.ttf");
		if (!f.is_loaded_) f.Load();

		return &f;
	}
}
