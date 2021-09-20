#pragma once
#include "sfh_def.h"

namespace SimpleFileHandler
{
	class File abstract
	{
	protected:
		const char* filename = "nullptr";
		bool isFileOpen = false;

	public:
		File();

	protected:
		virtual void Open() = 0;

	public:	
		// Used to open a file
		void Open(const char* filename);

	public:
		// Used to close file
		virtual void Close() = 0;

	public:
		// Used to get filename
		const char* GetFilename();

		// Used to get file open state
		bool GetIsFileOpen();
	};
}


