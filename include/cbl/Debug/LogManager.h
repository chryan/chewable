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
 * @file LogManager.h
 * @brief Log management class.
 */

#ifndef __CBL_LOGMANAGER_H_
#define __CBL_LOGMANAGER_H_

// Chewable Headers //
#include "cbl/Chewable.h"

#if CBL_LOGGING_ENABLED == CBL_ENABLED
// Chewable Headers //
#include "cbl/Debug/ILogger.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Util/Property.h"
#include "cbl/Util/Singleton.h"
#include "cbl/Thread/Mutex.h"

namespace cbl
{
	//! @brief Log management class.
	//! 
	//! The log manager handles the lifecycle of every logger added to it.
	//! Writing a message through the log manager will map the message to the containing
	//! loggers.
	//! Usage:
	//! @code
	//! class ConsoleLogger : public ILogger
	//! {
	//! protected:
	//!     virtual void Output( Char const * const message, LogLevel::Options msgLevel )
	//!     {
	//!         std::cout << message << std::endl;
	//!     }
	//! };
	//! 
	//! LogManager logMgr;
	//! logMgr.Add( "ConsoleLogger", new ConsoleLogger );
	//! logMgr.Write( "Hello World!", LogLevel::Info );
	//! logMgr.SetThreshold( LogLevel::Warning );
	//! logMgr.Write( "No output.", LogLevel::Info );
	//! logMgr.Remove( "ConsoleLogger" );
	//! logMgr.Write( "No output." );
	//! @endcode
	class CBL_API LogManager
	{
	/***** Public Members *****/
	public:
		Uint16				Threshold;		//!< Log manager threshold.

	/***** Public Methods *****/
	public:
		//! Destructor.
		~LogManager();
		//! Write a log message to the containing loggers.
		//! @param	message		Message to write.
		//! @param	msgLevel	The log level of the message.
		void Write( const Char * const message, LogLevel::Options msgLevel,
			const Char * file, Uint32 line );
		//! Add a new logger to the manager.
		//! @param	logName		Identifying logger name.
		//! @param	logger		Pointer to a new logger instance.
		void Add( const Char * const logName, ILogger * logger );
		//! Remove an existing logger from the manager.
		//! @param	logName		Identifying logger name.
		void Remove( const Char * const logName );
		//! Retrieve an existing logger type from the manager.
		//! @param	logName		Identifying logger name.
		//! @return				Returns a pointer to the logger or NULL if not found.
		ILogger * Get( const Char * const logName );
		//! Insertion operator.
		//! Logs message to all containing loggers.
		//! @tparam	T			Value type.
		template< typename T >
		LogManager & operator << ( const T & value );
		//! Insertion operator.
		//! Sets the log manager threshold.
		//! @param	logLevel	Threshold to set.
		LogManager & operator << ( LogLevel::Options logLevel );
		//! Write the message with the source file and line names.
		//! @param	file	Source file.
		//! @param	line	Line number.
		void OutputMessage( const Char * file, Uint32 line );

	/***** Private Methods *****/
	private:
		//! Default constructor.
		LogManager();

	/***** Internal Types *****/
	private:
		typedef std::map< std::string, ILogger * >		LoggerList;		//!< Logger list.
		typedef std::pair< std::string, ILogger * >		LoggerEntry;	//!< Logger list entry.

	/***** Private Members *****/
	private:
		LoggerList							mLogs;			//!< Loggers list.
		mutable Ostringstream				mBuffer;		//!< Log buffer.
		mutable LogLevel::Options			mWriteThreshold;//!< Log buffer threshold.
		CBL_MUTEX_DECLARE( mtxLogging );
		CBL_DECL_SINGLETON( LogManager );
	};
	
	template< typename T >
	LogManager & LogManager::operator << ( const T & value )
	{
		CBL_MUTEX_SCOPEDLOCK( mtxLogging );
		mBuffer << value;
		return *this;
	}
#endif
}

#endif // __CBL_LOGMANAGER_H_
