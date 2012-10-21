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
 * @brief File info class.
 */

#ifndef __CBL_FILEINFO_H_
#define __CBL_FILEINFO_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Property.h"
#include "cbl/Util/Hash.h"

namespace cbl
{
	//! Utility to extract path and extension names out of a file path string.
	class CBL_API FileInfo
	{
	/***** Types *****/
	public:
		typedef std::vector< cbl::FileInfo>			List;

	/***** Properties *****/
	public:
		GETTER_AUTO_CREF( cbl::String, Path );		//!< Get the file's path.
		GETTER_AUTO_CREF( cbl::String, File );		//!< Get the file name (with extension).
		cbl::String GetFileNoExt( void ) const;		//!< Get the file name without the extension.
		cbl::String GetExtension( void ) const;		//!< Get the file's extension.
		cbl::String GetFullFile( void ) const;		//!< Get the full file name (with path).
		cbl::String GetUpOneLevel( void ) const;	//!< Get the path directory one level up.
		//! Get all files in the current fileinfo path.
		//! @param	recursive	Recursively scan for files.
		//! @return				Folder list.
		List GetFilesInPath( bool recursive = false ) const;
		//! Get all files in the current fileinfo path.
		//! @param	exclude		Comma separated file extensions to exclude. e.g. exe,txt,fbx
		//! @param	recursive	Recursively scan for files.
		//! @return				Folder list.
		List GetFilesInPathExclude( const cbl::Char* excludes, bool recursive = false ) const;
		//! Get all files in the current fileinfo path.
		//! @param	exclude		Comma separated file extensions to include. Only files of specified type will appear in the list.
		//! @param	recursive	Recursively scan for files.
		//! @return				Folder list.
		List GetFilesInPathInclude( const cbl::Char* includes, bool recursive = false ) const;
		//! Get all files in the current fileinfo path.
		//! @param	recursive	Recursively scan for paths.
		//! @return				Folder list.
		List GetFoldersInPath( bool recursive = false ) const;	

		//! Check if file exists.
		const bool Exists( void ) const;
		//! Set a new file.
		//! @param	file	File to set.
		void Set( const cbl::Char * file );
		//! Set a new file with path.
		//! @param	path	File path.
		//! @param	file	File to set.
		void Set( const cbl::Char * path, const cbl::Char * file );
		
	/***** Public Methods *****/
	public:
		//! Constructor.
		FileInfo();
		//! Overloaded constructor.
		//! @param	file		File to set.
		FileInfo( const cbl::Char* file );
		//! Overloaded constructor.
		//! @param	file		File to set.
		FileInfo( const cbl::String& file );
		//! Overloaded constructor.
		//! @param	path		File path.
		//! @param	file		File to set.
		FileInfo( const cbl::Char* path, const cbl::Char* file );
		//! Assignment operator.
		//! Equivalent to calling Set().
		FileInfo & operator = ( const cbl::Char* rhs );
		//! Assignment operator.
		//! Equivalent to calling Set().
		FileInfo & operator = ( const cbl::String& rhs );
		//! Comparison operator to check if full path names are the same.
		const bool operator == ( const cbl::Char* rhs ) const;
		//! Comparison operator to check if full path names are the same.
		const bool operator == ( const cbl::String& rhs ) const;
		//! Comparison operator to check if full path names are the same.
		const bool operator == ( const cbl::FileInfo& rhs ) const;
		//! Less-than operator for STL containers.
		const bool operator < ( const cbl::FileInfo& rhs ) const;
		//! Conversion operator to string.
		//! @return				Returns full file name with path.
		operator const cbl::String ( void ) const;

	/***** Static Public Methods *****/
	public:
		//! Used for serialisation.
		static void ToString( String& str, const Type*, const void* obj, const FieldAttr* );
		//! Used for deserialisation.
		static void FromString( const String& str, const Type*, void* obj, const FieldAttr* );
		
	/***** Private Members *****/
	private:
		cbl::String		mPath;
		cbl::String		mFile;
		cbl::HashValue	mFileHash;

		friend class CblRegistrar;
	};
}

CBL_TYPE( cbl::FileInfo, FileInfo );
	
/***** Helper functions *****/
//! Insertion operator for use with std::ostream.
CBL_API cbl::Ostream & operator << ( cbl::Ostream& ostream, const cbl::FileInfo& fileInfo );
//! Append a path in front of the file info.
CBL_API cbl::FileInfo operator + ( const cbl::String& lhs, const cbl::FileInfo& rhs );
//! Append a path in front of the file info.
CBL_API cbl::FileInfo operator + ( const cbl::Char* lhs, const cbl::FileInfo& rhs );

#endif // __CBL_FILEINFO_H_
