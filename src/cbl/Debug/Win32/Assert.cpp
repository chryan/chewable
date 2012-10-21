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
 * @file Assert.cpp
 * @brief Assertion macros and utilities.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Debug/Assert.h"

#if CBL_PLATFORM == CBL_PLATFORM_WIN32
// External Dependencies //
#include <windows.h>

using namespace cbl;

void cbl::Assert( Char * const expression,
	const Char * const message,
	const Char * const filename,
	const size_t line )
{
	String file( filename );
	Ostringstream msg;

	msg << _STR( "Expression: " ) << expression << std::endl
		<< "@ " << file.substr( file.find_last_of( '\\' ) + 1 ) << ":" << line
		<< std::endl << std::endl 
		<< _STR( "Message: ") << std::endl << message << std::endl;

	int result = ::MessageBox( NULL, msg.str().c_str(),
		_STR("Assertion Error"), MB_ABORTRETRYIGNORE | MB_ICONERROR | MB_DEFBUTTON2 );

	switch( result )
	{
	case IDABORT:
		::exit( EXIT_FAILURE );
		break;

	case IDRETRY:
		::DebugBreak();
		break;

	case IDIGNORE:
		break;
	}
}
#endif
