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
			return valueMap.at(section).at(name);
		}
		catch (std::out_of_range ex) 
		{
			return fallback;
		}
	}

	void Config::LoadFrom(const char* filePath)
	{
		char* iniString = FileSystem::Instance().ReadString(filePath);
		ProcessString(iniString);
		delete iniString;
	}

	void Config::ProcessString(char* iniString)
	{
		std::string currentSection;

		char* context;
		char* line = strtok_s(iniString, "\n\r", &context);

		while (line != NULL)
		{
			if (!CheckForSection(line, currentSection)) // change section name if needed
			{
				std::string key, value;
				if (ProcessLine(line, key, value))
				{
					valueMap[currentSection][key] = ConfigVar(0);
				}
			}

			line = strtok_s(NULL, "\n\r", &context); // move to next line
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

	bool Config::CheckForSection(char* line, std::string& outName) const
	{
		if (line[0] == '[')
		{
			for (int i = 0; i < strlen(line); i++)
			{
				if (line[i] == ']') 
				{
					line[i] = '\0';
					outName = std::string(&line[1]);
					return true;
				}
			}
		}

		return false;
	}
}
