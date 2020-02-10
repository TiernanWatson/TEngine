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

		// Check if the file_ specified exists, can return false if folder doesnt exist
		bool FileExists(const char* file_path) const;

		/**
		* Simple synchronous file_ read function
		**/
		char* Read(const char* file_path, U32* out_size = nullptr) const;

		/**
		* Simple synchronous file_ read function that adds null terminator
		**/
		char* ReadString(const char* file_path) const;

	private:
		void ThrowFileError() const;

		void ThrowReadError() const;
	};
}
