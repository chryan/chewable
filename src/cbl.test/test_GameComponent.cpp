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
 * @file test_GameComponent.cpp
 * @brief Unit testing for game component class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Core/GameComponent.h>
#include <cbl/Core/Game.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

class GameComponentTest : public GameComponent
{
public:
	explicit GameComponentTest( cbl::Game & game )
		: GameComponent( game )
	{
	}
	
	virtual ~GameComponentTest()
	{
	}

	void Initialise( void )
	{
		SCOPED_TRACE( "[GameComponentTest] Initialise failed.\n" );
	}

	void Shutdown( void )
	{
		SCOPED_TRACE( "[GameComponentTest] Shutdown failed.\n" );
	}

	void Update( GameTime const & gameTime )
	{
		SCOPED_TRACE( "[GameComponentTest] Update failed.\n" );
	}
};

class GameComponentFixture : public ::testing::Test
{
protected:

	GameComponentFixture()
		: game( "GameComponentFixture" ),
		component( game )
	{
	}

	Game					game;
	GameComponentTest		component;
};

TEST_F( GameComponentFixture, GameComponent_Test )
{
	component.Initialise();
	component.Shutdown();
	component.Update( GameTime() );
}
