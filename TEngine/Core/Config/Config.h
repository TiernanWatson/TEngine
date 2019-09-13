#pragma once
#include "../PortableTypes.h"
#include "ConfigVar.h"
#include <unordered_map>

#define CONFIG_INT32(section, name, fallback) TEngine::Config::Instance().GetVar(section, name, fallback).GetInt32()
#define CONFIG_FLOAT32(section, name, fallback) TEngine::Config::Instance().GetVar(section, name, fallback).GetFloat32()
#define CONFIG_BOOL(section, name, fallback) TEngine::Config::Instance().GetVar(section, name, fallback).GetBool()

namespace TEngine
{
	class Config
	{
	private:
		std::unordered_map<std::string, std::unordered_map<std::string, ConfigVar>> valueMap;

		Config(); // singleton

	public:
		static Config& Instance();

		ConfigVar GetVar(const std::string& section, const std::string& name, const ConfigVar& fallback = ConfigVar(0)) const;

		/**
		* Reads an INI file into memory and then calls ProcessString on it
		**/
		void LoadFrom(const char* filePath);

		/**
		* Take an INI file's contents and fills the configuration map
		**/
		void ProcessString(char* iniString);

	private:
		/**
		* Pulls a valid key and value from a line if possible (key=value)
		**/
		bool ProcessLine(char* line, std::string& key, std::string& value) const;

		/**
		* Changes the current section name if the line contains [nameHere]
		**/
		bool CheckForSection(char* line, std::string& outName) const;
	};
}
