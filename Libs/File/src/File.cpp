//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "File.h"

namespace Azul
{
	// holds the directory internally to File.cpp
	static char BaseDir[File::BASE_DIR_SIZE] = {0};

	File::Error File::ClearBaseDir() noexcept
	{
		BaseDir[0] = '\0';

		return File::Error::SUCCESS;
	}

	File::Error File::GetBaseDir(char *const pDirOut, size_t DirOutSize) noexcept
	{
		if (!pDirOut) 
		{
			return File::Error::BASE_DIR_NULLPTR_FAIL;
		}

		if (DirOutSize < File::BASE_DIR_SIZE)
		{
			return File::Error::BASE_DIR_INSUFFICIENT_SPACE_FAIL;
		}

		if (BaseDir[0] == '\0')
		{
			return File::Error::BASE_DIR_FAIL;
		}

		for (size_t i = 0; i < File::BASE_DIR_SIZE; i++)
		{
			pDirOut[i] = BaseDir[i];
		}
		pDirOut[File::BASE_DIR_SIZE - 1] = '\0'; 

		return File::Error::SUCCESS;
	}

	File::Error File::SetBaseDir(const char *const pDir) noexcept
	{
		
		if (pDir == nullptr)
		{
			return File::Error::BASE_DIR_NULLPTR_FAIL;
		}

		size_t length = strlen(pDir);

		if (File::BASE_DIR_SIZE <= length)
		{
			return File::Error::BASE_DIR_INSUFFICIENT_SPACE_FAIL;
		}

		for (size_t i = 0; i < length; i++)
		{
			BaseDir[i] = pDir[i];
		}
		BaseDir[length] = '\0'; 

		return File::Error::SUCCESS;
	}

