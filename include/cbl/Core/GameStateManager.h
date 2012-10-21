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
 * @file GameStateManager.h
 * @brief Game state manager.
 */

#ifndef __CBL_GAMESTATEMANAGER_H_
#define __CBL_GAMESTATEMANAGER_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Core/GameState.h"
#include "cbl/Core/Services.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Util/Hash.h"
#include "cbl/Util/Singleton.h"

// External Dependencies //
#include <stack>
#include <map>

namespace cbl
{
	//! Game state manager class.
	class CBL_API GameStateManager :
		Noncopyable
	{
	/***** Public Methods *****/
	public:
		//! Constructor.
		GameStateManager();
		//! Destructor.
		~GameStateManager();
		//! Push state to stack.
		//! @tparam	STATE_TYPE	State type.
		template< typename STATE_TYPE >
		void Push( void );
		//! Push state to stack
		//! @param	type		State type.
		void Push( const CName& type );
		//! Pop state from stack.
		void Pop( void );
		//! Add persistent state.
		//! @tparam	STATE_TYPE	State type.
		//! @param	name		State name.
		template< typename STATE_TYPE >
		void Add( const Hash& name );
		//! Add persistent state.
		//! @param	type		State type.
		//! @param	name		State name.
		void Add( const CName& type, const Hash& name );
		//! Remove persistent state.
		void Remove( const Hash& name );
		//! Get persistent state by name.
		//! @tparam	STATE_TYPE	State type to cast to.
		//! @param	name		State name.
		//! @return				Game state, NULL if doesn't exist.
		template< typename STATE_TYPE >
		STATE_TYPE* Get( const Hash& name ) const;
		//! Get persistent state by name.
		//! @param	name		State name.
		//! @return				Game state, NULL if doesn't exist.
		GameState* Get( const Hash& name ) const;
		//! Initialise and purge states.
		void Update( void );
		//! Clear all stack and persistent states.
		void Clear( void );
		
	/***** Private Types *****/
	private:
		static void ActivateState( GameState* state );
		static void DeactivateState( GameState* state );
		static void ResumeState( GameState* state );
		static void PauseState( GameState* state );

		typedef void (*StateFunction)( GameState* );
		typedef std::pair<GameState*,StateFunction>		StateAction;

		typedef std::unordered_map<Hash, GameState*>	StateMap;
		typedef std::vector<GameState*>					StateArray;
		typedef std::vector<StateAction>				StateActions;
		
	/***** Private Members *****/
	private:
		StateActions		mStateActions;
		StateArray			mStateStack;	//!< Current state stack.
		StateArray			mToDelete;		//!< States to delete.
		StateMap			mStates;		//!< Existing persistent states.

		friend class		Game;
	};
}

#include "GameStateManager.inl"

#endif // __CBL_GAMESTATEMANAGER_H_
