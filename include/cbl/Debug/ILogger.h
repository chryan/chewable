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
 * @file ILogger.h
 * @brief Log stream abstract class.
 */

#ifndef __CBL_ILOGGER_H_
#define __CBL_ILOGGER_H_

// Chewable Headers //
#include "cbl/Chewable.h"

#if CBL_LOGGING_ENABLED == CBL_ENABLED

// Chewable Headers //
#include "cbl/Util/Noncopyable.h"
#include "cbl/Util/Property.h"
#include "cbl/Debug/LogLevel.h"

namespace cbl
{
	//! @brief Abstract log stream class.
	//! 
	//! Derive from this class to create a new log stream.
	//! For an example on how this class is used, see FileLogger.
	//! @see FileLogger
	class CBL_API ILogger :
		Noncopyable
	{
	/***** Static Constants *****/
	public:
		static const Uint32		sMaxMessageWidth;	//!< Maximum message line width.
		static const Uint32		sTimeStampWidth;	//!< Time stamp line width.
		static const Uint32		sLogLevelWidth;		//!< Log level line width.
		static const Uint32		sFileNameWidth;		//!< File name line width.

	/***** Properties *****/
	public:
		Uint16					Threshold;			//!< Log stream threshold.

	/***** Static Methods *****/
	public:
		//! Converts a log level enum into a string.
		//! @param	msgLevel	Message level.
		//! @return				Log level string.
		static const String GetLogLevelString( LogLevel::Options msgLevel );

	/***** Public Methods *****/
	public:
		//! Default constructor.
		ILogger();
		//! Virtual destructor.
		virtual ~ILogger();
		//! @brief Write a message to the log stream.
		//! 
		//! The message will be written if log stream threshold corresponds with
		//! the message log level.
		//! @param	message		Message to write.
		//! @param	msgLevel	The log level of the message.
		void Write( const Char * const message, LogLevel::Options msgLevel,
			const Char * file, Uint32 line );

	/***** Protected Methods *****/
	protected:
		//! Log stream's output method to be overridden.
		//! @param	message		Message to write.
		//! @param	msgLevel	The log level of the message.
		virtual void Output( const Char * const message, LogLevel::Options msgLevel,
			const Char * file, Uint32 line ) = 0;
	};
}

#endif // CBL_LOGGING_ENABLED == CBL_ENABLED

#endif // __CBL_ILOGGER_H_
