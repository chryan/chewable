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
 * @file Config.h
 * @brief Configuration macros.
 */

#ifndef __CBL_CONFIG_H_
#define __CBL_CONFIG_H_

namespace cbl
{
	/***** Versioning *****/
    #define CBL_VERSION_MAJOR 1
    #define CBL_VERSION_MINOR 0
    #define CBL_VERSION_PATCH 0

	/***** Debug Configurations *****/
	#if ( DEBUG || _DEBUG ) 
		#define CBL_DEBUG	// Turn on debug.
	#endif

	#if ( STATIC_LIB || _STATIC_LIB )
		#define CBL_STATIC_LIB  // Turn on STATIC LIB.
	#endif

	/***** Enable/Disable Macros *****/
	#define CBL_DISABLED				0
	#define CBL_ENABLED					1

	/***** Text Configurations *****/
	#define CBL_TEXT_STD				1	//!< Standard ANSI text formatting.
	#define CBL_TEXT_WIDE				2	//!< UTF-16 text.
	//! Our text format.
	#define CBL_TEXT_FORMAT				CBL_TEXT_STD

	/***** Use custom Chewable string *****/
	#define CBL_CUSTOM_STRING			CBL_DISABLED

	/***** Threading Configurations *****/
	//! Make Chewable thread safe.
	#define CBL_THREAD_SAFE				CBL_DISABLED

	/***** Float Point Configurations *****/
	//! Use double floating point precision.
	#define CBL_FP_DOUBLE				CBL_DISABLED

	/***** Assertion Configurations *****/
	#define CBL_ASSERT_FATAL			1	//!< Program halting assertions.
	#define CBL_ASSERT_SILENT			2	//!< Silent assertions.
	#define CBL_ASSERT_NONE				3	//!< Disable assertions
	//! Assertion mode.
	#define CBL_ASSERT_MODE				CBL_ASSERT_FATAL

	/***** Memory Management Configurations *****/
	#define CBL_MEMORY_MANAGER_DEBUG	0	//!< Use debug memory allocator.
	#define CBL_MEMORY_MANAGER_STD		1	//!< Use standard memory allocator.

	//! Memory manager to be used.
	#ifdef CBL_DEBUG
		#define CBL_MEMORY_MANAGER		CBL_MEMORY_MANAGER_DEBUG
	#else
		#define CBL_MEMORY_MANAGER		CBL_MEMORY_MANAGER_STD
	#endif

	//! Use Visual Leak Detector for debugging.
	#define CBL_VLD_ENABLED				CBL_DISABLED

	/***** Logging Configurations *****/	
	//! Logging mode. 1 to enable, 0 to disable.
	#define CBL_LOGGING_ENABLED			CBL_ENABLED
	#define CBL_FILE_LOGGER_ENABLED		CBL_DISABLED

	/***** Profiling Configurations *****/
	//! Profiling mode.
	#define CBL_PROFILING_ENABLED		CBL_DISABLED

	/***** Delegate/Event Syntax Configuration *****/
	#define CBL_TPLFUNCTION_PREFERRED_SYNTAX

	/***** SSE Configuration *****/
	#define CBL_SSE_ENABLED				CBL_ENABLED
}

#endif // __CBL_CONFIG_H_
