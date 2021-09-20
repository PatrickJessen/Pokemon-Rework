#include "sfh_file.h"

namespace SimpleFileHandler
{
	File::File()
	{

	}

	void File::Open(const char* filename)
	{
		if (isFileOpen)
			Close();

		this->filename = filename;
		Open();
	}

	const char* File::GetFilename()
	{
		return filename;
	}
	bool File::GetIsFileOpen()
	{
		return isFileOpen;
	}
}

