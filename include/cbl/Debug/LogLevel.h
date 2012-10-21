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
 * @file LogLevel.h
 * @brief Log levels.
 */

#ifndef __CBL_LOGLEVEL_H_
#define __CBL_LOGLEVEL_H_

// Chewable Headers //
#include "cbl/Chewable.h"

#if CBL_LOGGING_ENABLED == CBL_ENABLED

namespace cbl
{
	namespace LogLevel
	{
		enum Options
		{
			Debug	= 1 << 0,	//!< Log debug messages.
			Info	= 1 << 1,	//!< Log info messages.
			Warning	= 1 << 2,	//!< Log warning messages.
			Error	= 1 << 3,	//!< Log error messages.
			All		= 0x0F,		//!< Log all messages.
		};
	}
}

#endif

#endif // __CBL_LOGLEVEL_H_