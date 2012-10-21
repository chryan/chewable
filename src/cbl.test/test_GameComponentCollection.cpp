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
 * @file test_GameComponentCollection.cpp
 * @brief Unit testing for game component collection class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Core/GameComponent.h>
#include <cbl/Core/DrawableGameComponent.h>
#include <cbl/Core/GameComponentCollection.h>
#include <cbl/Core/Game.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

class TestComponent : public GameComponent
{
public:

	explicit TestComponent( cbl::Game & game )
		: GameComponent( game )
	{
	}
	
	virtual ~TestComponent()
	{
	}

	void Initialise( void )
	{
		SCOPED_TRACE( "[TestComponent] Initialise failed.\n" );
	}

	void Shutdown( void )
	{
		SCOPED_TRACE( "[TestComponent] Shutdown failed.\n" );
	}

	void Update( GameTime const & gameTime )
	{
		SCOPED_TRACE( "[TestComponent] Update failed.\n" );
	}
};

class TestDrawableComponent : public DrawableGameComponent
{
public:

	explicit TestDrawableComponent( cbl::Game & game )
		: DrawableGameComponent( game )
	{
	}
	
	virtual ~TestDrawableComponent()
	{
	}

	void Initialise( void )
	{
		SCOPED_TRACE( "[TestDrawableComponent] Initialise failed.\n" );
	}

	void Shutdown( void )
	{
		SCOPED_TRACE( "[TestDrawableComponent] Shutdown failed.\n" );
	}

	void Update( GameTime const & gameTime )
	{
		SCOPED_TRACE( "[TestDrawableComponent] Update failed.\n" );
	}

	void Draw( GameTime const & gameTime )
	{
		SCOPED_TRACE( "[TestDrawableComponent] Draw failed.\n" );
	}
};

class CompCollectionFixture :
	public ::testing::Test
{
public:

	void OnComponentAdded( GameComponent * component )
	{
		++componentsAdded;
	}

	void OnComponentRemoved( GameComponent * component )
	{
		++componentsRemoved;
	}
	
	void OnDrawableAdded( DrawableGameComponent * component )
	{
		++drawablesAdded;
	}
	
	void OnDrawableRemoved( DrawableGameComponent * component )
	{
		++drawablesRemoved;
	}

	CompCollectionFixture()
		: game( "GameComponentCollectionFixture" ),
		componentsAdded( 0 ), componentsRemoved( 0 ),
		drawablesAdded( 0 ), drawablesRemoved( 0 )
	{
	}

	void SetUp()
	{
		component = new TestComponent( game );
		drawcomponent = new TestDrawableComponent( game );
	}
	
	void TearDown()
	{
		CBL_DELETE( drawcomponent );
		CBL_DELETE( component );
		ASSERT_TRUE( component == NULL );
	}

	Game						game;
	TestComponent				* component;
	TestDrawableComponent		* drawcomponent;
	GameComponentCollection		componentList;

	Uint32						componentsAdded;
	Uint32						componentsRemoved;
	Uint32						drawablesAdded;
	Uint32						drawablesRemoved;
};

using namespace E;

TEST_F( CompCollectionFixture, GameComponentCollection_Test )
{
	componentList.OnComponentAdded += Component::Method<CBL_E_METHOD(CompCollectionFixture,OnComponentAdded)>(this);
	componentList.OnComponentRemoved += Component::Method<CBL_E_METHOD(CompCollectionFixture,OnComponentRemoved)>(this);
	componentList.OnDrawableAdded += DrawComponent::Method<CBL_E_METHOD(CompCollectionFixture,OnDrawableAdded)>(this);
	componentList.OnDrawableRemoved += DrawComponent::Method<CBL_E_METHOD(CompCollectionFixture,OnDrawableRemoved)>(this);

	componentList.Add( component );
	componentList.Remove( component );
	componentList.Add( drawcomponent );
	componentList.Remove( drawcomponent );
	
	componentList.OnDrawableRemoved -= DrawComponent::Method<CBL_E_METHOD(CompCollectionFixture,OnDrawableRemoved)>(this);
	componentList.OnDrawableAdded -= DrawComponent::Method<CBL_E_METHOD(CompCollectionFixture,OnDrawableAdded)>(this);
	componentList.OnComponentRemoved -= Component::Method<CBL_E_METHOD(CompCollectionFixture,OnComponentRemoved)>(this);
	componentList.OnComponentAdded -= Component::Method<CBL_E_METHOD(CompCollectionFixture,OnComponentAdded)>(this);

	ASSERT_EQ( componentsAdded, 2 );
	ASSERT_EQ( componentsRemoved, 2 );
	
	ASSERT_EQ( drawablesAdded, 1 );
	ASSERT_EQ( drawablesRemoved, 1 );
}
