/* This source file is part of the Chewable Framework.
 * For the latest info, please visit http://chewable.googlecode.com/
 *
 * Copyright (c) 2009-2012 Ryan Chew
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file FileSystem_Win32.cpp
 * @brief File system utilities (Windows specific).
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Util/FileSystem.h"
#include "cbl/Debug/Logging.h"

#include <windows.h>

using namespace cbl;


void FileSystem::GetFileFolderListing( FileInfo::List& files, const cbl::Char* root_dir,
	const cbl::String& child_dir, bool recursive, bool folders, const std::unordered_set<HashValue>* extChecks, bool exclude )
{
	cbl::String dir = root_dir;
	dir += ".\\"; dir += child_dir;
	dir += "\\*";

	WIN32_FIND_DATA data;
	HANDLE h = FindFirstFile( dir.c_str(), &data );

	if( h == INVALID_HANDLE_VALUE )
		return;

	do {
		if( data.cFileName[0] == '.' )
			continue;

		bool _isfolder = ( data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) != 0;
		cbl::String output = child_dir.length() > 0 ? child_dir + "\\" + data.cFileName : data.cFileName;
		if( _isfolder && recursive )
			GetFileFolderListing( files, root_dir, output, recursive, folders, extChecks, exclude );

		if( folders == _isfolder ) {
			cbl::FileInfo out = _isfolder ? cbl::FileInfo( output.c_str(), "" ) : cbl::FileInfo( output );
			if( !extChecks || ( ( extChecks->find( cbl::Hash::Generate( out.GetExtension() ) ) == extChecks->end() ) == exclude ) )
				files.push_back( out );
		}

	} while( ::FindNextFile( h, &data ) == TRUE );

	::FindClose(h);
}

bool FileSystem::FolderCreate( const cbl::Char * directory )
{
	BOOL success = ::CreateDirectory( directory, NULL );
	if( success == 0 ) {
		if( GetLastError() == ERROR_ALREADY_EXISTS ) {
			LOG( LogLevel::Warning << directory << " already exists." );
		}
		else {
			LOG_ERROR( "Unable to create directory " << directory );
		}
		return false;
	}

	// Set directory attributes
	::SetFileAttributes( directory, FILE_ATTRIBUTE_NORMAL & FILE_ATTRIBUTE_DIRECTORY );

	return true;
}

bool FileSystem::FolderDelete( const cbl::Char * directory, bool full )
{
	bool            bSubdirectory = false;       // Flag, indicating whether
	// subdirectories have been found
	HANDLE          hFile;                       // Handle to directory
	std::string     strFilePath;                 // Filepath
	std::string     strPattern;                  // Pattern
	WIN32_FIND_DATA fileInfo;             // File information

	strPattern = directory;
	strPattern += "\\*.*";

	hFile = ::FindFirstFile( strPattern.c_str(), &fileInfo );
	if( hFile != INVALID_HANDLE_VALUE ) {
		do {
			if( fileInfo.cFileName[0] == '.' )
				continue;

			strFilePath = directory;
			strFilePath += "\\";
			strFilePath += fileInfo.cFileName;

			if( fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {
				if( full ) {
					// Delete subdirectory
					if( !FolderDelete( strFilePath.c_str(), full ) )
						return false;
				}
				else
					bSubdirectory = true;
			}
			else if( full ) {
				// Set file attributes
				if( ::SetFileAttributes(strFilePath.c_str(),
					FILE_ATTRIBUTE_NORMAL) == FALSE )
					return false;

				// Delete file
				if( ::DeleteFile(strFilePath.c_str()) == FALSE )
					return false;
			}
		} while( ::FindNextFile( hFile, &fileInfo ) == TRUE );

		// Close handle
		::FindClose(hFile);

		DWORD dwError = ::GetLastError();
		if(dwError != ERROR_NO_MORE_FILES)
			return false;
		else if( !bSubdirectory ) {
			// Set directory attributes
			if(::SetFileAttributes( directory,
				FILE_ATTRIBUTE_NORMAL ) == FALSE )
				return false;

			// Delete directory
			return ::RemoveDirectory( directory ) == TRUE;
		}
	}

	return false;
}

#include <Shlobj.h>
cbl::FileInfo FileSystem::GetLocalAppDirectory( void )
{
	TCHAR szPath[MAX_PATH];
	::SHGetFolderPath( NULL, CSIDL_LOCAL_APPDATA, NULL, 0, szPath );

	return cbl::FileInfo( szPath, "" );
}

bool FileSystem::FileCreate( const cbl::Char* directory, const cbl::Char* fileName, bool overwrite )
{
	cbl::String file = directory;
	file += "./";
	file += fileName;

	HANDLE result = CreateFile( file.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		0, NULL,
		( overwrite ? CREATE_ALWAYS : CREATE_NEW ),
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if( result != INVALID_HANDLE_VALUE ) {
		CloseHandle( result );
		return true;
	}

	return false;
}

bool FileSystem::FileCopy( const cbl::Char* source, const cbl::Char* dest, bool replace )
{
	BOOL success = ::CopyFile( source, dest, replace ? FALSE : TRUE );
	return success != 0;

}

cbl::FileInfo FileSystem::GetWorkingDirectory( void )
{
	TCHAR curr_dir[MAX_PATH] = "";

	if( !::GetCurrentDirectory( sizeof(curr_dir) - 1, curr_dir ) ) {
		LOG_ERROR( "Unable to determine current working directory." );
		return cbl::String();
	}

	return cbl::FileInfo( curr_dir );
}