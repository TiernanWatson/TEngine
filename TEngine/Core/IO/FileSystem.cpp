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
		      "FileSystem::ThrowFileError: ERROR_ALREADY_EXISTS file already "
		      "exists, cannot be created");
			break;
		case ERROR_FILE_EXISTS:
			throw std::exception(
				"FileSystem::ThrowFileError: ERROR_FILE_EXISTS file cannot be "
				"created, file exists");
			break;
		case ERROR_FILE_NOT_FOUND:
			throw std::exception(
				"FileSystem::ThrowFileError: ERROR_FILE_NOT_FOUND file cannot be "
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

	bool FileSystem::FileExists(const char* filePath) const
	{
		assert(filePath != nullptr);

		WIN32_FIND_DATA findFileData;
		HANDLE hFind = FindFirstFile(filePath, &findFileData);

		bool exists = hFind != INVALID_HANDLE_VALUE;
		if (exists) 
		{
			FindClose(hFind);
		}

		return exists;
	}

	char* FileSystem::Read(const char* filePath, uint32* outSize) const
	{
		assert(filePath != nullptr);

		HANDLE hFile = CreateFile(filePath, GENERIC_READ,
			NULL, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (hFile == INVALID_HANDLE_VALUE)
			ThrowFileError();

		DWORD fileSize = GetFileSize(hFile, NULL);
		DWORD bytesRead = 0;

		char* buffer = new char[fileSize + 1];

		if (!ReadFile(hFile, buffer, fileSize, &bytesRead, NULL)) 
			ThrowReadError();

		if (outSize != nullptr)
			*outSize = fileSize;
		
		return buffer;
	}

	char* FileSystem::ReadString(const char* filePath) const
	{
		uint32 fileSize;
		char* buffer = Read(filePath, &fileSize);
		buffer[fileSize] = '\0';

		return buffer;
	}
}
