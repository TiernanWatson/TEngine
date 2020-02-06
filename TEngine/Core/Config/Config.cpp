#include "Config.h"
#include <stdexcept>
#include <cstring>
#include "../IO/FileSystem.h"

namespace TEngine
{
	Config::Config() {}
	
	Config& Config::Instance()
	{
		static Config instance;
		return instance;
	}

	ConfigVar Config::GetVar(const std::string& section, const std::string& name, const ConfigVar& fallback) const
	{
		try 
		{
			return value_map_.at(section).at(name);
		}
		catch (std::out_of_range ex) 
		{
			return fallback;
		}
	}

	void Config::LoadFrom(const char* file_path)
	{
		char* ini_string = FileSystem::Instance().ReadString(file_path);
		ProcessString(ini_string);
		delete ini_string;
	}

	void Config::ProcessString(char* ini_string)
	{
		std::string current_section;

		char* context;
		char* line = strtok_s(ini_string, "\n\r", &context);

		while (line != NULL)
		{
			if (!CheckForSection(line, current_section)) // change section name_ if needed
			{
				std::string key, value;
				if (ProcessLine(line, key, value))
				{
					value_map_[current_section][key] = ConfigVar(value);
				}
			}

			line = strtok_s(NULL, "\n\r", &context); // move to next line_
		}
	}

	bool Config::ProcessLine(char* line, std::string& key, std::string& value) const
	{
		for (int i = 0; i < strlen(line); i++)
		{
			if (line[i] == '=') 
			{
				line[i] = '\0';
				key = line;
				value = &line[i + 1];

				return true;
			}
		}

		return false;
	}

	bool Config::CheckForSection(char* line, std::string& out_name) const
	{
		if (line[0] == '[')
		{
			for (int i = 0; i < strlen(line); i++)
			{
				if (line[i] == ']') 
				{
					line[i] = '\0';
					out_name = std::string(&line[1]);
					return true;
				}
			}
		}

		return false;
	}
}
