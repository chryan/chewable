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
 * @file Assert.h
 * @brief Assertion macros and utilities.
 */

#ifndef __CBL_ASSERT_H_
#define __CBL_ASSERT_H_

// Chewable Headers //
#include "cbl/Chewable.h"

namespace cbl
{
	//! Assertion break.
	//! Usage:
	//! @code
	//! Char * tmp = NULL;
	//! CBL_ASSERT_TRUE( tmp );
	//! CBL_ASSERT( tmp != NULL, "tmp is null!" );
	//! @endcode
	//! @param	expression	Expression
	//! @param	message		Error message.
	//! @param	filename	Source filename.
	//! @param	line		Source file line number.
	CBL_API void Assert( Char * const expression,
		const Char * const message,
		const Char * const filename,
		const size_t line );
	
	#define CBL_FORCE_ASSERT( message )\
		{ ::cbl::Assert( "Force assert.", message, __FILE__, __LINE__ ); }

	#if CBL_ASSERT_MODE == CBL_ASSERT_FATAL
		//! Assert expression is not null.
		#define CBL_ASSERT_TRUE( exp )\
			{ if( !(exp) ) ::cbl::Assert( #exp, "Expression is false. Expected true.", __FILE__, __LINE__ ); }
		//! Assert expression is null.
		#define CBL_ASSERT_FALSE( exp )\
			{ if( (exp) ) ::cbl::Assert( #exp, "Expression is true. Expected false.", __FILE__, __LINE__ ); }
		//! Assert expression.
		#define CBL_ASSERT( exp, message )\
			{ if( !(exp) ) { std::ostringstream m; m << message; ::cbl::Assert( #exp, m.str().c_str(), __FILE__, __LINE__ ); } }
		#define CBL_FAIL( message )\
			{ std::ostringstream m; m << message; ::cbl::Assert( "Assertion failed.", m.str().c_str(), __FILE__, __LINE__ ); }
	#elif CBL_ASSERT_MODE == CBL_ASSERT_SILENT
		#define CBL_ASSERT_TRUE( exp )			CBL_VOID
		#define CBL_ASSERT_FALSE( exp )			CBL_VOID
		#define CBL_ASSERT( exp, message )		CBL_VOID
		#define CBL_FAIL( message )				CBL_VOID
	#else
		#define CBL_ASSERT_TRUE( exp )			CBL_VOID
		#define CBL_ASSERT_FALSE( exp )			CBL_VOID
		#define CBL_ASSERT( exp, message )		CBL_VOID
		#define CBL_FAIL( message )				CBL_VOID
	#endif

	namespace detail
	{
		template <bool> struct StaticAssertFailure;
		template <> struct StaticAssertFailure<true> { };
	}

	#define CBL_STATIC_ASSERT( condition ) sizeof( cbl::detail::StaticAssertFailure<condition> )
}

#endif // __CBL_ASSERT_H_
