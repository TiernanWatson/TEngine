#pragma once
#include "../PortableTypes.h"

namespace TEngine 
{
	class FileSystem
	{
	private:
		FileSystem();

	public:
		static FileSystem& Instance();

		/**
		* Check if the file specified exists, can return false if folder doesnt exist
		**/
		bool FileExists(const char* filePath) const;

		/**
		* Simple synchronous file read function
		**/
		char* Read(const char* filePath, uint32* outSize = nullptr) const;

		/**
		* Simple synchronous file read function that adds null terminator
		**/
		char* ReadString(const char* filePath) const;

	private:
		void ThrowFileError() const;

		void ThrowReadError() const;
	};
}
