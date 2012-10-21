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
 * @file GameState.cpp
 * @brief Game state.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Core/GameState.h"

using namespace cbl;

GameState::GameState()
: mActive( false )
, mPaused( true )
{
}

GameState::~GameState()
{
}

Entity::OPTIONS GameState::OnPreChanged( void )
{
	return Entity::O_NORMAL;
}

void GameState::OnChanged( void )
{
}

Entity::OPTIONS GameState::OnPreSaved( void ) const
{
	return Entity::O_NORMAL;
}

void GameState::OnSaved( void ) const
{
}
