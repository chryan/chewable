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
 * @file ConsoleLogger.h
 * @brief Console log stream class.
 */

#ifndef __CBL_CONSOLELOGGER_H_
#define __CBL_CONSOLELOGGER_H_

// Chewable Headers //
#include "cbl/Chewable.h"

#if CBL_LOGGING_ENABLED == CBL_ENABLED
// Chewable Headers //
#include "cbl/Debug/ILogger.h"

namespace cbl
{
	//! @brief Console log stream.
	//! 
	//! This logger writes to the console.
	class CBL_API ConsoleLogger :
		public ILogger
	{
	/***** Public Methods *****/
	public:
		//! Constructor.
		ConsoleLogger();
		//! Destructor.
		virtual ~ConsoleLogger();

	/***** Protected Methods *****/
	protected:
		//! @brief Console logger output method.
		//! @param	message		Message to write.
		//! @param	msgLevel	The log level of the message.
		//! @param	file		Source file.
		//! @param	line		Line number.
		virtual void Output( const Char * const message, LogLevel::Options msgLevel, 
			const Char * file, Uint32 line );
	};
}
#endif // CBL_LOGGING_ENABLED == CBL_ENABLED

#endif // __CBL_CONSOLELOGGER_H_
