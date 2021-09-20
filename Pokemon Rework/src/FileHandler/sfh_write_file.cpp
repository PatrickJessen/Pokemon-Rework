#include "sfh_write_file.h"

namespace SimpleFileHandler
{
	WriteFile::WriteFile()
		: File()
	{
	}
	WriteFile::WriteFile(const char* filename)
		: File()
	{
		File::Open(filename);
	}
	void WriteFile::WriteBuffer(char* buffer, int size)
	{
		outFile.write(buffer, size);
	}
	void WriteFile::Open()
	{
		outFile = std::ofstream(filename, std::ios::out | std::ios::binary);
		if (outFile.fail())
		{
			std::string msg = "Couldn't write to " + (std::string)filename;
			throw std::exception(msg.c_str());
		}

		isFileOpen = true;
	}
	void WriteFile::Close()
	{
		outFile.close();
		isFileOpen = false;
	}
	std::ofstream& WriteFile::GetOutFileStream()
	{
		return outFile;
	}
}