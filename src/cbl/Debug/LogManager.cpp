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
 * @file LogManager.cpp
 * @brief Log management class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Debug/LogManager.h"

#if CBL_LOGGING_ENABLED == CBL_ENABLED
// Chewable Headers //
#include "cbl/Debug/ILogger.h"
#include "cbl/Debug/Assert.h"

using namespace cbl;

LogManager::LogManager()
: Threshold( LogLevel::All )
, mWriteThreshold( LogLevel::Info )
{
}

LogManager::~LogManager()
{
	if( !mLogs.empty() )
	{
		CBL_FOREACH( LoggerList, it, mLogs )
		{
			CBL_DELETE( it->second );
		}

		mLogs.clear();
	}
}

void LogManager::Write( const Char * const message, LogLevel::Options msgLevel,
	const Char * file, Uint32 line )
{
	if( msgLevel & Threshold )
	{
		std::string filename = file;
		size_t found = filename.find_last_of("\\");
		
		if( found == String::npos )
			found = filename.find_last_of("/");

		if( found != String::npos )
			filename = filename.substr( found + 1 );

		CBL_FOREACH( LoggerList, it, mLogs )
		{
			it->second->Write( message, msgLevel, filename.c_str(), line );				
		}
	}
}

void LogManager::Add( const Char * const logName, ILogger * logger )
{
	LoggerList::iterator findIt = mLogs.find( logName );
	CBL_ASSERT( findIt == mLogs.end(), "Logger already exists!" );
	mLogs.insert( LoggerEntry( logName, logger ) );
}

void LogManager::Remove( const Char * const logName )
{
	LoggerList::iterator findIt = mLogs.find( logName );
	CBL_ASSERT( findIt != mLogs.end(), "Logger does not exist!" );
	CBL_DELETE( findIt->second );
	mLogs.erase( findIt );
}

ILogger * LogManager::Get( const Char * const logName )
{
	LoggerList::iterator findIt = mLogs.find( logName );
	return findIt != mLogs.end() ? findIt->second : NULL;
}

LogManager & LogManager::operator << ( LogLevel::Options logLevel )
{
	mWriteThreshold = logLevel;
	return *this;
}

void LogManager::OutputMessage( const Char * file, Uint32 line )
{
	Write( mBuffer.str().c_str(), mWriteThreshold, file, line );
	
	// Reset the buffer and threshold.
	{
		mBuffer.str("");
		mWriteThreshold = LogLevel::Info;
	}
}

#endif // CBL_LOGGING_ENABLED == CBL_ENABLED
