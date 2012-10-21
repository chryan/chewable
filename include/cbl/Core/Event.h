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
 * @file Event.h
 * @brief Event include file.
 * 
 * Usage example:
 * @code
 * namespace E
 * {
 *     typedef cbl::Event< void( int ) > KeyPress; //!< params: keycode.
 * }
 *
 * class TestClass
 * {
 * public:
 *     void KeyPressTest( int keycode ) { printf( "pressed %d", keycode ); }
 * };
 * 
 * E::KeyPress OnKeyPress;
 * TestClass testClass;
 * OnKeyPress += E::KeyPress::Method<CBL_E_METHOD(TestClass,KeyPressTest)>(&testClass);
 * OnKeyPress( 5 );
 *
 * // Output: pressed 5
 * @endcode
 */

#ifndef __CBL_EVENT_H_
#define __CBL_EVENT_H_

// Chewable Headers //
#include "cbl/Chewable.h"

namespace cbl
{
#ifdef CBL_TPLFUNCTION_PREFERRED_SYNTAX
	template <typename TSignature> class Event;
#endif
}

// Chewable Headers //
#include "cbl/Util/Delegate.h"
#include "Detail/Event_List.h"

//! Convenience macro.
//! Usage: Event< void() >::Method<CBL_E_METHOD( classType, classMethod )>( classInstance );
#define CBL_E_METHOD( classType, classMethod )\
	classType,&classType::classMethod

#endif // __CBL_EVENT_H_
