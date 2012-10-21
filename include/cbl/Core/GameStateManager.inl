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
 * @file GameStateManager.inl
 * @brief Game state manager template methods.
 */

namespace cbl
{
	template< typename GAMESTATE_TYPE >
	inline void GameStateManager::Push( void )
	{
		// Force a compile-time type test.
		CBL_ENTITY_TYPETEST( GameState, GAMESTATE_TYPE );
		Push( TypeCName<GAMESTATE_TYPE>() );
	}

	template< typename GAMESTATE_TYPE >
	void GameStateManager::Add( const Hash& name )
	{
		// Force a compile-time type test.
		CBL_ENTITY_TYPETEST( GameState, GAMESTATE_TYPE );
		Add( TypeCName<GAMESTATE_TYPE>(), name );
	}

	template< typename STATE_TYPE >
	inline STATE_TYPE* GameStateManager::Get( const Hash& name ) const
	{
		return static_cast< STATE_TYPE* >( Get( name ) );
	}

	inline GameState* GameStateManager::Get( const Hash& name ) const
	{
		StateMap::const_iterator findit = mStates.find( name );
		return findit != mStates.end() ? findit->second : NULL;
	}
}
