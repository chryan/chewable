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
 * @file test_FileSystem.cpp
 * @brief Unit testing for file system utilities.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Util/FileSystem.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

TEST( FileSystem, FileExists )
{
	// File
	ASSERT_TRUE( FileSystem::FileCheckExists( "..\\..\\..\\include\\cbl\\Chewable.h" ) );
	ASSERT_FALSE( FileSystem::FileCheckExists( "..\\..\\..\\include\\cbl\\NONE" ) );
	ASSERT_FALSE( FileSystem::FileCheckExists( "..\\..\\..\\include\\cbl" ) );
	ASSERT_FALSE( FileSystem::FileCheckExists( "..\\..\\..\\include\\cbl\\" ) );

	// Folder
	ASSERT_TRUE( FileSystem::FolderCheckExists( "..\\..\\..\\include\\cbl" ) );
	ASSERT_TRUE( FileSystem::FolderCheckExists( "..\\..\\..\\include\\cbl\\" ) );
	ASSERT_FALSE( FileSystem::FolderCheckExists( "..\\..\\..\\include\\cbl\\Chewable.h" ) );
	ASSERT_FALSE( FileSystem::FolderCheckExists( "..\\..\\..\\include\\cblnan" ) );
}

TEST( FileSystem, DirectoryCreationAndRemoval )
{
	ASSERT_TRUE( cbl::FileSystem::FolderCreate( "dir_test" ) );
	ASSERT_FALSE( cbl::FileSystem::FolderCreate( "dir_test" ) );
	ASSERT_TRUE( cbl::FileSystem::FolderDelete( "dir_test" ) );
	ASSERT_FALSE( cbl::FileSystem::FolderDelete( "dir_test" ) );
}

TEST( FileSystem, FileCreationAndRemoval )
{
	ASSERT_TRUE( cbl::FileSystem::FileCreate( "", "NewFile.bin" ) );
	ASSERT_FALSE( cbl::FileSystem::FileCreate( "", "NewFile.bin", false ) );
	ASSERT_TRUE( cbl::FileSystem::FileCreate( "", "NewFile.bin" ) );
	ASSERT_TRUE( cbl::FileSystem::FileDelete( "", "NewFile.bin" ) );
	ASSERT_FALSE( cbl::FileSystem::FileDelete( "", "NewFile.bin" ) );
}

TEST( FileSystem, FileExtIncludeExclude )
{
	cbl::FileSystem::FolderCreate( "test" );
	const Char* exts[] = { "bin", "Nfo", "tXT" };
	for( size_t i = 0; i < 6; ++i ) {
		char filename[255] = {'\0'};
		sprintf( filename, "NewFile%d.%s", i, exts[i%3] );
		cbl::FileSystem::FileCreate( "test", filename, true );
	}

	ASSERT_EQ( cbl::FileSystem::GetFileListExclude( "test", "bin" ).size(), 4 );
	ASSERT_EQ( cbl::FileSystem::GetFileListExclude( "test", "nfO" ).size(), 4 );
	ASSERT_EQ( cbl::FileSystem::GetFileListExclude( "test", "TXT" ).size(), 4 );
	ASSERT_EQ( cbl::FileSystem::GetFileListExclude( "test", "txt,n  fo  " ).size(), 2 );
	ASSERT_EQ( cbl::FileSystem::GetFileListExclude( "test", " t x t  ,  b in" ).size(), 2 );
	ASSERT_EQ( cbl::FileSystem::GetFileListExclude( "test", "" ).size(), 6 );
	ASSERT_EQ( cbl::FileSystem::GetFileListExclude( "test", "bin,Nfo,tXT" ).size(), 0 );

	ASSERT_EQ( cbl::FileSystem::GetFileListInclude( "test", "bin" ).size(), 2 );
	ASSERT_EQ( cbl::FileSystem::GetFileListInclude( "test", "nfO" ).size(), 2 );
	ASSERT_EQ( cbl::FileSystem::GetFileListInclude( "test", "TXT" ).size(), 2 );
	ASSERT_EQ( cbl::FileSystem::GetFileListInclude( "test", "bin,nfo" ).size(), 4 );
	ASSERT_EQ( cbl::FileSystem::GetFileListInclude( "test", "txt,n  fo  " ).size(), 4 );
	ASSERT_EQ( cbl::FileSystem::GetFileListInclude( "test", " t x t  ,  b in" ).size(), 4 );
	ASSERT_EQ( cbl::FileSystem::GetFileListInclude( "test", "" ).size(), 6 );
	ASSERT_EQ( cbl::FileSystem::GetFileListInclude( "test", "bin,Nfo,tXT" ).size(), 6 );

	cbl::FileSystem::FolderDelete( "test" );
}

