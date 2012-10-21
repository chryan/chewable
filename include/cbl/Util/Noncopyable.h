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
 * @file Noncopyable.h
 * @brief Utility class to disable the copy constructor and assignment operator.
 */

#ifndef __CBL_NONCOPYABLE_H_
#define __CBL_NONCOPYABLE_H_

// Disable annoying warning about non dll-interface class.
#pragma warning( disable:4275 )

namespace cbl
{
	//! @brief Inherit from this class to prevent default object copying.
	//!
	//! Private copy constructor and copy assignment ensure that classes
	//! derived from Noncopyable cannot be copied.
	//! @code
	//! class Example : Noncopyable
	//! @endcode
	class Noncopyable
	{
	/***** Protected Methods *****/
	protected:
		//! Empty default constructor.
		Noncopyable()	{}
		//! Empty destructor.
		~Noncopyable()	{}
		
	/***** Private Methods *****/
	private:
		//! Empty copy constructor.
		Noncopyable( const Noncopyable & );
		//! Empty copy assignment operator.
		const Noncopyable & operator = ( const Noncopyable & );
	};
}

#endif // __CBL_NONCOPYABLE_H_
