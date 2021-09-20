#include "sfh_read_file.h"
#include <string>

namespace SimpleFileHandler
{
	ReadFile::ReadFile()
		: File()
	{
	}
	ReadFile::ReadFile(const char* filename)
		: File()
	{
		File::Open(filename);
	}
	char* ReadFile::ReadBuffer(int size)
	{
		char* buffer = new char[size];
		inFile.read(buffer, size);
		return buffer;
	}
	void ReadFile::ReadSkip(int amount)
	{
		for (int i = 0; i < amount; i++)
		{
			char byte = 0;
			inFile.read(&byte, 1);
		}
	}
	void ReadFile::Open()
	{
		inFile = std::ifstream(filename, std::ifstream::binary);

		if (inFile.fail())
		{
			std::string msg = "Couldn't read from " + (std::string)filename;
			throw std::exception(msg.c_str());
		}

		isFileOpen = true;
	}
	void ReadFile::Close()
	{
		inFile.close();
		isFileOpen = false;
	}
	std::ifstream& ReadFile::GetInFileStream()
	{
		return inFile;
	}
}