TEST( FileSystem, FileListing )
{
	static const int fileCount = 5;
	cbl::FileSystem::FolderDelete( "listing_test" );

	ASSERT_TRUE( cbl::FileSystem::FolderCreate( "listing_test" ) );
	ASSERT_TRUE( cbl::FileSystem::FolderCreate( "listing_test\\inside" ) );

	for( int i = 0; i < fileCount; ++i ) {
		char fileName[255];

		// Base folder
		{
			sprintf( fileName, ".\\listing_test\\new_%d", i );
			std::fstream file;
			file.open( fileName, std::fstream::out );
			if( file.is_open() ) {
				file << fileName;
				file.close();
			}
		}
		// Child folder
		{
			sprintf( fileName, ".\\listing_test\\inside\\new_%d", i );
			std::fstream file;
			file.open( fileName, std::fstream::out );
			if( file.is_open() ) {
				file << fileName;
				file.close();
			}
		}
	}

	ASSERT_EQ( cbl::FileSystem::GetFileList( "listing_test", false ).size(), fileCount );
	ASSERT_EQ( cbl::FileSystem::GetFileList( "listing_test", true ).size(), fileCount * 2 );
	ASSERT_EQ( cbl::FileSystem::GetFileList( "listing_test\\inside", false ).size(), fileCount );
	ASSERT_EQ( cbl::FileSystem::GetFileList( "listing_test\\inside", true ).size(), fileCount );

	ASSERT_TRUE( cbl::FileSystem::FolderDelete( "listing_test" ) );
}

TEST( FileSystem, DirectoryListing )
{
	static const int dirCount = 4;
	cbl::FileSystem::FolderDelete( "dir_test_root" );

	ASSERT_TRUE( cbl::FileSystem::FolderCreate( "dir_test_root" ) );

	for( cbl::Uint32 i = 0; i < dirCount; ++i ) {
		char dirName[255];
		sprintf( dirName, "dir_test_root\\_d_test_%d", i );
		ASSERT_TRUE( cbl::FileSystem::FolderCreate( dirName ) );
		sprintf( dirName, "dir_test_root\\_d_test_%d\\_inside_test", i );
		ASSERT_TRUE( cbl::FileSystem::FolderCreate( dirName ) );
	}

	// Non-recursive tests.
	{
		FileInfo::List dirs = cbl::FileSystem::GetFolderList( "dir_test_root" );
		ASSERT_EQ( dirs.size(), dirCount );

		cbl::Uint32 t = 0;
		CBL_FOREACH( FileInfo::List, it, dirs ) {
			char dirName[255];
			sprintf( dirName, "_d_test_%d", t );
			++t;
		}
	}

	// Recursive tests.
	{
		FileInfo::List dirs = cbl::FileSystem::GetFolderList( "dir_test_root", true );
		ASSERT_EQ( dirs.size(), dirCount * 2 );
		ASSERT_FALSE( dirs.size() == 3 );

		cbl::Uint32 t = 0;
		CBL_FOREACH( FileInfo::List, it, dirs ) {
			char dirName[255];
			if( t % 2 == 0 ) {
				sprintf( dirName, "_d_test_%d\\_inside_test", t/2 );
				ASSERT_EQ( *it, FileInfo( dirName, "" ) );
			}
			else {
				sprintf( dirName, "_d_test_%d", t/2 );
				ASSERT_EQ( *it, FileInfo( dirName, "" ) );
			}
			++t;
		}
	}

	ASSERT_TRUE( cbl::FileSystem::FolderDelete( "dir_test_root" ) );
}
