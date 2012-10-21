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
 * @file IDrawable.h
 * @brief Drawable interface class.
 */

#ifndef __CBL_IDRAWABLE_H_
#define __CBL_IDRAWABLE_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Property.h"
#include "cbl/Core/GameTime.h"

namespace cbl
{
	//! @brief Drawable interface.
	class CBL_API IDrawable
	{
	/***** Private Members *****/
	public:
		Int32			DrawOrder;	//!< Draw order.
		bool			Visible;	//!< Visibility.

	/***** Public Methods *****/
	public:
		//! Default constructor.
		IDrawable();
		//! Empty virtual destructor.
		virtual ~IDrawable() {}
		//! Pure virtual draw function.
		virtual void Draw( const GameTime & time ) = 0;
	};
	
	//! Comparison operator.
	CBL_API
	bool operator < ( const IDrawable & lhs, const IDrawable & rhs );
}

#endif // __CBL_IDRAWABLE_H_
