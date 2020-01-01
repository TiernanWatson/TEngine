#pragma once
#include "../PortableTypes.h"
#include <string>

namespace TEngine
{
	/**
	* Configuration variable holding atomic types, 4-byte aligned
	**/
	class ConfigVar
	{
	public:
		ConfigVar() : str("") {}
		ConfigVar(char* str) : str(str) {}
		ConfigVar(std::string str) : str(str) {}

		inline std::string GetValue() const
		{
			return str;
		}

		inline bool GetBool() const
		{
			return str == "true" ? true : false;
		}

		inline uint32 GetInt() const
		{
			return std::atoi(str.c_str());
		}

		inline float32 GetFloat() const
		{
			return (float32)std::atof(str.c_str());
		}

	private:
		std::string str;
	};
}
