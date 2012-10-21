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
 * @file GameTime.h
 * @brief Game time structure.
 */

#ifndef __CBL_GAMETIME_H_
#define __CBL_GAMETIME_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Property.h"
#include "cbl/Util/TimeSpan.h"

namespace cbl
{
	//! @brief This class holds a snapshot of the game timing state.
	//!
	//! It is used in the Update methods of all IUpdatable objects.
	class CBL_API GameTime
	{
	/***** Public Members *****/
	public:
		TimeSpan			Total;				//!< The amount of game time since the start of the game.
		TimeSpan			Elapsed;			//!< The amount of elapsed game time since the last update.
		TimeSpan			TotalReal;			//!< The amount of real time since the start of the game.
		TimeSpan			ElapsedReal;		//!< The amount of elapsed real time since the last update.
		bool				IsRunningSlowly;	//!< Indicates if the game is running slow.

	/***** Public Methods *****/
	public:
		//! Default constructor.
		GameTime();
	};

	/***** Inline Methods *****/
	inline GameTime::GameTime()
		: Total( 0 )
		, Elapsed( 0 )
		, TotalReal( 0 )
		, ElapsedReal( 0 )
		, IsRunningSlowly( false )
	{
	}
}

#endif // __CBL_GAMETIME_H_
