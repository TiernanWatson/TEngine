#pragma once
#include "../PortableTypes.h"
#include "ConfigVar.h"
#include <unordered_map>

#define CONFIG_INT32(section, name, fallback) TEngine::Config::Instance().GetVar(section, name, fallback).GetInt()
#define CONFIG_FLOAT32(section, name, fallback) TEngine::Config::Instance().GetVar(section, name, fallback).GetFloat()
#define CONFIG_BOOL(section, name, fallback) TEngine::Config::Instance().GetVar(section, name, fallback).GetBool()
#define CONFIG_STRING(section, name, fallback) TEngine::Config::Instance().GetVar(section, name, fallback).GetValue()
#define CONFIG_VAL(section, name, fallback) TEngine::Config::Instance().GetVar(section, name, fallback)

namespace TEngine
{
	class Config
	{
	public:
		static Config& Instance();

		ConfigVar GetVar(const std::string& section, const std::string& name, const ConfigVar& fallback = ConfigVar(0)) const;

		// Reads an INI file_ into memory and then calls ProcessString on it
		void LoadFrom(const char* file_path);

		// Take an INI file_'s contents and fills the configuration map
		void ProcessString(char* ini_string);

	private:
		Config(); // Singleton

		std::unordered_map<std::string, std::unordered_map<std::string, ConfigVar>> value_map_;

		// Pulls a valid key and value from a line_ if possible (key=value)
		bool ProcessLine(char* line, std::string& key, std::string& value) const;

		// Changes the current section name if the line contains [nameHere]
		bool CheckForSection(char* line, std::string& out_name) const;
	};
}
