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
 * @file GameState.h
 * @brief Abstract game state class.
 */

#ifndef __CBL_GAMESTATE_H_
#define __CBL_GAMESTATE_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Property.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Reflection/Entity.h"

namespace cbl
{
	//! Abstract game state class.
	class CBL_API GameState :
		public Entity,
		Noncopyable
	{
	/***** Properties *****/
	public:
		GETTER_AUTO( bool, Active );
		GETTER_AUTO( bool, Paused );

	/***** Public Methods *****/
	public:
		//! Destructor.
		virtual ~GameState();
		//! Called when state is added/pushed.
		virtual void Activate( void ) {}
		//! Called when state is removed/popped.
		virtual void Deactivate( void ) {}
		//! Called when a state is popped from the stack and this state is the new state on top.
		virtual void Resume( void ) {}
		//! Called when a state is pushed on to the stack and was the previous state on top.
		virtual void Pause( void ) {}
		//! Called just before the internal representation of the entity changes.
		//! e.g. Before deserialisation.
		virtual Entity::OPTIONS OnPreChanged( void );
		//! Called when the internal representation of the entity changes.
		//! e.g. After deserialisation.
		virtual void OnChanged( void );
		//! Called when the entity is about to be saved.
		//! e.g. Before serialisation.
		virtual Entity::OPTIONS OnPreSaved( void ) const;
		//! Called after the entity is saved.
		//! e.g. After serialisation.
		virtual void OnSaved( void ) const;
		
	/***** Protected Methods *****/
	protected:
		//! Constructor.
		GameState();
		
	/***** Private Members *****/
	private:
		bool			mActive;
		bool			mPaused;
		friend class	GameStateManager;
		friend class	TypeDB;
	};
}

//! Declare the game state's friends
#define CBL_GAMESTATE_FRIENDS\
	friend class ::cbl::GameStateManager;\
	friend class ::cbl::TypeDB;

CBL_TYPE( cbl::GameState, GameState );

#endif // __CBL_GAMESTATE_H_
