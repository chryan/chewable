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
 * @file Platform.h
 * @brief Platform specific macros file.
 */

#ifndef __CBL_PLATFORM_H_
#define __CBL_PLATFORM_H_

#include <cbl/Config.h>

namespace cbl
{
	/***** Platform Specific Configurations *****/
	#define CBL_PLATFORM_WIN32		1   //!< Windows 32-bit.
	#define CBL_PLATFORM_WIN64		2   //!< Windows 64-bit.
	#define CBL_PLATFORM_LINUX		3   //!< Linux.
	#define CBL_PLATFORM_APPLE		4	//!< Apple.

	#define CBL_COMPILER_MSVC		1	//!< Visual Studio Compiler.
	#define CBL_COMPILER_GNUC		2	//!< GCC Compiler.
	#define CBL_COMPILER_BORL		3	//!< Borland C++ Compiler.

	#define CBL_ARCHITECTURE_32	1	//!< 32-bit architecture.
	#define CBL_ARCHITECTURE_64	2	//!< 64-bit architecture.

	// Find compiler type and version.
	#if defined( _MSC_VER )
		#define CBL_COMPILER		CBL_COMPILER_MSVC
		#define CBL_COMP_VER		_MSC_VER
		#define CBL_FASTCALL		__fastcall
	#elif defined( __GNUC__ )
		#define CBL_COMPILER CBL_COMPILER_GNUC
		#define CBL_COMP_VER (((__GNUC__)*100) + (__GNUC_MINOR__*10) + __GNUC_PATCHLEVEL__)
		#define CBL_FASTCALL
	#elif defined( __BORLANDC__ )
		#define CBL_COMPILER CBL_COMPILER_BORL
		#define CBL_COMP_VER __BCPLUSPLUS__
		#define CBL_FASTCALL
	#else
		#pragma error "No known compiler. Abort! Abort!"
	#endif

	// Find current platform type.
	#if defined( __WIN32__ ) || defined( _WIN32 )
		#define CBL_PLATFORM	CBL_PLATFORM_WIN32
	#elif defined( __WIN64__ ) || defined( _WIN64 ) 
		#define CBL_PLATFORM	CBL_PLATFORM_WIN64
	#else
		#error Unsupported platform.
	#endif

	// Find the arch type
	#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) \
		|| defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
		#define CBL_ARCHITECTURE CBL_ARCHITECTURE_64
	#else
		#define CBL_ARCHITECTURE CBL_ARCHITECTURE_32
	#endif

	/***** Windows Settings *****/
	#if ( CBL_PLATFORM == CBL_PLATFORM_WIN32 ) || ( CBL_PLATFORM == CBL_PLATFORM_WIN64 )
		// If we're not including this from a client build, specify that the stuff
		// should get exported. Otherwise, import it.
		#define CBL_API_EXPORT			__declspec( dllexport )
		#define CBL_API_IMPORT			__declspec( dllimport )

		#if defined( CBL_STATIC_LIB )
			// Linux compilers don't have symbol import/export directives.
			#define CBL_API
			#define CBL_PRIVATE
		#else
			#if defined( CBL_EXPORT )
				#define CBL_API		CBL_API_EXPORT
			#else
				#if defined( __MINGW32__ )
					#define CBL_API
				#else
					#define CBL_API	CBL_API_IMPORT
				#endif
			#endif

			#define CBL_PRIVATE
		#endif

		#ifndef _WIN32_WINNT
			//! Windows XP and above.
			#define _WIN32_WINNT    0x0501
		#endif

		//! Disable the Windows min/max macros.
		#define NOMINMAX
		//! Aligned malloc.
		#define aligned_malloc          _aligned_malloc
		//! Aligned free.
		#define aligned_free            _aligned_free
		//! Windows XP and above.
		#ifndef _WIN32_WINDOWS
			#define _WIN32_WINDOWS  0x0501
		#endif

		#ifndef WIN32_LEAN_AND_MEAN
			// Use minimal Windows libraries.
			#define WIN32_LEAN_AND_MEAN
		#endif
	#endif
}

#endif // __CBL_PLATFORM_H_
