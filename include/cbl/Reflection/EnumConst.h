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
 * @file Type.h
 * @brief Type information.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

#ifndef __CBL_ENUMCONST_H_
#define __CBL_ENUMCONST_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/CName.h"
#include "cbl/Util/Noncopyable.h"

namespace cbl
{
	//! Enum constant for Type.
	class CBL_API EnumConst
	{
	/***** Public Methods *****/
	public:
		//! Constructor.
		//! @param	name	Enum name.
		//! @param	name	Enum value.
		EnumConst( const CName& name, Uint32 value )
			: Name( name ), Value(value) {}
		
	/***** Public Members *****/
	public:
		CName	Name;	//!< Enum name.
		Uint32	Value;	//!< Enum value.
	};
}

#endif // __CBL_ENUMCONST_H_