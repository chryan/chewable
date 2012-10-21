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
 * @file ConsoleLogger.cpp
 * @brief Console log stream class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Debug/ConsoleLogger.h"

#if CBL_LOGGING_ENABLED == CBL_ENABLED
// Chewable Headers //
#include "cbl/Util/TimeSpan.h"

using namespace cbl;

ConsoleLogger::ConsoleLogger()
: ILogger()
{
}

ConsoleLogger::~ConsoleLogger()
{
}

void ConsoleLogger::Output( const Char * const message, LogLevel::Options msgLevel, 
	const Char * file, Uint32 line )
{
	std::string timestamp = TimeSpan::GetSystemTime();

	Ostringstream fileline;
	fileline << file << ":" << line;

	Stdout << std::left
		<< "[" << timestamp << " > "
		<< std::setw( sLogLevelWidth )
		<< GetLogLevelString( msgLevel ) << "] "
		<< std::setw( sFileNameWidth )
		<< fileline.str() << " ";

	Istringstream stream( message );

	Uint32 lineCount	= 0;
	Uint32 spacing		= timestamp.length() + sLogLevelWidth + sFileNameWidth;

	while( !stream.eof() )
	{
		std::string lineStr;
		std::getline( stream, lineStr, '\n' );

		while( lineStr.length() >= sMaxMessageWidth )
		{
			if( lineCount > 0 )
				Stdout << std::setw( spacing ) << '|';
			
			size_t pos = lineStr.find_last_of( ' ', sMaxMessageWidth );

			Stdout
				<< lineStr.substr( 0, pos )
				<< std::endl;

			++lineCount;
			if( pos == std::string::npos )
				break;

			lineStr = lineStr.substr( pos + 1 );
		}

		if( lineCount > 0 )
			Stdout << std::setw( spacing ) << '|';

		Stdout << lineStr << std::endl;
		++lineCount;
	}
}

#endif // CBL_LOGGING_ENABLED == CBL_ENABLED
