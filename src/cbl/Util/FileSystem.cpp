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
 * @file FileSystem.cpp
 * @brief File system utilities.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Util/FileSystem.h"
#include "cbl/Debug/Logging.h"

// External Dependencies //
#include <sys/stat.h> 
#include <locale>

using namespace cbl;

bool FileSystem::FolderCheckExists( const cbl::Char* folder )
{
	cbl::String name = folder;
	while( name.length() && ( name[name.size()-1] == '\\' || name[name.size()-1] == '/' ) )
		name.pop_back();

	if( name.length() == 0 )
		return false;

	struct stat stFileInfo;
	int result = stat( name.c_str(), &stFileInfo );
	return result == 0 && ( (stFileInfo.st_mode & S_IFMT) == S_IFDIR );
}

bool FileSystem::FileCheckExists( const cbl::Char * file )
{
	cbl::String name = file;
	while( name.length() && ( name[name.size()-1] == '\\' || name[name.size()-1] == '/' ) )
		name.pop_back();

	if( name.length() == 0 )
		return false;

	struct stat stFileInfo;
	int result = stat( name.c_str(), &stFileInfo );
	return result == 0 && ( (stFileInfo.st_mode & S_IFMT) != S_IFDIR );
}

bool FileSystem::FileDelete( const cbl::Char* directory, const cbl::Char * file )
{
	cbl::String f = directory;
	f += "./";
	f += file;

	if( ::remove( f.c_str() ) != 0 ) {
		LOG_ERROR( "Could not delete file: " << f );
		return false;
	}

	return true;
}

std::unordered_set<HashValue> GetExtensionList( const cbl::Char* extList )
{
	// Make sure that we skip all spaces.
	while( *extList == ' ' && *extList != '\0' ) ++extList;

	std::unordered_set<HashValue> exts;
	const Char* curr = extList;

	std::locale loc;
	Char currExt[64] = { '\0' };
	Char* writer = currExt;

	while( *curr != '\0' ) {
		if( std::isalnum( *curr, loc ) )
			*writer++ = Char( ::tolower( *curr ) );

		if( *curr == ',' ) {
			*writer = '\0';
			exts.insert( cbl::Hash::Generate( currExt ) );
			writer = currExt;
		}
		++curr;
	}

	if( writer != currExt ) exts.insert( cbl::Hash::Generate( currExt ) );

	return exts;
}

FileInfo::List FileSystem::GetFileList( const cbl::Char * directory, bool recursive )
{
	FileInfo::List files;
	GetFileFolderListing( files, directory, "", recursive, false, NULL, false );
	return files;
}

FileInfo::List FileSystem::GetFileListExclude( const cbl::Char * directory, const cbl::Char* extExclude, bool recursive )
{
	CBL_ASSERT_TRUE( extExclude != NULL );

	FileInfo::List files;
	std::unordered_set<HashValue> extList = GetExtensionList( extExclude );
	GetFileFolderListing( files, directory, "", recursive, false, ( extList.size() == 0 ? NULL : &extList ), true );
	return files;
}

FileInfo::List FileSystem::GetFileListInclude( const cbl::Char * directory, const cbl::Char* extInclude, bool recursive )
{
	CBL_ASSERT_TRUE( extInclude != NULL );

	FileInfo::List files;
	std::unordered_set<HashValue> extList = GetExtensionList( extInclude );
	GetFileFolderListing( files, directory, "", recursive, false, ( extList.size() == 0 ? NULL : &extList ), false );
	return files;
}

FileInfo::List FileSystem::GetFolderList( const cbl::Char * directory, bool recursive )
{
	FileInfo::List files;
	GetFileFolderListing( files, directory, "", recursive, true, NULL, false );
	return files;
}
