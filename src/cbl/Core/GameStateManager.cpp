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
 * @file GameStateManager.cpp
 * @brief Game state manager definitions.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Core/GameStateManager.h"
#include "cbl/Reflection/EntityManager.h"
#include "cbl/Debug/Logging.h"

using namespace cbl;

GameStateManager::GameStateManager()
{
}

GameStateManager::~GameStateManager()
{
	Clear();
	Update();
}

void GameStateManager::Push( const CName& type )
{
	if( EntityPtr newEnt = (EntityPtr)CBL_ENT.New( type ) ) {
		GameState* state = static_cast<GameState*>( newEnt );

		// Pause the current state on the top of the stack.
		if( !mStateStack.empty() )
			mStateActions.push_back( StateAction( mStateStack.back(), PauseState ) );

		// Push it to the stack.
		mStateStack.push_back( state );

		mStateActions.push_back( StateAction( state, ActivateState ) );
		mStateActions.push_back( StateAction( state, ResumeState ) );
	}
}

void GameStateManager::Pop( void )
{
	if( mStateStack.empty() ) {
		LOG_ERROR( "State stack is empty. Unable to pop." );
		return;
	}

	GameState* state = mStateStack.back();
	mStateStack.pop_back();

	// Pause and deactivate the state we just popped.
	mStateActions.push_back( StateAction( state, PauseState ) );
	mStateActions.push_back( StateAction( state, DeactivateState ) );
	// Resume the state on the top of the stack.
	if( !mStateStack.empty() )
		mStateActions.push_back( StateAction( mStateStack.back(), ResumeState ) );
	// Set the popped state to be deleted.
	mToDelete.push_back( state );
}

void GameStateManager::Add( const CName& type, const Hash& name )
{
	if( mStates.find( name ) != mStates.end() ) {
		LOG_ERROR( "State (" << name << ") already exists." );
		return;
	}

	if( EntityPtr newEnt = (EntityPtr)CBL_ENT.New( type ) ) {
		GameState* state = static_cast<GameState*>( newEnt );
		// Add it to the map.
		mStates.insert( std::make_pair( name, state ) );
		mStateActions.push_back( StateAction( state, ActivateState ) );
		mStateActions.push_back( StateAction( state, ResumeState ) );
	}
}

void GameStateManager::Remove( const Hash& name )
{
	StateMap::iterator findit = mStates.find( name );
	if( findit == mStates.end() ) {
		LOG_ERROR( "State (" << name.GetText() << ") does not exist." );
		return;
	}

	GameState* state = findit->second;
	mStates.erase( findit );

	// Pause and deactivate the state we just removed.
	mStateActions.push_back( StateAction( state, PauseState ) );
	mStateActions.push_back( StateAction( state, DeactivateState ) );
	// Set the popped state to be deleted.
	mToDelete.push_back( state );
}

void GameStateManager::Clear( void )
{
	// Clear all states on stack. Start from the back.
	for( size_t i = mStateStack.size(); i > 0; --i ) {
		mStateActions.push_back( StateAction( mStateStack[i-1], PauseState ) );
		mStateActions.push_back( StateAction( mStateStack[i-1], DeactivateState ) );
		mToDelete.push_back( mStateStack[i-1] );
	}

	CBL_FOREACH( StateMap, it, mStates ) {
		mStateActions.push_back( StateAction( it->second, PauseState ) );
		mStateActions.push_back( StateAction( it->second, DeactivateState ) );
		mToDelete.push_back( it->second );
	}

	mStateStack.clear();
	mStates.clear();
}

void GameStateManager::Update( void )
{
	for( size_t i = 0; i < mStateActions.size(); ++i )
		mStateActions[i].second( mStateActions[i].first );
	mStateActions.clear();

	for( size_t i = 0; i < mToDelete.size(); ++i )
		CBL_ENT.Delete( mToDelete[i] );
	mToDelete.clear();
}

void GameStateManager::ActivateState( GameState* state )
{
	if( !state->mActive )
	{
		state->Activate();
		state->mActive = true;
	}
}

void GameStateManager::DeactivateState( GameState* state )
{
	if( state->mActive )
	{
		state->mActive = false;
		state->Deactivate();
	}
}

void GameStateManager::ResumeState( GameState* state )
{
	if( state->mActive && state->mPaused )
	{
		state->Resume();
		state->mPaused = false;
	}
}

void GameStateManager::PauseState( GameState* state )
{
	if( state->mActive && !state->mPaused )
	{
		state->mPaused = true;
		state->Pause();
	}
}
