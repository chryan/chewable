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
 * @file DrawableGameComponent.h
 * @brief Drawable game component abstract class.
 */

#ifndef __CBL_DRAWABLEGAMECOMPONENT_H_
#define __CBL_DRAWABLEGAMECOMPONENT_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Core/IDrawable.h"
#include "cbl/Core/GameComponent.h"
#include "cbl/Util/Property.h"

namespace cbl
{
	//! @brief A drawable game component.
	//! Modelled after from http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.drawablegamecomponent_members.aspx
	//! @see GameComponent
	class CBL_API DrawableGameComponent :
		public GameComponent,
		public IDrawable
	{
	/***** Public Methods *****/
	public:
		//! Explicit constructor.
		//! @param	game	Game pointer.
		explicit DrawableGameComponent( cbl::Game & game );
		//! Destructor.
		virtual ~DrawableGameComponent();
		//! Abstract function to initialise component (from GameComponent).
		virtual void Initialise( void ) = 0;
		//! Abstract function to shut down component (from GameComponent).
		virtual void Shutdown( void ) = 0;
		//! Pure virtual update function (from IUpdatable).
		virtual void Update( const GameTime & time ) = 0;
		//! Pure virtual draw function (from IDrawable).
		virtual void Draw( const GameTime & time ) = 0;
	};
}

#endif // __CBL_DRAWABLEGAMECOMPONENT_H_
