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
 * @file FileSystem.h
 * @brief File system utilities.
 */

#ifndef __CBL_FILESYSTEM_H_
#define __CBL_FILESYSTEM_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Hash.h"
#include "cbl/Util/FileInfo.h"
#include "cbl/Util/Singleton.h"

#include <list>

namespace cbl
{
	//! @brief File system utilties.
	class CBL_API FileSystem
	{
	/***** Static Public Methods *****/
	public:
		//! Get local applications directory.
		static cbl::FileInfo GetLocalAppDirectory( void );
		//! Get the current woring directory.
		static cbl::FileInfo GetWorkingDirectory( void );
		//! Check if a folder exists.
		//! @param	file	File name.
		static bool FolderCheckExists( const cbl::Char* folder );
		//! Check if a file exists (.
		//! @param	file	File name.
		static bool FileCheckExists( const cbl::Char * file );
		//! Get file listing from directory.
		//! @param	directory	Directory to use.
		//! @param	recursive	Recursively search directory.
		//! @return				List of files.
		static FileInfo::List GetFileList( const cbl::Char * directory, bool recursive = false );
		//! Get file listing from directory.
		//! @param	directory	Directory to use.
		//! @param	recursive	Recursively search directory.
		//! @param	exclude		Comma separated extensions to exclude from search. e.g. exe,txt,fbx
		//! @return				List of files.
		static FileInfo::List GetFileListExclude( const cbl::Char * directory, const cbl::Char* extExclude, bool recursive = false );
		//! Get file listing from directory.
		//! @param	directory	Directory to use.
		//! @param	recursive	Recursively search directory.
		//! @param	exclude		Comma separated extensions to include from search. Only files of specified type will appear in the list.
		//! @return				List of files.
		static FileInfo::List GetFileListInclude( const cbl::Char * directory, const cbl::Char* extExclude, bool recursive = false );
		//! Get directory listing from directory.
		//! @param	directory	Directory to use.
		//! @param	recursive	Recursively search directory.
		//! @return				List of folders.
		static FileInfo::List GetFolderList( const cbl::Char * directory, bool recursive = false );
		//! Create a directory.
		static bool FolderCreate( const cbl::Char * directory );
		//! Remove a directory.
		static bool FolderDelete( const cbl::Char * directory, bool recursive = true );
		//! Create a new blank file.
		static bool FileCreate( const cbl::Char* directory, const cbl::Char* fileName, bool overwrite = true );
		//! Copy a file from a source to directory.
		static bool FileCopy( const cbl::Char* source, const cbl::Char* dest, bool full = true );
		//! Delete a specified file.
		static bool FileDelete( const cbl::Char* directory, const cbl::Char * file );

	/***** Private Static Methods *****/
	private:
		static void GetFileFolderListing( FileInfo::List& files, const cbl::Char* root_dir,
			const cbl::String& child_dir, bool recursive, bool folders, const std::unordered_set<HashValue>* extChecks, bool exclude );
	};
}

#endif // __CBL_FILESYSTEM_H_
