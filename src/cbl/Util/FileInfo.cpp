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
 * @file FileInfo.h
 * @brief File descriptor class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Util/FileInfo.h"
#include "cbl/Util/FileSystem.h"

using namespace cbl;

cbl::String FileInfo::GetFileNoExt( void ) const
{
	size_t pos = mFile.find_last_of( '.' );
	return mFile.substr( 0, pos );
}

cbl::String FileInfo::GetExtension( void ) const
{
	size_t pos = mFile.find_last_of( '.' );
	return ( pos == std::string::npos && pos > 0 ) ? "" : mFile.substr( pos + 1 );
}

cbl::String FileInfo::GetFullFile( void ) const
{
	return mPath + mFile;
}

cbl::String FileInfo::GetUpOneLevel( void ) const
{
	size_t pos = mPath.find_last_of( '/' );
	if( pos != std::string::npos && pos > 0 )
		pos = mPath.find_last_of( '/', pos - 1 );
	return pos != std::string::npos ? mPath.substr( 0, pos + 1 ) : "";
}

FileInfo::List FileInfo::GetFilesInPath( bool recursive ) const
{
	return FileSystem::GetFileList( mPath.c_str(), recursive );
}

FileInfo::List FileInfo::GetFilesInPathExclude( const cbl::Char* excludes, bool recursive ) const
{
	return FileSystem::GetFileListExclude( mPath.c_str(), excludes, recursive );
}

FileInfo::List FileInfo::GetFilesInPathInclude( const cbl::Char* includes, bool recursive ) const
{
	return FileSystem::GetFileListInclude( mPath.c_str(), includes, recursive );
}

FileInfo::List FileInfo::GetFoldersInPath( bool recursive ) const
{
	return FileSystem::GetFolderList( mPath.c_str(), recursive );
}

FileInfo::FileInfo()
: mFileHash(0)
{
}

FileInfo::FileInfo( const cbl::Char * file )
{
	Set( file );
}

FileInfo::FileInfo( const std::string & file )
{
	Set( file.c_str() );
}

FileInfo::FileInfo( const cbl::Char * path, const cbl::Char * file )
{
	Set( path, file );
}

FileInfo & FileInfo::operator = ( const cbl::Char * rhs )
{
	Set( rhs );
	return *this;
}

FileInfo & FileInfo::operator = ( const cbl::String& rhs )
{
	Set( rhs.c_str() );
	return *this;
}

const bool FileInfo::operator == ( const cbl::Char* rhs ) const
{
	return mFileHash == cbl::Hash::Generate( rhs );
}

const bool FileInfo::operator == ( const cbl::String& rhs ) const
{
	return mFileHash == cbl::Hash::Generate( rhs.c_str() );
}

const bool FileInfo::Exists( void ) const
{
	return FileSystem::FileCheckExists( GetFullFile().c_str() );
}

const bool FileInfo::operator == ( const cbl::FileInfo & rhs ) const
{
	return mFileHash == rhs.mFileHash;
}

const bool FileInfo::operator < ( const cbl::FileInfo & rhs ) const
{
	return mFileHash < rhs.mFileHash;
}

void FileInfo::Set( const cbl::Char * file )
{
	mPath = "";
	mFile = "";
	mFileHash = 0;

	if( !file || strlen( file ) == 0 )
		return;
	
	std::string stripper = file;
	std::replace( stripper.begin(), stripper.end(), '\\', '/' ); // Replace all backslashes with slashes.

	Int32 slashCount = 1; // remove the very first slashes.
	cbl::String fullname = "";
	for( size_t i = 0; i < stripper.size(); ++i )
	{
		if( stripper[i] == '/' ) {
			if( slashCount == 0 )		
				fullname.push_back( stripper[i] );
			++slashCount;
			continue;
		}

		slashCount = 0;
		fullname.push_back( stripper[i] );
	}

	mFileHash = cbl::Hash::Generate( fullname.c_str() );
	size_t pos = fullname.find_last_of( '/' );
	if( pos != std::string::npos ) {
		mPath = fullname.substr( 0, pos + 1 );
		mFile = fullname.substr( pos + 1 );
	}
	else {
		mFile = fullname;
	}

	if( mPath.length() > 1 && mPath[0] == '.' && mPath[1] == '/' ) mPath = mPath.substr(2);

	// Make sure our file extension is lower case.
	pos = mFile.find_last_of( '.' );
	if( pos != std::string::npos ) {
		for( size_t i = pos + 1; i < mFile.size(); ++i ) {
			mFile[i] = Char( ::tolower( mFile[i] ) );
		}
	}
}

void FileInfo::Set( const cbl::Char * path, const cbl::Char * file )
{
	if( path && ( strlen( path ) > 0 ) ) {
		std::string full( path );
		char c = full[ full.length() - 1 ];
		if( !( c == '/' || c == '\\' ) )
			full += '/';
		full += file;
		Set( full.c_str() );
	}
	else {
		Set( file );
	}
}

FileInfo::operator const std::string ( void ) const
{
	return mPath + mFile;
}

void FileInfo::ToString( String& str, const Type*, const void* obj, const FieldAttr* )
{
	str = (*(FileInfo*)obj).GetFullFile();
}

void FileInfo::FromString( const String& str, const Type*, void* obj, const FieldAttr* )
{
	(*(FileInfo*)obj).Set( str.c_str() );
}

cbl::Ostream & operator << ( cbl::Ostream& ostream, const cbl::FileInfo& fileInfo )
{
	ostream << fileInfo.GetFullFile();
	return ostream;
}

cbl::FileInfo operator + ( const cbl::String& lhs, const cbl::FileInfo& rhs )
{
	return cbl::FileInfo( ( lhs + "/" ) + rhs.GetFullFile() );
}

cbl::FileInfo operator + ( const cbl::Char* lhs, const cbl::FileInfo& rhs )
{
	return cbl::FileInfo( ( cbl::String( lhs ) + "/" ) + rhs.GetFullFile() );
}