	bool File::IsHandleValid(File::Handle fh) noexcept
	{
		
		if (fh == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		DWORD pos = SetFilePointer(fh, 0, nullptr, FILE_CURRENT);
		if (pos == INVALID_SET_FILE_POINTER)
		{
			return false;
		}
			
		return true;
		
	}

	File::Error File::Open(File::Handle &fh, const char *const fileName, File::Mode mode, bool UseBaseAddr) noexcept
	{
		if (fileName == nullptr)
		{
			return File::Error::OPEN_FILENAME_FAIL;
		}

		char oldDir[File::BASE_DIR_SIZE];
		DWORD length = GetCurrentDirectory(File::BASE_DIR_SIZE, oldDir);

		if (length == 0 || length >= File::BASE_DIR_SIZE)
		{
			return File::Error::OPEN_FAIL;
		}

		bool dirChanged = false;

		if (UseBaseAddr)
		{
			if (BaseDir[0] == '\0')
			{
				return File::Error::OPEN_BASE_DIR_FAIL;
			}


			if (!SetCurrentDirectory(BaseDir))
			{
				return File::Error::OPEN_BASE_DIR_FAIL;
			}

			dirChanged = true;
		}

		DWORD dwAccess = 0;
		DWORD dwCreation = 0;
		DWORD dwMode = 0;

		switch (mode)
		{
		case File::Mode::READ:
			dwAccess = GENERIC_READ;
			dwCreation = OPEN_EXISTING;
			dwMode = FILE_SHARE_READ;
			break;

		case File::Mode::WRITE:
			dwAccess = GENERIC_WRITE;
			dwCreation = CREATE_ALWAYS;

			break;

		case File::Mode::READ_WRITE:
			dwAccess = GENERIC_READ | GENERIC_WRITE;
			dwCreation = OPEN_ALWAYS;

			break;

		default:

			if (dirChanged)
			{
				SetCurrentDirectory(oldDir);
			}

			return File::Error::OPEN_FAIL;
		}

		HANDLE handle = CreateFile(fileName,
											dwAccess,
											dwMode,
											nullptr,
											dwCreation,
											FILE_ATTRIBUTE_NORMAL,
											nullptr);

		if (dirChanged)
		{
			SetCurrentDirectory(oldDir);
		}

		if (handle == INVALID_HANDLE_VALUE)
		{
			return File::Error::OPEN_FAIL;
		}
			
		fh = (File::Handle)handle;

		return File::Error::SUCCESS;


	}

	File::Error File::Close(File::Handle &fh) noexcept
	{
		if (fh == INVALID_HANDLE_VALUE)
		{
			return File::Error::CLOSE_FAIL;
		}
		
		if (!IsHandleValid(fh))
		{
			return File::Error::CLOSE_FAIL;
		}

		if (!CloseHandle(fh))
		{
			return File::Error::CLOSE_FAIL;
		}

		fh = INVALID_HANDLE_VALUE;

		return File::Error::SUCCESS;

	}

	File::Error File::Write(File::Handle fh, const void *const buffer, const DWORD inSize) noexcept
	{
		if (fh == INVALID_HANDLE_VALUE)
		{
			return File::Error::WRITE_FAIL;
		}

		if (buffer == nullptr || !IsHandleValid(fh))
		{
			return File::Error::WRITE_FAIL;
		}

		DWORD dwWritten = 0;

		if (!WriteFile(fh, buffer, inSize, &dwWritten, nullptr) || dwWritten != inSize)
		{
			return File::Error::WRITE_FAIL;
		}

		return File::Error::SUCCESS;
	}

	File::Error File::Read(File::Handle fh, void *const buffer, const DWORD inSize) noexcept
	{
		if (fh == INVALID_HANDLE_VALUE)
		{
			return File::Error::READ_FAIL;
		}

		if (buffer == nullptr || !IsHandleValid(fh))
		{
			return File::Error::READ_FAIL;
		}

		DWORD dwReadCnt = 0;

		if (!ReadFile(fh, buffer, inSize, &dwReadCnt, nullptr) || dwReadCnt != inSize)
		{
			return File::Error::READ_FAIL;
		}

		return File::Error::SUCCESS;
	}


	File::Error File::Seek(File::Handle fh, File::Position location, int offset) noexcept
	{
		if (fh == INVALID_HANDLE_VALUE)
		{
			return File::Error::SEEK_FAIL;
		}

		if (!IsHandleValid(fh))
		{
			return File::Error::SEEK_FAIL;
		}

		if (offset < 0 && location == File::Position::BEGIN)
		{
			return File::Error::SEEK_FAIL;
		}
			
		DWORD dwLoc = 0;

		switch (location)
		{
		case File::Position::BEGIN:   
			dwLoc = FILE_BEGIN;

			break;
		case File::Position::CURRENT:
			dwLoc = FILE_CURRENT;

			break;
		case File::Position::END:  
			dwLoc = FILE_END;

			break;
		default:           

			return File::Error::SEEK_FAIL;
		}

		DWORD result = SetFilePointer(fh, offset, nullptr, dwLoc);

		if (result == INVALID_SET_FILE_POINTER)
		{
			return File::Error::SEEK_FAIL;
		}

		return File::Error::SUCCESS;
	}

	File::Error File::Tell(File::Handle fh, DWORD &offset) noexcept
	{
		if (fh == INVALID_HANDLE_VALUE)
		{
			return File::Error::TELL_FAIL;
		}

		if (!IsHandleValid(fh))
		{
			return File::Error::TELL_FAIL;
		}
			
		DWORD dwPos = SetFilePointer(fh, 0, nullptr, FILE_CURRENT);

		if (dwPos == INVALID_SET_FILE_POINTER)
		{
			return File::Error::TELL_FAIL;
		}
			
		offset = dwPos;

		return File::Error::SUCCESS;
	}

	File::Error File::Flush(File::Handle fh) noexcept
	{
		if (fh == INVALID_HANDLE_VALUE)
		{
			return File::Error::FLUSH_FAIL;
		}

		if (!IsHandleValid(fh))
		{
			return File::Error::FLUSH_FAIL;
		}
			
		if (!FlushFileBuffers(fh))
		{
			return File::Error::FLUSH_FAIL;
		}
			
		return File::Error::SUCCESS;
	}

}

// --- End of File ---
