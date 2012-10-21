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
 * @file FileLogger.h
 * @brief File log stream class.
 */

#ifndef __CBL_FILELOGGER_H_
#define __CBL_FILELOGGER_H_

// Chewable Headers //
#include "cbl/Chewable.h"

#if CBL_LOGGING_ENABLED == CBL_ENABLED

// Chewable Headers //
#include "cbl/Debug/ILogger.h"

namespace cbl
{
	//! @brief File log stream.
	//! 
	//! This logger writes to a specified file.
	class CBL_API FileLogger :
		public ILogger
	{
	/***** Public Methods *****/
	public:
		//! Constructor.
		//! @param	filename	Filename to write to.
		//! @param	title		File title.
		FileLogger( const Char * const filename, const Char * const title = "Chewable Log" );

		//! Destructor.
		virtual ~FileLogger();
		
	/***** Protected Methods *****/
	protected:
		//! @brief Console logger output method.
		//! @param	message		Message to write.
		//! @param	msgLevel	The log level of the message.
		//! @param	file		Source file.
		//! @param	line		Line number.
		virtual void Output( const Char * const message, LogLevel::Options msgLevel,
			const Char * file, Uint32 line );

	/***** Private Members *****/
	private:
		String				mFileName;		//!< Filename to write log entries to.
		Ofstream			mFileStream;	//!< File stream.
	};
}
#endif // CBL_LOGGING_ENABLED == CBL_ENABLED

#endif // __CBL_FILELOGGER_H_
