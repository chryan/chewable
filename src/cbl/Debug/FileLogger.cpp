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
 * @file FileLogger.cpp
 * @brief File log stream class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Debug/FileLogger.h"

#if  CBL_LOGGING_ENABLED == CBL_ENABLED
// Chewable Headers //
#include "cbl/Util/TimeSpan.h"

using namespace cbl;

FileLogger::FileLogger( const Char * const filename, const Char * const title )
: ILogger()
, mFileName( filename )
{
	mFileStream.open( mFileName.c_str() );

	if( mFileStream.is_open() )
	{
		Uint32 lineLen = sMaxMessageWidth + sTimeStampWidth + sLogLevelWidth;

		mFileStream
			<< std::setfill( '*' ) 
			<< std::setw( lineLen ) << "*" << std::endl
			<< title << " [Created on: " << TimeSpan::GetSystemTime() << "]" << std::endl
			<< std::setw( lineLen ) << "*" << std::endl << std::setfill( ' ' );

		mFileStream << std::left
			<< std::setw( sTimeStampWidth ) << "TIME"
			<< std::setw( sLogLevelWidth ) << "LEVEL"
			<< std::setw( sFileNameWidth ) << "FILE"
			<< "MESSAGE"
			<< std::endl
			<< std::setfill( '-' ) 
			<< std::setw( lineLen ) << "-"
			<< std::endl << std::setfill( ' ' );

		mFileStream.close();
	}
}

FileLogger::~FileLogger()
{
	if( mFileStream.is_open() )
	{
		mFileStream.close();
	}
}

void FileLogger::Output( const Char * const message, LogLevel::Options msgLevel,
	const Char * file, Uint32 line )
{
	String timestamp = TimeSpan::GetSystemTime();

	mFileStream.open( mFileName.c_str(), std::ios::app );

	Ostringstream fileline;
	fileline << file << ":" << line;

	if( mFileStream.is_open() )
	{
		mFileStream
			<< std::setw( sTimeStampWidth ) << timestamp
			<< std::setw( sLogLevelWidth ) << GetLogLevelString( msgLevel )
			<< std::setw( sFileNameWidth ) << fileline.str() << " ";

		Istringstream stream( message );

		Uint32 lineCount	= 0;
		Uint32 spacing		= sTimeStampWidth + sLogLevelWidth + sFileNameWidth + 1;
		
		while( !stream.eof() )
		{
			std::string lineStr;
			std::getline( stream, lineStr, '\n' );

			while( lineStr.length() >= sMaxMessageWidth )
			{
				if( lineCount > 0 )
					mFileStream << std::setw( spacing ) << '|';
			
				size_t pos = lineStr.find_last_of( ' ', sMaxMessageWidth );

				mFileStream
					<< lineStr.substr( 0, pos )
					<< std::endl;

				++lineCount;
				if( pos == cbl::String::npos )
					break;

				lineStr = lineStr.substr( pos + 1 );
			}

			if( lineCount > 0 )
				mFileStream << std::setw( spacing ) << '|';

			mFileStream << lineStr << std::endl;
			++lineCount;
		}
		mFileStream.close();
	}
}

#endif // CBL_LOGGING_ENABLED == CBL_ENABLED
