#pragma once
#include "../../Core/PortableTypes.h"
#include "Character.h"
#include <map>
#include <string>

namespace TEngine
{
	class Font
	{
	public:
		Font(std::string name, std::string file);

		Character GetCharacter(char c) const;

		void Load();

		std::string GetFilePath() const;
		std::string GetName() const;

		/**
		* Returns the default engine font_ (does NOT need to be deleted after)
		**/
		static Font* GetDefaultFont();

	private:
		std::map<char, Character> character_map_;

		const std::string file_;
		const std::string name_;

		bool is_loaded_ = false;
	};
}
