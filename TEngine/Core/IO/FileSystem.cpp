#include "FileSystem.h"
#include <Windows.h>
#include <exception>
#include <assert.h>

namespace TEngine
{
	FileSystem::FileSystem() { }

	FileSystem& FileSystem::Instance()
	{
		static FileSystem instance;
		return instance;
	}

	void FileSystem::ThrowFileError() const
	{
		switch (GetLastError()) 
		{
		case 0:  
			break;
		case ERROR_ALREADY_EXISTS:  // not necessarily an error
		   throw std::exception(
		      "FileSystem::ThrowFileError: ERROR_ALREADY_EXISTS file_ already "
		      "exists, cannot be created");
			break;
		case ERROR_FILE_EXISTS:
			throw std::exception(
				"FileSystem::ThrowFileError: ERROR_FILE_EXISTS file_ cannot be "
				"created, file_ exists");
			break;
		case ERROR_FILE_NOT_FOUND:
			throw std::exception(
				"FileSystem::ThrowFileError: ERROR_FILE_NOT_FOUND file_ cannot be "
				"opened, not found");
			break;
		default:
			throw std::exception("FileSystem::ThrowFileError: Unknown error occured.");
			break;
		}
	}

	void FileSystem::ThrowReadError() const
	{
	}

	bool FileSystem::FileExists(const char* file_path) const
	{
		assert(file_path != nullptr);

		WIN32_FIND_DATA findFileData;
		HANDLE file_handle = FindFirstFile(file_path, &findFileData);

		bool exists = file_handle != INVALID_HANDLE_VALUE;
		if (exists) 
		{
			FindClose(file_handle);
		}

		return exists;
	}

	char* FileSystem::Read(const char* file_path, U32* out_size) const
	{
		assert(file_path != nullptr);

		HANDLE file_handle = CreateFile(file_path, GENERIC_READ,
			NULL, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (file_handle == INVALID_HANDLE_VALUE)
			ThrowFileError();

		DWORD file_size = GetFileSize(file_handle, NULL);
		DWORD bytes_read = 0;

		char* buffer = new char[file_size + 1];

		if (!ReadFile(file_handle, buffer, file_size, &bytes_read, NULL)) 
			ThrowReadError();

		if (out_size != nullptr)
			*out_size = file_size;
		
		return buffer;
	}

	char* FileSystem::ReadString(const char* file_path) const
	{
		U32 file_size;
		char* buffer = Read(file_path, &file_size);
		buffer[file_size] = '\0';

		return buffer;
	}
}
