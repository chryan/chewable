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
 * @file ILogger.cpp
 * @brief Log stream abstract class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Debug/ILogger.h"

#if CBL_LOGGING_ENABLED == CBL_ENABLED

using namespace cbl;

const Uint32	ILogger::sMaxMessageWidth		= 70;
const Uint32	ILogger::sTimeStampWidth		= 10;
const Uint32	ILogger::sLogLevelWidth			= 8;
const Uint32	ILogger::sFileNameWidth			= 30;

ILogger::ILogger()
: Threshold( LogLevel::All )
{
}

ILogger::~ILogger()
{
}

void ILogger::Write( const Char * const message, LogLevel::Options msgLevel,
	const Char * file, Uint32 line )
{
	CBL_MUTEX_SCOPEDLOCK( mtxWrite );
	if( msgLevel & Threshold )
		Output( message, msgLevel, file, line );
}

const String ILogger::GetLogLevelString( LogLevel::Options msgLevel )
{
	switch( msgLevel )
	{
	case LogLevel::Debug:
		return "Debug";
		break;

	case LogLevel::Info:
		return "Info";
		break;

	case LogLevel::Warning:
		return "Warning";
		break;

	case LogLevel::Error:
		return "Error";
		break;

	case LogLevel::All:
		return "All";
		break;
	}

	return "None";
}

#endif // CBL_LOGGING_ENABLED == CBL_ENABLED
