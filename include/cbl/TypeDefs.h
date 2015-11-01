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
 * @file TypeDefs.h
 * @brief Useful types, typedefs and defines.
 */

#ifndef __CBL_TYPES_H_
#define __CBL_TYPES_H_

// Disable that annoying deprecation warning from MSVC.
#pragma warning ( disable : 4996 )

// Chewable Headers //
#include "cbl/Config.h"
#include "cbl/Platform.h"

// External Dependencies //
#include <string>
#include <sstream>
#include <fstream>

namespace cbl
{
	/***** Convenience macros *****/
	//! Void macro.
	#define CBL_VOID						(void)(0)
	//! Delete a pointer and set it to null.
	#define CBL_DELETE( ptr )				{ if( ptr ) { delete ( ptr ); ( ptr )=NULL; } }
	//! Delete a pointer to an array and set it to null.
	#define CBL_DELETE_ARRAY( ptr )			{ if( ptr ) { delete [] ( ptr ); ( ptr )=NULL; } }

	/***** Integral Types *****/
	typedef signed char			Int8;			//!< 8-bit signed integer
	typedef unsigned char		Uint8;			//!< 8-bit unsigned integer

	typedef short				Int16;			//!< 16-bit signed integer
	typedef unsigned short		Uint16;			//!< 16-bit unsigned integer

	typedef int					Int32;			//!< 32-bit signed integer
	typedef unsigned int		Uint32;			//!< 32-bit unsigned integer

	typedef long long			Int64;			//!< Windows 64-bit signed integer
	typedef unsigned long long	Uint64;			//!< Windows 64-bit signed integer

	typedef float				Float32;		//!< 32-bit float
	typedef double				Float64;		//!< 64-bit float

#if ( CBL_FP_DOUBLE == CBL_ENABLED )
	typedef Float64				Real;
#else
	typedef Float32				Real;
#endif

	typedef Float64				TimeReal;		//!< Timing float type.
		
	/***** String types *****/
	typedef char				Char;			//!< Char type.
	typedef unsigned char		Uchar;			//!< Unsigned char type.
	typedef wchar_t				Wchar;			//!< Wchar type.
	typedef std::ostream		Ostream;        //!< Output stream.
	typedef std::ostringstream	Ostringstream;  //!< Output string stream.
	typedef std::ofstream		Ofstream;       //!< Output file stream.
	typedef std::istream		Istream;        //!< Input stream.
	typedef std::istringstream	Istringstream;  //!< Input string stream.
	typedef std::ifstream		Ifstream;       //!< Input file stream.
	typedef std::fstream		Fstream;		//!< I/O file stream.

	#define Stdout				std::cout
	#define Stdin				std::cin
	#define Stderr				std::cerr

	#define	_STR( str )			str
}

#endif // __CBL_TYPES_H_
