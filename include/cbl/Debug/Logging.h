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
 * @file Logging.h
 * @brief Logging utilities. Include this file to use logging.
 */

#ifndef __CBL_LOGGING_H_
#define __CBL_LOGGING_H_

// Chewable Headers //
#include "cbl/Chewable.h"

#if CBL_LOGGING_ENABLED == CBL_ENABLED
// Chewable Headers //
#include "cbl/Debug/LogLevel.h"
#include "cbl/Debug/LogManager.h"

/***** Profiling Macros *****/
//! Add a logger to the log manager.
//! @param	logName	New logger name.
//! @param	newLog	New logger pointer (new ILogger).
#define LOG_ADDLOGGER( logName, newLog )\
	::cbl::LogManager::Instance().Add( logName, newLog )
//! Remove a logger from the log manager.
//! @param	logName	Log name to remove.
#define LOG_REMOVELOGGER( logName )\
	::cbl::LogManager::Instance().Remove( logName )
//! Find a logger in the log manager.
//! @param	logMgr	Log manager to use.
//! @param	logName	Log name to get.
#define LOG_GETLOGGER( logName )\
	::cbl::LogManager::Instance().Get( logName )
//! Log writing macro.
//! Uses the log manager's bitshift (<<) operator.
//! Setting CBL_LOGGING_ENABLED to CBL_DISABLED
//! automatically removes logging capabilities.
//! Usage:
//! @code
//! LOG( GLOBAL_LOGMANAGER, "Hello W" << 0 << "rld" );
//! @endcode
//! Output:
//! @code
//! Hello W0rld
//! @endcode
#define LOG( message )\
	{ ::cbl::LogManager::Instance() << message; ::cbl::LogManager::Instance().OutputMessage( __FILE__, __LINE__ ); }
//! Log error macro.
#define LOG_ERROR( message )\
	LOG( cbl::LogLevel::Error << message )
//! Log warning macro.
#define LOG_WARNING( message )\
	LOG( cbl::LogLevel::Warning << message )
//! Log debug macro.
#define LOG_DEBUG( message )\
	LOG( cbl::LogLevel::Debug << message )

#else // CBL_LOGGING_ENABLED == CBL_ENABLED

// Disable all logging.
#define LOG_ADDLOGGER( logName, newLog )
#define LOG_REMOVELOGGER( logName )
#define LOG_GETLOGGER( logName )
#define LOG( message )
#define LOG_ERROR( message )
#define LOG_WARNING( message )
#define LOG_DEBUG( message )

#endif // CBL_LOGGING_ENABLED == CBL_DISABLED

#endif // __CBL_LOGGING_H_
