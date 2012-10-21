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
 * @file GameComponent.h
 * @brief Game component abstract class.
 */

#ifndef __CBL_GAMECOMPONENT_H_
#define __CBL_GAMECOMPONENT_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Core/IUpdatable.h"
#include "cbl/Util/Property.h"
#include "cbl/Util/Noncopyable.h"

namespace cbl
{
	//! @brief GameComponents are attached to a game to provide access to its functionality (abstract class).
	//! See http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.gamecomponent_members.aspx
	//! Several game component methods are called automatically when added to a Game object:
	//! - Initialise is called when the game component is added before the Game's intialisation.
	//! - Update method is run every frame.
	//! - Shutdown is called when the Game is shutting down.
	//!
	//! If a game component is added after the Game object has been initialised, Initialise must be called manually.
	class CBL_API GameComponent :
		public IUpdatable,
		Noncopyable
	{
	/***** Public Members *****/
	public:
		cbl::Game			& Game;	//!< Reference to game.

	/***** Public Methods *****/
	public:
		//! Explicit constructor.
		//! @param	game	Game pointer.
		explicit GameComponent( cbl::Game & game );
		//! Destructor.
		virtual ~GameComponent();
		//! Pure virtual function to initialise component.
		virtual void Initialise( void ) = 0;
		//! Pure virtual function to shut down component.
		virtual void Shutdown( void ) = 0;
		//! Pure virtual update function (from IUpdatable).
		virtual void Update( const GameTime & time ) = 0;
	};
}

#endif // __CBL_GAMECOMPONENT_H_
