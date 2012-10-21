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
 * @file test_FielInfo.cpp
 * @brief Unit testing for file info.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Util/FileInfo.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

TEST( FileInfoTestFixture, ValidityTest )
{
	// Create the test file.
	if( FILE * f = fopen( "testFile.txt", "w" ) ) {
		fprintf( f, "Test file." );
		fclose( f );
	}

	FileInfo finfo( ".\\", "testFile.txt" );
	FileInfo finfo2( "testpath", "testFile.txt" );
	FileInfo finfo3( "./newpath\\test\\noFileFound.txt.bak" );
	FileInfo finfo4( "testFile.txt" );
	FileInfo finfo5( "", "testFile.txt" );
	FileInfo finfo6( ".", "testFile.txt" );

	ASSERT_TRUE( finfo.Exists() );
	ASSERT_EQ( finfo.GetExtension(), "txt" );
	ASSERT_EQ( finfo.GetFile(), "testFile.txt" );
	ASSERT_EQ( finfo.GetFileNoExt(), "testFile" );
	ASSERT_EQ( finfo.GetPath(), "" );
	ASSERT_EQ( finfo.GetUpOneLevel(), "" );
	ASSERT_EQ( finfo.GetFullFile(), "testFile.txt" );
	
	ASSERT_EQ( finfo2.GetExtension(), "txt" );
	ASSERT_EQ( finfo2.GetFile(), "testFile.txt" );
	ASSERT_EQ( finfo2.GetFileNoExt(), "testFile" );
	ASSERT_EQ( finfo2.GetPath(), "testpath/" );
	ASSERT_EQ( finfo2.GetUpOneLevel(), "" );
	ASSERT_EQ( finfo2.GetFullFile(), "testpath/testFile.txt" );

	ASSERT_EQ( finfo3.GetExtension(), "bak" );
	ASSERT_EQ( finfo3.GetFile(), "noFileFound.txt.bak" );
	ASSERT_EQ( finfo3.GetFileNoExt(), "noFileFound.txt" );
	ASSERT_EQ( finfo3.GetPath(), "newpath/test/" );
	ASSERT_EQ( finfo3.GetUpOneLevel(), "newpath/" );
	ASSERT_EQ( finfo3.GetFullFile(), "newpath/test/noFileFound.txt.bak" );

	ASSERT_FALSE( finfo2.Exists() );
	ASSERT_FALSE( finfo3.Exists() );

	std::ostringstream test;
	test << finfo;
	ASSERT_EQ( test.str(), finfo.GetFullFile() );

	ASSERT_EQ( std::string("Hello") + finfo, "Hello/testFile.txt" );
	ASSERT_EQ( "Hello" + finfo, "Hello/testFile.txt" );

	ASSERT_EQ( finfo4.GetFullFile(), "testFile.txt" );
	ASSERT_EQ( finfo4.GetFile(), "testFile.txt" );
	ASSERT_EQ( finfo4.GetFileNoExt(), "testFile" );
	ASSERT_EQ( finfo4.GetExtension(), "txt" );
	ASSERT_EQ( finfo5.GetFullFile(), "testFile.txt" );
	ASSERT_EQ( finfo4.GetFile(), "testFile.txt" );
	ASSERT_EQ( finfo4.GetFileNoExt(), "testFile" );
	ASSERT_EQ( finfo4.GetExtension(), "txt" );
	ASSERT_EQ( finfo6.GetFullFile(), "testFile.txt" );
	ASSERT_EQ( finfo4.GetFile(), "testFile.txt" );
	ASSERT_EQ( finfo4.GetFileNoExt(), "testFile" );
	ASSERT_EQ( finfo4.GetExtension(), "txt" );

	remove( "testFile.txt" ); // Delete the test file.
}

TEST( FileInfoTestFixture, AssignmentTest )
{
	FileInfo finfo;
	finfo == "";
	ASSERT_EQ( finfo, "" );

	finfo = "test/testinfo.xml";
	ASSERT_EQ( finfo, "test/testinfo.xml" );
	ASSERT_EQ( finfo.GetPath(), "test/" );
	ASSERT_EQ( finfo.GetExtension(), "xml" );

	finfo = "./test/testinfo.xml";
	ASSERT_EQ( finfo.GetFullFile(), "test/testinfo.xml" );
	ASSERT_EQ( finfo.GetPath(), "test/" );
	ASSERT_EQ( finfo.GetExtension(), "xml" );
}

TEST( FileInfoTestFixture, PathStrippingTest )
{
	FileInfo finfo( "////\\/\\///Test///secondpath////", "Test.xml" );
	ASSERT_EQ( finfo, "Test/secondpath/Test.xml" );
}

