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
 * @file test_Game.cpp
 * @brief Unit testing for game class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Core/Game.h>
#include <cbl/Core/DrawableGameComponent.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

Float64 maxTimeOut	= 1.0;

class TestGame : public Game
{
public:

	TestGame()
		: Game( "TestGame" ),
		timeOut( 0.0 ) {}

	virtual void Update( const GameTime & gameTime )
	{
		Game::Update( gameTime );
		timeOut += static_cast< Real >( gameTime.Elapsed.TotalSeconds() );

		if( timeOut >= maxTimeOut )
		{
			this->Exit();
		}
	}

	virtual void Draw( GameTime const & gameTime )
	{
		Game::Draw( gameTime );
	}

	String			updateOrderTestString;
	String			drawOrderTestString;
	Float64			timeOut;
};

class TestOrderComponent :
	public DrawableGameComponent
{
public:
	explicit TestOrderComponent( TestGame & game, const char * const str )
		: DrawableGameComponent( game ),
		theString( str )
	{
	}

	virtual void Initialise()
	{
	}

	virtual void Update( const GameTime & time )
	{
		static_cast< TestGame & >( Game ).updateOrderTestString += theString;
	}

	virtual void Draw( const GameTime & time )
	{
		static_cast< TestGame & >( Game ).drawOrderTestString += theString;
	}
	
	virtual void Shutdown()
	{
	}

private:
	String				theString;
};

class GameTestFixture : public ::testing::Test
{
protected:

	TestGame		testGame;
};

class GameOrderTestFixture : public ::testing::Test
{
protected:

	void SetUp()
	{
		comp1 = new TestOrderComponent( testGame, "This " );
		comp2 = new TestOrderComponent( testGame, "should " );
		comp3 = new TestOrderComponent( testGame, "be " );
		comp4 = new TestOrderComponent( testGame, "in " );
		comp5 = new TestOrderComponent( testGame, "sequence." );

		comp1->UpdateOrder = 1;
		comp2->UpdateOrder = 2;
		comp3->UpdateOrder = 3;
		comp4->UpdateOrder = 4;
		comp5->UpdateOrder = 5;
		
		comp1->DrawOrder = 1;
		comp2->DrawOrder = 2;
		comp3->DrawOrder = 3;
		comp4->DrawOrder = 4;
		comp5->DrawOrder = 5;

		finalString = "This should be in sequence.";
	}

	void TearDown()
	{
		CBL_DELETE( comp5 );
		CBL_DELETE( comp4 );
		CBL_DELETE( comp3 );
		CBL_DELETE( comp2 );
		CBL_DELETE( comp1 );
	}

	TestOrderComponent	* comp1;
	TestOrderComponent	* comp2;
	TestOrderComponent	* comp3;
	TestOrderComponent	* comp4;
	TestOrderComponent	* comp5;
	TestGame			testGame;
	String				finalString;
};

TEST_F( GameTestFixture, Game_Test )
{
	Stopwatch gameLifeTime;
	gameLifeTime.Start();
	testGame.Run();
	gameLifeTime.Stop();

	// Approximate timeout.
	ASSERT_NEAR( gameLifeTime.GetElapsedTime().TotalSeconds(), testGame.timeOut, 0.1 );
}

TEST_F( GameOrderTestFixture, Game_OrderTest1 )
{
	testGame.Components.Add( comp5 );
	testGame.Components.Add( comp2 );
	testGame.Components.Add( comp3 );
	testGame.Components.Add( comp4 );
	testGame.Components.Add( comp1 );

	testGame.Update( GameTime() );
	testGame.Draw( GameTime() );
	
	testGame.Components.Remove( comp5 );
	testGame.Components.Remove( comp2 );
	testGame.Components.Remove( comp3 );
	testGame.Components.Remove( comp4 );
	testGame.Components.Remove( comp1 );

	// Approximate timeout.
	ASSERT_EQ( testGame.drawOrderTestString, finalString );
	ASSERT_EQ( testGame.updateOrderTestString, finalString );
}

TEST_F( GameOrderTestFixture, Game_OrderTest2 )
{
	testGame.Components.Add( comp5 );
	testGame.Components.Add( comp4 );
	testGame.Components.Add( comp1 );
	testGame.Components.Add( comp3 );
	testGame.Components.Add( comp2 );

	comp2->DrawOrder = -4;
	comp3->DrawOrder = 10;
	comp5->UpdateOrder = 1;
	comp1->UpdateOrder = 20;

	testGame.Update( GameTime() );
	testGame.Draw( GameTime() );
	
	testGame.Components.Remove( comp5 );
	testGame.Components.Remove( comp2 );
	testGame.Components.Remove( comp3 );
	testGame.Components.Remove( comp4 );
	testGame.Components.Remove( comp1 );

	// Approximate timeout.
	ASSERT_NE( testGame.drawOrderTestString, finalString );
	ASSERT_NE( testGame.updateOrderTestString, finalString );
}